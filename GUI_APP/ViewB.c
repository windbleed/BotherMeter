/************************************************************************
* 				ViewB Data UI class										*
*																		*
*	Field: 	int SDataUI location x & y									*
*           int SDataUI SizeX&Y											*
*		   	COLOR SDataUI_BackgroundColor(selected and enabled)			*
*		   	COLOR SDataUI_Color											*
*			COLOR SDataUI_SUB_COLOR_DISABLED								*
*			COLOR SDataUI_SUB_COLOR_ENABLED								*
*			Handler SDataUI_Handler;										*
*			Handler SDataUI_FrameWin_Handler								*
*																		*
*   Method: CreateViewB(int loc_x, int loc_y)						*
*			ViewB_Show();											*
*			ViewB_Hide();											*
*			ViewB_CallBack();										*
*                            -------------------by Softwind 2019/5/6	*
*************************************************************************/
#include "ViewB.h"
#include "MainMenu.h"
#include "DataViewPainter.h"
#include "App_start.h"
#include "DataResolver.h"


#define ID_Text_DeepData		(GUI_ID_USER +  151)
#define ID_Text_Unit			(GUI_ID_USER +  152)
#define ID_Text_SensorFreq		(GUI_ID_USER +  153)
#define ID_Text_SensorLoc		(GUI_ID_USER +  154)


#define ViewB_XYData_Max_Num            200






static int  ViewB_ChannelMode=1;  //1: A channel   2:B channel    3:A&B channel



static char  	ViewB_DeepDataStr[]		=		"88.8";

static char 	ViewB_Unit_Str[]		=		"m";

static char 	ViewB_Sensor_Freq_Str[]	= 		"200kHz";


static char 	ViewB_Sensor_Loc_Str[]	=		"C-B";



static TEXT_Handle ViewB_DeepData_Handler;
static TEXT_Handle ViewB_Unit_Handler;
static TEXT_Handle ViewB_SensorFreq_Handler;
static TEXT_Handle ViewB_SensorLoc_Handler;

static WM_HWIN  Next_Win_Handler=NULL;




static WM_HWIN 				ViewB_FrameWin_Handler=NULL;




static void ViewB_FrameWin_Create(void)
{
	ViewB_FrameWin_Handler= FRAMEWIN_CreateEx(ViewB_Location_X, ViewB_Location_Y,ViewB_FrameWin_Width,ViewB_FrameWin_Heigth, WM_HBKWIN, WM_CF_SHOW, 0, 0, "",ViewB_Frame_CallBack);
 
	FRAMEWIN_SetTitleVis(ViewB_FrameWin_Handler,0);
	FRAMEWIN_SetClientColor(ViewB_FrameWin_Handler,GUI_BLUE);

	WM_SetCallback(ViewB_FrameWin_Handler,ViewB_Frame_CallBack);
	WM_SetCallback(WM_GetClientWindow(ViewB_FrameWin_Handler),ViewB_CallBack);

	
}







static void ViewB_Create_DeepData_Str(void)
{
	
	ViewB_DeepData_Handler=TEXT_CreateEx(ViewB_DeepStr_Location_X -40,ViewB_DeepStr_Location_Y,
		ViewB_DeepStr_Width+10,ViewB_DeepStr_Heigth,ViewB_FrameWin_Handler,
		WM_CF_SHOW,TEXT_CF_RIGHT,ID_Text_DeepData,ViewB_DeepDataStr);
		
	TEXT_SetFont(ViewB_DeepData_Handler,ViewB_Data_Font	);
	TEXT_SetTextColor(ViewB_DeepData_Handler,GUI_WHITE);
}





static void ViewB_Create_Unit_Str(void)
{
	ViewB_Unit_Handler=TEXT_CreateEx(ViewB_UnitStr_Location_X ,ViewB_UnitStr_Location_Y,
		ViewB_Comment_Width	,ViewB_Comment_Heigth,ViewB_FrameWin_Handler,
		WM_CF_SHOW,TEXT_CF_LEFT,ID_Text_Unit,ViewB_Unit_Str);
		
	TEXT_SetFont(ViewB_Unit_Handler,ViewB_Comment_Font	);
	TEXT_SetTextColor(ViewB_Unit_Handler,GUI_WHITE);
	
}


void ViewB_Set_Unit_Str(char * str)
{
	
}

static void ViewB_Create_SensorFreq_Str(void)
{
	ViewB_SensorFreq_Handler=TEXT_CreateEx(ViewB_SensorStr_Location_X ,ViewB_SensorStr_Location_Y,
		ViewB_Comment_Width	,ViewB_Comment_Heigth,ViewB_FrameWin_Handler,
		WM_CF_SHOW,TEXT_CF_LEFT,ID_Text_SensorFreq,ViewB_Sensor_Freq_Str);
		
	TEXT_SetFont(ViewB_SensorFreq_Handler,ViewB_Comment_Font	);
	TEXT_SetTextColor(ViewB_SensorFreq_Handler,GUI_WHITE);
	
}


void ViewB_Set_SensorFreq_Str(char * str)
{
	
}

static void ViewB_Create_SensorLoc_Str(void)
{
	ViewB_SensorLoc_Handler=TEXT_CreateEx(ViewB_SensorLoc_Location_X ,ViewB_SensorLoc_Location_Y,
		ViewB_Comment_Width	,ViewB_Comment_Heigth,ViewB_FrameWin_Handler,
		WM_CF_SHOW,TEXT_CF_LEFT,ID_Text_SensorLoc,ViewB_Sensor_Loc_Str);
		
	TEXT_SetFont(ViewB_SensorLoc_Handler,ViewB_Comment_Font	);
	TEXT_SetTextColor(ViewB_SensorLoc_Handler,GUI_WHITE);
	
}


void ViewB_Set_SensorLoc_Str(char * str)
{
	
}


static void ViewB_Init(void)
{
	

	
	ViewB_Create_DeepData_Str();
	ViewB_Create_Unit_Str();
	ViewB_Create_SensorFreq_Str();
	ViewB_Create_SensorLoc_Str();
	

	
	

	
	
	
	
}










WM_HWIN ViewB_Create(void)
{
	ViewB_FrameWin_Create();
	
	
	
	if ((ViewB_FrameWin_Handler!=NULL))
	{
		ViewB_Init();
		
		return ViewB_FrameWin_Handler;
	}
	
	else
		return NULL;
	
		
	
}




static void ViewB_Frame_CallBack(WM_MESSAGE * pMsg)
{
	WM_HWIN hItem;


	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
		
			
		
		break;
		
		
		
		
		case MSG_Set_Channel_A:
		{
			
			
			switch(ViewB_ChannelMode)    
			{
				case 1:
					
				break;
				
				case 2:
					
					ViewB_Hide();
					
				break;
				
				case 3:
					
					WM_MoveWindow(ViewB_FrameWin_Handler,-400,0);
					WM_ResizeWindow(ViewB_FrameWin_Handler,400,0);
				
					ViewB_Hide();
				
				break;
				
				
				
			}
			ViewB_ChannelMode=1;
			
		}
		break;
		
		
		case MSG_Set_Channel_B:
		{
			
			switch(ViewB_ChannelMode)    
			{
				case 1:
				
					ViewB_Show(NULL);
					
				break;
				
				case 2:
					
					
					
				break;
				
				case 3:
					
					WM_MoveWindow(ViewB_FrameWin_Handler,-400,0);
					WM_ResizeWindow(ViewB_FrameWin_Handler,400,0);
				
					ViewB_Show(NULL);
				
				break;
				
				
				
			}
			
			
			ViewB_ChannelMode=2;
			
		}
		break;
		
		
		case MSG_Set_Channel_Dual:
		{
			
			
			switch(ViewB_ChannelMode)    
			{
				case 1:
				
					WM_ResizeWindow(ViewB_FrameWin_Handler,-400,0);
					WM_MoveWindow(ViewB_FrameWin_Handler,400,0);

					ViewB_Show(NULL);
					
				break;
				
				case 2:
					
					WM_ResizeWindow(ViewB_FrameWin_Handler,-400,0);
					WM_MoveWindow(ViewB_FrameWin_Handler,400,0);
					
				break;
				
				case 3:
					
					
				
				break;
				
				
				
			}
			
						
			ViewB_ChannelMode=3;
			
			
		}
		break;
		
		
		 
		case WM_PAINT:
		
		
			
			
			
			DataViewPainter_Draw_Frame(ViewB_FrameWin_Handler,&DeepDataBuffer_Frame,ViewB_ChannelMode);
		
			
			DataViewPainter_Draw_Scale(ViewB_FrameWin_Handler,ViewB_ChannelMode);
			
			
			DataViewPainter_Set_DeepData_Str(ViewB_DeepData_Handler,DataResolver_Get_DeepData());
			
			if(ViewB_ChannelMode==2)
				DataViewPainter_Draw_ColorBar();
			
			
			 
			
			
			
    
		break;

		case WM_KEY:

			switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key)

			{
				case	GUI_KEY_UP:
						
						MainMenu_Show(ViewB_FrameWin_Handler);
					
						
					
				break;
		
			}
		break;



		default:
			WM_DefaultProc(pMsg);
			
		break;
	}
}
static void ViewB_CallBack(WM_MESSAGE * pMsg)
{
	WM_HWIN hItem;


	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
		
			
		
		break;
		
		
		case MSG_Set_Channel_A:
		{
			
			
			switch(ViewB_ChannelMode)    
			{
				case 1:
					
				break;
				
				case 2:
					
					ViewB_Hide();
					
				break;
				
				case 3:
					
					WM_MoveWindow(ViewB_FrameWin_Handler,-400,0);
					WM_ResizeWindow(ViewB_FrameWin_Handler,400,0);
				
					ViewB_Hide();
				
				break;
				
				
				
			}
			ViewB_ChannelMode=1;
			
		}
		break;
		
		
		case MSG_Set_Channel_B:
		{
			
			switch(ViewB_ChannelMode)    
			{
				case 1:
				
					ViewB_Show(NULL);
					
				break;
				
				case 2:
					
					
					
				break;
				
				case 3:
					
					WM_MoveWindow(ViewB_FrameWin_Handler,-400,0);
					WM_ResizeWindow(ViewB_FrameWin_Handler,400,0);
				
					ViewB_Show(NULL);
				
				break;
				
				
				
			}
			
			
			ViewB_ChannelMode=2;
			
		}
		break;
		
		
		case MSG_Set_Channel_Dual:
		{
			
			
			switch(ViewB_ChannelMode)    
			{
				case 1:
				
					WM_ResizeWindow(ViewB_FrameWin_Handler,-400,0);
					WM_MoveWindow(ViewB_FrameWin_Handler,400,0);

					ViewB_Show(NULL);
					
				break;
				
				case 2:
					
					WM_ResizeWindow(ViewB_FrameWin_Handler,-400,0);
					WM_MoveWindow(ViewB_FrameWin_Handler,400,0);
					
				break;
				
				case 3:
					
					
				
				break;
				
				
				
			}
			
						
			ViewB_ChannelMode=3;
			
			
		}
		break;
		
		

		
		
		 
		case WM_PAINT:
		
		
			
			
    
		break;

		case WM_KEY:

			switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key)

			{
				case	GUI_KEY_UP:
						
						MainMenu_Show(ViewB_FrameWin_Handler);
					
						
					
				break;
		
			}
		break;


		default:
			WM_DefaultProc(pMsg);
			
		break;
	}
}

WM_HWIN ViewB_Show(WM_HWIN	NextHWin)
{
	
	
	WM_SetDesktopColor(GUI_BLACK);
	
	if (ViewB_FrameWin_Handler==NULL)
			ViewB_Create();
	
	
	else
	{
		WM_ShowWindow(ViewB_FrameWin_Handler);
		
	}
	if (NextHWin!=NULL)
		Next_Win_Handler=NextHWin;
	
	WM_SetFocus(ViewB_FrameWin_Handler);
	
	return ViewB_FrameWin_Handler;
}


void ViewB_Hide()
{
	if (ViewB_FrameWin_Handler==NULL)
		ViewB_Create();
	else
		WM_HideWindow(ViewB_FrameWin_Handler);
	
	if (Next_Win_Handler!=NULL)
	{
		WM_BringToTop(Next_Win_Handler);
		WM_SetFocus(Next_Win_Handler);
	}
	
	
}






WM_HWIN ViewB_Get_Handler(void)
{
	
	return ViewB_FrameWin_Handler;
}

