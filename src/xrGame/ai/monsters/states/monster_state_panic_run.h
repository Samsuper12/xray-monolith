#pragma once

template <typename _Object>
class CStateMonsterPanicRun : public CState<_Object>
{
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

public:
	CStateMonsterPanicRun(_Object* obj) : inherited(obj)
	{
	}

	virtual ~CStateMonsterPanicRun()
	{
	}

	virtual void initialize();
	virtual void execute();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }

	virtual bool check_completion();
};

#include "monster_state_panic_run_inline.h"
