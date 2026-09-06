module;
#include <vulkan_main.hpp>
module RV.HW:Swapchain;
import :Interface;

void VkHW::create_swapchain(VkExtent2D extent, bool recreate) {
  vkb::SwapchainBuilder swapchainBuilder{device};

  swapchainBuilder.set_desired_format({.format = VK_FORMAT_R8G8B8A8_UNORM})
      .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
      .set_desired_extent(extent.width, extent.height)
      .add_image_usage_flags(VK_IMAGE_USAGE_TRANSFER_DST_BIT |
                             VK_IMAGE_USAGE_TRANSFER_SRC_BIT);

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