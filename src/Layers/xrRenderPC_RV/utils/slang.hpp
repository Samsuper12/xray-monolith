#pragma once
#include "vulkan_main.hpp"

#include <slang.h>
#include <slang-com-ptr.h>

#include <map>

namespace rv::utils::shader {

inline std::map<std::string, VkShaderModule>
loadModuleSlang(VkDevice dev, const std::string module_name,
                const std::span<std::string> entry_point_names) {
  using namespace Slang;

  const char *search_path[] = {"/Users/eva00/Projects/vlk/shaders",
                               "/Users/eva00/Projects/vlk/shaders/cube"};

  std::map<std::string, VkShaderModule> ret;

  Slang::ComPtr<slang::IGlobalSession> slangGlobal;
  auto res = slang::createGlobalSession(slangGlobal.writeRef());
  if (SLANG_FAILED(res))
    abort();

  slang::TargetDesc targetDesc{.format = SLANG_SPIRV,
                               .profile = slangGlobal->findProfile("spirv_1_5"),
                               .flags = 0};
  slang::SessionDesc sessionDesc{.targets = &targetDesc,
                                 .targetCount = 1,
                                 .compilerOptionEntryCount = 0,
                                 .searchPaths = search_path,
                                 .searchPathCount = 2};

  ComPtr<slang::ISession> session;
  res = slangGlobal->createSession(sessionDesc, session.writeRef());
  if (SLANG_FAILED(res))
    abort();

  ComPtr<slang::IBlob> diagBlob;
  slang::IModule *slangModule = nullptr;

  try {
    slangModule = session->loadModule(module_name.c_str(), diagBlob.writeRef());
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
    abort();
  }

  if (slangModule == nullptr) {
    std::cout << "nullptr!";
  }

  std::vector<slang::IComponentType *> componentTypes;
  componentTypes.push_back(slangModule);

  for (const auto &entry : entry_point_names) {
    ComPtr<slang::IEntryPoint> entryPoint;
    slangModule->findEntryPointByName(entry.c_str(), entryPoint.writeRef());
    componentTypes.push_back(entryPoint);
  }

  ComPtr<slang::IComponentType> program;

  res = session->createCompositeComponentType(
      componentTypes.data(), componentTypes.size(), program.writeRef());
  if (SLANG_FAILED(res))
    abort();

  SlangInt entryPointCount = slangModule->getDefinedEntryPointCount();
  size_t entryPointIndex = 0;
  for (const auto &entry : entry_point_names) {
    VkShaderModule ret_module;
    ComPtr<slang::IBlob> spirv;

    res = program->getEntryPointCode(entryPointIndex++, 0, spirv.writeRef());
    if (SLANG_FAILED(res))
      abort();

    VkShaderModuleCreateInfo info{
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext = nullptr,
        .codeSize = spirv->getBufferSize(),
        .pCode = static_cast<const uint32_t *>(spirv->getBufferPointer()),
    };
    vkCreateShaderModule(dev, &info, nullptr, &ret_module);
    ret[entry] = ret_module;
  }

  return ret;
}
}

