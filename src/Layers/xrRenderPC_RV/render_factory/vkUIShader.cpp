#include "vkUIShader.hpp"
#include "render_stub.hpp"
#include "stdio.h"
#include "utils/vkUtil.hpp"
#include "vkRenderDeviceRender.hpp"
#include <FS.h>
#include <LocatorAPI.h>
#include <map>
#include <rv.hpp>

static constexpr std::string_view defaultShader = "hud/default";
static constexpr std::string_view errorTexture = "error_tex";
static constexpr PipelineConfig defaultPipelineConfig{
    .blend = PipelineBlend::None,
    .zTest = false,
    .zWrite = false,
};

static const std::map<std::string_view, PipelineConfig> uiConfigMap{
    {"hud\\default",
     {.blend = PipelineBlend::AlphaBlend, .zTest = false, .zWrite = false}},
    {"hud\\cursor",
     {.blend = PipelineBlend::AlphaBlend, .zTest = false, .zWrite = false}},
    {"effects\\wallmark",
     {.blend = PipelineBlend::Addictive, .zTest = true, .zWrite = false}},
};

void vkUIShader::Copy(IUIShader &_in) { *this = *((vkUIShader *)&_in); }

auto vkUIShader::OnFrame() -> void {
    if (!isAnimation)
      return;

    frame++;

    if (frame == framerate) {
      textureLayer++;
      textureLayer = textureLayer % texture->layersCount;
    }

    frame = frame % framerate;
  }

void vkUIShader::create(LPCSTR sh, LPCSTR tex) {
  auto passItt = DEV->m_passes.find(sh);
  auto textureItt = DEV->m_textures.find(tex);

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
                              .size = sizeof(GPU_UIPC)},
      }};

  PipelineConfig config;

  if (auto configItt = uiConfigMap.find(sh); configItt != uiConfigMap.end()) {
    config = configItt->second;
  } else {
    Msg("[RV][ERR]: Found no optimal blenging for the shader: %s", sh);
    config = {
        .blend = PipelineBlend::AlphaBlend,
        .zTest = false,
        .zWrite = false,
    };
  }

  this->shaderPass = passItt != DEV->m_passes.end()
                         ? passItt->second
                         : DEV->createPass(sh, config, pipelineInput);

  
  // check if it's an animation
  std::fs::path texPath;
  if (FS.exist(texPath, "$game_textures$", tex, ".seq")) {
    char buffer[256];
    IReader *_fs = FS.r_open(texPath.c_str());

    _fs->r_string(buffer, sizeof(buffer));
    auto fps = atoi(buffer);

    this->framerate = animationSpeed; //1000 / fps;
    this->isAnimation = true;
    FS.r_close(_fs);
  }

  this->texture = textureItt != DEV->m_textures.end() ? textureItt->second
                                                      : DEV->createTexture(tex);
  if (!shaderPass) {
    Msg("[RV][ERR]: ShaderPass not created: %s. Using default", sh);
    shaderPass =
        DEV->createPass(defaultShader, defaultPipelineConfig, pipelineInput);
    if (!shaderPass)
      Msg("[RV][ERR]: Default shader fault too. Stange.");
  }

  if (!texture) {
    Msg("[RV][ERR]: Texture not created: %s. Using default", tex);
    texture = DEV->createTexture(errorTexture);
  }

  shaderName = sh;
  textureName = tex;
  isInited = true;
}

void vkUIShader::destroy() {}
