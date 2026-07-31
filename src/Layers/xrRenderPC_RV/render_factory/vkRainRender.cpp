#include "vkRainRender.hpp"
#include "render_stub.hpp"


vkRainRender::vkRainRender()
{
	render_stub();
}

vkRainRender::~vkRainRender()
{
	render_stub();
}

void vkRainRender::Copy(IRainRender& _in)
{
	render_stub();
}

void vkRainRender::Render(CEffect_Rain& owner)
{
	render_stub();
}

const Fsphere& vkRainRender::GetDropBounds() const
{
	render_stub();
	static Fsphere dummy;
	return dummy;
}