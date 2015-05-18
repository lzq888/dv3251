/******************** (C) COPYRIGHT 2013 BUILDWIN ************************/
#ifndef _MSG_H_
#define _MSG_H_

#define MSG_DEPTH 15

/***设备在线情况位定义***********/
//#define NO_DEVICE             0  //这个是整byte
#define B_SD_ONLINE		 0  //以下的是相应的位
#define B_USB_DEV_ONLINE     1//card reader
#define B_USB_CAMERA_ONLINE	 2//usb camera
#define B_USB_HOST_ONLINE	 3//udisk





extern volatile u8 msg_pool[MSG_DEPTH];

void msg_init(u8 *msg_pool, u8 depth);
void flush_msg(void);
void put_msg(u8 msg);
u8 get_msg(void);
u8 peek_msg(void);


#endif
