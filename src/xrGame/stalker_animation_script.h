////////////////////////////////////////////////////////////////////////////
//	Module 		: stalker_animation_script.h
//	Created 	: 25.02.2003
//  Modified 	: 19.11.2004
//	Author		: Dmitriy Iassenev
//	Description : Stalker animation script
////////////////////////////////////////////////////////////////////////////

#pragma once

class CStalkerAnimationScript
{
private:
	Fmatrix m_transform;
	Fmatrix const* m_transform_ptr;
	MotionID m_animation;
	bool m_hand_usage;
	bool m_use_movement_controller;
	bool m_local_animation;

public:
	inline CStalkerAnimationScript(const MotionID& animation, bool hand_usage, bool use_movement_controller,
	                           Fmatrix const* transform = 0, bool local_animation = true);
	inline CStalkerAnimationScript(CStalkerAnimationScript const& object);
	inline const MotionID& animation() const;
	inline const bool& hand_usage() const;
	inline const bool& use_movement_controller() const;
	inline const bool& local_animation() const;
	inline Fmatrix const& transform(CObject const& object) const;
	inline bool has_transform() const;
};

#include "stalker_animation_script_inline.h"
