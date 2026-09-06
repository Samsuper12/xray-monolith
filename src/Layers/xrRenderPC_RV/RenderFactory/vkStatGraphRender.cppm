module;

#include "render_stub.hpp"
#include <StatGraph.h>
#include <StatGraphRender.h>
export module RenderFactory.StatGraphRender;

export class vkStatGraphRender : public IStatGraphRender {
public:
  virtual void Copy(IStatGraphRender &_in);

  virtual void OnDeviceCreate();
  virtual void OnDeviceDestroy();
  virtual void OnRender(CStatGraph &owner);
};

void vkStatGraphRender::Copy(IStatGraphRender &_in) { render_stub(); }

void vkStatGraphRender::OnDeviceCreate() { render_stub(); }

void vkStatGraphRender::OnDeviceDestroy() { render_stub(); }

void vkStatGraphRender::OnRender(CStatGraph &owner) { render_stub(); }