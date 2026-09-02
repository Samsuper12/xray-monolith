////////////////////////////////////////////////////////////////////////////
//	Module 		: ai_stalker_inline.h
//	Created 	: 25.02.2003
//  Modified 	: 25.02.2003
//	Author		: Dmitriy Iassenev
//	Description : AI Behaviour for monster "Stalker" (inline functions)
////////////////////////////////////////////////////////////////////////////

#pragma once

inline BOOL CAI_Stalker::UsedAI_Locations()
{
	return (TRUE);
}

inline CStalkerAnimationManager& CAI_Stalker::animation() const
{
	VERIFY(m_animation_manager);
	return (*m_animation_manager);
}

inline CStalkerPlanner& CAI_Stalker::brain() const
{
	VERIFY(m_brain);
	return (*m_brain);
}

inline CSightManager& CAI_Stalker::sight() const
{
	VERIFY(m_sight_manager);
	return (*m_sight_manager);
}

inline LPCSTR CAI_Stalker::Name() const
{
	return (CInventoryOwner::Name());
}

inline stalker_movement_manager_smart_cover& CAI_Stalker::movement() const
{
	VERIFY(m_movement_manager);
	return (*m_movement_manager);
}

inline bool CAI_Stalker::frame_check(u32& frame)
{
	if (Device.dwFrame == frame)
		return (false);

	frame = Device.dwFrame;
	return (true);
}

inline bool CAI_Stalker::group_behaviour() const
{
	return (m_group_behaviour);
}

inline CWeaponShotEffector& CAI_Stalker::weapon_shot_effector() const
{
	VERIFY(m_weapon_shot_effector);
	return (*m_weapon_shot_effector);
}

inline bool CAI_Stalker::wounded() const
{
	return (m_wounded);
}

inline const CAI_Stalker::CRITICAL_WOUND_WEIGHTS& CAI_Stalker::critical_wound_weights() const
{
	VERIFY(!m_critical_wound_weights.empty());
	return (m_critical_wound_weights);
}

inline const bool& CAI_Stalker::throw_enabled()
{
	if (!m_throw_actual)
		update_throw_params();

	return (m_throw_enabled);
}

inline const u32& CAI_Stalker::last_throw_time() const
{
	return (m_last_throw_time);
}

inline const bool& CAI_Stalker::can_throw_grenades() const
{
	return (m_can_throw_grenades);
}

inline void CAI_Stalker::can_throw_grenades(const bool& value)
{
	m_can_throw_grenades = value;
}

inline const u32& CAI_Stalker::throw_time_interval() const
{
	return (m_throw_time_interval);
}

inline void CAI_Stalker::throw_time_interval(const u32& value)
{
	m_throw_time_interval = value;
}

inline const Fvector& CAI_Stalker::throw_target() const
{
	return (m_throw_target_position);
}

inline void CAI_Stalker::sniper_update_rate(bool value)
{
	m_sniper_update_rate = value;
}

inline bool CAI_Stalker::sniper_update_rate() const
{
	return (m_sniper_update_rate);
}

inline void CAI_Stalker::hit_callback(HitCallback const& hit_callback)
{
	m_hit_callback = hit_callback;
}

inline CCoverPoint const* const& CAI_Stalker::current_best_cover() const
{
	return (m_best_cover);
}

inline void CAI_Stalker::sniper_fire_mode(bool value)
{
	m_sniper_fire_mode = value;
}

inline bool CAI_Stalker::sniper_fire_mode() const
{
	return (m_sniper_fire_mode);
}

inline void CAI_Stalker::take_items_enabled(bool value)
{
	m_take_items_enabled = value;
}

inline bool CAI_Stalker::take_items_enabled() const
{
	return (m_take_items_enabled);
}

inline void CAI_Stalker::death_sound_enabled(bool value)
{
	m_death_sound_enabled = value;
}

inline bool CAI_Stalker::death_sound_enabled() const
{
	return (m_death_sound_enabled);
}

inline u32 CAI_Stalker::pstl_min_queue_size_far() const
{
	return (m_pstl_min_queue_size_far);
}

inline u32 CAI_Stalker::pstl_max_queue_size_far() const
{
	return (m_pstl_max_queue_size_far);
}

inline u32 CAI_Stalker::pstl_min_queue_interval_far() const
{
	return (m_pstl_min_queue_interval_far);
}

inline u32 CAI_Stalker::pstl_max_queue_interval_far() const
{
	return (m_pstl_max_queue_interval_far);
}

inline u32 CAI_Stalker::pstl_min_queue_size_medium() const
{
	return (m_pstl_min_queue_size_medium);
}

inline u32 CAI_Stalker::pstl_max_queue_size_medium() const
{
	return (m_pstl_max_queue_size_medium);
}

inline u32 CAI_Stalker::pstl_min_queue_interval_medium() const
{
	return (m_pstl_min_queue_interval_medium);
}

inline u32 CAI_Stalker::pstl_max_queue_interval_medium() const
{
	return (m_pstl_max_queue_interval_medium);
}

inline u32 CAI_Stalker::pstl_min_queue_size_close() const
{
	return (m_pstl_min_queue_size_close);
}

inline u32 CAI_Stalker::pstl_max_queue_size_close() const
{
	return (m_pstl_max_queue_size_close);
}

inline u32 CAI_Stalker::pstl_min_queue_interval_close() const
{
	return (m_pstl_min_queue_interval_close);
}

inline u32 CAI_Stalker::pstl_max_queue_interval_close() const
{
	return (m_pstl_max_queue_interval_close);
}

inline u32 CAI_Stalker::shtg_min_queue_size_far() const
{
	return (m_shtg_min_queue_size_far);
}

inline u32 CAI_Stalker::shtg_max_queue_size_far() const
{
	return (m_shtg_max_queue_size_far);
}

inline u32 CAI_Stalker::shtg_min_queue_interval_far() const
{
	return (m_shtg_min_queue_interval_far);
}

inline u32 CAI_Stalker::shtg_max_queue_interval_far() const
{
	return (m_shtg_max_queue_interval_far);
}

inline u32 CAI_Stalker::shtg_min_queue_size_medium() const
{
	return (m_shtg_min_queue_size_medium);
}

inline u32 CAI_Stalker::shtg_max_queue_size_medium() const
{
	return (m_shtg_max_queue_size_medium);
}

inline u32 CAI_Stalker::shtg_min_queue_interval_medium() const
{
	return (m_shtg_min_queue_interval_medium);
}

inline u32 CAI_Stalker::shtg_max_queue_interval_medium() const
{
	return (m_shtg_max_queue_interval_medium);
}

inline u32 CAI_Stalker::shtg_min_queue_size_close() const
{
	return (m_shtg_min_queue_size_close);
}

inline u32 CAI_Stalker::shtg_max_queue_size_close() const
{
	return (m_shtg_max_queue_size_close);
}

inline u32 CAI_Stalker::shtg_min_queue_interval_close() const
{
	return (m_shtg_min_queue_interval_close);
}

inline u32 CAI_Stalker::shtg_max_queue_interval_close() const
{
	return (m_shtg_max_queue_interval_close);
}

inline u32 CAI_Stalker::snp_min_queue_size_far() const
{
	return (m_snp_min_queue_size_far);
}

inline u32 CAI_Stalker::snp_max_queue_size_far() const
{
	return (m_snp_max_queue_size_far);
}

inline u32 CAI_Stalker::snp_min_queue_interval_far() const
{
	return (m_snp_min_queue_interval_far);
}

inline u32 CAI_Stalker::snp_max_queue_interval_far() const
{
	return (m_snp_max_queue_interval_far);
}

inline u32 CAI_Stalker::snp_min_queue_size_medium() const
{
	return (m_snp_min_queue_size_medium);
}

inline u32 CAI_Stalker::snp_max_queue_size_medium() const
{
	return (m_snp_max_queue_size_medium);
}

inline u32 CAI_Stalker::snp_min_queue_interval_medium() const
{
	return (m_snp_min_queue_interval_medium);
}

inline u32 CAI_Stalker::snp_max_queue_interval_medium() const
{
	return (m_snp_max_queue_interval_medium);
}

inline u32 CAI_Stalker::snp_min_queue_size_close() const
{
	return (m_snp_min_queue_size_close);
}

inline u32 CAI_Stalker::snp_max_queue_size_close() const
{
	return (m_snp_max_queue_size_close);
}

inline u32 CAI_Stalker::snp_min_queue_interval_close() const
{
	return (m_snp_min_queue_interval_close);
}

inline u32 CAI_Stalker::snp_max_queue_interval_close() const
{
	return (m_snp_max_queue_interval_close);
}

inline u32 CAI_Stalker::mchg_min_queue_size_far() const
{
	return (m_mchg_min_queue_size_far);
}

inline u32 CAI_Stalker::mchg_max_queue_size_far() const
{
	return (m_mchg_max_queue_size_far);
}

inline u32 CAI_Stalker::mchg_min_queue_interval_far() const
{
	return (m_mchg_min_queue_interval_far);
}

inline u32 CAI_Stalker::mchg_max_queue_interval_far() const
{
	return (m_mchg_max_queue_interval_far);
}

inline u32 CAI_Stalker::mchg_min_queue_size_medium() const
{
	return (m_mchg_min_queue_size_medium);
}

inline u32 CAI_Stalker::mchg_max_queue_size_medium() const
{
	return (m_mchg_max_queue_size_medium);
}

inline u32 CAI_Stalker::mchg_min_queue_interval_medium() const
{
	return (m_mchg_min_queue_interval_medium);
}

inline u32 CAI_Stalker::mchg_max_queue_interval_medium() const
{
	return (m_mchg_max_queue_interval_medium);
}

inline u32 CAI_Stalker::mchg_min_queue_size_close() const
{
	return (m_mchg_min_queue_size_close);
}

inline u32 CAI_Stalker::mchg_max_queue_size_close() const
{
	return (m_mchg_max_queue_size_close);
}

inline u32 CAI_Stalker::mchg_min_queue_interval_close() const
{
	return (m_mchg_min_queue_interval_close);
}

inline u32 CAI_Stalker::mchg_max_queue_interval_close() const
{
	return (m_mchg_max_queue_interval_close);
}

inline u32 CAI_Stalker::auto_min_queue_size_far() const
{
	return (m_auto_min_queue_size_far);
}

inline u32 CAI_Stalker::auto_max_queue_size_far() const
{
	return (m_auto_max_queue_size_far);
}

inline u32 CAI_Stalker::auto_min_queue_interval_far() const
{
	return (m_auto_min_queue_interval_far);
}

inline u32 CAI_Stalker::auto_max_queue_interval_far() const
{
	return (m_auto_max_queue_interval_far);
}

inline u32 CAI_Stalker::auto_min_queue_size_medium() const
{
	return (m_auto_min_queue_size_medium);
}

inline u32 CAI_Stalker::auto_max_queue_size_medium() const
{
	return (m_auto_max_queue_size_medium);
}

inline u32 CAI_Stalker::auto_min_queue_interval_medium() const
{
	return (m_auto_min_queue_interval_medium);
}

inline u32 CAI_Stalker::auto_max_queue_interval_medium() const
{
	return (m_auto_max_queue_interval_medium);
}

inline u32 CAI_Stalker::auto_min_queue_size_close() const
{
	return (m_auto_min_queue_size_close);
}

inline u32 CAI_Stalker::auto_max_queue_size_close() const
{
	return (m_auto_max_queue_size_close);
}

inline u32 CAI_Stalker::auto_min_queue_interval_close() const
{
	return (m_auto_min_queue_interval_close);
}

inline u32 CAI_Stalker::auto_max_queue_interval_close() const
{
	return (m_auto_max_queue_interval_close);
}


//inline	float CAI_Stalker::pstl_queue_fire_dist_close						() const
//{
//	return					(m_pstl_queue_fire_dist_close);
//}
inline float CAI_Stalker::pstl_queue_fire_dist_med() const
{
	return (m_pstl_queue_fire_dist_med);
}

inline float CAI_Stalker::pstl_queue_fire_dist_far() const
{
	return (m_pstl_queue_fire_dist_far);
}

//inline	float CAI_Stalker::shtg_queue_fire_dist_close						() const
//{
//	return					(m_shtg_queue_fire_dist_close);
//}
inline float CAI_Stalker::shtg_queue_fire_dist_med() const
{
	return (m_shtg_queue_fire_dist_med);
}

inline float CAI_Stalker::shtg_queue_fire_dist_far() const
{
	return (m_shtg_queue_fire_dist_far);
}

//inline	float CAI_Stalker::snp_queue_fire_dist_close						() const
//{
//	return					(m_snp_queue_fire_dist_close);
//}
inline float CAI_Stalker::snp_queue_fire_dist_med() const
{
	return (m_snp_queue_fire_dist_med);
}

inline float CAI_Stalker::snp_queue_fire_dist_far() const
{
	return (m_snp_queue_fire_dist_far);
}

//inline	float CAI_Stalker::mchg_queue_fire_dist_close						() const
//{
//	return					(m_mchg_queue_fire_dist_close);
//}
inline float CAI_Stalker::mchg_queue_fire_dist_med() const
{
	return (m_mchg_queue_fire_dist_med);
}

inline float CAI_Stalker::mchg_queue_fire_dist_far() const
{
	return (m_mchg_queue_fire_dist_far);
}

//inline	float CAI_Stalker::auto_queue_fire_dist_close						() const
//{
//	return					(m_auto_queue_fire_dist_close);
//}
inline float CAI_Stalker::auto_queue_fire_dist_med() const
{
	return (m_auto_queue_fire_dist_med);
}

inline float CAI_Stalker::auto_queue_fire_dist_far() const
{
	return (m_auto_queue_fire_dist_far);
}
