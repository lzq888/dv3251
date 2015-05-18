#ifndef __TVOUT_H__
#define __TVOUT_H__
//---------------------------------------------------------------------------//
// Define Macro
//---------------------------------------------------------------------------//
		

//PAL
#define PAL_DEFINITION	0	//0:720*576	1:702*576  //720*576 is the standard definition.


enum 
{
	TVOUT_MODE_LCD = 0,
	TVOUT_MODE_NTSC,
	TVOUT_MODE_PAL,
};


#define TVDAC_CTRL		0
#define TVDAC_DATA		1
#define TVDAC_GAIN		2


#define TVVIDEO_DATA_ADR3  0x20f00000

extern u32 enlager_offset_len;
//=======for outside call=======
void tvout_lcd_en();
void tvout_lcd_disen();  
void tv_disable(void);
void tvout_set_cur_mode(u8 type);							//=set the output type: TVOUT_MODE_LCD,TVOUT_MODE_NTSC,TVOUT_MODE_PAL
u32 tvout_get_cur_mode();									//return:TVOUT_MODE_LCD,TVOUT_MODE_NTSC,TVOUT_MODE_PAL

//==========================================
//src_x,src_y为YUV buf 的起点
//src_span,数据源的宽
//src_w,为YUV buf 的宽
//src_h,为YUV buf 的高
//YUV buf有2种，1：RGB2YUV ，2：摄像头输出YUV ,根据当前YUV的大小设置

//dst_w,为TVOUT 输出 的宽
//dst_h,为TVOUT 输出 的高
//tvout mode 有三种，1：lcd ,2: ntsc ,3:pal  分别对应不同模式的输出大小设置。
//==========================================
void tvout_display_set(int src_x,int src_y,int src_span, int src_w, int src_h,int dst_w,int dst_h);
u32 tvout_get_w();
u32 tvout_get_h();

void tvout_test();		//call this for test lcd ,ntsc ,pal output
void tvout_Change_dis_size(u8 factor, bool updateFlag);
void tvout_Change_display(void);
#endif