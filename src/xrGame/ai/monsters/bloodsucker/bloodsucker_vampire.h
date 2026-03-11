#pragma once
#include "../state.h"
#include "../../../../xrServerEntities/clsid_game.h"

template <typename _Object>
class CStateBloodsuckerVampire : public CState<_Object>
{
	typedef CState<_Object> inherited;
	typedef CState<_Object>* state_ptr;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 


	const CEntityAlive* enemy;

public:
	CStateBloodsuckerVampire(_Object* obj);

	virtual void reinit();

	virtual void initialize();
	virtual void reselect_state();
	virtual void finalize();
	virtual void critical_finalize();
	virtual bool check_start_conditions();
	virtual bool check_completion();
	virtual void remove_links(CObject* object);

	virtual void setup_substates();
	virtual void check_force_state();
};

#include "bloodsucker_vampire_inline.h"
