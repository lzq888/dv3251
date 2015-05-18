/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : play_Picture.c
* Author             : pengtao_zhang
* Version            : V0829a
* Date               : 08/29/2013
* Description        : This file provides all the picture play firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================

void play_Picture(FIL *fp)
{
	u32 readed;
	u32 u32DisBuf_Addr;

	deg_Printf("play picture start\n");
	f_lseek(fp, 0);
	f_read(fp,(u8 *)JPEG_BUFFER_START_ADDRESS,fp->fsize,(uint *)(&readed));

	u32DisBuf_Addr = REG32(LCDCON46) + DISPLAY_SIZE;
	if(u32DisBuf_Addr >= (DISPLAY_ADDR + DISPLAY_SIZE*3))
		u32DisBuf_Addr = DISPLAY_ADDR;
	
	mjpdec_Start((u8 *)JPEG_BUFFER_START_ADDRESS,(u8 *)u32DisBuf_Addr);
	deg_Printf("jpdec...\n");
	while(jpdec_flag==0);
	deg_Printf("jpeg dec  finish\n");

	if(task_ctl.work_sta == TASK_PHOTO)
	{
		if(sys_ctl.fast_view)
		{
			u32 lcd_con_reg_save = REG32(LCDCON0);
			DIS_OSD1();
			DIS_OSD2();
			DIS_OSD3();
			lcd_set_panel_colour(0,0,0);
			#if(0 == LCD_MCU)
				waittingLcdFrameEnd();
				REG32(LCDCON0) &= ~(BIT(0)|BIT(6)|BIT(11));
				REG32(LCDCON46) = u32DisBuf_Addr;
				if(u32jpegSize_H == 1280)
					tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
				else if(u32jpegSize_H == 640)
					tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
				else if((u32jpegSize_H == 1920) | (u32jpegSize_H == JPEG_SCALE_SIZE_H))
					tvout_display_set(0,0,u32jpegSize_H/4,u32jpegSize_H/4,u32jpegSize_V/4,tvout_get_w(),tvout_get_h());
				else
					tvout_display_set(0,0,u32jpegSize_H,u32jpegSize_H,u32jpegSize_V,tvout_get_w(),tvout_get_h());

				REG32(LCDCON0) = lcd_con_reg_save;
				REG32(LCDCON0) &= ~(BIT(7)|BIT(11));	//write back disable
				EN_OSD1();	
				REG32(LCDCON0) |= (BIT(0)|BIT(6));

			#else
			
				REG32(LCDCON0) &= ~(BIT(6)|BIT(11));
				waittingLcdFrameEnd();
				REG32(LCDCON46) = u32DisBuf_Addr;
				if(u32jpegSize_H == 1280)
					tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
				else if(u32jpegSize_H == 640)
					tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
				else if((u32jpegSize_H == 1920) | (u32jpegSize_H == JPEG_SCALE_SIZE_H))
					tvout_display_set(0,0,u32jpegSize_H/4,u32jpegSize_H/4,u32jpegSize_V/4,tvout_get_w(),tvout_get_h());
				else
					tvout_display_set(0,0,u32jpegSize_H,u32jpegSize_H,u32jpegSize_V,tvout_get_w(),tvout_get_h());


				waittingLcdFrameEnd();
				REG32(LCDCON0) = lcd_con_reg_save;
				REG32(LCDCON0) &= ~(BIT(7)|BIT(11));	//write back disable
				EN_OSD1();	
				REG32(LCDCON0) |= (BIT(6));
			#endif
			
		}
	}
    else
	{
		u32 lcd_con_reg_save = REG32(LCDCON0);
		DIS_OSD1();
		DIS_OSD2();
		DIS_OSD3();
		lcd_set_panel_colour(0,0,0);
		#if(0 == LCD_MCU)
			waittingLcdFrameEnd();
			REG32(LCDCON0) &= ~(BIT(0)|BIT(6));
			REG32(LCDCON46) = u32DisBuf_Addr;
			if(u32jpegSize_H == 1280)
				tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
			else if(u32jpegSize_H == 640)
				tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
			else if((u32jpegSize_H == 1920) | (u32jpegSize_H == JPEG_SCALE_SIZE_H))
				tvout_display_set(0,0,u32jpegSize_H/4,u32jpegSize_H/4,u32jpegSize_V/4,tvout_get_w(),tvout_get_h());
			else
				tvout_display_set(0,0,u32jpegSize_H,u32jpegSize_H,u32jpegSize_V,tvout_get_w(),tvout_get_h());

			REG32(LCDCON0) = lcd_con_reg_save;
			REG32(LCDCON0) |= (BIT(0)|BIT(6));
		#else
			REG32(LCDCON0) &= ~(BIT(6));
			waittingLcdFrameEnd();
			REG32(LCDCON46) = u32DisBuf_Addr;
			if(u32jpegSize_H == 1280)
				tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
			else if(u32jpegSize_H == 640)
				tvout_display_set(0,0,u32jpegSize_H/2,u32jpegSize_H/2,u32jpegSize_V/2,tvout_get_w(),tvout_get_h());
			else if((u32jpegSize_H == 1920) | (u32jpegSize_H == JPEG_SCALE_SIZE_H))
				tvout_display_set(0,0,u32jpegSize_H/4,u32jpegSize_H/4,u32jpegSize_V/4,tvout_get_w(),tvout_get_h());
			else
				tvout_display_set(0,0,u32jpegSize_H,u32jpegSize_H,u32jpegSize_V,tvout_get_w(),tvout_get_h());
			waittingLcdFrameEnd();
			REG32(LCDCON0) = lcd_con_reg_save;
			REG32(LCDCON0) |= (BIT(6));
		#endif
    }
	deg_Printf("display picture end\n");
}

