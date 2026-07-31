#pragma once
#include <glm_main.hpp>
#include "vulkan_main.hpp"

#include <deque>
#include <span>

struct DescriptorAllocatorGrowable {
  struct PoolSizeRatio {
    VkDescriptorType type;
    float ratio;
  };

  void init(VkDevice device, uint32_t maxSets,
                std::span<PoolSizeRatio> poolRatios) {
    ratios.clear();

    for (auto ratio : poolRatios)
      ratios.push_back(ratio);

    auto newPool = create_pool(device, maxSets, poolRatios);
    setsPerPool = maxSets * 1.6; // Golden Rule
    readyPools.push_back(newPool);
  }

  auto clear_pools(VkDevice device) {
    for (auto pool : readyPools)
      vkResetDescriptorPool(device, pool, 0);

    for (auto pool : fullPools) {
      vkResetDescriptorPool(device, pool, 0);
      readyPools.push_back(pool);
    }

    fullPools.clear();
  }

  auto destroy_pools(VkDevice device) {
    for (auto pool : readyPools)
      vkDestroyDescriptorPool(device, pool, nullptr);

    for (auto pool : fullPools) {
      vkDestroyDescriptorPool(device, pool, nullptr);
    }
    readyPools.clear();
    fullPools.clear();
  }

  auto allocate(VkDevice device, VkDescriptorSetLayout layout,
                void *pNext = nullptr) -> VkDescriptorSet {
    VkDescriptorPool usePool = get_pool(device);
    VkDescriptorSet set;

    VkDescriptorSetAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .pNext = pNext,
        .descriptorPool = usePool,
        .descriptorSetCount = 1,
        .pSetLayouts = &layout,
    };

    auto res = vkAllocateDescriptorSets(device, &allocInfo, &set);

    if (res == VK_ERROR_OUT_OF_POOL_MEMORY || VK_ERROR_FRAGMENTED_POOL) {
      fullPools.push_back(usePool);
      usePool = get_pool(device);
      allocInfo.descriptorPool = usePool;
      VK_CHECK(vkAllocateDescriptorSets(device, &allocInfo, &set));
    }

    readyPools.push_back(usePool);
    return set;
  }

private:
  auto get_pool(VkDevice device) -> VkDescriptorPool {
    VkDescriptorPool newPool;
    if (!readyPools.empty()) {
      newPool = readyPools.back();
      readyPools.pop_back();
    } else {
      newPool = create_pool(device, setsPerPool, ratios);
      setsPerPool = setsPerPool * 1.6; // Golden Rule.
      if (setsPerPool > 4092)
        setsPerPool = 4092;
    }
    return newPool;
  }

  auto create_pool(VkDevice device, uint32_t setCount,
                   std::span<PoolSizeRatio> poolRatios) -> VkDescriptorPool {
    std::vector<VkDescriptorPoolSize> poolSizes;
    VkDescriptorPool newPool;
    for (auto ratio : poolRatios) {
      poolSizes.push_back(VkDescriptorPoolSize{
          .type = ratio.type,
          .descriptorCount = static_cast<uint32_t>(ratio.ratio * setCount)});
    }

    VkDescriptorPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .flags = 0,
        .maxSets = setCount,
        .poolSizeCount = static_cast<uint32_t>(poolSizes.size()),
        .pPoolSizes = poolSizes.data(),
    };

    vkCreateDescriptorPool(device, &poolInfo, nullptr, &newPool);
    return newPool;
  }

  std::vector<PoolSizeRatio> ratios;
  std::vector<VkDescriptorPool> fullPools;
  std::vector<VkDescriptorPool> readyPools;
  size_t setsPerPool;
};

struct DescriptorWriter {
  std::deque<VkDescriptorImageInfo> imageInfos;
  std::deque<VkDescriptorBufferInfo> bufferInfos;
  std::vector<VkWriteDescriptorSet> writes;

  auto write_image(uint32_t bindingIndex, VkImageView image, VkSampler sampler,
                   VkImageLayout layout, VkDescriptorType type) -> void {
    VkDescriptorImageInfo &info = imageInfos.emplace_back(VkDescriptorImageInfo{
        .sampler = sampler,
        .imageView = image,
        .imageLayout = layout,
    });

    VkWriteDescriptorSet write = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .pNext = nullptr,
        .dstSet = VK_NULL_HANDLE,

        .dstBinding = bindingIndex,
        .descriptorType = type,
        .pImageInfo = &info,
    };

    writes.push_back(write);
  }

  auto write_sampler(uint32_t bindingIndex, VkSampler) -> void {
    write_image(bindingIndex, VK_NULL_HANDLE, VK_NULL_HANDLE,
                VK_IMAGE_LAYOUT_UNDEFINED, VK_DESCRIPTOR_TYPE_SAMPLER);
  }

  auto write_buffer(uint32_t bindingIndex, VkBuffer buffer, size_t size,
                    size_t offset, VkDescriptorType type) -> void {
    VkDescriptorBufferInfo &info =
        bufferInfos.emplace_back(VkDescriptorBufferInfo{
            .buffer = buffer,
            .offset = offset,
            .range = size,
        });

    VkWriteDescriptorSet write = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .pNext = nullptr,
        .dstSet = VK_NULL_HANDLE,

        .dstBinding = bindingIndex,
        .descriptorType = type,
        .pBufferInfo = &info,
    };

    writes.push_back(write);
  }

  auto clear() -> void {
    imageInfos.clear();
    bufferInfos.clear();
    writes.clear();
  }

  auto updatee_set(VkDevice device, VkDescriptorSet set) -> void {
    for (auto &write : writes)
      write.dstSet = set;

    vkUpdateDescriptorSets(device, static_cast<uint32_t>(writes.size()),
                           writes.data(), 0, nullptr);
  }
};