#pragma once

#include "../state.h"
#include "../../../ai_debug.h"

template <typename _Object>
class CStateMonsterRestSleep : public CState<_Object>
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
	CStateMonsterRestSleep(_Object* obj);
	virtual ~CStateMonsterRestSleep();

	virtual void initialize();
	virtual void execute();
	virtual void finalize();
	virtual void critical_finalize();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "monster_state_rest_sleep_inline.h"
