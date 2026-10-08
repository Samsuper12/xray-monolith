module;
#include "render_stub.hpp"
#include <FS.h>
#include <LocatorAPI.h>
#include <gli/gli.hpp>
#include <vulkan_main.hpp>
#include <Fmesh.h>

export module RV.ResourceManager;
import xr.Core;
import RV.HW;
import RV.Utils;

static constexpr bool bAllowChildrenDuplicate = true;

struct ModelDef {
  std::string name;
  // vkRender_Visual* model;
  u32 refs;

  ModelDef() {
    refs = 0;
    // model = 0;
  }
};

export struct IResource {
  enum class Type {
    Unknown,
    Texture,
    Pipeline
  };
 
  // size_t CPUSize;
  // size_t GPUSize;
  // Type type;

  // auto Load() -> void = 0;
  // auto UpdateSize() -> void = 0;
  
};


export class CResourceManager {

public:
  std::vector<ModelDef> models;
  std::unordered_map<std::string, std::shared_ptr<ShaderPass>> m_passes;
  std::unordered_map<std::string, std::shared_ptr<AllocatedImage>> m_textures;
  std::unordered_map<std::string, size_t> modelIndices;

  CResourceManager() {
    m_passes.reserve(50);
    m_textures.reserve(200);
    models.reserve(100);
    modelIndices.reserve(100);
  }

  ~CResourceManager() { render_stub(); }

  auto createPass(std::fs::path shaderPath, PipelineConfig config,
                  PipelineInput input) -> std::shared_ptr<ShaderPass>;
  auto createTexture(std::fs::path path) -> std::shared_ptr<AllocatedImage>;

  //auto CreateModel(const std::fs::path& path) -> IRenderVisual*;
  // auto CreateModelChild(const std::fs::path& path, IReader* data) ->
  // IRenderVisual*;

  auto OnDeviceCreate(std::fs::path file) -> void;
  auto OnDeviceDestroy(bool bKeepTextures) -> void {}

  auto reset_begin() -> void {}
  auto reset_end() -> void {}

private:
  std::unique_ptr<rv::utils::slang_shader::Loader> slangLoader;
};

auto CResourceManager::OnDeviceCreate(std::fs::path file) -> void {
  PROF_EVENT();
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
  PROF_EVENT();
  ZoneText(shaderPath.c_str(), shaderPath.string().size());
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
  PROF_EVENT();
  ZoneText(path.c_str(), path.string().size());
  std::shared_ptr<AllocatedImage> ret;
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

    VkExtent3D extent{
        .width = tex2d.extent().x,
        .height = tex2d.extent().y,
        .depth = 1,
    };

    auto format = rv::texture::gliToVkFormat(tex2d.format());
    bool formatSupported =
        format ? HW.formatIsSupported(format.value()) : false;

    if (formatSupported) {
      ret = std::make_shared<AllocatedImage>(
          HW.createImage(tex2d.data(), tex2d.size(), extent, format.value(),
                         VK_IMAGE_USAGE_SAMPLED_BIT));

    } else {
      // convert texture to rgba8888.
      PROF_EVENT_N("Converting Texture");
      ZoneText(path.c_str(), path.string().size());
      Msg("[RV][ERR]: Texture format out of support. Converting to RGBA8. "
          "Warning: consider huge performance loss during converting %s",
          texPath.c_str());

      auto convertedTex =
          gli::convert<gli::texture2d>(tex2d, gli::FORMAT_RGBA8_UNORM_PACK32);

      ret = std::make_shared<AllocatedImage>(
          HW.createImage(convertedTex.data(), convertedTex.size(), extent,
                         VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_SAMPLED_BIT));
    }

    m_textures[path] = ret;
    return ret;

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

// dxRender_Visual* CModelPool::Instance_Create(u32 type)
// {
// 	dxRender_Visual* V = NULL;

// 	// Check types
// 	switch (type)
// 	{
// 	case MT_NORMAL: // our base visual
// 		V = xr_new<Fvisual>();
// 		break;
// 	case MT_HIERRARHY:
// 		V = xr_new<FHierrarhyVisual>();
// 		break;
// 	case MT_PROGRESSIVE: // dynamic-resolution visual
// 		V = xr_new<FProgressive>();
// 		break;
// 	case MT_SKELETON_ANIM:
// 		V = xr_new<CKinematicsAnimated>();
// 		break;
// 	case MT_SKELETON_RIGID:
// 		V = xr_new<CKinematics>();
// 		break;
// 	case MT_SKELETON_GEOMDEF_PM:
// 		V = xr_new<CSkeletonX_PM>();
// 		break;
// 	case MT_SKELETON_GEOMDEF_ST:
// 		V = xr_new<CSkeletonX_ST>();
// 		break;
// 	case MT_PARTICLE_EFFECT:
// 		V = xr_new<PS::CParticleEffect>();
// 		break;
// 	case MT_PARTICLE_GROUP:
// 		V = xr_new<PS::CParticleGroup>();
// 		break;
// #ifndef _EDITOR
// 	case MT_LOD:
// 		V = xr_new<FLOD>();
// 		break;
// 	case MT_TREE_ST:
// 		V = xr_new<FTreeVisual_ST>();
// 		break;
// 	case MT_TREE_PM:
// 		V = xr_new<FTreeVisual_PM>();
// 		break;
// #endif
// 	default:
// 		FATAL("Unknown visual type");
// 		break;
// 	}
// 	R_ASSERT(V);
// 	V->Type = type;
// 	return V;
// }

// auto CResourceManager::CreateModel(const std::fs::path &path)
//     -> IRenderVisual * {
//   PROF_EVENT();
//   ZoneText(path.c_str(), path.string().size());

//   // TODO: lower the name.

//   std::fs::path modelPath;
//   if (!FS.exist(modelPath, "$game_meshes$", path.c_str(), ".ogf")) {
//     if (!FS.exist(modelPath, "$level$", path.c_str(), ".ogf")) {
//       Msg("[RV][ERR]: model % not found", path.c_str());
//       // TODO: load default instead
//       return nullptr;
//     }
//   }

//   // {__pn_:"anomaly_weapons\\hands\\wpn_hand_no_outfit"}
//   // H.type = 3 -> MT_SKELETON_ANIM
//   // H.format_version = 4
//   // H.shader_id = 0

//   IReader *data = FS.r_open(modelPath.c_str());
//   vkRender_Visual *V;
//   ogf_header H;
//   data->r_chunk_safe(OGF_HEADER, &H, sizeof(H));
//   switch (H.type) {
//   default:
//     Msg("[RV][ERR]: unexpected ogf model type: %d", H.type);
//     return nullptr;
//   }

//   //V->Load(N, data, 0);

//   FS.r_close(data);
//   // 	g_pGamePersistent->RegisterModel(V);
//   // models[]ModelDef {
//   //   .model = V,
//   //   .name = path,
//   // }
//   // Instance_Register(N, V);
// }

// vkRender_Visual *CResourceManager::CreateModelChild(const std::fs::path
// &name,
//                                                     IReader *data) {
//   auto base = m_models.find(name);
//   dxRender_Visual *Base = Instance_Find(low_name);

//   // found? return duplicate
//   // no? return CreateModel

//   if (base != m_models.end()) {
//   }
//   //.	if (0==Base) Base	 	=
//   Instance_Load(name,data,FALSE); if (0 == Base) {
//     if (data)
//       Base = Instance_Load(low_name, data, FALSE);
//     else
//       Base = Instance_Load(low_name, FALSE);
//   }
//   // bAllowChildrenDuplicate = true always
//   dxRender_Visual *Model =
//       bAllowChildrenDuplicate ? Instance_Duplicate(Base) : Base;
//   return Model;
// }