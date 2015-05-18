/*
 * usb.h
 *
 *  Created on: 2013Äê11ÔÂ7ÈÕ
 *      Author: jingcunxu
 */

#ifndef USB_H_
#define USB_H_


#define usb_deg(data)				deg(data)
#define usb_deg_u8(pstr,data) 		deg_u8(pstr,data)
#define USB_DEVICE_MODE 	1

#define EP0		0
#define EP1     1
#define EP2		2
#define EP3		3



//USB_Power
#define USB_SUSPENDM_EN		(1<<0)
#define USB_SUSPEND_MODE	(1<<1)//in host send suspend signal to target or be a device to into suspend mode
#define USB_RESUME_MODE		(1<<2)//the same to suspend mode
#define USB_RESET_MODE		(1<<3)//read/write in host but read only in peripheral
#define USB_HS_MODE			(1<<4)
#define USB_HS_ENAB			(1<<5)//1:HIGH speed 0:full speed
#define USB_SOFT_CONN		(1<<6)
#define USB_ISO_UPDATE		(1<<7)



//USB_IntrUSB (read only)
//USB_IntrUSBE¶ÔÓ¦ÉèÖÃbit
#define USB_SUSPEND			(1<<0)
#define USB_RESUME			(1<<1)
#define USB_RESET			(1<<2)
#define USB_BABBLE			(1<<2)
#define USB_SOF				(1<<3)
#define USB_CONN			(1<<4)//device connection is detected,only valid in host mode
#define USB_DISCON			(1<<5)
#define USB_SESS_REQ		(1<<6)
#define USB_VBUS_ERR		(1<<7)


//USB_IntrInl¡¢USB_IntrIneh
//USB_IntrInel¡¢USB_IntrIneh ¶ËµãnÆðinÖÐ¶Ï
#define USB_INEP_INT(n)		(1<<n)

//USB_IntrOutl¡¢USB_IntrOuth
//USB_IntrOutel¡¢USB_IntrOuteh ¶ËµãnÆðinÖÐ¶Ï
#define USB_OUTEP_INT(n)	(1<<n)//0 not include



void usb_reset_int(void);
void usb_dma_dpk(u8 epx, u32 adr, u32 cnt, u8 dir);
void usb20_detect();
void usb_clk_set();

#endif /* USB_H_ */
