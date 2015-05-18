/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sd.c
* Author             : pengtao_zhang
* Version            : V0625a
* Date               : 06/25/2014
* Description        : This file provides all the sd firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

#define SD_CHECK_BAUD	500000		//初始化sd卡前，先把波特率调低到1m. 否则会有可能出现卡初始化不成功

volatile int bSDCardStatus = CARD_OFFLINE;
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================
 
/*******************************************************************************
* Function Name  : SDInit
* Description    : initialize the  SDCard
* Input          : None
* Output         : BOOL
* Return         : TURE--initialize the  SDCard is right;FALSE--initialize the  SDCard is error
*******************************************************************************/
BOOL bsd_Init(void)
{
    deg_Printf("-------sd init --------------\n");
	InitSDCard();
	//sd_DetectInit();
	//reset sd
	if (!bsd_Reset()) //CMD0
	{
		deg_Printf("reset sd fail !!!\n");
		return FALSE;
	}

	/* forces the card to stop transmission. 
	 * fix bug: some card don't support hotplug. */
	bsd_SendCMD(12, 0);

	//get sd ver
	if (!bsd_GetVer()) //CMD8
	{
		deg_Printf("can't get sd ver\n");
		return FALSE;
	}

	//get all cid
	if (!bsd_GetAllCID()) //CMD2
	{
		deg_Printf("get all cid fail !!!\n");
		return FALSE;
	}

	//deal with rca
	if (!bsd_DealWithRCA()) //CMD3
	{
		deg_Printf("deal with rca fail !!!\n");
		return FALSE;
	}

	//get cid
	if (!bsd_GetCID())   //CMD10
	{
		deg_Printf("get cid fail !!!\n");
		return FALSE;
	}

	//get csd
	if (!bsd_GetCSD())  //CMD9
	{
		deg_Printf("get csd fail !!!\n");
		return FALSE;
	}

	//get sd cap
	if (0 == (g_stcSDInfo.dwCap=dwsd_GetSDCap()))
	{
		deg_Printf("get SDCap fail !!!\n");
		return FALSE;
	}

	//enter transfer state
	if (!bsd_SelectCard())		//CMD7
	{
		deg_Printf("enter transfer state fail !!!\n");
		return FALSE;
	}

	//set block len
	if (!bsd_SetBlockLen())    //CMD16
	{
		deg_Printf("set block len fail !!!\n");
		return FALSE;
	}

	//set bus width
	if (MMC != g_stcSDInfo.eVer)
	{
		if (!bsd_SetBusWidth(TRUE))  //ACMD6
		{
			deg_Printf("set bus width fail !!!\n");
			return FALSE;
		}
	}
	else
	{
		CLRB(REG32(SDC0_CFG0), 7); //bus width = 1
	}

	//check transfer state
	if (!bsd_IsTranState())		//CMD13
	{
		return FALSE;
	}

#if 0
	if(bsd_SetFunc(work_fatfs.win)) {	// support high speed mode
		REG32(SDC0_BAUD) = APB_CLK/(2*SD_HS_CLK) - 1;   //sd_clk=APB_CLK2(SDC0_BAUD+1)=96/8=12M
		SETB(REG32(SDC0_CFG0), 3);						//out rise
		deg_Printf("sd is in high speed mode:%x,%x\n", REG32(SDC0_BAUD),REG32(SDC0_CFG0));
	}
	else {
		REG32(SDC0_BAUD) = APB_CLK/(2*SD_CLK) - 1;   //sd_clk=APB_CLK2(SDC0_BAUD+1)=96/8=12M
		deg_Printf("sd is in normal speed mode:%x\n", REG32(SDC0_BAUD));
		//deg_Printf("SDC0_BAUD = %x \n", REG32(SDC0_BAUD));
	}
#else
	REG32(SDC0_BAUD) = APB_CLK/(2*SD_CLK) - 1;   //sd_clk=APB_CLK/2*(SDC0_BAUD+1)=120/6=20M
	//deg_Printf("sd is in normal speed mode:%x\n", REG32(SDC0_BAUD));
#endif
 
	deg_Printf("\nsd init ok \n");
	deg_Printf("--------------------------\n");
	bSDCardStatus = CARD_READY;
	return TRUE;
}
 


/*******************************************************************************
* Function Name  : sd_Wait74Clk
* Description    : wait 74 clock for delay
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void sd_Wait74Clk(void)
{
	int i = 1200;
	while (i--);
}

/*******************************************************************************
* Function Name  : bsd_DetectIO
* Description    : detect SD IO status
* Input          : None
* Output         : None
* Return         : TURE--SDCard is offline,FALSE--SDCard is not offline
*******************************************************************************/
BOOL bsd_DetectIO(void)
{ 
	BOOL bRes = FALSE;
	
	spi_setCSStatus(1);					//CS HIGH
	CLRB(REG32(PA_DIR), 9);	
	
	SETB(SD_DETECT_PORT_DIR, SD_DETECT_PORT_BIT);
	SETB(SD_DETECT_PORT_IE,SD_DETECT_PORT_BIT);
	SETB(SD_DETECT_PORT_PU, SD_DETECT_PORT_BIT);
	Delay_nopCnt(20);
	if (CHKB(SD_DETECT_PORT_DATA, SD_DETECT_PORT_BIT))
	{
		bRes = TRUE;
	}
	CLRB(SD_DETECT_PORT_DIR, SD_DETECT_PORT_BIT);
	SETB(SD_DETECT_PORT_DATA, SD_DETECT_PORT_BIT);			
	return bRes;
}

/*******************************************************************************
* Function Name  : sd_CheckOffline
* Description    : cheeck if the SDCard is offline
* Input          : None
* Output         : None
* Return         : TURE--SDCard is offline,FALSE--SDCard is not offline
*******************************************************************************/
void sd_CheckOffline(void)
{
#if SD_INS_RESET
	static u32	bSD_ReInit_Flag=0;
#endif 
	if(bsd_DetectIO())
	{
	#if SD_INS_RESET
		bSD_ReInit_Flag=1;
	#endif
		if(!(device_online&BIT(B_SD_ONLINE)))
			return; 

		if (device_remove(DEVICE_SDMMC)) 
		{
			sys_ctl.SD_err_off_flag = 1;
			bSDCardStatus = CARD_OFFLINE;
			put_msg(SDMMC_CHANGE_OUT);
			CLRB(device_online, B_SD_ONLINE);
			g_SystemState = SYSTEM_CARD_ERROR;
			deg_Printf("sd offline\n");
		}	
	}
	else
	{
		if(device_online&BIT(B_SD_ONLINE))
			return;

		if (device_insert(DEVICE_SDMMC)) 
		{
			sys_ctl.SD_err_off_flag = 0;
			bSDCardStatus = CARD_ONLINE;
			put_msg(SDMMC_CHANGE_IN);
			SETB(device_online, B_SD_ONLINE);
			g_SystemState = SYSTEM_IDLE;
			task_video_MD_wait(3);
			deg_Printf("sd online\n");
		#if SD_INS_RESET
			if(bSD_ReInit_Flag)
			{
				bSD_ReInit_Flag = 0;
				sys_wdt_reset();
			}
		#endif
		}
	}
}

void sd_Detect(void)
{
	if(bSFBusy_Flag == 0)
	{
		sd_CheckOffline();
	}
}

//=====return TRUE: is ok , FALSE: sd err=======
BOOL  sd_err_reinit(void)
{
	BOOL bRes = FALSE;
	if(!(device_online&BIT(B_SD_ONLINE)))		//sd off line
		return bRes;
	if(CARD_STANDBY == bSDCardStatus) {
		//select card
		if (!bsd_SelectCard())		//CMD7
		{
			deg_Printf("enter transfer state fail !!!\n");
			bSDCardStatus = CARD_ONLINE;
			return bRes;
		}
		else 
		{
			bSDCardStatus = CARD_READY;
			deg_Printf("enter transfer state OK\n");
		}
	}
	else if(bSDCardStatus != CARD_READY) 
	{
		bsd_Close();
		if(!bsd_Init())
		{
			sys_ctl.SD_err_off_flag = 1;
			g_SystemState = SYSTEM_CARD_ERROR;
			deg_Printf("sd init err!!!!!!!!!!\n");
			return bRes;
		}
		else
		{
			FRESULT ret = f_mount(&work_fatfs, ROOT_DIR_NAME, 1);		/* Give a work area to the default drive */
			//deg_Printf("pass f_mount ret = 0x%x \n",ret);
		}
	}
	bRes = TRUE;
	return bRes;
}


