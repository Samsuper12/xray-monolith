#include "pch_script.h"
#include <dinput.h>
#include "key_binding_registrator.h"
#include "xr_level_controller.h"
#include "xr_sdl3_input.hpp"

using namespace luabind;

int _dik_to_bind(int dik)
{
	return get_binded_action(dik);
}

BOOL _key_state(int key)
{
	return pSDL3Input->iGetAsyncKeyState(static_cast<SDL_Scancode>(key));
}

const char* _dik_to_keyname(int dik) {
	auto keyboard = get_keyboard_by_code(static_cast<SDL_Scancode>(dik));
	return keyboard ? keyboard->key_name : "";
}

int _get_action_dik(EGameActions _action_id, int idx)
{
	auto binding = get_binding_by_action_id(_action_id);
	if (!binding) 
		return 0;

	if (idx == -1)
	{
		if (binding->keyboard[0])
		return static_cast<int>(binding->keyboard[0]->code);

		if (binding->keyboard[1])
		return static_cast<int>(binding->keyboard[1]->code);
	}
	else
	{
		if (binding->keyboard[idx])
		return static_cast<int>(binding->keyboard[idx]->code);
	}
	return 0;
}

#pragma optimize("s",on)
void key_binding_registrator::script_register(lua_State* L)
{
	module(L)
	[
		// TODO: create new funcs for SDL_Scancode
		def("dik_to_keyname", &_dik_to_keyname),
		def("dik_to_bind", &_dik_to_bind),
		def("bind_to_dik", &_get_action_dik),
		def("key_state", &_key_state),

		class_<enum_exporter<EGameActions>>("key_bindings")
		.enum_("commands")
		[
			value("kLEFT", int(kLEFT)),
			value("kRIGHT", int(kRIGHT)),
			value("kUP", int(kUP)),
			value("kDOWN", int(kDOWN)),
			value("kJUMP", int(kJUMP)),
			value("kCROUCH", int(kCROUCH)),
			value("kACCEL", int(kACCEL)),
			value("kSPRINT_TOGGLE", int(kSPRINT_TOGGLE)),
			value("kFWD", int(kFWD)),
			value("kBACK", int(kBACK)),
			value("kL_STRAFE", int(kL_STRAFE)),
			value("kR_STRAFE", int(kR_STRAFE)),
			value("kL_LOOKOUT", int(kL_LOOKOUT)),
			value("kR_LOOKOUT", int(kR_LOOKOUT)),
			value("kCAM_1", int(kCAM_1)),
			value("kCAM_2", int(kCAM_2)),
			value("kCAM_3", int(kCAM_3)),
			value("kCAM_ZOOM_IN", int(kCAM_ZOOM_IN)),
			value("kCAM_ZOOM_OUT", int(kCAM_ZOOM_OUT)),
			value("kTORCH", int(kTORCH)),
			value("kNIGHT_VISION", int(kNIGHT_VISION)),
			value("kDETECTOR", int(kDETECTOR)),
			value("kWPN_1", int(kWPN_1)),
			value("kWPN_2", int(kWPN_2)),
			value("kWPN_3", int(kWPN_3)),
			value("kWPN_4", int(kWPN_4)),
			value("kWPN_5", int(kWPN_5)),
			value("kWPN_6", int(kWPN_6)),
			value("kARTEFACT", int(kARTEFACT)),
			value("kWPN_NEXT", int(kWPN_NEXT)),
			value("kWPN_FIRE", int(kWPN_FIRE)),
			value("kWPN_ZOOM", int(kWPN_ZOOM)),
			value("kWPN_ZOOM_INC", int(kWPN_ZOOM_INC)),
			value("kWPN_ZOOM_DEC", int(kWPN_ZOOM_DEC)),
			value("kWPN_RELOAD", int(kWPN_RELOAD)),
			value("kWPN_FUNC", int(kWPN_FUNC)),
			value("kWPN_FIREMODE_PREV", int(kWPN_FIREMODE_PREV)),
			value("kWPN_FIREMODE_NEXT", int(kWPN_FIREMODE_NEXT)),
			value("kPAUSE", int(kPAUSE)),
			value("kDROP", int(kDROP)),
			value("kUSE", int(kUSE)),
			value("kSCORES", int(kSCORES)),
			value("kCHAT", int(kCHAT)),
			value("kCHAT_TEAM", int(kCHAT_TEAM)),
			value("kSCREENSHOT", int(kSCREENSHOT)),
			value("kQUIT", int(kQUIT)),
			value("kCONSOLE", int(kCONSOLE)),
			value("kINVENTORY", int(kINVENTORY)),
			value("kBUY", int(kBUY)),
			value("kSKIN", int(kSKIN)),
			value("kTEAM", int(kTEAM)),
			value("kACTIVE_JOBS", int(kACTIVE_JOBS)),
			value("kVOTE_BEGIN", int(kVOTE_BEGIN)),
			value("kSHOW_ADMIN_MENU", int(kSHOW_ADMIN_MENU)),
			value("kVOTE", int(kVOTE)),
			value("kVOTEYES", int(kVOTEYES)),
			value("kVOTENO", int(kVOTENO)),
			value("kNEXT_SLOT", int(kNEXT_SLOT)),
			value("kPREV_SLOT", int(kPREV_SLOT)),
			value("kSPEECH_MENU_0", int(kSPEECH_MENU_0)),
			value("kSPEECH_MENU_1", int(kSPEECH_MENU_1)),
			value("kQUICK_USE_1", int(kQUICK_USE_1)),
			value("kQUICK_USE_2", int(kQUICK_USE_2)),
			value("kQUICK_USE_3", int(kQUICK_USE_3)),
			value("kQUICK_USE_4", int(kQUICK_USE_4)),
			value("kQUICK_SAVE", int(kQUICK_SAVE)),
			value("kQUICK_LOAD", int(kQUICK_LOAD)),
			value("kCUSTOM1", int(kCUSTOM1)),
			value("kCUSTOM2", int(kCUSTOM2)),
			value("kCUSTOM3", int(kCUSTOM3)),
			value("kCUSTOM4", int(kCUSTOM4)),
			value("kCUSTOM5", int(kCUSTOM5)),
			value("kCUSTOM6", int(kCUSTOM6)),
			value("kCUSTOM7", int(kCUSTOM7)),
			value("kCUSTOM8", int(kCUSTOM8)),
			value("kCUSTOM9", int(kCUSTOM9)),
			value("kCUSTOM10", int(kCUSTOM10)),
			value("kCUSTOM11", int(kCUSTOM11)),
			value("kCUSTOM12", int(kCUSTOM12)),
			value("kCUSTOM13", int(kCUSTOM13)),
			value("kCUSTOM14", int(kCUSTOM14)),
			value("kCUSTOM15", int(kCUSTOM15)),
			value("kCUSTOM16", int(kCUSTOM16)),
			value("kCUSTOM17", int(kCUSTOM17)),
			value("kCUSTOM18", int(kCUSTOM18)),
			value("kCUSTOM19", int(kCUSTOM19)),
			value("kCUSTOM20", int(kCUSTOM20)),
			value("kCUSTOM21", int(kCUSTOM21)),
			value("kCUSTOM22", int(kCUSTOM22)),
			value("kCUSTOM23", int(kCUSTOM23)),
			value("kCUSTOM24", int(kCUSTOM24)),
			value("kCUSTOM25", int(kCUSTOM25)),
			value("kSAFEMODE", int(kSAFEMODE)),
			value("kFREELOOK", int(kFREELOOK)),
			value("kCAM_AUTOAIM", int(kCAM_AUTOAIM))
		],
		class_<key_binding_registrator>("DIK_keys")
		.enum_("dik_keys")
		[
			value("DIK_ESCAPE", int(SDL_SCANCODE_ESCAPE)),
			value("DIK_2", int(SDL_SCANCODE_2)),
			value("DIK_4", int(SDL_SCANCODE_4)),
			value("DIK_6", int(SDL_SCANCODE_6)),
			value("DIK_8", int(SDL_SCANCODE_8)),
			value("DIK_0", int(SDL_SCANCODE_0)),
			value("DIK_EQUALS", int(SDL_SCANCODE_EQUALS)),
			value("DIK_TAB", int(SDL_SCANCODE_TAB)),
			value("DIK_W", int(SDL_SCANCODE_W)),
			value("DIK_R", int(SDL_SCANCODE_R)),
			value("DIK_Y", int(SDL_SCANCODE_Y)),
			value("DIK_I", int(SDL_SCANCODE_I)),
			value("DIK_P", int(SDL_SCANCODE_P)),
			value("DIK_RBRACKET", int(SDL_SCANCODE_RIGHTBRACKET)),
			value("DIK_LCONTROL", int(SDL_SCANCODE_LCTRL)),
			value("DIK_S", int(SDL_SCANCODE_S)),
			value("DIK_F", int(SDL_SCANCODE_F)),
			value("DIK_H", int(SDL_SCANCODE_H)),
			value("DIK_K", int(SDL_SCANCODE_K)),
			value("DIK_SEMICOLON", int(SDL_SCANCODE_SEMICOLON)),
			value("DIK_GRAVE", int(SDL_SCANCODE_GRAVE)),
			value("DIK_BACKSLASH", int(SDL_SCANCODE_BACKSLASH)),
			value("DIK_X", int(SDL_SCANCODE_X)),
			value("DIK_V", int(SDL_SCANCODE_V)),
			value("DIK_N", int(SDL_SCANCODE_N)),
			value("DIK_COMMA", int(SDL_SCANCODE_COMMA)),
			value("DIK_SLASH", int(SDL_SCANCODE_SLASH)),
			value("DIK_MULTIPLY", int(SDL_SCANCODE_KP_MULTIPLY)),
			value("DIK_SPACE", int(SDL_SCANCODE_SPACE)),
			value("DIK_F1", int(SDL_SCANCODE_F1)),
			value("DIK_F3", int(SDL_SCANCODE_F3)),
			value("DIK_F5", int(SDL_SCANCODE_F5)),
			value("DIK_F7", int(SDL_SCANCODE_F7)),
			value("DIK_F9", int(SDL_SCANCODE_F9)),
			value("DIK_NUMLOCK", int(SDL_SCANCODE_NUMLOCKCLEAR)),
			value("DIK_NUMPAD7", int(SDL_SCANCODE_KP_7)),
			value("DIK_NUMPAD9", int(SDL_SCANCODE_KP_9)),
			value("DIK_NUMPAD4", int(SDL_SCANCODE_KP_4)),
			value("DIK_NUMPAD6", int(SDL_SCANCODE_KP_6)),
			value("DIK_NUMPAD1", int(SDL_SCANCODE_KP_1)),
			value("DIK_NUMPAD3", int(SDL_SCANCODE_KP_3)),
			value("DIK_DECIMAL", int(SDL_SCANCODE_DELETE)),
			value("DIK_F12", int(SDL_SCANCODE_F12)),
			value("DIK_F14", int(SDL_SCANCODE_F14)),
		//	value("DIK_KANA", int(SDL_SCANCODE_KANA)),
		//	value("DIK_NOCONVERT", int(DIK_NOCONVERT)),
			value("DIK_NUMPADEQUALS", int(DIK_NUMPADEQUALS)),
			// value("DIK_AT", int(DIK_AT)),
			// value("DIK_UNDERLINE", int(DIK_UNDERLINE)),
			value("DIK_STOP", int(DIK_STOP)),
			// value("DIK_UNLABELED", int(DIK_UNLABELED)),
			value("DIK_RCONTROL", int(SDL_SCANCODE_RCTRL)),
			value("DIK_DIVIDE", int(SDL_SCANCODE_KP_DIVIDE)),
			value("DIK_RMENU", int(SDL_SCANCODE_RGUI)),
			value("DIK_UP", int(SDL_SCANCODE_UP)),
			value("DIK_LEFT", int(SDL_SCANCODE_LEFT)),
			value("DIK_END", int(SDL_SCANCODE_END)),
			value("DIK_NEXT", int(SDL_SCANCODE_MEDIA_NEXT_TRACK)),
			value("DIK_DELETE", int(SDL_SCANCODE_DELETE)),
			value("DIK_RWIN", int(SDL_SCANCODE_RGUI)),
			value("DIK_PAUSE", int(SDL_SCANCODE_PAUSE)),
			value("DIK_1", int(SDL_SCANCODE_1)),
			value("DIK_3", int(SDL_SCANCODE_3)),
			value("DIK_5", int(SDL_SCANCODE_5)),
			value("DIK_7", int(SDL_SCANCODE_7)),
			value("DIK_9", int(SDL_SCANCODE_9)),
			value("DIK_MINUS", int(SDL_SCANCODE_MINUS)),
			value("DIK_BACK", int(SDL_SCANCODE_BACKSPACE)),
			value("DIK_Q", int(SDL_SCANCODE_Q)),
			value("DIK_E", int(SDL_SCANCODE_E)),
			value("DIK_T", int(SDL_SCANCODE_T)),
			value("DIK_U", int(SDL_SCANCODE_U)),
			value("DIK_O", int(SDL_SCANCODE_O)),
			value("DIK_LBRACKET", int(SDL_SCANCODE_LEFTBRACKET)),
			value("DIK_RETURN", int(SDL_SCANCODE_RETURN)),
			value("DIK_A", int(SDL_SCANCODE_A)),
			value("DIK_D", int(SDL_SCANCODE_D)),
			value("DIK_G", int(SDL_SCANCODE_G)),
			value("DIK_J", int(SDL_SCANCODE_J)),
			value("DIK_L", int(SDL_SCANCODE_L)),
			value("DIK_APOSTROPHE", int(SDL_SCANCODE_APOSTROPHE)),
			value("DIK_LSHIFT", int(SDL_SCANCODE_LSHIFT)),
			value("DIK_Z", int(SDL_SCANCODE_Z)),
			value("DIK_C", int(SDL_SCANCODE_C)),
			value("DIK_B", int(SDL_SCANCODE_B)),
			value("DIK_M", int(SDL_SCANCODE_M)),
			value("DIK_PERIOD", int(SDL_SCANCODE_PERIOD)),
			value("DIK_RSHIFT", int(SDL_SCANCODE_RSHIFT)),
			value("DIK_LMENU", int(SDL_SCANCODE_LGUI)),
			value("DIK_CAPITAL", int(SDL_SCANCODE_CAPSLOCK)),
			value("DIK_F2", int(SDL_SCANCODE_F2)),
			value("DIK_F4", int(SDL_SCANCODE_F4)),
			value("DIK_F6", int(SDL_SCANCODE_F6)),
			value("DIK_F8", int(SDL_SCANCODE_F8)),
			value("DIK_F10", int(SDL_SCANCODE_F10)),
			value("DIK_SCROLL", int(SDL_SCANCODE_SCROLLLOCK)),
			value("DIK_NUMPAD8", int(SDL_SCANCODE_KP_8)),
			value("DIK_SUBTRACT", int(SDL_SCANCODE_KP_MINUS)),
			value("DIK_NUMPAD5", int(SDL_SCANCODE_KP_5)),
			value("DIK_ADD", int(SDL_SCANCODE_KP_PLUS)),
			value("DIK_NUMPAD2", int(SDL_SCANCODE_KP_2)),
			value("DIK_NUMPAD0", int(SDL_SCANCODE_KP_0)),
			value("DIK_F11", int(SDL_SCANCODE_F11)),
			value("DIK_F13", int(SDL_SCANCODE_F13)),
			value("DIK_F15", int(SDL_SCANCODE_F15)),
			// value("DIK_CONVERT", int(SDL_SCANCODE_CONVERT)),
			// value("DIK_YEN", int(SDL_SCANCODE_YEN)),
			value("DIK_CIRCUMFLEX", int(SDL_SCANCODE_GRAVE)),
			// value("DIK_COLON", int(SDL_SCANCODE_COLON)),
			// value("DIK_KANJI", int(SDL_SCANCODE_KANJI)),
			// value("DIK_AX", int(SDL_SCANCODE_AX)),
			value("DIK_NUMPADENTER", int(SDL_SCANCODE_KP_ENTER)),
			value("DIK_NUMPADCOMMA", int(SDL_SCANCODE_KP_PERIOD)),
			value("DIK_SYSRQ", int(SDL_SCANCODE_SYSREQ)),
			value("DIK_HOME", int(SDL_SCANCODE_HOME)),
			value("DIK_PRIOR", int(SDL_SCANCODE_PRIOR)),
			value("DIK_RIGHT", int(SDL_SCANCODE_RIGHT)),
			value("DIK_DOWN", int(SDL_SCANCODE_DOWN)),
			value("DIK_INSERT", int(SDL_SCANCODE_INSERT)),
			value("DIK_LWIN", int(SDL_SCANCODE_LGUI)),
			value("DIK_APPS", int(SDL_SCANCODE_APPLICATION)),
			value("MOUSE_1", int(SDL_BUTTON_LEFT)),
			value("MOUSE_2", int(SDL_BUTTON_RIGHT)),
			value("MOUSE_3", int(SDL_BUTTON_MIDDLE)),
			// value("MOUSE_4", int(MOUSE_4)),
			// value("MOUSE_5", int(MOUSE_5)),
			// value("MOUSE_6", int(MOUSE_6)),
			// value("MOUSE_7", int(MOUSE_7)),
			// value("MOUSE_8", int(MOUSE_8)),
			value("DIK_RETURN", int(SDL_SCANCODE_RETURN)),
			value("DIK_NUMPADENTER", int(SDL_SCANCODE_KP_ENTER))

		]
	];
}
