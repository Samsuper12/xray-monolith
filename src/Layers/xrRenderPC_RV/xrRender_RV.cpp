#include "RenderFactory/vkRenderFactory.hpp"
#include <xrRender_console.h>
#include <Render.h>

import xr.RV;

extern void xrRender_initconsole();
BOOL DllMainXrRenderRV()
{
		Render = &RImplementation;
		RenderFactory = &RenderFactoryImpl;
		// ::DU = &DUImpl;
		// //::vid_mode_token			= inited by HW;
		UIRender = &UIRenderImpl;
		// DRender	= &DebugRenderImpl;
		xrRender_initconsole();
}

extern "C" {
bool /*_declspec(dllexport)*/ SupportsVulkanRendering();
};

bool /*_declspec(dllexport)*/ SupportsVulkanRendering()
{

}
