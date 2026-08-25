#include "ResourceManager.hpp"
#include "VkHW.hpp"

auto CResourceManager::OnDeviceCreate(std::fs::path file) -> void {
  auto shadersRoot = rv::utils::slang_shader::getShaderRoot();
  std::vector<const char *> shaderLoadPath = {
      shadersRoot.c_str(),
  };
  slangLoader =
      std::make_unique<rv::utils::slang_shader::Loader>(shaderLoadPath);
}

auto CResourceManager::createPass(std::fs::path shaderPath,
                                  PipelineConfig config, PipelineInput input)
    -> std::shared_ptr<ShaderPass> {
  VkShaderModule vertexModule, fragmentModule;
  auto shPath = rv::utils::slang_shader::getShaderPath(shaderPath);
  auto pass = std::make_shared<ShaderPass>();
  pass->config = config;
  pass->inputs = input;

  if (!shPath) {
    Msg("[RV][ERR]: shader: %s not found.", shaderPath.c_str());
    return nullptr;
  }

  std::string entry_points[] = {
      "vertexMain",
      "fragmentMain",
  };

  auto p = shPath.value();
  normalize_path(p);
  auto slangShaders = slangLoader->load(HW.device, p, entry_points);

  if (slangShaders.empty()) {
    Msg("[RV][ERR]: shader: %s failed to compile.", shaderPath.c_str());
    return nullptr;
  }

  vertexModule = slangShaders["vertexMain"];
  fragmentModule = slangShaders["fragmentMain"];

  std::vector<VkDescriptorSetLayout> inputLayouts{
      pass->inputs.globalDescriptorLayout};
  inputLayouts.insert(inputLayouts.end(),
                      pass->inputs.descriptorLayouts.begin(),
                      pass->inputs.descriptorLayouts.end());

  VkPipelineLayoutCreateInfo layoutInfo{
      .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
      .pNext = nullptr,
      .setLayoutCount = inputLayouts.size(),
      .pSetLayouts = inputLayouts.data(),
      .pushConstantRangeCount = pass->inputs.pcRanges.size(),
      .pPushConstantRanges = pass->inputs.pcRanges.data(),
  };

  auto result = vkCreatePipelineLayout(HW.device, &layoutInfo, nullptr,
                                       &pass->pipelineLayout);
  if (result != VK_SUCCESS) {
    Msg("[RV][ERR]: pipeline layout: %s not compiled.", shaderPath.c_str());
    vkDestroyShaderModule(HW.device, vertexModule, nullptr);
    vkDestroyShaderModule(HW.device, fragmentModule, nullptr);
    return nullptr;
  }

  PipelineBuilder pipelineBuilder;
  pipelineBuilder.layout = pass->pipelineLayout;
  pipelineBuilder.setShaders(vertexModule, fragmentModule);
  pipelineBuilder.setInputTopology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
  pipelineBuilder.setPolygonMode(VK_POLYGON_MODE_FILL);
  pipelineBuilder.setCullMode(VK_CULL_MODE_NONE,
                              VK_FRONT_FACE_COUNTER_CLOCKWISE);
  pipelineBuilder.setMultisampleNone();
  switch (config.blend) {
  case PipelineBlend::Addictive:
    pipelineBuilder.enableBlendingAdditive();
    break;
  case PipelineBlend::AlphaBlend:
    pipelineBuilder.enableBlendingAlphablend();
    break;
  case PipelineBlend::None:
  default:
    pipelineBuilder.disableBlending();
  }
  pipelineBuilder.enableDepthtest(config.zTest ? VK_TRUE : VK_FALSE,
                                  config.zWrite ? VK_TRUE : VK_FALSE,
                                  VK_COMPARE_OP_ALWAYS);
  pipelineBuilder.setColorAttachementFormat(HW.drawImage.imageFormat);
  pipelineBuilder.setDepthFormat(HW.depthImage.imageFormat);

  pass->pipeline = pipelineBuilder.build(HW.device);
  vkDestroyShaderModule(HW.device, vertexModule, nullptr);
  vkDestroyShaderModule(HW.device, fragmentModule, nullptr);

  if (pass->pipeline == VK_NULL_HANDLE) {
    Msg("[RV][ERR]: pipeline: %s not compiled.", shaderPath.c_str());
    return nullptr;
  }

  m_passes.try_emplace(shaderPath, pass);
  return pass;
}

auto CResourceManager::createTexture(std::fs::path path)
    -> std::shared_ptr<AllocatedImage> {
  std::fs::path texPath;

  if (FS.exist(texPath, "$game_textures$", path.c_str(), ".dds")) {
    FS.update_path(texPath, "$game_textures$",
                   path.replace_extension(".dds").c_str());

    if (!FS.exist(texPath)) {
      Msg("[RV][ERR]: texture: %s.dds not found.", texPath.c_str());
      return nullptr;
    }
    auto ddsTex = rv::texture::load_dds_image(texPath);

    if (!ddsTex || ddsTex->empty()) {
      Msg("[RV][ERR]: Can't load texture: %s.dds.", texPath.c_str());
      return nullptr;
    }

    if (ddsTex->target() != gli::target::TARGET_2D) {
      Msg("[RV][ERR]: 2D arrays, 3D and CUBE textures currently out of "
          "support! %s",
          texPath.c_str());
      return nullptr;
    }
    gli::texture2d tex2d(*ddsTex);

    // convert texture to rgba8888.
    auto convertedTex =
        gli::convert<gli::texture2d>(tex2d, gli::FORMAT_RGBA8_UNORM_PACK32);

    VkExtent3D extent{
        .width = convertedTex.extent().x,
        .height = convertedTex.extent().y,
        .depth = 1,
    };

    auto tex = std::make_shared<AllocatedImage>(
        HW.createImage(convertedTex.data(), convertedTex.size(), extent,
                       VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_SAMPLED_BIT));

    m_textures[path] = tex;
    return tex;

  } else if (FS.exist(texPath, "$game_textures$", path.c_str(), ".ktx2")) {
    FS.update_path(texPath, "$game_textures$",
                   path.replace_extension(".ktx2").c_str());

    auto [ktxTexturePtrOpt, msg] = rv::texture::load_ktx2_image(texPath);

    if (!ktxTexturePtrOpt) {
      Msg("[RV][ERR]: %s", msg.c_str());
      return nullptr;
    }
    auto tex = std::make_shared<AllocatedImage>(
        HW.createImage(ktxTexturePtrOpt.value(), VK_IMAGE_USAGE_SAMPLED_BIT));

    m_textures[path] = tex;
    return tex;
  }

  return nullptr;
}