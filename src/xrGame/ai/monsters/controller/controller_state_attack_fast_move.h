#pragma once

#include "../state.h"

template <typename _Object>
class CStateControllerFastMove : public CState<_Object>
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
public:
	CStateControllerFastMove(_Object* obj) : inherited(obj)
	{
	}

	virtual void initialize();
	virtual void finalize();
	virtual void critical_finalize();

	virtual void execute();
};

#include "controller_state_attack_fast_move_inline.h"
