#define MMNOSOUND
#define MMNOMIDI
#define MMNOAUX
#define MMNOMIXER
#define MMNOJOY

#include "_math.h"
#include "_matrix.h"
#include "_random.h"
#include "cpuid.h"
#include "log.h"
#include "profiler.h"
#include "xrCore.h"
#include <thread>

// Initialized on startup
XRCORE_API Fmatrix Fidentity;
XRCORE_API Dmatrix Didentity;
XRCORE_API CRandom Random;

struct LaunchedThread {
	std::string functionName;
	std::thread thread;
};

static std::vector<LaunchedThread> launchedThreads{};
namespace CPU
{
	XRCORE_API u64 clk_per_second;
	XRCORE_API u64 qpc_freq = 1'000'000'000LL;
	XRCORE_API _processor_info ID;

	XRCORE_API long long QPC()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}
};

bool g_initialize_cpu_called = false;

//------------------------------------------------------------------------------------
void _initialize_cpu(void)
{
	// TODO: maybe later.
	// Msg("* Detected CPU: %s [%s], F%d/M%d/S%d, %.2f mhz, %d-clk 'rdtsc'",
	//     CPU::ID.model_name, CPU::ID.v_name,
	//     CPU::ID.family, CPU::ID.model, CPU::ID.stepping,
	//     float(CPU::clk_per_second / u64(1000000)),
	//     u32(CPU::clk_overhead)
	// );

	// // DUMP_PHASE;

	// if (Core.Params.x86)
	// {
	// 	CPU::ID.feature &= ~_CPU_FEATURE_MMX;
	// 	CPU::ID.feature &= ~_CPU_FEATURE_3DNOW;
	// 	CPU::ID.feature &= ~_CPU_FEATURE_SSE;
	// 	CPU::ID.feature &= ~_CPU_FEATURE_SSE2;
	// 	CPU::ID.feature &= ~_CPU_FEATURE_SSE3;
	// 	CPU::ID.feature &= ~_CPU_FEATURE_SSSE3;
	// 	CPU::ID.feature &= ~_CPU_FEATURE_SSE4_1;
	// 	CPU::ID.feature &= ~_CPU_FEATURE_SSE4_2;
	// };

	// string256 features;
	// xr_strcpy(features, sizeof(features), "RDTSC");
	// if (CPU::ID.feature & _CPU_FEATURE_MMX) xr_strcat(features, ", MMX");
	// if (CPU::ID.feature & _CPU_FEATURE_3DNOW) xr_strcat(features, ", 3DNow!");
	// if (CPU::ID.feature & _CPU_FEATURE_SSE) xr_strcat(features, ", SSE");
	// if (CPU::ID.feature & _CPU_FEATURE_SSE2) xr_strcat(features, ", SSE2");
	// if (CPU::ID.feature & _CPU_FEATURE_SSE3) xr_strcat(features, ", SSE3");
	// if (CPU::ID.feature & _CPU_FEATURE_SSSE3) xr_strcat(features, ", SSSE3");
	// if (CPU::ID.feature & _CPU_FEATURE_SSE4_1)xr_strcat(features, ", SSE4.1");
	// if (CPU::ID.feature & _CPU_FEATURE_SSE4_2)xr_strcat(features, ", SSE4.2");
	// if (CPU::ID.feature & _CPU_FEATURE_HTT) xr_strcat(features, ", HTT");

	// Msg("* CPU features: %s", features);
	Msg("* CPU threads: %d/%d\n", std::thread::hardware_concurrency());

	Fidentity.identity(); // Identity matrix
	Didentity.identity(); // Identity matrix
	pvInitializeStatics(); // Lookup table for compressed normals
	Random.seed(u32(CPU::GetCLK() % (1 << 32)));

	g_initialize_cpu_called = true;
}

void thread_spawn(thread_t* entry, const char* name, unsigned stack, void* arglist)
{
	Msg("Thread launched: %s", name);
	auto& ref = launchedThreads.emplace_back(LaunchedThread{.functionName = name, .thread = std::thread(entry, arglist)});
	ref.thread.detach();
}