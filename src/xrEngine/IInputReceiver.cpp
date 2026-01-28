
#include "xr_sdl3_input.hpp"
#include "iinputreceiver.h"

void IInputReceiver::IR_Capture()
{
	VERIFY(pSDL3Input);
	pSDL3Input->iCapture(this);
}

void IInputReceiver::IR_Release()
{
	VERIFY(pSDL3Input);
	pSDL3Input->iRelease(this);
}

// void IInputReceiver::IR_GetLastMouseDelta(Ivector2& p)
// {
// 	VERIFY(pInput);
// 	pInput->iGetLastMouseDelta(p);
// }

void IInputReceiver::IR_OnDeactivate(void)
{
	//FIXME:
	// int i;
	// for (i = 0; i < CInput::COUNT_KB_BUTTONS; i++)
	// 	if (IR_GetKeyState(i))
	// 		IR_OnKeyboardRelease(i);

	// for (i = 0; i < CInput::COUNT_MOUSE_BUTTONS; i++)
	// 	if (IR_GetBtnState(i))
	// 		IR_OnMouseRelease(i);
	// IR_OnMouseStop(DIMOFS_X, 0);
	// IR_OnMouseStop(DIMOFS_Y, 0);
}

void IInputReceiver::IR_OnActivate(void)
{
}

BOOL IInputReceiver::IR_GetKeyState(int dik)
{
	VERIFY(pSDL3Input);
	return pSDL3Input->iGetAsyncKeyState(dik);
}

BOOL IInputReceiver::IR_GetBtnState(int btn)
{
	VERIFY(pSDL3Input);
	return pSDL3Input->iGetAsyncBtnState(btn);
}

glm::ivec2 IInputReceiver::IR_GetMousePosReal() {
		VERIFY(pSDL3Input);
		return pSDL3Input->iGetLastMouseReal();
}

// void IInputReceiver::IR_GetMousePosScreen(Ivector2& p)
// {
// 	GetCursorPos((LPPOINT)&p);
// }

// void IInputReceiver::IR_GetMousePosReal(HWND hwnd, Ivector2& p)
// {
// 	// FIXME:
// 	//IR_GetMousePosScreen(p);
// 	//if (hwnd) ScreenToClient(hwnd, (LPPOINT)&p);
// }

// void IInputReceiver::IR_GetMousePosReal(Ivector2& p)
// {
// 	// FIXME:
// 	IR_GetMousePosReal(RDEVICE.m_hWnd, p);
// }

// void IInputReceiver::IR_GetMousePosIndependent(Fvector2& f)
// {
// 	Ivector2 p;
// 	IR_GetMousePosReal(p);
// 	f.set(
// 		2.f * float(p.x) / float(RDEVICE.dwWidth) - 1.f,
// 		2.f * float(p.y) / float(RDEVICE.dwHeight) - 1.f
// 	);
// }

// void IInputReceiver::IR_GetMousePosIndependentCrop(Fvector2& f)
// {
// 	IR_GetMousePosIndependent(f);
// 	if (f.x < -1.f) f.x = -1.f;
// 	if (f.x > 1.f) f.x = 1.f;
// 	if (f.y < -1.f) f.y = -1.f;
// 	if (f.y > 1.f) f.y = 1.f;
// }
