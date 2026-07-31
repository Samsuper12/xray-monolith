#pragma once

#include <ApplicationRender.h>

class vkApplicationRender : public IApplicationRender
{
public:
	virtual void Copy(IApplicationRender& _in);

	virtual void LoadBegin();
	virtual void destroy_loading_shaders();
	virtual void setLevelLogo(LPCSTR pszLogoName);
	virtual void load_draw_internal(CApplication& owner);
	//	?????
	virtual void KillHW();
};
