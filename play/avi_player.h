#ifndef	__AVI_PLAYER_H__
#define	__AVI_PLAYER_H__


typedef struct _avi_info
{
	DWORD	RIFFChunkSize;
	DWORD	hdrlChunkSize;
	DWORD	moviChunkSize;
	DWORD	idx1ChunkSize;
	DWORD	idx1Offset;

	AVIMAINHEADER		aviMainHeader;
//	AVISTREAMHEADER		videoStreamHeader;
//	AVISTREAMHEADER		audioStreamHeader;
//	BITMAPINFOHEADER	videoStreamFormat;
//	WAVEFORMATEX		audioStreamFormat;

} AVI_INFO;

typedef struct _aIndexInfo
{
	AVIINDEXENTRY	aIndex;
	int		valid;
} aIndexInfo;

typedef	struct _aFrameInfo
{
	u8	*buf_addr;
	u32	buf_size;
	int iFrameCnt;
	int	valid;
} aFrameInfo;

extern AVI_INFO g_AVIFileInfo;

extern aFrameInfo g_VideoFrameBuf;
extern aFrameInfo g_AudioFrameBuf;
extern aFrameInfo g_DispFrameBuf;


void avi_Player(FIL *fp);


#endif

