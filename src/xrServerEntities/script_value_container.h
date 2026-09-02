////////////////////////////////////////////////////////////////////////////
//	Module 		: script_value_container.h
//	Created 	: 16.07.2004
//  Modified 	: 16.07.2004
//	Author		: Dmitriy Iassenev
//	Description : Script value container
////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef XRSE_FACTORY_EXPORTS
	class CScriptValue;
#else
class CScriptValue
{
public:
	virtual ~CScriptValue()
	{
	}
};
#endif

class CScriptValueContainer
{
protected:
	xr_vector<CScriptValue*> m_values;

public:
	virtual ~CScriptValueContainer();
	inline void assign();
	inline void clear();
	inline void add(CScriptValue* value);
};
