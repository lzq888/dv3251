/******************** (C) COPYRIGHT 2013 BUILDWIN ************************/
#ifndef _OSD_H_
#define _OSD_H_

#define OSDICON_DISPLAY_DISABLE		0
#define OSDICON_DISPLAY_ENABLE		1

#define OSD1_LUT_ADR  0x10080000
#define OSD2_LUT_ADR  0x10080400
#define OSD3_LUT_ADR  0x10080800


#define EN_OSD1()        REG32(LCDCON0) |= BIT(3)
#define EN_OSD2()        REG32(LCDCON0) |= BIT(4) 
#define EN_OSD3()        REG32(LCDCON0) |= BIT(5) 
#define DIS_OSD1()       REG32(LCDCON0) &= ~BIT(3)
#define DIS_OSD2()       REG32(LCDCON0) &= ~BIT(4)
#define DIS_OSD3()       REG32(LCDCON0) &= ~BIT(5)

#define OSD1_useColorAlpha()	REG32(LCDCON37) |= BIT(8)
#define OSD2_useColorAlpha()	REG32(LCDCON38) |= BIT(8)
#define OSD3_useColorAlpha()	REG32(LCDCON39) |= BIT(8)
#define OSD1_useLayerAlpha()	REG32(LCDCON37) &= ~BIT(8)
#define OSD2_useLayerAlpha()	REG32(LCDCON38) &= ~BIT(8)
#define OSD3_useLayerAlpha()	REG32(LCDCON39) &= ~BIT(8)

typedef struct
{
	u16 xstart;	     //起始x坐标
	u16 xwidth;	     //宽度
	u16 ystart;	     //起始y坐标
	u16 yheight;	 //高度
	u8  alpha;	     //透明度
	u32 sdramaddr;	 //资源sdram物理地址
	u8 osd_num;
}OSDInf;

extern OSDInf OSD3Inf,OSD2Inf,OSD1Inf;
extern u32 OSD_changeFlag;

typedef struct
{
	u32 xwidth;
	u32 yheight;
	u32 dataoffset;
}OSDSOURCE_INF;

void OSDInfInit(void);
void lcd_UpdateOsdLUT(u8 osdnum,u32 sourceindex);
void lcd_FillFullOsdData(OSDInf *pOsdInfo, u8 ColorIndex);
void lcd_FillPartOsdData(OSDInf *pOsdInfo, u8 ColorIndex, u16 x, u16 y, u16 xwidth, u16 yheight);
void lcd_UpdatePartOsdData(OSDInf *pOsdInfo, u32 sourcenum, u16 x, u16 y);
void lcd_UpdatePartOsdData_SDRAM(OSDInf *pOsdInfo, u32 sdramaddress, u16 x, u16 y, u16 xwidth, u16 yheight);
void lcd_OsdInit(u8 osdnum);
u8 OSDInit(OSDInf *pOsdInf,u16 xstart,u16 ystart ,u16 xwidth,u16 yheight,u8 alpha,u8 colorindex);
void  osd_OsdData_load(u32 sourceindex);
void lcd_UpdateOsdIconData_FromSdram(OSDInf *pOsdInfo,u32 sourcenum, u16 x, u16 y);
void lcd_UpdateOsdIconData_FromSdram_EX(OSDInf *pOsdInfo,u32 sourcenum, u16 x, u16 y);
void lcd_UpdateOsdIconData_FromSdramToOsdBuf(OSDInf *pOsdInfo,u32 SdramAddr, u16 x, u16 y,u16 w,u16 h);
void lcd_Clean_TempOsdBuf(u32 addr, u16 w, u16 h);
#endif
