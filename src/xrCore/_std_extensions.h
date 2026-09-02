#ifndef _STD_EXT_internal
#define _STD_EXT_internal

#include <algorithm>
#include <cstdio>
#include <float.h>
#include <stdarg.h>
#include <stdio.h>

#include "_types_own.h"
#include <cmath>

#define BREAK_AT_STRCMP
#ifndef DEBUG
#undef BREAK_AT_STRCMP
#endif
#ifdef _EDITOR
#undef BREAK_AT_STRCMP
#endif

#ifdef abs
#undef abs
#endif

#ifdef _MIN
#undef _MIN
#endif

#ifdef _MAX
#undef _MAX
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifdef _EDITOR
inline char* strncpy_s(char* strDestination, size_t sizeInBytes, const char* strSource, size_t count)
{
    return strncpy(strDestination, strSource, count);
}

inline char* xr_strcpy(char* strDestination, size_t sizeInBytes, const char* strSource)
{
    return strcpy(strDestination, strSource);
}

inline char* xr_strcpy(char* strDestination, const char* strSource)
{
    return strcpy(strDestination, strSource);
}

inline char* _strlwr_s(char* strDestination, size_t sizeInBytes)
{
    return _strlwr(strDestination);
}

inline char* xr_strcat(char* strDestination, size_t sizeInBytes, const char* strSource)
{
    return strncat(strDestination, strSource, sizeInBytes);
}

inline char* xr_strcat(char* strDestination, const char* strSource)
{
    return strcat(strDestination, strSource);
}

inline int xr_sprintf(char* dest, size_t sizeOfBuffer, const char* format, ...)
{
    va_list mark;
    va_start(mark, format);
    int sz = vsnprintf(dest, sizeOfBuffer, format, mark);
    dest[sizeOfBuffer - 1] = 0;
    va_end(mark);
    return sz;
}
#endif

// token type definition
struct XRCORE_API xr_token
{
	LPCSTR name;
	int id;
};

inline LPCSTR get_token_name(xr_token* tokens, int key)
{
	for (int k = 0; tokens[k].name; k++)
		if (key == tokens[k].id) return tokens[k].name;
	return "";
}

inline int get_token_id(xr_token* tokens, LPCSTR key)
{
	for (int k = 0; tokens[k].name; k++)
		if (_stricmp(tokens[k].name, key) == 0)
			return tokens[k].id;
	return -1;
}

struct XRCORE_API xr_token2
{
	LPCSTR name;
	LPCSTR info;
	int id;
};

// generic
template <class T>
inline T _min(T a, T b) { return a < b ? a : b; }

template <class T>
inline T _max(T a, T b) { return a > b ? a : b; }

template <class T>
inline T _sqr(T a) { return a * a; }

// float
inline float _abs(float x) { return std::fabsf(x); }
inline float _sqrt(float x) { return std::sqrtf(x); }
inline float _sin(float x) { return std::sinf(x); }
inline float _cos(float x) { return std::cosf(x); }
inline BOOL _valid(const float x)
{
	switch (std::fpclassify(x))
    {
        case FP_INFINITE:
        case FP_NAN:
        case FP_SUBNORMAL:
            return false;
    }
	return true;
}


// double
inline double _abs(double x) { return std::fabs(x); }
inline double _sqrt(double x) { return std::sqrt(x); }
inline double _sin(double x) { return std::sin(x); }
inline double _cos(double x) { return std::cos(x); }
inline BOOL _valid(const double x)
{
	// check for: Signaling NaN, Quiet NaN, Negative infinity ( –INF), Positive infinity (+INF), Negative denormalized, Positive denormalized
	switch (std::fpclassify(x))
    {
        case FP_INFINITE:
        case FP_NAN:
        case FP_SUBNORMAL:
            return false;
    }

	// int cls = _fpclass(x);
	// if (cls & (_FPCLASS_SNAN + _FPCLASS_QNAN + _FPCLASS_NINF + _FPCLASS_PINF + _FPCLASS_ND + _FPCLASS_PD))
	// 	return false;

	/* *****other cases are*****
	_FPCLASS_NN Negative normalized non-zero
	_FPCLASS_NZ Negative zero ( – 0)
	_FPCLASS_PZ Positive 0 (+0)
	_FPCLASS_PN Positive normalized non-zero
	*/
	return true;
}

// int8
inline s8 _abs(s8 x) { return (x >= 0) ? x : s8(-x); }
inline s8 _min(s8 x, s8 y) { return y + ((x - y) & ((x - y) >> (sizeof(s8) * 8 - 1))); };
inline s8 _max(s8 x, s8 y) { return x - ((x - y) & ((x - y) >> (sizeof(s8) * 8 - 1))); };

// unsigned int8
inline u8 _abs(u8 x) { return x; }

// int16
inline s16 _abs(s16 x) { return (x >= 0) ? x : s16(-x); }
inline s16 _min(s16 x, s16 y) { return y + ((x - y) & ((x - y) >> (sizeof(s16) * 8 - 1))); };
inline s16 _max(s16 x, s16 y) { return x - ((x - y) & ((x - y) >> (sizeof(s16) * 8 - 1))); };

// unsigned int16
inline u16 _abs(u16 x) { return x; }

// int32
inline s32 _abs(s32 x) { return (x >= 0) ? x : s32(-x); }
inline s32 _min(s32 x, s32 y) { return y + ((x - y) & ((x - y) >> (sizeof(s32) * 8 - 1))); };
inline s32 _max(s32 x, s32 y) { return x - ((x - y) & ((x - y) >> (sizeof(s32) * 8 - 1))); };

// int64
inline s64 _abs(s64 x) { return (x >= 0) ? x : s64(-x); }
inline s64 _min(s64 x, s64 y) { return y + ((x - y) & ((x - y) >> (sizeof(s64) * 8 - 1))); };
inline s64 _max(s64 x, s64 y) { return x - ((x - y) & ((x - y) >> (sizeof(s64) * 8 - 1))); };

inline u32 xr_strlen(const char* S);

// string management

// return pointer to ".ext"
inline char* strext(const char* S)
{
	return (char*)strrchr(S, '.');
}

inline u32 xr_strlen(const char* S)
{
	return (u32)strlen(S);
}

inline char* xr_strlwr(char* S)
{
	return _strlwr(S);
}

inline std::filesystem::path& xr_pathlwr(std::filesystem::path& p) {

	auto str = p.string();
	std::transform(str.begin(), str.end(), str.begin(), [] (unsigned char c) { return std::tolower(c);});
	p = str;
	return p;
}

#ifdef BREAK_AT_STRCMP
XRCORE_API int xr_strcmp(const char* S1, const char* S2);
#else
inline int xr_strcmp(const char* S1, const char* S2)
{
	return (int)strcmp(S1, S2);
}
#endif

#ifndef _EDITOR
#ifndef MASTER_GOLD
inline void xr_strcpy(char * destination, size_t const destination_size, LPCSTR source)
{
    snprintf(destination, destination_size, "%s", source);
}

inline void xr_strcat(char * destination, size_t const buffer_size, LPCSTR source)
{
    size_t dst_len = strlen(destination);
    if (dst_len < buffer_size)
        snprintf(destination + dst_len, buffer_size - dst_len, "%s", source);
}

inline int xr_sprintf(char * destination, size_t const buffer_size, LPCSTR format_string, ...)
{
    va_list args;
    va_start(args, format_string);
    return 1;//vsprintf(destination, buffer_size, format_string, args);
}

template <int count>
inline int xr_sprintf(char(&destination)[count], LPCSTR format_string, ...)
{
    va_list args;
    va_start(args, format_string);
    return vsprintf(destination, count, format_string, args);
}
#else // #ifndef MASTER_GOLD

inline void xr_strcpy(char * destination, size_t const destination_size, LPCSTR source)
{
	snprintf(destination, destination_size, "%s", source);
}

inline errno_t xr_strcat(char * destination, size_t const buffer_size, LPCSTR source)
{
	size_t const destination_length = xr_strlen(destination);
	char * i = destination + destination_length;
	char * const e = destination + buffer_size - 1;
	if (i > e)
		return 0;

	for (LPCSTR j = source; *j && (i != e); ++i, ++j)
		*i = *j;

	*i = 0;
	return 0;
}

inline int xr_sprintf(char * destination, size_t const buffer_size, LPCSTR format_string, ...)
{
	va_list args;
	va_start(args, format_string);
	return vsnprintf(destination, buffer_size, format_string, args);
}

template <int count>
inline int xr_sprintf(char (&destination)[count], LPCSTR format_string, ...)
{
	va_list args;
	va_start(args, format_string);
	return vsnprintf(destination, count, format_string, args);
}
#endif // #ifndef MASTER_GOLD

template <int count>
inline void xr_strcpy(char (&destination)[count], LPCSTR source)
{
	xr_strcpy(destination, count, source);
}

template <int count>
inline errno_t xr_strcat(char (&destination)[count], LPCSTR source)
{
	return xr_strcat(destination, count, source);
}
#endif // #ifndef _EDITOR

XRCORE_API char* timestamp(string64& dest);

extern XRCORE_API u32 crc32(const void* P, u32 len);
extern XRCORE_API u32 crc32(const void* P, u32 len, u32 starting_crc);
extern XRCORE_API u32 path_crc32(const char* path, u32 len); // ignores '/' and '\'

#endif // _STD_EXT_internal
