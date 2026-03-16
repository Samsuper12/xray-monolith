include_guard()

set(XRAY_COMPILER_FLAGS
  # Compatibility flags
  -fpermissive
  -Wno-implicit-function-declaration
  -Wno-c++11-narrowing
  -Wno-invalid-token-paste
  -Wno-nonportable-include-path
  -Wno-shift-negative-value
  -Wno-address-of-temporary
  -Wno-register
  -w
  # Initialize to zero for MSVC equivalence
  -ftrivial-auto-var-init=zero
  # ...but warn about it
  -Wuninitialized
  -ferror-limit=0
  -fdeclspec
)

# Explicitly state when we're compiling for Win32
if(WIN32)
  list(APPEND XRAY_COMPILER_FLAGS -DWIN32)
endif()

set(XRAY_COMPILER_FLAGS_DEBUG
  -O0
  -g
)

set(XRAY_COMPILER_FLAGS_RELEASE
  -O2
 # -funroll-loops
  -flto=full
  -D_HAS_ITERATOR_DEBUGGING=0
  -D_SECURE_SCL=0
)

set(XRAY_COMPILER_FLAGS_RELWITHDEBINFO
  -O2
  -g
  #-flto=thin
  -D_HAS_ITERATOR_DEBUGGING=0
  -D_SECURE_SCL=0
)

set(XRAY_LINKER_FLAGS_RELEASE
  -O2
  -flto=full
)
