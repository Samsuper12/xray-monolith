module;
#include "render_stub.hpp"
#include <StatsRender.h>

export module RenderFactory.StatRender;

export class vkStatsRender : public IStatsRender {
public:
  virtual void Copy(IStatsRender &_in);

  virtual void OutData1(CGameFont &F);
  virtual void OutData2(CGameFont &F);
  virtual void OutData3(CGameFont &F);
  virtual void OutData4(CGameFont &F);
  virtual void GuardVerts(CGameFont &F);
  virtual void GuardDrawCalls(CGameFont &F);
  virtual void SetDrawParams(IRenderDeviceRender *pRender);

private:
};

void vkStatsRender::Copy(IStatsRender &_in) { render_stub(); }

void vkStatsRender::OutData1(CGameFont &F) { render_stub(); }

void vkStatsRender::OutData2(CGameFont &F) { render_stub(); }

void vkStatsRender::OutData3(CGameFont &F) { render_stub(); }

void vkStatsRender::OutData4(CGameFont &F) { render_stub(); }

void vkStatsRender::GuardVerts(CGameFont &F) { render_stub(); }

void vkStatsRender::GuardDrawCalls(CGameFont &F) { render_stub(); }

void vkStatsRender::SetDrawParams(IRenderDeviceRender *pRender) {
  render_stub();
}