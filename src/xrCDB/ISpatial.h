#ifndef XRENGINE_ISPATIAL_H_INCLUDED
#define XRENGINE_ISPATIAL_H_INCLUDED
#pragma once

#include <FTimer.h>
#include <xrPool.h>

#include "xr_collide_defs.h"


// #pragma pack(push,4)

/*
Requirements:
0. Generic
	* O(1) insertion
		- radius completely determines	"level"
		- position completely detemines "node"
	* O(1) removal
	* 
1. Rendering
	* Should live inside spatial DB
	* Should have at least "bounding-sphere" or "bounding-box"
	* Should have pointer to "sector" it lives in
	* Approximate traversal order relative to point ("camera")
2. Spatial queries
	* Should live inside spatial DB
	* Should have at least "bounding-sphere" or "bounding-box"
*/

const float c_spatial_min = 8.f;

//////////////////////////////////////////////////////////////////////////
enum
{
	STYPE_RENDERABLE = (1 << 0),
	STYPE_LIGHTSOURCE = (1 << 1),
	STYPE_COLLIDEABLE = (1 << 2),
	STYPE_VISIBLEFORAI = (1 << 3),
	STYPE_REACTTOSOUND = (1 << 4),
	STYPE_PHYSIC = (1 << 5),
	STYPE_OBSTACLE = (1 << 6),
	STYPE_SHAPE = (1 << 7),
	STYPE_LIGHTSOURCEHEMI = (1 << 8),
#ifdef SPATIAL_CHANGE
	STYPE_FEELVISIONIGNORE = (1 << 9),
#endif

	STYPEFLAG_INVALIDSECTOR = (1 << 16)
};

//////////////////////////////////////////////////////////////////////////
// Comment: 
//		ordinal objects			- renderable?, collideable?, visibleforAI?
//		physical-decorations	- renderable, collideable
//		lights					- lightsource
//		particles(temp-objects)	- renderable
//		glow					- renderable
//		sound					- ???
//////////////////////////////////////////////////////////////////////////
//class 				IRender_Sector;
//class 				ISpatial;
//class 				ISpatial_NODE;
//class 				ISpatial_DB;

//////////////////////////////////////////////////////////////////////////
// Fast type conversion
//class 			CObject;
//class 			IRenderable;
//class 			IRender_Light;
//
//namespace Feel { class Sound; }

//////////////////////////////////////////////////////////////////////////
class ISpatial_NODE;
class IRender_Sector;
class ISpatial_DB;

namespace Feel
{
	class Sound;
}

class IRenderable;
class IRender_Light;

class XRCDB_API ISpatial
{
private:
	Fvector last_sector_point;
public:
	struct _spatial
	{
		uint32_t type;
		Fsphere sphere;
		Fvector node_center; // Cached node center for TBV optimization
		float node_radius; // Cached node bounds for TBV optimization
		ISpatial_NODE* node_ptr; // Cached parent node for "empty-members" optimization
		IRender_Sector* sector;
		ISpatial_DB* space; // allow different spaces

		_spatial() : type(0)
		{
		} // safe way to enhure type is zero before any contstructors takes place
	} spatial;

public:
	BOOL spatial_inside();
	void spatial_updatesector_internal();
public:
	virtual void spatial_register();
	virtual void spatial_unregister();
	BENCH_SEC_SCRAMBLEVTBL2
	virtual void spatial_move();
	virtual Fvector spatial_sector_point() { return spatial.sphere.P; }
	inline void spatial_updatesector()
	{
		if (0 == (spatial.type & STYPEFLAG_INVALIDSECTOR)) return;
		spatial_updatesector_internal();
	};

	virtual CObject* dcast_CObject() { return 0; }
	virtual Feel::Sound* dcast_FeelSound() { return 0; }
	virtual IRenderable* dcast_Renderable() { return 0; }
	virtual IRender_Light* dcast_Light() { return 0; }

	// demonized: Check if eligible for bone calc optimizations
	virtual bool canOptimizeCalculateBones() { return true; }

	ISpatial(ISpatial_DB* space);
	virtual ~ISpatial();
};

//////////////////////////////////////////////////////////////////////////
//class ISpatial_NODE;
class ISpatial_NODE
{
public:
	typedef uint64_t ptrt;
public:
	ISpatial_NODE* parent; // parent node for "empty-members" optimization
	ISpatial_NODE* children [8]; // children nodes
	xr_vector<ISpatial*> items; // own items
public:
	void _init(ISpatial_NODE* _parent);
	void _remove(ISpatial* _S);
	void _insert(ISpatial* _S);

	bool _empty()
	{
		return items.empty() && !(
			children[0] || children[1] ||
			children[2] || children[3] ||
			children[4] || children[5] ||
			children[6] || children[7]
		);
	}
};

////////////


//template <class T, int granularity>
//class	poolSS;
#ifndef	DLL_API
#	define DLL_API					__declspec(dllimport)
#endif // #ifndef	DLL_API

//////////////////////////////////////////////////////////////////////////
class XRCDB_API ISpatial_DB
{
private:
	xrCriticalSection cs;

	poolSS<ISpatial_NODE, 128> allocator;

	xr_vector<ISpatial_NODE*> allocator_pool;
	ISpatial* rt_insert_object;
public:
	ISpatial_NODE* m_root;
	Fvector m_center;
	float m_bounds;
	xr_vector<ISpatial*>* q_result;
	uint32_t stat_nodes;
	uint32_t stat_objects;
	CStatTimer stat_insert;
	CStatTimer stat_remove;
private:
	IC uint32_t _octant(uint32_t x, uint32_t y, uint32_t z) { return z * 4 + y * 2 + x; }
	IC uint32_t _octant(Fvector& base, Fvector& rel)
	{
		uint32_t o = 0;
		if (rel.x > base.x) o += 1;
		if (rel.y > base.y) o += 2;
		if (rel.z > base.z) o += 4;
		return o;
	}

	ISpatial_NODE* _node_create();
	void _node_destroy(ISpatial_NODE* & P);

	void _insert(ISpatial_NODE* N, Fvector& n_center, float n_radius);
	void _remove(ISpatial_NODE* N, ISpatial_NODE* N_sub);
public:
	ISpatial_DB();
	~ISpatial_DB();

	// managing
	void initialize(Fbox& BB);
	//void							destroy			();
	void insert(ISpatial* S);
	void remove(ISpatial* S);
	void update(uint32_t nodes = 8);
	BOOL verify();

public:
	enum
	{
		O_ONLYFIRST = (1 << 0),
		O_ONLYNEAREST = (1 << 1),
		O_ORDERED = (1 << 2),
		O_force_uint32_t = uint32_t(-1)
	};

	// query
	void q_ray(xr_vector<ISpatial*>& R, uint32_t _o, uint32_t _mask_and, const Fvector& _start, const Fvector& _dir,
	           float _range);
	void q_box(xr_vector<ISpatial*>& R, uint32_t _o, uint32_t _mask_or, const Fvector& _center, const Fvector& _size);
	void q_sphere(xr_vector<ISpatial*>& R, uint32_t _o, uint32_t _mask_or, const Fvector& _center, const float _radius);
	void q_frustum(xr_vector<ISpatial*>& R, uint32_t _o, uint32_t _mask_or, const CFrustum& _frustum);
};

XRCDB_API extern ISpatial_DB* g_SpatialSpace;
XRCDB_API extern ISpatial_DB* g_SpatialSpacePhysic;

// #pragma pack(pop)

#endif // #ifndef XRENGINE_ISPATIAL_H_INCLUDED
