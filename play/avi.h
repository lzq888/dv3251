#ifndef __AVI_H__
#define	__AVI_H__

#define AVIF_HASINDEX 			0x10
#define AVIF_MUSTUSEINDEX  		0x20
#define AVIF_ISINTERLEAVED		0x100
#define AVIF_WASCAPTUREFILE	0x10000
#define AVIF_COPYRIGHTED		0x20000
#define AVI_KNOWN_FLAGS 		0x30130



typedef struct {
	DWORD ckid;
	DWORD dwFlags;
	DWORD dwChunkOffset;
	DWORD dwChunkLength;
} AVIINDEXENTRY;

typedef struct {
  DWORD  fcc;//avih
  DWORD  cb;//size
  DWORD  dwMicroSecPerFrame;
  DWORD  dwMaxBytesPerSec;
  DWORD  dwPaddingGranularity;
  DWORD  dwFlags;
  DWORD  dwTotalFrames;
  DWORD  dwInitialFrames;
  DWORD  dwStreams;
  DWORD  dwSuggestedBufferSize;
  DWORD  dwWidth;
  DWORD  dwHeight;
  DWORD  dwReserved[4];
} AVIMAINHEADER;

typedef struct {
DWORD  fcc;//4//strh
DWORD  cb;//4//size
DWORD  fccType;//4//vids|auds
DWORD  fccHandler;//4
DWORD  dwFlags;//4
WORD  wPriority;//2
WORD  wLanguage;//2
DWORD dwInitialFrames;//4
DWORD dwScale;//4
DWORD dwRate; //4/* dwRate / dwScale == samples/second */
DWORD dwStart;//4
DWORD dwLength; //4/* In units above... */
DWORD dwSuggestedBufferSize;//4
DWORD dwQuality;//4
DWORD dwSampleSize;//4
  struct {
    short int left;//2
    short int top;//2
    short int right;//2
    short int bottom;//2
  } rcFrame;

} AVISTREAMHEADER;

typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  DWORD  biWidth;//4
  DWORD  biHeight;//4
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  DWORD  biXPelsPerMeter;
  DWORD  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER;

typedef struct {
  WORD  wFormatTag;
  WORD  nChannels;
  DWORD nSamplesPerSec;
  DWORD nAvgBytesPerSec;
  WORD  nBlockAlign;
  WORD  wBitsPerSample;
  WORD  cbSize;
} WAVEFORMATEX;


typedef struct {
	DWORD dwFourCC;
	DWORD dwSize;
} CHUNK;

typedef struct{ 
	DWORD fcc;
	DWORD cb;
	DWORD fcctype;
} LIST;


typedef struct {
LIST riff;				//{"RIFF",dwsize,"AVI "};
LIST hdrl;			//{"LIST",dwsize,"hdr1"};
AVIMAINHEADER avih;	//aviheader
LIST strl_v;						//strl vids
AVISTREAMHEADER strh_v;			//stream vids
CHUNK strf_v;					//vids stream info
BITMAPINFOHEADER bitmapinfo;
LIST strl_a;						//strl auds
AVISTREAMHEADER strh_a;			//stream auds
CHUNK strf_a;					//auds stream info
WAVEFORMATEX  wavinfo;	
CHUNK junk;	
}AVIFILEHEADER;



//
//
//LIST={"RIFF",dwsize,"AVI "};
//LIST={"LIST",dwsize,"hdr1"};
//AVIMAINHEADER;
//LIST={"LIST",dwsize,"strl"};//vids
//AVISTREAMHEADER
//"strf"+size+BITMAPINFOHEADER
//"strd"+dummy
//LIST={"LIST",dwsize,"strl"};//auds
//AVISTREAMHEADER
//"strf"+size+WAVEFORMATEX
//"strd"+dummy
//
//
//LIST={"LIST",dwsize,"movi"};<-----512 boundary
//
//[CHUNK][CHUNK].........
//



#endif

