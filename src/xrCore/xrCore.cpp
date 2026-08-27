// xrCore.cpp : Defines the entry point for the DLL application.
//

#include <fstream>
#include <iostream>
#include <string>
#include "FileSystem.h"
#include "LocatorAPI.h"
#include "string_concatenations.h"
#include "rt_compressor.h"
#include "xrCore.h"
#include <profiler.h>

xrCore Core;

static u32 init_counter = 0;

class CLocatorAPI;
extern CLocatorAPI* xr_FS;
extern u32 build_id;
extern LPCSTR build_date;
extern int get_modded_exes_version();
extern std::string timeInDMYHMSMMM();
namespace CPU
{
	extern void Detect();
};

void xrCore::ParseArgs(int argc, char **argv) {
	try {
		Params.p.ParseCLI(argc, argv);
		ApplicationPath = std::filesystem::canonical(argv[0]);
		WorkingPath = ApplicationPath.parent_path();

		for (auto i = 0; i < argc; ++i) {
			if (i > 0) RawArgs += " ";
			RawArgs += argv[i];
		}

	} catch (const args::Help &) {
		// FMT:
		std::cout << Params.p;
  } catch (const args::ParseError &e) {
		Msg(e.what());
  }
}

std::tuple<std::string, std::string> xrCore::FetchPCNames() {
	std::string username, hostname;
#ifdef _WIN32
	char buf[256];
	auto size = sizeof(buf);
	iGetuserNameA(buf, &size))
	username = buf;
    size = sizeof(buf);
    GetComputerNameA(buf, &size);
    hostname = buf;
#else
	char buf[256];
	gethostname(buf, sizeof(buf));
	username = getenv("USER");
	hostname = buf;
#endif
    return {username, hostname};
}

void xrCore::_initialize(const std::string& ApplicationName)
{
	PROF_EVENT();
	auto [username, hostname] = FetchPCNames();
	this->ApplicationName = ApplicationName;
	this->UserName = username;
	this->CompName = hostname;

	if (0 == init_counter)
	{
		Memory._initialize(Params.mem_debug);

		InitLog();
		_initialize_cpu();

		rtc_initialize();

		xr_FS = xr_new<CLocatorAPI>();
		xr_EFS = xr_new<EFS_Utils>();
		//. R_ASSERT (co_res==S_OK);
	}

		u32 flags = 0;
		if (Params.build) flags |= CLocatorAPI::flBuildCopy;
		if (Params.ebuild) flags |= CLocatorAPI::flBuildCopy | CLocatorAPI::flEBuildCopy;
#ifdef DEBUG
        if (Params.cache) flags |= CLocatorAPI::flCacheFiles;
        else flags &= ~CLocatorAPI::flCacheFiles;
#endif // DEBUG

#ifdef _EDITOR // for EDITORS - no cache
        flags &= ~CLocatorAPI::flCacheFiles;
#endif // _EDITOR
		flags |= CLocatorAPI::flScanAppRoot;

		if (Params.file_activity) flags |= CLocatorAPI::flDumpFileActivity;

		bool ltxPresent = Params.fsltx && std::filesystem::exists(args::get(Params.fsltx));
		FS._initialize(flags, 0, ltxPresent ? args::get(Params.fsltx).c_str() : nullptr);
		Msg("'%s' build %d, %s\n", "xrCore", build_id, build_date);

		// demonized: Print modded exes version
		Msg("Modded exes version %d\n", get_modded_exes_version());
		Msg("Game started: %s\n", timeInDMYHMSMMM().c_str());
		EFS._initialize();
	
	SetLogCB(nullptr);
	init_counter++;
}

#ifndef _EDITOR
#include "compression_ppmd_stream.h"
extern compression::ppmd::stream* trained_model;
#endif
void xrCore::_destroy()
{
	--init_counter;
	if (0 == init_counter)
	{
		FS._destroy();
		EFS._destroy();
		xr_delete(xr_FS);
		xr_delete(xr_EFS);

#ifndef _EDITOR
		if (trained_model)
		{
			void* buffer = trained_model->buffer();
			xr_free(buffer);
			xr_delete(trained_model);
		}
#endif
		Memory._destroy();
	}
}

#ifdef _EDITOR
BOOL WINAPI DllEntryPoint(HINSTANCE hinstDLL, DWORD ul_reason_for_call, LPVOID lpvReserved)
#endif