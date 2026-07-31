#pragma once

#include <LensFlareRender.h>

class vkFlareRender : public IFlareRender
{
public:
	virtual void Copy(IFlareRender& _in);

	virtual void CreateShader(LPCSTR sh_name, LPCSTR tex_name);
	virtual void DestroyShader();
};

class vkLensFlareRender : public ILensFlareRender
{
public:
	virtual void Copy(ILensFlareRender& _in);

	virtual void Render(CLensFlare& owner, BOOL bSun, BOOL bFlares, BOOL bGradient);

	virtual void OnDeviceCreate();
	virtual void OnDeviceDestroy();
};
