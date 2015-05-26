/******************** (C) COPYRIGHT 2013 BUILDWIN ************************
* File Name          : config.h
* Author             : dingping_chen
* Version            : V0225a
* Date               : 10/22/2014	;mm/dd/yyyy
* Description        : include file
***************************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/*****************************************************************************
 * Module    : IC package
 *****************************************************************************/
#define HUNTER_64PIN    1		//IC package is 64  PIN
#define HUNTER_128PIN	2		//IC package is 128 PIN

/*****************************************************************************
 * Module    : 用户选择
 *****************************************************************************/
#define CONFIG_AX3251_K6000		1		//AX3251行车记录仪方案
#define CONFIG_AX3250_K6000		2		//AX3250行车记录仪方案
#define CONFIG_AX3251_AIRBORNE	3		//AX3251航拍方案

//#define USER_CONFIG		CONFIG_AX3251_K6000
#define USER_CONFIG		CONFIG_AX3251_AIRBORNE

#if		(USER_CONFIG==CONFIG_AX3251_K6000)
	#include "config_ax3251_K6000.h"
#elif	(USER_CONFIG==CONFIG_AX3250_K6000)
	#include "config_ax3250_K6000.h"
#elif	(USER_CONFIG==CONFIG_AX3251_AIRBORNE)
	#include "config_ax3251_airborne.h"
#else
	.......
#endif


#endif
