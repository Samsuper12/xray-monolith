module;

#include "render_stub.hpp"
#include <UISequenceVideoItem.h>

export module RenderFactory.UISequenceVideoItem;
import xr.Core;

export class vkUISequenceVideoItem : public IUISequenceVideoItem {
public:
  vkUISequenceVideoItem();
  virtual void Copy(IUISequenceVideoItem &_in);

  virtual bool HasTexture();
  virtual void CaptureTexture();
  virtual void ResetTexture();
  virtual bool video_IsPlaying();
  virtual void video_Sync(uint64_t _time);
  virtual void
  video_Play(bool looped,
             uint64_t _time = std::numeric_limits<uint64_t>::max());
  virtual void video_Stop();
};

vkUISequenceVideoItem::vkUISequenceVideoItem() { render_stub(); }

bool vkUISequenceVideoItem::HasTexture() { render_stub(); }

void vkUISequenceVideoItem::Copy(IUISequenceVideoItem &_in) { render_stub(); }

void vkUISequenceVideoItem::CaptureTexture() { render_stub(); }
void vkUISequenceVideoItem::ResetTexture() { render_stub(); }

bool vkUISequenceVideoItem::video_IsPlaying() { render_stub(); }
void vkUISequenceVideoItem::video_Sync(uint64_t _time) { render_stub(); }
void vkUISequenceVideoItem::video_Play(bool looped, uint64_t _time) {
  render_stub();
}
void vkUISequenceVideoItem::video_Stop() { render_stub(); }