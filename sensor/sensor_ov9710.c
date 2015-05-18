/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor_ov9710.c
* Author             : pengtao_zhang
* Version            : V0827a
* Date               : 08/27/2013
* Description        : This file provides all the sensor ov9710 firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

#if(SEN_USE == SEN_OV9710)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================

u8 OV9710InitTable_1280_720[][2] =
{
{0x12,0x80},    
                 
{0x1e,0x07},
{0x5f,0x18},
{0x69,0x04},
{0x65,0x2a},
{0x68,0x0a},
{0x39,0x28},
{0x4d,0x90},
{0xc1,0x80},                                 

{0x96,0xf1},
{0xbc,0x68},

{0x12,0x00},
{0x97,0x80},
{0x17,0x25},
{0x18,0xa2},
{0x19,0x01},
{0x1a,0xca},
{0x03,0x0a},
{0x32,0x07},
{0x98,0x00},
{0x99,0x00},
{0x9a,0x00},
{0x57,0x00},
{0x58,0xc8},
{0x59,0xa0},
{0x4c,0x13},
{0x4b,0x36},
{0x3d,0x3c},
{0x3e,0x03},
{0xbd,0xa0},
{0xbe,0xc8},

{0x4e,0x55},
{0x4f,0x55},
{0x50,0x55},
{0x51,0x55},
{0x24,0x70},//55
{0x25,0x60},//40
{0x26,0xa1},

{0x5c,0x3c},//0x38,//0x3c,//0x59
{0x5d,0x14},
{0x11,0x00},
{0x2a,0x00}, //0x9b
{0x2b,0x07}, //0x06
{0x2d,0x00},
{0x2e,0x00},

{0x13,0x85},//0x85
{0x14,0x40},

{0x04,0xc8},//flip&mirr 
{0x03,0x01},

};


/*******************************************************************************
* Function Name  : sensor_Init
* Description    : initialize the sensor
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u8 sensor_Init(void)
{
     u32 i;
     u8 j;
     u8 u8Buf[2];
	 u8 SensorId;

	 #if(SYS_CLK == 120000000)
		sensor_ClockInit(30000000);//xjc
	 #elif(SYS_CLK == 48000000)
		sensor_ClockInit(24000000);
	 #endif
     u8SensorwriteID = OV9710_I2C_WRITE_ADDR;
     u8SensorreadID  = OV9710_I2C_READ_ADDR;
     u8Addrbytnum = 1;
     u8Databytnum = 1;


	//=======close sensor power ========
	#if (I2C_MAP == I2C_MAP_SW2)			//select software simulate I2C signal
	bI2CBusy_Flag=1;					//set dc check unuse
	bSFBusy_Flag=1;						//set tf card check unuse
	REG32(PMAP_CFG0)  &= ~(1<<14);		//SPI0_MAP0 not mapping to io
	REG32(PMAP_CFG0)  &= ~(1<<7);		// uart not map to io 
	I2C_SCL_SDA_OUT();
	I2C_SCL_LOW();
	I2C_SDA_LOW();
	#endif

	REG32(SYS_CON) = 0x932B;			//SPEC request value
	REG32(LDO_ACON) &= ~(0xf << 4);		//close senosr ldo power

	#if	(USER_CONFIG==CONFIG_AX3251_K6000)		
	Delay_MS(250);		//rc reset need delay, IO reset not do it
	#endif

	#if (I2C_MAP == I2C_MAP_SW2)	//select software simulate I2C signal
	bI2CBusy_Flag=0;
	bSFBusy_Flag=0;
	#endif
	//======end close sensor power=======

	//====sensor ldo open======
	REG32(LDO_ACON) |= (7<<4);   //sensor 3bit 111:3.3v,110:3.2v .... 000:2.6v
	REG32(LDO_ACON) |= (1<<7);   //sensor ldo enable
	Delay_MS(50);
	//===end sensor ldo open====
	
     i2c_Init(OV9710_I2C_BAUD, OV9710_I2C_WRITE_ADDR,OV9710_I2C_READ_ADDR);
     CLRB(REG32(PCON0), 23);							//csi Clock Enable Bit
    
     //SENSOR_PIN_CONF();
     //SENSOR_NORMAL();
    // SENSOR_POWERDN();
     SENSOR_NRESET();
     Delay_MS(10);
     SENSOR_RESET();
     Delay_MS(10);
     SENSOR_NRESET();
   //  SENSOR_NORMAL();
     Delay_MS(10);
     
  	Delay_MS(10);
     SensorId=u8sensor_ReadID();
     for(i=0; i<sizeof(OV9710InitTable_1280_720)/2; i++)
     {
          for(j=0; j<(u8Addrbytnum+u8Databytnum); j++) 
         {
             u8Buf[j] = OV9710InitTable_1280_720[i][j];    
         }   
         Sensor_WriteRegister(u8Buf,u8Addrbytnum,u8Databytnum);
         Delay_MS(1);
     } 
	sensor_I2C_port_release();
	deg_Printf("SensorId=%x\n",SensorId);
       return 0;
}

/*******************************************************************************
* Function Name  : u8sensor_ReadID
* Description    : read sensor chip ID
* Input          : None
* Output         : None
* Return         : sensor chip ID
*******************************************************************************/
u8 u8sensor_ReadID(void)
{
    u8 u8OV9710Id;  
    u8 u8Buf[2]; 

    u8Buf[0] = OV9710_CHIP_ID_ADDR & 0xff;
    u8OV9710Id = (u8)Sensor_ReadRegister(u8Buf,u8Addrbytnum,u8Databytnum);  
    //deg_Printf("u8OV9710Id=%x\n",u8OV9710Id);
    return  u8OV9710Id;               
}


//=====flag: 0 is rotate 0',  1 is rotate 180'  flip====
void sensor_rotate(u8 flag)
{
	u8 rot_buf[2];
	i2c_Init(OV9710_I2C_BAUD, OV9710_I2C_WRITE_ADDR,OV9710_I2C_READ_ADDR);
	//deg_Printf("rotate=%x",flag);
	if(0 == flag)
	{
		rot_buf[0] = 0x04;
		rot_buf[1] = 0xc8;
		 Sensor_WriteRegister(rot_buf,1,1);
		rot_buf[0] = 0x03;
		rot_buf[1] = 0x01;
		 Sensor_WriteRegister(rot_buf,1,1);
		rot_buf[0] = 0x19;
		rot_buf[1] = 0x01;
		 Sensor_WriteRegister(rot_buf,1,1);
	}
	else if(1 == flag)
	{
		rot_buf[0] = 0x04;
		rot_buf[1] = 0x88;
		 Sensor_WriteRegister(rot_buf,1,1);
		rot_buf[0] = 0x03;
		rot_buf[1] = 0x02;
		 Sensor_WriteRegister(rot_buf,1,1);
		rot_buf[0] = 0x19;
		rot_buf[1] = 0x02;
		 Sensor_WriteRegister(rot_buf,1,1);
	}
	sensor_I2C_port_release();
}

#endif
