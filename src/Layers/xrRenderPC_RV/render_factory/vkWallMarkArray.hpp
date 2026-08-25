#pragma once
#include <WallMarkArray.h>

// TODO: remove this. 
class vkWallMarkArray : public IWallMarkArray
{
public:
	virtual ~vkWallMarkArray();
	virtual void Copy(IWallMarkArray& _in);

	virtual void AppendMark(LPCSTR s_textures);
	virtual void clear();
	virtual bool empty();
	virtual wm_shader GenerateWallmark();
};
