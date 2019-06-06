/**********************************************************
*
	This Unit include all app message handler, Message such as 

	Deep warn / ADC update/ time update/ channel switch/
	SysCFG update/EchoBoardCFG update/History Review/
	Frame Rate switch/Set save time space....

	was handled in this unit


										Made by Softwind
										2019/6/1
**************************************************************/

#ifndef MessageHandler_Unit
#define MessageHandler_Unit


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


#define MSG_Deep_Warn         	0x01
#define MSG_ADC_Update			0x02
#define MSG_Time_Update			0x03
#define MSG_Channel_Switch		0x04
#define MSG_SysCFG_Update		0x05
#define MSG_EBCFG_Update		0x06
#define MSG_History_Review		0x07
#define MSG_FRate_Switch		0x08
#define MSG_Record_Space_Set	0x09




#define Msg_Event_Mask       0xff000000
#define MSG_Info_Mask        0x0000ffff



static void MessageHandler_Handle_Deep_Warn(unsigned long pxMessage);
static void MessageHandler_Handle_ADC_Update(unsigned long pxMessage);

static void MessageHandler_Handle_Time_Update(unsigned long pxMessage);
static void MessageHandler_Handle_Channel_Switch(unsigned long pxMessage);

static void MessageHandler_Handle_SysCFG_Update(unsigned long pxMessage);
static void MessageHandler_Handle_EBCFG_Update(unsigned long pxMessage);
static void MessageHandler_Handle_History_Review(unsigned long pxMessage);

static void MessageHandler_Handle_FRate_Switch(unsigned long pxMessage);

static void MessageHandler_Handle_Record_Space_Set(unsigned long pxMessage);


extern xQueueHandle App_Message_Queue;
extern xQueueHandle GUI_Message_Queue;


extern void MessageHandler_Send_APP_Message(unsigned long pxMessage);
extern void MessageHandler_Send_GUI_Message(unsigned long pxMessage);
extern void MessageHandler_Handle_Message(unsigned long pxMessage);

#endif
