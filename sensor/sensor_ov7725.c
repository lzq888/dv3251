/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor_ov7725.c
* Author             : pengtao_zhang
* Version            : V0829a
* Date               : 08/29/2013
* Description        : This file provides all the sensor ov7725 firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

#if(SEN_USE == SEN_OV7725)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================


u8 OV7725InitTable[][2] =
{
	0x12, 0x80,
	0x3d, 0x03,
	0x15, 0x02,
	0x17, 0x22,//{0x17, 0x26}, hstart
	0x18, 0xa8,//{0x18, 0xa0}, hsize
	0x19, 0x07,//{0x19, 0x05}, vstart
	0x1a, 0xf0,//{0x1a, 0xf2}, vsize
	0x32, 0x00,
	0x29, 0xa8,
	0x2c, 0xf0,
	0x65, 0x20,
	0x0c, 0x10,
	0x11, 0x01,
	0x42, 0x7f,
	0x22, 0x7f,
	0x23, 0x03,
	0x63, 0xe0,
	0x64, 0xff,
	0x66, 0x00,
	0x13, 0xff,
	0x0d, 0x41,
	0x0e, 0x65,//0xd5
	0x0f, 0xa5,
	0x14, 0x10,//0x20
	0x22, 0x84,//0x67
	0x23, 0x03,
	0x24, 0x70,//0x60
	0x25, 0x30,//0x40
	0x26, 0xa1,
	0x6b, 0xaa,
	0x90, 0x05,
	0x91, 0x01,
	0x92, 0x03,
	0x93, 0x00,
	0x9c, 0x20,
	0x9e, 0x81,
	0x7e, 0x0c,
	0x7f, 0x16,
	0x80, 0x2a,
	0x81, 0x4e,
	0x82, 0x61,
	0x83, 0x6f,
	0x84, 0x7b,
	0x85, 0x86,
	0x86, 0x8e,
	0x87, 0x97,
	0x88, 0xa4,
	0x89, 0xaf,
	0x8a, 0xc5,
	0x8b, 0xd7,
	0x8c, 0xe8,
	0x8d, 0x20,
	0x94, 0x6a,
	0x95, 0x60,
	0x96, 0x0e,
	0x97, 0x0e,
	0x98, 0x71,
	0x99, 0x83,
	0x9a, 0x1e,
	0x9b, 0x02,
	0x9c, 0x1d,
	0xa6, 0x04,
	0x46, 0x05,
	0x47, 0x21,
	0x48, 0x10,
	0x49, 0x0d,
	0x4a, 0x00,
	0x4b, 0x0a,
	0x4c, 0x11,
	0x10, 0x7f,
	0xac, 0xdf,
	0x8f, 0x05,
	0x09, 0x03,
	0x33, 0x00,
	0x34, 0x00,
	0x2a, 0x00,//0x10
	0x2b, 0x80,
	0x2d, 0x0a,    
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
		sensor_ClockInit(24000000);
	 #elif(SYS_CLK == 48000000)
		sensor_ClockInit(12000000);
	 #endif
     u8SensorwriteID = OV7725_I2C_WRITE_ADDR;
     u8SensorreadID = OV7725_I2C_READ_ADDR;
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
	REG32(LDO_ACON) |= (4<<4);   //sensor 3bit 111:3.3v,110:3.2v .... 000:2.6v
	REG32(LDO_ACON) |= (1<<7);   //sensor ldo enable
	Delay_MS(50);
	//===end sensor ldo open====

     i2c_Init(OV7725_I2C_BAUD, OV7725_I2C_WRITE_ADDR,OV7725_I2C_READ_ADDR);
     CLRB(REG32(PCON0), 23);							//csi Clock Enable Bit
   
     //SENSOR_PIN_CONF();
     //SENSOR_POWERDN();
     SENSOR_NRESET();
     Delay_MS(10);
     SENSOR_RESET();
     Delay_MS(10);
     SENSOR_NRESET();
     //SENSOR_NORMAL();
     Delay_MS(10);

 	i2c_SendStop();
     SensorId = u8sensor_ReadID();
     for(i=0; i<sizeof(OV7725InitTable)/2; i++)
     {
         for(j=0; j<(u8Addrbytnum+u8Databytnum); j++) 
         {
             u8Buf[j] = OV7725InitTable[i][j];    
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
    u8 u8OV7725Id;
    u8 u8Buf[2];  
    
    u8Buf[0] = OV7725_CHIP_ID_ADDR;
    u8OV7725Id = (u8)Sensor_ReadRegister(u8Buf,u8Addrbytnum,u8Databytnum); 
    //deg_Printf("u8OV7670Id=%x\n",u8OV7670Id);
    return  u8OV7725Id;                         
}

//=====flag: 0 is rotate 0',  1 is rotate 180'  flip====
void sensor_rotate(u8 flag)
{

	u8 rot_buf[2];
	 i2c_Init(OV7725_I2C_BAUD, OV7725_I2C_WRITE_ADDR,OV7725_I2C_READ_ADDR);
	//deg_Printf("rotate=%x",flag);
	if(0 == flag)
	{
		rot_buf[0] = 0x0c;
		rot_buf[1] = 0x10;
		 Sensor_WriteRegister(rot_buf,1,1);

	}
	else if(1 == flag)
	{
		rot_buf[0] = 0x0c;
		rot_buf[1] = 0xd0;
		 Sensor_WriteRegister(rot_buf,1,1);
	}

	sensor_I2C_port_release();

}


#endif

