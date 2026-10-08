module;
#include <vulkan_main.hpp>
#include "RenderVisual.h"
#include <Fmesh.h>
#include <render_stub.hpp>
#include <vis_common.h>
export module RenderVisual.vkRenderVisual;
export import RV.ResourceManager;

import RV.HW;
import RV.Utils;
import RenderFactory.RenderDeviceRender;


export extern "C++" {
  class IRenderVisual;
};


export struct IRender_Mesh {
  // vertices + indices
  AllocatedBuffer buffer;
	VkDeviceAddress bufferAddress;
  uint32_t vBase;
  uint32_t vCount;
  uint32_t iBase;
  uint32_t iCount;
  uint32_t dwPrimitives;

  IRender_Mesh() = default;
  IRender_Mesh(const IRender_Mesh &other) = delete;
  void operator=(const IRender_Mesh &other) = delete;

  virtual ~IRender_Mesh() { }//HW.destroyBuffer(vertexBuffer); }
};

export class vkRender_Visual : public IRenderVisual, public IResource {
public:
  ogf_desc desc;
  uint32_t dbg_id;
  shared_str dbg_name;
  std::string dbg_shader;
  std::string dbg_texture;
  std::string dbg_shader_def;
  std::string dbg_texture_def;
  virtual void setID(u32 id) { dbg_id = id; }
  virtual u32 getID() { return dbg_id; }
  virtual shared_str getDebugName() { return dbg_name; }
  virtual LPCSTR getDebugShader() { return dbg_shader.c_str(); }
  virtual LPCSTR getDebugTexture() { return dbg_texture.c_str(); }
  virtual LPCSTR getDebugShaderDef() { return dbg_shader_def.c_str(); }
  virtual LPCSTR getDebugTextureDef() { return dbg_texture_def.c_str(); }

public:
  // Common data for rendering
  uint32_t Type;                      // visual's type
  vis_data vis;                       // visibility-data
  std::shared_ptr<ShaderPass> shader; // pipe state, shared
  std::shared_ptr<AllocatedImage> texture;
  uint32_t skinning;

  virtual void Render(float LOD) {}; // LOD - Level Of Detail  [0..1], Ignored
  virtual void Load(const char *N, IReader *data, u32 dwFlags);
  virtual void Release() {} // Shared memory release
  virtual void Copy(vkRender_Visual *from) {render_stub();}
  virtual void Spawn() {};
  virtual void Depart() {};
  virtual void SetShaderTexture(const char* shader, const char* texture);
  virtual void ResetShaderTexture();
  virtual vis_data &getVisData() { return vis; }
  virtual u32 getType() { return Type; }

  // std::shared_ptr<AllocatedImage> GetTexture();
  // //--DSR--
  //virtual void MarkAsHot(bool is_hot);         //--DSR-- HeatVision
  //virtual void MarkAsGlowing(bool is_glowing); //--DSR-- SilencerOverheat

  vkRender_Visual() : Type(0){vis.clear();}
  virtual ~vkRender_Visual() {}
};

static constexpr PipelineConfig pipelineConfigDefault {
	.blend = PipelineBlend::None,
	.zTest = true,
	.zWrite = false,
};


void vkRender_Visual::Load(const char* N, IReader* data, u32 flags)
{
	dbg_name = N;
	dbg_id = 1;
	// TODO:
	//skinning = ::Render->m_skinning;

	// header
	VERIFY(data);
	ogf_header hdr;
	if (data->r_chunk_safe(OGF_HEADER, &hdr, sizeof(hdr)))
	{
		R_ASSERT2(hdr.format_version==xrOGF_FormatVersion, "Invalid visual version");
		Type = hdr.type;
		//if (hdr.shader_id)	shader	= ::Render->getShader	(hdr.shader_id);
		vis.box.set(hdr.bb.min, hdr.bb.max);
		vis.sphere.set(hdr.bs.c, hdr.bs.r);
	}
	else
	{
		FATAL("Invalid visual");
	}

	// Shader
	if (data->find_chunk(OGF_TEXTURE))
	{
		string256 fnT, fnS;
		data->r_stringZ(fnT, sizeof(fnT));
		data->r_stringZ(fnS, sizeof(fnS));
		dbg_shader_def = fnS;
		dbg_texture_def = fnT;
		ResetShaderTexture();
	}

  if (data->find_chunk(OGF_S_DESC)) 
	  desc.Load		(*data);
}

void vkRender_Visual::SetShaderTexture(const char* s_shader, const char* s_texture)
{
	// if (s_shader && strlen(s_shader))
	// {
	// 	flags.set(IRenderVisualFlags::eNoShadow, strstr(s_shader, "$no_shadows") ? TRUE : FALSE);
	// 	dbg_shader = s_shader;
	// }

	// if (s_texture && strlen(s_texture))
	// {
	// 	dbg_texture = s_texture;
	// }

	// DescriptorLayoutBuilder layoutBuilder;
  // layoutBuilder.addBinding(0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);

	// PipelineInput pipelineInput = {
  //     .globalDescriptorLayout = HW.sceneDescriptorLayout,
  //     .descriptorLayouts =
  //         {
  //             layoutBuilder.build(HW.device, VK_SHADER_STAGE_FRAGMENT_BIT),
  //         },
  //     .pcRanges = {
  //         VkPushConstantRange{.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
  //                             .offset = 0,
  //                             .size = sizeof(GPU_BasePushConstantData)},
  //     }};

	// ::Render->m_skinning = skinning;
	// shader = DEV()->createPass(dbg_shader, pipelineConfigDefault, pipelineInput);
	//shader.create(dbg_shader, dbg_texture);
}

void vkRender_Visual::ResetShaderTexture()
{
	if ((dbg_shader != dbg_shader_def) || (dbg_texture != dbg_texture_def))
		SetShaderTexture(dbg_shader_def.c_str(), dbg_texture_def.c_str());
}

