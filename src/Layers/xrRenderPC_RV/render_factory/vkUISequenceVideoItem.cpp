#include "vkUISequenceVideoItem.hpp"
#include "render_stub.hpp"

vkUISequenceVideoItem::vkUISequenceVideoItem() { render_stub(); }

bool vkUISequenceVideoItem::HasTexture() { render_stub(); }

void vkUISequenceVideoItem::Copy(IUISequenceVideoItem &_in) { render_stub(); }

void vkUISequenceVideoItem::CaptureTexture() { render_stub(); }
void vkUISequenceVideoItem::ResetTexture() { render_stub(); }

bool vkUISequenceVideoItem::video_IsPlaying() { render_stub(); }
void vkUISequenceVideoItem::video_Sync(uint64_t _time) { render_stub(); }
void vkUISequenceVideoItem::video_Play(bool looped, uint64_t _time) {render_stub();}
void vkUISequenceVideoItem::video_Stop() { render_stub(); }