module;

#include "render_stub.hpp"
#include <LensFlareRender.h>

export module RenderFactory.LensFlareRender;

export class vkFlareRender : public IFlareRender {
public:
  virtual void Copy(IFlareRender &_in);

  virtual void CreateShader(LPCSTR sh_name, LPCSTR tex_name);
  virtual void DestroyShader();
};

export class vkLensFlareRender : public ILensFlareRender {
public:
  virtual void Copy(ILensFlareRender &_in);

  virtual void Render(CLensFlare &owner, BOOL bSun, BOOL bFlares,
                      BOOL bGradient);

  virtual void OnDeviceCreate();
  virtual void OnDeviceDestroy();
};

void vkFlareRender::Copy(IFlareRender &_in) { render_stub(); }

void vkFlareRender::CreateShader(LPCSTR sh_name, LPCSTR tex_name) {
  render_stub();
}

void vkFlareRender::DestroyShader() { render_stub(); }

void vkLensFlareRender::Copy(ILensFlareRender &_in) { render_stub(); }

void vkLensFlareRender::Render(CLensFlare &owner, BOOL bSun, BOOL bFlares,
                               BOOL bGradient) {
  render_stub();
}

void vkLensFlareRender::OnDeviceCreate() { render_stub(); }

void vkLensFlareRender::OnDeviceDestroy() { render_stub(); }