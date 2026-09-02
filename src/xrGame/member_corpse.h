////////////////////////////////////////////////////////////////////////////
//	Module 		: member_corpse.h
//	Created 	: 24.05.2004
//  Modified 	: 14.01.2005
//	Author		: Dmitriy Iassenev
//	Description : Member corpse class
////////////////////////////////////////////////////////////////////////////

#pragma once

class CAI_Stalker;

class CMemberCorpse
{
private:
	CAI_Stalker* m_corpse;
	CAI_Stalker* m_reactor;
	u32 m_time;

public:
	inline CMemberCorpse(CAI_Stalker* corpse, CAI_Stalker* reactor, u32 time);
	inline bool operator==(CAI_Stalker* corpse) const;
	inline void reactor(CAI_Stalker* reactor);

public:
	inline CAI_Stalker* corpse() const;
	inline CAI_Stalker* reactor() const;
	inline u32 time() const;
};

#include "member_corpse_inline.h"
