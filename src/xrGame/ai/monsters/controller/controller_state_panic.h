#pragma once
#include "../state.h"

template <typename _Object>
class CStateControllerPanic : public CState<_Object>
{
protected:
	typedef CState<_Object> inherited;
	typedef CState<_Object>* state_ptr;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

	enum
	{
		eStateRun = u32(0),
		eStateSteal,
		eStateLookAround,
	};

public:
	CStateControllerPanic(_Object* obj);
	virtual ~CStateControllerPanic();

	virtual void reselect_state();
};

#include "controller_state_panic_inline.h"
