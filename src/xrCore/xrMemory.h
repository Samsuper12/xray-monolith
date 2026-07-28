#ifndef xrMemoryH
#define xrMemoryH
#pragma once

#include "_types_own.h"
#include <_type_traits.h>
#include <fast_dynamic_cast.h>
#include <cstdlib>
#include <algorithm>

class XRCORE_API xrMemory
{
public:
	xrMemory();
	void _initialize(BOOL _debug_mode = FALSE);
	void _destroy();
	
	u32 stat_calls;
public:
	void log_vminfo();
	size_t mem_usage();
	void mem_compact();
	void* mem_alloc(size_t size);
	void* mem_realloc(void* p, size_t size);
	void mem_free(void* p);
	inline void mem_fill(void* dest, int value, u32 count) { memset(dest, int(value), count); }
	inline void mem_fill32(void* dest, u32 value, u32 count) {
		uint32_t* ptr = static_cast<uint32_t*>(dest);
		std::fill(ptr, ptr + count, value);
	}
	inline void mem_copy(void* dest, const void* src, u32 n) { memcpy(dest, src, n); }
	
};

extern XRCORE_API xrMemory Memory;

#undef ZeroMemory
#undef CopyMemory
#undef FillMemory
#define ZeroMemory(a,b) Memory.mem_fill(a,0,b)
#define FillMemory(a,b,c) Memory.mem_fill(a,c,b)

template <class T, class... Args>
inline T* xr_new(Args&&... args)
{
	T* ptr = (T*)Memory.mem_alloc(sizeof(T));
	return new(ptr)T(std::forward<Args>(args)...);
}


template <bool _is_pm, typename T>
struct xr_special_free
{
	inline void operator()(T*& ptr) {
		void* _real_ptr = fast_dynamic_cast<void*>(ptr);
		ptr->~T();
		Memory.mem_free(_real_ptr);
	}
};

template <typename T>
struct xr_special_free<false, T>
{
	inline void operator()(T*& ptr) {
		ptr->~T();
		Memory.mem_free(ptr);
	}
};

template <class T>
inline void xr_delete(T*& ptr)
{
	if (ptr) {
		xr_special_free<is_polymorphic<T>::result, T>()(ptr);
		ptr = nullptr;
	}
}

template <class T>
inline void xr_delete(T* const& ptr)
{
	if (ptr) {
		xr_special_free<is_polymorphic<T>::result, T> (ptr);
		const_cast<T*&>(ptr) = nullptr;
	}
}

template <class T>
inline T* xr_alloc(u32 count) { return (T*)Memory.mem_alloc(count * sizeof(T)); }

template <class T>
inline void xr_free(T*& P)
{
	if (P) {
		Memory.mem_free((void*)P);
		P = NULL;
	};
}

inline void* xr_malloc(size_t size) { return Memory.mem_alloc(size); }
inline void* xr_realloc(void* P, size_t size) { return Memory.mem_realloc(P, size); }

char* xr_strdup(const char* string);
#endif // xrMemoryH
