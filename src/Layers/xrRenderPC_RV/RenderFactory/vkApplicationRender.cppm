module;
#include "render_stub.hpp"
#include <ApplicationRender.h>

export module RenderFactory.ApplicationRender;

export class vkApplicationRender : public IApplicationRender {
public:
  virtual void Copy(IApplicationRender &_in);

  virtual void LoadBegin();
  virtual void destroy_loading_shaders();
  virtual void setLevelLogo(LPCSTR pszLogoName);
  virtual void load_draw_internal(CApplication &owner);
  //	?????
  virtual void KillHW();
};

void vkApplicationRender::Copy(IApplicationRender &_in) { render_stub(); }

void vkApplicationRender::LoadBegin() { render_stub(); }

void vkApplicationRender::destroy_loading_shaders() { render_stub(); }

void vkApplicationRender::setLevelLogo(LPCSTR pszLogoName) { render_stub(); }

void vkApplicationRender::load_draw_internal(CApplication &owner) {
  render_stub();
}

void vkApplicationRender::KillHW() { render_stub(); }