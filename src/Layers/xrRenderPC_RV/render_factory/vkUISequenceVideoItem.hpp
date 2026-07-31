#pragma once

#include <UISequenceVideoItem.h>
#include <limits>

class vkUISequenceVideoItem : public IUISequenceVideoItem
{
public:
	vkUISequenceVideoItem();
	virtual void Copy(IUISequenceVideoItem& _in);

	virtual bool HasTexture();
	virtual void CaptureTexture();
	virtual void ResetTexture();
	virtual bool video_IsPlaying();
	virtual void video_Sync(uint64_t _time);
	virtual void video_Play(bool looped, uint64_t _time = std::numeric_limits<uint64_t>::max());
	virtual void video_Stop();
};

