////////////////////////////////////////////////////////////////////////////
//	Module 		: ai_obstacle.h
//	Created 	: 02.04.2007
//  Modified 	: 06.04.2007
//	Author		: Dmitriy Iassenev
//	Description : ai obstacle class inline functions
////////////////////////////////////////////////////////////////////////////

#ifndef AI_OBSTACLE_H
#define AI_OBSTACLE_H

#include "moving_objects.h"
#include "magic_box3.h"

class CGameObject;

class ai_obstacle
{
public:
	typedef moving_objects::AREA AREA;

private:
	enum
	{
		PLANE_COUNT = 6,
	};

private:
	typedef Fplane CPlanesArray[PLANE_COUNT];

private:
	struct CPlanes
	{
		CPlanesArray m_planes;
	};

private:
	CGameObject* m_object;
	bool m_actual;
	AREA m_area;
	AREA m_danger_area;
	u32 m_crc;
	CPlanes m_box;
	MagicBox3 m_min_box;

private:
	inline bool inside(const Fvector& position, const float& radius) const;
	inline bool inside(const Fvector& position, const float& radius, const float& increment, const u32 step_count) const;
	void prepare_inside(Fvector& start, Fvector& dest);
	void correct_position(Fvector& position);
	void compute_impl();
	void compute();
	void compute_matrix(Fmatrix& result, const Fvector& additional);

public:
	inline ai_obstacle(CGameObject* object);
	inline const AREA& area();
	inline const AREA& danger_area();
	void on_move();
	inline bool inside(const u32& vertex_id) const;
	inline const u32& crc();
	float distance_to(const Fvector& position) const;
	inline const MagicBox3 min_box();
};

#include "ai_obstacle_inline.h"

#endif // AI_OBSTACLE_H
