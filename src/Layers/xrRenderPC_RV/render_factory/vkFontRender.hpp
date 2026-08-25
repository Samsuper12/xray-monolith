#pragma once

#include <FontRender.h>
#include <memory>
#include "utils/vkUtil.hpp"

// TODO: use quads
// TODO: font antialiasing
// TODO: vkCmdDrawIndirect
// TODO: generate mipmaps

class vkFontRender : public IFontRender
{
public:
	vkFontRender();
	virtual ~vkFontRender();

	virtual void Initialize(LPCSTR cShader, LPCSTR cTexture);
	virtual void OnRender(CGameFont& owner);

private:
	std::shared_ptr<ShaderPass> shaderPass;
	std::shared_ptr<AllocatedImage> texture;
	
	AllocatedBuffer vertexBuffer;
	VkDeviceAddress vertexBufferAddress;
	size_t vertexBufferSize;
	uint64_t vertexCursor;
	uint64_t vertexIndex;
	uint64_t currentFrame;
};