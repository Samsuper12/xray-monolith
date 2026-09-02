////////////////////////////////////////////////////////////////////////////
//	Module 		: space_restrictor_inline.h
//	Created 	: 17.08.2004
//  Modified 	: 17.08.2004
//	Author		: Dmitriy Iassenev
//	Description : Space restrictor inline functions
////////////////////////////////////////////////////////////////////////////

#pragma once

inline CSpaceRestrictor::CSpaceRestrictor()
{
	m_space_restrictor_type = RestrictionSpace::eRestrictorTypeNone;
}

inline bool CSpaceRestrictor::actual() const
{
	return (m_actuality);
}

inline void CSpaceRestrictor::actual(bool value) const
{
	m_actuality = value;
}

inline RestrictionSpace::ERestrictorTypes CSpaceRestrictor::restrictor_type() const
{
	return RestrictionSpace::ERestrictorTypes(m_space_restrictor_type);
}
