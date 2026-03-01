#pragma once

#include <VkBootstrap.h>
#include "hwcaps.h"
#include "../../build_config_defines.h"

class VHW : public pureAppActivate, public pureAppDeactivate {

public:
    VHW() : pPhysicalDevice(nullptr), pDevice(nullptr), pSwapchain(nullptr) {  
        Device.seqAppActivate.Add(this);
        Device.seqAppDeactivate.Add(this);
    }
    ~VHW() {
        Device.seqAppActivate.Remove(this);
        Device.seqAppDeactivate.Remove(this);
    }
    virtual	void	OnAppActivate();
	virtual void	OnAppDeactivate();

    void CreateDevice(SDL_Window* win);
    void Destroy();
    void Reset();

    // TODO:
    // void SelectGPU();

private:
    void createInstance();
    void CreateDevice();
    void CreateSwapchain();

private;
    // TODO: multi-gpu setup
    vkb::Instance instance;
    vkb::Device device;
    vkb::Swapchain swapchain;
};