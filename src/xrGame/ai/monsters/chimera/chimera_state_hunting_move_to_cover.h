#pragma once
#include "../state.h"

template <typename _Object>
class CStateChimeraHuntingMoveToCover : public CState<_Object>
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
	CStateChimeraHuntingMoveToCover(_Object* obj);

	virtual void initialize();
	virtual void execute();
	virtual bool check_start_conditions();
	virtual bool check_completion();
};

#include "chimera_state_hunting_move_to_cover_inline.h"
