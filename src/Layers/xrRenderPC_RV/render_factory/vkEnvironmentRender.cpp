#include "vkEnvironmentRender.hpp"
#include "render_stub.hpp"

static const char* filename = "vkApplicationRender";

void vkEnvDescriptorRender::OnDeviceCreate(CEnvDescriptor& owner)
{
	render_stub();
}

void vkEnvDescriptorRender::OnDeviceDestroy()
{
	render_stub();
}

void vkEnvDescriptorRender::Copy(IEnvDescriptorRender& _in)
{
	render_stub();
}

void vkEnvDescriptorMixerRender::Copy(IEnvDescriptorMixerRender& _in)
{
	render_stub();
}

void vkEnvDescriptorMixerRender::Destroy()
{
	render_stub();
}

void vkEnvDescriptorMixerRender::Clear()
{
	render_stub();
}

void vkEnvDescriptorMixerRender::lerp(IEnvDescriptorRender* inA, IEnvDescriptorRender* inB)
{
	render_stub();
}

vkEnvironmentRender::vkEnvironmentRender()
{
	render_stub();
}

void vkEnvironmentRender::Copy(IEnvironmentRender& _in)
{
	render_stub();
}

void vkEnvironmentRender::OnFrame(CEnvironment& env)
{
	render_stub();
}

void vkEnvironmentRender::OnLoad()
{
	render_stub();
}

void vkEnvironmentRender::OnUnload()
{
	render_stub();
}

void vkEnvironmentRender::RenderSky(CEnvironment& env, bool OnlyMV)
{
	render_stub();
}

void vkEnvironmentRender::RenderClouds(CEnvironment& env)
{
	render_stub();
}

void vkEnvironmentRender::OnDeviceCreate()
{
	render_stub();
}

void vkEnvironmentRender::OnDeviceDestroy()
{
	render_stub();
}

particles_systems::library_interface const& vkEnvironmentRender::particles_systems_library()
{
	render_stub();
	//return (RImplementation.PSLibrary);
	static particles_systems::library_interface* lib = nullptr;
	return *lib;
}