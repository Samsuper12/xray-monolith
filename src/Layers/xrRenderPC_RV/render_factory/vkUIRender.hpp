#pragma once
#include "vkUIShader.hpp"
#include "vulkan_main.hpp"
#include <UIRender.h>

struct AllocatedBuffer;
struct GPU_Vertex;

// FIXME: strange slider bug that multiplies count of vertices in a single frame
class vkUIRender : public IUIRender {
public:
  vkUIRender();

  virtual void CreateUIGeom();
  virtual void DestroyUIGeom();

  virtual void SetShader(IUIShader &shader);
  virtual void SetAlphaRef(int aref);
  virtual void SetScissor(Irect *rect = NULL);
  virtual void GetActiveTextureResolution(Fvector2 &res);
  virtual void PushPoint(float x, float y, float z, u32 C, float u, float v);
  virtual void StartPrimitive(u32 iMaxVerts, ePrimitiveType primType,
                              ePointType pointType);
  virtual void FlushPrimitive();

  virtual LPCSTR UpdateShaderName(LPCSTR tex_name, LPCSTR sh_name);

  virtual void CacheSetXformWorld(const Fmatrix &M);
  virtual void CacheSetCullMode(CullMode);

private:
  std::vector<vkUIShader *> keepAliveUI;

  AllocatedBuffer vertexArena;
  VkDeviceAddress vertexArenaAddress;
  size_t arenaSize;
  uint64_t vertexIndex;
  uint64_t arenaCursor;
  uint64_t lastFrameIndex;
  bool skipCurrentDraw;
};

extern vkUIRender UIRenderImpl;
