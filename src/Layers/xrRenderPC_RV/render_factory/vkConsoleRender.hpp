
#pragma once

#include <ConsoleRender.h>

class vkConsoleRender : public IConsoleRender
{
public:
	vkConsoleRender();

	virtual void Copy(IConsoleRender& _in);
	virtual void OnRender(bool bGame);
};
