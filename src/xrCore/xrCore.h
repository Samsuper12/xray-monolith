#ifndef xrCoreH
#define xrCoreH
#pragma once

#include "xrstring.h"
#include "log.h"
#include <stdint.h>
#include <filesystem>
#include <optional>
#include <string>
#include <filesystem>
#include <iostream>
#include <unistd.h>
#include <args.hxx>

namespace std {
	namespace fs = std::filesystem;
};

//RENAME:
// ********************************************** The Core definition
class XRCORE_API xrCore
{
public:
	struct StartupFlags {
		args::ArgumentParser p{"XRay Monolith"};
		args::HelpFlag help{p, "help", "Display this help menu", {'h', "help"}};


		args::ValueFlag<std::fs::path> fsltx{p, "fsltx path", "", {"-fsltx"}};
		args::ValueFlag<std::fs::path> overlaypath{p, "overlay path", "", {"-overlaypath"}};
		args::ValueFlag<std::fs::path> ltx{p, "ltx path", "", {"-ltx"}};
		args::ValueFlag<std::fs::path> demomode{p, "demomode", "", {"-demomode"}};
		args::ValueFlag<std::fs::path> svcfg{p, "svcfg path", "", {"-svcfg"}};


		args::ValueFlag<std::string> start{p, "start", "", {"-start"}};
		args::ValueFlag<std::string> load{p, "load", "", {"-load"}};
		args::ValueFlag<std::string> benchmark{p, "benchmark","batch benchmark <name>", {"-benchmark"}};
		args::ValueFlag<std::string> openautomate{p, "openautomate","openautomate", {"-openautomate"}};

		args::ValueFlag<float> gloss{p, "gloss", "", {"-gloss"}};

		args::Flag launcher{p, "launcher","launcher", {"-launcher"}};
		args::Flag editor{p, "editor", "editor", {"-editor"}};
		args::Flag mem_debug{p, "memory debug",  "memory debug", {"-mem_debug"}};
		args::Flag build{p, "build", "build", {"-build"}};
		args::Flag ebuild{p, "ebuild", "ebuild", {"-ebuild"}};
		args::Flag cache{p, "cache", "cache", {"-cache"}};
		args::Flag file_activity{p, "file activity", "file activity", {"-file_activity"}};
		args::Flag dbgdev{p, "dbgdev", "dbgdev", {"-dbgdev"}};
		args::Flag sound_constant_speed{p, "sound_constant_speed", "sound_constant_speed", {"-sound_constant_speed"}};
		args::Flag ignore_save_incompatibility{p, "ignore_save_incompatibility", "ignore_save_incompatibility", {"-ignore_save_incompatibility"}};
		args::Flag keep_lua{p, "keep_lua", "keep_lua", {"-keep_lua"}};
		args::Flag dbgact{p, "dbgact", "dbgact", {"-dbgact"}};
		args::Flag capture_input{p, "capture_input", "capture_input", {"-capture_input"}};
		args::Flag slowdown{p, "slowdown", "slowdown", {"-slowdown"}};
		args::Flag slowdown2x{p, "slowdown2x", "slowdown2x", {"-slowdown2x"}};
		args::Flag xclsx{p, "xclsx", "xclsx", {"-xclsx"}};
		args::Flag noprefetch{p, "noprefetch", "noprefetch", {"-noprefetch"}};
		args::Flag nes_texture_storing{p, "nes_texture_storing", "nes_texture_storing", {"-nes_texture_storing"}};
		args::Flag perfhud_hack{p, "perfhud_hack", "perfhud_hack", {"-perfhud_hack"}};
		args::Flag swap_on_compact{p, "swap_on_compact", "swap_on_compact", {"-swap_on_compact"}};
		args::Flag memo{p, "memo", "memo", {"-memo"}};
		args::Flag pure_alloc{p, "pure_alloc", "pure_alloc", {"-pure_alloc"}};
		args::Flag nolog{p, "nolog", "nolog", {"-nolog"}};
		args::Flag auth_debug{p, "auth_debug", "auth_debug", {"-auth_debug"}};
		args::Flag auto_load_arch{p, "auto_load_arch", "auto_load_arch", {"-auto_load_arch"}};
		args::Flag x86{p, "x86", "x86", {"-x86"}};
		args::Flag mt_cdb{p, "mt_cdb", "mt_cdb", {"-mt_cdb"}};
		args::Flag skinw{p, "skinw", "skinw", {"-skinw"}};
		args::Flag disasm{p, "disasm", "disasm", {"-disasm"}};
		args::Flag nodistort{p, "nodistort", "nodistort", {"-nodistort"}};
		args::Flag tsh{p, "tsh", "tsh", {"-tsh"}};
		args::Flag noshadows{p, "noshadows", "noshadows", {"-noshadows"}};
		args::Flag depth16{p, "depth16", "depth16", {"-depth16"}};
		args::Flag sjitter{p, "sjitter", "sjitter", {"-sjitter"}};
		args::Flag sunfilter{p, "sunfilter", "sunfilter", {"-sunfilter"}};
		args::Flag bug{p, "bug", "bug", {"-bug"}};
		args::Flag sunstatic{p, "sunstatic", "sunstatic", {"-sunstatic"}};
		args::Flag smap1536{p, "smap1536", "smap1536", {"-smap1536"}};
		args::Flag smap2048{p, "smap2048", "smap2048", {"-smap2048"}};
		args::Flag smap2560{p, "smap2560", "smap2560", {"-smap2560"}};
		args::Flag smap3072{p, "smap3072", "smap3072", {"-smap3072"}};
		args::Flag smap4096{p, "smap4096", "smap4096", {"-smap4096"}};
		args::Flag r4xx{p, "r4xx", "r4xx", {"-r4xx"}};
		args::Flag nojit{p, "nojit", "nojit", {"-nojit"}};
		args::Flag dbg{p, "dbg", "dbg", {"-dbg"}};
		args::Flag nosound{p, "nosound", "nosound", {"-nosound"}};
		args::Flag prefetch_sounds{p, "prefetch_sounds", "prefetch_sounds", {"-prefetch_sounds"}};
		args::Flag _g{p, "_g", "_g", {"-_g"}};
		args::Flag break_on_assert{p, "break_on_assert", "break_on_assert", {"-break_on_assert"}};
		args::Flag designer{p, "designer", "designer", {"-designer"}};
		args::Flag lua_studio{p, "lua_studio", "lua_studio", {"-lua_studio"}};
		args::Flag dump_traffic{p, "dump_traffic", "dump_traffic", {"-dump_traffic"}};
		args::Flag dbgbullet{p, "dbgbullet", "dbgbullet", {"-dbgbullet"}};
		args::Flag nove{p, "nove", "nove", {"-nove"}};
		args::Flag debug_ge{p, "debug_ge", "debug_ge", {"-debug_ge"}};
		args::Flag skiplogo{p, "skiplogo", "skiplogo", {"-skiplogo"}};
		args::Flag nointro{p, "nointro", "nointro", {"-nointro"}};
		args::Flag savescreenshots{p, "savescreenshots", "savescreenshots", {"-savescreenshots"}};
		args::Flag r2{p, "r2", "r2", {"-r2"}};
		args::Flag r2a{p, "r2a", "r2a", {"-r2a"}};
		args::Flag r4_dev{p, "r4_dev", "r4_dev", {"-r4_dev"}};
		args::Flag noramtex{p, "noramtex", "noramtex", {"-noramtex"}};
		args::Flag nonvs{p, "nonvs", "nonvs", {"-nonvs"}};
		args::Flag nodf24{p, "nodf24", "nodf24", {"-nodf24"}};
		args::Flag no_volumetric_fog{p, "no_volumetric_fog", "no_volumetric_fog", {"-no_volumetric_fog"}};
		args::Flag fps60{p, "fps60", "fps60", {"-fps60"}};
		args::Flag no_bump_mode1{p, "no_bump_mode1", "no_bump_mode1", {"-no_bump_mode1"}};
		args::Flag no_bump_mode2{p, "no_bump_mode2", "no_bump_mode2", {"-no_bump_mode2"}};
		args::Flag no_dialog_header{p, "no_dialog_header", "no_dialog_header", {"-no_dialog_header"}};
		args::Flag game_designer{p, "game_designer", "game_designer", {"-game_designer"}};
		args::Flag no_occq{p, "no_occq", "no_occq", {"-no_occq"}};
		args::Flag noaref{p, "noaref", "noaref", {"-noaref"}};
		args::Flag gpu_sw{p, "gpu_sw", "gpu_sw", {"-gpu_sw"}};
		args::Flag gpu_nopure{p, "gpu_nopure", "gpu_nopure", {"-gpu_nopure"}};
		args::Flag gpu_ref{p, "gpu_ref", "gpu_ref", {"-gpu_ref"}};
	};

	std::string ApplicationName;
	std::fs::path ApplicationPath;
	std::fs::path WorkingPath;
	std::string UserName;
	std::string CompName;
	std::string RawArgs;
	StartupFlags Params;
	uint32_t dwFrame;
	bool april1;

public:
	void ParseArgs(int argc, char** argv);
	void _initialize(const std::string& ApplicationName);
	void _destroy();

private:
	std::tuple<std::string, std::string> FetchPCNames();

};

// TODO: remove fucking static objects
extern XRCORE_API xrCore Core;

#endif
