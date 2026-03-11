#pragma once

#include "../state.h"

template <typename _Object>
class CStateMonsterControlledFollow : public CState<_Object>
{
	typedef CState<_Object> inherited;
	typedef CState<_Object>* state_ptr;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

public:
	CStateMonsterControlledFollow(_Object* obj);
	virtual void reselect_state();
	virtual void setup_substates();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "monster_state_controlled_follow_inline.h"
