/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : common.h
* Author             : pengtao_zhang
* Version            : V0725a
* Date               : 07/25/2013  ;dd/mm/yyyy
* Description        : common HEADER FILE.
***************************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_


#define REG32(addr)  	*((volatile unsigned long *)(addr))
#define BIT(x)     	(1UL<<(x))

#define	SETB(REG,BIT)			((REG) |= (1UL << (BIT)))
#define	CLRB(REG,BIT)			((REG) &= (~(1UL << (BIT))))
#define	XRLB(REG,BIT)			((REG) ^= (1UL << (BIT)))
#define CHKB(REG,BIT)			(REG & (1UL << BIT))
#define BIT_CK_1(REG,BIT)		(REG & (1UL << BIT))
#define BIT_CK_0(REG,BIT)		(!(REG & (1UL << BIT)))

#define	min(a, b) (((a)<(b))?(a):(b))

#define 	memset__        my_memset
#define 	memcpy__        my_memcpy
#define  	zeromem__		zeromem


enum {
    DEVICE_SDMMC = 0,           //SD/MMC卡
    DEVICE_UDISK,               //U盘

    //DEVICE_LINEIN,              //LINE IN
    DEVICE_PC,                  //连接PC
    //DEVICE_EAR ,                //耳机

    DEVICE_INVALID = 0xff       //无效的设备
};


typedef struct {
    u8 delay;           //处理延时
    u8 cnt;             //稳定计数
    u8 status;          //瞬时状态
    u8 stable;          //稳定状态
} type_dev;

typedef struct {
    u8 dev_num;         //当前激活的设备编号（U盘与SD卡）
    type_dev sd;        //SD/MMC卡
    type_dev udisk;     //连接U盘
    //type_dev line;      //LINE
    type_dev pc;        //连接PC
    //type_dev ear;       //连接耳机
    type_dev reserved;
} DEV_CTL;

DEV_CTL dev_ctl;
#define DEV_TOTAL  4

typedef struct {
	u32* write_itr;
	u32* read_itr;
	u32* buffer;
	s32 bufsize;
}gp_fifo;

int my_strlen(const char *cpSrc);
char * _strcpy(char * dest, const char *src);
void my_memset(void *dst, BYTE val, int cnt);
void zeromem(void *dst, int cnt);
void my_memcpy(void *dst, void *src, int cnt);
int my_mem_cmp(const void* dst, const void* src, u8 cnt);
BOOL bmemcmp(void *dst, void *src, u32 byte_len);
s8 datacmp(u32 dst, u32 src);
void Delay_nopCnt(u32 cnt);
void Delay_MS(u32 u32MS);
void Delay_10US(u32 u32MS);
#if 1
DWORD XCHDWORD(DWORD dwXCHData);
WORD XCHWORD(WORD wXCHData);
#endif


bool device_insert(u8 dev_num);
bool device_remove(u8 dev_num);
void device_init(void);

void gp_fifo_ctr(volatile gp_fifo* fifo_ptr,u32* buffer_ptr,s32 size);
u32 gp_fifo_read(volatile gp_fifo* fifo_ptr);
u32 gp_fifo_look(volatile gp_fifo* fifo_ptr);
void gp_fifo_write(volatile gp_fifo* fifo_ptr,u32 element);
u32 gp_fifo_num_ele_ava(volatile gp_fifo* fifo_ptr);
#endif
