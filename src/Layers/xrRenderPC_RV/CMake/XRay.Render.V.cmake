add_module(XRay.Render.RV.ForceIncludes INTERFACE)

target_compile_options(XRay.Render.RV.ForceIncludes
  INTERFACE
  $<$<CXX_COMPILER_ID:MSVC>:/FIrv.hpp>
  $<$<CXX_COMPILER_ID:Clang>:-includerv.hpp>
  $<$<CXX_COMPILER_ID:GNU>:-includerv.hpp>
)

add_module(XRay.Render.RV
  TYPE STATIC

  INCLUDES
  ${CMAKE_CURRENT_SOURCE_DIR}

  DEFINES
  RENDER=5
  STATIC_RENDERER_RV
  USE_VK
  XRRENDER_RV_EXPORTS

  LINKS
  fastdelegate
  FastDynamicCast
  luabind
  LuaJIT
  robin_hood
  imgui
  
  XRay.Platform
  XRay.Render.RV.ForceIncludes
  
  XRay.Core.Defines
  XRay.Engine.Defines
  XRay.Render.Common.Defines
  
  XRay.Includes
  XRay.Collision.Includes
  XRay.Core.Includes
  XRay.CPUPipe.Includes
  XRay.Engine.Includes
  XRay.Particles.Includes
  XRay.Physics.Includes
  XRay.Render.API.Includes
  XRay.Render.Common.Includes
  XRay.ServerEntities.Includes
  XRay.Sound.Includes
  
  PRECOMPILES
  [["vulkan_main.hpp"]]
  [["rv.hpp"]]
  [["Render.h"]]

  SOURCES
  xrRender_RV.cpp
  xrRender_console.cpp
)

find_package(glm CONFIG REQUIRED)
find_package(volk CONFIG REQUIRED)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
find_package(glslang CONFIG REQUIRED)
find_package(VulkanHeaders CONFIG REQUIRED)
find_package(gli CONFIG REQUIRED)

#TODO: use CPM instead of brew
find_package(Slang CONFIG REQUIRED)

target_link_libraries(XRay.Render.RV.Includes INTERFACE
  glm::glm-header-only
  volk::volk
  volk::volk_headers
  vk-bootstrap::vk-bootstrap
  VulkanMemoryAllocator
  Vulkan::Headers
  slang::slang
  ktx
  gli
)

add_module(XRay.Render.RV.RenderFactory
  SOURCES
  render_factory/vkUISequenceVideoItem.cpp
  render_factory/vkUISequenceVideoItem.hpp
  render_factory/vkUIShader.hpp
  render_factory/vkUIShader.cpp
  render_factory/vkStatGraphRender.hpp
  render_factory/vkStatGraphRender.cpp
  render_factory/vkApplicationRender.hpp
  render_factory/vkApplicationRender.cpp
  render_factory/vkConsoleRender.hpp
  render_factory/vkConsoleRender.cpp
  render_factory/vkWallMarkArray.hpp
  render_factory/vkWallMarkArray.cpp
  render_factory/vkStatRender.hpp
  render_factory/vkStatRender.cpp
  render_factory/vkThunderboltRender.hpp
  render_factory/vkThunderboltRender.cpp
  render_factory/vkThunderboltDescRender.hpp
  render_factory/vkThunderboltDescRender.cpp
  render_factory/vkRainRender.hpp
  render_factory/vkRainRender.cpp
  render_factory/vkLensFlareRender.hpp
  render_factory/vkLensFlareRender.cpp
  render_factory/vkImGuiRender.hpp
  render_factory/vkImGuiRender.cpp
  render_factory/vkFontRender.hpp
  render_factory/vkFontRender.cpp
  render_factory/vkRenderDeviceRender.hpp
  render_factory/vkRenderDeviceRender.cpp
  render_factory/vkEnvironmentRender.hpp
  render_factory/vkEnvironmentRender.cpp
  render_factory/vkUIRender.hpp
  render_factory/vkUIRender.cpp
  render_factory/vkUIRender.cpp
  render_factory/vkRenderFactory.hpp
  render_factory/vkRenderFactory.cpp
)

add_module(XRay.Render.RV.Core
  SOURCES
  rv.cpp
  rv.hpp
  VkHW.hpp
  VkHW.cpp
  ResourceManager.cpp
)
