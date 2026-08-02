#include <Engine.h>
#include <defines.h>
#include <imgui.h>
#include <imgui/backends/imgui_impl_sdl3.h>
#include <LocatorAPI.h>
#include <string_concatenations.h>
#include <xr_ini.h>

#include "imgui_base.h"
#include "device.h"
#include "IGame_Persistent.h"

namespace xr_imgui
{
    static bool imgui_demo = false;
    static bool imgui_metrics = false;

    ide::ide()
        :  m_render(nullptr), m_shown(true), firstframe(true)
    {
        m_context = ImGui::CreateContext();
        Device.seqResolutionChanged.Add(this);
    }

    ide::~ide()
    {
       ImGui::DestroyContext(m_context);
    }

    void ide::SDL3ProcessEvent(SDL_Event* ev) {
        ImGui_ImplSDL3_ProcessEvent(ev);
    }

    void ide::OnDeviceCreate()
    {

        m_render = RenderFactory->CreateImGuiRender();
        m_render->OnDeviceCreate(m_context);
    }

    void ide::OnDeviceDestroy()
    {
        m_render->OnDeviceDestroy();
        RenderFactory->DestroyImGuiRender(m_render);
        m_render = nullptr;
    }

    void ide::OnDeviceResetBegin() const
    {
        m_render->OnDeviceResetBegin();
    }

    void ide::OnDeviceResetEnd() const
    {
        m_render->OnDeviceResetEnd();
    }

    void ide::OnAppStart()
    {
        Device.seqFrame.Add(this, -5);
        Device.seqRender.Add(this, -5);
    }

    void ide::OnAppEnd()
    {
        Device.seqFrame.Remove(this);
        Device.seqRender.Remove(this);
    }

    void ide::OnScreenResolutionChanged()
    {
        // TODO:
        // ImGuiIO& io = ImGui::GetIO();
        // io.DisplaySize = { static_cast<float>(Device.dwWidth), static_cast<float>(Device.dwHeight) };
    }

     void ide::OnAppActivate()
    {

    }

    void ide::OnAppDeactivate()
    {
        // ImGuiIO& io = ImGui::GetIO();
        // io.AddFocusEvent(false);
    }

    void ide::OnFrame()
    {
        if (!!!Device.b_is_Active) return;

        m_render->Frame();

        if (firstframe)
        {
            OnScreenResolutionChanged();
            ImGui::NewFrame();
        }
        
        if (is_shown())
        {
            ShowMain();
            if (imgui_demo)     ImGui::ShowDemoWindow(&imgui_demo);
            if (imgui_metrics)  ImGui::ShowMetricsWindow(&imgui_metrics);
            
        }
        ImGui::End();
    }

    void ide::OnRender()
    {
        ImGui::Render();
        m_render->Render(ImGui::GetDrawData());

        if (firstframe)
        {
            firstframe = false;
            return;
        }

        ImGui::NewFrame();
    }

    void ide::ShowMain()
    {

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Stats", nullptr, psDeviceFlags.test(rsStatistic)))
                    psDeviceFlags.set(rsStatistic, !psDeviceFlags.test(rsStatistic));

                g_pGamePersistent->ImGui_OnRender("MenuFile");

                if (ImGui::MenuItem("Close"))
                    Show(false);

                ImGui::EndMenu();
            }

            g_pGamePersistent->ImGui_OnRender("MenuBar");

            if (ImGui::BeginMenu("About"))
            {
                if (ImGui::MenuItem("Demo", nullptr, imgui_demo))
                    imgui_demo = !imgui_demo;

                if (ImGui::MenuItem("Metrics", nullptr, imgui_metrics))
                    imgui_metrics = !imgui_metrics;

                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();

            g_pGamePersistent->ImGui_OnRender("Main");
        }

        const ImGuiViewport* Viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(Viewport->WorkPos);
        ImGui::SetNextWindowSize(Viewport->WorkSize);
        ImGui::SetNextWindowViewport(Viewport->ID);
        ImGui::SetNextWindowBgAlpha(0);

        constexpr ImGuiWindowFlags dockspace_window_flags = 0
            | ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoCollapse
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoMove
            //| ImGuiWindowFlags_NoDocking
            | ImGuiWindowFlags_NoNavFocus;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        if (ImGui::Begin("DockSpaceViewport_Main", nullptr, dockspace_window_flags))
        {
            ImGui::DockSpace(ImGui::GetID("DockSpace"), ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        }
        ImGui::PopStyleVar(3);
    }

    void ide::Show(bool bShow)
    {
        if (m_shown == bShow) return;
        m_shown = bShow;
    }
} // namespace xr_imgui