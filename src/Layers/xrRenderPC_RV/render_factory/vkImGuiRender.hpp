#pragma once

#include <ImGuiRender.h>
#include "VkHW.hpp"

class vkImGuiRender : public IImGuiRender
{
    void SetState(ImDrawData* data);

public:
    void Copy(IImGuiRender& _in) override;

    void Frame() override;
    void Render(ImDrawData* data) override;

    void OnDeviceCreate(ImGuiContext* context) override;
    void OnDeviceDestroy() override;
    void OnDeviceResetBegin() override;
    void OnDeviceResetEnd() override;

private:
    VkViewport viewport;
    VkDescriptorPool imguiPool;
};