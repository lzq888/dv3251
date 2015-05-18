
#ifndef __USB_DEV_AUDIO_H
#define __USB_DEV_AUDIO_H

#define EP3TXUNBER 64
#define UAC_FEATURE_UNIT		0x05//0x02 Ray fix

#define UAC_STREAMING_ENDPOINT	0x83

#define UAC_SET_REQ				0x21
#define UAC_SET_ENDPOINT		0x22
#define UAC_GET_REQ				0xA1
#define UAC_GET_ENDPOINT		0xA2

#define UAC_REQUEST_CODE_UNDEFINED 	0x00
#define UAC_SET_CUR  				0x01
#define UAC_GET_CUR  				0x81
#define UAC_SET_MIN  				0x02
#define UAC_GET_MIN  				0x82
#define UAC_SET_MAX  				0x03
#define UAC_GET_MAX  				0x83
#define UAC_SET_RES  				0x04
#define UAC_GET_RES  				0x84
#define UAC_SET_MEM  				0x05
#define UAC_GET_MEM  				0x85
#define UAC_GET_STAT 				0xFF

#define UAC_FU_CONTROL_UNDEFINED 			0x00
#define UAC_FU_MUTE_CONTROL 				0x01
#define UAC_FU_VOLUME_CONTROL 				0x02
#define UAC_FU_BASS_CONTROL 				0x03
#define UAC_FU_MID_CONTROL 					0x04
#define UAC_FU_TREBLE_CONTROL 				0x05
#define UAC_FU_GRAPHIC_EQUALIZER_CONTROL 	0x06
#define UAC_FU_AUTOMATIC_GAIN_CONTROL 		0x07
#define UAC_FU_DELAY_CONTROL 				0x08
#define UAC_FU_BASS_BOOST_CONTROL 			0x09
#define UAC_FU_LOUDNESS_CONTROL 			0x0A

#define UAC_EP_CONTROL_UNDEFINED 		0x00
#define UAC_EP_SAMPLING_FREQ_CONTROL 	0x01
#define UAC_EP_PITCH_CONTROL 			0x02


#define	USB_REQUEST_ERROR		0
#define	USB_DATAIN_STAGE		1
#define	USB_STATUS_STAGE		1
#define	USB_REQUEST_OVER		1

#define UacReqSelector			((unsigned char)(usb_dev_req.wValue >> 8))
#define UacReqInterface			((unsigned char)(usb_dev_req.wIndex))
#define UacReqTermUnitId		((unsigned char)(usb_dev_req.wIndex >> 8))
#define UacReqLen				((unsigned char)(usb_dev_req.wLength))
#define	UacEndPointNumber		((unsigned char)(usb_dev_req.wIndex))

typedef bool TypeUsbStage;

#if 1
typedef unsigned char (*SET_REQ_CALLBACK_TYPE)(unsigned char);

extern u8 const audioSample[64];
extern volatile bool EP0WaitForSetReqData;
extern SET_REQ_CALLBACK_TYPE pSetReqCallback;
#endif

extern void USB_EP3DataIn(u8 *Pbuf,u16 Length);
TypeUsbStage HandleUacFeatUnitReq(unsigned char reqType, unsigned char request, unsigned char reqSelector, unsigned char len);
TypeUsbStage UacHandleRequestToStreamingEndpoint(unsigned char reqType, unsigned char request, unsigned char reqSelector, unsigned char len);
void uac_var_init(void);
void dealforep3isr(void);
#endif /* DAC_H_ */

