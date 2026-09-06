module;
#include "RenderVisual.h"
#include <Fmesh.h>
#include <render_stub.hpp>
#include <vis_common.h>

export module vkRenderVisual;
import RV.HW;
import RV.Utils;

export struct IRender_Mesh {
  // vertices + indices
  AllocatedBuffer vertexBuffer;
  uint32_t vBase;
  uint32_t vCount;
  uint32_t iBase;
  uint32_t iCount;
  uint32_t dwPrimitives;

  IRender_Mesh() = default;
  IRender_Mesh(const IRender_Mesh &other) = delete;
  void operator=(const IRender_Mesh &other) = delete;

  virtual ~IRender_Mesh() { HW.destroyBuffer(vertexBuffer); }
};

export class vkRender_Visual : public IRenderVisual {
public:
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
  s32 skinning;

  virtual void Render(float LOD) {}; // LOD - Level Of Detail  [0..1], Ignored
  virtual void Load(const char *N, IReader *data, u32 dwFlags);
  virtual void Release(); // Shared memory release
  virtual void Copy(vkRender_Visual *from) {render_stub();}
  virtual void Spawn() {};
  virtual void Depart() {};
  virtual void SetShaderTexture(LPCSTR shader, LPCSTR texture);
  virtual void ResetShaderTexture();
  virtual vis_data &getVisData() { return vis; }
  virtual u32 getType() { return Type; }

  // std::shared_ptr<AllocatedImage> GetTexture();
  // //--DSR--
  virtual void MarkAsHot(bool is_hot);         //--DSR-- HeatVision
  virtual void MarkAsGlowing(bool is_glowing); //--DSR-- SilencerOverheat

  vkRender_Visual() : Type(0){vis.clear();}
  virtual ~vkRender_Visual() {}
};