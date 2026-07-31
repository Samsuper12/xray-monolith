#pragma once
#include "SDL3/SDL.h"
#include "vulkan_main.hpp"
#include <vector>
#include <algorithm>

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

  void CreateDevice(SDL_Window *window, VkExtent2D windowExtent);
  void DestroyDevice();

  void immediateSubmit(std::function<void(VkCommandBuffer cmd)> &&f);
  auto create_buffer()-> void {}


private:
  void init_vulkan();
  void init_swapchain();
  void init_commands();
  void init_sync_structures();
  void init_descriptors();
  void init_pipelines();

  void resize_swapchain();
  void create_swapchain(VkExtent2D extent, bool recreate = false);

public:
  vkb::Instance instance;
  vkb::Device device;
  vkb::Swapchain swapchain;

  VkFence immFence;
  VkCommandBuffer immCmdBuff;
  VkCommandPool immCmdPool;

  std::vector<VkImage> swapchainImages;
  std::vector<VkImageView> swapchainImageViews;
  VkExtent2D swapchainExtent;
  VkExtent2D drawExtent;
  VkExtent2D windowExtent;;
  float renderScale;

  SDL_Window *window;

  VkSurfaceKHR surface;
  VkQueue graphicsQueue;
  uint32_t graphicsQueueFamily;

VmaAllocator allocator;

};

extern VkHW HW;