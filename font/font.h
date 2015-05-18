/******************** (C) COPYRIGHT 2013 BUILDWIN ************************/
#ifndef _FONT_H_
#define _FONT_H_


#define MAX_FONT_NUMS	40
typedef struct _SegIndexInfo
{
	u8 x;						// 字模的x值，字符宽（[0x00],<BE>）
	u8 y;						// 字模的y值，字符高（[0x01],<BE>）
	u16 length;					// 字模的字符点阵数据长度（[0x02],<BE>），Byte为单位
	u32 BaseAddr;				// 字模的字符点阵数据起始地址（[0x04],<BE>），相对于Seg[0]地址
} FontIndexInfo,IconIndexInfo;

typedef struct _SegInfo
{
	u32 UnicoValue;					// unicode value
	u32 StartAddr;					// 
} FontSegInfo;

typedef struct _FontLibrary
{
	u32 NumOfUnicode;				// unicode num
	u32 UniAddrOffset;				// unicode addr
}FontLibrary ;


typedef struct _FontGroup
{
	u8 num;
	u32 handleflag;
	u16 fontx;
	FontIndexInfo FontInfo[MAX_FONT_NUMS];
}FontGroup ;

typedef struct
{
	u16 x;					// 图标宽
	u16 y;					// 图标高
	u32 bpp;					// 保留
	u32 addr;					// 图标起始地址
	u32 length;					// 图标数据长度
} ICON_FILE_HEAD;

void FontInit(void);
void GetUnicodeIndex(u16 unicode, FontIndexInfo *pFont);
void UnicodeInfoUpdate(OSDInf *pOsdInfo,FontIndexInfo *pFont,u16 xs,u16 ys,u8 foreColor,u8 backColor,u8 flag,u32 language_handle);
void UnicodeInfoUpdate_EX(OSDInf *pOsdInfo,FontIndexInfo *pFont,u16 startx,u16 starty,u16 xs,u16 ys,u16 w,u16 h,u8 foreColor,u8 backColor,u8 flag,u32 language_handle);
void GetStrFontInfo(u8 *pString, FontGroup *pFontGroup );
void DotMatrixIconDisplay(u8 icon_addr,u16 x,u16 y,u8 forecolor,u8 backcolor);
void DisplayUnicodeStr(OSDInf *pOSDInf,u8 *pString,u16 startx,u16 starty,u16 w,u16 h,u8 forecolor, u8 backcolor,u8 align);
void DisplayUnicodeStr_ToTempBuf(OSDInf *pOSDInf,u8 *pString,u16 startx,u16 starty,u16 offset_x,u16 offset_y,u16 w,u16 h,u8 forecolor, u8 backcolor,u8 align);
void DisplayUnicodeStr_EXT(OSDInf *pOSDInf,u8 *pString,u16 startx,u16 starty,u16 offset_x,u16 offset_y,u16 w,u16 h,u8 forecolor, u8 backcolor,u8 align);
#endif
