# X-Ray entrypoint
# Link this to a Win32 executable alongside an XRay.Render.R* module to produce a runnable game
add_library(XRay.Engine.Main INTERFACE)

target_link_libraries(XRay.Engine.Main
  INTERFACE
  #discord

  XRay.Core
  XRay.Collision
  XRay.CPUPipe
  XRay.Engine
  XRay.Game
  XRay.NetServer
  XRay.Particles
  XRay.Physics
  XRay.Render.API
  XRay.Sound
  XRay.XMLParser
)

target_sources(XRay.Engine.Main
  INTERFACE
  x_ray.cpp
  x_ray.h
  
  EngineAPI.cpp
  EngineAPI.h

  resource.h
  resource.rc
  
  dpi-aware.manifest
)

if(APPLE)
  execute_process(
    COMMAND brew --prefix icu4c
    OUTPUT_VARIABLE HOMEBREW_ICU_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  set(ICU_ROOT             "${HOMEBREW_ICU_PREFIX}")
  set(ICU_INCLUDE_DIR      "${HOMEBREW_ICU_PREFIX}/include")
  set(ICU_LIBRARY          "${HOMEBREW_ICU_PREFIX}/lib/libicuuc.dylib")
  set(ICU_UC_LIBRARY       "${HOMEBREW_ICU_PREFIX}/lib/libicuuc.dylib")
  set(ICU_I18N_LIBRARY     "${HOMEBREW_ICU_PREFIX}/lib/libicui18n.dylib")
  set(ICU_DATA_LIBRARY     "${HOMEBREW_ICU_PREFIX}/lib/libicudata.dylib")
endif()

find_package(ICU REQUIRED)
target_link_libraries(XRay.Engine.Main INTERFACE
  ${ICU_UC_LIBRARIES}
  ${ICU_I18N_LIBRARIES}
  ${ICU_DATA_LIBRARIES}
)
target_include_directories(XRay.Engine.Main INTERFACE
  ${ICU_INCLUDE_DIRS}
  ${ICU_INCLUDE_DIR}                        # fallback
  "${HOMEBREW_ICU_PREFIX}/include"          # explicit fallback
)
