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
  USE_DX11
  XRRENDER_RV_EXPORTS

  LINKS
  fastdelegate
  FastDynamicCast
  imgui
  luabind
  LuaJIT
  #NVAPI
  #ReShadeCompat
  robin_hood
  tbb
  
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
  #XRay.Render.DX10.Includes
  XRay.ServerEntities.Includes
  XRay.Sound.Includes
  
  PRECOMPILES
  #[["d3dx9.h"]]
  #[["d3d11.h"]]
  #[["d3d11_1.h"]]
  #[["d3d11_2.h"]]
  #[["D3Dx11core.h"]]
  #[["D3DCompiler.h"]]
  #[["xrD3DDefs.h"]]
  #[["dx10EventWrapper.h"]]
  #[["psystem.h"]]
  #[["HW.h"]]
  #[["Shader.h"]]
  #[["R_Backend.h"]]
  #[["R_Backend_Runtime.h"]]
  #[["resourcemanager.h"]]
  #[["vis_common.h"]]
  #[["Render.h"]]
  #[["_d3d_extensions.h"]]
  #[["IGame_Level.h"]]
  #[["blenders/blender.h"]]
  #[["blenders/blender_clsid.h"]]
  #[["xrRender_console.h"]]
  #[["r4.h"]]

  SOURCES
  #../xrRenderDX10/DXCommonTypes.h
  #../xrRender/xrD3DDefs.h
  
  #../xrRender/xrRender_console.cpp
  #../xrRender/xrRender_console.h

  #jitter.h

  xrRender_RV.cpp
)

#find_package(glm CONFIG REQUIRED)
#find_package(volk CONFIG REQUIRED)
#find_package(glslang CONFIG REQUIRED)

target_link_libraries(XRay.Render.RV.Includes INTERFACE
  #glm::glm-header-only
  #volk::volk
  #volk::volk_headers
  # glslang::glslang
  # glslang::glslang-default-resource-limits
  # glslang::SPIRV
)

add_module(XRay.Render.RV.Core
  SOURCES
 # ../xrRenderDX10/dx10Texture.cpp
  # ../xrRender/particles_systems_library_interface.hpp
  # ../xrRender/PSLibrary.cpp
  # ../xrRender/PSLibrary.h
  # ../xrRender/QueryHelper.h
  # ../xrRender/r__dsgraph_build.cpp
  # ../xrRender/r__dsgraph_render.cpp
  # ../xrRender/r__dsgraph_render_lods.cpp
  # ../xrRender/r__dsgraph_structure.h
  # ../xrRender/r__dsgraph_types.h
  # ../xrRender/r__occlusion.cpp
  # ../xrRender/r__occlusion.h
  # ../xrRender/r__pixel_calculator.cpp
  # ../xrRender/r__pixel_calculator.h
  # ../xrRender/r__screenshot.cpp
  # ../xrRender/r_sun_cascades.h
  rv.cpp
  rv.hpp
  rv_loader.cpp
  rv_R_render.cpp
  stub.cpp
  ../xrRender/tga.cpp
  ../xrRender/tga.h
)

add_module(XRay.Render.RV.Core.Target
  SOURCES
  #   ../xrRender/rendertarget_phase_blur.cpp
  # ../xrRender/rendertarget_phase_dof.cpp
  # ../xrRender/rendertarget_phase_lut.cpp
  # ../xrRender/rendertarget_phase_nightvision.cpp
  # ../xrRender/rendertarget_phase_gasmask_drops.cpp
  # ../xrRender/rendertarget_phase_gasmask_dudv.cpp
  # ../xrRender/rendertarget_phase_pp_bloom.cpp
  # ../xrRender/rendertarget_phase_smaa.cpp
  # ../xrRender/rendertarget_phase_sunshafts.cpp
  rv_rendertarget.cpp
  rv_rendertarget.hpp
)