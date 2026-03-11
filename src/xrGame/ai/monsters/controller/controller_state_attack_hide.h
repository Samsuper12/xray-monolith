#pragma once

template <typename _Object>
class CStateControlHide : public CState<_Object>
{
	typedef CState<_Object> inherited;
	typedef CState<_Object>* state_ptr;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

	bool m_cover_reached;

	struct
	{
		Fvector position;
		u32 node;
	} target;

	u32 m_time_finished;

	bool m_state_fast_run;

public:

	CStateControlHide(_Object* obj) : inherited(obj)
	{
	}

	virtual ~CStateControlHide()
	{
	}

	virtual void initialize();
	virtual void execute();

	virtual void finalize();
	virtual void critical_finalize();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }

	virtual bool check_completion();
	virtual bool check_start_conditions();


private:
	void select_target_point();
};


#include "controller_state_attack_hide_inline.h"
