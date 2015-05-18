/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : common.c
* Author             : pengtao_zhang
* Version            : V0725a
* Date               : 07/25/2013   ; mm/dd/yyyy
* Description        : This file provides all the common functions.
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
//===================================================================

int my_strlen(const char *cpSrc)
{
        const char *cpTemp = cpSrc;
        while(*cpTemp++);
        return cpTemp-cpSrc-1;
}
 
/*******************************************************************************
* Function Name  : my_memset
* Description    : write value to mem
* Input          : *dst: destination pointer
*                  val : value
*                  cnt :length
* Output         : None
* Return         : None
*******************************************************************************/
void my_memset(void *dst, BYTE val, int cnt)
{
	BYTE *pDstTemp = (BYTE *)dst;
	while (cnt--)
	{
		*pDstTemp++ = val;
	}
}

/*******************************************************************************
* Function Name  : zeromem
* Description    : clear mem to 0
* Input          : *dst: destination pointer
*                  cnt :length
* Output         : None
* Return         : None
*******************************************************************************/
void zeromem(void *dst, int cnt)
{
	my_memset(dst, 0, cnt);
}

/*******************************************************************************
* Function Name  : my_memcpy
* Description    : copy data from src to dst
* Input          : *dst: destination pointer
*                  *src: source pointer
*                  cnt :length
* Output         : None
* Return         : None
*******************************************************************************/
void my_memcpy(void *dst, void *src, int cnt)
{
	BYTE *pDstTemp = (BYTE *)dst;
	BYTE *pSrcTemp = (BYTE *)src;
	while (cnt--)
	{
		*pDstTemp++ = *pSrcTemp++;
	}
}

/* Compare memory to memory */
int my_mem_cmp(const void* dst, const void* src, u8 cnt)
{
    const char *d = (const char *)dst, *s = (const char *)src;
    int r = 0;
    while (cnt-- && (r = *d++ - *s++) == 0) ;
    return r;
}


/*******************************************************************************
* Function Name  : bmemcmp
* Description    : compare src and dst data same or different
* Input          : *dst: destination pointer
*                  *src: source pointer
*                  cnt :length
* Output         : None
* Return         : 0:different; 1:same
*******************************************************************************/
BOOL bmemcmp(void *dst, void *src, u32 byte_len)
{
    int i = 0;
    u8 *dst_u8 = (u8*)dst;
    u8 *src_u8 = (u8*)src;
    for(i=0; i<byte_len;)
    {
       if(dst_u8[i] != src_u8[i]) 
       {
          return 0;
       }   
       i++;     
       if(i%0x100000 == 0x00)
       {
          deg_Printf("cmp len = ",i);              
       }
    }
    return 1;
}

/*******************************************************************************
* Function Name  : datacmp
* Description    : u32 data compare
* Input          : dst: destination data
*                  src: source data
* Output         : None
* Return         : 0:same; 1:dst>src ; -1:dst<src
*******************************************************************************/
s8 datacmp(u32 dst, u32 src)
{
	s8 res = 0;
	if(dst > src)
		res = 1;
	else if(dst == src)
		res = 0;
	else if(dst < src)
		res = -1;

	return res;
}


/**
 * strcpy - Copy a %NUL terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 */
char * _strcpy(char * dest, const char *src) {
	char *tmp = dest;

	while ((*dest++ = *src++) != '\0');
	return tmp;
}

/**
 * strncmp - Compare two length-limited strings
 * @cs: One string
 * @ct: Another string
 * @count: The maximum number of bytes to compare
 */
int _strncmp(const char * cs, const char * ct, unsigned int count) {
	register signed char __res = 0;

	while (count) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
		count--;
	}

	return __res;
}

/*******************************************************************************
* Function Name  : Delay_Cnt
* Description    : delay cnt nop
* Input          : nop number
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_nopCnt(u32 cnt)
{
	while(cnt-->0)
	{
		asm("nop");
	}
}

/*******************************************************************************
* Function Name  : Delay_MS
* Description    : delay,fsys = 48M
* Input          : delay number(ms)
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_MS(u32 u32MS)
{
	u32Delay_1msCnt = 0;
	while (u32Delay_1msCnt < u32MS);
}

/*******************************************************************************
* Function Name  : Delay_US
* Description    : delay
* Input          : delay number(10us)
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_10US(u32 u32US)
{
    int iUSCnt;

	while (u32US-- > 0)
	{
        iUSCnt = 38;
		while (iUSCnt-- > 0)
		{
			asm("nop");
		}
	}
}
#if 1
/*******************************************************************************
* Function Name  : XCHDWORD
* Description    : exchange DWORD data high_low byte
* Input          : Before the exchange of data
* Output         : None
* Return         : After an exchange of data
*******************************************************************************/
DWORD XCHDWORD(DWORD dwXCHData)
{
	DWORD dwXCHDataTmp;

	((BYTE *)(&dwXCHDataTmp))[0] = ((BYTE *)(&dwXCHData))[3];
	((BYTE *)(&dwXCHDataTmp))[1] = ((BYTE *)(&dwXCHData))[2];
	((BYTE *)(&dwXCHDataTmp))[2] = ((BYTE *)(&dwXCHData))[1];
	((BYTE *)(&dwXCHDataTmp))[3] = ((BYTE *)(&dwXCHData))[0];

	return dwXCHDataTmp;
}

/*******************************************************************************
* Function Name  : XCHWORD
* Description    : exchange WORD data high_low byte
* Input          : Before the exchange of data
* Output         : None
* Return         : After an exchange of data
*******************************************************************************/
WORD XCHWORD(WORD wXCHData)
{
	WORD wXCHDataTmp;

	((BYTE *)(&wXCHDataTmp))[0] = ((BYTE *)(&wXCHData))[1];
	((BYTE *)(&wXCHDataTmp))[1] = ((BYTE *)(&wXCHData))[0];

	return wXCHDataTmp;
}
#endif

void device_init(void)
{
    my_memset(&dev_ctl, 0, sizeof(dev_ctl));
    dev_ctl.sd.delay = 5;              //延时50MS
    //dev_ctl.line.delay = 40;            //延时100MS
    dev_ctl.pc.delay = 50;              //延时50MS
    dev_ctl.udisk.delay = 50;           //延时50MS
    //dev_ctl.ear.delay = 20;             //延时100MS
	
	device_online = 0;	
}

type_dev *device_get(u8 dev_num)
{
    if (dev_num >= DEV_TOTAL) 
	{
        return NULL;
    }
    return (&dev_ctl.sd + dev_num);
}


bool device_status_stable(u8 dev_num, u8 new_sta)
{
    type_dev *dev = device_get(dev_num);

    if (dev == NULL) 
	{
		deg("dev == NULL\n");
        return false;
    }

    if (dev->status == new_sta) 
	{
        dev->cnt++;
    } 
	else 
	{
        dev->status = new_sta;
        dev->cnt = 0;
    }

    if (dev->stable == new_sta) 
	{
        return false;               //状态不变
    }
    if (dev->cnt < dev->delay) 
	{    
		//消抖处理。插入和拔除都需要
        return false;
    }
    dev->stable = new_sta;
    return true;                    //状态发生变化
}

//设备插入
bool device_insert(u8 dev_num)
{
    return device_status_stable(dev_num, 1);
}

//设备移除
bool device_remove(u8 dev_num)
{
    return device_status_stable(dev_num, 0);
}


void gp_fifo_ctr(volatile gp_fifo* fifo_ptr,u32* buffer_ptr,s32 size)
{
	s32 i = 0;
	fifo_ptr->buffer = buffer_ptr;
	fifo_ptr->write_itr = &fifo_ptr->buffer[0];
	fifo_ptr->read_itr = &fifo_ptr->buffer[0];
	fifo_ptr->bufsize = size;
	for(i=0;i<size;i++)
		buffer_ptr[i]=0;
}

u32 gp_fifo_read(volatile gp_fifo* fifo_ptr)
{
	u32 cur_val = *fifo_ptr->read_itr;
	fifo_ptr->read_itr++;
	if(fifo_ptr->read_itr > &fifo_ptr->buffer[fifo_ptr->bufsize-1])
		fifo_ptr->read_itr = &fifo_ptr->buffer[0];
	return cur_val;
}

u32 gp_fifo_look(volatile gp_fifo* fifo_ptr)
{
	return *fifo_ptr->read_itr;
}

void gp_fifo_write(volatile gp_fifo* fifo_ptr,u32 element)
{
	*fifo_ptr->write_itr = element;
	fifo_ptr->write_itr++;
	if(fifo_ptr->write_itr > &fifo_ptr->buffer[fifo_ptr->bufsize-1])
		fifo_ptr->write_itr = &fifo_ptr->buffer[0];
}

u32 gp_fifo_num_ele_ava(volatile gp_fifo* fifo_ptr)
{
	if( fifo_ptr->write_itr >= fifo_ptr->read_itr)
		return (fifo_ptr->write_itr -fifo_ptr->read_itr);
	else
		return (fifo_ptr->read_itr - fifo_ptr->write_itr);
}
