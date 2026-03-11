#pragma once

#include "../state.h"

//#include "../../../EntityCondition.h"

template <typename _Object>
class CStateCaptureJumpBloodsucker : public CState<_Object>
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

public:
	CStateCaptureJumpBloodsucker(_Object* obj);
	virtual ~CStateCaptureJumpBloodsucker();

	virtual void execute();
	virtual void setup_substates();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "bloodsucker_state_capture_jump_inline.h"
