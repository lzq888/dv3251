
#ifndef USB_DEVICE_VIDEO_H_
#define USB_DEVICE_VIDEO_H_


#define UVC_VS_CONTROL_UNDEFINED 				0x00
#define UVC_VS_PROBE_CONTROL 					0x01
#define UVC_VS_COMMIT_CONTROL 					0x02
#define UVC_VS_STILL_PROBE_CONTROL 				0x03
#define UVC_VS_STILL_COMMIT_CONTROL 			0x04
#define UVC_VS_STILL_IMAGE_TRIGGER_CONTROL 		0x05
#define UVC_VS_STREAM_ERROR_CODE_CONTROL 		0x06
#define UVC_VS_GENERATE_KEY_FRAME_CONTROL 		0x07
#define UVC_VS_UPDATE_FRAME_SEGMENT_CONTROL 	0x08
#define UVC_VS_SYNCH_DELAY_CONTROL 				0x09

#define PU_CONTROL_UNDEFINED					0x00
#define PU_BACKLIGHT_COMPENSATION_CONTROL		0x01
#define PU_BRIGHTNESS_CONTROL					0x02
#define PU_CONTRAST_CONTROL						0x03
#define PU_GAIN_CONTROL							0x04
#define PU_POWER_LINE_FREQUENCY_CONTROL			0x05
#define PU_HUE_CONTROL							0x06
#define PU_SATURATION_CONTROL					0x07
#define PU_SHARPNESS_CONTROL					0x08
#define PU_GAMMA_CONTROL						0x09
#define PU_WHITE_BALANCE_TEMPERATURE_CONTROL	0x0A
#define PU_WHITE_BALANCE_TEMPERATURE_AUTO_CONTROL 0x0B

#define PROCESSING_UINT_CONTROL					1
#define PROCESSING_UINT_ID						0x02	//if configuration desperator change processing id ,this should change
#define VEDIO_CONTROL_INTERFACE_ID				0x00


#define UVC_VIDEO_PROBE_COMMIT_FRAME_INDEX_OFFSET		3
#define UVC_VIDEO_PROBE_COMMIT_FRAME_INTERVAL_OFFSET	4


#define UVC_SET_REQ				0x21
#define UVC_GET_REQ				0xA1
#define UVC_SET_CUR				0x01
#define UVC_GET_CUR				0x81
#define UVC_GET_MIN				0x82
#define UVC_GET_MAX				0x83
#define UVC_GET_RES				0x84
#define UVC_GET_LEN				0x85
#define UVC_GET_INFO			0x86
#define UVC_GET_DEF				0x87



//#define EP2_BUF_SIZE		(3072-20)        // occupies 3072 bytes (HS only)
#define EP2_BUF_SIZE		(2988)        // occupies 3072 bytes (HS only)


#define MAX_FRAME_INDEX				5
#define UVC_PAYLOAD_HEADER_SIZE		12


typedef unsigned char (*SET_REQ_CALLBACK_TYPE)(unsigned char);
SET_REQ_CALLBACK_TYPE pSetReqCallback;
volatile bool EP0WaitForSetReqData;

u8 uvc_video_probe_control(u8 request,u8 len);
void uvc_video_commit_control(u8 request,u8 len);
void uvc_still_probe_control(u8 request,u8 len);
void uvc_still_commit_control(u8 request,u8 len);

#if (PROCESSING_UINT_CONTROL == 1)
void uvc_pu_power_line_frequency_control(u8 request,u8 len);
void uvc_pu_backlight_compensation_control(u8 request,u8 len);
void uvc_pu_contrast_control(u8 request,u8 len);
void uvc_pu_saturation_control(u8 request,u8 len);
void uvc_pu_sharpness_control(u8 request,u8 len);
void uvc_pu_gamma_control(u8 request,u8 len);
void uvc_pu_brightness_control(u8 request,u8 len);
void uvc_pu_hue_control(u8 request,u8 len);
#endif


void uvc_var_init();
u8 uvc_still_trigger_control(unsigned char request, unsigned char len);
void CsiHandleLastPacket(void);
void CsiBuffer0FullIntrHandler(void);
void CsiBuffer1FullIntrHandler(void);
void CsiEndOfFrameIntrHandler(void);

#endif
