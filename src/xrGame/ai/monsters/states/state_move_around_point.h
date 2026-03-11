#pragma once

#include "../state.h"
#include "state_data.h"

template <typename _Object>
class CStateMonsterMoveAroundPoint : public CState<_Object>
{
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

	SStateDataMoveAroundPoint data;

public:
	CStateMonsterMoveAroundPoint(_Object* obj) : inherited(obj, &data)
	{
	}

	virtual ~CStateMonsterMoveAroundPoint()
	{
	}

	virtual void initialize();
	virtual void execute();

	virtual bool check_completion();
};

#include "state_move_to_point_inline.h"
