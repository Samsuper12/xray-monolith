//#include <dinput.h>
#include "../xrEngine/XR_IOConsole.h"
#include "entity_alive.h"
#include "game_sv_single.h"
#include "alife_simulator.h"
#include "alife_simulator_header.h"
#include "level_graph.h"
#include "../xrEngine/FDemoRecord.h"
#include "Level.h"
#include "xr_level_controller.h"
#include "game_cl_base.h"
#include "stalker_movement_manager_smart_cover.h"
#include "Inventory.h"
#include "xrServer.h"
#include "autosave_manager.h"

#include "Actor.h"
#include "HudItem.h"
#include "UIGameCustom.h"
#include "ui/UIDialogWnd.h"
#include "../xrEngine/xr_sdl3_input.hpp"
#include "saved_game_wrapper.h"
#include "ui/UIPdaWnd.h"

#include "DebugRender.h"

#include "../build_config_defines.h"

//Alundaio
#include "pch_script.h"
#include "script_engine.h"
using namespace luabind;
//-Alundaio

#ifdef DEBUG
#	include "ai/monsters/basemonster/base_monster.h"

// Lain: add
#   include "level_debug.h"
#endif

#ifdef DEBUG
extern void try_change_current_entity();
extern void restore_actor();
#endif

bool g_bDisableAllInput = false;
extern float g_fTimeFactor;

#define CURRENT_ENTITY()	(game?((GameID() == eGameIDSingle) ? CurrentEntity() : CurrentControlEntity()):NULL)

void CLevel::IR_OnMouseWheel(int direction)
{
	if (g_bDisableAllInput) return;

	/* avo: script callback */
#ifdef MOUSE_INPUT_CALLBACKS
    if (g_actor) {
        // demonized: add mouse wheel callback with consuming input
        ::luabind::functor<bool> funct;
        if (ai().script_engine().functor("_G.COnMouseWheel", funct))
        {
            if (!funct(direction))
            {
                return;
            }
        }
        //g_actor->callback(GameObject::eMouseWheel)(direction);
    }
#endif
	/* avo: end */

	if (CurrentGameUI()->IR_UIOnMouseWheel(direction)) return;
	if (Device.Paused()
#ifdef DEBUG
        && !psActorFlags.test(AF_NO_CLIP)
#endif //DEBUG
	)
		return;

	if (CURRENT_ENTITY())
	{
		IInputReceiver* IR = smart_cast<IInputReceiver*>(smart_cast<CGameObject*>(CURRENT_ENTITY()));
		if (IR) IR->IR_OnMouseWheel(direction);
	}
}

void CLevel::IR_OnMousePress(int btn)
{
	IR_OnKeyboardPress(btn);
}

void CLevel::IR_OnMouseRelease(int btn)
{
	IR_OnKeyboardRelease(btn);
}

void CLevel::IR_OnMouseHold(int btn)
{
	IR_OnKeyboardHold(btn);
}

void CLevel::IR_OnMouseMove(int dx, int dy)
{
    ::luabind::functor<bool> funct;
    if (ai().script_engine().functor("level_input.on_mouse_move", funct))
    {
        if (funct(dx, dy, g_bDisableAllInput))
            return;
    }

	if (g_bDisableAllInput) return;

#ifdef MOUSE_INPUT_CALLBACKS
/* avo: script callback */
    if (g_actor) g_actor->callback(GameObject::eMouseMove)(dx, dy);
    /* avo: end */
#endif // INPUT_CALLBACKS

	if (CurrentGameUI()->IR_UIOnMouseMove(dx, dy)) return;
	if (Device.Paused() && !IsDemoPlay()
#ifdef DEBUG
        && !psActorFlags.test(AF_NO_CLIP)
#endif //DEBUG
	)
		return;
	if (CURRENT_ENTITY())
	{
		IInputReceiver* IR = smart_cast<IInputReceiver*>(smart_cast<CGameObject*>(CURRENT_ENTITY()));
		if (IR) IR->IR_OnMouseMove(dx, dy);
	}

    POINT p;
    p.x = Device.dwWidth / 2;
    p.y = Device.dwHeight / 2;
    // FIXME: why? for what?
    //ClientToScreen(Device.m_hWnd, &p);
    //SetCursorPos(p.x, p.y);
}

// Обработка нажатия клавиш
extern bool g_block_pause;
extern bool g_block_all_except_movement;

// Lain: added TEMP!!!
#ifdef DEBUG
	extern float g_separate_factor;
	extern float g_separate_radius;
#endif

#include <luabind/functor.hpp>
#include "script_engine.h"
#include "ai_space.h"
#include "ui/UIActorMenu.h"

extern string_path g_last_saved_game;

void CLevel::IR_OnKeyboardPress(int key)
{
	if (Device.dwPrecacheFrame)
		return;

	bool b_ui_exist = (!!CurrentGameUI());

	EGameActions _curr = get_binded_action(static_cast<SDL_Scancode>(key));

    if (_curr == kEDITOR)
    {
        if (!Device.imgui_shown())
        {
            Device.imgui().Show();
            return;
        }

        if (!Device.imgui().is_input())
        {
            Device.imgui().EnableInput();
            return;
        }

        Device.imgui().Show(false);
        return;
    }

    ::luabind::functor<bool> funct;
    if (ai().script_engine().functor("level_input.on_key_press", funct))
    {
        if (funct(key, _curr, g_bDisableAllInput))
            return;
    }

	if (g_block_all_except_movement)
	{
		if (!(_curr < kCAM_1 || _curr == kWPN_FIRE || _curr == kPAUSE || _curr == kDROP || _curr == kSCREENSHOT || _curr == kQUIT || _curr == kCONSOLE || _curr == kQUICK_LOAD || _curr == kQUICK_SAVE))
			return;
	}

	/* avo: script callback */
#ifdef INPUT_CALLBACKS
	if (!g_bDisableAllInput && g_actor) g_actor->callback(GameObject::eKeyPress)(key);
#endif
	/* avo: end */

	if (_curr == kPAUSE)
	{
		if (!g_block_pause && (IsGameTypeSingle() || IsDemoPlay()))
		{
#ifdef DEBUG
            if(psActorFlags.test(AF_NO_CLIP))
                Device.Pause(!Device.Paused(), TRUE, TRUE, "li_pause_key_no_clip");
            else
#endif //DEBUG
			Device.Pause(!Device.Paused(), TRUE, TRUE, "li_pause_key");
		}
		return;
	}

	if (b_ui_exist && CurrentGameUI()->GetActorMenu().IsShown() && CurrentGameUI()->GetActorMenu().b_sort_hotkeys)
	{
		switch (key)
		{
		case SDL_SCANCODE_1:
		case SDL_SCANCODE_2:
		case SDL_SCANCODE_3:
		case SDL_SCANCODE_4:
		case SDL_SCANCODE_5:
		case SDL_SCANCODE_6:
		case SDL_SCANCODE_7:
		case SDL_SCANCODE_8:
		case SDL_SCANCODE_9:
		case SDL_SCANCODE_0:
		{
			u16 tab = u16(key - SDL_SCANCODE_1);
			if (CurrentGameUI()->GetActorMenu().m_sort_buttons.size() > tab && CurrentGameUI()->GetActorMenu().m_sort_buttons.at(tab)->IsEnabled())
				CurrentGameUI()->GetActorMenu().SelectInventoryTab(tab);
			return;
		}
		break;
		}
	}

    if (!g_bDisableAllInput)
    {
        CUIPdaWnd* pda = b_ui_exist ? &CurrentGameUI()->GetPdaMenu() : nullptr;
        if (pda && CurrentGameUI()->TopInputReceiver() == pda) // Fix PDA hotkey input for disabled state
            if (pda->IsShown() && !pda->IsEnabled() && pda->OnKeyboardAction(key, WINDOW_KEY_PRESSED)) return;
    }

	switch (_curr)
	{
	case kSCREENSHOT:
		Render->Screenshot();
		return;
		break;

	case kCONSOLE:
		Console->Show();
		return;
		break;

	case kQUIT:
		{
			if (b_ui_exist && CurrentGameUI()->TopInputReceiver())
			{
				if (CurrentGameUI()->IR_UIOnKeyboardPress(key)) return; //special case for mp and main_menu
				CurrentGameUI()->TopInputReceiver()->HideDialog();
			}
			else
			{
				Console->Execute("main_menu");
			}
			return;
		}
		break;
    default:
        break;
	};

	if (g_bDisableAllInput || !bReady || !b_ui_exist) return;

	if (b_ui_exist && CurrentGameUI()->IR_UIOnKeyboardPress(key)) return;

	if (Device.Paused() && !IsDemoPlay()
#ifdef DEBUG
        && !psActorFlags.test(AF_NO_CLIP)
#endif //DEBUG
	)
		return;

	if (game && game->OnKeyboardPress(get_binded_action(key))) return;

    /*
	if (_curr == kQUICK_SAVE && IsGameTypeSingle())
	{
		Console->Execute("save");
		return;
	}
	if (_curr == kQUICK_LOAD && IsGameTypeSingle())
	{
#ifdef DEBUG
        FS.get_path					("$game_config$")->m_Flags.set(FS_Path::flNeedRescan, TRUE);
        FS.get_path					("$game_scripts$")->m_Flags.set(FS_Path::flNeedRescan, TRUE);
        FS.rescan_pathes			();
#endif // DEBUG
		Console->Execute("load_last_save");
		return;
	}
    */

#ifndef MASTER_GOLD
    switch (key) {
    case SDL_SCANCODE_F7: {
                     if (GameID() != eGameIDSingle) return;
                     FS.get_path					("$game_config$")->m_Flags.set(FS_Path::flNeedRescan, TRUE);
                     FS.get_path					("$game_scripts$")->m_Flags.set(FS_Path::flNeedRescan, TRUE);
                     FS.rescan_pathes			();
                     NET_Packet					net_packet;
                     net_packet.w_begin			(M_RELOAD_GAME);
                     Send						(net_packet,net_flags(TRUE));
                     return;
    }
    case SDL_SCANCODE_DIVIDE: {
                         if (!Server)
                             break;

                         SetGameTimeFactor			(g_fTimeFactor);

#ifdef DEBUG
                         if(!m_bEnvPaused)
                             SetEnvironmentGameTimeFactor(GetEnvironmentGameTime(), g_fTimeFactor);
#else //DEBUG
                         SetEnvironmentGameTimeFactor(GetEnvironmentGameTime(), g_fTimeFactor);
#endif //DEBUG

                         break;
    }
    case SDL_SCANCODE_MULTIPLY: {
                           if (!Server)
                               break;

                           SetGameTimeFactor			(1000.f);
#ifdef DEBUG
                           if(!m_bEnvPaused)
                               SetEnvironmentGameTimeFactor(GetEnvironmentGameTime(), 1000.f);
#else //DEBUG
                           SetEnvironmentGameTimeFactor(GetEnvironmentGameTime(), 1000.f);
#endif //DEBUG

                           break;
    }
#ifdef DEBUG
    case SDL_SCANCODE_SUBTRACT:{
                          if (!Server)
                              break;
                          if(m_bEnvPaused)
                              SetEnvironmentGameTimeFactor(GetEnvironmentGameTime(), g_fTimeFactor);
                          else
                              SetEnvironmentGameTimeFactor(GetEnvironmentGameTime(), 0.00001f);

                          m_bEnvPaused = !m_bEnvPaused;
                          break;
    }
#endif //DEBUG
    case SDL_SCANCODE_KP_5:
    {
                        if (GameID()!=eGameIDSingle)
                        {
                            Msg("For this game type Demo Record is disabled.");
                            ///				return;
                        };
                        if(!pSDL3Input->iGetAsyncKeyState(SDL_SCANCODE_LSHIFT))
                        {
                            Console->Hide	();
                            Console->Execute("demo_record 1");
                        }
    }
        break;

#ifdef DEBUG

        // Lain: added TEMP!!!
    case SDL_SCANCODE_UP:
    {
                   g_separate_factor /= 0.9f;
                   break;
    }
    case SDL_SCANCODE_DOWN:
    {
                     g_separate_factor *= 0.9f;
                     if ( g_separate_factor < 0.1f )
                     {
                         g_separate_factor = 0.1f;
                     }
                     break;
    }
    case SDL_SCANCODE_LEFT:
    {
                     g_separate_radius *= 0.9f;
                     if ( g_separate_radius < 0 )
                     {
                         g_separate_radius = 0;
                     }
                     break;
    }
    case SDL_SCANCODE_RIGHT:
    {
                      g_separate_radius /= 0.9f;
                      break;
    }

    case SDL_SCANCODE_RETURN: {
                         bDebug	= !bDebug;
                         return;
    }
    case SDL_SCANCODE_BACKSPACE:
        if (GameID() == eGameIDSingle)
            DRender->NextSceneMode();
        //HW.Caps.SceneMode			= (HW.Caps.SceneMode+1)%3;
        return;

    case SDL_SCANCODE_F4: {
                     if (pSDL3Input->iGetAsyncKeyState(SDL_SCANCODE_LALT))
                         break;

                     if (pSDL3Input->iGetAsyncKeyState(SDL_SCANCODE_RALT))
                         break;

                     bool bOk = false;
                     u32 i=0, j, n=Objects.o_count();
                     if (pCurrentEntity)
                     for ( ; i<n; ++i)
                     if (Objects.o_get_by_iterator(i) == pCurrentEntity)
                         break;
                     if (i < n) {
                         j = i;
                         bOk = false;
                         for (++i; i <n; ++i) {
                             CEntityAlive* tpEntityAlive = smart_cast<CEntityAlive*>(Objects.o_get_by_iterator(i));
                             if (tpEntityAlive) {
                                 bOk = true;
                                 break;
                             }
                         }
                         if (!bOk)
                         for (i = 0; i <j; ++i) {
                             CEntityAlive* tpEntityAlive = smart_cast<CEntityAlive*>(Objects.o_get_by_iterator(i));
                             if (tpEntityAlive) {
                                 bOk = true;
                                 break;
                             }
                         }
                         if (bOk) {
                             CObject *tpObject = CurrentEntity();
                             CObject *__I = Objects.o_get_by_iterator(i);
                             CObject **I = &__I;

                             SetEntity(*I);
                             if (tpObject != *I)
                             {
                                 CActor* pActor = smart_cast<CActor*> (tpObject);
                                 if (pActor)
                                     pActor->inventory().Items_SetCurrentEntityHud(false);
                             }
                             if (tpObject)
                             {
                                 Engine.Sheduler.Unregister	(tpObject);
                                 Engine.Sheduler.Register	(tpObject, TRUE);
                             };
                             Engine.Sheduler.Unregister	(*I);
                             Engine.Sheduler.Register	(*I, TRUE);

                             CActor* pActor = smart_cast<CActor*> (*I);
                             if (pActor)
                             {
                                 pActor->inventory().Items_SetCurrentEntityHud(true);

                                 CHudItem* pHudItem = smart_cast<CHudItem*>(pActor->inventory().ActiveItem());
                                 if (pHudItem)
                                 {
									 pHudItem->OnStateSwitch(pHudItem->GetState(), pHudItem->GetState());
                                 }
                             }
                         }
                     }
                     return;
    }
        // Lain: added
    case SDL_SCANCODE_F5:
    {
                   if ( CBaseMonster* pBM = smart_cast<CBaseMonster*>(CurrentEntity()))
                   {
                       DBG().log_debug_info();
                   }
                   break;
    }

    case SDL_BUTTON_LEFT: {
                      if (GameID() != eGameIDSingle)
                          break;

                      if (pSDL3Input->iGetAsyncKeyState(SDL_SCANCODE_LALT)) {
                          if (smart_cast<CActor*>(CurrentEntity()))
                              try_change_current_entity	();
                          else
                              restore_actor				();
                          return;
                      }
                      break;
    }
        /**/
#endif
#ifdef DEBUG
    case SDL_SCANCODE_F9:{
                    //		if (!ai().get_alife())
	//			break;
                    //		const_cast<CALifeSimulatorHeader&>(ai().alife().header()).set_state(ALife::eZoneStateSurge);
                    break;
    }
        return;
        //	case DIK_F10:{
	//		ai().level_graph().set_dest_point();
	//		ai().level_graph().build_detail_path();
	//		if (!Objects.FindObjectByName("m_stalker_e0000") || !Objects.FindObjectByName("localhost/dima"))
	//			return;
	//		if (!m_bSynchronization) {
	//			m_bSynchronization	= true;
	//			ai().level_graph().set_start_point();
	//			m_bSynchronization	= false;
	//		}
	//		::luabind::functor<void>	functor;
	//		ai().script_engine().functor("alife_test.set_switch_online",functor);
	//		functor(0,false);
	//	}
	//		return;
	//	case DIK_F11:
	//		ai().level_graph().build_detail_path();
	//		if (!Objects.FindObjectByName("m_stalker_e0000") || !Objects.FindObjectByName("localhost/dima"))
	//			return;
	//		if (!m_bSynchronization) {
	//			m_bSynchronization	= true;
	//			ai().level_graph().set_dest_point();
	//			ai().level_graph().select_cover_point();
	//			m_bSynchronization	= false;
	//		}
	//		return;
#endif // DEBUG
    }
#endif // MASTER_GOLD

	if (bindConsoleCmds.execute(static_cast<SDL_Scancode>(key)))
		return;

	if (CURRENT_ENTITY())
	{
		IInputReceiver* IR = smart_cast<IInputReceiver*>(smart_cast<CGameObject*>(CURRENT_ENTITY()));
		if (IR) IR->IR_OnKeyboardPress(get_binded_action(key));
	}

#ifdef _DEBUG
    CObject *obj = Level().Objects.FindObjectByName("monster");
    if (obj) {
        CBaseMonster *monster = smart_cast<CBaseMonster *>(obj);
        if (monster)
            monster->debug_on_key(key);
    }
#endif
}

void CLevel::IR_OnKeyboardRelease(int key)
{
	if (!bReady) return;

    ::luabind::functor<bool> funct;
    if (ai().script_engine().functor("level_input.on_key_release", funct))
    {
        if (funct(key, get_binded_action(key), g_bDisableAllInput))
            return;
    }

    if (g_bDisableAllInput) return;

#ifdef INPUT_CALLBACKS
	/* avo: script callback */
	if (g_actor) g_actor->callback(GameObject::eKeyRelease)(key);
	/* avo: end */
#endif // INPUT_CALLBACKS

	if (CurrentGameUI() && CurrentGameUI()->IR_UIOnKeyboardRelease(key)) return;
	if (game && game->OnKeyboardRelease(get_binded_action(key))) return;
	if (Device.Paused()
#ifdef DEBUG
        && !psActorFlags.test(AF_NO_CLIP)
#endif //DEBUG
	)
		return;

	if (CURRENT_ENTITY())
	{
		IInputReceiver* IR = smart_cast<IInputReceiver*>(smart_cast<CGameObject*>(CURRENT_ENTITY()));
		if (IR) IR->IR_OnKeyboardRelease(get_binded_action(key));
	}
}

void CLevel::IR_OnKeyboardHold(int key)
{
    ::luabind::functor<bool> funct;
    if (ai().script_engine().functor("level_input.on_key_hold", funct))
    {
        if (funct(key, get_binded_action(key), g_bDisableAllInput))
            return;
    }

	if (g_bDisableAllInput) return;

#ifdef INPUT_CALLBACKS
	/* avo: script callback */
	if (g_actor) g_actor->callback(GameObject::eKeyHold)(key);
	/* avo: end */
#endif // INPUT_CALLBACKS


#ifdef DEBUG
    // Lain: added
    if ( key == SDL_SCANCODE_UP )
    {
        static u32 time = Device.dwTimeGlobal;
        if ( Device.dwTimeGlobal - time > 20 )
        {
            if ( CBaseMonster* pBM = smart_cast<CBaseMonster*>(CurrentEntity()) )
            {
                DBG().debug_info_up();
                time = Device.dwTimeGlobal;
            }
        }
    }
    else if ( key == SDL_SCANCODE_DOWN )
    {
        static u32 time = Device.dwTimeGlobal;
        if ( Device.dwTimeGlobal - time > 20 )
        {
            if ( CBaseMonster* pBM = smart_cast<CBaseMonster*>(CurrentEntity()) )
            {
                DBG().debug_info_down();
                time = Device.dwTimeGlobal;
            }
        }
    }

#endif // DEBUG

	if (CurrentGameUI() && CurrentGameUI()->IR_UIOnKeyboardHold(key)) return;
	if (Device.Paused() && !Level().IsDemoPlay()
#ifdef DEBUG
        && !psActorFlags.test(AF_NO_CLIP)
#endif //DEBUG
	)
		return;
	if (CURRENT_ENTITY())
	{
		IInputReceiver* IR = smart_cast<IInputReceiver*>(smart_cast<CGameObject*>(CURRENT_ENTITY()));
		if (IR) IR->IR_OnKeyboardHold(get_binded_action(key));
	}
}

void CLevel::IR_OnMouseStop(int /*axis**/, int /*value**/)
{
}

void CLevel::IR_OnActivate()
{
	if (!pSDL3Input) return;
	int i;
	for (i = 0; i < SDL3Input::count_kb_buttons; i++)
	{
		if (IR_GetKeyState(i))
		{
			EGameActions action = get_binded_action(i);
			switch (action)
			{
			case kFWD:
			case kBACK:
			case kL_STRAFE:
			case kR_STRAFE:
			case kLEFT:
			case kRIGHT:
			case kUP:
			case kDOWN:
			case kCROUCH:
			case kACCEL:
			case kL_LOOKOUT:
			case kR_LOOKOUT:
			case kWPN_FIRE:
				{
					IR_OnKeyboardPress(i);
				}
				break;
            default:
                break;
			};
		};
	}
}
