module;

#include "render_stub.hpp"
#include <ConsoleRender.h>
export module RenderFactory.ConsoleRender;

export class vkConsoleRender : public IConsoleRender {
public:
  vkConsoleRender();

  virtual void Copy(IConsoleRender &_in);
  virtual void OnRender(bool bGame);
};

vkConsoleRender::vkConsoleRender() { render_stub(); }

void vkConsoleRender::Copy(IConsoleRender &_in) { render_stub(); }

void vkConsoleRender::OnRender(bool bGame) { render_stub(); }