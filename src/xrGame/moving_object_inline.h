////////////////////////////////////////////////////////////////////////////
//	Module 		: moving_objects_inline.h
//	Created 	: 28.03.2007
//  Modified 	: 28.03.2007
//	Author		: Dmitriy Iassenev
//	Description : moving object inline functions
////////////////////////////////////////////////////////////////////////////

#ifndef MOVING_OBJECT_INLINE_H
#define MOVING_OBJECT_INLINE_H

inline shared_str moving_object::id() const
{
	VERIFY(m_object);
	return (m_object->cName());
}

inline const Fvector& moving_object::position() const
{
	return (m_position);
}

inline float moving_object::radius() const
{
	return (m_object->Radius());
}

inline const CEntityAlive& moving_object::object() const
{
	VERIFY(m_object);
	return (*m_object);
}

inline void moving_object::action(const action_type& action)
{
	m_action_frame = Device.dwFrame;
	VERIFY((action == moving_object::action_move) || (action == moving_object::action_wait));
	if (action == m_action)
		return;

	m_action = action;
	m_action_position = Fvector().set(flt_max,flt_max,flt_max);
	m_action_time = Device.dwTimeGlobal;
#if 0//def DEBUG
	Msg					("%6d %s %s",Device.dwFrame,*object().cName(),action == moving_object::action_wait ? "wait" : "move");
#endif // DEBUG
}

inline void moving_object::action(const action_type& action, const Fvector& action_position)
{
	m_action_frame = Device.dwFrame;
	VERIFY((action == moving_object::action_move) || (action == moving_object::action_wait));
	if (action == m_action)
		return;

	m_action = action;
	m_action_position = action_position;
	m_action_time = Device.dwTimeGlobal;
#if 0//def DEBUG
	Msg					("%6d %s %s",Device.dwFrame,*object().cName(),action == moving_object::action_wait ? "wait" : "move");
#endif // DEBUG
}

inline const moving_object::action_type& moving_object::action() const
{
	return (m_action);
}

inline const Fvector& moving_object::action_position() const
{
	return (m_action_position);
}

inline const u32& moving_object::action_frame() const
{
	return (m_action_frame);
}

inline const u32& moving_object::action_time() const
{
	return (m_action_time);
}

inline obstacles_query& moving_object::static_query()
{
	return (m_static_query);
}

inline obstacles_query& moving_object::dynamic_query()
{
	return (m_dynamic_query);
}

#endif // MOVING_OBJECT_INLINE_H
