#ifndef XR_SDL3_INPUT_HPP
#define XR_SDL3_INPUT_HPP

#include <cstdint>
#include <array>
#include <glm/vec2.hpp>
#include <glm/integer.hpp>
#include <SDL3/SDL_events.h>

// TODO: remove this piece of shit
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class IInputReceiver;

/// ЇЇЇЇЇ 
class ENGINE_API SDL3Input
	:
	public pureFrame,
	public pureAppActivate,
	public pureAppDeactivate
{
public:
    virtual void OnFrame(void);
	virtual void OnAppActivate(void);
	virtual void OnAppDeactivate(void);

    // make 305 rule
    SDL3Input();
	~SDL3Input();

	// FIXME: let SDL3 handle it
    static constexpr int count_mouse_buttors = 3;
    static constexpr int count_mouse_axis = 2;
    static constexpr int count_kb_buttons = 256;

	// FIXME:
	// if (pInput->get_exclusive_mode())
	// {
	// 	SetCursorPos(m_mouse_pos.x, m_mouse_pos.y);
	// }

    void resetMouseState();
    void UpdateSDL3Event(const SDL_Event& ev);

	void iCapture(IInputReceiver* pc);
	void iRelease(IInputReceiver* pc);
	bool iGetAsyncKeyState(int dik);
	bool iGetAsyncBtnState(int btn);

	glm::vec2 iGetLastMouseDelta() const { return mouseLastRel; }
	glm::ivec2 iGetLastMouseReal() const { return mouseLastPos; }

    void DeactivateSoft();
	IInputReceiver* CurrentIR();

	// FIXME: SDL_SetWindowMouseGrab
	//exclusive_mode();

	// FIXME: 
	// bool get_dik_name(int dik, LPSTR dest, int dest_sz);

private:
	//FIXME: init {} in constructor
    uint64_t timeStamp;
    std::array<bool, count_mouse_buttors> mouseState;
    std::array<bool, count_kb_buttons> KBState;
	glm::vec2 mouseLastRel;
	glm::ivec2 mouseLastPos;
    xr_vector<IInputReceiver*> cbStack;

	void Update();
    void MouseUpdate(SDL_MouseMotionEvent motion);
	void MouseUpdate(SDL_MouseButtonEvent button);
    void MouseUpdate(SDL_MouseWheelEvent whell);

	void KeyUpdate(SDL_KeyboardEvent key);
};

extern ENGINE_API SDL3Input* pSDL3Input;

#endif // XR_SDL3_INPUT_HPP