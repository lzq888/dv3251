/******************** (C) COPYRIGHT 2013 BUILDWIN ********************************
* File Name          : msg.c
* Author             :
* Version            :
* Date               : 24/10/2013
* Description        : msg.
**********************************************************************************/
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
volatile struct {
    u8 inptr;
    u8 outptr;
    u8 depth;
    u8 *msg_pool;
} msg_ctrl;

volatile u8 msg_pool[MSG_DEPTH];

/*******************************************************************************
* Function Name  : msg_init
* Description    : message initiate
* Input          : msg_pool : array to store message
                   depth    : the length of message array
* Output         : None
* Return         : None
*******************************************************************************/
void msg_init(u8 *msg_pool, u8 depth)
{
    msg_ctrl.msg_pool = msg_pool;
    msg_ctrl.depth = depth;
    msg_ctrl.inptr = 0;
    msg_ctrl.outptr = 0;
}

/*******************************************************************************
* Function Name  : flush_msg
* Description    : clear the message
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void flush_msg(void)
{
    msg_ctrl.inptr = 0;
    msg_ctrl.outptr = 0;
}

/*******************************************************************************
* Function Name  : put_msg
* Description    : add message
* Input          : msg
* Output         : None
* Return         : None
*******************************************************************************/
void put_msg(u8 msg)
{
    msg_ctrl.msg_pool[msg_ctrl.inptr] = msg;
    msg_ctrl.inptr++;

    if (msg_ctrl.inptr == msg_ctrl.depth) {
        msg_ctrl.inptr = 0;
    }
}

/*******************************************************************************
* Function Name  : get_msg
* Description    : get message
* Input          : None
* Output         : msg
* Return         : None
*******************************************************************************/
u8 get_msg(void)
{
	u8 msg;
    if (msg_ctrl.outptr == msg_ctrl.inptr) {
        return NO_KEY;
    }
    msg = msg_ctrl.msg_pool[msg_ctrl.outptr];
    msg_ctrl.outptr++;
    if (msg_ctrl.outptr == msg_ctrl.depth) {
        msg_ctrl.outptr = 0;
    }
//    if(sys_ctl.beep_status)
//    {
//		if(bRecordVideo_Flag != 1 && task_ctl.on_playing != 1 && msg != SYSTEM_1S && msg != NO_KEY && g_SystemState != SYSTEM_POWER_ON && g_SystemState != SYSTEM_POWER_OFF)
//			key_voice();
//    }

    return msg;
}

/*******************************************************************************
* Function Name  : peek_msg
* Description    : view message
* Input          : None
* Output         : msg
* Return         : None
*******************************************************************************/
u8 peek_msg(void)
{
    u8 msg;
    if (msg_ctrl.outptr == msg_ctrl.inptr) {
        return NO_KEY;
    }
    msg = msg_ctrl.msg_pool[msg_ctrl.outptr];
    return msg;
}



