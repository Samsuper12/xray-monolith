#include "vkLensFlareRender.hpp"
#include "render_stub.hpp"

static const char* filename = "vkFlareRender";
void vkFlareRender::Copy(IFlareRender& _in)
{
	render_stub();
}

void vkFlareRender::CreateShader(LPCSTR sh_name, LPCSTR tex_name)
{
	render_stub();
}

void vkFlareRender::DestroyShader()
{
	render_stub();
}

void vkLensFlareRender::Copy(ILensFlareRender& _in)
{
	render_stub();
}

void vkLensFlareRender::Render(CLensFlare& owner, BOOL bSun, BOOL bFlares, BOOL bGradient)
{
	render_stub();
}

void vkLensFlareRender::OnDeviceCreate()
{
	render_stub();
}

void vkLensFlareRender::OnDeviceDestroy()
{
	render_stub();
}