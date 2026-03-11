#pragma once
#include "../state.h"

template <typename _Object>
class CStateGroupEating : public CState<_Object>
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
	using inherited::get_state; 

	CEntityAlive* corpse;
	u32 time_last_eat;

public:
	CStateGroupEating(_Object* obj);
	virtual ~CStateGroupEating();

	virtual void initialize();
	virtual void execute();

	virtual bool check_start_conditions();
	virtual bool check_completion();
	virtual void remove_links(CObject* object);
};

#include "group_state_eat_eat_inline.h"
