#pragma once

inline CEntityCondition& CEntityAlive::conditions() const
{
	VERIFY(m_entity_condition);
	return (*m_entity_condition);
}

inline bool const& CEntityAlive::is_agresive() const
{
	return (m_is_agresive);
}

inline void CEntityAlive::is_agresive(bool const& value)
{
	m_is_agresive = value;
}

inline bool const& CEntityAlive::is_start_attack() const
{
	return (m_is_start_attack);
}

inline void CEntityAlive::is_start_attack(bool const& value)
{
	m_is_start_attack = value;
}
