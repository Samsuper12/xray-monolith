////////////////////////////////////////////////////////////////////////////
//	Module 		: CEdge.h
//	Created 	: 14.01.2004
//  Modified 	: 19.02.2005
//	Author		: Dmitriy Iassenev
//	Description : Graph edge class template
////////////////////////////////////////////////////////////////////////////

#pragma once

#include <loki/EmptyType.h>

template <
	typename _edge_weight_type1,
	typename _vertex_type1
>
class CEdgeBase
{
public:
	using _edge_weight_type = _edge_weight_type1;
	using _vertex_type = _vertex_type1;
	typedef typename _vertex_type::_vertex_id_type _vertex_id_type;

private:
	_edge_weight_type m_weight;
	_vertex_type* m_vertex;

public:
	inline CEdgeBase(const _edge_weight_type& weight, _vertex_type* vertex);
	inline const _edge_weight_type& weight() const;
	inline _vertex_type* vertex() const;
	inline const _vertex_id_type& vertex_id() const;
};

template <
	typename _edge_weight_type,
	typename _vertex_type,
	typename _edge_data_type
>
class CEdge : public CEdgeBase<_edge_weight_type, _vertex_type>
{
private:
	typedef CEdgeBase<_edge_weight_type, _vertex_type> inherited;
	typedef typename _vertex_type::_vertex_id_type _vertex_id_type;

private:
	_edge_data_type m_data;

public:
	inline CEdge(const _edge_weight_type& weight, _vertex_type* vertex);
	inline bool operator==(const _vertex_id_type& vertex_id) const;
	inline bool operator==(const CEdge& obj) const;
	inline const _edge_data_type& data() const;
	inline _edge_data_type& data();
};

template <
	typename _edge_weight_type,
	typename _vertex_type
>
class CEdge<_edge_weight_type, _vertex_type, Loki::EmptyType> : public CEdgeBase<_edge_weight_type, _vertex_type>
{
private:
	typedef CEdgeBase<_edge_weight_type, _vertex_type> inherited;
	typedef typename _vertex_type::_vertex_id_type _vertex_id_type;

public:
	inline CEdge(const _edge_weight_type& weight, _vertex_type* vertex);
	inline bool operator==(const _vertex_id_type& vertex_id) const;
	inline bool operator==(const CEdge& obj) const;
};

#include "graph_edge_inline.h"
