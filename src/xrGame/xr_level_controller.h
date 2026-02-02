#pragma once
#include <optional>
#include <map>
#include <string_view>
enum EGameActions
{
	kLEFT,
	kRIGHT,
	kUP,
	kDOWN,
	kJUMP,
	kCROUCH,
	kACCEL,
	kSPRINT_TOGGLE,

	kFWD,
	kBACK,
	kL_STRAFE,
	kR_STRAFE,

	kL_LOOKOUT,
	kR_LOOKOUT,

	kCAM_1,
	kCAM_2,
	kCAM_3,
	kCAM_ZOOM_IN,
	kCAM_ZOOM_OUT,

	kTORCH,
	kNIGHT_VISION,
	kDETECTOR,
	kWPN_1,
	kWPN_2,
	kWPN_3,
	kWPN_4,
	kWPN_5,
	kWPN_6,
	kARTEFACT,
	kWPN_NEXT,
	kWPN_FIRE,
	kWPN_ZOOM,
	kWPN_ZOOM_INC,
	kWPN_ZOOM_DEC,
	kWPN_RELOAD,
	kWPN_FUNC,
	kWPN_FIREMODE_PREV,
	kWPN_FIREMODE_NEXT,

	kPAUSE,
	kDROP,
	kUSE,
	kSCORES,
	kCHAT,
	kCHAT_TEAM,
	kSCREENSHOT,
	kQUIT,
	kCONSOLE,
	kINVENTORY,
	kBUY,
	kSKIN,
	kTEAM,
	kACTIVE_JOBS,

	kVOTE_BEGIN,
	kSHOW_ADMIN_MENU,
	kVOTE,
	kVOTEYES,
	kVOTENO,

	kNEXT_SLOT,
	kPREV_SLOT,

	kSPEECH_MENU_0,
	kSPEECH_MENU_1,

	kQUICK_USE_1,
	kQUICK_USE_2,
	kQUICK_USE_3,
	kQUICK_USE_4,

	kQUICK_SAVE,
	kQUICK_LOAD,
	//	kALIFE_CMD,

	kCUSTOM1,
	kCUSTOM2,
	kCUSTOM3,
	kCUSTOM4,
	kCUSTOM5,
	kCUSTOM6,
	kCUSTOM7,
	kCUSTOM8,
	kCUSTOM9,
	kCUSTOM10,
	kCUSTOM11,
	kCUSTOM12,
	kCUSTOM13,
	kCUSTOM14,
	kCUSTOM15,
	kCUSTOM16,
	kCUSTOM17,
	kCUSTOM18,
	kCUSTOM19,
	kCUSTOM20,
	kCUSTOM21,
	kCUSTOM22,
	kCUSTOM23,
	kCUSTOM24,
	kCUSTOM25,
	kSAFEMODE,
	kFREELOOK,

	kCAM_AUTOAIM,
	kEDITOR,

	kLASTACTION,
	kNOTBINDED,
	kFORCEDWORD = u32(-1)
};

enum bind_type : uint32_t {
	primary = 0,
	secondary = 1,
	any,
};

struct _conCmd
{
	shared_str cmd;
};

struct _keyboard
{
	const char* key_name;
	SDL_Scancode code;
};

struct _action
{
	const char* action_name;
	EGameActions id;
};

struct _binding
{	
	_action action;
	_keyboard* keyboard[2];
};

class ConsoleBindCmds
{
public:
	std::map<SDL_Scancode, _conCmd> m_bindConsoleCmds;

	void bind(SDL_Scancode code, const char* N);
	void unbind(SDL_Scancode code);
	bool execute(SDL_Scancode code);
	void clear();
	void save(IWriter* F);
};

extern void CCC_RegisterInput();
extern ConsoleBindCmds bindConsoleCmds;

auto get_scancode_by_action_id(EGameActions _action_id, bind_type bind = bind_type::any) -> SDL_Scancode;

auto get_keyboard_by_name(const char* _name) -> _keyboard*;
auto get_keyboard_by_code(SDL_Scancode code) -> _keyboard*;

auto get_action_by_name(const char* _name) -> std::optional<_action>;
auto get_action_id_by_scancode(SDL_Scancode code) -> EGameActions;

auto get_binding_by_action_id_ref(EGameActions _action_id) -> std::optional<std::reference_wrapper<_binding>>;
auto get_binding_by_action_id(EGameActions _action_id) -> std::optional<_binding>;

auto is_binded_sdl(EGameActions action_id, SDL_Scancode code) -> bool;

auto GetActionAllBinding(const char* action) -> std::string;

// TODO:
// Compatibility:
inline auto get_binded_action(int dik) -> EGameActions{
	return get_action_id_by_scancode(static_cast<SDL_Scancode>(dik));
}
inline auto get_action_dik(EGameActions _action_id, int index = -1) -> SDL_Scancode {
	return get_scancode_by_action_id(_action_id, (index == -1) ? bind_type::any : static_cast<bind_type>(index));
}
inline auto is_binded(EGameActions action_id, int dik) -> bool {
	return is_binded_sdl(action_id, static_cast<SDL_Scancode>(dik));
}
inline auto dik_to_ptr(int dik, bool safe) -> _keyboard* {
	return get_keyboard_by_code(static_cast<SDL_Scancode>(dik));
}
inline EGameActions action_name_to_id(const char* _name) {
	auto action = get_action_by_name(_name);
	return action ? action.value().id : kNOTBINDED;
}
inline int keyname_to_dik(const char* name) {
	const auto* ret = get_keyboard_by_name(name);
	return static_cast<int>(ret ? ret->code : SDL_SCANCODE_UNKNOWN);
}

