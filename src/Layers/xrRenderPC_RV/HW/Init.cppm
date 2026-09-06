module;
#include "SDL3/SDL.h"
#include <format>
#include <vulkan_main.hpp>
extern xr_token *vid_mode_token;

module RV.HW:Init;
import :Interface;

bool useValidationLayers = false;

VKAPI_ATTR VkBool32 VKAPI_CALL
vulkan_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData) {

  std::string severityStr = "[UNKNOWN]";
  if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
    severityStr = "[VERBOSE]";
  } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
    severityStr = "[INFO]";
  } else if (messageSeverity &
             VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
    severityStr = "[WARNING]";
  } else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
    severityStr = "[ERROR]";
  }

  std::string typeStr = "[GENERAL]:";
  if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
    typeStr = "[VALIDATION]:";
  } else if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
    typeStr = "[PERFORMANCE]:";
  }

  std::string result =
      severityStr + typeStr + std::string(" Message ID Name: ") +
      std::string((pCallbackData->pMessageIdName ? pCallbackData->pMessageIdName
                                                 : "None")) +
      std::string(" | Message: ") + pCallbackData->pMessage;

  Msg("[RV]%s", result.c_str());
  return VK_FALSE;
}

void VkHW::CreateDevice(SDL_Window *window, VkExtent2D windowExtent) {
  PROF_EVENT();
  this->window = window;
  this->windowExtent = windowExtent;

  init_vulkan();
  init_swapchain();
  init_commands();
  init_sync_structures();
  init_descriptors();
  init_buffers();

  InitResolutionList();

  isInit = true;
}

void VkHW::DestroyDevice() {
  DestroyResolutionsList();
  // cleanup
}

inline VmaAllocatorCreateFlags
translateToVmaFlags(VkHW::DeviceProperties props) {
  VmaAllocatorCreateFlags ret{};

  if (props.KHR_dedicated_allocation && props.KHR_get_memory_requirements2 &&
      props.KHR_get_physical_device_properties2)
    ret |= VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT;

  if (props.KHR_bind_memory2)
    ret |= VMA_ALLOCATOR_CREATE_KHR_BIND_MEMORY2_BIT;

  if (props.KHR_maintenance4)
    ret |= VMA_ALLOCATOR_CREATE_KHR_MAINTENANCE4_BIT;

  if (props.KHR_maintenance5)
    ret |= VMA_ALLOCATOR_CREATE_KHR_MAINTENANCE5_BIT;

  if (props.EXT_memory_budget && props.KHR_get_physical_device_properties2)
    ret |= VMA_ALLOCATOR_CREATE_EXT_MEMORY_BUDGET_BIT;

  if (props.bufferDeviceAddress)
    ret |= VMA_ALLOCATOR_CREATE_BUFFER_DEVICE_ADDRESS_BIT;

  if (props.EXT_memory_priority && props.KHR_get_physical_device_properties2)
    ret |= VMA_ALLOCATOR_CREATE_EXT_MEMORY_PRIORITY_BIT;

  if (props.AMD_device_coherent_memory &&
      props.KHR_get_physical_device_properties2)
    ret |= VMA_ALLOCATOR_CREATE_AMD_DEVICE_COHERENT_MEMORY_BIT;

  if (props.KHR_external_memory_win32)
    ret |= VMA_ALLOCATOR_CREATE_KHR_EXTERNAL_MEMORY_WIN32_BIT;

  return ret;
}

void VkHW::init_vulkan() {

  VK_CHECK(volkInitialize());

  auto sysInfoRet = vkb::SystemInfo::get_system_info();
  R_ASSERT2(sysInfoRet, sysInfoRet.error().message());

  auto sysInfo = sysInfoRet.value();

  vkb::InstanceBuilder instBuilder;

  instBuilder.set_app_name("Vulkan")
      .require_api_version(1, 4, 0)
      .request_validation_layers(useValidationLayers)
      .set_debug_messenger_severity(
          VkDebugUtilsMessageSeverityFlagBitsEXT::
              VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
      .set_debug_callback(&vulkan_callback);

  if (sysInfo.is_extension_available(
          "VK_KHR_get_physical_device_properties2")) {
    instBuilder.enable_extension("VK_KHR_get_physical_device_properties2");
    props.KHR_get_physical_device_properties2 = true;
  }

  auto ivkres = instBuilder.build();
  R_ASSERT2(ivkres, ivkres.error().message());

  instance = ivkres.value();

  VkInstance ins = instance.instance;
  volkLoadInstance(ins);

  auto sdlres = SDL_Vulkan_CreateSurface(window, instance, nullptr, &surface);
  R_ASSERT2(sdlres, SDL_GetError());

  VkPhysicalDeviceVulkan13Features features13{
      .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES};
  features13.dynamicRendering = true;
  features13.synchronization2 = true;

  VkPhysicalDeviceVulkan12Features features12{
      .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES};
  features12.bufferDeviceAddress = true;
  features12.descriptorIndexing = true;

  vkb::PhysicalDeviceSelector selector{instance};
  physDevice = selector.set_minimum_version(1, 3)
                   .set_required_features_13(features13)
                   .set_required_features_12(features12)
                   .set_surface(surface)
                   .select()
                   .value();

  props.KHR_get_memory_requirements2 =
      physDevice.enable_extension_if_present("VK_KHR_get_memory_requirements2");
  props.KHR_dedicated_allocation =
      physDevice.enable_extension_if_present("VK_KHR_dedicated_allocation");
  props.KHR_bind_memory2 =
      physDevice.enable_extension_if_present("VK_KHR_bind_memory2");
  props.EXT_memory_budget =
      physDevice.enable_extension_if_present("VK_EXT_memory_budget");
  props.KHR_maintenance4 =
      physDevice.enable_extension_if_present("VK_KHR_maintenance4");
  props.KHR_maintenance5 =
      physDevice.enable_extension_if_present("VK_KHR_maintenance5");
  props.bufferDeviceAddress = true;
  props.EXT_memory_priority =
      physDevice.enable_extension_if_present("VK_EXT_memory_priority");
  props.AMD_device_coherent_memory =
      physDevice.enable_extension_if_present("VK_AMD_device_coherent_memory");
  props.KHR_external_memory_win32 =
      physDevice.enable_extension_if_present("VK_KHR_external_memory_win32");

  // TODO:
  physDevice.enable_extension_if_present("VK_EXT_descriptor_buffer");
  physDevice.enable_extension_if_present("VK_EXT_calibrated_timestamps");
  physDevice.enable_extension_if_present("VK_EXT_host_query_reset");
  vkGetPhysicalDeviceProperties(physDevice, &deviceCaps);

  vkb::DeviceBuilder deviceBuilder{physDevice};
  auto dvkres = deviceBuilder.build();
  R_ASSERT2(dvkres, dvkres.error().message());

  device = dvkres.value();
  auto qRes = device.get_queue(vkb::QueueType::graphics);
  R_ASSERT2(qRes, qRes.error().message());

  volkLoadDevice(device);

  graphicsQueue = qRes.value();
  graphicsQueueFamily =
      device.get_queue_index(vkb::QueueType::graphics).value();

  VmaVulkanFunctions vmaFuncs = {};

  VmaAllocatorCreateInfo allocInfo = {
      .flags = translateToVmaFlags(props),
      .physicalDevice = device.physical_device,
      .device = device.device,
      .pVulkanFunctions = &vmaFuncs,
      .instance = instance.instance,
  };

  vmaImportVulkanFunctionsFromVolk(&allocInfo, &vmaFuncs);
  vmaCreateAllocator(&allocInfo, &allocator);
  TracyGPUMemNotify(allocator);

  tracyCtx = TracyVkContextHostCalibrated(
      instance, physDevice, device, vkGetInstanceProcAddr, vkGetDeviceProcAddr);

  TracyVkContextName(tracyCtx, deviceCaps.deviceName,
                     strlen(deviceCaps.deviceName));
  // vmaDestroyAllocator(allocator); });
}

void VkHW::init_commands() {
  auto cmdInfo = util::createCommandPoolInfo(
      graphicsQueueFamily, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);

  for (size_t i = 0; i < frame_overlap; ++i) {
    VK_CHECK(
        vkCreateCommandPool(device, &cmdInfo, nullptr, &frames[i].cmdPool));

    auto allocInfo = util::createBufferAllocateInfo(frames[i].cmdPool, 1);

    VK_CHECK(
        vkAllocateCommandBuffers(device, &allocInfo, &frames[i].cmdBuffer));
  }

  { // Immediate cmd buffers
    VK_CHECK(vkCreateCommandPool(device, &cmdInfo, nullptr, &immCmdPool));
    auto immAllocInfo = util::createBufferAllocateInfo(immCmdPool, 1);
    VK_CHECK(vkAllocateCommandBuffers(device, &immAllocInfo, &immCmdBuff));
  }
}

// TODO: update drawImageExtern whenever window updates own size.
void VkHW::init_swapchain() {
  create_swapchain(windowExtent);

  VkExtent3D drawImageExtent{
      .width = windowExtent.width,
      .height = windowExtent.height,
      .depth = 1,
  };

  VmaAllocationCreateInfo ringAllocInfo = {
      .usage = VMA_MEMORY_USAGE_GPU_ONLY,
      .requiredFlags =
          VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
  };

  { // Draw Image
    drawImage.imageFormat = VK_FORMAT_R16G16B16A16_SFLOAT;
    drawImage.imageExtent = drawImageExtent;

    VkImageUsageFlags drawImageUsage =
        VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
        VK_IMAGE_USAGE_STORAGE_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT |
        VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;

    auto rimgInfo = util::imageCreateInfo(drawImage.imageFormat, drawImageUsage,
                                          drawImageExtent);

    VK_CHECK(vmaCreateImage(allocator, &rimgInfo, &ringAllocInfo,
                            &drawImage.image, &drawImage.alloc, nullptr));
    TracyGPUMemNotify(allocator);

    auto rviewInfo = util::imageViewCreateInfo(
        drawImage.imageFormat, drawImage.image, VK_IMAGE_ASPECT_COLOR_BIT);

    VK_CHECK(
        vkCreateImageView(device, &rviewInfo, nullptr, &drawImage.imageView));
  }

  { // Depth Image
    depthImage.imageFormat = VK_FORMAT_D32_SFLOAT;
    depthImage.imageExtent = drawImageExtent;

    VkImageUsageFlags depthImageUsage =
        VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    VkImageCreateInfo dimgInfo = util::imageCreateInfo(
        depthImage.imageFormat, depthImageUsage, depthImage.imageExtent);

    VK_CHECK(vmaCreateImage(allocator, &dimgInfo, &ringAllocInfo,
                            &depthImage.image, &depthImage.alloc, nullptr));
    TracyGPUMemNotify(allocator);

    VkImageViewCreateInfo dviewInfo = util::imageViewCreateInfo(
        depthImage.imageFormat, depthImage.image, VK_IMAGE_ASPECT_DEPTH_BIT);

    VK_CHECK(
        vkCreateImageView(device, &dviewInfo, nullptr, &depthImage.imageView));
  }
}

void VkHW::init_sync_structures() {
  auto semaphoreInfo = util::createSempahoreInfo();
  auto fenceInfo = util::createFenceInfo(VK_FENCE_CREATE_SIGNALED_BIT);

  for (size_t i = 0; i < frame_overlap; ++i) {
    VK_CHECK(vkCreateFence(device, &fenceInfo, nullptr, &frames[i].fence));
    VK_CHECK(vkCreateSemaphore(device, &semaphoreInfo, nullptr,
                               &frames[i].renderSemaphore));
    VK_CHECK(vkCreateSemaphore(device, &semaphoreInfo, nullptr,
                               &frames[i].swapchainSemaphore));

    { // tracy Image
      frames[i].tracyImage.imageFormat = TracyImageFormat;
      frames[i].tracyImage.imageExtent = TracyExtent;

      VkImageUsageFlags imageUsage =
          VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;

      VmaAllocationCreateInfo ringAllocInfo = {
          .usage = VMA_MEMORY_USAGE_GPU_ONLY,
          .requiredFlags =
              VkMemoryPropertyFlags(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
      };

      auto rimgInfo =
          util::imageCreateInfo(TracyImageFormat, imageUsage, TracyExtent);

      VK_CHECK(vmaCreateImage(allocator, &rimgInfo, &ringAllocInfo,
                              &frames[i].tracyImage.image,
                              &frames[i].tracyImage.alloc, nullptr));
      TracyGPUMemNotify(allocator);

      auto rviewInfo = util::imageViewCreateInfo(TracyImageFormat,
                                                 frames[i].tracyImage.image,
                                                 VK_IMAGE_ASPECT_COLOR_BIT);

      VK_CHECK(vkCreateImageView(device, &rviewInfo, nullptr,
                                 &frames[i].tracyImage.imageView));
    }

    { // tracy buffer
      auto bufferSize = TracyExtent.width * TracyExtent.height * 4;
      frames[i].tracyBuffer =
          createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                       VMA_MEMORY_USAGE_GPU_TO_CPU);
    }
  }

  VK_CHECK(vkCreateFence(device, &fenceInfo, nullptr, &immFence));
}
void VkHW::init_descriptors() {
  for (size_t i = 0; i < frame_overlap; ++i) {
    std::vector<DescriptorAllocatorGrowable::PoolSizeRatio> frameSizes{
        {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 3},
        {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 3},
        {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 3},
        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 4},
    };

    frames[i].frameDescriptors = DescriptorAllocatorGrowable{};
    frames[i].frameDescriptors.init(device, 1000, frameSizes);
  }

  // allocate default descriptors here
  std::vector<DescriptorAllocatorGrowable::PoolSizeRatio> globalPoolRatios{
      {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 3},
      {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 3},
      {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 3},
      {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 4},
  };

  globalDescriptorAllocator = DescriptorAllocatorGrowable{};
  globalDescriptorAllocator.init(device, 1000, globalPoolRatios);

  // GPU_Scenedata
  DescriptorLayoutBuilder layoutBuilder;
  layoutBuilder.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
  sceneDescriptorLayout = layoutBuilder.build(device, VK_SHADER_STAGE_ALL);
  sceneDescriptorSet =
      globalDescriptorAllocator.allocate(device, sceneDescriptorLayout);
}

void VkHW::init_buffers() {
  sceneDataBuffer =
      createBuffer(sizeof(GPU_SceneData), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                   VMA_MEMORY_USAGE_CPU_TO_GPU);
  DescriptorWriter sceneWriter;
  sceneWriter.write_buffer(0, sceneDataBuffer.buffer, sizeof(GPU_SceneData), 0,
                           VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
  sceneWriter.updatee_set(device, sceneDescriptorSet);

  VkSamplerCreateInfo samplerInfo{
      .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
      .magFilter = VK_FILTER_LINEAR,
      .minFilter = VK_FILTER_LINEAR,
      .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .anisotropyEnable = VK_FALSE,
      .compareEnable = VK_FALSE,
      .unnormalizedCoordinates = VK_FALSE,
      .mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
      .mipLodBias = 0.0f,
      .minLod = 0.0f,
      .maxLod = 0.0f,
  };

  VK_CHECK(vkCreateSampler(device, &samplerInfo, nullptr, &linearSampler));
}

auto VkHW::InitResolutionList() -> void {
  std::vector<std::string> resolutions;

  int displayCount = 0;
  SDL_DisplayID *displays = SDL_GetDisplays(&displayCount);
  if (displays) {
    for (auto i = 0; i < displayCount; i++) {
      int modeCount = 0;
      SDL_DisplayMode **modes =
          SDL_GetFullscreenDisplayModes(displays[i], &modeCount);
      if (modes) {
        // store only one resolution from subset {wxh} * refresh_rate
        float refreshRate = 0;
        uint32_t w = 0;
        uint32_t h = 0;
        for (auto j = 0; j < modeCount; j++) {
          if (w == modes[j]->w && h == modes[j]->h &&
              refreshRate != modes[j]->refresh_rate)
            continue;

          resolutions.push_back(std::format("{}x{}", modes[j]->w, modes[j]->h));

          refreshRate = modes[i]->refresh_rate;
          w = modes[j]->w;
          h = modes[j]->h;
        }
        SDL_free(modes);
      }
    }
    SDL_free(displays);
  }

  vid_mode_token = xr_alloc<xr_token>(resolutions.size());
  vid_mode_token[resolutions.size()].id = -1;
  vid_mode_token[resolutions.size()].name = nullptr;

  for (auto i = 0; i < resolutions.size(); i++) {
    vid_mode_token[i].id = i;
    vid_mode_token[i].name = xr_strdup(resolutions[i].c_str());
  }
}

auto VkHW::DestroyResolutionsList() -> void {
  xr_token *t = vid_mode_token;
  while (t) {
    xr_free(t->name);
    t++;
  }
  xr_free(vid_mode_token);
}