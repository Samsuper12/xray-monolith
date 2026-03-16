#pragma once
#include "../state.h"

template <typename _Object>
class CStateMonsterLookActor : public CState<_Object>
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
	CStateMonsterLookActor(_Object* obj) : inherited(obj)
	{
	}

	virtual void execute();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};


template <typename _Object>
class CStateMonsterTurnAwayFromActor : public CState<_Object>
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
	CStateMonsterTurnAwayFromActor(_Object* obj) : inherited(obj)
	{
	}

	virtual void execute();
};


template <typename _Object>
class CStateMonstertTestIdle : public CState<_Object>
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
	CStateMonstertTestIdle(_Object* obj) : inherited(obj)
	{
	}

	virtual void execute();
};

#include "state_test_look_actor_inline.h"
