/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : gsensor.c
* Author             : zhipen_lin
* Version            : V0726a
* Date               : 09/05/2014
* Description        : This file provides all the sensor  firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

#if(G_SEN_USE == G_SEN_GMA301A)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================

static s16 sen_hold_last_xdata = 0;
static s16 sen_hold_last_ydata = 0;
static s16 sen_hold_last_zdata = 0;


static u8 u8sensor_Read_Gsen_ID(void)
{
    u8 g_sen_id;  
    u8 u8Buf[2]; 
    
    u8Buf[0] = 0x12;
    g_sen_id = (u8)GSensor_ReadRegister(u8Buf,1,1);  
    deg_Printf("g_sen_id=%x\n",g_sen_id);
    return  g_sen_id;      
}

static u8 Gsen_Read_Reg( u8 reg)
{
    u8 val = 0;  
    u8 u8Buf[2]; 
    u8Buf[0] = reg;
    val = (u8)GSensor_ReadRegister(u8Buf,1,1);  
    return  val;    
}

static void Gsen_Write_Reg(u8 reg,u8 data)
{
     u8 u8Buf[2]; 
     u8Buf[0] = reg;
     u8Buf[1] = data;
     GSensor_WriteRegister(u8Buf,1,1);
}


void Gsen_set_Threshold(u8 threshold)
{
	if(bSFBusy_Flag == 0)
	{
		i2c_Init(G_SEN_BAUD, G_SEN_WRITE_ADDR,G_SEN_READ_ADDR);
		Gsen_Write_Reg(0x39,threshold);
		sensor_I2C_port_release();
	}
}
void G_sensor_init(void)
{
	SETB(GSEN_DETECT_PORT_DIR, GSEN_DETECT_PORT_BIT);
	SETB(GSEN_DETECT_PORT_IE, GSEN_DETECT_PORT_BIT);
	CLRB(GSEN_DETECT_PORT_PU, GSEN_DETECT_PORT_BIT);
	CLRB(GSEN_DETECT_PORT_PD, GSEN_DETECT_PORT_BIT);
	if(bSFBusy_Flag == 0)
	{
		i2c_Init(G_SEN_BAUD, G_SEN_WRITE_ADDR,G_SEN_READ_ADDR);
		Gsensor_ID = u8sensor_Read_Gsen_ID();
		if(Gsensor_ID != G_SEN_ID)
		{
			sensor_I2C_port_release();
			return;
		}
		//init gma301
		Gsen_Write_Reg(0x21,0x52);//reset
		Gsen_Write_Reg(0x00,0x02);//
		Gsen_Write_Reg(0x00,0x12);//
		Gsen_Write_Reg(0x00,0x02);//
		Gsen_Write_Reg(0x00,0x82);//
		Gsen_Write_Reg(0x00,0x02);//
		//interrupt setup
		Gsen_Write_Reg(0x11,0x05);//
		Gsen_Write_Reg(0x0E,0x00);//
		//Clear interrupt
		Gsen_Read_Reg(0x1C);//
		Gsen_Read_Reg(0x1D);//
		//Set threshold to maximum.
		Gsen_Write_Reg(0x1F,0x28);//disable micro motion interrupt but enable shake interrupt
		Gsen_Write_Reg(0x38,0xFF);//Always set to maximum
		Gsen_Write_Reg(0x39,0x60);//interrupt threshold
		//Set active
		Gsen_Write_Reg(0x0C,0x8F);//
		Gsen_Write_Reg(0x00,0x06);//
		
		Delay_MS(2);
		Gsen_Read_Reg(0x12);
		Gsen_Read_Reg(0x13);
		Gsen_Read_Reg(0x14);
		Gsen_Read_Reg(0x15);
		Gsen_Read_Reg(0x16);
		Gsen_Read_Reg(0x17);
		Gsen_Read_Reg(0x18);
		Gsen_Read_Reg(0x19);	
		Gsen_Write_Reg(0x1F,0x38);//enable micro motion interrupt
		Delay_MS(1);
		//Clear interrupt
		Gsen_Read_Reg(0x1C);//
		Gsen_Read_Reg(0x1D);//
		Gsen_Write_Reg(0x0E,0x1C);//start int	
	
		sensor_I2C_port_release();
		//deg_Printf("Gsensor GMA301A init finish\n");
	}
}

void Gsen_Int_Set(void)
{
	if(bSFBusy_Flag == 0)
	{
		OSD_changeFlag = 0;
		i2c_Init(G_SEN_BAUD, G_SEN_WRITE_ADDR,G_SEN_READ_ADDR);
		Gsen_Write_Reg(0x11,0x05);//
		Gsen_Write_Reg(0x0E,0x00);//0x0E:To disable Z, Y, and X interrupt
		Gsen_Write_Reg(0x1F,0x28);//disable micro motion interrupt but enable shake interrupt
		//Set threshold 
		Gsen_Write_Reg(0x38,0xFF);//Always set to maximum
		Gsen_Write_Reg(0x39,sys_ctl.Gsensor_senstivity_value);//interrupt threshold
		//Delay_MS(1);
		Gsen_Read_Reg(0x12);
		Gsen_Read_Reg(0x13);
		Gsen_Read_Reg(0x14);
		Gsen_Read_Reg(0x15);
		Gsen_Read_Reg(0x16);
		Gsen_Read_Reg(0x17);
		Gsen_Read_Reg(0x18);
		Gsen_Read_Reg(0x19);	
		Gsen_Write_Reg(0x1F,0x38);//enable micro motion interrupt
		//Delay_MS(1);
		//Clear interrupt
		Gsen_Read_Reg(0x1C);//
		Gsen_Read_Reg(0x1D);//
		Gsen_Write_Reg(0x0E,0x1C);//start int	
	
		sensor_I2C_port_release();
		OSD_changeFlag = 1;
		//deg_Printf("Int_Set ok\n");
	}
}

//======return 0: do nothing , 1: will lock file====
u8 Gsen_check_lock_flag(void)
{
	u8 flag = 0;
	u16 now_xdata,now_ydata,now_zdata;
	u8 now_xdata_L,now_ydata_L,now_zdata_L,now_xdata_H,now_ydata_H,now_zdata_H;
	s16 GsXData,GsYData,GsZData;

	if(bSFBusy_Flag == 0)
	{
		i2c_Init(G_SEN_BAUD, G_SEN_WRITE_ADDR,G_SEN_READ_ADDR);
		Gsen_Read_Reg(0x12);
		Gsen_Read_Reg(0x13);
		
		now_xdata_L = Gsen_Read_Reg(0x14);
		now_ydata_L = Gsen_Read_Reg(0x16);
		now_zdata_L = Gsen_Read_Reg(0x18);
		now_xdata_H = Gsen_Read_Reg(0x15);
		now_ydata_H = Gsen_Read_Reg(0x17);
		now_zdata_H = Gsen_Read_Reg(0x19);
		
		now_xdata = (u16)now_xdata_H<<8 | (u16)now_xdata_L;
		now_ydata = (u16)now_ydata_H<<8 | (u16)now_ydata_L;
		now_zdata = (u16)now_zdata_H<<8 | (u16)now_zdata_L;
		
		sensor_I2C_port_release();
	}
	//deg_Printf("x=%x, y=%x, z=%x\n",now_xdata,now_ydata,now_zdata);
			
	if(((now_xdata)&0x03ff)>=0x0200)
		GsXData =-(512 - (now_xdata&0x1ff));
	else
		GsXData = now_xdata&0x1ff;
		
	if(((now_ydata)&0x03ff)>=0x0200)
		GsYData =-(512 - (now_ydata&0x1ff));
	else
		GsYData = now_ydata&0x1ff;
		
	if(((now_zdata)&0x03ff)>=0x0200)
		GsZData =-(512 - (now_zdata&0x1ff));
	else
		GsZData = now_zdata&0x1ff;
		
	if(((GsXData - sen_hold_last_xdata) > sys_ctl.Gsensor_senstivity_value) || ((GsXData - sen_hold_last_xdata) < -sys_ctl.Gsensor_senstivity_value) )
	{	
		flag = 1;
		//deg_Printf("X=%x\n",GsXData - sen_hold_last_xdata);
	}
		
	if(((GsYData - sen_hold_last_ydata) > sys_ctl.Gsensor_senstivity_value)||((GsYData - sen_hold_last_ydata) < -sys_ctl.Gsensor_senstivity_value))
	{	
		flag = 1;
		//deg_Printf("Y=%x\n",GsYData - sen_hold_last_ydata);
	}
		
	if(((GsZData - sen_hold_last_zdata) > sys_ctl.Gsensor_senstivity_value)||((GsZData - sen_hold_last_zdata) < -sys_ctl.Gsensor_senstivity_value))
	{	
		flag = 1;
		//deg_Printf("Z=%x\n",GsZData - sen_hold_last_zdata);
	}
		
	sen_hold_last_xdata = GsXData;
	sen_hold_last_ydata = GsYData;
	sen_hold_last_zdata = GsZData;

	return flag;
}

#endif