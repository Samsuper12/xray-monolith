#include "VkHW.hpp"
#include "utils/Descriptors.hpp"
#include "utils/vkUtil.hpp"

// #ifdef DEBUG
// bool useValidationLayers = true;
// #else
// bool useValidationLayers = false;
// #endif

inline auto fmatrix_to_glm(const Fmatrix &m) -> glm::mat4 const {
  return glm::mat4{
      m._11, m._12, m._13, m._14, m._21, m._22, m._23, m._24,
      m._31, m._32, m._33, m._34, m._41, m._42, m._43, m._44,
  };
}

bool useValidationLayers = true;

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
}

void VkHW::CreateDevice(SDL_Window *window, VkExtent2D windowExtent) {
  this->window = window;
  this->windowExtent = windowExtent;

  init_vulkan();
  init_swapchain();
  init_commands();
  init_sync_structures();
  init_descriptors();
  init_buffers();

  isInit = true;
}

void VkHW::DestroyDevice() {
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
  vkb::PhysicalDevice physDevice = selector.set_minimum_version(1, 3)
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

  physDevice.enable_extension_if_present("VK_EXT_descriptor_buffer");

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

//-------------------------------
AllocatedImage VkHW::createImage(VkExtent3D size, VkFormat format,
                                 VkImageUsageFlags flags, bool mipmapped,
                                 uint32_t layers) {
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

void VkHW::immediateSubmit(std::function<void(VkCommandBuffer cmd)> &&f) {
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

void VkHW::create_swapchain(VkExtent2D extent, bool recreate) {
  vkb::SwapchainBuilder swapchainBuilder{device};

  swapchainBuilder.set_desired_format({.format = VK_FORMAT_B8G8R8_UNORM})
      .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
      .set_desired_extent(extent.width, extent.height)
      .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT);

  if (recreate)
    swapchainBuilder.set_old_swapchain(swapchain);

  auto vkres = swapchainBuilder.build();

  if (!vkres) {
    swapchain.swapchain = VK_NULL_HANDLE;
    std::runtime_error(vkres.error().message());
  }

  if (recreate) {
    vkb::destroy_swapchain(swapchain);
    swapchainImages.clear();
    swapchainImageViews.clear();
  }

  swapchain = vkres.value();
  swapchainImages = swapchain.get_images().value();
  swapchainImageViews = swapchain.get_image_views().value();
  swapchainExtent = swapchain.extent;
}

void VkHW::resize_swapchain() {
  vkDeviceWaitIdle(device);
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  windowExtent.width = w;
  windowExtent.height = h;

  create_swapchain(windowExtent, true);
  request_resize = false;
}

AllocatedBuffer VkHW::createBuffer(size_t allocSize, VkBufferUsageFlags usage,
                                   VmaMemoryUsage memoryUsage) {
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
  return buffer;
}

void VkHW::BeginRendering() {

  VK_CHECK(
      vkWaitForFences(device, 1, &get_current_frame().fence, true, 1000000000));
  VK_CHECK(vkResetFences(device, 1, &get_current_frame().fence));
  // get_current_frame().deletionQueue.flush();
  get_current_frame().frameDescriptors.clear_pools(device);

  VkResult swapchainErr = vkAcquireNextImageKHR(
      device, swapchain, 1000000000, get_current_frame().swapchainSemaphore,
      nullptr, &swapchainImgIndex);

  if (swapchainErr == VK_ERROR_OUT_OF_DATE_KHR) {
    request_resize = true;
    return;
  }

  auto &frameData = get_current_frame();

  auto cmd = frameData.cmdBuffer;
  VK_CHECK(vkResetCommandBuffer(cmd, 0));

  auto cmdBegin =
      util::cmdBufferBeginInfo(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

  drawExtent.width =
      std::min(drawImage.imageExtent.width, swapchainExtent.width) *
      renderScale;
  drawExtent.height =
      std::min(drawImage.imageExtent.height, swapchainExtent.height) *
      renderScale;

  VkViewport vp{
      .x = 0,
      .y = 0,
      .width = static_cast<float>(drawExtent.width),
      .height = static_cast<float>(drawExtent.height),
      .minDepth = 0.0f,
      .maxDepth = 1.0f,
  };

  VkRect2D scissor{
      .offset =
          {
              .x = 0,
              .y = 0,
          },
      .extent =
          {
              .width = drawExtent.width,
              .height = drawExtent.height,
          },
  };

  auto m_view = fmatrix_to_glm(Device.mView);
  auto m_project = fmatrix_to_glm(Device.mProject);

  auto *sceneData =
      static_cast<GPU_SceneData *>(sceneDataBuffer.info.pMappedData);
  *sceneData = GPU_SceneData{};

  glm::mat4 m_Texgen{1.0f};
  // u_compute_texgen_screen ?
  // TODO:
  sceneData->m_W = m_Texgen;
  sceneData->m_WV = sceneData->m_V * sceneData->m_W;
  sceneData->m_WVP = sceneData->m_P * sceneData->m_WV;
  sceneData->m_V = m_view;
  sceneData->m_WV = sceneData->m_V * sceneData->m_W;
  sceneData->m_VP = sceneData->m_P * sceneData->m_V;
  sceneData->m_WVP = sceneData->m_P * sceneData->m_WV;
  sceneData->m_P = m_project;
  sceneData->m_VP = sceneData->m_P * sceneData->m_V;
  sceneData->m_WVP = sceneData->m_P * sceneData->m_WV;

  // TODO:
  sceneData->deltaTime = 0;
  sceneData->frameNumber = frameNumber;

  set_ActiveTextureExtent(VkExtent3D{drawExtent.width, drawExtent.height, 1});

  VK_CHECK(vkBeginCommandBuffer(cmd, &cmdBegin));

  vkCmdSetViewport(cmd, 0, 1, &vp);
  vkCmdSetScissor(cmd, 0, 1, &scissor);

  util::transition_umage(cmd, drawImage.image, VK_IMAGE_LAYOUT_UNDEFINED,
                         VK_IMAGE_LAYOUT_GENERAL);

  // compute pipelines here

  util::transition_umage(cmd, drawImage.image, VK_IMAGE_LAYOUT_GENERAL,
                         VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
  util::transition_umage(cmd, depthImage.image, VK_IMAGE_LAYOUT_UNDEFINED,
                         VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL);

  // drawImage ready to use as resulting image
}

void VkHW::EndRendering() {
  auto cmd = get_current_frame().cmdBuffer;

  util::transition_umage(cmd, drawImage.image,
                         VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                         VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);

  util::transition_umage(cmd, swapchainImages[swapchainImgIndex],
                         VK_IMAGE_LAYOUT_UNDEFINED,
                         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

  util::copyImageToImage(cmd, drawImage.image,
                         swapchainImages[swapchainImgIndex], drawExtent,
                         swapchainExtent);

  // TODO: remove this transition later
  util::transition_umage(cmd, swapchainImages[swapchainImgIndex],
                         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                         VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
  //--------

  util::transition_umage(cmd, swapchainImages[swapchainImgIndex],
                         VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                         VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

  VK_CHECK(vkEndCommandBuffer(cmd));

  auto cmdSubmitInfo = util::cmdBufferSubmitInfo(cmd);

  auto waitInfo =
      util::semaphoreSubmitInfo(VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT,
                                get_current_frame().swapchainSemaphore);
  auto signalInfo =
      util::semaphoreSubmitInfo(VK_PIPELINE_STAGE_2_ALL_GRAPHICS_BIT,
                                get_current_frame().renderSemaphore);
  auto submit = util::submitInfo2(&cmdSubmitInfo, &signalInfo, &waitInfo);

  VK_CHECK(
      vkQueueSubmit2(graphicsQueue, 1, &submit, get_current_frame().fence));

  VkPresentInfoKHR present = {
      .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
      .pNext = nullptr,
      .waitSemaphoreCount = 1,
      .pWaitSemaphores = &get_current_frame().renderSemaphore,
      .swapchainCount = 1,
      .pSwapchains = &swapchain.swapchain,
      .pImageIndices = &swapchainImgIndex,
  };

  VkResult presentErr = vkQueuePresentKHR(graphicsQueue, &present);

  if (presentErr == VK_ERROR_OUT_OF_DATE_KHR) {
    request_resize = true;
  }

  frameNumber++;

  if (request_resize)
    resize_swapchain();
}

VkHW HW;