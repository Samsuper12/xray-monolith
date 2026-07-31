#pragma once

#include <FontRender.h>

class vkFontRender : public IFontRender
{
public:
	vkFontRender();
	virtual ~vkFontRender();

	virtual void Initialize(LPCSTR cShader, LPCSTR cTexture);
	virtual void OnRender(CGameFont& owner);
};