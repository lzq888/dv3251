/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : menu_setting.c
* Author             : pengtao_zhang
* Version            : V0304a
* Date               : 03/04/2014  ;mm/dd/yyyy
* Description        : This file provides menu setting functions.
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
//==================================================================
type_sys_ctl sys_ctl;
u8 light_sta = 1;

#if (USER_CONFIG==CONFIG_AX3251_AIRBORNE)
const u32 tbl_powerSaveCnt[] = {5*125, 5*125, 5*125, 5*125};	//power save time is 5 Second
#else
const u32 tbl_powerSaveCnt[] = {0xffffffff, 60*125, 180*125, 300*125};	//power save time is 10 second, 180 second, 300 second
#endif

const u16 tbl_poweroff[] = {0xffff, 60, 180, 300};
const u16 tbl_record_video_s[] = {600, 180, 300, 600};//{30, 10, 20, 30};//
const s8 tbl_fast_view_time[] = {-1, 2, 5};

#if(G_SEN_USE == G_SEN_NULL)
const u8 tbl_Gsensor_senstivity[] = {0, 0x00, 0x00,0x00};
#elif(G_SEN_USE == G_SEN_DMARD07)
const u8 tbl_Gsensor_senstivity[] = {0, 0x60, 0x40,0x20};
#elif(G_SEN_USE == G_SEN_GMA301A)
const u8 tbl_Gsensor_senstivity[] = {0, 0x78, 0x60,0x40};
#endif
extern const int daysPerMonth[12];


void spi_param_init(void)
{
	u32 spiData_addr;
	u32 spiData_len;
	u32 iTableAdr;
	u8 * pBuffer = (u8 *)(__TEMP_BUFF_BEG);
	spi_SFReadData(__TEMP_BUFF_BEG,0,512);
	iTableAdr = *((u8 *)(__TEMP_BUFF_BEG  + 9))* 0x10;
	spiData_addr = *((u32 *)(__TEMP_BUFF_BEG  + iTableAdr + 0x14));
	spiData_addr = spiData_addr<<9;
	spiData_len = *((DWORD *)(__TEMP_BUFF_BEG  + iTableAdr + 0x18));
	spiData_len = spiData_len<<9;
	deg_Printf("SPI:addr=0x%x,len=0x%x\n",spiData_addr,spiData_len);
	
	iTableAdr = (spiData_addr+spiData_len);
	if (iTableAdr & ((1 << 16) - 1))	//aligh with block(64KB)
	{
		iTableAdr = ((iTableAdr >> 16) + 1) << 16;	
	}
	seg_info.param_start = iTableAdr;

    u16 page_addr = (SPI_PARAM_BASE + SPI_PARAM_BLOCK);   //æç´¢èµ·å§
    //æç´¢æ å¿
    while (1) 
	{
        page_addr -= SPI_PARAM_PAGE;
        if (page_addr < SPI_PARAM_BASE) 
		{
            break;                                      //æ¾ä¸å°ææçåæ°
        }
        u32 tmp;
        spi_SFReadData(&tmp, ((u32)page_addr << 8) + SPI_PARAM_FLAG, 4);
        if (SPI_PARAM_SIG ==  tmp)
		{
			//deg_Printf("SPI_PARAM_SIG \n");
        	spi_SFReadData(pBuffer, (u32)page_addr << 8, SPI_PARAM_LEN);
            if (user_setting_load(pBuffer)) 		//å è½½ç¨æ·åæ°
			{          
                seg_info.param_addr = page_addr;
                return;                                      //æåæ¾å°
            }
            break;
        }
    }
    seg_info.param_addr = SPI_PARAM_BASE;
    spi_param_factory(1);                         //æ¢å¤åºåè®¾ç½®	
	
}

//ä¸çµå è½½ç¨æ·åæ°
bool user_setting_load(u8 *setting_buf)
{
	deg_Printf("user_setting_load \n");
    sys_ctl.crc_record = setting_buf[PARAM_CRC_RECORD];           //å¾ªç¯å½å
    if (sys_ctl.crc_record > MAX_CRC_RECORD) {
        return false;                                       //å¾ªç¯å½ååæ°éæ³
    }
    set_record_video_s();
	
	sys_ctl.Gsensor_senstivity = setting_buf[PARAM_GSENSOR_SENSTIVITY]; 
	if(sys_ctl.Gsensor_senstivity > MAX_GSENSOR_SENSTIVITY)
		return false;
	set_Gsensor_senstivity_value();

    sys_ctl.moving_detect = setting_buf[PARAM_MOVING_DETECT];         //ç§»å¨ä¾¦æµ
    if (sys_ctl.moving_detect > MAX_MOVING_DETECT) {
        return false;                                       //ç§»å¨ä¾¦æµåæ°éæ³
    }

    sys_ctl.backlight = setting_buf[PARAM_BACKLIGHT];       //å±å¹ä¿æ¤
    if (sys_ctl.backlight > MAX_BACKLIGHT) {
        return false;                                       //å±å¹ä¿æ¤åæ°éæ³
    }
    sys_ctl.powerSaveChkCnt = tbl_powerSaveCnt[sys_ctl.backlight];

    sys_ctl.poweroff = setting_buf[PARAM_POWEROFF];       //èªå¨å³æº
    if (sys_ctl.poweroff > MAX_POWEROFF) {
        return false;                                       //èªå¨å³æºåæ°éæ³
    }
    set_poweroff();

    sys_ctl.jpeg_video_size = setting_buf[PARAM_JPEG_VIDEO_SIZE];         //å½ååè¾¨ç?
    if (sys_ctl.jpeg_video_size > MAX_JPEG_VIDEO_SIZE) {
        return false;                                       //å½ååè¾¨çåæ°éæ³?
    }

    sys_ctl.jpeg_picture_size = setting_buf[PARAM_JPEG_PICTURE_SIZE];         //æç§åè¾¨ç?
    if (sys_ctl.jpeg_picture_size > MAX_JPEG_PICTURE_SIZE) {
        return false;                                       //æç§åè¾¨çåæ°éæ³?
    }

    sys_ctl.record_voice = setting_buf[PARAM_RECORD_VOICE];         //éé³
    if (sys_ctl.record_voice > MAX_RECORD_VOICE) {
        return false;                                       //éé³åæ°éæ³
    }

    sys_ctl.video_time_info_en = setting_buf[PARAM_VIDEO_TIME_INFO_EN];         //æ¶é´æ°´å°
    if (sys_ctl.video_time_info_en > MAX_VIDEO_TIME_INFO_EN) {
        return false;                                       //æ¶é´æ°´å°åæ°éæ³
    }

    sys_ctl.picture_time_info_en = setting_buf[PARAM_PICTURE_TIME_INFO_EN];         //æ¶é´æ°´å°
    if (sys_ctl.picture_time_info_en > MAX_PICTURE_TIME_INFO_EN) {
        return false;                                       //æ¶é´æ°´å°åæ°éæ³
    }

    sys_ctl.video_night_light = setting_buf[PARAM_VIDEO_NIGHT_LINGHT];         //å¤è§åè½
    if (sys_ctl.video_night_light > MAX_VIDEO_NIGHT_LINGHT) {
        return false;                                       //å¤è§åè½åæ°éæ³
    }
    set_night_light();

    sys_ctl.fast_view = setting_buf[PARAM_FAST_VIEW];         //æç§å¿«éé¢è§?
    if (sys_ctl.fast_view > MAX_FAST_VIEW) {
        return false;                                       //æç§å¿«éé¢è§åæ°éæ³?
    }
    set_fast_view_time();

    sys_ctl.language = setting_buf[PARAM_LANGUAGE];         //è¯­è¨
    if (sys_ctl.language > MAX_LANGUAGE) {
        return false;                                       //è¯­è¨æ°´å°åæ°éæ³
    }

//    sys_ctl.light_freq = setting_buf[PARAM_LIGHT_FREQ];         //åæºé¢ç
//    if (sys_ctl.light_freq > MAX_LIGHT_FREQ) {
//        return false;                                       //åæºé¢çåæ°éæ³
//    }

    sys_ctl.video_rotate = setting_buf[PARAM_VIDEO_ROTATE];         //å±å¹æè½¬
    if (sys_ctl.video_rotate > MAX_VIDEO_ROTATE) {
        return false;                                       //å±å¹æè½¬åæ°éæ³
    }
    user_show_video_rotate();					//here handle user video rotate setting

    sys_ctl.beep_status = setting_buf[PARAM_BEEP_STATUS];         //æé®é³ææ?
    if (sys_ctl.beep_status > MAX_BEEP_STATUS) {
        return false;                                       //æé®é³ææåæ°éæ³?
    }
    set_beep_sound();

    sys_ctl.usb_mode = setting_buf[PARAM_USB_MODE];         //å±å¹æè½¬
    if (sys_ctl.usb_mode > MAX_USB_MODE) {
        return false;                                       //å±å¹æè½¬åæ°éæ³
    }

    sys_ctl.take_pic_nums = setting_buf[PARAM_TAKE_PIC_NUMS];    //å±å¹æè½¬
    if (sys_ctl.take_pic_nums > MAX_TAKE_PIC_NUMS) {
        return false;                                       //å±å¹æè½¬åæ°éæ³
    }
	
	sys_ctl.tv_mode = setting_buf[PARAM_TV_MODE]; 
	if(sys_ctl.tv_mode > MAX_TV_MODE)
		return false;

    return true;
}


//Â»ÃÂ¸Â´Â³Ã¶Â³Â§ÃÃ¨ÃÃÂ£Â¬ÃÃ¢ÃÃ¯ÃÂ»Â¶ÃÂ±Ã¤ÃÂ¿Â½Ã¸ÃÃÂ³ÃµÃÂ¼Â»Â¯Â¡Â£Â½Ã»ÃÂ¹ÃÃÃÂ´SPIFlashÂµÃÂ²ÃÃÃ·Â¡Â£
void user_setting_factory(u8 *setting_buf)
{
    sys_ctl.crc_record = DEFAULT_CRC_RECORD;                        //ÃÂ­Â»Â·ÃÂ¼ÃÃ±
    setting_buf[PARAM_CRC_RECORD] = DEFAULT_CRC_RECORD;
    set_record_video_s();

	sys_ctl.Gsensor_senstivity = 0;
	setting_buf[PARAM_GSENSOR_SENSTIVITY] = 0;
	set_Gsensor_senstivity_value();

    sys_ctl.moving_detect = DEFAULT_MOVING_DETECT;                     //ÃÃÂ¶Â¯ÃÃ¬Â²Ã¢
    setting_buf[PARAM_MOVING_DETECT] = DEFAULT_MOVING_DETECT;

    sys_ctl.backlight = 0;                         //ÃÃÃÂ»Â±Â£Â»Â¤
    setting_buf[PARAM_BACKLIGHT] = 0;
    sys_ctl.powerSaveChkCnt = tbl_powerSaveCnt[sys_ctl.backlight];

    sys_ctl.poweroff = 0;                         //ÃÃÂ¶Â¯Â¹ÃÂ»Ãº
    setting_buf[PARAM_POWEROFF] = 0;
    set_poweroff();
//	PowerOnDetect();

    sys_ctl.jpeg_video_size = DEFAULT_VIDEO_SIZE;                  //ÃÂ¼ÃÃ±Â·ÃÂ±Ã¦ÃÃ
    setting_buf[PARAM_JPEG_VIDEO_SIZE] = DEFAULT_VIDEO_SIZE;
    sys_ctl.jpeg_picture_size = DEFAULT_JPEG_SIZE;                //ÃÃÃÃÂ·ÃÂ±Ã¦ÃÃ
    setting_buf[PARAM_JPEG_PICTURE_SIZE] = DEFAULT_JPEG_SIZE;

    sys_ctl.record_voice = 1;                      //Â²Â»Â¾Â²ÃÃ´
    setting_buf[PARAM_RECORD_VOICE] = 1;

    sys_ctl.video_time_info_en = DEFAULT_VIDEO_TIME_EN;               //Â´Ã¸ÃÂ±Â¼Ã¤ÃÂ®ÃÂ¡
    setting_buf[PARAM_VIDEO_TIME_INFO_EN] = DEFAULT_VIDEO_TIME_EN;


    sys_ctl.video_night_light = 0;               //Â²Â»Â¿ÂªÃÂ¹ÃÃÂ¹Â¦ÃÃ
    setting_buf[PARAM_VIDEO_NIGHT_LINGHT] = 0;
    set_night_light();


    sys_ctl.fast_view = 0;                        //ÃÃÃÃªÃÃÃÂ¬ÂºÃ³Â¿Ã¬ÃÃÃÂ¤ÃÃÂ¹ÃÂ±Ã
    setting_buf[PARAM_FAST_VIEW] = 0;
    set_fast_view_time();

    sys_ctl.picture_time_info_en = DEFAULT_JPEG_TIME_EN;             //Â´Ã¸ÃÂ±Â¼Ã¤ÃÂ®ÃÂ¡
    setting_buf[PARAM_PICTURE_TIME_INFO_EN] = DEFAULT_JPEG_TIME_EN;

    sys_ctl.language = DEFAULT_LANGUAGE;                          //ÃÃ¯ÃÃ ÃÃÃÃ
    setting_buf[PARAM_LANGUAGE] = DEFAULT_LANGUAGE;

//    sys_ctl.light_freq = 0;                        //Â¹Ã¢ÃÂ´ÃÂµÃÃ 50hz
//    setting_buf[PARAM_LIGHT_FREQ] = 0;

  /*  if(u8SensorChipID == 0x76)    //7670
    {
        sys_ctl.video_rotate = 0;                      //ÃÃÃÂ»Â²Â»ÃÃ½ÃÂª
        setting_buf[PARAM_VIDEO_ROTATE] = 0;
    }
    else
    {
        sys_ctl.video_rotate = 0;                      //ÃÃÃÂ»Â²Â»ÃÃ½ÃÂª
        setting_buf[PARAM_VIDEO_ROTATE] = 0;
    }*/
	sys_ctl.video_rotate = 0;                      //ÃÃÃÂ»Â²Â»ÃÃ½ÃÂª
	setting_buf[PARAM_VIDEO_ROTATE] = 0;
	user_show_video_rotate();
    //set_video_rotate();

    sys_ctl.beep_status = 1;                      //Â³ÃµÃÂ¼Â»Â¯Â¿ÂªÂ°Â´Â¼Ã¼ÃÃ´
    setting_buf[PARAM_BEEP_STATUS] = 1;
    //set_beep_sound();

    sys_ctl.usb_mode = 0;                      //Â³ÃµÃÂ¼Â»Â¯Â¿ÂªÂ°Â´Â¼Ã¼ÃÃ´
    setting_buf[PARAM_USB_MODE] = 0;

    sys_ctl.take_pic_nums = 0;                      //Â³ÃµÃÂ¼Â»Â¯Â¿ÂªÂ°Â´Â¼Ã¼ÃÃ´
    setting_buf[PARAM_TAKE_PIC_NUMS] = 0;
	
//	sys_ctl.fast_view_time = -1;				//Â³ÃµÃÂ¼Â»Â¯Â¿Ã¬ÃÃÃ¤Â¯ÃÃ

	sys_ctl.tv_mode = 0;                     
    setting_buf[PARAM_TV_MODE] = 0;
}

//Ã¦ÂÂ¢Ã¥Â¤ÂÃ¥ÂÂºÃ¥ÂÂÃ¨Â®Â¾Ã§Â½Â®
void spi_param_factory(u8 flag)
{
	deg_Printf("spi_param_factory \n");
	u8 *pBuffer = (u8 *)(__TEMP_BUFF_BEG);
	if(!flag)
		return;
	
	spi_SFEraseSector(SPI_PARAM_BASE << 8);
	
	my_memset(pBuffer, 0, SPI_PARAM_LEN);
    user_setting_factory(pBuffer);        //Â»ÃÂ¸Â´Â³Ã¶Â³Â§Â²ÃÃÃ½Â¡Â£ÃÃÂ»Â§ÃÃÂ¶Â¨ÃÃ¥

    //åå¥CRCä¸æ å¿ä½
    *(u32 *)(pBuffer + SPI_PARAM_FLAG) = SPI_PARAM_SIG;

    spi_SFWriteData(seg_info.param_addr << 8, pBuffer, SPI_PARAM_LEN);
  /*  if(g_SystemState == SYSTEM_POWER_OFF)
    {
    	irtcc_write_time(2014,1,1,0,0,0);     //ä¿®æ¹ç³»ç»æ¶é´ãonly set when power on, recover default not change system time
    }*/
}

//åå¥ä¿¡æ¯ï¼å¹¶ä¸ä¸ç ´åå¶å®å·²æä¿¡æ¯
void spi_param_write(void *buf, u8 addr, u16 len)
{
	u8 * pBuffer = (u8 *)(__TEMP_BUFF_BEG);
    if (len + addr > SPI_PARAM_VLEN) {
        return;                         //è¶åºæ°æ®èå´
    }
    spi_SFReadData(pBuffer, (u32)(seg_info.param_addr<<8), SPI_PARAM_LEN);
    memcpy__(pBuffer + addr, buf, len);

    //åå¥CRCä¸æ å¿ä½
    *(u32 *)(pBuffer + SPI_PARAM_FLAG) = SPI_PARAM_SIG;

    seg_info.param_addr += SPI_PARAM_PAGE;
    if(seg_info.param_addr >= (SPI_PARAM_BASE + SPI_PARAM_BLOCK))
    {
    	spi_SFEraseSector(SPI_PARAM_BASE << 8);
        seg_info.param_addr = SPI_PARAM_BASE;
    }
    //printf("write addr: %x\n", seg_info.param_addr);
    //while (SPI_PARAM_PAGE)
    spi_SFWriteData(seg_info.param_addr << 8, pBuffer, SPI_PARAM_LEN);
}

//åå¥1byteä¿¡æ¯ï¼å¹¶ä¸ä¸ç ´åå¶å®å·²æä¿¡æ¯
void spi_param_write8(u8 addr, u8 val)
{
    spi_param_write(&val, addr, 1);
}

void set_fast_view_time(void)
{
    sys_ctl.fast_view_time = tbl_fast_view_time[sys_ctl.fast_view];
}


//è®¾ç½®æé®é?
void set_beep_sound(void)
{
	if(sys_ctl.beep_status)
	{
		/*dac_Init();
		REG32(DACCON2) &= ~(1<<7);
		dac_ExitMute();*/
	}
	else
	{
		/*REG32(DACCON2) |= (1<<7);      //mute DAC
		dac_EntryMute();*/
	}
}

//ÃÂ¼ÃÃ±ÃÃÂ·Ã±Â´Ã¸ÃÂ±Â¼Ã¤ÃÂ®ÃÂ¡
void user_set_video_time_info(u8 timer_info_en)
{
    if (timer_info_en == sys_ctl.video_time_info_en) 
	{
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (timer_info_en <= MAX_VIDEO_TIME_INFO_EN) 
	{
        sys_ctl.video_time_info_en = timer_info_en;
        spi_param_write8(PARAM_VIDEO_TIME_INFO_EN, timer_info_en);
    }
}

void set_record_video_s(void)
{
#if (USER_CONFIG==CONFIG_AX3251_AIRBORNE)
    sys_ctl.record_video_s = DEFAULT_VIDEO_REC_TIME;
#else
    sys_ctl.record_video_s = tbl_record_video_s[sys_ctl.crc_record];
#endif

}

//Ã¤Â¿ÂÃ¥Â­ÂÃ¥Â¾ÂªÃ§ÂÂ¯Ã¥Â½ÂÃ¥ÂÂ
void user_set_crc_record(u8 crc_record)
{
    if (crc_record == sys_ctl.crc_record) 
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    
    if (crc_record <= MAX_CRC_RECORD) 
	{
        sys_ctl.crc_record = crc_record;
        spi_param_write8(PARAM_CRC_RECORD, crc_record);
        set_record_video_s();
    }
}

void set_Gsensor_senstivity_value(void)
{
	sys_ctl.Gsensor_senstivity_value = tbl_Gsensor_senstivity[sys_ctl.Gsensor_senstivity];
	Gsen_set_Threshold(sys_ctl.Gsensor_senstivity_value);
}

void user_set_Gsensor_senstivity(u8 gsensor_senstivity)
{
    if (gsensor_senstivity == sys_ctl.Gsensor_senstivity) 
        return;                             
    
    if (gsensor_senstivity <= MAX_GSENSOR_SENSTIVITY) 
	{
        sys_ctl.Gsensor_senstivity = gsensor_senstivity;
        spi_param_write8(PARAM_GSENSOR_SENSTIVITY, gsensor_senstivity);
        set_Gsensor_senstivity_value();
    }
}

//Ã¤Â¿ÂÃ¥Â­ÂÃ¥Â½ÂÃ¥ÂÂÃ§ÂÂÃ¥ÂÂÃ¨Â¾Â¨Ã§ÂÂ
void user_set_jpeg_video_size(u8 jpeg_size)
{
    if (jpeg_size == sys_ctl.jpeg_video_size) 
	{
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (jpeg_size <= MAX_JPEG_VIDEO_SIZE)
	{
        sys_ctl.jpeg_video_size = jpeg_size;
        spi_param_write8(PARAM_JPEG_VIDEO_SIZE, jpeg_size);
    }
}

//Ã¤Â¿ÂÃ¥Â­ÂÃ§Â§Â»Ã¥ÂÂ¨Ã¤Â¾Â¦Ã¦ÂµÂ
void user_set_moving_detect(u8 moving_detect)
{
    if (moving_detect == sys_ctl.moving_detect) {
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (moving_detect <= MAX_MOVING_DETECT) {
        sys_ctl.moving_detect = moving_detect;
        spi_param_write8(PARAM_MOVING_DETECT, moving_detect);
    }
	if(sys_ctl.moving_detect)
		csi_MD_Enable();
	else
		csi_MD_Disable();
}

//Ã¤Â¿ÂÃ¥Â­ÂÃ¥Â½ÂÃ¥ÂÂ¶Ã¨Â§ÂÃ©Â¢ÂÃ§ÂÂÃ¦ÂÂ¶Ã¥ÂÂÃ¦ÂÂ¯Ã¥ÂÂ¦Ã¨Â¦ÂÃ©ÂÂÃ©ÂÂ³
void user_set_record_mute(u8 voice)
{
    if (voice == sys_ctl.record_voice) 
	{
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (voice <= MAX_RECORD_VOICE) 
	{
        sys_ctl.record_voice = voice;
        spi_param_write8(PARAM_RECORD_VOICE, voice);
    }
}

//Ã¦ÂÂ¯Ã¥ÂÂ¦Ã¥Â¼ÂÃ¥ÂÂ¯Ã¥Â¤ÂÃ¨Â§ÂÃ§ÂÂ¯
void user_set_night_light(u8 flag)
{
    if (flag == sys_ctl.video_night_light) 
	{
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (flag <= MAX_VIDEO_NIGHT_LINGHT)
   {
        sys_ctl.video_night_light = flag;
        spi_param_write8(PARAM_VIDEO_NIGHT_LINGHT, flag);
        set_night_light();
    }
}
//Ã¨Â®Â¾Ã§Â½Â®Ã¥Â¤ÂÃ¨Â§ÂÃ¥ÂÂÃ¨ÂÂ½
void set_night_light(void)
{
	if(sys_ctl.video_night_light)
	{
		OPEN_NIGHT_LIGHT();
		light_sta = 1;
		deg_Printf("open night light \n");
	}
	else
	{
		CLOSE_NIGHT_LIGHT();
		light_sta = 0;
	}
}

//Ã¤Â¿ÂÃ¥Â­ÂÃ¦ÂÂÃ§ÂÂ§Ã§ÂÂÃ¥ÂÂÃ¨Â¾Â¨Ã§ÂÂ
void user_set_jpeg_picture_size(u8 jpeg_size)
{
    if (jpeg_size == sys_ctl.jpeg_picture_size) 
	{
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (jpeg_size <= MAX_JPEG_PICTURE_SIZE) 
	{
        sys_ctl.jpeg_picture_size = jpeg_size;
        spi_param_write8(PARAM_JPEG_PICTURE_SIZE, jpeg_size);
    }
}

//ÃÃÃÃÃÃÂ·Ã±Â´Ã¸ÃÂ±Â¼Ã¤ÃÂ®ÃÂ¡
void user_set_picture_time_info(u8 timer_info_en)
{
    if (timer_info_en == sys_ctl.picture_time_info_en) {
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (timer_info_en <= MAX_PICTURE_TIME_INFO_EN) {
        sys_ctl.picture_time_info_en = timer_info_en;
        spi_param_write8(PARAM_PICTURE_TIME_INFO_EN, timer_info_en);
    }
}


#if 1
void fix_date(u16 *time_buf)
{
	if(time_buf[0] < 2000)
		time_buf[0] = 2099;
	if(time_buf[0] > 2099)
		time_buf[0] = 2000;
	if(time_buf[1] > 12)
		time_buf[1] = 1;
	if(time_buf[1] < 1)
		time_buf[1] = 12;
	if(isLeapYear(time_buf[0]) && time_buf[1] == 2)
	{
		if(time_buf[2] > daysPerMonth[time_buf[1]-1] + 1)
			time_buf[2] = 1;
		if(time_buf[2] < 1)
			time_buf[2] = daysPerMonth[time_buf[1]-1] + 1;
	}
	else
	{
		if(time_buf[2] > daysPerMonth[time_buf[1]-1])
			time_buf[2] = 1;
		if(time_buf[2] < 1)
			time_buf[2] = daysPerMonth[time_buf[1]-1];
	}
	if(time_buf[3] > 23 && time_buf[3] < 0xff)
		time_buf[3] = 0;
	if(time_buf[3] > 0xff)
		time_buf[3] = 23;
	if(time_buf[4] > 59 && time_buf[4] < 0xff)
		time_buf[4] = 0;
	if(time_buf[4] > 0xff)
		time_buf[4] = 59;
}
#endif

int byte2Dec10000(u16 src , u8* dest)//in 10000, hex to dec
{
	if (src < 10000 && src >= 1000)
	{
		dest[0] = '0'+src/1000;
		dest[1] = '0'+(src%1000)/100;
		dest[2] = '0'+((src%1000)%100)/10;
		dest[3] = '0'+((src%1000)%100)%10;		
	}
	else if(src < 1000 && src >= 100)
	{
		dest[0] = '0'+src/100;
		dest[1] = '0'+(src%100)/10;
		dest[2] = '0'+(src%100)%10;
	}
	else if (src < 100 && src >= 0)
	{
		dest[0] = '0'+src/10;
		dest[1] = '0'+(src%10);
	}
	else
	{
		return -1;
	}
	return 0;
}

void time_setting_display(u8 update_flag, u16 * date_buf, u8 setting_step)
{
//		u16 triangle_position = 0;
//		u16 startx = 0, starty = 0, itemw = 0;
//		u8 tmp[21] = {0};
		int i;
		u8 charShift = 0;
		char * cMiddleChar = "-";
		char * cTimeMiddleChar = ":";
		char * cSpaceChar = " ";
//		MENU_ITEM  *MenuItem;
		TIME_SETTING_DISPLAY arrTime_setting_display[12];
		
		for (i=0; i<12; i++)
		{
			memset__(arrTime_setting_display[i].timepString, 0, sizeof(arrTime_setting_display[i].timepString));
			arrTime_setting_display[i].pOSDInf = menu_mgroup.p_menu_inf;
			arrTime_setting_display[i].startx = menu_highlight[menu_mgroup.level].xs;
			arrTime_setting_display[i].starty = menu_highlight[menu_mgroup.level].ys;
			arrTime_setting_display[i].w = 160;
			arrTime_setting_display[i].h = 16;
			arrTime_setting_display[i].forecolor = UNSELECT_LEV1_FORE_COLOR;
			arrTime_setting_display[i].backcolor = UNSELECT_LEV1_BACK_COLOR;
			arrTime_setting_display[i].align = 3;			
		}	
		arrTime_setting_display[setting_step<<1].forecolor = SELECT_FORE_COLOR;
		arrTime_setting_display[setting_step<<1].backcolor = SELECT_BACK_COLOR;  //select the time
		
		byte2Dec10000(date_buf[0], (arrTime_setting_display[0].timepString)); //year
		memcpy__(arrTime_setting_display[1].timepString, cMiddleChar, 1); //-
		byte2Dec10000(date_buf[1], (arrTime_setting_display[2].timepString)); //month
		memcpy__(arrTime_setting_display[3].timepString, cMiddleChar, 1); //-
		byte2Dec10000(date_buf[2], (arrTime_setting_display[4].timepString)); //date
	
		memcpy__(arrTime_setting_display[5].timepString, cSpaceChar, 1); // space
		
		byte2Dec10000(date_buf[3], (arrTime_setting_display[6].timepString)); //h
		memcpy__(arrTime_setting_display[7].timepString, cTimeMiddleChar, 1); //-
		byte2Dec10000(date_buf[4], (arrTime_setting_display[8].timepString)); //min
		memcpy__(arrTime_setting_display[9].timepString, cTimeMiddleChar, 1); //-
		byte2Dec10000(date_buf[5], (arrTime_setting_display[10].timepString)); //sec
		
		memcpy__(arrTime_setting_display[11].timepString, cSpaceChar, 1); // space	
		
		if(update_flag == 1)
		{
			update_flag = 0;

			for (i=0; i<12; i++)
			{		
				DisplayUnicodeStr(arrTime_setting_display[i].pOSDInf,(u8*)(arrTime_setting_display[i].timepString),
								  (arrTime_setting_display[i].startx+charShift),arrTime_setting_display[i].starty,arrTime_setting_display[i].w,
								  arrTime_setting_display[i].h,arrTime_setting_display[i].forecolor,arrTime_setting_display[i].backcolor,
								  arrTime_setting_display[i].align);

				//========get string w=======
				int k;
				int tempx = 0;
				FontGroup  font_group;
				GetStrFontInfo(arrTime_setting_display[i].timepString,(FontGroup *)&font_group);

				for(k=0; k<font_group.num; k++)
				{
					tempx += (font_group.FontInfo[k]).x;
				}
				//========end get string w=====
				charShift += tempx;

			}

		}

}


static void fixed_setting_display(void)
{
	u16 startx = 0, starty = 0, itemw = 0;
	MENU_ITEM  *MenuItem;

	MenuBackgroundUpdate(0);	//	fill the screen with backcolor
/*
	lcd_FillPartOsdData(menu_mgroup.p_menu_inf,ALPHA_0X00_COLOR, 0, menu_highlight[menu_mgroup.level].ys+(MENU_ITEM_HEIGHT)*1+1,
			menu_level_region[menu_mgroup.level].w, menu_level_region[menu_mgroup.level].h - MENU_ITEM_HEIGHT); 	//clear the surplus backcolor
*/

/*
	lcd_FillPartOsdData(menu_mgroup.p_menu_inf,ALPHA_0X00_COLOR, menu_level_region[menu_mgroup.level].xs, menu_level_region[menu_mgroup.level].ys,
			menu_level_region[menu_mgroup.level].w, menu_level_region[menu_mgroup.level].h);
	lcd_FillPartOsdData(menu_mgroup.p_menu_inf,ALPHA_0X80_COLOR, menu_level_region[menu_mgroup.level].xs, menu_level_region[menu_mgroup.level].ys,
			menu_level_region[menu_mgroup.level].w,MENU_ITEM_HEIGHT);	//clear the surplus backcolor
*/

	startx = MENU_TITLE_STR_XS;
	starty = MENU_YS+2;
	itemw = MENU_W-MENU_TITLE_STR_XS;
	MenuItem = menu_mgroup.mgr_page.mpage->p_menu_item;
	lcd_FillPartOsdData(menu_mgroup.p_menu_inf, HEAD_STATUS_BACK_COLOR, MENU_TITLE_STR_XS, MENU_YS, MENU_W-MENU_TITLE_STR_XS, MENU_HEAD_HEIGHT);  //fill the string of the menu bar with backcolor 
//	DisplayUnicodeStr(menu_mgroup.p_menu_inf,(u8*)(MenuItem->string_addr->pLanguage[sys_ctl.language]),startx,starty,itemw,16,CHARACTER_FORE_COLOR,HEAD_STATUS_BACK_COLOR,1);  //write the new string
	DisplayUnicodeStr(menu_mgroup.p_menu_inf,(u8*)(attribute_page_string6.pLanguage[sys_ctl.language]),startx,starty,itemw,16,CHARACTER_FORE_COLOR,HEAD_STATUS_BACK_COLOR,1);  //write the new string


	return;
}


void date_adjust_setting(u8 flag)
{
	//u8	tmpTimeInfoCurrent[TIME_INFO_LEN+2];	//store curent timerinfo
	//static date memdate = {0};	//store curent timerinfo
		
	u16 date_buf[6];
	u8 flag_update_osd = 1;
	u8 setting_step = SETTING_YEAR;
	date today;

	now(&today);
	date_buf[0] = today.year;
	date_buf[1] = today.month;
	date_buf[2] = today.day;
	date_buf[3] = today.hour;
	date_buf[4] = today.min;
	date_buf[5] = today.sec;

	fixed_setting_display();
	while(cur_menu.menu_type != MENU_IDLE)
	{
		now(&today);

		if (date_buf[5] != today.sec)
		{
			flag_update_osd = 1;
			date_buf[5] = today.sec;
		}

	        u8 msg = get_msg();
	        switch(msg)
	        {
				case T_KEY_MENU | T_KEY_SHORT_UP:
					goto time_save;
				case T_KEY_PLAY | T_KEY_SHORT_UP:
					setting_step++;
					if(setting_step > SETTING_MIN)
					{
						setting_step = 0;
					}
					flag_update_osd = 1;
					break;
				case T_KEY_UP | T_KEY_SHORT_UP:
				case T_KEY_DOWN | T_KEY_SHORT_UP:
					if(msg == (T_KEY_UP | T_KEY_SHORT_UP))
						date_buf[setting_step]++;
					else
						date_buf[setting_step]--;
					flag_update_osd = 1;
					fix_date(date_buf);
					break;
				case T_KEY_MODE | T_KEY_SHORT_UP:
					deal_msg(msg);
					return;
				default:
					deal_msg(msg);
					break;
	        }
	        time_setting_display(flag_update_osd, date_buf, setting_step);
		
	}
	
time_save:
	rtc_WriteTime(date_buf[0],date_buf[1],date_buf[2],date_buf[3],date_buf[4],today.sec);
	
}

void user_set_language(u8 language)
{
    if (language == sys_ctl.language) {
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (language <= MAX_LANGUAGE) 
    {
        sys_ctl.language = language;
	 spi_param_write8(PARAM_LANGUAGE, language);
    }
}

void poweroff_1s_check(void)
{
	
    if((0 == task_ctl.on_recording) && (0 == task_ctl.on_playing) && (task_ctl.work_sta != TASK_USB_DEVICE) && (g_SystemState != SYSTEM_POWER_ON))				// recoding and playing will not power off,just stop it
    {

	    if(sys_ctl.poweroffcnt != 0 && sys_ctl.poweroffcnt != 0xffff)
	    {
	        sys_ctl.poweroffcnt--;
			deg_Printf("** power off count %d\r\n", sys_ctl.poweroffcnt);
	    }
	    if (sys_ctl.poweroffcnt == 0)
	    {
			//u8 backup = task_ctl.work_sta;
	//        task_ctl.work_sta = TASK_POWER_OFF;
			deg_Printf("***** power off %d\r\n", tbl_poweroff[sys_ctl.poweroff]);
	//		POWER_CONTROL_OUTPUT_LOW;		
			
			sys_ctl.poweroffcnt = tbl_poweroff[0];
			sys_ctl.poweroff = 0;

			task_exit();				// poweroff
		}
    }
}

void set_poweroff(void)
{
    sys_ctl.poweroffcnt = tbl_poweroff[sys_ctl.poweroff];	

	deg_Printf("power off seting %d, poweroff %d\r\n", sys_ctl.poweroffcnt, sys_ctl.poweroff);
}

void user_set_poweroff(u8 poweroff)
{
    if (poweroff == sys_ctl.poweroff) {
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (poweroff <= MAX_POWEROFF) {
        sys_ctl.poweroff = poweroff;
	 spi_param_write8(PARAM_POWEROFF, poweroff);
        set_poweroff();
    }
}


void user_set_beep_sound(u8 beep_status)
{
    if (beep_status == sys_ctl.beep_status) 
	{
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (beep_status <= MAX_BEEP_STATUS) 
	{
        sys_ctl.beep_status = beep_status;
        spi_param_write8(PARAM_BEEP_STATUS, beep_status);
    }
    set_beep_sound();
}

void reset_powerSaveChk(void)
{
    sys_ctl.powerSaveChkCnt = tbl_powerSaveCnt[sys_ctl.backlight];
	//powerSaveFlag = 0;
	//deg_Printf("sys_ctl.backlightcnt = %d\n", sys_ctl.backlightcnt);
}

//Ã¥Â±ÂÃ¥Â¹ÂÃ¤Â¿ÂÃ¦ÂÂ¤
void user_set_backlight(u8 backlight)
{
   if (backlight == sys_ctl.backlight) 
	{
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (backlight <= MAX_BACKLIGHT) 
	{
        sys_ctl.backlight = backlight;
		//deg_Printf("sys_ctl.backlight = %d\n", sys_ctl.backlight);
		spi_param_write8(PARAM_BACKLIGHT, backlight);
        reset_powerSaveChk();
		lcd_set_backlight(1);
    }  
}


void set_video_rotate(void)
{
	REG32(LCDCON57) =1;
	while((REG32(LCDCON57)&0x01)==0); 
	REG32(LCD_CFG) &= ~BIT(BIT_LCD_EN);
	
	if(sys_ctl.video_rotate==0x0)
	{

		REG32(LCD_YUV2RGB) &= ~BIT(BIT_ROTATEMODE);
	}
	else
	{
		REG32(LCD_YUV2RGB) |= BITS(BIT_ROTATEMODE, ROTATE_180);
	}
	REG32(LCD_CFG) |= BIT(BIT_LCD_EN);
}

void user_show_video_rotate()
{
//	deg_Printf("sys_ctl.video_rotate = 0x%d \n",sys_ctl.video_rotate);
    if(sys_ctl.video_rotate == MAX_VIDEO_ROTATE)
    {
		sensor_rotate(1);
    }
    else
    {
		sensor_rotate(0);
    }
}

//Ã¥Â±ÂÃ¥Â¹ÂÃ¦ÂÂÃ¨Â½Â¬
void user_set_video_rotate(u8 rotate)
{
	//deg_Printf("sys_ctl.video_rotate = %d\n", sys_ctl.video_rotate);
    if (rotate == sys_ctl.video_rotate) {
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    } 
    if (rotate == MAX_VIDEO_ROTATE) 
    {
        sys_ctl.video_rotate = rotate;
        sensor_rotate(1);
    }
    else
    {
        sys_ctl.video_rotate = rotate;
		sensor_rotate(0);
    }
    spi_param_write8(PARAM_VIDEO_ROTATE, rotate);
}

//ÃÃÃÃÂ¿Ã¬ÃÃÃÂ¤ÃÃ
void user_set_fast_view(u8 fast_view)
{
	//deg_Printf("fast_view = %d\n",fast_view);
    if (fast_view == sys_ctl.fast_view) 
	{
        return;                             //ÃÂ»ÃÃÂ¸Ã¼Â¸Ã
    }
    if (fast_view <= MAX_FAST_VIEW) 
	{
        sys_ctl.fast_view = fast_view;
        spi_param_write8(PARAM_FAST_VIEW, fast_view);
        set_fast_view_time();
		sys_ctl.fast_view_time = tbl_fast_view_time[sys_ctl.fast_view];
		
    }
}


#define FORMAT_SD_NO	0
#define FORMAT_SD_YES	1
enum {FORMAT_SD_OK, FORMAT_SD_FAIL};

void user_set_format(u8 format_select) 
{
	volatile u32 i = 6553600*3;
	if(sys_ctl.SD_err_off_flag == 1)
		return;
	deg_Printf("format select: %d\n", format_select);
	
	if (FORMAT_SD_NO == format_select) 
	{
		deg_Printf("don't format sd card\n");
//		cur_menu.menu_type = MENU_IDLE;
		return;
	}
	else if (FORMAT_SD_YES == format_select) 
	{
		if(FALSE==sd_err_reinit())
		{
			return;
		}
		deg_Printf("format sd card\n");
//		cur_menu.menu_type = MENU_IDLE;
		Delay_MS(50);	
		lcd_FillFullOsdData(menu_mgroup.p_menu_inf,ALPHA_0X00_COLOR);

		DisplayUnicodeStr(&OSD1Inf,(u8 *)(group_format_sd_ing[sys_ctl.language]),0+20,MENU_HEIGHT/2,MENU_ITEM1_W+10,FONT_HEIGHT,OSD_TIME_COLOR, ALPHA_0X00_COLOR,2);
		
		if (format_filesystem() == FORMAT_SD_OK)
		{
			
//			lcd_FillFullOsdData(menu_mgroup.p_menu_inf,ALPHA_0X00_COLOR);
 			lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, 0+20, MENU_HEIGHT/2, MENU_ITEM1_W, 4*FONT_HEIGHT);
			deg_Printf("format sd card ok\n");
			DisplayUnicodeStr(&OSD1Inf,(u8 *)(group_format_sd_succeed[sys_ctl.language]),0+20,MENU_HEIGHT/2,MENU_ITEM1_W,FONT_HEIGHT,OSD_TIME_COLOR, ALPHA_0X00_COLOR,2);

			//====after format ,need create work folder=====
			InitRecordFolder();
			//====end create folder
		} 
		else 
		{
			deg_Printf("format sd card fail\n");
//			lcd_FillFullOsdData(menu_mgroup.p_menu_inf,ALPHA_0X00_COLOR);
			lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, 0+20, MENU_HEIGHT/2, MENU_ITEM1_W, 4*FONT_HEIGHT);
			DisplayUnicodeStr(&OSD1Inf,(u8 *)(group_format_sd_fail[sys_ctl.language]),0+20,MENU_HEIGHT/2,MENU_ITEM1_W,FONT_HEIGHT,OSD_TIME_COLOR, ALPHA_0X00_COLOR,2);
		}
		sys_update_FileOrder();
		
//		while(!get_msg());
		while(i--);
//		i = 65536000;while(i--);


		lcd_FillPartOsdData(&OSD1Inf, ALPHA_0X00_COLOR, 0+20,MENU_HEIGHT/2,MENU_ITEM1_W+10,FONT_HEIGHT+32);	/* 清除警告提示语 */
		lcd_UpdateOsdIconData_FromSdram(menu_mgroup.p_menu_inf, menu_level_region[0].icon, 0, 0);
		SetOSDDisplayFlag(MENU_HEARD_DISPLAY_FLAG);
		MenuPageOSDHeaderUpdate();
	
	}
}

/* for delete file */

#define DELETE_CURRENT_NO	0
#define DELETE_CURRENT_YES	1

void user_set_delete_current(u8 delete_select) {
	
	if (DELETE_CURRENT_NO == delete_select) 
	{
//		deg_Printf("don't delete current file\n");
//		cur_menu.menu_type = MENU_IDLE;
		return;
	} 
	else if (DELETE_CURRENT_YES == delete_select)
	{
		deg_Printf("delete current file\n");
//		cur_menu.menu_type = MENU_IDLE;
		delete_file(DELETE_CURRENT);
		task_play_Next();
	}
}


#define DELETE_ALL_NO	0
#define DELETE_ALL_YES	1

void user_set_delete_all(u8 delete_select) {
	
	if (DELETE_ALL_NO == delete_select) {
//		deg_Printf("don't delete all file\n");
//		cur_menu.menu_type = MENU_IDLE;
		return;
	} else if (DELETE_ALL_YES == delete_select) {
//		deg_Printf("delete all file\n");
		cur_menu.menu_type = MENU_IDLE;
		delete_file(DELETE_ALL);
	}
}


// for lock file

#define LOCK_CURRENT_NO		0
#define LOCK_CURRENT_YES	1

void user_set_lock_current(u8 lock_select) {
	
	if (LOCK_CURRENT_NO == lock_select) {
//		deg_Printf("don't lock current file\n");
//		cur_menu.menu_type = MENU_IDLE;
		return;
	} else if (LOCK_CURRENT_YES == lock_select) {
//		deg_Printf("lock current file\n");
//		cur_menu.menu_type = MENU_IDLE;
		lock_unlock_file(CURRENT_FILE | LOCK);
	}
}


#define UNLOCK_CURRENT_NO		0
#define UNLOCK_CURRENT_YES		1

void user_set_unlock_current(u8 lock_select) {
	
	if (UNLOCK_CURRENT_NO == lock_select) {
//		deg_Printf("don't unlock current file\n");
//		cur_menu.menu_type = MENU_IDLE;
		return;
	} else if (UNLOCK_CURRENT_YES == lock_select) {
//		deg_Printf("unlock current file\n");
//		cur_menu.menu_type = MENU_IDLE;
		lock_unlock_file(CURRENT_FILE | UNLOCK);
	}
}


#define LOCK_ALL_NO		0
#define LOCK_ALL_YES	1

void user_set_lock_all(u8 lock_select) {
	
	if (LOCK_ALL_NO == lock_select) {
//		deg_Printf("don't lock all file\n");
//		cur_menu.menu_type = MENU_IDLE;
		return;
	} else if (LOCK_ALL_YES == lock_select) {
//		deg_Printf("lock all file\n");
//		cur_menu.menu_type = MENU_IDLE;
		lock_unlock_file(ALL_FILE | LOCK);
	}
}


#define UNLOCK_ALL_NO		0
#define UNLOCK_ALL_YES		1

void user_set_unlock_all(u8 lock_select) {
	
	if (UNLOCK_ALL_NO == lock_select) {
//		deg_Printf("don't unlock all file\n");
//		cur_menu.menu_type = MENU_IDLE;
		return;
	} else if (UNLOCK_ALL_YES == lock_select) {
//		deg_Printf("unlock all file\n");
//		cur_menu.menu_type = MENU_IDLE;
		lock_unlock_file(ALL_FILE | UNLOCK);
	}
}

void user_set_tv_mode(u8 tv_mode)
{
	if(tv_mode == sys_ctl.tv_mode)
		return;
		
	if(tv_mode <= MAX_TV_MODE)
	{
		sys_ctl.tv_mode = tv_mode;
		spi_param_write8(PARAM_TV_MODE, tv_mode);
		tvout_set_cur_mode(sys_ctl.tv_mode);
		EN_OSD1();
		EN_OSD3();
		if(sys_ctl.tv_mode == 0)
		{
			lcd_set_backlight(1);	//open backlight
		}
	}
}


