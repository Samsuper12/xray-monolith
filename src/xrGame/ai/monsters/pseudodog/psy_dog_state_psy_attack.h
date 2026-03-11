#pragma once

#include "../state.h"

template <typename _Object>
class CStatePsyDogPsyAttack : public CState<_Object>
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
	CStatePsyDogPsyAttack(_Object* obj);

	virtual ~CStatePsyDogPsyAttack()
	{
	}

	virtual void reselect_state();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "psy_dog_state_psy_attack_inline.h"
