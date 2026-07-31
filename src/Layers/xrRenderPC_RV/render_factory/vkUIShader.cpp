#include "vkUIShader.hpp"
#include "render_stub.hpp"

static const char* filename = "vkUIShader";


void vkUIShader::Copy(IUIShader& _in)
{
	*this = *((vkUIShader*)&_in);
}

void vkUIShader::create(LPCSTR sh, LPCSTR tex)
{
	render_stub();
	//hShader.create(sh, tex);
}

void vkUIShader::destroy()
{
	render_stub();
	//hShader.destroy();
}

bool vkUIShader::inited() { render_stub();}
