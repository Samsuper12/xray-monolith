add_library(robin_hood INTERFACE)

target_folder(robin_hood ${FOLDER_EXTERNAL})

set(ROBIN_HOOD_DIR ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(robin_hood
  INTERFACE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/robin_hood
)

target_sources_sandboxed(robin_hood
  DIRECTORY robin_hood
  STRIP
  ${ROBIN_HOOD_DIR}/
  SOURCES
  ${ROBIN_HOOD_DIR}/robin_hood.h
)