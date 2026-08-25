#include "vkFontRender.hpp"
#include "VkHW.hpp"
#include "render_stub.hpp"
#include "utils/vkUtil.hpp"
#include "vkRenderDeviceRender.hpp"
#include "vkUIRender.hpp"

extern Fvector2 g_current_font_scale;

vkFontRender::vkFontRender() : vertexBufferSize(16384 * 6) {
  vertexBuffer = HW.createBuffer(sizeof(GPU_Vertex) * vertexBufferSize,
                                 VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
                                     VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT,
                                 VMA_MEMORY_USAGE_CPU_TO_GPU);
  VkBufferDeviceAddressInfo info{
      .sType = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO,
      .buffer = vertexBuffer.buffer,
  };

  vertexBufferAddress = vkGetBufferDeviceAddress(HW.device, &info);
}

vkFontRender::~vkFontRender() { HW.destroyBuffer(vertexBuffer); }

void vkFontRender::Initialize(LPCSTR cShader, LPCSTR cTexture) {

  auto texItt = DEV->m_textures.find(cTexture);

  if (auto shaderItt = DEV->m_passes.find(cShader);
      shaderItt != DEV->m_passes.end()) {
    shaderPass = shaderItt->second;
  } else {
    DescriptorLayoutBuilder layoutBuilder;
    layoutBuilder.addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);

    PipelineInput pipelineInput = {
        .globalDescriptorLayout = HW.sceneDescriptorLayout,
        .descriptorLayouts =
            {
                layoutBuilder.build(HW.device, VK_SHADER_STAGE_FRAGMENT_BIT),
            },
        .pcRanges = {
            VkPushConstantRange{.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
                                .offset = 0,
                                .size = sizeof(GPU_BasePushConstantData)},
        }};

    PipelineConfig cfg{
        .blend = PipelineBlend::AlphaBlend,
        .zTest = false,
        .zWrite = false,
    };
    shaderPass = DEV->createPass(cShader, cfg, pipelineInput);
  }

  texture = texItt != DEV->m_textures.end() ? texItt->second
                                            : DEV->createTexture(cTexture);
}

void vkFontRender::OnRender(CGameFont &owner) {
  if (!shaderPass || !texture)
    return;

  if (!(owner.uFlags & CGameFont::fsValid)) {
    VkExtent3D extent = texture->imageExtent;
    owner.vTS.set((int)extent.width, (int)extent.height);
    owner.fTCHeight = owner.fHeight / float(owner.vTS.y);
    owner.uFlags |= CGameFont::fsValid;
  }

  auto cmd = HW.get_current_frame().cmdBuffer;

  VkRenderingAttachmentInfo colorAttachment =
      util::colorAttachmentInfo(HW.drawImage.imageView, std::nullopt);
  VkRenderingAttachmentInfo depthAttachment = util::depthAttachmentInfo(
      HW.depthImage.imageView, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL);

  auto renderingInfo =
      util::renderingInfo(HW.drawExtent, &colorAttachment, &depthAttachment);
  VkDescriptorSet frameDescriptorSet =
      HW.get_current_frame().frameDescriptors.allocate(
          HW.device, shaderPass->inputs.descriptorLayouts);

  DescriptorWriter dWriter;
  dWriter.write_image(0, texture->imageView, HW.linearSampler,
                      VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                      VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
  dWriter.updatee_set(HW.device, frameDescriptorSet);

  std::array descriptorSets = {HW.sceneDescriptorSet, frameDescriptorSet};
  vkCmdBeginRendering(cmd, &renderingInfo);

  vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, shaderPass->pipeline);
  vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS,
                          shaderPass->pipelineLayout, 0, descriptorSets.size(),
                          descriptorSets.data(), 0, nullptr);

  if (auto frameNumber = HW.frameNumber; currentFrame != frameNumber) {
    vertexCursor = 0;
    vertexIndex = 0;
    currentFrame = frameNumber;
  }

  GPU_Vertex *v = static_cast<GPU_Vertex *>(vertexBuffer.info.pMappedData);

  for (size_t i = 0; i < owner.strings.size();) {
    // calculate first-fit
    int count = 1;

    int length = owner.smart_strlen(owner.strings[i].string);

    while ((i + count) < owner.strings.size()) {
      int L = owner.smart_strlen(owner.strings[i + count].string);

      if ((L + length) < MAX_MB_CHARS) {
        count++;
        length += L;
      } else
        break;
    }

    vertexCursor += vertexIndex;
    vertexIndex = 0;

    // fill vertices
    u32 last = i + count;
    for (; i < last; i++) {
      CGameFont::String &PS = owner.strings[i];
      wide_char wsStr[MAX_MB_CHARS];

      int len = owner.IsMultibyte()
                    ? mbhMulti2Wide(wsStr, NULL, MAX_MB_CHARS, PS.string)
                    : xr_strlen(PS.string);

      if (len) {
        float X = float(iFloor(PS.x));
        float Y = float(iFloor(PS.y));
        float S = PS.height * g_current_font_scale.y;
        float Y2 = Y + S;
        float fSize = 0;

        if (PS.align)
          fSize = owner.IsMultibyte() ? owner.SizeOf_(wsStr)
                                      : owner.SizeOf_(PS.string);

        switch (PS.align) {
        case CGameFont::alCenter:
          X -= (iFloor(fSize * 0.5f)) * g_current_font_scale.x;
          break;
        case CGameFont::alRight:
          X -= iFloor(fSize);
          break;
        default:
          break;
        }

        u32 clr, clr2;
        clr2 = clr = PS.c;
        if (owner.uFlags & CGameFont::fsGradient) {
          u32 _R = color_get_R(clr) / 2;
          u32 _G = color_get_G(clr) / 2;
          u32 _B = color_get_B(clr) / 2;
          u32 _A = color_get_A(clr);
          clr2 = color_rgba(_R, _G, _B, _A);
        }

        float tu, tv;
        for (int j = 0; j < len; j++) {
          Fvector l;

          l = owner.IsMultibyte() ? owner.GetCharTC(wsStr[1 + j])
                                  : owner.GetCharTC((u16)(u8)PS.string[j]);

          float scw = l.z * g_current_font_scale.x;

          float fTCWidth = l.z / owner.vTS.x;

          if (!fis_zero(l.z)) {

            tu = (l.x / owner.vTS.x);
            tv = (l.y / owner.vTS.y);

            // x, y , color, (u, v)
            v[vertexCursor + vertexIndex++] = GPU_Vertex{
                // 1
                util::normalizeToScreenNDC(glm::vec3(X, Y2, 0),
                                           HW.drawExtent.width,
                                           HW.drawExtent.height),
                tu,
                glm::vec3(0),
                tv + owner.fTCHeight,
                glm::vec4(
                    color_get_R(clr2) / 255.0f, color_get_G(clr2) / 255.0f,
                    color_get_B(clr2) / 255.0f, color_get_A(clr2) / 255.0f),
            };

            v[vertexCursor + vertexIndex++] = GPU_Vertex{
                // 2
                util::normalizeToScreenNDC(glm::vec3(X, Y, 0),
                                           HW.drawExtent.width,
                                           HW.drawExtent.height),
                tu,
                glm::vec3(0),
                tv,
                glm::vec4(color_get_R(clr) / 255.0f, color_get_G(clr) / 255.0f,
                          color_get_B(clr) / 255.0f, color_get_A(clr) / 255.0f),
            };

            v[vertexCursor + vertexIndex++] = GPU_Vertex{
                // 3
                util::normalizeToScreenNDC(glm::vec3(X + scw, Y2, 0),
                                           HW.drawExtent.width,
                                           HW.drawExtent.height),
                tu + fTCWidth,
                glm::vec3(0),
                tv + owner.fTCHeight,
                glm::vec4(
                    color_get_R(clr2) / 255.0f, color_get_G(clr2) / 255.0f,
                    color_get_B(clr2) / 255.0f, color_get_A(clr2) / 255.0f),
            };

            v[vertexCursor + vertexIndex++] = GPU_Vertex{
                // 4
                util::normalizeToScreenNDC(glm::vec3(X + scw, Y, 0),
                                           HW.drawExtent.width,
                                           HW.drawExtent.height),
                tu + fTCWidth,
                glm::vec3(0),
                tv,
                glm::vec4(color_get_R(clr) / 255.0f, color_get_G(clr) / 255.0f,
                          color_get_B(clr) / 255.0f, color_get_A(clr) / 255.0f),
            };

            // second triangle
            v[vertexCursor + vertexIndex++] = GPU_Vertex{
                // 2
                util::normalizeToScreenNDC(glm::vec3(X, Y, 0),
                                           HW.drawExtent.width,
                                           HW.drawExtent.height),
                tu,
                glm::vec3(0),
                tv,
                glm::vec4(color_get_R(clr) / 255.0f, color_get_G(clr) / 255.0f,
                          color_get_B(clr) / 255.0f, color_get_A(clr) / 255.0f),
            };

            v[vertexCursor + vertexIndex++] = GPU_Vertex{
                // 3
                util::normalizeToScreenNDC(glm::vec3(X + scw, Y2, 0),
                                           HW.drawExtent.width,
                                           HW.drawExtent.height),
                tu + fTCWidth,
                glm::vec3(0),
                tv + owner.fTCHeight,
                glm::vec4(
                    color_get_R(clr2) / 255.0f, color_get_G(clr2) / 255.0f,
                    color_get_B(clr2) / 255.0f, color_get_A(clr2) / 255.0f),
            };
          }
          X += scw * owner.vInterval.x;
          if (owner.IsMultibyte()) {
            X -= 2;
            if (IsNeedSpaceCharacter(wsStr[1 + j]))
              X += owner.fXStep;
          }
        }
      }
    }

    GPU_BasePushConstantData pc{
        .vertexBufferPtr = vertexBufferAddress,
        .vertexIndex = vertexCursor,
    };

    vkCmdPushConstants(cmd, shaderPass->pipelineLayout,
                       VK_SHADER_STAGE_VERTEX_BIT, 0,
                       sizeof(GPU_BasePushConstantData), &pc);

    if (vertexCursor + vertexIndex > vertexBufferSize) {
      Msg("[RV][ERR]: %d too many vertices", vertexCursor + vertexIndex);
    }

    vkCmdDraw(cmd, vertexIndex, 1, 0, 0);
  }

  vkCmdEndRendering(cmd);
}