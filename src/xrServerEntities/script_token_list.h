////////////////////////////////////////////////////////////////////////////
//	Module 		: script_token_list.h
//	Created 	: 21.05.2004
//  Modified 	: 21.05.2004
//	Author		: Dmitriy Iassenev
//	Description : Script token list class
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "script_export_space.h"

class CScriptTokenList
{
protected:
	typedef xr_vector<xr_token> TOKEN_LIST;
	typedef TOKEN_LIST::iterator iterator;
	typedef TOKEN_LIST::const_iterator const_iterator;

protected:
	struct CTokenPredicateName
	{
		LPCSTR m_name;

		inline CTokenPredicateName(LPCSTR name)
		{
			m_name = name;
		}

		inline bool operator()(const xr_token& token) const
		{
			return (token.name && !xr_strcmp(token.name, m_name));
		}
	};

	struct CTokenPredicateID
	{
		int m_id;

		inline CTokenPredicateID(int id)
		{
			m_id = id;
		}

		inline bool operator()(const xr_token& token) const
		{
			return (token.name && (token.id == m_id));
		}
	};

protected:
	TOKEN_LIST m_token_list;

protected:
	inline iterator token(LPCSTR name);
	inline iterator token(int id);

public:
	inline CScriptTokenList();
	~CScriptTokenList();
	inline void add(LPCSTR name, int id);
	inline void remove(LPCSTR name);
	inline void clear();
	inline int id(LPCSTR name);
	inline LPCSTR name(int id);
	inline const TOKEN_LIST& tokens() const;
	inline TOKEN_LIST& tokens();
DECLARE_SCRIPT_REGISTER_FUNCTION
};

add_to_type_list(CScriptTokenList)
#undef script_type_list
#define script_type_list save_type_list(CScriptTokenList)

#include "script_token_list_inline.h"
