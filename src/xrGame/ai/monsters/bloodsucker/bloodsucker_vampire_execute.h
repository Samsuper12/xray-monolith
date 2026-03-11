#pragma once
#include "../state.h"

template <typename _Object>
class CStateBloodsuckerVampireExecute : public CState<_Object>
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

	u32 time_vampire_started;

	bool m_effector_activated;

public:
	CStateBloodsuckerVampireExecute(_Object* obj) : inherited(obj)
	{
	}

	virtual void initialize();
	virtual void execute();
	virtual void finalize();
	virtual void critical_finalize();
	virtual bool check_start_conditions();
	virtual bool check_completion();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }

private:
	void execute_vampire_prepare();
	void execute_vampire_continue();
	void execute_vampire_hit();

	void look_head();
	void show_hud();
	void cleanup();
};

#include "bloodsucker_vampire_execute_inline.h"
