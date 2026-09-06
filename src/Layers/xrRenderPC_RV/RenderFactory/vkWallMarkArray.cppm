module;
#include "render_stub.hpp"
#include <WallMarkArray.h>
export module RenderFactory.WallMarkArray;

export class vkWallMarkArray : public IWallMarkArray {
public:
  virtual ~vkWallMarkArray();
  virtual void Copy(IWallMarkArray &_in);

  virtual void AppendMark(LPCSTR s_textures);
  virtual void clear();
  virtual bool empty();
  virtual wm_shader GenerateWallmark();
};

vkWallMarkArray::~vkWallMarkArray() { render_stub(); }

void vkWallMarkArray::Copy(IWallMarkArray &_in) { render_stub(); }

void vkWallMarkArray::AppendMark(LPCSTR s_textures) { render_stub(); }

void vkWallMarkArray::clear() { render_stub(); }

bool vkWallMarkArray::empty() {
  render_stub();
  return true;
}

wm_shader vkWallMarkArray::GenerateWallmark() {
  render_stub();
  return wm_shader();
}