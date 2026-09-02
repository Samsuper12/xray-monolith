cmake_minimum_required(VERSION 3.21)

execute_process(
    COMMAND brew --prefix llvm
    OUTPUT_VARIABLE LLVM_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE LLVM_RESULT
)

# LLVM
if(NOT LLVM_RESULT EQUAL 0)
    message(FATAL_ERROR
        "Homebrew LLVM was not found. Install it with:\n"
        "  brew install llvm"
    )
endif()

set(CMAKE_C_COMPILER
    "${LLVM_PREFIX}/bin/clang"
    CACHE FILEPATH "C compiler" FORCE
)
set(CMAKE_CXX_COMPILER
    "${LLVM_PREFIX}/bin/clang++"
    CACHE FILEPATH "C++ compiler" FORCE
)
set(CMAKE_AR
    "${LLVM_PREFIX}/bin/llvm-ar"
    CACHE FILEPATH "Archiver" FORCE
)
set(CMAKE_RANLIB
    "${LLVM_PREFIX}/bin/llvm-ranlib"
    CACHE FILEPATH "Ranlib" FORCE
)
set(CMAKE_NM
    "${LLVM_PREFIX}/bin/llvm-nm"
    CACHE FILEPATH "nm" FORCE
)
set(CMAKE_OBJCOPY
    "${LLVM_PREFIX}/bin/llvm-objcopy"
    CACHE FILEPATH "objcopy" FORCE
)
set(CMAKE_OBJDUMP
    "${LLVM_PREFIX}/bin/llvm-objdump"
    CACHE FILEPATH "objdump" FORCE
)

# LLD
execute_process(
    COMMAND brew --prefix lld
    OUTPUT_VARIABLE LLD_PREFIX
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE LLD_RESULT
)

if(NOT LLD_RESULT EQUAL 0)
    message(FATAL_ERROR
        "Homebrew LLD was not found. Install it with:\n"
        "  brew install lld"
    )
endif()

set(LLVM_LD64
    "${LLD_PREFIX}/bin/ld64.lld"
)

if(NOT EXISTS "${LLVM_LD64}")
    message(FATAL_ERROR
        "ld64.lld was not found at:\n"
        "  ${LLVM_LD64}"
    )
endif()

set(CMAKE_EXE_LINKER_FLAGS_INIT
    "-fuse-ld=${LLVM_LD64}"
)
set(CMAKE_SHARED_LINKER_FLAGS_INIT
    "-fuse-ld=${LLVM_LD64}"
)
set(CMAKE_MODULE_LINKER_FLAGS_INIT
    "-fuse-ld=${LLVM_LD64}"
)

set(CMAKE_OSX_DEPLOYMENT_TARGET
    "26.0"
    CACHE STRING "Minimum macOS deployment target"
)

set(CMAKE_FIND_FRAMEWORK FIRST)
set(CMAKE_FIND_APPBUNDLE FIRST)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD ON)

message(STATUS "")
message(STATUS "MacOS LLVM toolchain")
message(STATUS "  LLVM:         ${LLVM_PREFIX}")
message(STATUS "  C compiler:   ${CMAKE_C_COMPILER}")
message(STATUS "  CXX compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "  LLD:          ${LLVM_LD64}")
message(STATUS "  Architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS "  Deployment:   ${CMAKE_OSX_DEPLOYMENT_TARGET}")
message(STATUS "")
