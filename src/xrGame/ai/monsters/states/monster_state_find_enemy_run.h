#pragma once

#include "../state.h"

template <typename _Object>
class CStateMonsterFindEnemyRun : public CState<_Object>
{
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

	Fvector target_point;
	u32 target_vertex;

public:
	CStateMonsterFindEnemyRun(_Object* obj);
	virtual ~CStateMonsterFindEnemyRun();

	virtual void initialize();
	virtual void execute();
	virtual bool check_completion();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "monster_state_find_enemy_run_inline.h"
