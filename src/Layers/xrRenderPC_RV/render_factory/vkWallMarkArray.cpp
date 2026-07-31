#include "vkWallMarkArray.hpp"
#include "render_stub.hpp"


vkWallMarkArray::~vkWallMarkArray()
{
	render_stub();
}

void vkWallMarkArray::Copy(IWallMarkArray& _in)
{
	render_stub();
}

void vkWallMarkArray::AppendMark(LPCSTR s_textures)
{
	render_stub();
}

void vkWallMarkArray::clear()
{
	render_stub();
}

bool vkWallMarkArray::empty()
{
	render_stub();
	return true;
}

wm_shader vkWallMarkArray::GenerateWallmark()
{
	render_stub();
	return wm_shader();
}