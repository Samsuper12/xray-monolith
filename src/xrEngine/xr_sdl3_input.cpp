#include "xr_sdl3_input.hpp"
#include "IInputReceiver.h"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <algorithm>

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

bool is_mouse_scancode(SDL_Scancode code) {
	return (code < SDL_SCANCODE_A && code > SDL_SCANCODE_UNKNOWN);
}

bool is_scanode_in_range(SDL_Scancode code) {
return code != SDL_SCANCODE_UNKNOWN && code < SDL_SCANCODE_ENDCALL;
}

bool SDL3Input::iGetAsyncKeyState(SDL_Scancode code)
{
	if (!is_scanode_in_range(code))
		return false;
	
	if (is_mouse_scancode(code))
		return iGetAsyncBtnState(static_cast<int>(code));
	
	const bool* state = SDL_GetKeyboardState(nullptr);
    return state[code];
}

bool SDL3Input::iGetAsyncBtnState(int btn)
{
	if (!is_scanode_in_range(static_cast<SDL_Scancode>(btn)))
		return false;

	size_t index = std::clamp(btn -1, 0,  static_cast<int>(mouseState.size() - 1));
	return mouseState[index];
}

void SDL3Input::resetMouseState()
{
   std::fill(mouseState.begin(), mouseState.end(), 0);
}

void SDL3Input::KeyUpdate(SDL_KeyboardEvent key)
{
	if (key.repeat) {
			cbStack.back()->IR_OnKeyboardHold(static_cast<int>(key.scancode));
			return;
	}
	if (key.down) {
		cbStack.back()->IR_OnKeyboardPress(static_cast<int>(key.scancode));
		KBState.insert(key.scancode);
	} else {
		cbStack.back()->IR_OnKeyboardRelease(static_cast<int>(key.scancode));
		KBState.erase(key.scancode);
	}
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
	// TODO: add support for x1-x1 keys
	if (button.button > SDL_BUTTON_RIGHT)
		return;

	size_t index = std::clamp(button.button - 1, 0, SDL_BUTTON_RIGHT);

	if(button.down)
		cbStack.back()->IR_OnMousePress(button.button);
			
	if(!button.down)
		cbStack.back()->IR_OnMouseRelease(button.button);

	if(mouseState[index] == button.down)
		cbStack.back()->IR_OnMouseHold(button.button);

	mouseState[index] = button.down;
}

void SDL3Input::Update() {
	const static int mouse_dt = 25;
	glm::vec2 pos;
	SDL_GetRelativeMouseState(&pos.x, &pos.y);
	if(timeStamp && ((SDL_GetTicks() - timeStamp) >= mouse_dt) && pos == mouseLastRel) {
		cbStack.back()->IR_OnMouseStop(0, 0);
	}
	timeStamp = 0;

	// SDL_KeyboardEvent.repeat not enough
	for(auto code : KBState) {
		cbStack.back()->IR_OnKeyboardHold(static_cast<int>(code));
	}
}
