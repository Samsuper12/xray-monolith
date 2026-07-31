// xrRender_R2.cpp : Defines the entry point for the DLL application.
//
#include "rv.hpp"
#include "render_factory/vkRenderFactory.hpp"
#include "render_factory/vkUIRender.hpp"
#include <xrRender_console.h>

//#include "render_factory/dxDebugRender.h"

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
