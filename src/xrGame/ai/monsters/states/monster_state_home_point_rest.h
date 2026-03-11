#pragma once
#include "../state.h"

template <typename _Object>
class CStateMonsterRestMoveToHomePoint : public CStateMove<_Object>
{
protected:
	typedef CStateMove<_Object> inherited;
	typedef CStateMove<_Object>* state_ptr;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

	u32 m_target_node;

public:
	CStateMonsterRestMoveToHomePoint(_Object* obj) : inherited(obj), m_target_node(0)
	{
	}

	virtual void initialize();
	virtual void execute();
	virtual bool check_start_conditions();
	virtual bool check_completion();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "monster_state_home_point_rest_inline.h"
