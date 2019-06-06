/*********************************************************************
*
*       MainTask
*/
#include "MainMenu.h"

#include "DeepDataBuffer.h"
#include "DataViewPainter.h"
#include "OutlineFrame.h"

#include "App_start.h"
#include "DataResolver.h"
#include "ViewA.h"
#include "ViewB.h"
#include "MainMenu.h"



#define RECOMMENDED_MEMORY (1024L * 2200)



SemaphoreHandle_t SingleUI_Update_View_Sem;



static    WM_HWIN GUIAPP_Handler_ViewA;
static    WM_HWIN GUIAPP_Handler_ViewB;
static    WM_HWIN GUIAPP_Handler_Menu;
static    WM_HWIN GUIAPP_Handler_FrameWin;



static void GUIAPP_Init(void)
{

  //WM_MULTIBUF_Enable(1);

  WM_SetCreateFlags(WM_CF_MEMDEV);
  
  GUI_Init();

  DataViewPainter_Create_Memdev();
  
  SingleUI_Update_View_Sem=xSemaphoreCreateBinary();
  
  //DeepDataBuffer_Create_SimData();
  
  
  if (GUI_ALLOC_GetNumFreeBytes() < RECOMMENDED_MEMORY) 
  {
    GUI_ErrorOut("Not enough memory available."); 
    return;
  }
  
  SysCFG_Init();
  
  GUIAPP_Handler_FrameWin=OutlineFrame_CreateFramewin();

  GUIAPP_Handler_Menu=MainMenu_Show(NULL);

  GUIAPP_Handler_ViewB=ViewB_Show(NULL);

   GUIAPP_Handler_ViewA=ViewA_Show(NULL);

  MainMenu_Hide();

  
  ViewB_Hide();


 
  

}



void GUIAPP_Task(void) 
{





  unsigned  long pxMessage;

 
  GUIAPP_Init();


  
  while (1) 
  {


	
		if(SingleUI_Update_View_Sem!=NULL)    //大数据信息无法通过消息info copy，使用信号量机制，先通知再处理
		{	
			if(xSemaphoreTake(SingleUI_Update_View_Sem,10)==pdTRUE)
			{
								
				WM_Invalidate(GUIAPP_Handler_ViewA);
				WM_Invalidate(GUIAPP_Handler_ViewB);
			}
		}
	
  
    if( xQueueReceive( GUI_Message_Queue, &( pxMessage ),  10  ))  //小数据信息直接通过消息透传
    {
            
      GUIAPP_Handle_Message( pxMessage);

    }
    
    
		  
    GUI_Delay(100);
  }
}



static void GUIAPP_Handle_Message(unsigned long pxMessage)
{
  unsigned short  Msg_Event=(pxMessage&Msg_Event_Mask)>>24;
  
  unsigned short  Msg_Info=(pxMessage&MSG_Info_Mask);
  
  
  switch(Msg_Event)
  {
    case MSG_Channel_Switch:
    {
      GUIAPP_Handle_Channel_Switch(Msg_Info);
      break;
    }
   
  }
}



static void GUIAPP_Handle_Channel_Switch(unsigned long pxMessage)
{
  WM_MESSAGE Message;
  

  Message.Data.p = "SetChannel";
  
  switch (pxMessage)
  {
    case 1:
      Message.MsgId = MSG_Set_Channel_A ;
      
      break;
      
    case 2:
      Message.MsgId = MSG_Set_Channel_B ;
      
      break;
    case 3:
      Message.MsgId = MSG_Set_Channel_Dual ;
      
      break;
    
    
    
    
  }
  
  WM_SendMessage(GUIAPP_Handler_ViewA,&Message);
  WM_SendMessage(GUIAPP_Handler_ViewB,&Message);
  
}

