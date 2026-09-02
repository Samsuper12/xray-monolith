////////////////////////////////////////////////////////////////////////////
//	Module 		: agent_manager_inline.h
//	Created 	: 24.05.2004
//  Modified 	: 24.05.2004
//	Author		: Dmitriy Iassenev
//	Description : Agent manager inline functions
////////////////////////////////////////////////////////////////////////////

#pragma once

inline shared_str CAgentManager::cName() const
{
	return ("agent_manager");
}

inline CAgentCorpseManager& CAgentManager::corpse() const
{
	VERIFY(m_corpse);
	return (*m_corpse);
}

inline CAgentEnemyManager& CAgentManager::enemy() const
{
	VERIFY(m_enemy);
	return (*m_enemy);
}

inline CAgentExplosiveManager& CAgentManager::explosive() const
{
	VERIFY(m_explosive);
	return (*m_explosive);
}

inline CAgentLocationManager& CAgentManager::location() const
{
	VERIFY(m_location);
	return (*m_location);
}

inline CAgentMemberManager& CAgentManager::member() const
{
	VERIFY(m_member);
	return (*m_member);
}

inline CAgentMemoryManager& CAgentManager::memory() const
{
	VERIFY(m_memory);
	return (*m_memory);
}

inline CAgentManagerPlanner& CAgentManager::brain() const
{
	VERIFY(m_brain);
	return (*m_brain);
}
