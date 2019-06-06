/************************************************************************
* 				Main Menu class											*
*																		*
*	Field: 	int Menu location x & y										*
*           int Menu SizeX&Y											*
*		   	COLOR Menu_BackgroundColor(selected and enabled)			*
*		   	COLOR Menu_Color											*
*			COLOR Menu_SUB_COLOR_DISABLED								*
*			COLOR Menu_SUB_COLOR_ENABLED								*
*			Handler hMenu;												*
*																		*
*   Method: CreateMainMenu(int loc_x, int loc_y)						*
*			MenuShow();													*
*			MenuHide();													*
*			MenuCallBack();												*
*                            -------------------by Softwind 2019/5/5	*
*************************************************************************/

#include "MainMenu.h"
#include "GUI.h"
#include "WM.h"
#include "ViewA.h"
#include "App_start.h"
#include "ViewB.h"
#include "MessageHandler.h"
#include "InputDialog.h"
#include "TimeBox.h"
#include "SystemCFG.h"


#define ID_MENU						(GUI_ID_USER +  0)



#define MainMenu_ItemNumber 	11

int MainMenu_Setup_Measure_Range=40;


static WM_HWIN MainMenu_Handler=NULL;
static WM_HWIN MainMenu_FrameWin_Handler=NULL;

static WM_HWIN Next_Win_Handler=NULL;

static MENU_Handle MainMenu_Root;
static MENU_Handle MainMenu_SubItemList[MainMenu_ItemNumber];


static int MainMenu_MenuItem_Value_From_InputBox[9];


void MainMenu_Get_InputBox(int menuItemIndex,int value)
{
	MainMenu_MenuItem_Value_From_InputBox[menuItemIndex]=value;
}


static int MainMenu_SubItem_Index[11]=
{
	GUI_ID_USER +  10,GUI_ID_USER + 20, GUI_ID_USER +  30,GUI_ID_USER +  40,GUI_ID_USER +  50,
	GUI_ID_USER +  60,GUI_ID_USER + 70, GUI_ID_USER +  80,GUI_ID_USER +  90,GUI_ID_USER +  100,
	GUI_ID_USER	+  110
};

static int MainMenu_SubItem_Num[11]=
{
	3,5,8,4,2,0,0,0,0,0,0
};

static char MainMenu_Item[11][15]=
{
	//"Channel Sel",
	"通道选择",
	//"Frame Rate",
	"帧速",
	//"Range Span",
	"量程",
	//"TX Power",
	"发射功率",
	//"Trace Mode",
	"跟踪模式",
	//"Gain A",
	"增益A",
	//"Gain B",
	"增益B",
	//"Alarm Deep ",
	"告警深度",
	//"Time",
	"日期设置",
	"时间设置",

	//"Next Menu"
	"下一页"
	
	
};




static void (* pFun[11])(int index)=
{
	MainMenu_Channel_Sel,
	MainMenu_FrameRate_Set,
	MainMenu_Range_Adj,
	MainMenu_Pwr_Set,
	MainMenu_Mode_Set,
	MainMenu_GainA_Set,
	MainMenu_GainB_Set,
	MainMenu_WarnDeep_Set,
	MainMenu_Date_Set,
	MainMenu_Time_Set,
	MainMenu_NextPage
	
	
	
};




static MENU_MSG_DATA * pData;
static MENU_ITEM_DATA  Data;


static void MainMenu_Channel_Sel(int index)
{
	unsigned short info=0 ;
	unsigned long msg=MSG_Channel_Switch;
	
	
	
	
	
	
	
	switch (index-2058)
	{
		case 0:
			info=1;
			
			break;
			
		case 1:
			info=2;
			
			break;
		case 2:
			info=3 ;
			
			break;
		
		
		
		
	}

	msg<<=24;
	msg|=info;

	MessageHandler_Send_APP_Message(msg);
	
	
		
	
	
	
	
}

static void MainMenu_FrameRate_Set(int index)
{}

static void MainMenu_Range_Adj(int index)
{
	int order=index-MainMenu_SubItem_Index[2];
	
	switch (order)
	{
		case 0:
			MainMenu_Setup_Measure_Range=5;
			break;
		case 1:
			MainMenu_Setup_Measure_Range=10;
			break;
		case 2:
			MainMenu_Setup_Measure_Range=20;
			break;
		case 3:
			MainMenu_Setup_Measure_Range=40;
			break;
		case 4:
			MainMenu_Setup_Measure_Range=100;
			break;
		case 5:
			MainMenu_Setup_Measure_Range=200;
			break;
		case 6:
			MainMenu_Setup_Measure_Range=400;
			break;
		case 7:
			MainMenu_Setup_Measure_Range=800;
			break;
		
		
		
	}
	
	//ViewA_Set_MeasureMax(MainMenu_Setup_Measure_Range);
	
	DataViewPainter_Set_MeasureMax(MainMenu_Setup_Measure_Range);
	
}

static void MainMenu_Pwr_Set(int index)
{}

static void MainMenu_Mode_Set(int index)
{}

static void MainMenu_GainA_Set(int index)
{
	

	InputDialog_Show(MainMenu_Handler,SysCFG_Item_GainA_Index);

	InputDialog_SetStyle(0);

	InputDialog_MoveWindow(5);


}

static void MainMenu_GainB_Set(int index)
{
	InputDialog_Show(MainMenu_Handler,SysCFG_Item_GainB_Index);

	InputDialog_SetStyle(0);

	InputDialog_MoveWindow(6);

}

static void MainMenu_WarnDeep_Set(int index)
{
	InputDialog_Show(MainMenu_Handler,SysCFG_Item_LowWater_Index);

	InputDialog_SetStyle(1);

	InputDialog_MoveWindow(7);
}

static void MainMenu_Date_Set(int index)
{

	TimeBox_Show(MainMenu_Handler,1);
	TimeBox_SetStyle(1);
	TimeBox_MoveWindow(8);

}


static void MainMenu_Time_Set(int index)
{

	TimeBox_Show(MainMenu_Handler,0);

	TimeBox_SetStyle(0);
	TimeBox_MoveWindow(9);

}

static void MainMenu_NextPage(int index)
{
	MainMenu_Hide();
	MainMenu2_Show(NULL);
}


static void MainMenu_MessageBox(const char * pText, const char * pCaption) 
{
  WM_HWIN hBox;

  hBox = MESSAGEBOX_Create(pText, pCaption, GUI_MESSAGEBOX_CF_MODAL | GUI_MESSAGEBOX_CF_MOVEABLE);
  WM_SetStayOnTop(hBox, 1);
  WM_BringToTop(hBox);
  GUI_ExecCreatedDialog(hBox);
  
  WM_SetFocus(MainMenu_Handler);
  MENU_SetSel(MainMenu_Handler, -1);
}



static void MainMenu_FrameWin_Create()
{
	MainMenu_FrameWin_Handler= FRAMEWIN_CreateEx(MainMenu_Location_X, MainMenu_Location_Y,MainMenu_FrameWin_Width,MainMenu_FrameWin_Heigth, WM_HBKWIN, WM_CF_SHOW, 0, 0, "",MainMenu_CallBack);
 
	FRAMEWIN_SetTitleVis(MainMenu_FrameWin_Handler,0);
	
	FRAMEWIN_SetClientColor(MainMenu_FrameWin_Handler,MainMenu_Frame_Color);
	
}

static void MainMenu_AddMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags) 
{
  MENU_ITEM_DATA Item;

  Item.pText    = pText;
  Item.hSubmenu = hSubmenu;
  Item.Flags    = Flags;
  Item.Id       = Id;
  
  MENU_AddItem(hMenu, &Item);
}


static void MainMenu_Init()
{
	int selectIndex=0;

	selectIndex= MainMenu_SubItem_Index[0]+SysCFG_Get_SysCFG(SysCFG_Item_Channel_Index)-1;

	MENU_EnableItem(MainMenu_SubItemList[0], selectIndex);

	(*pFun[0])(selectIndex);


	selectIndex= MainMenu_SubItem_Index[1]+SysCFG_Get_SysCFG(SysCFG_Item_FrameRate_Index)-1;

	MENU_EnableItem(MainMenu_SubItemList[1], selectIndex);

	(*pFun[1])(selectIndex);


	selectIndex= MainMenu_SubItem_Index[2]+SysCFG_Get_SysCFG(SysCFG_Item_MeasureRange_Index)-1;

	MENU_EnableItem(MainMenu_SubItemList[2], selectIndex);

	(*pFun[2])(selectIndex);


	selectIndex= MainMenu_SubItem_Index[3]+SysCFG_Get_SysCFG(SysCFG_Item_TxPwr_Index)-1;

	MENU_EnableItem(MainMenu_SubItemList[3], selectIndex);

	(*pFun[3])(selectIndex);

	selectIndex= MainMenu_SubItem_Index[4]+SysCFG_Get_SysCFG(SysCFG_Item_Mode_Index)-1;

	MENU_EnableItem(MainMenu_SubItemList[4], selectIndex);

	(*pFun[4])(selectIndex);




}

static  WM_HWIN MainMenu_Item_Create()
{
	int i=0;

	MainMenu_Root = MENU_CreateEx(0, 0, MainMenu_Width, MainMenu_Heigth, WM_UNATTACHED, 0, MENU_CF_VERTICAL, ID_MENU);
	
	for( i=0;i<MainMenu_ItemNumber-6;i++)
		MainMenu_SubItemList[i] 	= MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_HORIZONTAL, 0);
	
		
	MainMenu_AddMenuItem(MainMenu_SubItemList[0],   0,     "A",      MainMenu_SubItem_Index[0],     MENU_IF_DISABLED);
    MainMenu_AddMenuItem(MainMenu_SubItemList[0],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[0],   0,     "B",     MainMenu_SubItem_Index[0]+1,    MENU_IF_DISABLED);
    MainMenu_AddMenuItem(MainMenu_SubItemList[0],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[0],   0,     "A+B",    MainMenu_SubItem_Index[0]+2,  MENU_IF_DISABLED);
	
	MainMenu_AddMenuItem(MainMenu_SubItemList[1],   0,     "VH",      MainMenu_SubItem_Index[1],     MENU_IF_DISABLED);
    MainMenu_AddMenuItem(MainMenu_SubItemList[1],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[1],   0,     "High",     MainMenu_SubItem_Index[1]+1,    MENU_IF_DISABLED);
    MainMenu_AddMenuItem(MainMenu_SubItemList[1],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[1],   0,     "Mid",    MainMenu_SubItem_Index[1]+2,  MENU_IF_DISABLED);
	MainMenu_AddMenuItem(MainMenu_SubItemList[1],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[1],   0,     "Low",     MainMenu_SubItem_Index[1]+3,    MENU_IF_DISABLED);
    MainMenu_AddMenuItem(MainMenu_SubItemList[1],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[1],   0,     "VL",    MainMenu_SubItem_Index[1]+4,  MENU_IF_DISABLED);

	MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,     "5",      MainMenu_SubItem_Index[2],     MENU_IF_DISABLED);
	//MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,     "10",     MainMenu_SubItem_Index[2]+1,    MENU_IF_DISABLED);
	//MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,     "20",    MainMenu_SubItem_Index[2]+2,  MENU_IF_DISABLED);
	//MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,     "40",     MainMenu_SubItem_Index[2]+3,    MENU_IF_DISABLED);
	//MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,     "100",    MainMenu_SubItem_Index[2]+4,  MENU_IF_DISABLED);
	//MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,     "200",    MainMenu_SubItem_Index[2]+5,  MENU_IF_DISABLED);
	//MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,     "400",     MainMenu_SubItem_Index[2]+6,    MENU_IF_DISABLED);
	//MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[2],   0,     "800",    MainMenu_SubItem_Index[2]+7,  MENU_IF_DISABLED);
	
	
	MainMenu_AddMenuItem(MainMenu_SubItemList[3],   0,     "High",      MainMenu_SubItem_Index[3],     MENU_IF_DISABLED);
	MainMenu_AddMenuItem(MainMenu_SubItemList[3],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[3],   0,     "Mid",     MainMenu_SubItem_Index[3]+1,    MENU_IF_DISABLED);
	MainMenu_AddMenuItem(MainMenu_SubItemList[3],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[3],   0,     "Low",    MainMenu_SubItem_Index[3]+2,  MENU_IF_DISABLED);
	MainMenu_AddMenuItem(MainMenu_SubItemList[3],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[3],   0,     "Auto",     MainMenu_SubItem_Index[3]+3,    MENU_IF_DISABLED);
	
	MainMenu_AddMenuItem(MainMenu_SubItemList[4],   0,     "Auto-1",      MainMenu_SubItem_Index[4],     MENU_IF_DISABLED);
	MainMenu_AddMenuItem(MainMenu_SubItemList[4],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu_AddMenuItem(MainMenu_SubItemList[4],   0,     "Auto-2",     MainMenu_SubItem_Index[4]+1,    MENU_IF_DISABLED);




	for( i=0;i<MainMenu_ItemNumber;i++)
	{
		if (i<=4)
			MainMenu_AddMenuItem(MainMenu_Root,MainMenu_SubItemList[i], MainMenu_Item[i],   0,  0);
		else
			MainMenu_AddMenuItem(MainMenu_Root,MainMenu_SubItemList[i], MainMenu_Item[i],   MainMenu_SubItem_Index[i],  0);
		if (i!=MainMenu_ItemNumber-1)
			MainMenu_AddMenuItem(MainMenu_Root,   0,      0,          0,                   MENU_IF_SEPARATOR);

		if (i!=MainMenu_Index_SetSmallFont)
			MENU_SetFont(MainMenu_SubItemList[i], MainMenu_Sub_Font);
		else
			MENU_SetFont(MainMenu_SubItemList[i], MainMenu_Sub_Font_Small);
			
		MENU_SetSkinClassic(MainMenu_SubItemList[i]);

		MENU_SetTextColor(MainMenu_SubItemList[i],MENU_CI_ENABLED,MainMenu_Sub_Sel_Color);
		MENU_SetTextColor(MainMenu_SubItemList[i],MENU_CI_DISABLED,MainMenu_Sub_Unsel_Color);
		
		MENU_SetBkColor(MainMenu_SubItemList[i],MENU_CI_DISABLED,MainMenu_Sub_Bk_Unsel_Color);
		MENU_SetBkColor(MainMenu_SubItemList[i],MENU_CI_ENABLED,MainMenu_Sub_Bk_Unsel_Color);

		MENU_SetBkColor(MainMenu_SubItemList[i],MENU_CI_SELECTED,MainMenu_Sub_Bk_Sel_Color);
		MENU_SetBkColor(MainMenu_SubItemList[i],MENU_CI_DISABLED_SEL,MainMenu_Sub_Bk_Sel_Color);

		
		//MENU_SetBkColor(MainMenu_SubItemList[i],MENU_CI_DISABLED,GUI_WHITE);


		MainMenu_Init();
		
	}
	
	
	

	MENU_SetFont(MainMenu_Root, &MainMenu_Font);
	
	MENU_SetSkinClassic(MainMenu_Root);
	
	MENU_SetBkColor(MainMenu_Root,MENU_CI_SELECTED,MainMenu_BK_Color_SEL);
	MENU_SetBkColor(MainMenu_Root,MENU_CI_ENABLED,MainMenu_BK_Color_UnSel);
	
	MENU_Attach(MainMenu_Root,MainMenu_FrameWin_Handler,MainMenu_Border_Size,
	MainMenu_Border_Size,MainMenu_Width,MainMenu_Heigth,1);
	MENU_SetOwner(MainMenu_Root,WM_GetClientWindow(MainMenu_FrameWin_Handler));
	
	
	

	
	return MainMenu_Root;
 
}

static void MainMenu_CallBack(WM_MESSAGE * pMsg)
{
	
	int             xSize;
	int             ySize;

	WM_HWIN         hWin;
	WM_HWIN         hClient;

	char acBuffer[50];
	int Index;
  
 

	hWin = pMsg->hWin;
	hClient = WM_GetClientWindow(hWin);
	xSize = WM_GetWindowSizeX(hClient);
	ySize = WM_GetWindowSizeY(hClient);
	switch (pMsg->MsgId) 
	
	{

		case WM_KEY:

		switch (((WM_KEY_INFO*)(pMsg->Data.p))->Key)

		{
		case	GUI_KEY_INSERT:

			
			MainMenu_Hide();



			break;

		}
		break;

		case WM_PAINT:
    
		break;
		
		case WM_MENU:
			pData = (MENU_MSG_DATA*)pMsg->Data.p;
			switch (pData->MsgType) 
			{
				case MENU_ON_ITEMPRESSED:
      
					MENU_GetItem(pMsg->hWinSrc, pData->ItemId, &Data);
					if (Data.Flags & MENU_IF_DISABLED) 
					{
						Data.Flags=0;
						//Index = pData->ItemId - ID_MENU_Sub_1_1;
						//MENU_EnableItem(MainMenu_Root,pData->ItemId);
						//MENU_DisableItem(MainMenu_Root,pData->ItemId-1);
						MainMenu_Active_Sel_Item(pData->ItemId);
		  
					}
	  
				break;
				
				case MENU_ON_ITEMACTIVATE:
      
					
					
				break;
				
				case MENU_ON_ITEMSELECT:
      
					Index = MainMenu_FindOrder(pData->ItemId) ;
					
					(*pFun[Index])(pData->ItemId);
					
					

					//sprintf(acBuffer, "ID of the selected\nitem is 0x%X",Index);
					//MainMenu_MessageBox(acBuffer, "Message");
	  
				break;
			}
	}
	
	WM_DefaultProc(pMsg);
	
}

static int MainMenu_FindOrder(int index)
{
	int i=0;
	int Order=88;
	
	for(i=0;i<11;i++)
	{
		if ((index-MainMenu_SubItem_Index[i])<10)
		{
			Order=i;
			
			break;
		}
					
	}
	
	return Order;
	
}

static void MainMenu_Active_Sel_Item(int index)
{
	int i;
	int SubMenu_Order=88;
	int Current_Item=0;
	
		
	SubMenu_Order=MainMenu_FindOrder(index);
	
	if (SubMenu_Order!=88)
	{
		for(i=0;i<MainMenu_SubItem_Num[SubMenu_Order];i++)
		{
			Current_Item=MainMenu_SubItem_Index[SubMenu_Order]+i;
			
			if (Current_Item!=index)
				MENU_DisableItem(MainMenu_Root,Current_Item);
			
		}
		
	}
	
	MENU_EnableItem(MainMenu_Root,index);
	
	
	
}



WM_HWIN MainMenu_Create()
{
		MainMenu_FrameWin_Create();
		
		MainMenu_Handler=MainMenu_Item_Create();
		
		WM_SetFocus(MainMenu_Handler);
		
		return MainMenu_FrameWin_Handler;

	
	
}




WM_HWIN MainMenu_Show(WM_HWIN NextWin)
{


	WM_SetDesktopColor(GUI_BLACK);
	
	if (MainMenu_Handler==NULL)
		MainMenu_Create();
	else
		WM_ShowWindow(MainMenu_FrameWin_Handler);


	WM_BringToTop(MainMenu_FrameWin_Handler);
	WM_SetFocus(MainMenu_FrameWin_Handler);
	
	if (NextWin!=NULL)
		Next_Win_Handler=NextWin;

	return MainMenu_FrameWin_Handler;
	
}

void MainMenu_Hide()
{
	if (MainMenu_Handler==NULL)
		MainMenu_Create();
		
	else
		WM_HideWindow(MainMenu_FrameWin_Handler);

	//WM_SetStayOnTop(MainMenu_FrameWin_Handler,1);
	if (Next_Win_Handler!=NULL)
	{
		WM_BringToTop(Next_Win_Handler);
		WM_SetFocus(Next_Win_Handler);
	}
		
	
}


