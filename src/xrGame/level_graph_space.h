////////////////////////////////////////////////////////////////////////////
//	Module 		: level_graph_space.h
//	Created 	: 02.10.2001
//  Modified 	: 08.12.2004
//	Author		: Dmitriy Iassenev
//	Description : Level graph space
////////////////////////////////////////////////////////////////////////////

#pragma once

namespace LevelGraph
{
	class CHeader : private hdrNODES
	{
	private:
		friend class CRenumbererConverter;

	public:
		inline u32 version() const;
		inline u32 vertex_count() const;
		inline float cell_size() const;
		inline float factor_y() const;
		inline const Fbox& box() const;
		inline const xrGUID& guid() const;
	};

	typedef NodePosition CPosition;

	class CVertex : public NodeCompressed
	{
	private:
		friend class CRenumbererConverter;

	public:
		inline u32 link(int i) const;
		inline u16 high_cover(u8 index) const;
		inline u16 low_cover(u8 index) const;
		inline u16 plane() const;
		inline const CPosition& position() const;
		inline bool operator<(const LevelGraph::CVertex& vertex) const;
		inline bool operator>(const LevelGraph::CVertex& vertex) const;
		inline bool operator==(const LevelGraph::CVertex& vertex) const;
		friend class CLevelGraph;
	};

	struct SSegment
	{
		Fvector v1;
		Fvector v2;
	};

	struct SContour : public SSegment
	{
		Fvector v3;
		Fvector v4;
	};
};
