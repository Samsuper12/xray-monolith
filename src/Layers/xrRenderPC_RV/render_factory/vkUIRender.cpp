#include "vkUIRender.hpp"
#include "render_stub.hpp"
#include <LocatorAPI.h>

vkUIRender UIRenderImpl;

vkUIRender::vkUIRender() {
	render_stub();
}
void vkUIRender::CreateUIGeom()
{
	render_stub();
}

void vkUIRender::DestroyUIGeom()
{
	render_stub();
}

void vkUIRender::SetShader(IUIShader& shader)
{
	render_stub();
}

void vkUIRender::SetAlphaRef(int aref)
{
	render_stub();
}

void vkUIRender::SetScissor(Irect* rect)
{
	render_stub();
}

void vkUIRender::GetActiveTextureResolution(Fvector2& res)
{
	render_stub();
}

void vkUIRender::PushPoint(float x, float y, float z, u32 C, float u, float v)
{
	render_stub();
}

void vkUIRender::StartPrimitive(u32 iMaxVerts, ePrimitiveType primType, ePointType pointType)
{
	render_stub();
}

void vkUIRender::FlushPrimitive()
{
	render_stub();
}

LPCSTR vkUIRender::UpdateShaderName(LPCSTR tex_name, LPCSTR sh_name)
{
	string_path buff;
	NeedAttention(".ogm");
	if (FS.exist(buff, "$game_textures$", tex_name, ".ogm"))
		return "hud/movie";
	else
		return sh_name;
}

void vkUIRender::CacheSetXformWorld(const Fmatrix& M)
{
	render_stub();
}

void vkUIRender::CacheSetCullMode(CullMode)
{
	render_stub();
}