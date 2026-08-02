#pragma once

#include "../Layers/xrRender/ImGuiRender.h"
#include <SDL3/SDL_events.h>

struct ImGuiContext;

class IReader;
namespace xr_imgui
{
    struct ide_backend;

    class ide :
        public pureRender,
        public pureFrame,
        public pureAppActivate,
        public pureAppDeactivate,
        public pureAppStart,
        public pureAppEnd,
        public pureScreenResolutionChanged
    {
    public:
        ide();
        ~ide();

        bool is_shown() const { return m_shown; }
        void Show(bool bShow = true);
        void EnableInput(bool bInput = true);

    public:
        void OnDeviceCreate();
        void OnDeviceDestroy();
        void OnDeviceResetBegin() const;
        void OnDeviceResetEnd() const;

    public:
        // Interface implementations
        void OnFrame() final;
        void OnRender() final;

        void OnAppActivate() final;
        void OnAppDeactivate() final;

        void OnAppStart() final;
        void OnAppEnd() final;

        virtual void OnScreenResolutionChanged();

        void SDL3ProcessEvent(SDL_Event* ev);

    private:
        void InitBackend();
        void ShutdownBackend();

    private:
        void ShowMain();

    private:
        IImGuiRender* m_render;
        ImGuiContext* m_context;
        bool m_shown;
        bool firstframe;
    };
} // namespace xr_imgui