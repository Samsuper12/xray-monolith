#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <optional>
#include <vector>

#include "vkDescriptorWriter.hpp"

namespace util {
inline VkCommandPoolCreateInfo
createCommandPoolInfo(uint32_t familyIndex, VkCommandPoolCreateFlags flags) {
  return VkCommandPoolCreateInfo{
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .pNext = nullptr,
      .flags = flags,
      .queueFamilyIndex = familyIndex,
  };
}

inline VkCommandBufferAllocateInfo createBufferAllocateInfo(VkCommandPool pool,
                                                            uint32_t count) {
  return VkCommandBufferAllocateInfo{
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .pNext = nullptr,
      .commandPool = pool,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = count,
  };
}

inline VkFenceCreateInfo createFenceInfo(VkFenceCreateFlags flags = 0) {
  return VkFenceCreateInfo{
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
      .pNext = nullptr,
      .flags = flags,
  };
}

inline VkSemaphoreCreateInfo
createSempahoreInfo(VkSemaphoreCreateFlags flags = 0) {
  return VkSemaphoreCreateInfo{
      .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
      .pNext = nullptr,
      .flags = flags,
  };
}

inline VkCommandBufferBeginInfo
cmdBufferBeginInfo(VkCommandBufferUsageFlags flags = 0) {
  return VkCommandBufferBeginInfo{
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .pNext = nullptr,
      .flags = flags,
      .pInheritanceInfo = nullptr,
  };
}

inline VkImageSubresourceRange
imageSubresourceRange(VkImageAspectFlags aspectMask) {
  return VkImageSubresourceRange{
      .aspectMask = aspectMask,
      .baseMipLevel = 0,
      .levelCount = VK_REMAINING_MIP_LEVELS,
      .baseArrayLayer = 0,
      .layerCount = VK_REMAINING_ARRAY_LAYERS,
  };
}

inline void transition_umage(VkCommandBuffer cmd, VkImage img,
                             VkImageLayout oldLayout, VkImageLayout newLayout) {

  VkImageAspectFlags aspectMask =
      (newLayout == VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL)
          ? VK_IMAGE_ASPECT_DEPTH_BIT
          : VK_IMAGE_ASPECT_COLOR_BIT;

  VkImageMemoryBarrier2 barrier = {
      .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER_2,
      .pNext = nullptr,
      .srcStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
      .srcAccessMask = VK_ACCESS_2_MEMORY_WRITE_BIT,
      .dstStageMask = VK_PIPELINE_STAGE_2_ALL_COMMANDS_BIT,
      .dstAccessMask =
          VK_ACCESS_2_MEMORY_WRITE_BIT | VK_ACCESS_2_MEMORY_READ_BIT,
      .oldLayout = oldLayout,
      .newLayout = newLayout,
      .image = img,
      .subresourceRange = util::imageSubresourceRange(aspectMask),
  };

  VkDependencyInfo depInfo = {
      .sType = VK_STRUCTURE_TYPE_DEPENDENCY_INFO,
      .pNext = nullptr,
      .imageMemoryBarrierCount = 1,
      .pImageMemoryBarriers = &barrier,
  };

  vkCmdPipelineBarrier2(cmd, &depInfo);
}

inline VkSemaphoreSubmitInfo
semaphoreSubmitInfo(VkPipelineStageFlagBits2 stageMask, VkSemaphore semaphore) {
  return VkSemaphoreSubmitInfo{
      .sType = VK_STRUCTURE_TYPE_SEMAPHORE_SUBMIT_INFO,
      .pNext = nullptr,
      .semaphore = semaphore,
      .value = 1,
      .stageMask = stageMask,
      .deviceIndex = 0,
  };
}

inline VkCommandBufferSubmitInfo cmdBufferSubmitInfo(VkCommandBuffer cmd) {
  return VkCommandBufferSubmitInfo{
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_SUBMIT_INFO,
      .pNext = nullptr,
      .commandBuffer = cmd,
      .deviceMask = 0,
  };
}

inline VkSubmitInfo2 submitInfo2(VkCommandBufferSubmitInfo *cmd,
                                 VkSemaphoreSubmitInfo *signalSemaphore,
                                 VkSemaphoreSubmitInfo *waitSemaphore) {

  uint32_t signalCount = (signalSemaphore == nullptr ? 0 : 1);
  uint32_t waitCount = (waitSemaphore == nullptr ? 0 : 1);
  return VkSubmitInfo2{
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO_2,
      .pNext = nullptr,
      .waitSemaphoreInfoCount = waitCount,
      .pWaitSemaphoreInfos = waitSemaphore,
      .commandBufferInfoCount = 1,
      .pCommandBufferInfos = cmd,
      .signalSemaphoreInfoCount = signalCount,
      .pSignalSemaphoreInfos = signalSemaphore,
  };
}

inline VkImageCreateInfo imageCreateInfo(VkFormat format,
                                         VkImageUsageFlags usageFlags,
                                         VkExtent3D extent) {
  return VkImageCreateInfo{
      .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
      .pNext = nullptr,
      .imageType = VK_IMAGE_TYPE_2D,
      .format = format,
      .extent = extent,
      .mipLevels = 1,
      .arrayLayers = 1,
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .tiling = VK_IMAGE_TILING_OPTIMAL,
      .usage = usageFlags,
  };
}

inline VkImageViewCreateInfo
imageViewCreateInfo(VkFormat format, VkImage image,
                    VkImageAspectFlags aspectMask) {
  return VkImageViewCreateInfo{
      .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
      .pNext = nullptr,
      .image = image,
      .viewType = VK_IMAGE_VIEW_TYPE_2D,
      .format = format,
      .subresourceRange = {
        .aspectMask = aspectMask,
        .baseMipLevel = 0,
        .levelCount = 1,
        .baseArrayLayer = 0,
        .layerCount = 1,
      },
  };
}

inline void copyImageToImage(VkCommandBuffer cmd, VkImage src, VkImage dst,
                             VkExtent2D srcSize, VkExtent2D dstSize) {
  VkImageBlit2 blitRegion{
      .sType = VK_STRUCTURE_TYPE_IMAGE_BLIT_2,
      .pNext = nullptr,
      .srcSubresource = {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .mipLevel = 0,
        .baseArrayLayer = 0,
        .layerCount = 1,
      },
      
      .dstSubresource = {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .mipLevel = 0,
        .baseArrayLayer = 0,
        .layerCount = 1,
      }, 

  };

  blitRegion.srcOffsets[1] = {
        .x = static_cast<int32_t>(srcSize.width),
        .y = static_cast<int32_t>(srcSize.height),
        .z = 1,
      };

      blitRegion .dstOffsets[1] = {
        .x = static_cast<int32_t>(dstSize.width),
        .y = static_cast<int32_t>(dstSize.height),
        .z = 1,
      };

  VkBlitImageInfo2 blitInfo{
      .sType = VK_STRUCTURE_TYPE_BLIT_IMAGE_INFO_2,
      .pNext = nullptr,
      .srcImage = src,
      .srcImageLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
      .dstImage = dst,
      .dstImageLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      .regionCount = 1,
      .pRegions = &blitRegion,
      .filter = VK_FILTER_LINEAR,
  };

  vkCmdBlitImage2(cmd, &blitInfo);
}

inline VkRenderingAttachmentInfo colorAttachmentInfo(
    VkImageView view, std::optional<VkClearValue> clear,
    VkImageLayout layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
  VkRenderingAttachmentInfo colorInfo{
      .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
      .pNext = nullptr,
      .imageView = view,
      .imageLayout = layout,
      .loadOp =
          clear ? VK_ATTACHMENT_LOAD_OP_CLEAR : VK_ATTACHMENT_LOAD_OP_LOAD,
      .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
  };

  if (clear)
    colorInfo.clearValue = clear.value();

  return colorInfo;
}

inline VkRenderingInfo
renderingInfo(VkExtent2D extent, VkRenderingAttachmentInfo *colorAttachment,
              VkRenderingAttachmentInfo *depthAttachment) {
  return VkRenderingInfo{.sType = VK_STRUCTURE_TYPE_RENDERING_INFO,
                         .pNext = nullptr,
                         .renderArea = VkRect2D{.extent = extent},
                         .layerCount = 1,
                         .colorAttachmentCount = 1,
                         .pColorAttachments = colorAttachment,
                         .pDepthAttachment = depthAttachment};
}

inline bool load_shader_module(const char *filePath, VkDevice device,
                               VkShaderModule *outShaderModule) {
  // open the file. With cursor at the end
  std::ifstream file(filePath, std::ios::ate | std::ios::binary);

  if (!file.is_open()) {
    return false;
  }

  // find what the size of the file is by looking up the location of the cursor
  // because the cursor is at the end, it gives the size directly in bytes
  size_t fileSize = (size_t)file.tellg();

  // spirv expects the buffer to be on uint32, so make sure to reserve a int
  // vector big enough for the entire file
  std::vector<uint32_t> buffer(fileSize / sizeof(uint32_t));

  // put file cursor at beginning
  file.seekg(0);

  // load the entire file into the buffer
  file.read((char *)buffer.data(), fileSize);

  // now that the file is loaded into the buffer, we can close it
  file.close();

  // create a new shader module, using the buffer we loaded
  VkShaderModuleCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.pNext = nullptr;

  // codeSize has to be in bytes, so multply the ints in the buffer by size of
  // int to know the real size of the buffer
  createInfo.codeSize = buffer.size() * sizeof(uint32_t);
  createInfo.pCode = buffer.data();

  // check that the creation goes well.
  VkShaderModule shaderModule;
  if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) !=
      VK_SUCCESS) {
    return false;
  }
  *outShaderModule = shaderModule;
  return true;
}

inline VkPipelineShaderStageCreateInfo
createShaderStage(VkShaderStageFlagBits stage, VkShaderModule module,
                  std::optional<const char *> name) {
  return VkPipelineShaderStageCreateInfo{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .pNext = nullptr,
      .stage = stage,
      .module = module,
      .pName = "main",
  };
}

inline VkRenderingAttachmentInfo depthAttachmentInfo(
    VkImageView view,
    VkImageLayout layout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL) {
  return VkRenderingAttachmentInfo{
      .sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO,
      .pNext = nullptr,
      .imageView = view,
      .imageLayout = layout,
      .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
      .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
      .clearValue = {.depthStencil = {.depth = 0.f}}
  };
}

template <typename T> struct MmapedBuffer {
  std::span<T> data;
  T *raw_data;
  VmaAllocator allocator;
  VmaAllocation allocation;
};

template <typename T> static inline void base_vma_unmmap(MmapedBuffer<T> *m) {
  vmaUnmapMemory(m->allocator, m->allocation);
  delete (m);
}

template <typename T>
using buffer_ptr_t =
    std::unique_ptr<MmapedBuffer<T>, decltype(&base_vma_unmmap<T>)>;

template <typename T>
inline buffer_ptr_t<T> getBufferPointer(VmaAllocator allocator,
                                        const AllocatedBuffer &buf) {

  MmapedBuffer<T> *buf_data = new MmapedBuffer<T>{};
  buf_data->allocator = allocator;
  buf_data->allocation = buf.allocation;
  vmaMapMemory(buf_data->allocator, buf_data->allocation,
               reinterpret_cast<void **>(&buf_data->raw_data));

  VmaAllocationInfo tmpAllocInfo;
  vmaGetAllocationInfo(buf_data->allocator, buf_data->allocation,
                       &tmpAllocInfo);
  buf_data->data =
      std::span<T>(buf_data->raw_data, tmpAllocInfo.size / sizeof(T));

  return buffer_ptr_t<T>(buf_data, &base_vma_unmmap<T>);
}


template buffer_ptr_t<float> getBufferPointer(VmaAllocator allocator,
                                              const AllocatedBuffer &buf);

                                              static inline VmaAllocator dumbAlloc;

} // namespace util
