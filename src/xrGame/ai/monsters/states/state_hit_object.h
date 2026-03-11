#pragma once
#include "../state.h"

template <typename _Object>
class CStateMonsterHitObject : public CState<_Object>
{
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 
	xr_vector<CObject*> m_nearest_objects;
	CPhysicsShellHolder* target;
	bool m_hitted;

public:
	CStateMonsterHitObject(_Object* obj) : inherited(obj)
	{
	}

	virtual void initialize();
	virtual void execute();
	virtual bool check_start_conditions();
	virtual bool check_completion();
};

#include "state_hit_object_inline.h"
