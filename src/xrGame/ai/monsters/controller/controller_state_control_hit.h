#pragma once

template <typename _Object>
class CStateControlAttack : public CState<_Object>
{
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

	enum
	{
		eActionPrepare,
		eActionContinue,
		eActionFire,
		eActionWaitTripleEnd,
		eActionCompleted
	} m_action;

	u32 time_control_started;

public:

	CStateControlAttack(_Object* p);
	virtual ~CStateControlAttack();

	virtual void initialize();
	virtual void execute();
	virtual void finalize();
	virtual void critical_finalize();

	virtual bool check_completion();
	virtual bool check_start_conditions();

private:

	void execute_hit_fire();
	void execute_hit_continue();
	void execute_hit_prepare();
};

#include "controller_state_control_hit_inline.h"
