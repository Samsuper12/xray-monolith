#pragma once
#include "../state.h"

template <typename _Object>
class CStateMonsterTestState : public CState<_Object>
{
	typedef CState<_Object> inherited;
	typedef CState<_Object>* state_ptr;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started;

public:
	CStateMonsterTestState(_Object* obj);
	virtual void reselect_state();
	virtual void setup_substates();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

template <typename _Object>
class CStateMonsterTestCover : public CState<_Object>
{
	typedef CState<_Object> inherited;
	typedef CState<_Object>* state_ptr;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started;

	u32 m_last_node;

public:
	CStateMonsterTestCover(_Object* obj);
	virtual void initialize();
	virtual void check_force_state();
	virtual void reselect_state();
	virtual void setup_substates();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "state_test_state_inline.h"
