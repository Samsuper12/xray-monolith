#pragma once

#include "../state.h"

template <typename _Object>
class CStateZombieAttackRun : public CState<_Object>
{
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started;

	TTime m_time_action_change;
	EAction action;

public:
	CStateZombieAttackRun(_Object* obj);
	virtual ~CStateZombieAttackRun();

	virtual void initialize();
	virtual void execute();

	virtual bool check_completion();
	virtual bool check_start_conditions();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }

private:
	void choose_action();
};

#include "zombie_state_attack_run_inline.h"
