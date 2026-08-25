#include "vkUIRender.hpp"
#include "VkHW.hpp"
#include "render_stub.hpp"
#include "vkUIShader.hpp"
#include <LocatorAPI.h>
#include <device.h>

vkUIRender UIRenderImpl;

vkUIRender::vkUIRender() : arenaSize(16384 * 10), skipCurrentDraw(false) {}

void vkUIRender::CreateUIGeom() {
  vertexArena = HW.createBuffer(sizeof(GPU_Vertex) * arenaSize,
                                VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                                    VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
                                VMA_MEMORY_USAGE_CPU_TO_GPU);

  VkBufferDeviceAddressInfo deviceAddressInfo{
      .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
      .buffer = vertexArena.buffer,
  };

  vertexArenaAddress = vkGetBufferDeviceAddress(HW.device, &deviceAddressInfo);
  arenaCursor = 0;
  vertexIndex = 0;
}

void vkUIRender::DestroyUIGeom() { HW.destroyBuffer(vertexArena); }

void vkUIRender::SetShader(IUIShader &shader) {
  auto *vkShader = dynamic_cast<vkUIShader *>(&shader);
  auto currentFrameIndex = HW.frameNumber;

  if (currentFrameIndex != lastFrameIndex) {
    lastFrameIndex = currentFrameIndex;
    keepAliveUI.clear();
    arenaCursor = 0;
    vertexIndex = 0;
  }
  
  if (!vkShader->shaderPass || !vkShader->texture) {
    skipCurrentDraw = true;
    Msg("[RV][ATTENTION]: Skipping UIShader: %s, %s",
        vkShader->shaderName.c_str(), vkShader->textureName.c_str());
    return;
  }

  arenaCursor += vertexIndex;
  vertexIndex = 0;

  keepAliveUI.push_back(dynamic_cast<vkUIShader *>(&shader));
  skipCurrentDraw = false;
}

void vkUIRender::SetAlphaRef(int aref) { render_stub(); }

void vkUIRender::SetScissor(Irect *rect) {
  auto cmd = HW.get_current_frame().cmdBuffer;
  VkRect2D targetScissor;

  if (!rect) {
    targetScissor = VkRect2D{
        .offset =
            {
                .x = 0,
                .y = 0,
            },
        .extent =
            {
                .width = HW.drawExtent.width,
                .height = HW.drawExtent.height,
            },
    };

  } else {
    targetScissor = VkRect2D{
        .offset =
            {
                .x = rect->left,
                .y = rect->top,
            },
        .extent =
            {
                .width = static_cast<uint32_t>(rect->right - rect->left),
                .height = static_cast<uint32_t>(rect->bottom - rect->top),
            },
    };
  }
  vkCmdSetScissor(cmd, 0, 1, &targetScissor);
}

void vkUIRender::GetActiveTextureResolution(Fvector2 &res) {
  if (skipCurrentDraw) {
    res.set(0.0, 0.0);
    return;
  }

  res.set(float(keepAliveUI.back()->texture->imageExtent.width),
          float(keepAliveUI.back()->texture->imageExtent.height));
}

void vkUIRender::StartPrimitive(u32 iMaxVerts, ePrimitiveType primType,
                                ePointType pointType) {
  if (arenaCursor + iMaxVerts > arenaSize) {
    Msg("[RV][ERR]: Too many vertices: %d", arenaCursor + iMaxVerts);
    skipCurrentDraw = true;
  }

  if (pointType == IUIRender::pttLIT || primType != ptTriList) {
    Msg("[RV][ERR]: Current primitive isn't supported yet");
    skipCurrentDraw = true;
    return;
  }
}

void vkUIRender::PushPoint(float x, float y, float z, u32 C, float u, float v) {
  GPU_Vertex *vertex = static_cast<GPU_Vertex *>(vertexArena.info.pMappedData);
  vertex[arenaCursor + vertexIndex++] = {
      util::normalizeToScreenNDC(glm::vec3(x, y, 0), HW.drawExtent.width,
                           HW.drawExtent.height),
      u,
      glm::vec3(0),
      v,
      glm::vec4(0),
  };
}

void vkUIRender::FlushPrimitive() {
  if (keepAliveUI.empty())
    return;

  auto *currentUI = keepAliveUI.back();
  auto cmd = HW.get_current_frame().cmdBuffer;

  HW.set_ActiveTextureExtent(currentUI->texture->imageExtent);

  VkRenderingAttachmentInfo colorAttachment =
      util::colorAttachmentInfo(HW.drawImage.imageView, std::nullopt);
  VkRenderingAttachmentInfo depthAttachment = util::depthAttachmentInfo(
      HW.depthImage.imageView, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL);

  auto renderingInfo =
      util::renderingInfo(HW.drawExtent, &colorAttachment, &depthAttachment);
  VkDescriptorSet frameDescriptorSet =
      HW.get_current_frame().frameDescriptors.allocate(
          HW.device, currentUI->shaderPass->inputs.descriptorLayouts);

  DescriptorWriter dWriter;
  dWriter.write_image(0, currentUI->texture->imageView, HW.linearSampler,
                      VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                      VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
  dWriter.updatee_set(HW.device, frameDescriptorSet);

  GPU_UIPC pc{
      .base.vertexBufferPtr = vertexArenaAddress,
      .base.vertexIndex = arenaCursor,
      .layerIndex = currentUI->textureLayer,
  };

  std::array descriptorSets = {HW.sceneDescriptorSet, frameDescriptorSet};
  vkCmdBeginRendering(cmd, &renderingInfo);
  vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS,
                    currentUI->shaderPass->pipeline);
  vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS,
                          currentUI->shaderPass->pipelineLayout, 0,
                          descriptorSets.size(), descriptorSets.data(), 0,
                          nullptr);
  vkCmdPushConstants(cmd, currentUI->shaderPass->pipelineLayout,
                     VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(GPU_UIPC),
                     &pc);
  vkCmdDraw(cmd, vertexIndex, 1, 0, 0);
  vkCmdEndRendering(cmd);

  if (currentUI->isAnimation)
    currentUI->OnFrame();
}

LPCSTR vkUIRender::UpdateShaderName(LPCSTR tex_name, LPCSTR sh_name) {
  // TODO:
  // string_path buff;
  // if (FS.exist(buff, "$game_textures$", tex_name, ".ogm"))
  //   return "hud/movie";
  // else
  return sh_name;
}

void vkUIRender::CacheSetXformWorld(const Fmatrix &M) { render_stub(); }

void vkUIRender::CacheSetCullMode(CullMode) { render_stub(); }