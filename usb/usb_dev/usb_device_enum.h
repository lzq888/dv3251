/*
 * usb_device_enum.h
 *
 *  Created on: 2013Äê11ÔÂ7ÈÕ
 *      Author: jingcunxu
 */

#ifndef USB_DEVICE_ENUM_H_
#define USB_DEVICE_ENUM_H_

#define		VID			0x8888
#define		PID			0x3251     //PID  MS+UVC:0x3231; MS:0x3241; UVC:0x3251


#define		EP0_IDLE_STATE				0
#define		EP0_RX_STATE			1
#define		EP0_TX_STATE			2

//String Index
#define ID_LANGUAGE                     0x00
#define ID_MANUFACTURE                  0x01   	
#define ID_PRODUCT                      0x02	
#define ID_SERIAL			            0x03

#define USB_UAC_SUPPORT			1		//audio support
#define USB_UDISK_SUPPORT			1		//usb cardreader support
#define USB_UVC_SUPPORT			1		//vedio support

#define 	EP0_BUF_SIZE			64          // occupies 64 bytes

//Setup Command Const
#define SC_GET_STATUS			        0x00	//; Setup command: Get Status
#define SC_CLEAR_FEATURE		        0x01	//; Setup command: Clear Feature
#define SC_RESERVED			            0x02	//; Setup command: Reserved
#define SC_SET_FEATURE			        0x03	//; Setup command: Set Feature
#define SC_SET_ADDRESS			        0x05	//; Setup command: Set Address
#define SC_GET_DESCRIPTOR		        0x06	//; Setup command: Get Descriptor
#define SC_SET_DESCRIPTOR		        0x07	//; Setup command: Set Descriptor
#define SC_GET_CONFIGURATION		    0x08	//; Setup command: Get Configuration
#define SC_SET_CONFIGURATION		    0x09	//; Setup command: Set Configuration
#define SC_GET_INTERFACE		        0x0a	//; Setup command: Get Interface
#define SC_SET_INTERFACE		        0x0b	//; Setup command: Set Interface
#define SC_SYNC_FRAME			        0x0c	//; Setup command: Sync Frame
#define SC_ANCHOR_LOAD			        0xa0	//; Setup command: Anchor load

#define DEVICE_DESCRIPTOR               0x01	//; Get device descriptor: Device
#define CONFIGURATION_DESCRIPTOR	    0x02	//; Get device descriptor: Configuration
#define STRING_DESCRIPTOR			    0x03	//; Get device descriptor: String
#define	INTERFACE_DESCRIPTOR			0x04
#define	ENDPOINT_DESCRIPTOR				0x05
#define DEVICE_QUALIFIER_DESCRIPTOR     0x06
#define OTHER_SPEED_CONFIG_DESCRIPTOR   0x07



#define UVC_5FPS_LEB0	0x80		// 5 fps, little endian byte 0 (lowest order byte)
#define UVC_5FPS_LEB1	0x84		// 5 fps, little endian byte 1
#define UVC_5FPS_LEB2	0x1E		// 5 fps, little endian byte 2
#define UVC_5FPS_LEB3	0x00		// 5 fps, little endian byte 3 (highest order byte)

#define UVC_15FPS_LEB0	0x2B		// 15 fps, little endian byte 0 (lowest order byte)
#define UVC_15FPS_LEB1	0x2C		// 15 fps, little endian byte 1
#define UVC_15FPS_LEB2	0x0A		// 15 fps, little endian byte 2
#define UVC_15FPS_LEB3	0x00		// 15 fps, little endian byte 3 (highest order byte)

#define UVC_20FPS_LEB0	0x20		// 15 fps, little endian byte 0 (lowest order byte)
#define UVC_20FPS_LEB1	0xA1		// 15 fps, little endian byte 1
#define UVC_20FPS_LEB2	0x07		// 15 fps, little endian byte 2
#define UVC_20FPS_LEB3	0x00		// 15 fps, little endian byte 3 (highest order byte)

#define UVC_30FPS_LEB0	0x15		// 30 fps, little endian byte 0 (lowest order byte)
#define UVC_30FPS_LEB1	0x16		// 30 fps, little endian byte 1
#define UVC_30FPS_LEB2	0x05		// 30 fps, little endian byte 2
#define UVC_30FPS_LEB3	0x00		// 30 fps, little endian byte 3 (highest order byte)

#define AUDIO_PKT_SIZE  64


//USB_CSR0
#define EP0_TXPKTRDY 			(1<<0) 
#define EP0_RXPKTRDY 			(1<<1) 
#define EP0_SEND_STALL_FLAG 	(1<<2) 
#define EP0_DATA_END 			(1<<3) 
#define EP0_SETUP_END 			(1<<4) 
#define EP0_SEND_STALL 			(1<<5) 
#define EP0_SERVICED_RXPKTRDY 	(1<<6) 
#define EP0_SERVICED_SETUP_END 	(1<<7)



#define EP1_BUF_SIZE		512


// Startup Command Request Packet
typedef struct
{
    u8 bmRequestType;
    u8 bRequest;
    u16 wValue;
    u16 wIndex;
    u16 wLength;
}USB_DEV_REQ;


// USB Variable
typedef struct
{
	//u32 ep0_buf[EP0_BUF_SIZE];	// to be modified by john
	u8 *pDesc_Data;
	u8 *pEP2_Data;
	u16 yEp0_Desc_Len;
	u8 bSetAddress;
	u8 y8Ep0_State;

    //u32  ep2_buf[EP2_BUF_SIZE];// to be modified by john
	u8 *ep2_Data;
    u32 yEp2_Desc_Len;

    u8* ep0_buf;   // EP0 buffer

	u8* ep1_bufIN_A;    // EP1 IN buffer 0
	u8* ep1_bufIN_B;    // EP1 IN buffer 1
	u8* ep1_bufOUT_A;   // EP1 OUT buffer 0
	u8* ep1_bufOUT_B;   // EP1 OUT buffer 1

    u8* ep2_buf_A;   // EP2 ping-pong 1
	u8* ep2_buf_B;     // EP2 ping-pong 2
	u8* ep3_buf_A;     // EP3 ping-pong 1
	u8* ep3_buf_B;     // EP3 ping-pong 2
}USB_VAR_t;



USB_DEV_REQ	usb_dev_req;
USB_VAR_t 	usb_varm;
extern u8 ep0_current_state;



void usb_device_init(void);
void usb_device_reset_int(void);
void usb_epx_tx_dat(u8 epx,u8 *wbuf,u16 len);

#endif /* USB_DEVICE_ENUM_H_ */
