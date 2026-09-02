////////////////////////////////////////////////////////////////////////////
//	Module 		: stalker_sound_data_inline.h
//	Created 	: 02.02.2005
//  Modified 	: 02.02.2005
//	Author		: Dmitriy Iassenev
//	Description : Stalker sound data inline functions
////////////////////////////////////////////////////////////////////////////

#pragma once

inline CStalkerSoundData::CStalkerSoundData(CAI_Stalker* object)
{
	VERIFY(object);
	m_object = object;
}

inline CAI_Stalker& CStalkerSoundData::object() const
{
	VERIFY(m_object);
	return (*m_object);
}
