#pragma once
#include "../state.h"

template <typename _Object>
class CStateChimeraThreatenRoar : public CState<_Object>
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
	inline CStateChimeraThreatenRoar(_Object* obj) : inherited(obj)
	{
	}

	virtual void initialize();
	virtual void execute();
	virtual bool check_completion();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "chimera_state_threaten_roar_inline.h"
