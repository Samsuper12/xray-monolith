#include "vkImGuiRender.hpp"
#include "render_stub.hpp"
#include "utils/vkUtil.hpp"
#include <imgui/backends/imgui_impl_sdl3.h>
#include <imgui/backends/imgui_impl_vulkan.h>
#include <imgui/imgui.h>

void vkImGuiRender::SetState(ImDrawData *data) {
  // TODO:
  // viewport.x = 0;
  // viewport.y = 0;
  // viewport.width = static_cast<uint32_t>(data->DisplaySize.x);
  // viewport.height = static_cast<uint32_t>(data->DisplaySize.y);
  // viewport.minDepth = 0;
  // viewport.maxDepth = 1.0f;
}

void vkImGuiRender::Copy(IImGuiRender &_in) {
  *this = *fast_dynamic_cast<vkImGuiRender *>(&_in);
}

void vkImGuiRender::Frame() {
  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplSDL3_NewFrame();
}

void vkImGuiRender::Render(ImDrawData *data) {
  auto frameData = HW.get_current_frame();
  auto cmd = frameData.cmdBuffer;

  auto colorAttach =
      util::colorAttachmentInfo(HW.drawImage.imageView, std::nullopt,
                                VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

  VkExtent2D extent {
    .width = HW.drawImage.imageExtent.width,
    .height = HW.drawImage.imageExtent.height,
  };

  auto renderInfo = util::renderingInfo(extent, &colorAttach, nullptr);

  vkCmdBeginRendering(cmd, &renderInfo);
  ImGui_ImplVulkan_RenderDrawData(data, cmd);
  vkCmdEndRendering(cmd);
}

void vkImGuiRender::OnDeviceCreate(ImGuiContext *context) {
  VkDescriptorPoolSize pool_sizes[] = {
      {VK_DESCRIPTOR_TYPE_SAMPLER, 1000},
      {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000},
      {VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000},
      {VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000},
      {VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000},
      {VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000},
      {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000},
      {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000},
      {VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000},
      {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000},
      {VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000}};

  VkDescriptorPoolCreateInfo pool_info = {};
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
  pool_info.maxSets = 1000;
  pool_info.poolSizeCount = (uint32_t)std::size(pool_sizes);
  pool_info.pPoolSizes = pool_sizes;

  VK_CHECK(vkCreateDescriptorPool(HW.device, &pool_info, nullptr, &imguiPool));

  ImGui::SetCurrentContext(context);

  ImGui_ImplSDL3_InitForVulkan(HW.window);

  ImGui_ImplVulkan_InitInfo init_info = {};
  init_info.Instance = HW.instance;
  init_info.PhysicalDevice = HW.device.physical_device;
  init_info.Device = HW.device;
  init_info.Queue = HW.graphicsQueue;
  init_info.DescriptorPool = imguiPool;
  init_info.MinImageCount = 3;
  init_info.ImageCount = 3;
  init_info.UseDynamicRendering = true;
  init_info.ApiVersion = VK_API_VERSION_1_3;
  init_info.PipelineInfoMain.PipelineRenderingCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_RENDERING_CREATE_INFO};
  init_info.PipelineInfoMain.PipelineRenderingCreateInfo.colorAttachmentCount =
      1;
  init_info.PipelineInfoMain.PipelineRenderingCreateInfo
      .pColorAttachmentFormats = &HW.drawImage.imageFormat;
  init_info.PipelineInfoMain.MSAASamples = VK_SAMPLE_COUNT_1_BIT;

  ImGui_ImplVulkan_Init(&init_info);
}

void vkImGuiRender::OnDeviceDestroy() { 
  ImGui_ImplVulkan_Shutdown();
  vkDestroyDescriptorPool(HW.device, imguiPool, nullptr);
}

void vkImGuiRender::OnDeviceResetBegin() {}

void vkImGuiRender::OnDeviceResetEnd() {}