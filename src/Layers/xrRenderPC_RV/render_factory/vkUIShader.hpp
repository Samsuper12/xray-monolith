#pragma once
#include "utils/vkUtil.hpp"
#include <UIShader.h>
#include <glm_main.hpp>

// TODO: use json for default pipeline configs.
// TODO: use ktx2 metadata for storing the framerate.
// TODO: fix framerate

static constexpr uint32_t animationSpeed = 3;
class vkUIShader : public IUIShader {
  friend class vkUIRender;
  friend class vkDebugRender;
  friend class vkWallMarkArray;
  friend class CRender;

public:
  virtual ~vkUIShader() { ; }
  virtual void Copy(IUIShader &_in);
  virtual void create(LPCSTR sh, LPCSTR tex = 0);
  virtual bool inited() { return isInited; }
  virtual void destroy();

  auto OnFrame() -> void;
  
  bool isAnimation;
  uint32_t framerate;
  uint32_t frame{0};
  uint32_t textureLayer{0};

private:
  bool isInited{false};
  std::shared_ptr<ShaderPass> shaderPass;
  std::shared_ptr<AllocatedImage> texture;
  std::string shaderName;
  std::string textureName;
};
