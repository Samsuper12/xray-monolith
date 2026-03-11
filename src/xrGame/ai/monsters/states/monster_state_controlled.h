#pragma once

#include "../state.h"

template <typename _Object>
class CStateMonsterControlled : public CState<_Object>
{
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

public:
	CStateMonsterControlled(_Object* obj);
	virtual void execute();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "monster_state_controlled_inline.h"
