#pragma once
#include "../state.h"

template <typename _Object>
class CStateChimeraHuntingComeOut : public CState<_Object>
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
	CStateChimeraHuntingComeOut(_Object* obj);

	virtual void reselect_state();
	virtual bool check_start_conditions();
	virtual bool check_completion();
};

#include "chimera_state_hunting_come_out_inline.h"
