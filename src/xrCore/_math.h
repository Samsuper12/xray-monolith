#pragma once

#include "vector.h"
#include "cpuid.h"
namespace CPU
{
	XRCORE_API extern u64 clk_per_second;
	XRCORE_API extern uint64_t qpc_freq;
	XRCORE_API extern _processor_info ID;
	XRCORE_API extern long long QPC();

	inline long long GetCLK(void)
	{
		return QPC();
	}
};

extern XRCORE_API void _initialize_cpu();

// threading
typedef void thread_t2(void*);
extern XRCORE_API void thread_spawn(
	thread_t2* entry,
	const char* name,
	unsigned stack,
	void* arglist
);