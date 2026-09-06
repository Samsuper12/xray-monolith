module;
#include <vulkan_main.hpp>
#include <ktx.h>
#include <ktxvulkan.h>
module RV.HW:Allocation;
import :Interface;

void VkHW::immediateSubmit(std::function<void(VkCommandBuffer cmd)> &&f) {
  PROF_EVENT();
  VK_CHECK(vkResetFences(device, 1, &immFence));
  VK_CHECK(vkResetCommandBuffer(immCmdBuff, 0));

  auto cmd = immCmdBuff;
  auto cmdBeginInfo =
      util::cmdBufferBeginInfo(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

  VK_CHECK(vkBeginCommandBuffer(cmd, &cmdBeginInfo));
  f(cmd);
  VK_CHECK(vkEndCommandBuffer(cmd));

  auto submitInfo = util::cmdBufferSubmitInfo(cmd);
  auto submit = util::submitInfo2(&submitInfo, nullptr, nullptr);

  VK_CHECK(vkQueueSubmit2(graphicsQueue, 1, &submit, immFence));
  VK_CHECK(vkWaitForFences(device, 1, &immFence, true, 9999999999));
}

AllocatedImage VkHW::createImage(VkExtent3D size, VkFormat format,
                                 VkImageUsageFlags flags, bool mipmapped,
                                 uint32_t layers) {
  PROF_EVENT();
  AllocatedImage newImage{
      .imageExtent = size,
      .imageFormat = format,
      .layersCount = layers,
  };

  VkImageCreateInfo imgInfo = util::imageCreateInfo(format, flags, size);

  if (mipmapped)
    imgInfo.mipLevels = static_cast<uint32_t>(std::floor(
                            std::log2(std::max(size.width, size.height)))) +
                        1;

  VmaAllocationCreateInfo allocInfo{.usage = VMA_MEMORY_USAGE_GPU_ONLY,
                                    .requiredFlags = VkMemoryPropertyFlags(
                                        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)};

  VK_CHECK(vmaCreateImage(allocator, &imgInfo, &allocInfo, &newImage.image,
                          &newImage.alloc, nullptr));
  TracyGPUMemNotify(allocator);

  VkImageAspectFlags aspect = (format == VK_FORMAT_D32_SFLOAT)
                                  ? VK_IMAGE_ASPECT_DEPTH_BIT
                                  : VK_IMAGE_ASPECT_COLOR_BIT;

  VkImageViewCreateInfo viewInfo =
      util::imageViewCreateInfo(format, newImage.image, aspect);
  VK_CHECK(vkCreateImageView(device, &viewInfo, nullptr, &newImage.imageView));

  return newImage;
}

AllocatedImage VkHW::createImage(void *data, uint32_t dataSize, VkExtent3D size,
                                 VkFormat format, VkImageUsageFlags flags,
                                 bool mipmapped, uint32_t layers) {
  PROF_EVENT();
  // size_t data_size = size.depth * size.height * size.width * 4;
  AllocatedBuffer staging = createBuffer(
      dataSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_TO_GPU);
  memcpy(staging.info.pMappedData, data, dataSize);

  AllocatedImage newImage = createImage(size, format, flags, mipmapped, layers);
  VkImageAspectFlags aspect = (format == VK_FORMAT_D32_SFLOAT)
                                  ? VK_IMAGE_ASPECT_DEPTH_BIT
                                  : VK_IMAGE_ASPECT_COLOR_BIT;

  immediateSubmit([&](VkCommandBuffer cmd) {
    util::transition_umage(cmd, newImage.image, VK_IMAGE_LAYOUT_UNDEFINED,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

    VkBufferImageCopy copyRegion{
        .bufferOffset = 0,
        .bufferRowLength = 0,
        .bufferImageHeight = 0,
        .imageExtent = size,
    };

    copyRegion.imageSubresource = {
        .aspectMask = aspect,
        .mipLevel = 0,
        .baseArrayLayer = 0,
        .layerCount = 1,
    };

    vkCmdCopyBufferToImage(cmd, staging.buffer, newImage.image,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1,
                           &copyRegion);

    util::transition_umage(cmd, newImage.image,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                           VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  });

  destroyBuffer(staging);

  return newImage;
}

// TODO: 3D/ArrayTexture
AllocatedImage VkHW::createImage(rv::texture::ktxTexsturePtr_t ktxTexturePtr,
                                 VkImageUsageFlags flags) {
  PROF_EVENT();
  VkExtent3D extent{
      .width = ktxTexturePtr->baseWidth,
      .height = ktxTexturePtr->baseHeight,
      .depth = 1,
  };

  VkFormat format = ktxTexture2_GetVkFormat(ktxTexturePtr.get());
  uint32_t dataSize = ktxTexture_GetDataSize(ktxTexture(ktxTexturePtr.get()));

  AllocatedImage newImage{
      .imageExtent = extent,
      .imageFormat = format,
      .layersCount = ktxTexturePtr->numLayers,
  };

  VkImageCreateInfo imgInfo = util::imageCreateInfo(format, flags, extent);
  imgInfo.mipLevels = ktxTexturePtr->numLevels;
  imgInfo.arrayLayers = ktxTexturePtr->numLayers;

  VmaAllocationCreateInfo allocInfo{.usage = VMA_MEMORY_USAGE_GPU_ONLY,
                                    .requiredFlags = VkMemoryPropertyFlags(
                                        VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)};

  VK_CHECK(vmaCreateImage(allocator, &imgInfo, &allocInfo, &newImage.image,
                          &newImage.alloc, nullptr));
  TracyGPUMemNotify(allocator);

  VkImageAspectFlags aspect = (format == VK_FORMAT_D32_SFLOAT)
                                  ? VK_IMAGE_ASPECT_DEPTH_BIT
                                  : VK_IMAGE_ASPECT_COLOR_BIT;

  VkImageViewCreateInfo viewInfo =
      util::imageViewCreateInfo(format, newImage.image, aspect);

  if (ktxTexturePtr->numLayers > 1) {
    viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D_ARRAY;
  }
  viewInfo.subresourceRange = {
      .aspectMask = aspect,
      .baseMipLevel = 0,
      .levelCount = ktxTexturePtr->numLevels,
      .baseArrayLayer = 0,
      .layerCount = ktxTexturePtr->numLayers,
  };

  VK_CHECK(vkCreateImageView(device, &viewInfo, nullptr, &newImage.imageView));

  AllocatedBuffer staging = createBuffer(
      dataSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_TO_GPU);
  memcpy(staging.info.pMappedData, ktxTexturePtr->pData, dataSize);

  immediateSubmit([&](VkCommandBuffer cmd) {
    util::transition_umage(cmd, newImage.image, VK_IMAGE_LAYOUT_UNDEFINED,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

    std::vector<VkBufferImageCopy> bufferCopyRegions;

    for (uint32_t level = 0; level < ktxTexturePtr->numLevels; ++level) {

      ktx_size_t offset;
      ktxTexture_GetImageOffset(ktxTexture(ktxTexturePtr.get()), level, 0, 0,
                                &offset);

      VkBufferImageCopy copyRegion{
          .bufferOffset = offset,
          .bufferRowLength = 0,
          .bufferImageHeight = 0,
          .imageExtent =
              VkExtent3D{
                  .width = std::max(1u, ktxTexturePtr->baseWidth >> level),
                  .height = std::max(1u, ktxTexturePtr->baseHeight >> level),
                  .depth = 1,
              },
      };

      copyRegion.imageSubresource = {
          .aspectMask = aspect,
          .mipLevel = level,
          .baseArrayLayer = 0,
          .layerCount = ktxTexturePtr->numLayers,
      };

      bufferCopyRegions.push_back(copyRegion);
    }

    vkCmdCopyBufferToImage(cmd, staging.buffer, newImage.image,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                           bufferCopyRegions.size(), bufferCopyRegions.data());

    util::transition_umage(cmd, newImage.image,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                           VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  });

  destroyBuffer(staging);

  return newImage;
}

AllocatedBuffer VkHW::createBuffer(size_t allocSize, VkBufferUsageFlags usage,
                                   VmaMemoryUsage memoryUsage) {
  PROF_EVENT();
  VkBufferCreateInfo bufferInfo{
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .pNext = nullptr,
      .size = allocSize,
      .usage = usage,
  };

  VmaAllocationCreateInfo vmaAlloc{
      .flags = VMA_ALLOCATION_CREATE_MAPPED_BIT,
      .usage = memoryUsage,
  };

  AllocatedBuffer buffer;
  VK_CHECK(vmaCreateBuffer(allocator, &bufferInfo, &vmaAlloc, &buffer.buffer,
                           &buffer.allocation, &buffer.info));
  TracyGPUMemNotify(allocator);
  return buffer;
}

auto VkHW::formatIsSupported(VkFormat format) -> bool {
  // TODO: .pNext contains additional info about format.
  VkFormatProperties2 out{
      .sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2,
  };
  vkGetPhysicalDeviceFormatProperties2(physDevice, format, &out);

  if (out.formatProperties.optimalTilingFeatures &
      VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT != 0) {
    return true;
  }
}