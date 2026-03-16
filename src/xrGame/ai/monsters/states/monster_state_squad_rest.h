#pragma once

#include "../state.h"

template <typename _Object>
class CStateMonsterSquadRest : public CState<_Object>
{
protected:
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started;

	typedef CState<_Object>* state_ptr;

	u32 time_next_state_reselect;

public:
	CStateMonsterSquadRest(_Object* obj);
	virtual ~CStateMonsterSquadRest();

	virtual void reselect_state();
	virtual void setup_substates();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "../ai_monster_squad.h"
#include "../ai_monster_squad_manager.h"
#include "monster_state_squad_rest_inline.h"
