////////////////////////////////////////////////////////////////////////////
//	Module 		: inventory_upgrade_inline.h
//	Created 	: 01.11.2007
//  Modified 	: 27.11.2007
//	Author		: Evgeniy Sokolov
//	Description : inventory upgrade class inline functions
////////////////////////////////////////////////////////////////////////////

#ifndef INVENTORY_UPGRADE_INLINE_H_INCLUDED
#define INVENTORY_UPGRADE_INLINE_H_INCLUDED

#include "inventory_upgrade_group.h"

namespace inventory
{
	namespace upgrade
	{
		inline LPCSTR Upgrade::section() const
		{
			return m_section.c_str();
		}

		inline shared_str const& Upgrade::parent_group_id() const
		{
			return m_parent_group->id();
		}

		inline Group const* Upgrade::parent_group() const
		{
			return m_parent_group;
		}

		inline LPCSTR Upgrade::icon_name() const
		{
			return m_icon.c_str();
		}

		inline LPCSTR Upgrade::name() const
		{
			return m_name.c_str();
		}

		inline LPCSTR Upgrade::description_text() const
		{
			return m_description.c_str();
		}

		inline bool Upgrade::get_highlight() const
		{
			return m_highlight;
		}

		inline shared_str const& Upgrade::get_property_name(u8 index) const
		{
			VERIFY(index<max_properties_count&&index>=0);
			return m_properties[index];
		}

		inline Ivector2 const& Upgrade::get_scheme_index() const
		{
			return m_scheme_index;
		}
	} // namespace upgrade
} // namespace inventory

#endif // INVENTORY_UPGRADE_INLINE_H_INCLUDED
