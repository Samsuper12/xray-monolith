#pragma once
#include "SDL3/SDL.h"
#include "utils/vkDescriptorWriter.hpp"
#include "vulkan_main.hpp"
#include <algorithm>
#include <vector>

constexpr uint32_t frame_overlap = 2;
struct FrameData {
  VkCommandPool cmdPool;
  VkCommandBuffer cmdBuffer;
  VkSemaphore swapchainSemaphore, renderSemaphore;
  VkFence fence;
  // DeletionQueue deletionQueue;

  DescriptorAllocatorGrowable frameDescriptors;
};

class VkHW {
public:
  struct DeviceProperties {
    bool KHR_dedicated_allocation;
    bool KHR_bind_memory2;
    bool EXT_memory_budget;
    bool KHR_maintenance4;
    bool KHR_maintenance5;
    bool bufferDeviceAddress;
    bool EXT_memory_priority;
    bool AMD_device_coherent_memory;
    bool KHR_external_memory_win32;
    bool KHR_get_memory_requirements2;
    bool KHR_get_physical_device_properties2;
  } props{};

  bool IsReady;

  VkHW() : renderScale(1.0), window(nullptr) {};
  ~VkHW() = default;

  // Probably this should move in rv.cpp
  inline FrameData &get_current_frame() {
    return frames[frameNumber % frame_overlap];
  }

  auto BeginRendering() -> void;
  auto EndRendering() -> void;

  void CreateDevice(SDL_Window *window, VkExtent2D windowExtent);
  void DestroyDevice();

  void immediateSubmit(std::function<void(VkCommandBuffer cmd)> &&f);
  AllocatedBuffer createBuffer(size_t allocSize, VkBufferUsageFlags usage,
                               VmaMemoryUsage memoryUsage);

private:
  void init_vulkan();
  void init_swapchain();
  void init_commands();
  void init_sync_structures();
  void init_descriptors();
  void resize_swapchain();
  void create_swapchain(VkExtent2D extent, bool recreate = false);

public:
  vkb::Instance instance;
  vkb::Device device;
  vkb::Swapchain swapchain;

  uint32_t frameNumber{0};
  FrameData frames[frame_overlap];
  uint32_t swapchainImgIndex;

  VkFence immFence;
  VkCommandBuffer immCmdBuff;
  VkCommandPool immCmdPool;

  std::vector<VkImage> swapchainImages;
  std::vector<VkImageView> swapchainImageViews;
  VkExtent2D swapchainExtent;
  VkExtent2D drawExtent;
  VkExtent2D windowExtent;


  SDL_Window *window;
  bool request_resize{false};
  bool isInit{false};
  bool stopRendering{false};
  float renderScale{1.0f};

  VkSurfaceKHR surface;
  VkQueue graphicsQueue;
  uint32_t graphicsQueueFamily;

  VmaAllocator allocator;

  AllocatedImage drawImage;
  AllocatedImage depthImage;
};

extern VkHW HW;