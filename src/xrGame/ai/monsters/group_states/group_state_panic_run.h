#pragma once

template <typename _Object>
class CStateGroupPanicRun : public CState<_Object>
{
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started;
	using inherited::get_state;

public:
	CStateGroupPanicRun(_Object* obj) : inherited(obj)
	{
	}

	virtual ~CStateGroupPanicRun()
	{
	}

	virtual void initialize();
	virtual void execute();

	virtual bool check_completion();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "group_state_panic_run_inline.h"
