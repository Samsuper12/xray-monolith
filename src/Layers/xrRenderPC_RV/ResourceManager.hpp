#pragma once

#include "render_stub.hpp"
#include "utils/slang.hpp"
#include "utils/vkUtil.hpp"
#include <FS.h>
#include <LocatorAPI.h>

struct lua_State;
class CResourceManager {

public:
  std::map<std::string, std::shared_ptr<ShaderPass>> m_passes;
  std::map<std::string, std::shared_ptr<AllocatedImage>> m_textures;

  CResourceManager() { render_stub(); }

  ~CResourceManager() { render_stub(); }

  auto createPass(std::fs::path shaderPath, PipelineConfig config,
                  PipelineInput input) -> std::shared_ptr<ShaderPass>;
  auto createTexture(std::fs::path path) -> std::shared_ptr<AllocatedImage>;

  auto OnDeviceCreate(std::fs::path file) -> void;
  auto OnDeviceDestroy(bool bKeepTextures) -> void {}

  auto reset_begin() -> void {}
  auto reset_end() -> void {}

private:
  std::unique_ptr<rv::utils::slang_shader::Loader> slangLoader;
};
