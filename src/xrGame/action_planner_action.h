////////////////////////////////////////////////////////////////////////////
//	Module 		: action_planner_action.h
//	Created 	: 28.01.2004
//  Modified 	: 10.03.2004
//	Author		: Dmitriy Iassenev
//	Description : Action planner action
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "action_base.h"
#include "action_planner.h"
#include "script_export_space.h"

class CScriptGameObject;

template <typename _object_type>
class CActionPlannerAction :
	public CActionPlanner<_object_type>,
	public CActionBase<_object_type>
{
public:
	using inherited_planner = CActionPlanner<_object_type>;
	using inherited_action = CActionBase<_object_type>;
	using typename inherited_action::_condition_type;
	using typename inherited_action::_value_type;
	using typename inherited_planner::_world_operator;
	using typename inherited_action::_edge_value_type;
	using typename inherited_action::COperatorCondition;
	using inherited_action::effects;
	using inherited_planner::set_target_state;

#ifdef LOG_ACTION
public:
	virtual	void		set_use_log				(bool value);
	virtual void		show					(LPCSTR offset = "");
#endif

public:
	IC CActionPlannerAction(_object_type* object = 0, LPCSTR action_name = "");
	virtual ~CActionPlannerAction();
	virtual void setup(_object_type* object, CPropertyStorage* storage);
	virtual void initialize();
	virtual void execute();
	virtual void finalize();
	virtual bool completed() const;
	IC void add_condition(inherited_planner::_world_operator* action, inherited_planner::_condition_type condition_id, inherited_planner::_value_type condition_value);
	IC void add_effect(inherited_planner::_world_operator* action, inherited_planner::_condition_type condition_id, inherited_planner::_value_type condition_value);

	virtual void save(NET_Packet& packet)
	{
		inherited_planner::save(packet);
		inherited_action::save(packet);
	}

	virtual void load(IReader& packet)
	{
		inherited_planner::load(packet);
		inherited_action::load(packet);
	}

DECLARE_SCRIPT_REGISTER_FUNCTION
};

using CScriptActionPlannerAction = CActionPlannerAction<CScriptGameObject>;
add_to_type_list(CScriptActionPlannerAction)
#undef script_type_list
#define script_type_list save_type_list(CScriptActionPlannerAction)

#include "action_planner_action_inline.h"
