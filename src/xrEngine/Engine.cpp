// Engine.cpp: implementation of the CEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "Engine.h"
#include "dedicated_server_only.h"

CEngine Engine;
xrDispatchTable PSGP;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEngine::CEngine()
{
}

CEngine::~CEngine()
{
}

extern void msCreate(LPCSTR name);

extern "C" void __cdecl xrBind_PSGP(xrDispatchTable* T, _processor_info* ID);

PROTECT_API void CEngine::Initialize(void)
{
	PROF_EVENT();
	xrBinder* bindCPU = xrBind_PSGP;
	R_ASSERT(bindCPU);
	bindCPU(&PSGP, &CPU::ID);

	// Other stuff
	Engine.Sheduler.Initialize();
	//
#ifdef DEBUG
    msCreate("game");
#endif
}


void CEngine::Destroy()
{
	Engine.Sheduler.Destroy();
	Engine.External.Destroy();

	ZeroMemory(&PSGP, sizeof(PSGP));
}
