#pragma once
#include "../state.h"
#include "state_data.h"

template <typename _Object>
class CStateMonsterCustomActionLook : public CState<_Object>
{
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

	SStateDataActionLook data;

public:
	CStateMonsterCustomActionLook(_Object* obj);
	virtual ~CStateMonsterCustomActionLook();

	virtual void execute();
	virtual bool check_completion();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "state_custom_action_look_inline.h"
