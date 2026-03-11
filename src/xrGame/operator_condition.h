////////////////////////////////////////////////////////////////////////////
//	Module 		: operator_condition.h
//	Created 	: 24.02.2004
//  Modified 	: 24.02.2004
//	Author		: Dmitriy Iassenev
//	Description : Operator condition
////////////////////////////////////////////////////////////////////////////

#pragma once

template <
	typename _condition_type1,
	typename _value_type1
>
class COperatorConditionAbstract
{
public:
	using _condition_type  = _condition_type1;
	using _value_type = _value_type1;

protected:
	typedef COperatorConditionAbstract<_condition_type, _value_type> COperatorCondition;

protected:
	_condition_type m_condition;
	u32 m_hash;
	_value_type m_value;

public:
	IC COperatorConditionAbstract(const _condition_type condition, const _value_type value);
	IC const _condition_type& condition() const;
	IC const _value_type& value() const;
	IC const u32& hash_value() const;
	IC bool operator<(const COperatorCondition& condition) const;
	IC bool operator==(const COperatorCondition& condition) const;
};

#include "operator_condition_inline.h"
