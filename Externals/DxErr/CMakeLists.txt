add_library(DxErr STATIC)

target_folder(DxErr ${FOLDER_EXTERNAL})

set_target_properties(DxErr PROPERTIES OUTPUT_NAME DxErr_x64_ar)

set(DXERR_DIR ../DxErr-git/DxErr/src)

# Patch dxerr.cpp with Clang / GCC -compliant macro stringify and concat
file(READ ${DXERR_DIR}/DXErr.cpp DXERR_CPP)
string(REPLACE "L#hrchk" "L###hrchk" DXERR_CPP "${DXERR_CPP}")
string(REPLACE "L##__VA_ARGS__" "L###__VA_ARGS__" DXERR_CPP "${DXERR_CPP}")
file(GENERATE OUTPUT DxErr/DXErr.cpp CONTENT "${DXERR_CPP}")
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS DXErr.cpp)
target_sources(DxErr PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/DxErr/DXErr.cpp)

target_sources_sandboxed(DxErr
  DIRECTORY DxErr

  STRIP
  ${DXERR_DIR}/

  SOURCES
  ${DXERR_DIR}/DXErr.h
  ${DXERR_DIR}/DXGetErrorString.inl
  ${DXERR_DIR}/DXGetErrorDescription.inl
  ${DXERR_DIR}/DXTrace.inl
)

target_include_directories(DxErr
  PUBLIC
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/DxErr
)

target_compile_options(DxErr
  PUBLIC
  $<$<CXX_COMPILER_ID:MSVC>:/wd4005>
  $<$<CXX_COMPILER_ID:Clang>:-Wno-macro-redefined>
  PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/permissive->
  $<$<CXX_COMPILER_ID:MSVC>:/wd4313>
  $<$<CXX_COMPILER_ID:MSVC>:/wd4474>
  $<$<CXX_COMPILER_ID:MSVC>:/wd4477>
)
