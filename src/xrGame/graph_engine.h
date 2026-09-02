////////////////////////////////////////////////////////////////////////////
//	Module 		: graph_engine.h
//	Created 	: 21.03.2002
//  Modified 	: 26.11.2003
//	Author		: Dmitriy Iassenev
//	Description : Graph engine
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "vertex_manager_fixed.h"
#include "vertex_manager_hash_fixed.h"
#include "a_star.h"
#include "edge_path.h"
#include "vertex_allocator_fixed.h"
#include "data_storage_bucket_list.h"
#include "data_storage_binary_heap.h"
#include "graph_engine_space.h"
#include "profiler.h"

#ifndef AI_COMPILER
#	include "operator_condition.h"
#	include "condition_state.h"
#	include "operator_abstract.h"
#endif // AI_COMPILER


template <
	typename _operator_condition,
	typename _condition_state,
	typename _operator,
	typename _condition_evaluator,
	typename _operator_id_type,
	bool _reverse_search,
	typename _operator_ptr1 ,
	typename _condition_evaluator_ptr1>
class CProblemSolver;

template <
	typename _path_id_type,
	typename _index_type1,
	unsigned long hash_size,
	unsigned long fix_size
>
struct CVertexManagerHashFixed;

template <
	typename _path_id_type1,
	typename _index_type1,
	unsigned char mask
>
struct CVertexManagerFixed;


namespace hash_fixed_vertex_manager
{
	inline u32 to_u32(GraphEngineSpace::CWorldState const& other)
	{
		return (other.hash_value());
	}
} // namespace hash_fixed_vertex_manager

using namespace GraphEngineSpace;

class CGraphEngine
{
public:
#ifndef AI_COMPILER
	typedef CDataStorageBinaryHeap CSolverPriorityQueue;
	typedef CDataStorageBinaryHeap CStringPriorityQueue;
#endif // AI_COMPILER
	typedef CDataStorageBucketList<u32, u32, 8 * 1024, false> CPriorityQueue;

	typedef CVertexManagerFixed<u32, u32, 8> CVertexManager;

#ifndef AI_COMPILER
	typedef CVertexManagerHashFixed<
		u32,
		_solver_index_type,
		256,
		8 * 1024
	> CSolverVertexManager;
	typedef CVertexManagerHashFixed<
		u32,
		shared_str,
		128,
		1024
	> CStringVertexManager;
#endif // AI_COMPILER
#ifdef AI_COMPILER
	typedef CVertexAllocatorFixed<2*1024*1024>				CVertexAllocator;
#else
	typedef CVertexAllocatorFixed<64 * 1024> CVertexAllocator;
	typedef CVertexAllocatorFixed<8 * 1024> CSolverVertexAllocator;
	typedef CVertexAllocatorFixed<1024> CStringVertexAllocator;
#endif // AI_COMPILER

	typedef CAStar<
		_dist_type,
		CPriorityQueue,
		CVertexManager,
		CVertexAllocator
	> CAlgorithm;

#ifndef AI_COMPILER
	typedef CAStar<
		_solver_dist_type,
		CSolverPriorityQueue,
		CSolverVertexManager,
		CSolverVertexAllocator,
		true,
		CEdgePath<
			_solver_edge_type,
			true
		>
	> CSolverAlgorithm;

	typedef CAStar<
		float,
		CStringPriorityQueue,
		CStringVertexManager,
		CStringVertexAllocator
	> CStringAlgorithm;
#endif // AI_COMPILER

	CAlgorithm* m_algorithm;

#ifndef AI_COMPILER
	CSolverAlgorithm* m_solver_algorithm;
	CStringAlgorithm* m_string_algorithm;
#endif // AI_COMPILER

public:

	inline CGraphEngine(u32 max_vertex_count);
	virtual ~CGraphEngine();
#ifndef AI_COMPILER
	inline const CSolverAlgorithm& solver_algorithm() const;
#endif // AI_COMPILER

	template <
		typename _Graph,
		typename _Parameters
	>
	inline bool search(
		const _Graph& graph,
		const shared_str& start_node,
		const shared_str& dest_node,
		xr_vector<shared_str>* node_path,
		_Parameters& parameters
	);

	template <
		typename _Graph,
		typename _Parameters
	>
	inline bool search(
		const _Graph& graph,
		const _index_type& start_node,
		const _index_type& dest_node,
		xr_vector<_index_type>* node_path,
		const _Parameters& parameters
	);

	template <
		typename _Graph,
		typename _Parameters
	>
	inline bool search(
		const _Graph& graph,
		const _index_type& start_node,
		const _index_type& dest_node,
		xr_vector<_index_type>* node_path,
		_Parameters& parameters
	);

	template <
		typename _Graph,
		typename _Parameters,
		typename _PathManager
	>
	inline bool search(
		const _Graph& graph,
		const _index_type& start_node,
		const _index_type& dest_node,
		xr_vector<_index_type>* node_path,
		const _Parameters& parameters,
		_PathManager& path_manager
	);

#ifndef AI_COMPILER
	template <
		typename T1,
		typename T2,
		typename T3,
		typename T4,
		typename T5,
		bool T6,
		typename T7,
		typename T8,
		typename _Parameters
	>
	inline bool search(
		const CProblemSolver<
			T1,
			T2,
			T3,
			T4,
			T5,
			T6,
			T7,
			T8
		>& graph,
		const _solver_index_type& start_node,
		const _solver_index_type& dest_node,
		xr_vector<_solver_edge_type>* node_path,
		const _Parameters& parameters
	);
#endif // AI_COMPILER
};

#include "path_manager.h"
#include "graph_engine_inline.h"
