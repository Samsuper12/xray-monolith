module;
#include <glm_main.hpp>
#include <vulkan_main.hpp>
module RV.HW:Rendering;
import :Interface;

inline auto fmatrix_to_glm(const Fmatrix &m) -> glm::mat4 const {
  return glm::mat4{
      m._11, m._12, m._13, m._14, m._21, m._22, m._23, m._24,
      m._31, m._32, m._33, m._34, m._41, m._42, m._43, m._44,
  };
}

void VkHW::BeginRendering() {
  PROF_EVENT();
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

  vmaInvalidateAllocation(allocator, frameData.tracyBuffer.allocation, 0,
                          VK_WHOLE_SIZE);

  FrameImage(frameData.tracyBuffer.info.pMappedData, TracyExtent.width,
             TracyExtent.height, 0, false);

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
  // FIXME:!
  auto m_view = glm::mat4(1);    // fmatrix_to_glm(Device.mView);
  auto m_project = glm::mat4(1); // fmatrix_to_glm(Device.mProject);

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
  PROF_EVENT();
  auto cmd = get_current_frame().cmdBuffer;
  auto tracyImage = get_current_frame().tracyImage;
  auto tracyBuffer = get_current_frame().tracyBuffer;

  util::transition_umage(cmd, drawImage.image,
                         VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                         VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);

  { // tracy
    util::transition_umage(cmd, tracyImage.image, VK_IMAGE_LAYOUT_UNDEFINED,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
    util::copyImageToImage(
        cmd, drawImage.image, tracyImage.image, drawExtent,
        VkExtent2D{.width = TracyExtent.width, .height = TracyExtent.height});
    util::transition_umage(cmd, tracyImage.image,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                           VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);

    util::copyImageToBuffer(cmd, tracyImage, tracyBuffer);
  }

  { // render target to swapchain
    util::transition_umage(cmd, swapchainImages[swapchainImgIndex],
                           VK_IMAGE_LAYOUT_UNDEFINED,
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

    util::copyImageToImage(cmd, drawImage.image,
                           swapchainImages[swapchainImgIndex], drawExtent,
                           swapchainExtent);

    util::transition_umage(cmd, swapchainImages[swapchainImgIndex],
                           VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                           VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
  }

  TracyVkCollect(tracyCtx, cmd);
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
  TracyVkCollectHost(tracyCtx);

  if (request_resize)
    resize_swapchain();
}