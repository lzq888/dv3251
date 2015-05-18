/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : include.h
* Author             : pengtao_zhang
* Version            : V0225a
* Date               : 02/25/2014	;mm/dd/yyyy
* Description        : include file
***************************************************************************/
#ifndef _INCLUDE_H_
#define _INCLUDE_H_

#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include "typedef.h"
#include "system_conf.h"
#include "board.h"
#include "hunter.h"
//#include "bootsect_conf.h"
#include "../startup/ld.h"
#include "../startup/cpu.h"
#include "../sys/sys.h"
#include "../uart/uart.h"
#include "../common/common.h"
#include "../rtc/rtc.h"
#include "../i2c/i2c.h"
#include "../csi/csi.h"
#include "../csi/csi_timeinfo.h"
#include "../int/int.h"
#include "../timer/timer.h"
#include "../sd/sd.h"
#include "../gpdma/gpdma.h"
#include "../tff/diskio.h"
#include "../tff/ff.h"
#include "../format/fat_format.h"
#include "../fat_api/fat_api.h"
#include "../fat_api/fat_fileorder.h"
#include "../jpeg/jpeg_enc.h"
#include "../jpeg/jpeg_dec.h"
#include "../play/avi.h"
#include "../play/play_picture.h"
#include "../play/avi_player.h"
#include "../jpeg/jpeg_linebuffer.h"
#include  "../lcd/osd.h"
#include  "../lcd/lcdc.h"
#include  "../lcd/lcd_interface.h"
#include  "../menu/menu_struct.h"
#include  "../menu/menu_display.h"
#include  "../font/font.h"
#include  "../msg/msg.h"
#include  "../spi/spi.h"
#include  "../tvout/tvout.h"
#include  "../task/task.h"
#include  "../task/task_video.h"
#include  "../task/task_photo.h"
#include  "../task/task_play.h"
#include  "../task/task_holdMode.h"
#include  "../menu/menu_setting.h"
#include  "../audio_adc/audio_adc.h"
#include  "../audio_dac/audio_dac.h"
#include  "../task/task_usb_device.h"
#include  "../usb/usb.h"
#include  "../usb/usb_dev/usb_device_enum.h"
#include  "../usb/usb_dev/usb_device_mass.h"
#include  "../usb/usb_dev/usb_device_video.h"
#include  "../usb/usb_dev/usb_dev_audio.h"
#include  "../usb/usb_host/usb_host.h"
#include  "../usb/usb_host/usb_host_enum.h"
#include  "../usb/usb_host/usb_host_tpbulk.h"
#include  "../led/led.h"
#include  "../config/config.h"
#include  "../sensor/sensor.h"
#include  "../g_sensor/g_sensor.h"
#include  "../lcd/lcd_cfg.h"
#include  "../msg/adkey.h"
#endif
