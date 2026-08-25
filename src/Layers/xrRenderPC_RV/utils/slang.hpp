#pragma once
#include "vulkan_main.hpp"

#include <slang-com-ptr.h>
#include <slang.h>

#include <FS.h>
#include <LocatorAPI.h>
#include <map>
#include <optional>

namespace rv::utils::slang_shader {

class Loader {
public:
  Loader(const std::vector<const char *> search_path) : loaded(false) {
    auto res = slang::createGlobalSession(slangGlobal.writeRef());
    if (SLANG_FAILED(res)) {
      Msg("[RV][SLANG]: failed to load global session.");
      return;
    }

    slang::TargetDesc targetDesc{.format = SLANG_SPIRV,
                                 .profile =
                                     slangGlobal->findProfile("spirv_1_5"),
                                 .flags = 0};

    slang::SessionDesc sessionDesc{.targets = &targetDesc,
                                   .targetCount = 1,
                                   .compilerOptionEntryCount = 0,
                                   .searchPaths = search_path.data(),
                                   .searchPathCount = search_path.size()};

    res =slangGlobal->createSession(sessionDesc, session.writeRef());
    if (SLANG_FAILED(res)) {
      Msg("[RV][SLANG]: failed to load target session.");
      return;
    }

    loaded = true;
  }

  auto diagnoseIfNeeded(Slang::ComPtr<slang::IBlob> diagBlob) -> void {
    if (diagBlob != nullptr)
      Msg("[RV][SLANG]: %s", diagBlob->getBufferPointer());
  }

  auto load(VkDevice dev, const std::string module_name,
                  const std::span<std::string> entry_point_names)
      -> std::map<std::string, VkShaderModule> {
    Slang::ComPtr<slang::IBlob> diagBlob;
    std::map<std::string, VkShaderModule> ret;

    slang::IModule *slangModule =
        session->loadModule(module_name.c_str(), diagBlob.writeRef());
    diagnoseIfNeeded(diagBlob);
    if (slangModule == nullptr) {
      return {};
    }

    std::vector<slang::IComponentType *> componentTypes;
    componentTypes.push_back(slangModule);

    for (const auto &entry : entry_point_names) {
      Slang::ComPtr<slang::IEntryPoint> entryPoint;
      slangModule->findEntryPointByName(entry.c_str(), entryPoint.writeRef());
      componentTypes.push_back(entryPoint);
    }

    Slang::ComPtr<slang::IComponentType> program;

    auto res = session->createCompositeComponentType(
        componentTypes.data(), componentTypes.size(), program.writeRef(),
        diagBlob.writeRef());
    diagnoseIfNeeded(diagBlob);
    if (SLANG_FAILED(res)) {
      return {};
    }

    SlangInt entryPointCount = slangModule->getDefinedEntryPointCount();
    size_t entryPointIndex = 0;
    for (const auto &entry : entry_point_names) {
      VkShaderModule ret_module;
      Slang::ComPtr<slang::IBlob> spirv;

      res = program->getEntryPointCode(entryPointIndex++, 0, spirv.writeRef(),
                                       diagBlob.writeRef());
      diagnoseIfNeeded(diagBlob);
      if (SLANG_FAILED(res)) {
        return {};
      }

      VkShaderModuleCreateInfo info{
          .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
          .pNext = nullptr,
          .codeSize = spirv->getBufferSize(),
          .pCode = static_cast<const uint32_t *>(spirv->getBufferPointer()),
      };

      if (vkCreateShaderModule(dev, &info, nullptr, &ret_module) !=
          VK_SUCCESS) {
        Msg("[RV][SLANG]: vkCreateShaderModule just failed");
        return {};
      }
      ret[entry] = ret_module;
    }

    return ret;
  }

private:
  bool loaded;
  Slang::ComPtr<slang::IGlobalSession> slangGlobal;
  Slang::ComPtr<slang::ISession> session;
};

// Slang relies on own filesystem, so I don't want to fuck with it. At least
// now.
inline auto getShaderRoot() -> std::fs::path {
  return std::fs::current_path().parent_path() / "gamedata" / "shaders" / "rv";
}

inline auto getShaderPath(std::fs::path shader_name)
    -> std::optional<std::fs::path> {
  normalize_path(shader_name);
  shader_name.replace_extension(".slang");

  std::fs::path shadersRoot;
  auto path = getShaderRoot() / shader_name;

  if (std::fs::exists(path))
    return path;

  return std::nullopt;
}
} // namespace rv::utils::slang_shader
