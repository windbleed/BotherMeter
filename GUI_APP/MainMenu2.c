#include "MainMenu2.h"

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
*   Method: CreateMainMenu2(int loc_x, int loc_y)						*
*			MenuShow();													*
*			MenuHide();													*
*			MenuCallBack();												*
*                            -------------------by Softwind 2019/5/5	*
*************************************************************************/

#include "MainMenu2.h"
#include "GUI.h"
#include "WM.h"
#include "ViewA.h"
#include "App_start.h"
#include "ViewB.h"
#include "MessageHandler.h"
#include "InputDialog.h"
#include "SystemCFG.h"
#include "SystemMenu.h"


#define ID_MENU_2						(GUI_ID_USER +  420)



#define MainMenu2_ItemNumber 	9

int MainMenu2_Setup_Measure_Range=40;


static WM_HWIN MainMenu2_Handler=NULL;
static WM_HWIN MainMenu2_FrameWin_Handler=NULL;

static WM_HWIN Next_Win_Handler=NULL;

static MENU_Handle MainMenu2_Root;
static MENU_Handle MainMenu2_SubItemList[MainMenu2_ItemNumber];

static int MainMenu2_SubItem_Index[MainMenu2_ItemNumber]=
{
	GUI_ID_USER +  430,GUI_ID_USER + 440, GUI_ID_USER +  450,GUI_ID_USER +  460,GUI_ID_USER +  470,
	GUI_ID_USER +  480,GUI_ID_USER + 490, GUI_ID_USER +  500,GUI_ID_USER +  510
};

static int MainMenu2_SubItem_Num[MainMenu2_ItemNumber]=
{
	3,5,8,4,2,0,0,0,0
};

static char MainMenu2_Item[MainMenu2_ItemNumber][25]=
{
	//"     Pulse Width",
	"脉冲宽度",
	//"    Dynamic Range",

	"动态范围",

	//"      Depth Ref",
	"深度基准",

	//"    Echo Threshold ",
	"回波门限",


	//"       TVGA",
	"时变增益A",
	//"       TVGB",
	"时变增益B",
	//" Trans Below Water",
	"换能器吃水",
	
	
	//"    Keel Heigth",
	"龙骨高度",
	//"    System Menu"
	"系统菜单"
	
	
};




static void (* pFun[MainMenu2_ItemNumber])(int index)=
{
	MainMenu2_PulseWidth_Sel,
	MainMenu2_DynamicRange_Set,
	MainMenu2_DepthRef_Set,
	MainMenu2_EchoThreshold_Set,
	MainMenu2_TVGA_Set,
	MainMenu2_TVGB_Set,
	MainMenu2_TBW_Set,
	MainMenu2_KeelHeight_Set,
	MainMenu2_NextPage
	
	
	
};




static MENU_MSG_DATA * pData;
static MENU_ITEM_DATA  Data;


static void MainMenu2_PulseWidth_Sel(int index)
{
	unsigned short info=0 ;

	
	
	
	
	
	
	
	switch (index-2478)
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


	
	
		
	
	
	
	
}

static void MainMenu2_DynamicRange_Set(int index)
{}

static void MainMenu2_DepthRef_Set(int index)
{
	int order=index-MainMenu2_SubItem_Index[2];
	
	switch (order)
	{
		case 0:
			MainMenu2_Setup_Measure_Range=5;
			break;
		case 1:
			MainMenu2_Setup_Measure_Range=10;
			break;
		case 2:
			MainMenu2_Setup_Measure_Range=20;
			break;
		case 3:
			MainMenu2_Setup_Measure_Range=40;
			break;
		case 4:
			MainMenu2_Setup_Measure_Range=100;
			break;
		case 5:
			MainMenu2_Setup_Measure_Range=200;
			break;
		case 6:
			MainMenu2_Setup_Measure_Range=400;
			break;
		case 7:
			MainMenu2_Setup_Measure_Range=800;
			break;
		
		
		
	}
	
	//ViewA_Set_MeasureMax(MainMenu2_Setup_Measure_Range);
	
	//DataViewPainter_Set_MeasureMax(MainMenu2_Setup_Measure_Range);
	
}

static void MainMenu2_EchoThreshold_Set(int index)
{}

static void MainMenu2_TVGA_Set(int index)
{
	InputDialog_Show(MainMenu2_FrameWin_Handler,SysCFG_Item_TVGA_Index);

	InputDialog_SetStyle(0);

	InputDialog_MoveWindow(4);


}

static void MainMenu2_TVGB_Set(int index)
{

	InputDialog_Show(MainMenu2_FrameWin_Handler,SysCFG_Item_TVGB_Index);

	InputDialog_SetStyle(0);

	InputDialog_MoveWindow(5);

}

static void MainMenu2_TBW_Set(int index)
{

	InputDialog_Show(MainMenu2_FrameWin_Handler,SysCFG_Item_TBS_Index);

	InputDialog_SetStyle(1);

	InputDialog_MoveWindow(6);


}

static void MainMenu2_KeelHeight_Set(int index)
{

	InputDialog_Show(MainMenu2_FrameWin_Handler,SysCFG_Item_KH_Index);

	InputDialog_SetStyle(1);

	InputDialog_MoveWindow(7);

}


static void MainMenu2_NextPage(int index)
{
	MainMenu2_Hide();

	SysMenu_Show(NULL);
}





static void MainMenu2_FrameWin_Create()
{
	MainMenu2_FrameWin_Handler= FRAMEWIN_CreateEx(MainMenu2_Location_X, MainMenu2_Location_Y,MainMenu2_FrameWin_Width,MainMenu2_FrameWin_Heigth, WM_HBKWIN, WM_CF_SHOW, 
	0, 0, "",MainMenu2_CallBack);
 
	FRAMEWIN_SetTitleVis(MainMenu2_FrameWin_Handler,0);
	
	FRAMEWIN_SetClientColor(MainMenu2_FrameWin_Handler,MainMenu2_Frame_Color);
	
}

static void MainMenu2_AddMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags) 
{
  MENU_ITEM_DATA Item;

  Item.pText    = pText;
  Item.hSubmenu = hSubmenu;
  Item.Flags    = Flags;
  Item.Id       = Id;
  
  MENU_AddItem(hMenu, &Item);
}

static  WM_HWIN MainMenu2_Item_Create()
{
	int i=0;

	MainMenu2_Root = MENU_CreateEx(0, 0, MainMenu2_Width, MainMenu2_Heigth, WM_UNATTACHED, 0, MENU_CF_VERTICAL, ID_MENU_2);
	
	for( i=0;i<MainMenu2_ItemNumber-5;i++)
		MainMenu2_SubItemList[i] 	= MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_HORIZONTAL, 0);
	
		
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[0],   0,     "Low",      MainMenu2_SubItem_Index[0],     MENU_IF_DISABLED);
    MainMenu2_AddMenuItem(MainMenu2_SubItemList[0],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[0],   0,     "Mid",     MainMenu2_SubItem_Index[0]+1,    MENU_IF_DISABLED);
    MainMenu2_AddMenuItem(MainMenu2_SubItemList[0],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[0],   0,     "High",    MainMenu2_SubItem_Index[0]+2,  MENU_IF_DISABLED);
	
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[1],   0,     "3dB",      MainMenu2_SubItem_Index[1],     MENU_IF_DISABLED);
    MainMenu2_AddMenuItem(MainMenu2_SubItemList[1],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[1],   0,     "4dB",     MainMenu2_SubItem_Index[1]+1,    MENU_IF_DISABLED);
    MainMenu2_AddMenuItem(MainMenu2_SubItemList[1],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[1],   0,     "5dB",    MainMenu2_SubItem_Index[1]+2,  MENU_IF_DISABLED);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[1],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[1],   0,     "6dB",     MainMenu2_SubItem_Index[1]+3,    MENU_IF_DISABLED);
  

	MainMenu2_AddMenuItem(MainMenu2_SubItemList[2],   0,     "Surface",      MainMenu2_SubItem_Index[2],     MENU_IF_DISABLED);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[2],   0,     "Transducer",     MainMenu2_SubItem_Index[2]+1,    MENU_IF_DISABLED);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[2],   0,     "Keel",    MainMenu2_SubItem_Index[2]+2,  MENU_IF_DISABLED);
	
	
	
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[3],   0,     "0",      MainMenu2_SubItem_Index[3],     MENU_IF_DISABLED);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[3],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[3],   0,     "1",     MainMenu2_SubItem_Index[3]+1,    MENU_IF_DISABLED);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[3],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[3],   0,     "2",    MainMenu2_SubItem_Index[3]+2,  MENU_IF_DISABLED);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[3],   0,      0,          0,                   MENU_IF_SEPARATOR);
	MainMenu2_AddMenuItem(MainMenu2_SubItemList[3],   0,     "3",     MainMenu2_SubItem_Index[3]+3,    MENU_IF_DISABLED);
	




	for( i=0;i<MainMenu2_ItemNumber;i++)
	{
		if (i<=3)
			MainMenu2_AddMenuItem(MainMenu2_Root,MainMenu2_SubItemList[i], MainMenu2_Item[i],   0,  0);
		else
			MainMenu2_AddMenuItem(MainMenu2_Root,MainMenu2_SubItemList[i], MainMenu2_Item[i],   MainMenu2_SubItem_Index[i],  0);
		if (i!=MainMenu2_ItemNumber-1)
			MainMenu2_AddMenuItem(MainMenu2_Root,   0,      0,          0,                   MENU_IF_SEPARATOR);

		if (i!=MainMenu2_Index_SetSmallFont)
			MENU_SetFont(MainMenu2_SubItemList[i], MainMenu2_Sub_Font);
		else
			MENU_SetFont(MainMenu2_SubItemList[i], MainMenu2_Sub_Font_Small);
			
		MENU_SetSkinClassic(MainMenu2_SubItemList[i]);

		MENU_SetTextColor(MainMenu2_SubItemList[i],MENU_CI_ENABLED,MainMenu2_Sub_Sel_Color);
		MENU_SetTextColor(MainMenu2_SubItemList[i],MENU_CI_DISABLED,MainMenu2_Sub_Unsel_Color);
		
		MENU_SetBkColor(MainMenu2_SubItemList[i],MENU_CI_DISABLED,MainMenu2_Sub_Bk_Unsel_Color);
		MENU_SetBkColor(MainMenu2_SubItemList[i],MENU_CI_ENABLED,MainMenu2_Sub_Bk_Unsel_Color);

		MENU_SetBkColor(MainMenu2_SubItemList[i],MENU_CI_SELECTED,MainMenu2_Sub_Bk_Sel_Color);
		MENU_SetBkColor(MainMenu2_SubItemList[i],MENU_CI_DISABLED_SEL,MainMenu2_Sub_Bk_Sel_Color);

		
		//MENU_SetBkColor(MainMenu2_SubItemList[i],MENU_CI_DISABLED,GUI_WHITE);
		
	}
	
	
	

	MENU_SetFont(MainMenu2_Root, &MainMenu2_Font);
	
	MENU_SetSkinClassic(MainMenu2_Root);
	
	MENU_SetBkColor(MainMenu2_Root,MENU_CI_SELECTED,MainMenu2_BK_Color_SEL);
	MENU_SetBkColor(MainMenu2_Root,MENU_CI_ENABLED,MainMenu2_BK_Color_UnSel);
	
	MENU_Attach(MainMenu2_Root,MainMenu2_FrameWin_Handler,MainMenu2_Border_Size,
	MainMenu2_Border_Size,MainMenu2_Width,MainMenu2_Heigth,1);
	MENU_SetOwner(MainMenu2_Root,WM_GetClientWindow(MainMenu2_FrameWin_Handler));
	
	
	

	
	return MainMenu2_Root;
 
}

static void MainMenu2_CallBack(WM_MESSAGE * pMsg)
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
						//MENU_EnableItem(MainMenu2_Root,pData->ItemId);
						//MENU_DisableItem(MainMenu2_Root,pData->ItemId-1);
						MainMenu2_Active_Sel_Item(pData->ItemId);
		  
					}
	  
				break;
				
				case MENU_ON_ITEMACTIVATE:
      
					
					
				break;
				
				case MENU_ON_ITEMSELECT:
      
					Index = MainMenu2_FindOrder(pData->ItemId) ;
					
					(*pFun[Index])(pData->ItemId);
					
					

					//sprintf(acBuffer, "ID of the selected\nitem is 0x%X",Index);
					//MainMenu2_MessageBox(acBuffer, "Message");
	  
				break;
			}
	}
	
	WM_DefaultProc(pMsg);
	
}

static int MainMenu2_FindOrder(int index)
{
	int i=0;
	int Order=88;
	
	for(i=0;i<MainMenu2_ItemNumber;i++)
	{
		if ((index-MainMenu2_SubItem_Index[i])<10)
		{
			Order=i;
			
			break;
		}
					
	}
	
	return Order;
	
}

static void MainMenu2_Active_Sel_Item(int index)
{
	int i;
	int SubMenu_Order=88;
	int Current_Item=0;
	
		
	SubMenu_Order=MainMenu2_FindOrder(index);
	
	if (SubMenu_Order!=88)
	{
		for(i=0;i<MainMenu2_SubItem_Num[SubMenu_Order];i++)
		{
			Current_Item=MainMenu2_SubItem_Index[SubMenu_Order]+i;
			
			if (Current_Item!=index)
				MENU_DisableItem(MainMenu2_Root,Current_Item);
			
		}
		
	}
	
	MENU_EnableItem(MainMenu2_Root,index);
	
	
	
}



WM_HWIN MainMenu2_Create()
{
		MainMenu2_FrameWin_Create();
		
		MainMenu2_Handler=MainMenu2_Item_Create();
		
		WM_SetFocus(MainMenu2_Handler);
		
		return MainMenu2_FrameWin_Handler;

	
	
}




WM_HWIN MainMenu2_Show(WM_HWIN NextWin)
{


	WM_SetDesktopColor(GUI_BLACK);
	
	if (MainMenu2_Handler==NULL)
		MainMenu2_Create();
	else
		WM_ShowWindow(MainMenu2_FrameWin_Handler);


	WM_BringToTop(MainMenu2_FrameWin_Handler);
	WM_SetFocus(MainMenu2_FrameWin_Handler);
	
	if (NextWin!=NULL)
		Next_Win_Handler=NextWin;

	return MainMenu2_FrameWin_Handler;
	
}

void MainMenu2_Hide()
{
	if (MainMenu2_Handler==NULL)
		MainMenu2_Create();
		
	else
		WM_HideWindow(MainMenu2_FrameWin_Handler);


	if (Next_Win_Handler!=NULL)
	{
		
		WM_ShowWindow(Next_Win_Handler);

		//MainMenu_Show(NULL);
		
		WM_BringToTop(Next_Win_Handler);
		WM_SetFocus(Next_Win_Handler);
	}
		
	
}



