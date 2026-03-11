#pragma once
#include "../state.h"

template <typename _Object>
class CStateControllerTube : public CState<_Object>
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
	CStateControllerTube(_Object* obj) : inherited(obj)
	{
	}

	virtual void execute();
	virtual bool check_start_conditions();
	virtual bool check_completion();
};

#include "controller_tube_inline.h"
