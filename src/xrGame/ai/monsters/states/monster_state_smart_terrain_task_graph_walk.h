#pragma once
#include "../state.h"

template <typename _Object>
class CStateMonsterSmartTerrainTaskGraphWalk : public CStateMove<_Object>
{
	typedef CStateMove<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

	CALifeSmartTerrainTask* m_task;

public:
	CStateMonsterSmartTerrainTaskGraphWalk(_Object* obj) : inherited(obj)
	{
	}

	virtual void initialize();
	virtual void execute();
	virtual bool check_start_conditions();
	virtual bool check_completion();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "monster_state_smart_terrain_task_graph_walk_inline.h"
