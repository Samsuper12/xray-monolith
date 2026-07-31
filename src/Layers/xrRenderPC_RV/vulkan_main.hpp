#pragma once 

#include <volk.h>
#define VMA_STATIC_VULKAN_FUNCTIONS 0
#define VMA_DYNAMIC_VULKAN_FUNCTIONS 0
#include "vk_mem_alloc.h"
#include <VkBootstrap.h>
#include <SDL3/SDL_vulkan.h>
#include "log.h"

inline void VK_CHECK(VkResult x) {
  if (x != VK_SUCCESS) {
    Msg("Vulkan check error: %s", x);
    std::runtime_error(std::string(" Detected Vulkan error: ") +
                       std::to_string(x));
  }
}

struct AllocatedBuffer {
  VkBuffer buffer;
  VmaAllocation allocation;
  VmaAllocationInfo info;
};

struct AllocatedImage {
  VkImage image;
  VkImageView imageView;
  VmaAllocation alloc;
  VkExtent3D imageExtent;
  VkFormat imageFormat;
};
