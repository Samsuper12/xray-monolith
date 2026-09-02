#ifndef tntQAVIH
#define tntQAVIH

#if 0

#include <math.h>

//#include "tntTimer.h"
//#include "vfw.h"
//#include "mmsystem.h"

// replaced with standard AVIIF_KEYFRAME
//rr #define AVIINDEX_ISKEYFRAME 0x10 // ключевой кадр

// reverse enginered AVI index v.1 format
/*struct AviIndex {

 uint32_t dwChunkType; // chunk type, i.e. '##dc' - DIB compressed
 uint32_t dwFlags; // key-frame etc.
 uint32_t dwOffset; // sub-chunk offset from the begining of the LIST chunk
 uint32_t dwLenght; // chunk lenght

 };

 typedef struct {
 FOURCC fccType;
 FOURCC fccHandler;
 uint32_t dwFlags;
 uint32_t dwPriority;
 uint32_t dwInitialFrames;
 uint32_t dwScale;
 uint32_t dwRate;
 uint32_t dwStart;
 uint32_t dwLength;
 uint32_t dwSuggestedBufferSize;
 uint32_t dwQuality;
 uint32_t dwSampleSize;
 RECT rcFrame;
 } AVIStreamHeader;
 */
typedef struct
{
	FOURCC fccType;
	FOURCC fccHandler;
	uint32_t dwFlags;
	uint32_t dwPriority;
	uint32_t dwInitialFrames;
	uint32_t dwScale;
	uint32_t dwRate;
	uint32_t dwStart;
	uint32_t dwLength;
	uint32_t dwSuggestedBufferSize;
	uint32_t dwQuality;
	uint32_t dwSampleSize;

	struct
	{
		unsigned short left;
		unsigned short top;
		unsigned short right;
		unsigned short bottom;
	};

	// RECT rcFrame; - лажа в MSDN
} AVIStreamHeaderCustom;

class ENGINE_API CAviPlayerCustom
{
protected:
	CAviPlayerCustom* alpha;
protected:
	AVIINDEXENTRY* m_pMovieIndex;
	unsigned char* m_pMovieData;
	HIC m_aviIC;
	unsigned char* m_pDecompressedBuf;

	BITMAPINFOHEADER m_biOutFormat;
	BITMAPINFOHEADER m_biInFormat;

	float m_fRate; // стандартная скорость, fps
	float m_fCurrentRate; // текущая скорость, fps

	uint32_t m_dwFrameTotal;
	uint32_t m_dwFrameCurrent;
	u32 m_dwFirstFrameOffset;


	uint32_t CalcFrame();

	BOOL DecompressFrame(uint32_t dwFrameNum);
	void PreRoll(uint32_t dwFrameNum);

public:
	CAviPlayerCustom();
	~CAviPlayerCustom();

	uint32_t m_dwWidth, m_dwHeight;

	void GetSize(uint32_t* dwWidth, uint32_t* dwHeight);

	BOOL Load(char* fname);
	BOOL GetFrame(unsigned char** pDest);

	BOOL NeedUpdate() { return CalcFrame() != m_dwFrameCurrent; }
	int32_t SetSpeed(int32_t nPercent);
};
#endif

#endif