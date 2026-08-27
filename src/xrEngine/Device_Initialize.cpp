#include "resource.h"
#include "dedicated_server_only.h"

#ifdef INGAME_EDITOR
# include "../include/editor/ide.hpp"
# include "engine_impl.hpp"
#endif // #ifdef INGAME_EDITOR

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#ifdef INGAME_EDITOR
void CRenderDevice::initialize_editor()
{
    m_editor_module = LoadLibrary("editor.dll");
    if (!m_editor_module)
    {
        Msg("! cannot load library \"editor.dll\"");
        return;
    }

    m_editor_initialize = (initialize_function_ptr)GetProcAddress(m_editor_module, "initialize");
    VERIFY(m_editor_initialize);

    m_editor_finalize = (finalize_function_ptr)GetProcAddress(m_editor_module, "finalize");
    VERIFY(m_editor_finalize);

    m_engine = xr_new<engine_impl>();
    m_editor_initialize(m_editor, m_engine);
    VERIFY(m_editor);

    m_hWnd = m_editor->view_handle();
    VERIFY(m_hWnd != INVALID_HANDLE_VALUE);
}
#endif // #ifdef INGAME_EDITOR

PROTECT_API void CRenderDevice::Initialize()
{
	PROF_EVENT();
	Log("Initializing Engine...");
	TimerGlobal.Start();
	TimerMM.Start();

#ifdef INGAME_EDITOR
    if (Core.Params.editor)
        initialize_editor();
#endif // #ifdef INGAME_EDITOR

	// Unless a substitute hWnd has been specified, create a window to render into

	m_window = SDL_CreateWindow(
		"S.T.A.L.K.E.R.: Anomaly SDL3",
		1920,
		1080,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN | SDL_WINDOW_HIGH_PIXEL_DENSITY
	);

	if (m_window == nullptr) {
		Msg("SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_Quit();
		abort();
	}

	SDL_PropertiesID props = SDL_GetWindowProperties(m_window);
	Device.seqAppStart.Add(&m_imgui);
	Device.seqAppEnd.Add(&m_imgui);
}
