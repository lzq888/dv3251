/*
 * usb_host_enum.h
 *
 *  Created on: 2013Äê10ÔÂ24ÈÕ
 *      Author: jingcunxu
 */

#ifndef USB_HOST_ENUM_H_
#define USB_HOST_ENUM_H_


// USB specific request
typedef struct
{
    u8  mrequest;
    u8  request;
    u16 value;
    u16 index;
    u16 length;
} SETUP_PKG, *P_SETUP_PKG;

typedef struct
{
    u8 pid;
    u8 payload;
    u8 len;
    u8 *buffer;	// usb transfer buffer must be
    u8 epbulkin;
    u8 epbulkout;
} XXGPKG, *P_XXGPKG;

typedef struct
{
    u8 max_lun;
    u8 cbw_lun;
//  u8 device_online;
    u8 usb_enum_sta;
//  u8 usb_dev_addr;
//  u8 config_index;
//  u8 usb_connect;
//  u8 pkt_per_sec;		// Ã¿¸öÊµ¼ÊSecotrµÄ Óë512µÄ±¶Êý¹ØÏµ
}USB_VA;

typedef union
{
    SETUP_PKG setup;
    u8 set_pkt[8];
} SETUPPKT;

//±ê×¼ÇëÇóÀàÐÍ
#define GET_STATUS      0x00
#define CLEAR_FEATURE   0x01
#define SET_FEATURE     0x03
#define SET_ADDRESS     0x05
#define GET_DESCRIPTOR  0x06
#define SET_DESCRIPTOR  0x07
#define GET_CONFIG      0x08
#define SET_CONFIG      0x09
#define GET_INTERFACE   0x0a
#define SET_INTERFACE   0x0b
#define SYNCH_FRAME     0x0c

//¸ßByte´ú±íÃèÊö·ûÀàÐÍ¼°±àºÅ¡¢µÍByte´ú±íË÷ÒýºÅ
#define DEVICE          0x0100
#define CONFIGURATION   0x0200
#define STRING          0x0300
#define INTERFACE       0x0400
#define ENDPOINT        0x0500


#define PID_SETUP       0xD0
#define PID_IN          0x90
#define PID_OUT         0x10

#define EP0				0
#define EP1				1
#define EP2				2
#define EP3				3


#define MASS_STORAGE_CLASS    0x08

SETUPPKT   setup_pkt;
XXGPKG     usbstack;
USB_VA   usb_var;

u8 usb_dev_addr;
u8 bs_buf[64];

void delay_5ms(u8 n);
u8 enum_usb_dev();

#endif /* USB_HOST_ENUM_H_ */
