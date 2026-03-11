#pragma once
#include "../monster_state_manager.h"

class CChimera;

class CStateManagerChimera : public CMonsterStateManager<CChimera>
{
private:
	typedef CMonsterStateManager<CChimera> inherited;
	using inherited::object;
	using inherited::add_state;
	using inherited::get_state_current;
	using inherited::select_state;
	using inherited::current_substate;
	using inherited::prev_substate;
	using inherited::time_state_started; 

public:
	CStateManagerChimera(CChimera* obj);
	virtual ~CStateManagerChimera();

	virtual void execute();
	virtual void remove_links(CObject* object) { inherited::remove_links(object); }
};
