#include "xr_sdl3_input.hpp"
#include "IInputReceiver.h"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <glm/common.hpp>
#include <glm/glm.hpp>

IInputReceiver dummyController;
SDL3Input* pSDL3Input = nullptr;

// TODO: move them
ENGINE_API float psMouseSens = 1.f;
ENGINE_API float psMouseSensScale = 1.f;
ENGINE_API float psMouseSensVerticalK = 1.f;
ENGINE_API Flags32 psMouseInvert = {FALSE};

SDL3Input::SDL3Input() {
    iCapture(&dummyController);

#ifdef ENGINE_BUILD
	Device.seqAppActivate.Add(this);
	Device.seqAppDeactivate.Add(this, REG_PRIORITY_HIGH);
	Device.seqFrame.Add(this, REG_PRIORITY_HIGH);
#endif
}

SDL3Input::~SDL3Input() {
#ifdef ENGINE_BUILD
	Device.seqFrame.Remove(this);
	Device.seqAppDeactivate.Remove(this);
	Device.seqAppActivate.Remove(this);
#endif
}

void SDL3Input::UpdateSDL3Event(const SDL_Event& ev) {
	// Update with info from the last frame.
	Update();

	switch(ev.type) {
		case SDL_EVENT_MOUSE_MOTION:
			MouseUpdate(ev.motion);
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			MouseUpdate(ev.button);
			break;
		case SDL_EVENT_MOUSE_WHEEL:
			MouseUpdate(ev.wheel);
			break;
		case SDL_EVENT_KEY_UP:
		case SDL_EVENT_KEY_DOWN:
			KeyUpdate(ev.key);
			break;
		default: break;
	}
}

void SDL3Input::iCapture(IInputReceiver* p)
{
	VERIFY(p);
	
	if (!cbStack.empty())
		cbStack.back()->IR_OnDeactivate();
	cbStack.push_back(p);
	cbStack.back()->IR_OnActivate();

    
   // std::fill(timeStamp.begin(), timeStamp.end(), 0);
   // std::fill(timeSave.begin(), timeSave.end(), 0);
    //std::fill(offs.begin(), offs.end(), 0);
}

void SDL3Input::iRelease(IInputReceiver* p)
{
	if (p == cbStack.back())
	{
		cbStack.back()->IR_OnDeactivate();
		cbStack.pop_back();
		IInputReceiver* ir = cbStack.back();
		ir->IR_OnActivate();
	}
	else
	{
        // FIXME: just use ranges-v3 or algorithm or something
		size_t cnt = cbStack.size();
		for (; cnt > 0; --cnt)
			if (cbStack[cnt - 1] == p)
			{
				xr_vector<IInputReceiver*>::iterator it = cbStack.begin();
				std::advance(it, cnt - 1);
				cbStack.erase(it);
				break;
			}
	}
}

IInputReceiver* SDL3Input::CurrentIR()
{
	if (cbStack.size())
		return cbStack.back();
	else
		return NULL;
}

void SDL3Input::OnAppActivate(void)
{
	if (CurrentIR())
		CurrentIR()->IR_OnActivate();
}

void SDL3Input::OnAppDeactivate(void)
{
	if (CurrentIR())
		CurrentIR()->IR_OnDeactivate();
}

void SDL3Input::DeactivateSoft()
{
	if (CurrentIR())
		CurrentIR()->IR_OnDeactivate();

}

void SDL3Input::OnFrame(void)
{
	RDEVICE.Statistic->Input.Begin();
	RDEVICE.Statistic->Input.End();
}

bool SDL3Input::iGetAsyncKeyState(int dik)
{
    //if (code < SDL_SCANCODE_UNKNOWN || code >= SDL_SCANCODE_COUNT)
      return false;

	//return KBState[code];
}

bool SDL3Input::iGetAsyncBtnState(int btn)
{
	if (btn == 0 || btn == 1)
		btn = btn == 0 ? 1 : 0;
	return mouseState[btn];
}

void SDL3Input::resetMouseState()
{

   std::fill(mouseState.begin(), mouseState.end(), 0);
}

void SDL3Input::KeyUpdate(SDL_KeyboardEvent key)
{

	// {
	// 	for (u32 i = 0; i < dwElements; i++)
	// 	{
	// 		if (od[i].uAppData == 666) //ignored action
	// 			continue;

	// 		key = od[i].dwOfs;
	// 		if (od[i].dwData & 0x80)
	// 			cbStack.back()->IR_OnKeyboardPress(key);
	// 		else
	// 		{
	// 			cbStack.back()->IR_OnKeyboardRelease(key);
	// 		}
	// 	}

	// 	for (u32 i = 0; i < COUNT_KB_BUTTONS; i++)
	// 		if (KBState[i])
	// 			cbStack.back()->IR_OnKeyboardHold(i);
	// }
}

void SDL3Input::MouseUpdate(SDL_MouseWheelEvent wheel)
{
	cbStack.back()->IR_OnMouseWheel(static_cast<int32_t>(wheel.y));
}

void SDL3Input::MouseUpdate(SDL_MouseMotionEvent motion)
{
	cbStack.back()->IR_OnMouseMove(static_cast<int32_t>(motion.xrel), static_cast<int32_t>(motion.yrel));

	timeStamp = motion.timestamp;
	mouseLastRel = glm::vec2(motion.xrel, motion.yrel);
	mouseLastPos = glm::vec2(motion.x, motion.y);
}

void SDL3Input::MouseUpdate(SDL_MouseButtonEvent button)
{
	std::array<bool, count_mouse_buttors> mousePrev = mouseState;

		switch (button.button)
		{
		case SDL_BUTTON_LEFT:
			mouseState[0] = button.down;
			
			if(button.down)
				cbStack.back()->IR_OnMousePress(0);
			
			if(!button.down)
				cbStack.back()->IR_OnMouseRelease(0);

			if(mousePrev[0] == button.down)
				cbStack.back()->IR_OnMouseHold(0);

			break;
		case SDL_BUTTON_RIGHT:
			mouseState[1] = button.down;
			
			if(button.down)
				cbStack.back()->IR_OnMousePress(1);
			
			if(!button.down)
				cbStack.back()->IR_OnMouseRelease(1);

			if(mousePrev[1] == button.down)
				cbStack.back()->IR_OnMouseHold(1);

			break;
		case SDL_BUTTON_MIDDLE:
			mouseState[2] = button.down;
			
			if(button.down)
				cbStack.back()->IR_OnMousePress(2);
			
			if(!button.down)
				cbStack.back()->IR_OnMouseRelease(2);

			if(button.down)
				cbStack.back()->IR_OnMouseHold(2);

			break;
		default:
			break;
	};
}

void SDL3Input::Update() {
	const static int mouse_dt = 25;
	glm::vec2 pos;
	SDL_GetRelativeMouseState(&pos.x, &pos.y);
	if(timeStamp && ((SDL_GetTicks() - timeStamp) >= mouse_dt) && pos == mouseLastRel) {
		cbStack.back()->IR_OnMouseStop(DIMOFS_X, 0);
		cbStack.back()->IR_OnMouseStop(DIMOFS_Y, 0);
	}

	timeStamp = 0;
}
