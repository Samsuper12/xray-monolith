module;

#include "render_stub.hpp"
#include <ThunderboltRender.h>

export module RenderFactory.ThunderboltRender;

export class vkThunderboltRender : public IThunderboltRender {
public:
  vkThunderboltRender();
  virtual ~vkThunderboltRender();

  virtual void Copy(IThunderboltRender &_in);

  virtual void Render(CEffect_Thunderbolt &owner);

private:
};

vkThunderboltRender::vkThunderboltRender() { render_stub(); }

vkThunderboltRender::~vkThunderboltRender() { render_stub(); }

void vkThunderboltRender::Copy(IThunderboltRender &_in) { render_stub(); }

void vkThunderboltRender::Render(CEffect_Thunderbolt &owner) { render_stub(); }