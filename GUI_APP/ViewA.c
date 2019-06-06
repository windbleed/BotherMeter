/************************************************************************
* 				Single Data UI class										*
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
*   Method: CreateViewA(int loc_x, int loc_y)						*
*			ViewA_Show();											*
*			ViewA_Hide();											*
*			ViewA_CallBack();										*
*                            -------------------by Softwind 2019/5/6	*
*************************************************************************/
#include "ViewA.h"
#include "MainMenu.h"
#include "DataViewPainter.h"
#include "App_start.h"
#include "DataResolver.h"


#define ID_Text_DeepData		(GUI_ID_USER +  101)
#define ID_Text_Unit			(GUI_ID_USER +  102)
#define ID_Text_SensorFreq		(GUI_ID_USER +  103)
#define ID_Text_SensorLoc		(GUI_ID_USER +  104)


#define ViewA_XYData_Max_Num            200






static int  ViewA_ChannelMode=1;  //1: A channel   2:B channel    3:A&B channel





static char  	ViewA_DeepDataStr[]		=		"88.8";

static char 	ViewA_Unit_Str[]		=		"m";

static char 	ViewA_Sensor_Freq_Str[]	= 		"200kHz";


static char 	ViewA_Sensor_Loc_Str[]	=		"C-A";



static TEXT_Handle ViewA_DeepData_Handler;
static TEXT_Handle ViewA_Unit_Handler;
static TEXT_Handle ViewA_SensorFreq_Handler;
static TEXT_Handle ViewA_SensorLoc_Handler;

static WM_HWIN  Next_Win_Handler=NULL;









static WM_HWIN 				ViewA_FrameWin_Handler=NULL;






static void ViewA_FrameWin_Create(void)
{
	ViewA_FrameWin_Handler= FRAMEWIN_CreateEx(ViewA_Location_X, ViewA_Location_Y,ViewA_FrameWin_Width,ViewA_FrameWin_Heigth, WM_HBKWIN, WM_CF_SHOW, 0, 0, "",ViewA_Frame_CallBack);
 
	FRAMEWIN_SetTitleVis(ViewA_FrameWin_Handler,0);
	FRAMEWIN_SetClientColor(ViewA_FrameWin_Handler,GUI_BLUE);
	WM_SetCallback(ViewA_FrameWin_Handler,ViewA_Frame_CallBack);
	WM_SetCallback(WM_GetClientWindow(ViewA_FrameWin_Handler),ViewA_CallBack);


}







static void ViewA_Create_DeepData_Str(void)
{
	
	ViewA_DeepData_Handler=TEXT_CreateEx(ViewA_DeepStr_Location_X -40,ViewA_DeepStr_Location_Y,
		ViewA_DeepStr_Width+10,ViewA_DeepStr_Heigth,ViewA_FrameWin_Handler,
		WM_CF_SHOW,TEXT_CF_RIGHT,ID_Text_DeepData,ViewA_DeepDataStr);
		
	TEXT_SetFont(ViewA_DeepData_Handler,ViewA_Data_Font	);
	TEXT_SetTextColor(ViewA_DeepData_Handler,GUI_WHITE);
}




static void ViewA_Create_Unit_Str(void)
{
	ViewA_Unit_Handler=TEXT_CreateEx(ViewA_UnitStr_Location_X ,ViewA_UnitStr_Location_Y,
		ViewA_Comment_Width	,ViewA_Comment_Heigth,ViewA_FrameWin_Handler,
		WM_CF_SHOW,TEXT_CF_LEFT,ID_Text_Unit,ViewA_Unit_Str);
		
	TEXT_SetFont(ViewA_Unit_Handler,ViewA_Comment_Font	);
	TEXT_SetTextColor(ViewA_Unit_Handler,GUI_WHITE);
	
}


void ViewA_Set_Unit_Str(char * str)
{
	
}

static void ViewA_Create_SensorFreq_Str(void)
{
	ViewA_SensorFreq_Handler=TEXT_CreateEx(ViewA_SensorStr_Location_X ,ViewA_SensorStr_Location_Y,
		ViewA_Comment_Width	,ViewA_Comment_Heigth,ViewA_FrameWin_Handler,
		WM_CF_SHOW,TEXT_CF_LEFT,ID_Text_SensorFreq,ViewA_Sensor_Freq_Str);
		
	TEXT_SetFont(ViewA_SensorFreq_Handler,ViewA_Comment_Font	);
	TEXT_SetTextColor(ViewA_SensorFreq_Handler,GUI_WHITE);
	
}


void ViewA_Set_SensorFreq_Str(char * str)
{
	
}

static void ViewA_Create_SensorLoc_Str(void)
{
	ViewA_SensorLoc_Handler=TEXT_CreateEx(ViewA_SensorLoc_Location_X ,ViewA_SensorLoc_Location_Y,
		ViewA_Comment_Width	,ViewA_Comment_Heigth,ViewA_FrameWin_Handler,
		WM_CF_SHOW,TEXT_CF_LEFT,ID_Text_SensorLoc,ViewA_Sensor_Loc_Str);
		
	TEXT_SetFont(ViewA_SensorLoc_Handler,ViewA_Comment_Font	);
	TEXT_SetTextColor(ViewA_SensorLoc_Handler,GUI_WHITE);
	
}


void ViewA_Set_SensorLoc_Str(char * str)
{
	
}


static void ViewA_Init(void)
{
	

	
	ViewA_Create_DeepData_Str();
	ViewA_Create_Unit_Str();
	ViewA_Create_SensorFreq_Str();
	ViewA_Create_SensorLoc_Str();
	
	
		
	
	
}




WM_HWIN ViewA_Create(void)
{
	ViewA_FrameWin_Create();
	
	
	
	if ((ViewA_FrameWin_Handler!=NULL))
	{
		ViewA_Init();
		
		return ViewA_FrameWin_Handler;
	}
	
	else
		return NULL;
	
		
	
}


static void ViewA_Frame_CallBack(WM_MESSAGE * pMsg)
{
	WM_HWIN hItem;


	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
		
			
		
		break;
		
		
		
		
		case MSG_Set_Channel_A:
		{
			
			
			switch(ViewA_ChannelMode)    
			{
				case 1:
				
					
					
				break;
				
				case 2:
					
					
					
					ViewA_Show(NULL);
					
				break;
				
				case 3:
					
					WM_ResizeWindow(ViewA_FrameWin_Handler,400,0);
				
				
					
				
				break;
				
				
				
			}
			
			
			ViewA_ChannelMode=1;
			
			
		}
		break;
		
		
		case MSG_Set_Channel_B:
		{
			
			switch(ViewA_ChannelMode)    
			{
				case 1:
				
					ViewA_Hide();
					
				break;
				
				case 2:
					
					
					
					
					
				break;
				
				case 3:
					
					WM_ResizeWindow(ViewA_FrameWin_Handler,400,0);
					
					ViewA_Hide();
				
				
					
				
				break;
				
				
				
			}
			
			
			ViewA_ChannelMode=2;
			
			
		}
		break;
		
		
		case MSG_Set_Channel_Dual:
		{
			
			
			
			switch(ViewA_ChannelMode)    
			{
				case 1:
				
					WM_ResizeWindow(ViewA_FrameWin_Handler,-400,0);
					
				break;
				
				case 2:
					
					
					WM_ResizeWindow(ViewA_FrameWin_Handler,-400,0);
					ViewA_Show(NULL);
					
					
				break;
				
				case 3:
					
					
				
				
					
				
				break;
				
				
				
			}
						
			ViewA_ChannelMode=3;
			
			
		}
		break;
		
		
		case WM_PAINT:
		
					
			DataViewPainter_Draw_Frame(ViewA_FrameWin_Handler,&DeepDataBuffer_Frame,ViewA_ChannelMode);
			
			
			DataViewPainter_Draw_Scale(ViewA_FrameWin_Handler,ViewA_ChannelMode);
			
			DataViewPainter_Set_DeepData_Str(ViewA_DeepData_Handler,DataResolver_Get_DeepData());
					
			
			DataViewPainter_Draw_ColorBar();
			
			
			
		
			
					
			
    
		break;
		case WM_KEY:

			switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key)

			{
				case	GUI_KEY_UP:
						
						MainMenu_Show(ViewA_FrameWin_Handler);
					
						
					
				break;
		
			}
		break;



		default:
			WM_DefaultProc(pMsg);
			
		break;
	}
}

static void ViewA_CallBack(WM_MESSAGE * pMsg)
{
	WM_HWIN hItem;


	switch (pMsg->MsgId) 
	{
		case WM_INIT_DIALOG:
		
			
		
		break;
		
		
		case MSG_Set_Channel_A:
		{
			
			
			switch(ViewA_ChannelMode)    
			{
				case 1:
				
					
					
				break;
				
				case 2:
					
					
					
					ViewA_Show(NULL);
					
				break;
				
				case 3:
					
					WM_ResizeWindow(ViewA_FrameWin_Handler,400,0);
				
				
					
				
				break;
				
				
				
			}
			
			
			ViewA_ChannelMode=1;
			
			
		}
		break;
		
		
		case MSG_Set_Channel_B:
		{
			
			switch(ViewA_ChannelMode)    
			{
				case 1:
				
					ViewA_Hide();
					
				break;
				
				case 2:
					
					
					
					
					
				break;
				
				case 3:
					
					WM_ResizeWindow(ViewA_FrameWin_Handler,400,0);
					
					ViewA_Hide();
				
				
					
				
				break;
				
				
				
			}
			
			
			ViewA_ChannelMode=2;
			
			
		}
		break;
		
		
		case MSG_Set_Channel_Dual:
		{
			
			
			
			switch(ViewA_ChannelMode)    
			{
				case 1:
				
					WM_ResizeWindow(ViewA_FrameWin_Handler,-400,0);
					
				break;
				
				case 2:
					
					
					WM_ResizeWindow(ViewA_FrameWin_Handler,-400,0);
					ViewA_Show(NULL);
					
					
				break;
				
				case 3:
					
					
				
				
					
				
				break;
				
				
				
			}
						
			ViewA_ChannelMode=3;
			
			
		}
		break;
		
		
		 
		case WM_PAINT:
		
					
			
    
		break;

		case WM_KEY:

			switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key)

			{
				case	GUI_KEY_UP:
						
						MainMenu_Show(ViewA_FrameWin_Handler);
					
						
					
				break;
		
			}
		break;


		default:
			WM_DefaultProc(pMsg);
			
		break;
	}
}

WM_HWIN ViewA_Show(WM_HWIN	NextHWin)
{
	
	
	WM_SetDesktopColor(GUI_BLACK);
	
	if (ViewA_FrameWin_Handler==NULL)
			ViewA_Create();
	
	
	else
	{
		WM_ShowWindow(ViewA_FrameWin_Handler);
		
	}
	if (NextHWin!=NULL)
		Next_Win_Handler=NextHWin;
	
	WM_SetFocus(ViewA_FrameWin_Handler);
	
	return ViewA_FrameWin_Handler;
}





void ViewA_Hide()
{
	if (ViewA_FrameWin_Handler==NULL)
		ViewA_Create();
	else
		WM_HideWindow(ViewA_FrameWin_Handler);
	
	if (Next_Win_Handler!=NULL)
	{
		WM_BringToTop(Next_Win_Handler);
		WM_SetFocus(Next_Win_Handler);
	}
	
	
}




WM_HWIN ViewA_Get_Handler(void)
{
	
	return ViewA_FrameWin_Handler;
}

