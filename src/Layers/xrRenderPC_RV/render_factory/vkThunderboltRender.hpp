#pragma once
#include <ThunderboltRender.h>

class vkThunderboltRender : public IThunderboltRender
{
public:
	vkThunderboltRender();
	virtual ~vkThunderboltRender();

	virtual void Copy(IThunderboltRender& _in);

	virtual void Render(CEffect_Thunderbolt& owner);
private:

};