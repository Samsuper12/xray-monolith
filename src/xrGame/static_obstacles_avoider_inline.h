////////////////////////////////////////////////////////////////////////////
//	Module 		: static_obstacles_avoider_inline.h
//	Created 	: 16.05.2007
//  Modified 	: 16.05.2007
//	Author		: Dmitriy Iassenev
//	Description : static obstacles avoider inline functions
////////////////////////////////////////////////////////////////////////////

#pragma once

inline static_obstacles_avoider::static_obstacles_avoider() :
	m_need_path_to_rebuild(false)
{
#ifdef DEBUG
	m_movement_manager			= 0;
	m_failed_to_build_path		= 0;
#endif // DEBUG
}

inline void static_obstacles_avoider::construct(stalker_movement_manager_obstacles* movement_manager,
                                            const bool& failed_to_build_path)
{
	m_movement_manager = movement_manager;
	m_failed_to_build_path = &failed_to_build_path;
}

inline const stalker_movement_manager_obstacles& static_obstacles_avoider::movement_manager() const
{
	VERIFY(m_movement_manager);
	return (*m_movement_manager);
}

inline const bool& static_obstacles_avoider::need_path_to_rebuild() const
{
	return (m_need_path_to_rebuild);
}

inline obstacles_query& static_obstacles_avoider::active_query()
{
	return (m_active_query);
}

inline obstacles_query& static_obstacles_avoider::inactive_query()
{
	return (m_inactive_query);
}

inline obstacles_query& static_obstacles_avoider::current_iteration()
{
	return (m_current_iteration);
}

inline void static_obstacles_avoider::clear()
{
	m_last_iteration.clear();
	m_current_iteration.clear();
	m_inactive_query.clear();
	m_active_query.clear();
}
