#include "vkConsoleRender.hpp"
#include "render_stub.hpp"

static const char* filename = "vkConsoleRender";
vkConsoleRender::vkConsoleRender()
{
	render_stub();
}

void vkConsoleRender::Copy(IConsoleRender& _in)
{
	render_stub();
}

void vkConsoleRender::OnRender(bool bGame)
{
	render_stub();
}