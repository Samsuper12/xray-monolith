module;
#include "../xrRender/RenderFactory.h"
export module RV.RenderFactory;
export import RenderFactory.ApplicationRender;
export import RenderFactory.UIShader;
export import RenderFactory.UIRender;
export import RenderFactory.ConsoleRender;
export import RenderFactory.FontRender;
export import RenderFactory.ImGuiRender;
export import RenderFactory.StatGraphRender;
export import RenderFactory.RenderDeviceRender;
export import RenderFactory.EnvironmentRender;
export import RenderFactory.LensFlareRender;
export import RenderFactory.RainRender;
export import RenderFactory.StatRender;
export import RenderFactory.WallMarkArray;
export import RenderFactory.UISequenceVideoItem;
export import RenderFactory.ThunderboltRender;
export import RenderFactory.ThunderboltDescRender;
//TODO:
// import xr.Core;

// #define RENDER_FACTORY_DECLARE(Class) \
// 	/*virtual*/ I##Class* Create##Class(); \
// 	/*virtual*/ void Destroy##Class(I##Class *pObject);

// #define RENDER_FACTORY_IMPLEMENT(Class) \
// 	export I##Class* vkRenderFactory::Create##Class() \
// { \
// 	return xr_new<vk##Class>(); \
// } \
// 	export void vkRenderFactory::Destroy##Class(I##Class *pObject)\
// { \
// 	xr_delete((vk##Class*&)pObject); \
// }

// export class vkRenderFactory /* : public IRenderFactory */
// {
// public:
// 	RENDER_FACTORY_DECLARE(UISequenceVideoItem)
// 	RENDER_FACTORY_DECLARE(UIShader)
// 	RENDER_FACTORY_DECLARE(StatGraphRender)
// 	RENDER_FACTORY_DECLARE(ConsoleRender)
// 	RENDER_FACTORY_DECLARE(RenderDeviceRender)
// #	ifdef DEBUG
// 		RENDER_FACTORY_DECLARE(ObjectSpaceRender)
// #	endif // DEBUG
// 	RENDER_FACTORY_DECLARE(ApplicationRender)
// 	RENDER_FACTORY_DECLARE(WallMarkArray)
// 	RENDER_FACTORY_DECLARE(StatsRender)
// 	RENDER_FACTORY_DECLARE(FlareRender)
// 	RENDER_FACTORY_DECLARE(ThunderboltRender)
// 	RENDER_FACTORY_DECLARE(ThunderboltDescRender)
// 	RENDER_FACTORY_DECLARE(RainRender)
// 	RENDER_FACTORY_DECLARE(LensFlareRender)
// 	RENDER_FACTORY_DECLARE(ImGuiRender)
// 	RENDER_FACTORY_DECLARE(EnvironmentRender)
// 	RENDER_FACTORY_DECLARE(EnvDescriptorMixerRender)
// 	RENDER_FACTORY_DECLARE(EnvDescriptorRender)
// 	RENDER_FACTORY_DECLARE(FontRender)
// };

// export vkRenderFactory RenderFactoryImpl;

// //extern vkRenderFactory RenderFactoryImpl;


// RENDER_FACTORY_IMPLEMENT(UISequenceVideoItem)
// RENDER_FACTORY_IMPLEMENT(UIShader)
// RENDER_FACTORY_IMPLEMENT(StatGraphRender)
// RENDER_FACTORY_IMPLEMENT(ConsoleRender)
// RENDER_FACTORY_IMPLEMENT(RenderDeviceRender)
// #	ifdef DEBUG
// 		RENDER_FACTORY_IMPLEMENT(ObjectSpaceRender)
// #	endif // DEBUG
// RENDER_FACTORY_IMPLEMENT(ApplicationRender)
// RENDER_FACTORY_IMPLEMENT(WallMarkArray)
// RENDER_FACTORY_IMPLEMENT(StatsRender)
// RENDER_FACTORY_IMPLEMENT(ThunderboltRender)
// RENDER_FACTORY_IMPLEMENT(ThunderboltDescRender)
// RENDER_FACTORY_IMPLEMENT(RainRender)
// RENDER_FACTORY_IMPLEMENT(LensFlareRender)
// RENDER_FACTORY_IMPLEMENT(ImGuiRender)
// RENDER_FACTORY_IMPLEMENT(EnvironmentRender)
// RENDER_FACTORY_IMPLEMENT(EnvDescriptorMixerRender)
// RENDER_FACTORY_IMPLEMENT(EnvDescriptorRender)
// RENDER_FACTORY_IMPLEMENT(FlareRender)
// RENDER_FACTORY_IMPLEMENT(FontRender)
