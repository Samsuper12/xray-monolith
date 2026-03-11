//#include <dinput.h>

#include <LocatorAPI.h>
#include <XR_IOConsole.h>
#include "xr_sdl3_input.hpp"
#include <xr_trims.h>
#include <xr_ioc_cmd.h>

#include "xr_level_controller.h"
#include "string_table.h"
#include <algorithm>
#include <variant>
#include <type_traits>
#include <sstream>
#include <functional>
#include <cstring>

std::vector<_binding> g_key_bindings;

const std::vector<_action> actions {
	{"left", kLEFT},
	{"right", kRIGHT},
	{"up", kUP},
	{"down", kDOWN},
	{"jump", kJUMP},
	{"crouch", kCROUCH},
	{"accel", kACCEL},
	{"sprint_toggle", kSPRINT_TOGGLE},

	{"forward", kFWD},
	{"back", kBACK},
	{"lstrafe", kL_STRAFE},
	{"rstrafe", kR_STRAFE},

	{"llookout", kL_LOOKOUT},
	{"rlookout", kR_LOOKOUT},

	{"cam_1", kCAM_1},
	{"cam_2", kCAM_2},
	{"cam_3", kCAM_3},
	{"cam_zoom_in", kCAM_ZOOM_IN},
	{"cam_zoom_out", kCAM_ZOOM_OUT},

	{"torch", kTORCH},
	{"night_vision", kNIGHT_VISION},
	{"show_detector", kDETECTOR},

	{"wpn_1", kWPN_1},
	{"wpn_2", kWPN_2},
	{"wpn_3", kWPN_3},
	{"wpn_4", kWPN_4},
	{"wpn_5", kWPN_5},
	{"wpn_6", kWPN_6},
	{"artefact", kARTEFACT/*_mp*/},
	{"wpn_next", kWPN_NEXT}, // means next ammo type
	{"wpn_fire", kWPN_FIRE},
	{"wpn_zoom", kWPN_ZOOM},
	{"wpn_zoom_inc", kWPN_ZOOM_INC},
	{"wpn_zoom_dec", kWPN_ZOOM_DEC},
	{"wpn_reload", kWPN_RELOAD},
	{"wpn_func", kWPN_FUNC},
	{"wpn_firemode_prev", kWPN_FIREMODE_PREV},
	{"wpn_firemode_next", kWPN_FIREMODE_NEXT},

	{"pause", kPAUSE},
	{"drop", kDROP},
	{"use", kUSE},
	{"scores", kSCORES},
	{"chat", kCHAT},
	{"chat_team", kCHAT_TEAM},
	{"screenshot", kSCREENSHOT},
	{"quit", kQUIT},
	{"console", kCONSOLE},
	{"inventory", kINVENTORY},
	{"buy_menu", kBUY},
	{"skin_menu", kSKIN},
	{"team_menu", kTEAM},
	{"active_jobs", kACTIVE_JOBS},

	{"vote_begin", kVOTE_BEGIN},
	{"show_admin_menu", kSHOW_ADMIN_MENU},
	{"vote", kVOTE},
	{"vote_yes", kVOTEYES},
	{"vote_no", kVOTENO},

	{"next_slot", kNEXT_SLOT},
	{"prev_slot", kPREV_SLOT},

	{"speech_menu_0", kSPEECH_MENU_0},
	{"speech_menu_1", kSPEECH_MENU_1},

	{"quick_use_1", kQUICK_USE_1},
	{"quick_use_2", kQUICK_USE_2},
	{"quick_use_3", kQUICK_USE_3},
	{"quick_use_4", kQUICK_USE_4},

	{"quick_save", kQUICK_SAVE},
	{"quick_load", kQUICK_LOAD},
	//	{ "alife_command",		kALIFE_CMD				,_sp},		
	{"custom1", kCUSTOM1},
	{"custom2", kCUSTOM2},
	{"custom3", kCUSTOM3},
	{"custom4", kCUSTOM4},
	{"custom5", kCUSTOM5},
	{"custom6", kCUSTOM6},
	{"custom7", kCUSTOM7},
	{"custom8", kCUSTOM8},
	{"custom9", kCUSTOM9},
	{"custom10", kCUSTOM10},
	{"custom11", kCUSTOM11},
	{"custom12", kCUSTOM12},
	{"custom13", kCUSTOM13},
	{"custom14", kCUSTOM14},
	{"custom15", kCUSTOM15},
	{"custom16", kCUSTOM16 },
	{"custom17", kCUSTOM17 },
	{"custom18", kCUSTOM18 },
	{"custom19", kCUSTOM19 },
	{"custom20", kCUSTOM20 },
	{"custom21", kCUSTOM21 },
	{"custom22", kCUSTOM22 },
	{"custom23", kCUSTOM23 },
	{"custom24", kCUSTOM24 },
	{"custom25", kCUSTOM25 },
	{"safemode", kSAFEMODE},
	{"freelook", kFREELOOK},
	{"cam_autoaim", kCAM_AUTOAIM},
	{"editor", kEDITOR},
};

std::vector<_keyboard> keyboards {
	{"kESCAPE", SDL_SCANCODE_ESCAPE}, {"k1", SDL_SCANCODE_1},
	{"k2", SDL_SCANCODE_2}, {"k3", SDL_SCANCODE_3},
	{"k4", SDL_SCANCODE_4}, {"k5", SDL_SCANCODE_5},
	{"k6", SDL_SCANCODE_6}, {"k7", SDL_SCANCODE_7},
	{"k8", SDL_SCANCODE_8}, {"k9", SDL_SCANCODE_9},
	{"k0", SDL_SCANCODE_0}, {"kMINUS", SDL_SCANCODE_MINUS},
	{"kEQUALS", SDL_SCANCODE_EQUALS}, {"kBACK", SDL_SCANCODE_BACKSPACE},
	{"kTAB", SDL_SCANCODE_TAB}, {"kQ", SDL_SCANCODE_Q},
	{"kW", SDL_SCANCODE_W}, {"kE", SDL_SCANCODE_E},
	{"kR", SDL_SCANCODE_R}, {"kT", SDL_SCANCODE_T},
	{"kY", SDL_SCANCODE_Y}, {"kU", SDL_SCANCODE_U},
	{"kI", SDL_SCANCODE_I}, {"kO", SDL_SCANCODE_O},
	{"kP", SDL_SCANCODE_P}, {"kLBRACKET", SDL_SCANCODE_LEFTBRACKET},
	{"kRBRACKET", SDL_SCANCODE_RIGHTBRACKET}, {"kRETURN", SDL_SCANCODE_RETURN},
	{"kLCONTROL", SDL_SCANCODE_LCTRL}, {"kA", SDL_SCANCODE_A},
	{"kS", SDL_SCANCODE_S}, {"kD", SDL_SCANCODE_D},
	{"kF", SDL_SCANCODE_F}, {"kG", SDL_SCANCODE_G},
	{"kH", SDL_SCANCODE_H}, {"kJ", SDL_SCANCODE_J},
	{"kK", SDL_SCANCODE_K}, {"kL", SDL_SCANCODE_L},
	{"kSEMICOLON", SDL_SCANCODE_SEMICOLON}, {"kAPOSTROPHE", SDL_SCANCODE_APOSTROPHE},
	{"kGRAVE", SDL_SCANCODE_GRAVE}, {"kLSHIFT", SDL_SCANCODE_LSHIFT},
	{"kBACKSLASH", SDL_SCANCODE_BACKSLASH}, {"kZ", SDL_SCANCODE_Z},
	{"kX", SDL_SCANCODE_X}, {"kC", SDL_SCANCODE_C},
	{"kV", SDL_SCANCODE_V}, {"kB", SDL_SCANCODE_B},
	{"kN", SDL_SCANCODE_N}, {"kM", SDL_SCANCODE_M},
	{"kCOMMA", SDL_SCANCODE_COMMA}, {"kPERIOD", SDL_SCANCODE_PERIOD},
	{"kSLASH", SDL_SCANCODE_SLASH}, {"kRSHIFT", SDL_SCANCODE_RSHIFT},
	{"kMULTIPLY", SDL_SCANCODE_KP_MULTIPLY}, {"kLMENU", SDL_SCANCODE_MENU},
	{"kSPACE", SDL_SCANCODE_SPACE}, {"kCAPITAL", SDL_SCANCODE_CAPSLOCK},
	{"kF1", SDL_SCANCODE_F1}, {"kF2", SDL_SCANCODE_F2},
	{"kF3", SDL_SCANCODE_F3}, {"kF4", SDL_SCANCODE_F4},
	{"kF5", SDL_SCANCODE_F5}, {"kF6", SDL_SCANCODE_F6},
	{"kF7", SDL_SCANCODE_F7}, {"kF8", SDL_SCANCODE_F8},
	{"kF9", SDL_SCANCODE_F9}, {"kF10", SDL_SCANCODE_F10},
	{"kNUMLOCK", SDL_SCANCODE_NUMLOCKCLEAR}, {"kSCROLL", SDL_SCANCODE_SCROLLLOCK},
	{"kNUMPAD7", SDL_SCANCODE_KP_7}, {"kNUMPAD8", SDL_SCANCODE_KP_8},
	{"kNUMPAD9", SDL_SCANCODE_KP_9}, {"kSUBTRACT", SDL_SCANCODE_KP_MINUS},
	{"kNUMPAD4", SDL_SCANCODE_KP_4}, {"kNUMPAD5", SDL_SCANCODE_KP_5},
	{"kNUMPAD6", SDL_SCANCODE_KP_6}, {"kADD", SDL_SCANCODE_KP_PLUS},
	{"kNUMPAD1", SDL_SCANCODE_KP_1}, {"kNUMPAD2", SDL_SCANCODE_KP_2},
	{"kNUMPAD3", SDL_SCANCODE_KP_3}, {"kNUMPAD0", SDL_SCANCODE_KP_0},
	{"kDECIMAL", SDL_SCANCODE_DELETE}, {"kF11", SDL_SCANCODE_F11},
	{"kF12", SDL_SCANCODE_F12}, {"kF13", SDL_SCANCODE_F13},
	{"kF14", SDL_SCANCODE_F14}, {"kF15", SDL_SCANCODE_F15},
	{"kNUMPADEQUALS", SDL_SCANCODE_KP_EQUALS},
	{"kSTOP", SDL_SCANCODE_STOP}, 
	{"kNUMPADENTER", SDL_SCANCODE_KP_ENTER},
	{"kRCONTROL", SDL_SCANCODE_RCTRL}, {"kNUMPADCOMMA", SDL_SCANCODE_KP_PERIOD},
	{"kDIVIDE", SDL_SCANCODE_KP_DIVIDE}, {"kSYSRQ", SDL_SCANCODE_SYSREQ},
	{"kRMENU", SDL_SCANCODE_MENU}, {"kHOME", SDL_SCANCODE_HOME},
	{"kUP", SDL_SCANCODE_UP}, {"kPRIOR", SDL_SCANCODE_PRIOR},
	{"kLEFT", SDL_SCANCODE_LEFT}, {"kRIGHT", SDL_SCANCODE_RIGHT},
	{"kEND", SDL_SCANCODE_END}, {"kDOWN", SDL_SCANCODE_DOWN},
	{"kINSERT", SDL_SCANCODE_INSERT},
	{"kDELETE", SDL_SCANCODE_DELETE}, {"kLWIN", SDL_SCANCODE_LGUI},
	{"kRWIN", SDL_SCANCODE_RGUI}, {"kAPPS", SDL_SCANCODE_APPLICATION},
	{"kPAUSE", SDL_SCANCODE_PAUSE},

	{"mouse1", static_cast<SDL_Scancode>(SDL_BUTTON_LEFT)},
	{"mouse2", static_cast<SDL_Scancode>(SDL_BUTTON_RIGHT)},
	{"mouse3", static_cast<SDL_Scancode>(SDL_BUTTON_MIDDLE)}
};

void initialize_bindings()
{
	g_key_bindings.reserve(actions.size());
}

std::optional<_action> get_action_by_name(const char* _name)
{
	auto res = std::find_if(actions.begin(), actions.end(), [_name] (const auto& action) -> bool {
		return _stricmp(action.action_name, _name) == 0;
	});

	if (res != actions.end())
		return std::make_optional(*res);

	return std::nullopt;
}

_keyboard* get_keyboard_by_code(SDL_Scancode code)
{
	auto res = std::find_if(keyboards.begin(), keyboards.end(), [code] (const auto& keyboard) -> bool {
		return keyboard.code == code;
	});

	if(res != keyboards.end()) 
		return std::addressof(*res);

	Msg("! cant find corresponding [_keyboard] for code");
	return nullptr;
}

_keyboard* get_keyboard_by_name(const char* _name)
{
	auto res = std::find_if(keyboards.begin(), keyboards.end(), [_name] (const auto& keyboard) -> bool {
		return _stricmp(keyboard.key_name, _name) == 0;
	});

	if (res != keyboards.end())
		return std::addressof(*res);

	Msg("! cant find corresponding [_keyboard] for keyname %s", _name);
	return nullptr;
}

bool is_binded_sdl(EGameActions _action_id, SDL_Scancode code)
{
	auto res = std::find_if(g_key_bindings.begin(),g_key_bindings.end(), [_action_id] (const auto& binding) {
		return binding.action.id == _action_id;
	});

	return res != g_key_bindings.end() ? ((res->keyboard[0] && res->keyboard[0]->code == code) || (res->keyboard[1] && res->keyboard[1]->code == code))  : false;
}

std::optional<std::reference_wrapper<_binding>> get_binding_by_action_id_ref(EGameActions _action_id) {
	auto res = std::find_if(g_key_bindings.begin(),g_key_bindings.end(), [_action_id] (const auto& binding) {
			return binding.action.id == _action_id;
		});

	if (res != g_key_bindings.end())
		return std::ref(*res);

	Msg("! cant find corresponding binding for action %d", _action_id);
	return std::nullopt;
}

std::optional<_binding> get_binding_by_action_id(EGameActions _action_id) {
	auto res = std::find_if(g_key_bindings.begin(),g_key_bindings.end(), [_action_id] (const auto& binding) {
			return binding.action.id == _action_id;
		});

	if (res != g_key_bindings.end())
		return std::make_optional(*res);

	Msg("! cant find corresponding binding for action %d", _action_id);
	return std::nullopt;
}

SDL_Scancode get_scancode_by_action_id(EGameActions _action_id, bind_type bind) {
	auto res = std::find_if(g_key_bindings.begin(),g_key_bindings.end(), [_action_id] (const auto& binding) {
			return binding.action.id == _action_id;
		});

	if (res == g_key_bindings.end()) {
		Msg("! cant find corresponding code for action %d", _action_id);
		return SDL_SCANCODE_UNKNOWN;
	}

	switch (bind) {
		case bind_type::primary:
			if (res->keyboard[0])
				return res->keyboard[0]->code;
			break;
		case bind_type::secondary:
		if (res->keyboard[1])
				return res->keyboard[1]->code;
			break;
		case bind_type::any:
		if (res->keyboard[0])
				return res->keyboard[0]->code;
		if (res->keyboard[1])
				return res->keyboard[1]->code;
			break;
	}
	
	Msg("! cant find corresponding code for [action %d / bind: %d]", _action_id, static_cast<int>(bind));
	return SDL_SCANCODE_UNKNOWN;
}

EGameActions get_action_id_by_scancode(SDL_Scancode code) {
	auto res = std::find_if(g_key_bindings.begin(), g_key_bindings.end(), [code] (const auto& binding) -> bool {
		return (binding.keyboard[0] && binding.keyboard[0]->code == code) ? true : (binding.keyboard[1] && binding.keyboard[1]->code == code);
	});
	
	return res != g_key_bindings.end() ? res->action.id : kNOTBINDED;
}

std::string GetActionAllBinding(const char* _action_name)
{
	std::string ret, prim, sec;

	auto action = get_action_by_name(_action_name);
	if (!action)
		return CStringTable().translate("st_key_notbinded").c_str();

	auto binding = get_binding_by_action_id(action->id);
	if (!binding)
		return CStringTable().translate("st_key_notbinded").c_str();

	if (binding->keyboard[0]) {
		prim = std::string(binding->keyboard[0]->key_name);
	}
	if (binding->keyboard[1]) {
		sec = std::string(binding->keyboard[1]->key_name);
	}

	if (binding->keyboard[0] && binding->keyboard[1]) {
		return CStringTable().translate("st_key_notbinded").c_str();
	}

	if(!prim.empty())
		ret += prim;

	if (!sec.empty() && !prim.empty())
		ret.append(" , ");
		
	if(!sec.empty())
		ret += sec;
	
	return ret;
}

ConsoleBindCmds bindConsoleCmds;
// BOOL bRemapped = FALSE;

class CCC_Bind : public IConsole_Command
{
	int m_work_idx;
public:
	CCC_Bind(const char* N, int idx) : IConsole_Command(N), m_work_idx(idx)
	{
	};

	virtual void Execute(const char* args)
	{
		std::string action_name;
		std::string key_name;
		
		std::istringstream iss(args);
		iss >> action_name >> key_name;

		if (action_name.empty() || key_name.empty())
			return;

		auto action_id = get_action_by_name(action_name.c_str());
		auto* pkeyboard = get_keyboard_by_name(key_name.c_str());

		if (!action_id || !pkeyboard)
			return;

		auto& curr_rbinding = g_key_bindings.emplace_back(_binding{action_id.value()});

		curr_rbinding.keyboard[m_work_idx] = pkeyboard;

		// TODO: check for multiple binding points

		CStringTable::ReparseKeyBindings();
	}

	virtual void Save(IWriter* F)
	{
		if (m_work_idx == 0)
			F->w_printf("default_controls\r\n");

		for(const auto& binding : g_key_bindings) {
			if (binding.keyboard[m_work_idx]) {
				F->w_printf("%s %s %s\r\n",
				            cName,
				            binding.action.action_name,
				            binding.keyboard[m_work_idx]->key_name);
			}
		}
	}
};

class CCC_UnBind : public IConsole_Command
{
	int m_work_idx;
public:
	CCC_UnBind(const char* N, int idx) : IConsole_Command(N), m_work_idx(idx)
	{
		bEmptyArgsHandled = TRUE;
	};

	virtual void Execute(const char* args)
	{
		auto action = get_action_by_name(args);
	
		if(!action)
			return;
		auto binging = get_binding_by_action_id_ref(action.value().id);

		if (binging) {
			binging.value().get().keyboard[m_work_idx] = nullptr;
			CStringTable::ReparseKeyBindings();
		}
	}
};

class CCC_ListActions : public IConsole_Command
{
public:
	CCC_ListActions(const char* N) : IConsole_Command(N)
	{
		bEmptyArgsHandled = TRUE;
	};

	virtual void Execute(const char* args)
	{
		Log("- --- Action list start ---");
		for(const auto& binding : g_key_bindings) {
			Log("-", binding.action.action_name);
		}
		Log("- --- Action list end   ---");
	}
};

class CCC_UnBindAll : public IConsole_Command
{
public:
	CCC_UnBindAll(const char* N) : IConsole_Command(N)
	{
		bEmptyArgsHandled = TRUE;
	};

	virtual void Execute(const char* args)
	{
		g_key_bindings.clear();
		bindConsoleCmds.clear();
	}
};

class CCC_DefControls : public CCC_UnBindAll
{
public:
	CCC_DefControls(const char* N) : CCC_UnBindAll(N)
	{
	}

	virtual void Execute(const char* args)
	{
		CCC_UnBindAll::Execute(args);
		string_path _cfg;
		string_path cmd;
		FS.update_path(_cfg, "$game_config$", "default_controls.ltx");
		strconcat(sizeof(cmd), cmd, "cfg_load", " ", _cfg);
		Console->Execute("bind editor kF11"); //Lucy : ImGui default key
		Console->Execute(cmd);
	}
};

class CCC_BindList : public IConsole_Command
{
public:
	CCC_BindList(const char* N) : IConsole_Command(N)
	{
		bEmptyArgsHandled = TRUE;
	};

	virtual void Execute(const char* args)
	{
		Log("- --- Bind list start ---");
		string512 buff;

		for(const auto& binding : g_key_bindings) {
			xr_sprintf(buff, "[%s] primary is[%s] secondary is[%s]",
			           binding.action.action_name,
			           (binding.keyboard[0]) ? binding.keyboard[0]->key_name : "NULL",
			           (binding.keyboard[1]) ? binding.keyboard[1]->key_name : "NULL");
			Log(buff);
		}
		Log("- --- Bind list end   ---");
	}
};

class CCC_BindConsoleCmd : public IConsole_Command
{
public:
	CCC_BindConsoleCmd(const char* N) : IConsole_Command(N)
	{
	};

	virtual void Execute(const char* args)
	{
		string512 console_command;
		string256 key;
		int cnt = _GetItemCount(args, ' ');
		_GetItems(args, 0, cnt - 1, console_command, ' ');
		_GetItem(args, cnt - 1, key, ' ');

		const auto keyboard = get_keyboard_by_name(key);
		if (keyboard) {
			bindConsoleCmds.bind(keyboard->code, console_command);
		}
	}

	virtual void Save(IWriter* F)
	{
		bindConsoleCmds.save(F);
	}
};


class CCC_UnBindConsoleCmd : public IConsole_Command
{
public:
	CCC_UnBindConsoleCmd(const char* N) : IConsole_Command(N)
	{
		bEmptyArgsHandled = FALSE;
	};

	virtual void Execute(const char* args)
	{
		const auto keyboard = get_keyboard_by_name(args);
		if (keyboard) {
			bindConsoleCmds.unbind(keyboard->code);
		}
	}
};

void ConsoleBindCmds::bind(SDL_Scancode code, LPCSTR N)
{
	_conCmd& c = m_bindConsoleCmds[code];
	c.cmd = N;
}

void ConsoleBindCmds::unbind(SDL_Scancode code)
{
	auto it = m_bindConsoleCmds.find(code);
	if (it == m_bindConsoleCmds.end())
		return;

	m_bindConsoleCmds.erase(it);
}

void ConsoleBindCmds::clear()
{
	m_bindConsoleCmds.clear();
}

bool ConsoleBindCmds::execute(SDL_Scancode code)
{
	auto it = m_bindConsoleCmds.find(code);
	if (it == m_bindConsoleCmds.end())
		return false;

	Console->Execute(it->second.cmd.c_str());
	return true;
}

void ConsoleBindCmds::save(IWriter* F)
{
	for(const auto m: m_bindConsoleCmds) {
		const auto* keyboard = get_keyboard_by_code(m.first);
		if (keyboard) {
			F->w_printf("bind_console %s %s\n", *m.second.cmd, keyboard->key_name);
		}
	}
}

void CCC_RegisterInput()
{
	initialize_bindings();
	CMD2(CCC_Bind, "bind", 0);
	CMD2(CCC_Bind, "bind_sec", 1);
	CMD2(CCC_UnBind, "unbind", 0);
	CMD2(CCC_UnBind, "unbind_sec", 1);
	CMD1(CCC_UnBindAll, "unbindall");
	CMD1(CCC_DefControls, "default_controls");
	CMD1(CCC_ListActions, "list_actions");

	CMD1(CCC_BindList, "bind_list");
	CMD1(CCC_BindConsoleCmd, "bind_console");
	CMD1(CCC_UnBindConsoleCmd, "unbind_console");
};
