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

#if(G_SEN_USE == G_SEN_DMARD07)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================
#define G_SEN_16G     			(0x3<<6)
#define G_SEN_32G     			(0x1<<6)
#define G_SEN_64G     			(0x0<<6)

#define G_SEN_XG_CONF			G_SEN_64G


static s8 sen_hold_last_xdata = 0;
static s8 sen_hold_last_ydata = 0;
static s8 sen_hold_last_zdata = 0;


static u8 u8sensor_Read_Gsen_ID(void)
{
    u8 g_sen_id;  
    u8 u8Buf[2]; 
    
    u8Buf[0] = 0x0f;
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

//======must i2c inited before call this fun========
u8 Gsen_Get_Temperature()
{
	u8 val;
	u8 tem = 25;
	val = Gsen_Read_Reg(0x40);		//temperature data
	tem = 25 + val/2;
	deg_Printf("tem = 0x%x\n",tem);
}

u8 Gsen_Get_X_acceleration()
{
	u8 val;
	val = Gsen_Read_Reg(0x41);		//x data
	deg_Printf("xval = 0x%x\n",val);
	return val;
}

u8 Gsen_Get_Y_acceleration()
{
	u8 val;
	val = Gsen_Read_Reg(0x42);		//y data
	deg_Printf("yval = 0x%x\n",val);
	return val;
}

u8 Gsen_Get_Z_acceleration()
{
	u8 val;
	val = Gsen_Read_Reg(0x43);		//z data
	deg_Printf("zval = 0x%x\n",val);
	return val;
}

u8 Gsen_Get_data_status()
{
	u8 val;
	val = Gsen_Read_Reg(0x49);		//data status
	deg_Printf("sta = 0x%x\n",val);
}

void Gsen_set_Threshold(u8 threshold)
{
	
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
		Gsen_Write_Reg(0x44,0x28);		//setting normal not int
		Gsen_Write_Reg(0x45,(G_SEN_XG_CONF | 0x20));
		sen_hold_last_xdata = Gsen_Read_Reg(0x41);
		sen_hold_last_ydata = Gsen_Read_Reg(0x42);
		sen_hold_last_zdata = Gsen_Read_Reg(0x43);
		sensor_I2C_port_release();
	}
}

void Gsen_Int_Set(void)
{
	
}

//======return 0: do nothing , 1: will lock file====
u8 Gsen_check_lock_flag(void)
{
	u8 flag = 0;
	u8 now_xdata,now_ydata,now_zdata;
	s8 GsXData,GsYData,GsZData;
	
	if(bSFBusy_Flag == 0)
	{
		i2c_Init(G_SEN_BAUD, G_SEN_WRITE_ADDR,G_SEN_READ_ADDR);
		now_xdata = Gsen_Read_Reg(0x41);
		now_ydata = Gsen_Read_Reg(0x42);
		now_zdata = Gsen_Read_Reg(0x43);
		sensor_I2C_port_release();
	}
	//deg_Printf("x=%x, y=%x, z=%x\n",now_xdata,now_ydata,now_zdata);
	if((now_xdata&0xff) >= 0x80)
		GsXData =-(128 - (now_xdata&0x7f));
	else
		GsXData = now_xdata&0x7f;
		
	if((now_ydata&0xff) >= 0x80)
		GsYData =-(128 - (now_ydata&0x7f));
	else
		GsYData = now_ydata&0x7f;
		
	if((now_zdata&0xff) >= 0x80)
		GsZData =-(128 - (now_zdata&0x7f));
	else
		GsZData = now_zdata&0x7f;
	
	if(((GsXData - sen_hold_last_xdata) > sys_ctl.Gsensor_senstivity_value)||((GsXData - sen_hold_last_xdata) < -sys_ctl.Gsensor_senstivity_value) )
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