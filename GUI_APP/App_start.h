#ifndef GUIAPP_Unit
#define GUIAPP_Unit




#include "FreeRTOS.h"     
#include "task.h"
#include "semphr.h"

#include "MessageHandler.h"

#define MSG_Change_ViewA_Size 	(WM_USER + 0)

#define MSG_Change_ViewB_Size 	(WM_USER+1)

#define MSG_Set_Channel_A		(WM_USER+2)
#define MSG_Set_Channel_B		(WM_USER+3)
#define MSG_Set_Channel_Dual	(WM_USER+4)

extern SemaphoreHandle_t SingleUI_Update_View_Sem;

extern void GUIAPP_Task(void);
static void GUIAPP_Handle_Message(unsigned long pxMessage);
static void GUIAPP_Handle_Channel_Switch(unsigned long pxMessage);

#endif
