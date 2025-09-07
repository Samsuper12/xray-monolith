add_library(fastdelegate INTERFACE)

target_folder(fastdelegate ${FOLDER_EXTERNAL})

set(FASTDELEGATE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(fastdelegate
  INTERFACE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/fastdelegate
)

target_sources_sandboxed(fastdelegate
  DIRECTORY fastdelegate
  STRIP
  ${FASTDELEGATE_DIR}/
  SOURCES
  ${FASTDELEGATE_DIR}/fastdelegate.h
)