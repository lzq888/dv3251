/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sys.h
* Author             : pengtao_zhang
* Version            : V0719a
* Date               : 07/19/2013  ; mm/dd/yyyy
* Description        : sys HEADER FILE.
***************************************************************************/
#ifndef _SYS_H_
#define _SYS_H_



void sys_Init(void);
void pll_Init(void);
void int_Init(void);
void sdram_Init(void);
void sdram_ClearBss(u32 *dst, u32 cnt);
void sys_show_jpeg(u8 image_index);
void sys_play_music(u8 music_index);
void sys_power_on();
void sys_power_off(u8 flag);
void powerOnCtrlInit();
void internal_ldo_Init();
void sys_close_ldo_voltage();

//=====dcin handle======
void sys_dcin_set_up();
void sys_dcin_set_down();
u32 sys_dcin_check();
void sys_dcin_start_flag_init();	//start set dcin flag, for if direct recording
u8 sys_dcin_get_start_flag();		//check if dcin start ,0: no  , 1 yes
void sys_dcin_set_start_flag(u8 flag);
//====end dcin handle=====
void sys_wdt_reset();
void sys_update_firmware(void);

#endif
