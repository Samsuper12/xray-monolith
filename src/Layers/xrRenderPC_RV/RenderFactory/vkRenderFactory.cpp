#include "vkRenderFactory.hpp"

import RenderFactory.ApplicationRender;
import RenderFactory.UIShader;
import RenderFactory.UIRender;
import RenderFactory.ConsoleRender;
import RenderFactory.FontRender;
import RenderFactory.ImGuiRender;
import RenderFactory.StatGraphRender;
import RenderFactory.RenderDeviceRender;
import RenderFactory.EnvironmentRender;
import RenderFactory.LensFlareRender;
import RenderFactory.RainRender;
import RenderFactory.StatRender;
import RenderFactory.WallMarkArray;
import RenderFactory.UISequenceVideoItem;
import RenderFactory.ThunderboltRender;
import RenderFactory.ThunderboltDescRender;

#include <xrMemory.h>
vkRenderFactory RenderFactoryImpl;

#define RENDER_FACTORY_IMPLEMENT(Class)                                        \
  I##Class *vkRenderFactory::Create##Class() { return xr_new<vk##Class>(); }   \
  void vkRenderFactory::Destroy##Class(I##Class *pObject) {                    \
    xr_delete((vk##Class *&)pObject);                                          \
  }
#ifndef _EDITOR
RENDER_FACTORY_IMPLEMENT(UISequenceVideoItem)
RENDER_FACTORY_IMPLEMENT(UIShader)
RENDER_FACTORY_IMPLEMENT(StatGraphRender)
RENDER_FACTORY_IMPLEMENT(ConsoleRender)
RENDER_FACTORY_IMPLEMENT(RenderDeviceRender)
#ifdef DEBUG
RENDER_FACTORY_IMPLEMENT(ObjectSpaceRender)
#endif // DEBUG
RENDER_FACTORY_IMPLEMENT(ApplicationRender)
RENDER_FACTORY_IMPLEMENT(WallMarkArray)
RENDER_FACTORY_IMPLEMENT(StatsRender)
#endif // _EDITOR

#ifndef _EDITOR
RENDER_FACTORY_IMPLEMENT(ThunderboltRender)
RENDER_FACTORY_IMPLEMENT(ThunderboltDescRender)
RENDER_FACTORY_IMPLEMENT(RainRender)
RENDER_FACTORY_IMPLEMENT(LensFlareRender)
RENDER_FACTORY_IMPLEMENT(ImGuiRender)
RENDER_FACTORY_IMPLEMENT(EnvironmentRender)
RENDER_FACTORY_IMPLEMENT(EnvDescriptorMixerRender)
RENDER_FACTORY_IMPLEMENT(EnvDescriptorRender)
RENDER_FACTORY_IMPLEMENT(FlareRender)
#endif
RENDER_FACTORY_IMPLEMENT(FontRender)
