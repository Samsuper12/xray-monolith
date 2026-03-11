#pragma once

template <typename _Object>
class CStateMonsterHittedHide : public CState<_Object>
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

	CStateMonsterHittedHide(_Object* obj) : inherited(obj)
	{
	}

	virtual ~CStateMonsterHittedHide()
	{
	}

	virtual void initialize();
	virtual void execute();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }

	virtual bool check_completion();
	virtual bool check_start_conditions();
};

#include "monster_state_hitted_hide_inline.h"
