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
  
  XRay.Core.Defines
  XRay.Core
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

  SOURCES
  xrRender_RV.cpp
  xrRender_console.cpp
  #TODO:
  RenderFactory/vkRenderFactory.hpp
  RenderFactory/vkRenderFactory.cpp

  CXX_MODULES

  RV.cppm
  
  RenderVisual/RenderVisual.cppm
  RenderVisual/vkRenderVisual.cppm
  
  ResourceManager.cppm

  RenderFactory/vkRenderFactory.cppm
  RenderFactory/vkUIShader.cppm
  RenderFactory/vkUIRender.cppm
  RenderFactory/vkApplicationRender.cppm
  RenderFactory/vkFontRender.cppm
  RenderFactory/vkConsoleRender.cppm
  RenderFactory/vkImGuiRender.cppm
  RenderFactory/vkStatGraphRender.cppm
  RenderFactory/vkRenderDeviceRender.cppm
  RenderFactory/vkEnvironmentRender.cppm
  RenderFactory/vkLensFlareRender.cppm
  RenderFactory/vkRainRender.cppm
  RenderFactory/vkStatRender.cppm
  RenderFactory/vkWallMarkArray.cppm
  RenderFactory/vkUISequenceVideoItem.cppm
  RenderFactory/vkThunderboltRender.cppm
  RenderFactory/vkThunderboltDescRender.cppm

  HW/HW.cppm
  HW/Allocation.cppm
  HW/Init.cppm
  HW/Rendering.cppm
  HW/Swapchain.cppm
  HW/Interface.cppm

  Utils/Utils.cppm
  Utils/Descriptor.cppm
  Utils/Pipeline.cppm
  Utils/Slang.cppm
  Utils/Structs.cppm
  Utils/Texture.cppm
  Utils/Vulkan.cppm
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

