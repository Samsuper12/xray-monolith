#pragma once
#include "WeaponCustomPistol.h"

class CWeaponRevolver :
	public CWeaponCustomPistol
{
	typedef CWeaponCustomPistol inherited;
public:
	CWeaponRevolver();
	virtual ~CWeaponRevolver();

	virtual void Load(LPCSTR section);
	virtual void PlayAnimReload();

protected:
	virtual bool AllowFireWhileWorking() { return true; }
	ESoundTypes m_eSoundClose;
};
