module;

#include "render_stub.hpp"
#include <RainRender.h>

export module RenderFactory.RainRender;

export class vkRainRender : public IRainRender {
public:
  vkRainRender();
  virtual ~vkRainRender();
  virtual void Copy(IRainRender &_in);

  virtual void Render(CEffect_Rain &owner);

  virtual const Fsphere &GetDropBounds() const;
};

vkRainRender::vkRainRender() { render_stub(); }

vkRainRender::~vkRainRender() { render_stub(); }

void vkRainRender::Copy(IRainRender &_in) { render_stub(); }

void vkRainRender::Render(CEffect_Rain &owner) { render_stub(); }

const Fsphere &vkRainRender::GetDropBounds() const {
  render_stub();
  static Fsphere dummy;
  return dummy;
}