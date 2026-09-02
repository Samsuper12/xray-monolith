////////////////////////////////////////////////////////////////////////////
//	Module 		: script_sound.h
//	Created 	: 06.02.2004
//  Modified 	: 06.02.2004
//	Author		: Dmitriy Iassenev
//	Description : XRay Script sound class
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <Sound.h>

#include "script_export_space.h"
#include "ai_sounds.h"

class CScriptGameObject;

class CScriptSound
{
	mutable ref_sound m_sound;
	shared_str m_caSoundToPlay;

	friend class CScriptSoundAction;
public:

	CScriptSound(LPCSTR caSoundName, ESoundTypes sound_type = SOUND_TYPE_NO_SOUND);
	virtual ~CScriptSound();
	inline u32 Length();
	inline void Play(CScriptGameObject* object);
	inline void Play(CScriptGameObject* object, float delay);
	void Play(CScriptGameObject* object, float delay, int flags);
	inline void PlayAtPos(CScriptGameObject* object, const Fvector& position);
	inline void PlayAtPos(CScriptGameObject* object, const Fvector& position, float delay);
	void PlayAtPos(CScriptGameObject* object, const Fvector& position, float delay, int flags);
	void PlayNoFeedback(CScriptGameObject* object, u32 flags/*!< Looping */, float delay/*!< Delay */, Fvector pos,
	                    float vol, float freq);
	inline void AttachTail(LPCSTR caSoundName);
	inline void Stop();
	inline void StopDeffered();
	inline void SetPosition(const Fvector& position);
	inline void SetFrequency(float frequency);
	inline void SetVolume(float volume);
	inline const CSound_params* GetParams();
	inline void SetParams(CSound_params* sound_params);
	void SetMinDistance(const float fMinDistance);
	inline void SetMaxDistance(const float fMaxDistance);
	Fvector GetPosition() const;
	inline const float GetFrequency() const;
	inline const float GetMinDistance() const;
	inline const float GetMaxDistance() const;
	inline const float GetVolume() const;
	inline bool IsPlaying() const;

DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CScriptSound)
#undef script_type_list
#define script_type_list save_type_list(CScriptSound)

#include "script_sound_inline.h"
