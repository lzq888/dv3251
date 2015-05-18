/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : menu_setting.h
* Author             : pengtao_zhang
* Version            : V0304a
* Date               : 03/04/2014  ;mm/dd/yyyy
* Description        : menu setting header file 
***************************************************************************/
#ifndef _MENU_SETTING_H_
#define _MENU_SETTING_H_



#define SPI_PARAM_PAGE          1                           //ÃÃÂ²ÃÃÃ½PageÃÃ½Â£Â¬ÃÂ»ÃÂ§Â³Ã1
#define SPI_PARAM_LEN           (256 * SPI_PARAM_PAGE)      //ÃÃÂ²ÃÃÃ½Â³Â¤Â¶Ã
#define SPI_PARAM_VLEN          (SPI_PARAM_LEN - 4)         //ÃÃÃÂ§Â²ÃÃÃ½Â³Â¤Â¶Ã
#define SPI_PARAM_FLAG          (SPI_PARAM_LEN - 4)         //Â±ÃªÃÂ¾ÂµÃÃÂ»ÃÃ
#define SPI_PARAM_SIG           0x3250                      //Â±ÃªÃÂ¾Â¡Â£Â¿ÃÃÃÃÃÃÃÂ°Ã¦Â±Â¾Â¸Ã¼ÃÃÂ¡Â£ÃÂ¬ÃÂ±ÃÃÃÃCRCÂµÃÂ³ÃµÃÂµ
#define SPI_PARAM_BASE          (seg_info.param_start>>8)   //Â¿Ã©ÃÃ°ÃÂ¼
#define SPI_PARAM_BLOCK         16                          //Â¿Ã©Â´Ã³ÃÂ¡

#define PARAM_JPEG_VIDEO_SIZE             0        //Â·ÃÂ±Ã¦ÃÃ  1byte
#define PARAM_CRC_RECORD                  1        //ÃÂ­Â»Â·ÃÂ¼ÃÃ±      1byte
#define PARAM_MOVING_DETECT               2        //ÃÃÂ¶Â¯ÃÃ¬Â²Ã¢      1byte
#define PARAM_RECORD_VOICE                3        //ÃÂ¼ÃÃ±ÃÃ¹ÃÃ´  1byte
#define PARAM_VIDEO_TIME_INFO_EN          4        //ÃÂ¼ÃÃ±ÃÂµÃÂ³ÃÂ±Â¼Ã¤ÃÂ®ÃÂ¡  1byte
#define PARAM_VIDEO_NIGHT_LINGHT          5        //
#define PARAM_GSENSOR_SENSTIVITY          6 
#define PARAM_JPEG_PICTURE_SIZE           7        //Â·ÃÂ±Ã¦ÃÃ  1byte
#define PARAM_FAST_VIEW                   8        //Â¿Ã¬ÃÃÃÂ¤ÃÃ  1byte
#define PARAM_PICTURE_TIME_INFO_EN        9        //ÃÃÃÃÃÂµÃÂ³ÃÂ±Â¼Ã¤ÃÂ®ÃÂ¡  1byte
#define PARAM_POWEROFF                    10        //ÃÃÂ¶Â¯Â¹ÃÂ»Ãº  1byte
#define PARAM_LANGUAGE                    11       //ÃÃ¯ÃÃ  1byte
//#define PARAM_LIGHT_FREQ                  12       //Â¹Ã¢ÃÂ´ÃÂµÃÃ  1byte
#define PARAM_BACKLIGHT                   12       //Â±Â³Â¹Ã¢ÃÃÃÂ±  1byte
#define PARAM_VIDEO_ROTATE                13       //ÃÃÃÂ»ÃÃ½ÃÂª  1byte
#define PARAM_TV_MODE				 	  14
#define PARAM_BEEP_STATUS				  15		//Â°Â´Â¼Ã¼ÃÃ¹ÃÃ´
#define	PARAM_USB_MODE					  16
#define PARAM_TAKE_PIC_NUMS				  17

#define MAX_JPEG_VIDEO_SIZE        2
#define MAX_CRC_RECORD             3
#define MAX_MOVING_DETECT          1
#define MAX_RECORD_VOICE           1
#define MAX_VIDEO_TIME_INFO_EN     1
#define MAX_VIDEO_NIGHT_LINGHT     1
#define MAX_GSENSOR_SENSTIVITY	   3
#define MAX_JPEG_PICTURE_SIZE      3
#define MAX_FAST_VIEW              2
#define MAX_PICTURE_TIME_INFO_EN   1
#define MAX_POWEROFF               3
#define MAX_LIGHT_FREQ             1
#define MAX_BACKLIGHT              3
#define MAX_VIDEO_ROTATE           1
#define MAX_BEEP_STATUS            1
#define MAX_USB_MODE            	1
#define MAX_TAKE_PIC_NUMS			1
#define MAX_TV_MODE	   				2

typedef struct {
    u8 jpeg_video_size;           //ÃÂ¼ÃÃ±Â·ÃÂ±Ã¦ÃÃ      0:1280*720 1:720*480  2:640*480
    u8 crc_record;                 //ÃÂ­Â»Â·ÃÂ¼ÃÃ±   0Â£Âºclose  1Â£Âº3mins  2Â£Âº5mins  3Â£Âº10mins
    u8 moving_detect;              //ÃÃÂ¶Â¯ÃÃ¬Â²Ã¢   0Â£Âºdisable  1:enable
    u8 record_voice;               //ÃÂ¼ÃÃÃÂµÃÃÂ·Ã±Â¾Â²ÃÃ´      0:Â¾Â²ÃÃ´  1:Â²Â»Â¾Â²ÃÃ´
    u8 video_time_info_en;         //ÃÂ¼ÃÃ±ÃÂ±Â¼Ã¤ÃÂ®ÃÂ¡      0:Â´Ã¸ÃÂ®ÃÂ¡  1:Â²Â»Â´Ã¸
    u8 video_night_light;          //ÃÂ¹ÃÃÂ¹Â¦ÃÃ      0:Â¹Ã  1:Â¿Âª
	u8  Gsensor_senstivity;
    u8 jpeg_picture_size;          //ÃÃÃÃÂ·ÃÂ±Ã¦ÃÃ      0:1280*720  1:1920*1080  
    u8 fast_view;                  //Â¿Ã¬ÃÃÃÂ¤ÃÃÂ¹Â¦ÃÃ   0:Â²Â»Â¿Âª     1:2s   2:5s
    u8 picture_time_info_en;       //ÃÃÃÃÃÂ±Â¼Ã¤ÃÂ®ÃÂ¡      0:Â´Ã¸ÃÂ®ÃÂ¡  1:Â²Â»Â´Ã¸
    u8 poweroff;                   //ÃÃÂ¶Â¯Â¹ÃÂ»ÃºÃÂ±Â¼Ã¤
    u8 language;                   //è¯­è¨              0:ä¸­æç® 1: ä¸­æç¹?:è±è¯­3: ä¿è¯­4: é©è¯­5:æ¥è¯­6:è¥¿ç­ç?
//    u8 light_freq;                 //Â¹Ã¢ÃÂ´ÃÂµÃÃ     0:50HZ  1:60HZ
    u8 backlight;                  //Â±Â³Â¹Ã¢ÃÂ±Â¼Ã¤ÃÂ¡ÃÃ±
    u8 video_rotate;               //ÃÃÃÂ»ÃÃ½ÃÂª     0:no    1:yes
	u8 tv_mode;
	u8 beep_status;               //ÃÃÃÂ»ÃÃ½ÃÂª     0:no    1:yes
    u8 usb_mode;					//USBÃÂ£ÃÂ½
    u8 take_pic_nums;
    u32 powerSaveChkCnt;              //Â±Â³Â¹Ã¢ÃÂ±Â¼Ã¤
    u16 poweroffcnt;               //Â¶Â¨ÃÂ±Â¹ÃÂ»ÃºÃÂ±Â¼Ã¤Â¼ÃÃÃ½ÃÃ·
    u16 record_video_s;            //ÃÂ­Â»Â·ÃÂ¼ÃÃ±ÂµÃÃÂ±ÂºÃ²Â£Â¬ÃÂ¿Â¸Ã¶ÃÃÃÂµÂµÃÃÃ®Â´Ã³ÃÂ±Â¼Ã¤
    s8 fast_view_time;             //Â¿Ã¬ÃÃÃÂ¤ÃÃÂµÃÃÂ±Â¼Ã¤
    u8 phone_in_flag;              //Â¶ÃºÂ»ÃºÂ²Ã¥ÃÃ«Â±ÃªÃÂ¾
    u8 SD_err_off_flag;            //SDÂ¿Â¨Â´Ã­ÃÃ³Â»Ã²ÃÃÂ²Â»ÃÃÃÃÂ±ÃªÃÂ¾
    u8 SD_err_off_cnt;             //SDÂ¿Â¨Â´Ã­ÃÃ³Â»Ã²ÃÃÂ²Â»ÃÃÃÃÂ±ÃªÃÂ¾,1minÂºÃ³Â¹ÃÂ»Ãº
	u8  Gsensor_senstivity_value;
} type_sys_ctl;

struct{
	u32 param_start;
	u32 param_addr;
}seg_info;

extern type_sys_ctl sys_ctl;
extern u8 light_sta;


void spi_param_init(void);
bool user_setting_load(u8 *setting_buf);
void user_setting_factory(u8 *setting_buf);
void spi_param_factory(u8 flag);
void spi_param_write(void *buf, u8 addr, u16 len);
void spi_param_write8(u8 addr, u8 val);

void set_fast_view_time(void);
void set_beep_sound(void);
void user_set_video_time_info(u8 timer_info_en);
void set_record_video_s(void);
void user_set_crc_record(u8 crc_record);
void set_Gsensor_senstivity_value(void);
void user_set_Gsensor_senstivity(u8 gsensor_senstivity);
void user_set_jpeg_video_size(u8 jpeg_size);
void user_set_record_mute(u8 voice);
void user_set_night_light(u8 flag);
void set_night_light(void);
void user_set_moving_detect(u8 moving_detect);
void user_set_jpeg_picture_size(u8 jpeg_size);
void user_set_picture_time_info(u8 timer_info_en);


void date_adjust_setting(u8 flag);
int byte2Dec10000(u16 src , u8* dest);
void user_set_language(u8 language);
void set_poweroff(void);
void PowerOnDetect(void);
void PowerOffDetect(void);
void user_set_poweroff(u8 poweroff);
void poweroff_1s_check(void);
void user_set_beep_sound(u8 beep_status);

void reset_powerSaveChk(void);
void user_set_backlight(u8 backlight);
void set_video_rotate(void);
void user_show_video_rotate();
void user_set_video_rotate(u8 rotate);
void user_set_fast_view(u8 fast_view);

/* for format sd card */
void user_set_format(u8 format_select);

/* for delete file */
void user_set_delete_current(u8 delete_select);
void user_set_delete_all(u8 delete_select);
/* for lock file */
void user_set_lock_current(u8 lock_select);
void user_set_unlock_current(u8 lock_select);

void user_set_lock_all(u8 lock_select);
void user_set_unlock_all(u8 lock_select);

void user_set_tv_mode(u8 tv_mode);
#endif
