#pragma once
#include "SDL3/SDL.h"
#include "render_factory/vkUIRender.hpp"
#include "utils/Structs.hpp"
#include "utils/vkUtil.hpp"
#include <algorithm>
#include <vector>

// TODO: refactor this shit.
// TODO: use better image format than rgba8 for swapchain. And don't forget
// about tracy.

static constexpr VkFormat TracyImageFormat = VK_FORMAT_R8G8B8A8_UNORM;
static constexpr VkExtent3D TracyExtent = {
    .width = 640, .height = 360, .depth = 1}; // Maximum.

static constexpr uint32_t frame_overlap = 1;
struct FrameData {
  VkCommandPool cmdPool;
  VkCommandBuffer cmdBuffer;
  VkSemaphore swapchainSemaphore, renderSemaphore;
  VkFence fence;
  // DeletionQueue deletionQueue;
  DescriptorAllocatorGrowable frameDescriptors;

  // tracy
  AllocatedImage tracyImage;
  AllocatedBuffer tracyBuffer;
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
  AllocatedImage createImage(VkExtent3D size, VkFormat format,
                             VkImageUsageFlags flags, bool mipmapped = false,
                             uint32_t layers = 1);
  AllocatedImage createImage(void *data, uint32_t dataSize, VkExtent3D size,
                             VkFormat format, VkImageUsageFlags flags,
                             bool mipmapped = false, uint32_t layers = 1);
  AllocatedImage createImage(rv::texture::ktxTexsturePtr_t ktxtexture,
                             VkImageUsageFlags flags);

  void deleteImage(AllocatedImage img) {
    vkDestroyImageView(device, img.imageView, nullptr);
    vmaDestroyImage(allocator, img.image, img.alloc);
  }

  void destroyBuffer(const AllocatedBuffer &buffer) {
    vmaDestroyBuffer(allocator, buffer.buffer, buffer.allocation);
  }

  auto get_ActiveTextureExtent() -> VkExtent3D const {
    return currentTextureExtent;
  }
  auto set_ActiveTextureExtent(VkExtent3D extent) {
    currentTextureExtent = extent;
  };

  // TODO: searches only for sampledimage bit. Extend later
  auto formatIsSupported(VkFormat format) -> bool;

private:
  void init_vulkan();
  void init_swapchain();
  void init_commands();
  void init_sync_structures();
  void init_descriptors();
  void init_buffers();

  auto InitResolutionList() -> void;
  auto DestroyResolutionsList() -> void;
  void resize_swapchain();
  void create_swapchain(VkExtent2D extent, bool recreate = false);

public:
  vkb::Instance instance;
  vkb::PhysicalDevice physDevice;
  vkb::Device device;
  vkb::Swapchain swapchain;

  uint64_t frameNumber{0};
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

  DescriptorAllocatorGrowable globalDescriptorAllocator;

  // Scene SSBO
  VkDescriptorSet sceneDescriptorSet;
  VkDescriptorSetLayout sceneDescriptorLayout;
  GPU_SceneData sceneData;
  GPU_SceneData *sceneDataWritePtr;
  AllocatedBuffer sceneDataBuffer;

  VkSampler linearSampler;

  VkPhysicalDeviceProperties deviceCaps;

  VkExtent3D currentTextureExtent;

  TracyVkCtx tracyCtx;
};

extern VkHW HW;