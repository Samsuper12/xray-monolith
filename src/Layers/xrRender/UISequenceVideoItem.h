#ifndef	UISequenceVideoItem_included
#define	UISequenceVideoItem_included
#pragma once

#include <limits>

class IUISequenceVideoItem
{
public:
	virtual ~IUISequenceVideoItem() { ; }
	virtual void Copy(IUISequenceVideoItem& _in) = 0;

	virtual bool HasTexture() = 0;
	virtual void CaptureTexture() = 0;
	virtual void ResetTexture() = 0;
	virtual bool video_IsPlaying() = 0;
	virtual void video_Sync(uint64_t _time) = 0;
	virtual void video_Play(bool looped, uint64_t _time = std::numeric_limits<uint64_t>::max()) = 0;
	virtual void video_Stop() = 0;
};

#endif	//	UISequenceVideoItem_included
