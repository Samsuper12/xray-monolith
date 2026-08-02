add_library(imgui STATIC)

find_package(SDL3 CONFIG REQUIRED)
find_package(VulkanHeaders CONFIG REQUIRED)

target_folder(imgui ${FOLDER_EXTERNAL})

target_compile_definitions(imgui
  PRIVATE
  IMGUI_IMPL_VULKAN_USE_VOLK
)

target_compile_options(imgui
  PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/permissive->
  $<$<CXX_COMPILER_ID:MSVC>:/wd4005>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-macro-redefined>
)

target_link_libraries(imgui
  PRIVATE
  SDL3::SDL3
  volk::volk
  volk::volk_headers
)

target_include_directories(imgui
  PUBLIC
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/imgui
)

target_sources_sandboxed(imgui
  DIRECTORY imgui

  STRIP
  ../IconFontCppHeaders-git/
  ../imgui-git/

  SOURCES
  ../IconFontCppHeaders-git/IconsFontAwesome6.h
  
  ../imgui-git/imconfig.h
  ../imgui-git/imgui.cpp
  ../imgui-git/imgui.h
  ../imgui-git/imgui_demo.cpp
  ../imgui-git/imgui_draw.cpp
  ../imgui-git/imgui_internal.h
  ../imgui-git/imgui_tables.cpp
  ../imgui-git/imgui_widgets.cpp
  ../imgui-git/imstb_rectpack.h
  ../imgui-git/imstb_textedit.h
  ../imgui-git/imstb_truetype.h
  ../imgui-git/backends/imgui_impl_sdl3.cpp
  ../imgui-git/backends/imgui_impl_sdl3.h
  ../imgui-git/backends/imgui_impl_vulkan.cpp
  ../imgui-git/backends/imgui_impl_vulkan.h
)
