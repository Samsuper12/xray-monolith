////////////////////////////////////////////////////////////////////////////
//	Module 		: smart_cover_transition_animation_inline.hpp
//	Created 	: 20.12.2007
//	Author		: Alexander Dudin
//	Description : Animation transition class for smart_cover inline functions
////////////////////////////////////////////////////////////////////////////

#ifndef SMART_COVER_TRANSITION_ANIMATION_INLINE_HPP_INCLUDED
#define SMART_COVER_TRANSITION_ANIMATION_INLINE_HPP_INCLUDED

namespace smart_cover
{
	namespace transitions
	{
		inline bool animation_action::has_animation() const
		{
			return (m_animation_id != "");
		}

		inline Fvector const& animation_action::position() const
		{
			return (m_position);
		}

		inline shared_str const& animation_action::animation_id() const
		{
			return (m_animation_id);
		}

		inline MonsterSpace::EBodyState const& animation_action::body_state() const
		{
			return (m_body_state);
		}

		inline MonsterSpace::EMovementType const& animation_action::movement_type() const
		{
			return (m_movement_type);
		}
	} // namespace transitions
} // nmaespace smart_cover

#endif // SMART_COVER_TRANSITION_ANIMATION_INLINE_HPP_INCLUDED
