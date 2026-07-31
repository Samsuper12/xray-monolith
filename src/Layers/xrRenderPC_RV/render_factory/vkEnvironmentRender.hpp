#pragma once
#include <EnvironmentRender.h>


class vkEnvDescriptorRender : public IEnvDescriptorRender
{
	friend class vkEnvDescriptorMixerRender;
public:
	virtual void OnDeviceCreate(CEnvDescriptor& owner);
	virtual void OnDeviceDestroy();

	virtual void Copy(IEnvDescriptorRender& _in);
};

class vkEnvDescriptorMixerRender : public IEnvDescriptorMixerRender
{
public:
	virtual void Copy(IEnvDescriptorMixerRender& _in);

	virtual void Destroy();
	virtual void Clear();
	virtual void lerp(IEnvDescriptorRender* inA, IEnvDescriptorRender* inB);
};



class vkEnvironmentRender : public IEnvironmentRender
{
public:
	vkEnvironmentRender();
	virtual void Copy(IEnvironmentRender& _in);

	virtual void OnFrame(CEnvironment& env);
	virtual void OnLoad();
	virtual void OnUnload();
	virtual void RenderSky(CEnvironment& env, bool OnlyMV = false);
	virtual void RenderClouds(CEnvironment& env);
	virtual void OnDeviceCreate();
	virtual void OnDeviceDestroy();
	virtual particles_systems::library_interface const& particles_systems_library();
};