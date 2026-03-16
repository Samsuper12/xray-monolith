# Use minimum VS-supported CMake for broad IDE compatibility
cmake_minimum_required(VERSION 3.28)

message(STATUS "CMake")
message(STATUS "      Version: ${CMAKE_VERSION}")
message(STATUS "    Generator: ${CMAKE_GENERATOR}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

set(CMAKE_OSX_DEPLOYMENT_TARGET "26.0")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Force shared libraries" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

set(SDL_RENDER OFF CACHE BOOL "" FORCE)
set(SDL_GPU OFF CACHE BOOL "" FORCE)
set(SDL_JOYSTICK OFF CACHE BOOL "" FORCE)
set(SDL_HAPTIC OFF CACHE BOOL "" FORCE)

#for all
set(ALSOFT_NO_CONFIG_UTIL ON CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL_CONFIG OFF CACHE BOOL "" FORCE)
set(ALSOFT_EXAMPLES OFF CACHE BOOL "" FORCE)
set(ALSOFT_UTILS OFF CACHE BOOL "" FORCE)
set(LIBTYPE "STATIC" CACHE STRING "" FORCE)
set(LSOFT_UPDATE_BUILD_VERSION OFF CACHE BOOL "" FORCE)

#macos
set(ALSOFT_BACKEND_COREAUDIO ON CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_COREAUDIO ON CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_APPLE ON CACHE BOOL "" FORCE)

#linux
set(ALSOFT_REQUIRE_LINUX OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_ALSA OFF CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_ALSA OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_JACK OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_PIPEWIRE OFF CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_PIPEWIRE OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_PULSEAUDIO OFF CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_PULSEAUDIO OFF CACHE BOOL "" FORCE)

#windows
set(ALSOFT_REQUIRE_WINDOWS OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_DSOUND OFF CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_DSOUND OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_WASAPI OFF CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_WASAPI OFF CACHE BOOL "" FORCE)

#etc
set(ALSOFT_INSTALL_AMBDEC_PRESETS OFF CACHE BOOL "" FORCE)
set(ALSOFT_INSTALL_HRTF_DATA OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_OPENSL OFF  CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_OPENSL OFF CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_RTKIT OFF CACHE BOOL "" FORCE)
set(ALSOFT_RTKIT OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_OSS OFF CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_OSS OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_SOLARIS OFF CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_SOLARIS OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_OPENSL OFF CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_OPENSL OFF CACHE BOOL "" FORCE)
set(ALSOFT_BACKEND_PORTAUDIO OFF CACHE BOOL "" FORCE)
set(ALSOFT_REQUIRE_PORTAUDIO OFF CACHE BOOL "" FORCE)

if(WIN32)
  set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
elseif(APPLE)
  set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_MACOS_MVK)
elseif(Linux)
  set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WAYLAND_KHR)
endif()


# Configure CCache
include(XRay.CCache)

# Configure IWYU
include(XRay.IWYU)

# Configure Win32-specific before-project settings
if (WIN32)
  include(XRay.Win32)
endif()

include(Today)

include(XRay.Git)

# Define project
project(
  Anomaly
  VERSION ${TODAY_DOTS}
  DESCRIPTION "X-Ray Monolith Edition for S.T.A.L.K.E.R. Anomaly"
  LANGUAGES CXX C
)

file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.1/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

#CPMAddPackage("gh:libsdl-org/SDL#release-3.4.2")
# CPMAddPackage("gh:fmtlib/fmt#12.1.0")
# CPMAddPackage("gh:GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator#v3.3.0")
#CPMAddPackage("gh:KhronosGroup/Vulkan-Headers@1.4.344")
CPMAddPackage("gh:g-truc/glm#1.0.3")
CPMAddPackage("gh:kcat/openal-soft#1.24.3")
CPMAddPackage("gh:uxlfoundation/oneTBB#v2022.3.0")
# CPMAddPackage("gh:ocornut/imgui#v1.92.6")
# CPMAddPackage("gh:spnda/fastgltf#v0.9.0")
# CPMAddPackage("gh:nothings/stb#f1c79c0")
#CPMAddPackage("gh:zeux/volk#vulkan-sdk-1.4.341.0")

message(STATUS)
message(STATUS "S.T.A.L.K.E.R. Anomaly")
message(STATUS "      Version: ${TODAY_DOTS}")

# Glob top-level CMake directory into Build target for developer convenience
add_custom_target(Build)
file(GLOB_RECURSE SOURCES_GAMEDATA CMake/*)
target_sources(Build PRIVATE ${SOURCES_GAMEDATA})

# Hand off to our XRay entrypoint
include(XRay.CMake)

# Setup external libraries
add_subdirectory(Externals)

# Setup compressor
add_subdirectory(compressor)

# Setup gamedata
add_subdirectory(gamedata)

# Setup SDK
add_subdirectory(sdk)

# Setup engine sources
add_subdirectory(src)
