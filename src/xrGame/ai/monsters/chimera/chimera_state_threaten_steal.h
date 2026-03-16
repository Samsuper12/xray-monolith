#pragma once
#include "../state.h"

template <typename _Object>
class CStateChimeraThreatenSteal : public CStateMonsterMoveToPointEx<_Object>
{
	typedef CStateMonsterMoveToPointEx<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started;
	using inherited::data; 


public:
	IC CStateChimeraThreatenSteal(_Object* obj) : inherited(obj)
	{
	}

	virtual void initialize();
	virtual void finalize();
	virtual void execute();
	virtual bool check_completion();
	virtual bool check_start_conditions();
};

#include "chimera_state_threaten_steal_inline.h"
