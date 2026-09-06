module;

#include "render_stub.hpp"
#include <ThunderboltDescRender.h>
export module RenderFactory.ThunderboltDescRender;

class IRender_DetailModel;

export class vkThunderboltDescRender : public IThunderboltDescRender {
public:
  virtual void Copy(IThunderboltDescRender &_in);

  virtual void CreateModel(LPCSTR m_name);
  virtual void DestroyModel();
  // private:
public:
  IRender_DetailModel *l_model;
};

void vkThunderboltDescRender::Copy(IThunderboltDescRender &_in) {
  render_stub();
}

void vkThunderboltDescRender::CreateModel(LPCSTR m_name) { render_stub(); }

void vkThunderboltDescRender::DestroyModel() { render_stub(); }
