

#include "../header/include.h"

extern DIR file_dir;
extern u32 Ep1Deal;

void task_usb_device_deal_msg(u8 msg)
{
	switch(msg)
	{
	case T_KEY_MODE | T_KEY_SHORT_UP:
		break;	
	default:
		deal_msg(msg);
		break;
	}
}

void task_usb_device()
{
	deg_Printf("enter usb device mode\n");
	g_SystemState = SYSTEM_USB_CONNECT;
	reset_powerSaveChk();
	csi_Stop();
	DIS_OSD1();								//use pull into USB ,no show osd icon
	DIS_OSD3();
	Delay_MS(20);

	while(delResult != FR_OK) {		//wait for finish deleting procedure
		delResult = f_unlink_removeChain(&delFS, &work_fatfs,&delCLST,1);
		deg_Printf("m");				
	}

	if(light_sta)		//if night light open just close it
	{
		CLOSE_NIGHT_LIGHT();
	}

	usb_enum_type = 0;
//====check key into mode====

	u32 key_cnt = 0;
	u32 i = 0;
	while(i < 50)
	{
		if(T_KEY_MENU == GetIOKeyTpye())			//menu key
		{
			key_cnt++;
		}
		i++;
		Delay_MS(1);
	}


	if(key_cnt > 45)
	{
		usb_enum_type = 1;
		deg_Printf("enter pc cam mode\n");
	}
//=====end check key =========
#if (LCD_USE != LCD_NO_DISPLAY)	
	if(0 == usb_enum_type)
	{
		 sys_show_jpeg(RES_USB_DEV_ICON);
	}
	else if(1 == usb_enum_type)
	{
 		sys_show_jpeg(RES_USB_DEV_ICON);
	}
#endif
	usb_enum_type = 1;
	usb_device_init();
	if(usb_enum_type)
	{
		csi_Stop();
		csi_camera_init();
	}

	deg_Printf("into usb while task_ctl.work_sta = %d\n",task_ctl.work_sta);
	while (task_ctl.work_sta == TASK_USB_DEVICE)
	{
		if(!(device_online&BIT(B_USB_DEV_ONLINE)))
		{
//			task_ctl.work_sta = task_ctl.work_backup_sta;
			g_stcJpegInfo.bPowerOffFlag = 1;
			task_ctl.work_sta = TASK_POWER_OFF;
			deg_Printf("usb out poweroff\n");
			break;
		}


		u8 msg = get_msg();
		task_usb_device_deal_msg(msg);
//		if(!usb_enum_type)
//		if(!uvc_on)				//if the usb vedio on, the mass store stop
//		if(Ep1Deal > 0)
//		{
//			if(0 == rbc_process())
			rbc_process();
//			if(Ep1Deal > 0)
//			{
//				Ep1Deal--;
//			}
//			if(Ep1Deal > 1)
//			{
//				deg_Printf("Ep1Deal %u\r\n",Ep1Deal);
//			}
//			if(Ep1Deal <= 0)
//			{
//				Ep1Deal = 0;
//			}
//		}
	}

	deg_Printf("exit usb device mode\n");
}


