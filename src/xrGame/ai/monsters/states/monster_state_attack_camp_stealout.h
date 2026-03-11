#pragma once


template <typename _Object>
class CStateMonsterAttackCampStealOut : public CStateMove<_Object>
{
	typedef CStateMove<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

public:
	CStateMonsterAttackCampStealOut(_Object* obj);

	virtual void execute();
	virtual bool check_completion();
	virtual bool check_start_conditions();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "monster_state_attack_camp_stealout_inline.h"
