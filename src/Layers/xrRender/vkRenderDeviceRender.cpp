#include "vkRenderDeviceRender.hpp"


void vkRenderDeviceRender::Create(SDL_Window* window, u32& dwWidth, u32& dwHeight, float& fWidth_2, float& fHeight_2,
                                  bool move_window) 
{
    vkHW.CreateDevice(window);

    // setup dwWidth, dwHeight
    Resources = xr_new<CResourceManager>();
}

void vkRenderDeviceRender::SetupGPU(BOOL bForceGPU_SW, BOOL bForceGPU_NonPure, BOOL bForceGPU_REF)
{
	HW.Caps.bForceGPU_SW = bForceGPU_SW;
	HW.Caps.bForceGPU_NonPure = bForceGPU_NonPure;
	HW.Caps.bForceGPU_REF = bForceGPU_REF;
}