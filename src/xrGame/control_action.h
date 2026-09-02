////////////////////////////////////////////////////////////////////////////
//	Module 		: animation_action.h
//	Created 	: 05.04.2004
//  Modified 	: 05.04.2004
//	Author		: Dmitriy Iassenev
//	Description : Control action
////////////////////////////////////////////////////////////////////////////

#pragma once

class CAI_Stalker;

class CControlAction
{
protected:
	CAI_Stalker* m_object;

public:
	inline CControlAction();
	inline void set_object(CAI_Stalker* object);
	inline bool applicable() const;
	inline bool completed() const;
	inline void initialize();
	inline void execute();
	inline void finalize();
	inline CAI_Stalker& object() const;
	inline void remove_links(CObject* object);
};

#include "control_action_inline.h"
