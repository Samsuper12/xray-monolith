#pragma once
#include "../state.h"

template <typename _Object>
class CStateBloodsuckerVampireApproach : public CState<_Object>
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
	CStateBloodsuckerVampireApproach(_Object* obj);
	virtual ~CStateBloodsuckerVampireApproach();

	virtual void initialize();
	virtual void execute();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "bloodsucker_vampire_approach_inline.h"
