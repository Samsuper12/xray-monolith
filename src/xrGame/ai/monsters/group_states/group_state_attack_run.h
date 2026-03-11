#pragma once

#include "../state.h"

template <typename _Object>
class CStateGroupAttackRun : public CState<_Object>
{
	typedef CState<_Object> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started;
	using inherited::get_state;

	TTime m_time_path_rebuild;

	TTime m_next_encircle_tick;
	TTime m_encircle_time;
	Fvector m_encircle_dir;

	TTime m_intercept_tick;
	TTime m_intercept_length;
	Fvector m_intercept;

	TTime m_memorized_tick;
	Fvector m_memorized_pos;
	Fvector m_predicted_vel;

public:
	IC CStateGroupAttackRun(_Object* obj);

	virtual void initialize();
	virtual void execute();
	virtual void finalize();
	virtual void critical_finalize();

	virtual bool check_completion();
	virtual bool check_start_conditions();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};

#include "group_state_attack_run_inline.h"
