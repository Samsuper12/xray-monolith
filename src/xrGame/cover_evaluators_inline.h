////////////////////////////////////////////////////////////////////////////
//	Module 		: cover_evaluators_inline.h
//	Created 	: 24.04.2004
//  Modified 	: 24.04.2004
//	Author		: Dmitriy Iassenev
//	Description : Cover evaluators inline functions
////////////////////////////////////////////////////////////////////////////

#pragma once

//////////////////////////////////////////////////////////////////////////
// CCoverEvaluatorBase
//////////////////////////////////////////////////////////////////////////
inline const CCoverPoint* CCoverEvaluatorBase::selected() const
{
	return (m_selected);
}

inline smart_cover::loophole const* CCoverEvaluatorBase::loophole() const
{
	return (m_loophole);
}

inline void CCoverEvaluatorBase::set_inertia(u32 inertia_time)
{
	m_inertia_time = inertia_time;
}

inline void CCoverEvaluatorBase::setup()
{
	m_initialized = true;
}

inline void CCoverEvaluatorBase::initialize(const Fvector& start_position, bool fake_call)
{
	VERIFY(initialized());
	m_start_position = start_position;
	m_previous_selected = m_selected;
	m_selected = 0;
	m_best_value = 1000.f;
	m_loophole = 0;
	if (!fake_call)
		m_last_update = Device.dwTimeGlobal;
}

inline void CCoverEvaluatorBase::finalize()
{
	m_initialized = false;
	m_actuality = true;
}

inline bool CCoverEvaluatorBase::initialized() const
{
	return (m_initialized);
}

inline bool CCoverEvaluatorBase::accessible(const Fvector& position)
{
	return (m_object ? object().accessible(position) : true);
}

inline bool CCoverEvaluatorBase::use_smart_covers_only() const
{
	return (m_use_smart_covers_only);
}

inline void CCoverEvaluatorBase::use_smart_covers_only(bool value)
{
	m_use_smart_covers_only = value;
}

inline bool CCoverEvaluatorBase::can_use_smart_covers() const
{
	return (m_can_use_smart_covers);
}

inline void CCoverEvaluatorBase::can_use_smart_covers(bool value)
{
	m_can_use_smart_covers = value;
}

inline CRestrictedObject& CCoverEvaluatorBase::object() const
{
	VERIFY(m_object);
	return (*m_object);
}

inline bool CCoverEvaluatorBase::actual() const
{
	return (m_actuality);
}

inline void CCoverEvaluatorBase::invalidate()
{
	m_last_update = 0;
}

inline float CCoverEvaluatorBase::best_value() const
{
	return (m_best_value);
}

//////////////////////////////////////////////////////////////////////////
// CCoverEvaluatorCloseToEnemy
//////////////////////////////////////////////////////////////////////////

inline CCoverEvaluatorCloseToEnemy::CCoverEvaluatorCloseToEnemy(CRestrictedObject* object) : inherited(object)
{
	m_enemy_position.set(flt_max,flt_max,flt_max);
	m_deviation = flt_max;
	m_min_distance = flt_max;
	m_max_distance = flt_max;
	m_best_distance = flt_max;
	m_current_distance = flt_max;
}

inline void CCoverEvaluatorCloseToEnemy::initialize(const Fvector& start_position, bool fake_call)
{
	inherited::initialize(start_position, fake_call);
	m_current_distance = m_start_position.distance_to(m_enemy_position);
}

inline void CCoverEvaluatorCloseToEnemy::setup(const Fvector& enemy_position, float min_enemy_distance,
                                           float max_enemy_distance, float deviation)
{
	inherited::setup();

	//	m_actuality				= m_actuality && m_enemy_position.similar(enemy_position,10.f);
	m_enemy_position = enemy_position;

	m_actuality = m_actuality && fsimilar(m_deviation, deviation);
	m_deviation = deviation;

	m_actuality = m_actuality && fsimilar(m_min_distance, min_enemy_distance);
	m_min_distance = min_enemy_distance;

	m_actuality = m_actuality && fsimilar(m_max_distance, max_enemy_distance);
	m_max_distance = max_enemy_distance;
}

//////////////////////////////////////////////////////////////////////////
// CCoverEvaluatorAngle
//////////////////////////////////////////////////////////////////////////

inline CCoverEvaluatorAngle::CCoverEvaluatorAngle(CRestrictedObject* object) : inherited(object)
{
	m_direction.set(flt_max,flt_max,flt_max);
	m_best_direction.set(flt_max,flt_max,flt_max);
	m_best_alpha = flt_max;;
	m_level_vertex_id = u32(-1);
}

inline void CCoverEvaluatorAngle::setup(const Fvector& enemy_position, float min_enemy_distance, float max_enemy_distance,
                                    u32 level_vertex_id)
{
	inherited::setup(enemy_position, min_enemy_distance, max_enemy_distance);
	m_actuality = m_actuality && (m_level_vertex_id == level_vertex_id);
	m_level_vertex_id = level_vertex_id;
}

//////////////////////////////////////////////////////////////////////////
// CCoverEvaluatorFarFromEnemy
//////////////////////////////////////////////////////////////////////////

inline CCoverEvaluatorFarFromEnemy::CCoverEvaluatorFarFromEnemy(CRestrictedObject* object) : inherited(object)
{
}

inline CCoverEvaluatorBest::CCoverEvaluatorBest(CRestrictedObject* object) : inherited(object)
{
}

//////////////////////////////////////////////////////////////////////////
// CCoverEvaluatorSafe
//////////////////////////////////////////////////////////////////////////

inline CCoverEvaluatorSafe::CCoverEvaluatorSafe(CRestrictedObject* object) : inherited(object)
{
	m_min_distance = flt_max;
}

inline void CCoverEvaluatorSafe::setup(float min_distance)
{
	inherited::setup();
	m_actuality = m_actuality && fsimilar(m_min_distance, min_distance);
	m_min_distance = min_distance;
}

//////////////////////////////////////////////////////////////////////////
// CCoverEvaluatorAmbush
//////////////////////////////////////////////////////////////////////////

inline CCoverEvaluatorAmbush::CCoverEvaluatorAmbush(CRestrictedObject* object) :
	inherited(object)
{
	m_my_position.set(flt_max,flt_max,flt_max);
	m_enemy_position.set(flt_max,flt_max,flt_max);
	m_min_enemy_distance = flt_max;;
}
