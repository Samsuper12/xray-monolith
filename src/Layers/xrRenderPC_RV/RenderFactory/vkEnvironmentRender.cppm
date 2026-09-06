module;

#include "render_stub.hpp"
#include <EnvironmentRender.h>

export module RenderFactory.EnvironmentRender;

export class vkEnvDescriptorRender : public IEnvDescriptorRender {
  friend class vkEnvDescriptorMixerRender;

public:
  virtual void OnDeviceCreate(CEnvDescriptor &owner);
  virtual void OnDeviceDestroy();

  virtual void Copy(IEnvDescriptorRender &_in);
};

export class vkEnvDescriptorMixerRender : public IEnvDescriptorMixerRender {
public:
  virtual void Copy(IEnvDescriptorMixerRender &_in);

  virtual void Destroy();
  virtual void Clear();
  virtual void lerp(IEnvDescriptorRender *inA, IEnvDescriptorRender *inB);
};

export class vkEnvironmentRender : public IEnvironmentRender {
public:
  vkEnvironmentRender();
  virtual void Copy(IEnvironmentRender &_in);

  virtual void OnFrame(CEnvironment &env);
  virtual void OnLoad();
  virtual void OnUnload();
  virtual void RenderSky(CEnvironment &env, bool OnlyMV = false);
  virtual void RenderClouds(CEnvironment &env);
  virtual void OnDeviceCreate();
  virtual void OnDeviceDestroy();
  virtual particles_systems::library_interface const &
  particles_systems_library();
};

void vkEnvDescriptorRender::OnDeviceCreate(CEnvDescriptor &owner) {
  render_stub();
}

void vkEnvDescriptorRender::OnDeviceDestroy() { render_stub(); }

void vkEnvDescriptorRender::Copy(IEnvDescriptorRender &_in) { render_stub(); }

void vkEnvDescriptorMixerRender::Copy(IEnvDescriptorMixerRender &_in) {
  render_stub();
}

void vkEnvDescriptorMixerRender::Destroy() { render_stub(); }

void vkEnvDescriptorMixerRender::Clear() { render_stub(); }

void vkEnvDescriptorMixerRender::lerp(IEnvDescriptorRender *inA,
                                      IEnvDescriptorRender *inB) {
  render_stub();
}

vkEnvironmentRender::vkEnvironmentRender() { render_stub(); }

void vkEnvironmentRender::Copy(IEnvironmentRender &_in) { render_stub(); }

void vkEnvironmentRender::OnFrame(CEnvironment &env) { render_stub(); }

void vkEnvironmentRender::OnLoad() { render_stub(); }

void vkEnvironmentRender::OnUnload() { render_stub(); }

void vkEnvironmentRender::RenderSky(CEnvironment &env, bool OnlyMV) {
  render_stub();
}

void vkEnvironmentRender::RenderClouds(CEnvironment &env) { render_stub(); }

void vkEnvironmentRender::OnDeviceCreate() { render_stub(); }

void vkEnvironmentRender::OnDeviceDestroy() { render_stub(); }

particles_systems::library_interface const &
vkEnvironmentRender::particles_systems_library() {
  render_stub();
  // return (RImplementation.PSLibrary);
  static particles_systems::library_interface *lib = nullptr;
  return *lib;
}