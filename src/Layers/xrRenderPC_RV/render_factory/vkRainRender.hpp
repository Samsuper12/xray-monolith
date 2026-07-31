#pragma once

#include <RainRender.h>

class vkRainRender : public IRainRender
{
public:
	vkRainRender();
	virtual ~vkRainRender();
	virtual void Copy(IRainRender& _in);

	virtual void Render(CEffect_Rain& owner);

	virtual const Fsphere& GetDropBounds() const;
};

