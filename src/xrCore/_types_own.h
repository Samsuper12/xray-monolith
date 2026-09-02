#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdlib.h>

#define _stdcall
#define __cdecl
#define __stdcall
#define _inline inline
#define __inline inline

#define LUABIND_NO_EXCEPTIONS

#ifdef BENCHMARK_BUILD
#define BENCH_SEC_CALLCONV __stdcall
#define BENCH_SEC_SCRAMBLEVTBL1                                                \
  virtual int GetFlags() { return 1; }
#define BENCH_SEC_SCRAMBLEVTBL2                                                \
  virtual void *GetData() { return 0; }
#define BENCH_SEC_SCRAMBLEVTBL3                                                \
  virtual void *GetCache() { return 0; }
#define BENCH_SEC_SIGN , void *pBenchScrampleVoid = 0
#define BENCH_SEC_SCRAMBLEMEMBER1 float m_fSrambleMember1;
#define BENCH_SEC_SCRAMBLEMEMBER2 float m_fSrambleMember2;
#else // BENCHMARK_BUILD
#define BENCH_SEC_CALLCONV
#define BENCH_SEC_SCRAMBLEVTBL1
#define BENCH_SEC_SCRAMBLEVTBL2
#define BENCH_SEC_SCRAMBLEVTBL3
#define BENCH_SEC_SIGN
#define BENCH_SEC_SCRAMBLEMEMBER1
#define BENCH_SEC_SCRAMBLEMEMBER2
#endif // BENCHMARK_BUILD

#define XRCORE_API
#define ENGINE_API

#define ALIGN(a) __declspec(align(a))

#define _stricmp strcasecmp
#define RGB(r, g, b)                                                           \
  ((uint32_t)(((r) | ((uint16_t)((g)) << 8)) | (((uint32_t)(b)) << 16)))

#define D3DCOLOR_ARGB(a, r, g, b)                                              \
  ((uint32_t)((((a) & 0xff) << 24) | (((r) & 0xff) << 16) |                    \
              (((g) & 0xff) << 8) | ((b) & 0xff)))
#define D3DCOLOR_RGBA(r, g, b, a) D3DCOLOR_ARGB(a, r, g, b)
#define D3DCOLOR_XRGB(r, g, b) D3DCOLOR_ARGB(0xff, r, g, b)

#define _cdecl

#define IC inline
#define ICF IC

#define TRUE true
#define FALSE false

#define PATH_MAX 260
#define _MAX_PATH PATH_MAX

// Type defs
typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef int64_t s64;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef char *pstr;
typedef const char *pcstr;
typedef const char *LPCSTR;

typedef int BOOL;

// Type limits
#define type_max(T) (std::numeric_limits<T>::max())
#define type_min(T) (-std::numeric_limits<T>::max())
#define type_zero(T) (std::numeric_limits<T>::min())
#define type_epsilon(T) (std::numeric_limits<T>::epsilon())

#define int_max type_max(int)
#define int_min type_min(int)
#define int_zero type_zero(int)

#define flt_max type_max(float)
#define flt_min type_min(float)
// #define flt_max 3.402823466e+38F /* max value */
// #define FLT_MIN 1.175494351e-38F /* min positive value */

#define flt_zero type_zero(float)
#define flt_eps type_epsilon(float)

#define dbl_max type_max(double)
#define dbl_min type_min(double)
#define dbl_zero type_zero(double)
#define dbl_eps type_epsilon(double)

typedef char string16[16];
typedef char string32[32];
typedef char string64[64];
typedef char string128[128];
typedef char string256[256];
typedef char string512[512];
typedef char string1024[1024];
typedef char string2048[2048];
typedef char string4096[4096];

typedef char string_path[2 * _MAX_PATH];

#ifdef __cplusplus
#include <cstdio>
#include <filesystem>
#include <pthread.h>
#include <strings.h>
#include <unistd.h>

static inline void stub_unix(const char *f) {

  fprintf(stderr, "function: %s\n", f);
  fprintf(stderr, "stub");
}

inline uint64_t GetTickCount() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

inline unsigned long GetCurrentThreadId() {
  return (unsigned long)pthread_self();
}

inline char *_strlwr(char *s) {
  for (size_t i = 0; s[i]; ++i)
    s[i] = tolower((unsigned char)s[i]);
  return s;
}

inline int _strupr_s(char *str, size_t size) {
  if (!str || size == 0)
    return -1;
  for (size_t i = 0; i < size && str[i]; i++)
    str[i] = (char)toupper((unsigned char)str[i]);
  return 0;
}

template <typename... Args>
inline int sscanf_s(const char *buffer, const char *format, Args... args) {
  return sscanf(buffer, format, args...);
}

inline char *_itoa(int i, char *s, int dummy_radix) {
  sprintf(s, "%d", i);
  return s;
}

inline char *strncpy_s(char *strDest, size_t numberOfElements,
                       const char *strSource, size_t count) {
  if (numberOfElements == 0)
    return strDest;
  size_t n = (count < numberOfElements - 1) ? count : numberOfElements - 1;
  strncpy(strDest, strSource, n);
  strDest[n] = '\0';
  return strDest;
}

template <size_t size>
inline char *strncpy_s(char (&strDest)[size], const char *strSource,
                       size_t count) {
  return strncpy_s(strDest, size, strSource, count);
}

inline auto GlobToRegex = [](std::string glob) -> std::string {
  std::string rx = "^";
  for (char c : glob) {
    switch (c) {
    case '*':
      rx += ".*";
      break;
    case '?':
      rx += '.';
      break;
    case '.':
      rx += "\\.";
      break;
    case '\\':
      rx += "\\\\";
      break;
    default:
      rx += c;
    }
  }
  rx += "$";
  return rx;
};

#endif

#endif
