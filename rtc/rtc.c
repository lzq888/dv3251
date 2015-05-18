/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : rtc.c
* Author             : pengtao_zhang
* Version            : V0726a
* Date               : 07/26/2013  ;mm/dd/yyyy
* Description        : This file provides all the rtc firmware functions.
***************************************************************************/
//===================================================================
//                                                     	            |
//                       INCLUDE FILES                              |
//                                                                  |
//===================================================================
#include "../header/include.h"
#if 1
//===================================================================
//                                                     	            |
//                      GLOBAL VARIABLE                             |
//                                                                  |
//===================================================================
const int daysPerMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};

/*******************************************************************************
* Function Name  : rtc_Init
* Description    : rtc initialize
* Input          : none
* Output         : none
* Return         : none
*******************************************************************************/
void rtc_Init(void)
{
/*	REG32(CLKCON0) &= ~(3<<2);
	REG32(CLKCON0) |= (1<<2);     //rc select 2M
	REG32(CLKCON0) &= ~BIT(9);    //rtc clk select rc 32k
*/
/*	REG32(CLKCON2) &= ~(3<<10);   //select 12M OSC
	REG32(CLKCON2) |= BIT(10);
	REG32(CLKCON2) &= ~BIT(8);   //TWO PIN
	REG32(CLKCON2) |= BIT(7);    //12M enable
	REG32(CLKCON0) |= BIT(9);    //rtc clk select external OSC
*/

	REG32(PCON0) &= ~BIT(20);    //rtc clk enable
	rtc_WriteCfg(0x1d);         //rtc clk select internal 32K

	u8 temp[4] = {0};
	rtc_ReadRam(temp,0,4);
	if(1==temp[0] && 2==temp[1] && 4==temp[2] && 8==temp[3] )
	{
		
	}
	else	
	{
		temp[0] = 1;
		temp[1] = 2;
		temp[2] = 4;
		temp[3] = 8;
		rtc_WriteRam(temp,0,4);			//write first rtc work flag
		rtc_WriteTime(2014,3,3,23,59,59);	//write rtc time
	}
}

/*******************************************************************************
* Function Name  : rtc_Byte
* Description    : write data and return new data
* Input          : data
* Output         : none
* Return         : new data
*******************************************************************************/
u8 rtc_Byte(u8 x)
{
	REG32(IRT_DATA) = x;
	while(REG32(IRT_CFG) & 0x08);
	return REG32(IRT_DATA);
}

/*******************************************************************************
* Function Name  : irtcc_write_cfg
* Description    : write RTC configure register
* Input          : cfg : config data
* Output         : none
* Return         : none
*******************************************************************************/
void rtc_WriteCfg (u8 cfg)
{
	REG32(IRT_CFG) |= BIT(8);  //rtc communication enable
	rtc_Byte(RTC_WRITE_CFG);
	rtc_Byte(cfg);
	REG32(IRT_CFG) &= ~BIT(8);  //rtc communication disable
}

/*******************************************************************************
* Function Name  : rtc_ReadCfg
* Description    : read RTC configure data
* Input          : none
* Output         : none
* Return         : read data
*******************************************************************************/
u8 rtc_ReadCfg(void)
{
	u8 u8Ret;

	REG32(IRT_CFG) |= BIT(8);  //rtc communication enable
	rtc_Byte(RTC_READ_CFG);
	u8Ret = rtc_Byte(0x00);
	REG32(IRT_CFG) &= ~BIT(8);  //rtc communication disable
	return u8Ret;
}

/*******************************************************************************
* Function Name  : rtc_WriteRam
* Description    : write data to RTC ram
* Input          : buf: data
* 				   adr: RAM address
* 				   len:data length
* Output         : none
* Return         : none
*******************************************************************************/
void rtc_WriteRam(u8 *buf,u8 adr, u8 len)
{
	u8 i;

	REG32(IRT_CFG) |= BIT(8);  //rtc communication enable
	rtc_Byte(RTC_WRITE_RAM);
	rtc_Byte(adr);
	for(i=0; i<len; i++)
	{
		rtc_Byte(buf[i]);
	}
	REG32(IRT_CFG) &= ~BIT(8);  //rtc communication disable
}

/*******************************************************************************
* Function Name  : rtc_ReadRam
* Description    : read data from RTC ram
* Input          : buf: data
* 				   adr: RAM address
* 				   len:data length
* Output         : none
* Return         : none
*******************************************************************************/
void rtc_ReadRam(u8 *buf,u8 adr, u8 len)
{
	u8 i;

	REG32(IRT_CFG) |= BIT(8);  //rtc communication enable
	rtc_Byte(RTC_READ_RAM);
	rtc_Byte(adr);
	for(i=0; i<len; i++)
	{
		buf[i] = rtc_Byte(0x00);
	}
	REG32(IRT_CFG) &= ~BIT(8);  //rtc communication disable
}

/*******************************************************************************
* Function Name  : rtc_WriteCnt
* Description    : write RTC data
* Input          : cmd: RTC_WIRTE_TIM,RTC_WIRTE_ALM
                 : counter: time
* Output         : none
* Return         : none
*******************************************************************************/
void rtc_WriteCnt(u8 cmd, u32 counter)
{
	REG32(IRT_CFG) |= BIT(8);  //rtc communication enable
	rtc_Byte(cmd);
	rtc_Byte(counter >> 24);
	rtc_Byte(counter >> 16);
	rtc_Byte(counter >> 8);
	rtc_Byte(counter);
	REG32(IRT_CFG) &= ~BIT(8);  //rtc communication disable
}

/*******************************************************************************
* Function Name  : rtc_ReadCnt
* Description    : READ RTC  data
* Input          : cmd: RTC_READ_TIM,RTC_READ_ALM
* Output         : none
* Return         : time
*******************************************************************************/
u32 rtc_ReadCnt(u8 cmd)
{
    u32 u32RecvTmp;
    u32 u32RetVal = 0;

    REG32(IRT_CFG) |= BIT(8); //IRTCC communications enable
    rtc_Byte(cmd);
    u32RecvTmp = rtc_Byte(0x00);
    u32RetVal = u32RecvTmp << 24;
    u32RecvTmp = rtc_Byte(0x00);
    u32RetVal += u32RecvTmp << 16;
    u32RecvTmp = rtc_Byte(0x00);
    u32RetVal += u32RecvTmp << 8;
    u32RetVal += rtc_Byte(0x00);
    REG32(IRT_CFG) &= ~BIT(8); //IRTCC communications disable
    return u32RetVal;
}

/*******************************************************************************
* Function Name  : iIsLeapYear
* Description    : calculate  Leap Year
* Input          : year
* Output         : none
* Return         : 1:Leap Year
*                  0:not Leap Year
*******************************************************************************/
u32 isLeapYear(int year)
{
	if(((year%4==0)&&(year%100!=0))||(year%400==0))
		return 1;
	else
		return 0;
}

/*******************************************************************************
* Function Name  : byte2Dec
* Description    : hex to decimal
* Input          : src :hex
* 				   dest:decimal
* Output         : none
* Return         : none
*******************************************************************************/
void byte2Dec(u8 src , u8* dest)//in 100, hex to dec
{
	u8 temp = src / 10;
	dest[0] = '0'+temp;
	dest[1] = '0' + src -temp*10;
}

/*******************************************************************************
* Function Name  : now
* Description    : update date
* Input          : date pointer
* Output         : none
* Return         : none
*******************************************************************************/
void now(date *datePtr)
{
	datePtr->year = YEAR;
	datePtr->month = 1;
	datePtr->day = 1;

	u32 secCount = rtc_ReadCnt(RTC_READ_TIM);

	u32 days = secCount / (24*60*60);
	secCount -= days * (24*60*60);
	datePtr->hour = secCount /(60*60);
	secCount -= datePtr->hour * (60*60);
	datePtr->min = secCount / 60;
	datePtr->sec = secCount - datePtr->min * 60;

	while(1)//Calc the year
	{
		u32 theYearDays = 365;
		theYearDays += isLeapYear(datePtr->year);
		if (days < theYearDays)
			break;	//less one year
		datePtr->year++;
		days -= theYearDays;
	}

	while(1) //calc the month
	{
		u32 theMonDays = daysPerMonth[datePtr->month-1];
		if(datePtr->month == 2)
			theMonDays += isLeapYear(datePtr->year);
		if(days+1<=theMonDays)
		{
			datePtr->day+=days;
			break;
		}
		datePtr->month++;
		days-=theMonDays;
	}

}

/*******************************************************************************
* Function Name  : CalcTimeInfo
* Description    : calculate time and ouput decimal number
* Input          : Time Info Buff
* Output         : none
* Return         : none
*******************************************************************************/
void CalcTimeInfo(u8* buf)
{
	u32 temp;
	date today;
	now(&today);
	//year
	temp = today.year - YEAR;
	buf[0] = '2';
	buf[1] = '0';
	while (temp>99)
	{
		buf[1]++;
		temp-=100;
	}
    byte2Dec((u8)temp,buf+2);
	buf[4] = '/';

	//mon
	byte2Dec((u8)today.month,buf+5);
	buf[7] = '/';

	//day
	byte2Dec((u8)today.day,buf+8);
	buf[10] = ' ';

	//hour
	byte2Dec((u8)today.hour,buf+11);
	buf[13] = ':';

	//min
	byte2Dec((u8)today.min,buf+14);
	buf[16] = ':';

	//sec
	byte2Dec((u8)today.sec,buf+17);
//	buf[19] = ' ';					//over the mem,so remove
}

/*******************************************************************************
* Function Name  : rtc_WriteTime
* Description    : wite time into RTC ram
* Input          : u16 year,u8 month,u8 day,u8 hour,u8 minute,u8 second
* Output         : none
* Return         : none
*******************************************************************************/
void rtc_WriteTime(u16 year,u8 month,u8 day,u8 hour,u8 minute,u8 second)
{
	U32 u32Seconds = 0;
	U32 u32Days = 0;

	if(year < 2000 || month>12 || day>31 || hour >23 || minute>59 || second>59)
	{
		return;
	}

	while(month>1)
	{
		month--;
		u32Days+=daysPerMonth[(month-1)];
		if(month == 2 && isLeapYear(year))
			u32Days++;
	}
	while(year> 2000)
	{
		year--;
		u32Days+= 365;
		if(isLeapYear(year))
			u32Days++;
	}

	u32Days += day-1;
	u32Seconds += 86400*u32Days;
	u32Seconds += 3600*hour;
	u32Seconds += 60*minute;
	u32Seconds += second;

	rtc_WriteCnt(RTC_WRITE_TIM, u32Seconds);
}

void rtc_set_wko_down()
{
	u32 temp = 0;
	temp = rtc_ReadCnt(RTC_READ_WKPCON);
	//deg_Printf("down temp = 0x%x\n",temp);
	temp |= 0x40000000;							//output  pull down
 	rtc_WriteCnt(RTC_WRITE_WKPCON,temp);
	//deg_Printf("down temp = 0x%x\n",temp);
}

void rtc_set_wko_up()
{
	u32 temp = 0;
	temp = rtc_ReadCnt(RTC_READ_WKPCON);
	//deg_Printf("up temp = 0x%x\n",temp);
	temp &= 0xbfffffff;							//output pull up
 	rtc_WriteCnt(RTC_WRITE_WKPCON,temp);
	//deg_Printf("up temp = 0x%x\n",temp);
}


//========creat file for updata data==========
void rtc_check_updata_time_from_txt()
{
	u32 ret;
	FIL rtc_file;
	date rtc_time;
	u8 rtc_timebuf[]="2015-03-03,23:59:59";
	ret =  f_open(&rtc_file,(char const *)"settime.txt", FA_WRITE | FA_READ);
	if(ret == FR_OK)		//file on
	{
		u32 read;
		deg_Printf("fopen rtc file  ok\n");
		f_read(&rtc_file,&rtc_timebuf, sizeof(rtc_timebuf),&read);
		f_close(&rtc_file);
		deg_Printf("fread rtc file size=%d,string=%s\n",read,rtc_timebuf);

	}
	else			//not find file ,creat new one
	{
		u32 writed;
		ret =  f_open(&rtc_file,(char const *)"settime.txt", FA_CREATE_NEW| FA_WRITE | FA_READ);
		deg_Printf("create rtc file ret = %d\n",ret);
		if(FR_OK != ret)
		{
			return FALSE;
		}
		f_write(&rtc_file,&rtc_timebuf, sizeof(rtc_timebuf),&writed);
		f_close(&rtc_file);
		deg_Printf("fwrite rtc file size %d\n",writed);
	}

	//======check if need updata rtc time=====
	if(!((rtc_timebuf[0]=='2')&&(rtc_timebuf[1]=='0')&&(rtc_timebuf[2]=='1')&&(rtc_timebuf[3]=='5')&&(rtc_timebuf[5]=='0')&&(rtc_timebuf[6]=='3')\
		&&(rtc_timebuf[8]=='0')&&(rtc_timebuf[9]=='3')&&(rtc_timebuf[11]=='2')&&(rtc_timebuf[12]=='3')&&(rtc_timebuf[14]=='5')&&(rtc_timebuf[15]=='9')\
		&&(rtc_timebuf[17]=='5')&&(rtc_timebuf[18]=='9')))
	{
		rtc_time.year = 1000*(rtc_timebuf[0]-'0')+100*(rtc_timebuf[1]-'0')+10*(rtc_timebuf[2]-'0')+(rtc_timebuf[3]-'0');
		rtc_time.month = 10*(rtc_timebuf[5]-'0')+(rtc_timebuf[6]-'0');
		rtc_time.day =10*(rtc_timebuf[8]-'0')+(rtc_timebuf[9]-'0');
		rtc_time.hour=10*(rtc_timebuf[11]-'0')+(rtc_timebuf[12]-'0');
		rtc_time.min =10*(rtc_timebuf[14]-'0')+(rtc_timebuf[15]-'0');
		rtc_time.sec =10*(rtc_timebuf[17]-'0')+(rtc_timebuf[18]-'0');

		u8 temp[4] = {0};		
		temp[0] = 1;
		temp[1] = 2;
		temp[2] = 4;
		temp[3] = 8;
		rtc_WriteRam(temp,0,4);			//write first rtc work flag
		rtc_WriteTime(rtc_time.year ,rtc_time.month,rtc_time.day,rtc_time.hour,rtc_time.min,rtc_time.sec);	//write rtc time
		deg_Printf("updata rtc time %s\n",rtc_timebuf);

		//=====set default value===
		u32 writed;
		u8 rtc_timebuf[]="2015-03-03,23:59:59";
		ret =  f_open(&rtc_file,(char const *)"settime.txt", FA_WRITE | FA_READ);
		f_write(&rtc_file,&rtc_timebuf, sizeof(rtc_timebuf),&writed);
		f_close(&rtc_file);
		//=====end set default value===

		return TRUE;
	}

}


#endif


