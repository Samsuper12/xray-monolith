////////////////////////////////////////////////////////////////////////////
//	Module 		: stalker_animation_pair_inline.h
//	Created 	: 25.02.2003
//  Modified 	: 19.11.2004
//	Author		: Dmitriy Iassenev
//	Description : Stalker animation pair inline functions
////////////////////////////////////////////////////////////////////////////

#pragma once

inline CStalkerAnimationPair::CStalkerAnimationPair(CAI_Stalker* object) :
	m_object(object),
	m_step_dependence(false),
	m_global_animation(false),
	m_callback_on_collision(false),
	m_target_matrix(0)
#ifdef DEBUG
	,m_object_name				("unassigned"),
	m_animation_type_name		("unassigned")
#endif
{
	reset();
}

inline bool CStalkerAnimationPair::actual() const
{
	return (m_actual);
}

inline bool CStalkerAnimationPair::animation(const MotionID& animation)
{
	VERIFY(animation.valid());
	bool result = (m_animation == animation);
	m_actual = m_actual && result;
	m_animation = animation;
	return (result);
}

inline const MotionID& CStalkerAnimationPair::animation() const
{
	return (m_animation);
}

inline CBlend* const& CStalkerAnimationPair::blend() const
{
	return (m_blend);
}

inline void CStalkerAnimationPair::step_dependence(bool value)
{
	m_step_dependence = value;
}

inline bool CStalkerAnimationPair::step_dependence() const
{
	return (m_step_dependence);
}

#ifdef DEBUG
inline	void CStalkerAnimationPair::set_dbg_info		(LPCSTR object_name, LPCSTR animation_type_name)
{
	m_object_name				= object_name;
	m_animation_type_name		= animation_type_name;
}
#endif

inline void CStalkerAnimationPair::global_animation(bool global_animation)
{
	m_global_animation = global_animation;
}

inline bool CStalkerAnimationPair::global_animation() const
{
	return (m_global_animation);
}

inline void CStalkerAnimationPair::make_inactual()
{
	m_actual = false;
}

inline const CStalkerAnimationPair::CALLBACK_ID* CStalkerAnimationPair::callback(const CALLBACK_ID& callback) const
{
	CALLBACKS::const_iterator I = std::find(m_callbacks.begin(), m_callbacks.end(), callback);
	if (I != m_callbacks.end())
		return (&*I);

	return (0);
}

inline void CStalkerAnimationPair::add_callback(const CALLBACK_ID& callback)
{
	VERIFY(std::find(m_callbacks.begin(),m_callbacks.end(),callback) == m_callbacks.end());
	m_callbacks.push_back(callback);
}

inline void CStalkerAnimationPair::remove_callback(const CALLBACK_ID& callback)
{
	CALLBACKS::iterator I = std::find(m_callbacks.begin(), m_callbacks.end(), callback);
	VERIFY(I != m_callbacks.end());
	m_callbacks.erase(I);
}

inline bool CStalkerAnimationPair::need_update() const
{
	return (!m_callbacks.empty());
}

inline void CStalkerAnimationPair::callback_on_collision(bool const& value)
{
	m_callback_on_collision = value;
}

inline bool CStalkerAnimationPair::callback_on_collision() const
{
	return (m_callback_on_collision);
}

inline void CStalkerAnimationPair::target_matrix()
{
	m_target_matrix = 0;
}

inline void CStalkerAnimationPair::target_matrix(Fmatrix const& matrix)
{
	m_target_matrix_impl = matrix;
	m_target_matrix = &m_target_matrix_impl;
}
