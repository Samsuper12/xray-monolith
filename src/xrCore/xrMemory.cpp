#ifndef __APPLE__
#include <malloc.h>
#endif
#include "xrMemory.h"
#include "xrsharedmem.h"
#include "xrstring.h"

xrMemory Memory;

xrMemory::xrMemory() {}

void xrMemory::_initialize(BOOL bDebug)
{
	stat_calls = 0;

	g_pStringContainer = xr_new<str_container>();
	g_pSharedMemoryContainer = xr_new<smem_container>();
}

void xrMemory::_destroy()
{
	xr_delete(g_pSharedMemoryContainer);
	xr_delete(g_pStringContainer);
}

void* xrMemory::mem_alloc(size_t size) {
	stat_calls++;
    return std::malloc(size);
}

void xrMemory::mem_free(void* P) {
	stat_calls++;
    std::free(P);
}

void* xrMemory::mem_realloc(void* P, size_t size) {
	stat_calls++;

	if (nullptr == P)
		return mem_alloc(size);

	return std::realloc(P, size);	
}

char* xr_strdup(const char* string)
{
	VERIFY(string);
	u32 len = u32(xr_strlen(string)) + 1;
	char* memory = (char*)Memory.mem_alloc(len);
	CopyMemory(memory, string, len);
	return memory;
}

//TODO: 
size_t xrMemory::mem_usage() {}
void xrMemory::mem_compact() {}
void xrMemory::log_vminfo() {
	// Msg(
	// 	"* [win32]: free[%lld K], reserved[%lld K], committed[%lld K]",
	// 	w_free / 1024,
	// 	w_reserved / 1024,
	// 	w_committed / 1024
	// );
}
