#include "VkHW.hpp"
#include "utils/vkUtil.hpp"

#ifdef DEBUG
bool useValidationLayers = true;
#else
bool useValidationLayers = false;
#endif

void VkHW::CreateDevice(SDL_Window *window, VkExtent2D windowExtent) {
  this->window = window;
  this->windowExtent = windowExtent;

  init_vulkan();
  init_swapchain();
  init_commands();
  init_sync_structures();
  init_descriptors();
  init_pipelines();
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
      .require_api_version(1, 3, 0)
      .request_validation_layers(useValidationLayers)
      .set_debug_messenger_severity(
          VkDebugUtilsMessageSeverityFlagBitsEXT::
              VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
      .use_default_debug_messenger();

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

  // TODO: mainDeletionQueue.pushFunction([&]() {
  // vmaDestroyAllocator(allocator); });
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
  R_ASSERT2(vkres, vkres.error().message());

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

void VkHW::init_swapchain() {
  create_swapchain(windowExtent, false);
  
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
}
void VkHW::init_commands() {}
void VkHW::init_sync_structures() {}
void VkHW::init_descriptors() {}
void VkHW::init_pipelines() {}
void VkHW::resize_swapchain() {}


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

VkHW HW;