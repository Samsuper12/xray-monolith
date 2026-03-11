#pragma once

#include "../state.h"

template <typename _Object>
class CStateMonsterFindEnemyAngry : public CState<_Object>
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
	CStateMonsterFindEnemyAngry(_Object* obj);
	virtual ~CStateMonsterFindEnemyAngry();

	virtual void execute();
	virtual bool check_completion();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "monster_state_find_enemy_angry_inline.h"
