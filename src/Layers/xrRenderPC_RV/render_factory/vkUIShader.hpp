#pragma once
#include <UIShader.h>

class vkUIShader : public IUIShader
{
	friend class vkUIRender;
	friend class vkDebugRender;
	friend class vkWallMarkArray;
	friend class CRender;
public:
	virtual ~vkUIShader() { ; }
	virtual void Copy(IUIShader& _in);
	virtual void create(LPCSTR sh, LPCSTR tex = 0);
	virtual bool inited();
	virtual void destroy();
};

