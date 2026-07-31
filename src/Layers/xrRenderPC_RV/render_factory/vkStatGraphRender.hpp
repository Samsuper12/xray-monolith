#pragma once

#include <StatGraph.h>
#include <StatGraphRender.h>

class vkStatGraphRender : public IStatGraphRender
{
public:
	virtual void Copy(IStatGraphRender& _in);

	virtual void OnDeviceCreate();
	virtual void OnDeviceDestroy();
	virtual void OnRender(CStatGraph& owner);
};

