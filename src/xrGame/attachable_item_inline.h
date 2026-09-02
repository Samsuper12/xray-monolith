////////////////////////////////////////////////////////////////////////////
//	Module 		: attachable_item_inline.h
//	Created 	: 11.02.2004
//  Modified 	: 11.02.2004
//	Author		: Dmitriy Iassenev
//	Description : Attachable item inline functions
////////////////////////////////////////////////////////////////////////////

#pragma once

inline CAttachableItem::CAttachableItem()
{
	m_item = 0;
	m_offset.identity();
	m_bone_name = "";
	m_enabled = true;
	//	m_auto_attach		= true;
#ifdef DEBUG
	m_valid				= false;
#endif
}

inline shared_str CAttachableItem::bone_name() const
{
#ifdef DEBUG
	VERIFY(m_valid);
#endif
	return (m_bone_name);
}

inline const Fmatrix& CAttachableItem::offset() const
{
#ifdef DEBUG
	VERIFY(m_valid);
#endif
	return (m_offset);
}

inline u16 CAttachableItem::bone_id() const
{
#ifdef DEBUG
	VERIFY(m_valid);
#endif
	return (m_bone_id);
}

inline void CAttachableItem::set_bone_id(u16 bone_id)
{
#ifdef DEBUG
	VERIFY(m_valid);
#endif
	m_bone_id = bone_id;
}

inline bool CAttachableItem::enabled() const
{
	//	VERIFY				(m_valid);
	return (m_enabled);
}

inline CInventoryItem& CAttachableItem::item() const
{
	VERIFY(m_item);
	return (*m_item);
}
