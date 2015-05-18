/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : sensor_SIV100B.c
* Author             : pengtao_zhang
* Version            : V0829a
* Date               : 08/29/2013
* Description        : This file provides all the sensor SIV100B firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"

#if(SEN_USE == SEN_SIV100B)
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================


u8 SIV100BInitTable[][2] =
{
/*
0x04, 0x03,       // setup clock divider and HV-mirror 0x00                   
0x05, 0x07,      // setup VGA output mode                                   
0x11, 0x04,                                                             
0x12, 0x0A,                                                             
0x13, 0x1F,                                                             
0x16, 0x89,                                                             
0x1B, 0x90,                                                             
0x1F, 0x52,                                                             
0x20, 0x00,                                                             
0x21, 0x80,    //0x00                                                           
0x22, 0x61,                                                             
0x34, 0x96,	                                                            
0x33, 0x0C,  //0x08                                                      
0x40, 0x00,  //0x80    AE enable                                         
0x41, 0x82,  //0x80    AE Target                                            
0x42, 0x7F,                                                            	
0x43, 0xC0,                                                            	
0x44, 0x48,	 //0x48                                                    	
0x45, 0x28,                                                            	
0x46, 0x08,                                                              
0x47, 0x15,                                                              
0x48, 0x14,  //0x1E                                                      
0x49, 0x0c,  //0x13                                                      
0x4A, 0x42,  //0x63                                                      
0x4B, 0xC4,                                                             
0x4C, 0x3C,                                                             
0x4E, 0x17,                                                             
0x4F, 0x8A,                                                             
0x50, 0x94,                                                             
0x5A, 0x00,                                                             
0x60, 0xc0,	  //0xd3                                                      
0x61, 0x88,	  //0x08                                                      
0x62, 0x01,                                                             
0x63, 0x80,   //0x80 cr Target                                          
0x64, 0x80,   //0x80 cb Target                                          
0x65, 0xc8,   //0xd2 R Gain Top                                         
0x66, 0x8d,   //0x83 R Gain Bottom                                      
0x67, 0xc3,   //0xd6 B Gain Top                                         
0x68, 0x88,   //0x80 B Gain Bottom                                      
0x69, 0x90,   //0x8a  White Pixel Cr TOP                                
0x6A, 0x68,   //0x73  White Pixel Cr BOT                                
0x6B, 0xa4,	  //0x95  White Pixel Cb TOP                                
0x6C, 0x72,   //0x70  White Pixel Cb BOT                                
0x6D, 0x88,   // White Pixel Cx TOP                                    
0x6E, 0x77,   // White Pixel Cx BOT                                    
0x6F, 0xa8,   //0x46 Average Mode Enable,White Mode Enable             
0x70, 0xD8,   //Luminance TOP                                          
0x71, 0x40,   //Luminance BOT                                          
0x72, 0x05,   //White Mode Minimum White Pixel Count                   
0x73, 0x02,   //Average Mode Detection White Pixel Count               
0x74, 0x0C,   //AWBGRNG 0C                                             
0x75, 0x60,	  //10  BRTSRT                                            
0x76, 0x64,	  //20  BRTEND                                            
0x77, 0xa8,   //B7  BRTRGAIN                                           
0x78, 0x9a,   //95  BRTBGAIN                                           
0x80, 0xAF,                                                             
0x81, 0x19,	   //0x0D Select Sensor's PCLK Polarity,invet VSYNC         
0x82, 0x3D,	   //Y,Cb,Y,Cr Order Sequence    
0x83, 0x00,                                                             
0x86, 0xA1,                                                             
0x87, 0x00,                                                             
0x88, 0x24,	  //0x28 DPC Start Gain                                     
0x89, 0x0F,                                                             
0x92, 0x44,                                                             
0x93, 0x0c,  //0x20 DPC                                                 
0x94, 0x10,  //0x1d                                                      
0x95, 0x18,	 //0x40                                                     
0x96, 0x0c,  //0x10                                                     
0x97, 0x10,  //0x1d                                                     
0x98, 0x14,	 //0x30                                                     
0x99, 0x18,	 //0x24                                                     
0x9A, 0x50,                                                             
0xA4, 0xAA,	 //0xDD  shading                                             
0xA5, 0xAA,	 //0xDD                                                      
0xA6, 0xAA,	 //0xDD                                                      
0xA7, 0xA9,	 //0xDC                                                     
0xA8, 0x87,	 //0xBA                                                     
0xA9, 0x22,	 //0x44                                                      
0xAA, 0x27,	 //0x37                                                      
0xAB, 0x22,	 //0x11                                                      
0xAC, 0x22,	 //0x13                                                      
0xAE, 0x11,	 //0x00                                                      
0xAD, 0x12,	 //0x01                                                      
0xAF, 0x98,                                                             
0xB0, 0x80,   //shading Y-axis center point                              
0xB1, 0x00,   //0x00                                                       
0xB2, 0x04,   //0x02	                                                      
0xB3, 0x0c,   //0x0A	                                                      
0xB4, 0x22,   //0x18	                                                      
0xB5, 0x42,   //0x32	                                                      
0xB6, 0x5d,   //0x48	                                                      
0xB7, 0x72,   //0x5D	                                                      
0xB8, 0x86,   //0x70	                                                      
0xB9, 0x97,   //0x82	                                                      
0xBA, 0xa5,   //0x92	                                                      
0xBB, 0xb2,   //0xA2	                                                      
0xBC, 0xc9,   //0xbe	                                                      
0xBD, 0xdd,   //0xd8	                                                      
0xBE, 0xf0,   //0xee	                                                      
0xBF, 0xf8,   //0xf8	                                                      
0xC0, 0xFF,   //0xFF                                                       
0xC1, 0x3d,  	//0x3D                                                      
0xC2, 0xc6,  	//0xC6                                                      
0xC3, 0xfd,  	//0xFD                                                      
0xC4, 0x10,                                                             
0xC5, 0x21,                                                             
0xC6, 0x10,                                                             
0xC7, 0xf3,   //0xf0                                                      
0xC8, 0xbd,   //0xaa                                                      
0xC9, 0x50,   //0x66                                                      
0xCA, 0x90,                                                               
0xCB, 0x20,	  //0x14     Edge upper gain                                                 
0xCC, 0x28,	  //0x1d                                                      
0xCD, 0x04,                                                               
0xCE, 0x04,                                                               
0xCF, 0x30,	  //0x18                                                      
0xD0, 0x30,   //0x20                                                      
0xD1, 0x28,	  //0x24 Edge start gain                                      
0xD2, 0x86,   //0x66                                                      
0xD3, 0x00,                                                               
0xD4, 0x12,   //0x10 2014.03                                              
0xD5, 0x13,	  //0x12                                                      
0xD6, 0x13,	  //0x12 cb color satuation gain                              
0xD7, 0x00,   //0x00                                                      
0xD8, 0x00,                                                             
0xD9, 0x00,                                                             
0xDA, 0x00,                                                             
0xDB, 0xFF,                                                             
0xDC, 0x00,   //0x0a Y bottom clip value                                  
0xDD, 0xFF,                                                             
0xDE, 0x00,                                                             
0xDF, 0xFF,                                                             
0xE0, 0x00,	                                                            
0xE1, 0x28,	 //0x28   color suppress Start Gain                          
0xE2, 0x46,	 //0x46   color suppress slpoe                               
0xF0, 0x24,                                                              
0xF1, 0x00,                                                              
0xF2, 0x80,                                                              
0xF3, 0x00,     	                                                        
0xF4, 0xE0,                                                              
0x40, 0x80,
0x03, 0xC5,                                                              
0x7A, 0xa3,	 //0x90 R color balance gain                                 
0x7B, 0xB0,  // B color balance gain                                     
0x7C, 0x80,  // G color balance gain 
*/


//============20~25fps============
0x04,0x03,
0x05,0x07,
0x11,0x04,
0x12,0x0a,
0x13,0x1f,
0x16,0x89,
0x1b,0x90,
0x1f,0x52,
0x20,0x00,
0x21,0x20,
0x22,0x41,
0x34,0x34,
0x33,0x0e,
0x40,0x00,
0x41,0x82,
0x42,0x7f,
0x43,0xc0,
0x44,0x48,
0x45,0x28,
0x46,0x08,
0x47,0x15,
0x48,0x14,
0x49,0x0c,
0x4a,0x42,
0x4b,0xc4,
0x4c,0x3c,
0x4e,0x17,
0x4f,0x8a,
0x50,0x94,
0x5a,0x00,
0x60,0xc0,
0x61,0x88,
0x62,0x01,
0x63,0x80,
0x64,0x80,
0x65,0xc8,
0x66,0x8d,
0x67,0xc3,
0x68,0x88,
0x69,0x90,
0x6a,0x68,
0x6b,0xa4,
0x6c,0x72,
0x6d,0x88,
0x6e,0x77,
0x6f,0xa8,
0x70,0xd8,
0x71,0x40,
0x72,0x05,
0x73,0x02,
0x74,0x0c,
0x75,0x60,
0x76,0x64,
0x77,0xa8,
0x78,0x9a,
0x80,0xaf,
0x81,0x19,
0x82,0x3d,
0x83,0x00,
0x86,0xa1,
0x87,0x00,
0x88,0x24,
0x89,0x0f,
0x92,0x44,
0x93,0x0c,
0x94,0x10,
0x95,0x18,
0x96,0x0c,
0x97,0x10,
0x98,0x14,
0x99,0x18,
0x9a,0x50,
0xa4,0xaa,
0xa5,0xaa,
0xa6,0xaa,
0xa7,0xa9,
0xa8,0x87,
0xa9,0x22,
0xaa,0x27,
0xab,0x22,
0xac,0x22,
0xae,0x11,
0xad,0x12,
0xaf,0x98,
0xb0,0x80,
0xb1,0x00,
0xb2,0x04,
0xb3,0x0c,
0xb4,0x22,
0xb5,0x42,
0xb6,0x5d,
0xb7,0x72,
0xb8,0x86,
0xb9,0x97,
0xba,0xa5,
0xbb,0xb2,
0xbc,0xc9,
0xbd,0xdd,
0xbe,0xf0,
0xbf,0xf8,
0xc0,0xff,
0xc1,0x3d,
0xc2,0xc6,
0xc3,0xfd,
0xc4,0x10,
0xc5,0x21,
0xc6,0x10,
0xc7,0xf3,
0xc8,0xbd,
0xc9,0x50,
0xca,0x90,
0xcb,0x20,
0xcc,0x28,
0xcd,0x04,
0xce,0x04,
0xcf,0x30,
0xd0,0x30,
0xd1,0x28,
0xd2,0x86,
0xd3,0x00,
0xd4,0x12,
0xd5,0x13,
0xd6,0x13,
0xd7,0x00,
0xd8,0x00,
0xd9,0x00,
0xda,0x00,
0xdb,0xff,
0xdc,0x00,
0xdd,0xff,
0xde,0x00,
0xdf,0xff,
0xe0,0x00,
0xe1,0x28,
0xe2,0x46,
0xf0,0x24,
0xf1,0x00,
0xf2,0x80,
0xf3,0x00,
0xf4,0xe0,
0x40,0x80,
0x03,0xc5,
0x7a,0xa3,
0x7b,0xb0,
0x7c,0x80,


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
     u8SensorwriteID = SIV100B_I2C_WRITE_ADDR;
     u8SensorreadID = SIV100B_I2C_READ_ADDR;
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
	Delay_MS(280);		//rc reset need delay, IO reset not do it
	#endif

	#if (I2C_MAP == I2C_MAP_SW2)	//select software simulate I2C signal
	bI2CBusy_Flag=0;
	bSFBusy_Flag=0;
	#endif
	//======end close sensor power=======

	//====sensor ldo open======
	REG32(LDO_ACON) |= (2<<4);   //sensor 3bit 111:3.3v,110:3.2v .... 000:2.6v
	REG32(LDO_ACON) |= (1<<7);   //sensor ldo enable
	Delay_MS(50);
	//===end sensor ldo open====
	
     i2c_Init(SIV100B_I2C_BAUD, SIV100B_I2C_WRITE_ADDR,SIV100B_I2C_READ_ADDR);
     CLRB(REG32(PCON0), 23);							//csi Clock Enable Bit


      SENSOR_NRESET();
     Delay_MS(10);
     SENSOR_RESET();
     Delay_MS(10);
     SENSOR_NRESET();
     //SENSOR_NORMAL();
     Delay_MS(10);


	i2c_SendStop();
     SensorId = u8sensor_ReadID();
     for(i=0; i<sizeof(SIV100BInitTable)/2; i++)
     {
         for(j=0; j<(u8Addrbytnum+u8Databytnum); j++) 
         {
             u8Buf[j] = SIV100BInitTable[i][j];    
         }   
         Sensor_WriteRegister(u8Buf,u8Addrbytnum,u8Databytnum);
         Delay_MS(1);
     } 
	sensor_I2C_port_release();
	deg_Printf("SensorId=%x,0x0c is ok\n",SensorId);
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
    u8 u8SIV100BId;
    u8 u8Buf[2];  
    
    u8Buf[0] = SIV100B_CHIP_ID_ADDR;
    u8SIV100BId = (u8)Sensor_ReadRegister(u8Buf,u8Addrbytnum,u8Databytnum); 
    //deg_Printf("u8SIV121DSId=%x\n",u8OV7670Id);
    return  u8SIV100BId;                         
}

//=====flag: 0 is rotate 0',  1 is rotate 180'  flip====
void sensor_rotate(u8 flag)
{

	u8 rot_buf[2];
       i2c_Init(SIV100B_I2C_BAUD, SIV100B_I2C_WRITE_ADDR,SIV100B_I2C_READ_ADDR);
	//deg_Printf("rotate=%x",flag);
	if(0 == flag)
	{
		rot_buf[0] = 0x04;
		rot_buf[1] = 0x03;
		 Sensor_WriteRegister(rot_buf,1,1);
	}
	else if(1 == flag)
	{
		rot_buf[0] = 0x04;
		rot_buf[1] = 0x00;
		 Sensor_WriteRegister(rot_buf,1,1);
	}
	sensor_I2C_port_release();

}


#endif
