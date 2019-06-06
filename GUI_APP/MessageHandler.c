#include "MessageHandler.h"


xQueueHandle App_Message_Queue;

xQueueHandle GUI_Message_Queue;



void MessageHandler_Init(void)
{

	App_Message_Queue = xQueueCreate( 10, sizeof( unsigned long ) );
	GUI_Message_Queue = xQueueCreate( 10, sizeof( unsigned long ) );

}


void MessageHandler_Send_APP_Message(unsigned long pxMessage)
{
	if( App_Message_Queue != 0 ) 
	{
       
		xQueueSend( App_Message_Queue, ( void * ) &pxMessage,  0 );
												
	}
}


void MessageHandler_Send_GUI_Message(unsigned long pxMessage)
{
	if( App_Message_Queue != 0 ) 
	{
       
		xQueueSend( GUI_Message_Queue, ( void * ) &pxMessage,  0 );
												
	}
}
				
 void MessageHandler_Handle_Message(unsigned long pxMessage)
{
	unsigned short 	Msg_Event=(pxMessage&Msg_Event_Mask)>>24;
	
	unsigned short  Msg_Info=(pxMessage&MSG_Info_Mask);
	
	
	switch(Msg_Event)
	{
		case MSG_Deep_Warn:
		{
			MessageHandler_Handle_Deep_Warn(Msg_Info);
			break;
		}
		case MSG_ADC_Update:
		{
			MessageHandler_Handle_ADC_Update(Msg_Info);
			break;
		}
		case MSG_Time_Update:
		{
			MessageHandler_Handle_Time_Update(Msg_Info);
			break;
		}
		case MSG_Channel_Switch:
		{
			MessageHandler_Handle_Channel_Switch(pxMessage);
			break;
		}
		case MSG_SysCFG_Update:
		{
			MessageHandler_Handle_SysCFG_Update(Msg_Info);
			break;
		}
		case MSG_EBCFG_Update:
		{
			MessageHandler_Handle_EBCFG_Update(Msg_Info);
			break;
		}
		case MSG_History_Review:
		{
			MessageHandler_Handle_History_Review(Msg_Info);
			break;
		}
		case MSG_FRate_Switch:
		{
			MessageHandler_Handle_FRate_Switch(Msg_Info);
			break;
		}
		case MSG_Record_Space_Set:
		{
			MessageHandler_Handle_Record_Space_Set(Msg_Info);
			break;
		}
		
	}
	
}


static void MessageHandler_Handle_Deep_Warn(unsigned long pxMessage)
{

}

static void MessageHandler_Handle_ADC_Update(unsigned long pxMessage)
{
	
}

static void MessageHandler_Handle_Time_Update(unsigned long pxMessage)
{
	
}

static void MessageHandler_Handle_Channel_Switch(unsigned long pxMessage)
{
	MessageHandler_Send_GUI_Message(pxMessage);
}

static void MessageHandler_Handle_SysCFG_Update(unsigned long pxMessage)
{
	
}

static void MessageHandler_Handle_EBCFG_Update(unsigned long pxMessage)
{
	
}

static void MessageHandler_Handle_History_Review(unsigned long pxMessage)
{
	
}

static void MessageHandler_Handle_FRate_Switch(unsigned long pxMessage)
{
	
}

static void MessageHandler_Handle_Record_Space_Set(unsigned long pxMessage)
{
	
}
