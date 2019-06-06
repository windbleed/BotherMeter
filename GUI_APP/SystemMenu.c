

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
*   Method: CreateSysMenu(int loc_x, int loc_y)						*
*			MenuShow();													*
*			MenuHide();													*
*			MenuCallBack();												*
*                            -------------------by Softwind 2019/5/5	*
*************************************************************************/

#include "SystemMenu.h"
#include "GUI.h"
#include "WM.h"
#include "ViewA.h"
#include "App_start.h"
#include "ViewB.h"
#include "MainMenu.h"



#define ID_MENU_SYS					(GUI_ID_USER +  520)



#define SysMenu_ItemNumber 	6

int SysMenu_Setup_Measure_Range=40;


static WM_HWIN SysMenu_Handler=NULL;
static WM_HWIN SysMenu_FrameWin_Handler=NULL;

static WM_HWIN Next_Win_Handler=NULL;

static MENU_Handle SysMenu_Root;
static MENU_Handle SysMenu_SubItemList[SysMenu_ItemNumber];

static int SysMenu_SubItem_Index[SysMenu_ItemNumber]=
{
	GUI_ID_USER +  530,GUI_ID_USER + 540, GUI_ID_USER +  550,GUI_ID_USER +  560,GUI_ID_USER +  570,
	GUI_ID_USER +  580
};

static int SysMenu_SubItem_Num[SysMenu_ItemNumber]=
{
	3,5,8,4,2,0
};

static char SysMenu_Item[SysMenu_ItemNumber][25]=
{
	
	
	//"      Language",
	"语言",

	//"     Simulation",

	"仿真",

	//"   Storage Interval ",
	"存储间隔",


	//"    History Review",
	"历史浏览",

	//"    Factory Setting",
	"出厂设置",

	//"    General Menu"
	"通用菜单"


	
	
};




static void (* pFun[SysMenu_ItemNumber])(int index)=
{
	SysMenu_Language_Set,
	SysMenu_Sim_Set,
	SysMenu_StoreInterval_Set,
	SysMenu_HistoryReview_Set,
	SysMenu_FactorySetting_Set,

	SysMenu_NextPage
	
	
	
};




static MENU_MSG_DATA * pData;
static MENU_ITEM_DATA  Data;


static void SysMenu_Language_Set(int index)
{
	unsigned short info=0 ;

	
	
	
	
	
	
	
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


	
	
		
	
	
	
	
}

static void SysMenu_Sim_Set(int index)
{}

static void SysMenu_StoreInterval_Set(int index)
{
	int order=index-SysMenu_SubItem_Index[2];
	
	switch (order)
	{
		case 0:
			SysMenu_Setup_Measure_Range=5;
			break;
		case 1:
			SysMenu_Setup_Measure_Range=10;
			break;
		case 2:
			SysMenu_Setup_Measure_Range=20;
			break;
		case 3:
			SysMenu_Setup_Measure_Range=40;
			break;
		case 4:
			SysMenu_Setup_Measure_Range=100;
			break;
		case 5:
			SysMenu_Setup_Measure_Range=200;
			break;
		case 6:
			SysMenu_Setup_Measure_Range=400;
			break;
		case 7:
			SysMenu_Setup_Measure_Range=800;
			break;
		
		
		
	}
	
	//ViewA_Set_MeasureMax(SysMenu_Setup_Measure_Range);
	
	//DataViewPainter_Set_MeasureMax(SysMenu_Setup_Measure_Range);
	
}

static void SysMenu_HistoryReview_Set(int index)
{}

static void SysMenu_FactorySetting_Set(int index)
{}


static void SysMenu_NextPage(int index)
{
	SysMenu_Hide();
	//MainMenu_Show(NULL);
	MainMenu_Show(NULL);
}






static void SysMenu_FrameWin_Create()
{
	SysMenu_FrameWin_Handler= FRAMEWIN_CreateEx(SysMenu_Location_X, SysMenu_Location_Y,SysMenu_FrameWin_Width,SysMenu_FrameWin_Heigth, WM_HBKWIN, WM_CF_SHOW, 
	0, 0, "",SysMenu_CallBack);
 
	FRAMEWIN_SetTitleVis(SysMenu_FrameWin_Handler,0);
	
	FRAMEWIN_SetClientColor(SysMenu_FrameWin_Handler,SysMenu_Frame_Color);
	
}

static void SysMenu_AddMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags) 
{
  MENU_ITEM_DATA Item;

  Item.pText    = pText;
  Item.hSubmenu = hSubmenu;
  Item.Flags    = Flags;
  Item.Id       = Id;
  
  MENU_AddItem(hMenu, &Item);
}

static  WM_HWIN SysMenu_Item_Create()
{
	int i=0;

	SysMenu_Root = MENU_CreateEx(0, 0, SysMenu_Width, SysMenu_Heigth, WM_UNATTACHED, 0, MENU_CF_VERTICAL, ID_MENU_SYS);
	
	for( i=0;i<SysMenu_ItemNumber-1;i++)
		SysMenu_SubItemList[i] 	= MENU_CreateEx(0, 0, 0, 0, WM_UNATTACHED, 0, MENU_CF_HORIZONTAL, 0);
	
		
	SysMenu_AddMenuItem(SysMenu_SubItemList[0],   0,     "CHinese",      SysMenu_SubItem_Index[0],     MENU_IF_DISABLED);
    SysMenu_AddMenuItem(SysMenu_SubItemList[0],   0,      0,          0,                   MENU_IF_SEPARATOR);
	SysMenu_AddMenuItem(SysMenu_SubItemList[0],   0,     "English",     SysMenu_SubItem_Index[0]+1,    MENU_IF_DISABLED);
 
	
	SysMenu_AddMenuItem(SysMenu_SubItemList[1],   0,     "Disable",      SysMenu_SubItem_Index[1],     MENU_IF_DISABLED);
    SysMenu_AddMenuItem(SysMenu_SubItemList[1],   0,      0,          0,                   MENU_IF_SEPARATOR);
	SysMenu_AddMenuItem(SysMenu_SubItemList[1],   0,     "Enable",     SysMenu_SubItem_Index[1]+1,    MENU_IF_DISABLED);
  

	SysMenu_AddMenuItem(SysMenu_SubItemList[2],   0,     "Disable",      SysMenu_SubItem_Index[2],     MENU_IF_DISABLED);
	SysMenu_AddMenuItem(SysMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	SysMenu_AddMenuItem(SysMenu_SubItemList[2],   0,     "5S",     SysMenu_SubItem_Index[2]+1,    MENU_IF_DISABLED);
	SysMenu_AddMenuItem(SysMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	SysMenu_AddMenuItem(SysMenu_SubItemList[2],   0,     "15S",    SysMenu_SubItem_Index[2]+2,  MENU_IF_DISABLED);
	SysMenu_AddMenuItem(SysMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	SysMenu_AddMenuItem(SysMenu_SubItemList[2],   0,     "30S",     SysMenu_SubItem_Index[2]+3,    MENU_IF_DISABLED);
	SysMenu_AddMenuItem(SysMenu_SubItemList[2],   0,      0,          0,                   MENU_IF_SEPARATOR);
	SysMenu_AddMenuItem(SysMenu_SubItemList[2],   0,     "60S",    SysMenu_SubItem_Index[2]+4,  MENU_IF_DISABLED);

	
	
	SysMenu_AddMenuItem(SysMenu_SubItemList[3],   0,     "Disable",      SysMenu_SubItem_Index[3],     MENU_IF_DISABLED);
	SysMenu_AddMenuItem(SysMenu_SubItemList[3],   0,      0,          0,                   MENU_IF_SEPARATOR);
	SysMenu_AddMenuItem(SysMenu_SubItemList[3],   0,     "For",     SysMenu_SubItem_Index[3]+1,    MENU_IF_DISABLED);
	SysMenu_AddMenuItem(SysMenu_SubItemList[3],   0,      0,          0,                   MENU_IF_SEPARATOR);
	SysMenu_AddMenuItem(SysMenu_SubItemList[3],   0,     "Play",    SysMenu_SubItem_Index[3]+2,  MENU_IF_DISABLED);
	SysMenu_AddMenuItem(SysMenu_SubItemList[3],   0,      0,          0,                   MENU_IF_SEPARATOR);
	SysMenu_AddMenuItem(SysMenu_SubItemList[3],   0,     "Back",     SysMenu_SubItem_Index[3]+3,    MENU_IF_DISABLED);
	
	SysMenu_AddMenuItem(SysMenu_SubItemList[4],   0,     "Disable",      SysMenu_SubItem_Index[4],     MENU_IF_DISABLED);
	SysMenu_AddMenuItem(SysMenu_SubItemList[4],   0,      0,          0,                   MENU_IF_SEPARATOR);
	SysMenu_AddMenuItem(SysMenu_SubItemList[4],   0,     "Enable",     SysMenu_SubItem_Index[4]+1,    MENU_IF_DISABLED);




	for( i=0;i<SysMenu_ItemNumber;i++)
	{
		if (i<=4)
			SysMenu_AddMenuItem(SysMenu_Root,SysMenu_SubItemList[i], SysMenu_Item[i],   0,  0);
		else
			SysMenu_AddMenuItem(SysMenu_Root,SysMenu_SubItemList[i], SysMenu_Item[i],   SysMenu_SubItem_Index[i],  0);
		if (i!=SysMenu_ItemNumber-1)
			SysMenu_AddMenuItem(SysMenu_Root,   0,      0,          0,                   MENU_IF_SEPARATOR);

		if (i!=SysMenu_Index_SetSmallFont)
			MENU_SetFont(SysMenu_SubItemList[i], SysMenu_Sub_Font);
		else
			MENU_SetFont(SysMenu_SubItemList[i], SysMenu_Sub_Font_Small);
			
		MENU_SetSkinClassic(SysMenu_SubItemList[i]);

		MENU_SetTextColor(SysMenu_SubItemList[i],MENU_CI_ENABLED,SysMenu_Sub_Sel_Color);
		MENU_SetTextColor(SysMenu_SubItemList[i],MENU_CI_DISABLED,SysMenu_Sub_Unsel_Color);
		
		MENU_SetBkColor(SysMenu_SubItemList[i],MENU_CI_DISABLED,SysMenu_Sub_Bk_Unsel_Color);
		MENU_SetBkColor(SysMenu_SubItemList[i],MENU_CI_ENABLED,SysMenu_Sub_Bk_Unsel_Color);

		MENU_SetBkColor(SysMenu_SubItemList[i],MENU_CI_SELECTED,SysMenu_Sub_Bk_Sel_Color);
		MENU_SetBkColor(SysMenu_SubItemList[i],MENU_CI_DISABLED_SEL,SysMenu_Sub_Bk_Sel_Color);

		
		//MENU_SetBkColor(SysMenu_SubItemList[i],MENU_CI_DISABLED,GUI_WHITE);
		
	}
	
	
	

	MENU_SetFont(SysMenu_Root, &SysMenu_Font);
	
	MENU_SetSkinClassic(SysMenu_Root);
	
	MENU_SetBkColor(SysMenu_Root,MENU_CI_SELECTED,SysMenu_BK_Color_SEL);
	MENU_SetBkColor(SysMenu_Root,MENU_CI_ENABLED,SysMenu_BK_Color_UnSel);
	
	MENU_Attach(SysMenu_Root,SysMenu_FrameWin_Handler,SysMenu_Border_Size,
	SysMenu_Border_Size,SysMenu_Width,SysMenu_Heigth,1);
	MENU_SetOwner(SysMenu_Root,WM_GetClientWindow(SysMenu_FrameWin_Handler));
	
	
	

	
	return SysMenu_Root;
 
}

static void SysMenu_CallBack(WM_MESSAGE * pMsg)
{
	
	int             xSize;
	int             ySize;

	WM_HWIN         hWin;
	WM_HWIN         hClient;


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
						//MENU_EnableItem(SysMenu_Root,pData->ItemId);
						//MENU_DisableItem(SysMenu_Root,pData->ItemId-1);
						SysMenu_Active_Sel_Item(pData->ItemId);
		  
					}
	  
				break;
				
				case MENU_ON_ITEMACTIVATE:
      
					
					
				break;
				
				case MENU_ON_ITEMSELECT:
      
					Index = SysMenu_FindOrder(pData->ItemId) ;
					
					(*pFun[Index])(pData->ItemId);
					
					

					//sprintf(acBuffer, "ID of the selected\nitem is 0x%X",Index);
					//SysMenu_MessageBox(acBuffer, "Message");
	  
				break;
			}
	}
	
	WM_DefaultProc(pMsg);
	
}

static int SysMenu_FindOrder(int index)
{
	int i=0;
	int Order=88;
	
	for(i=0;i<SysMenu_ItemNumber;i++)
	{
		if ((index-SysMenu_SubItem_Index[i])<10)
		{
			Order=i;
			
			break;
		}
					
	}
	
	return Order;
	
}

static void SysMenu_Active_Sel_Item(int index)
{
	int i;
	int SubMenu_Order=88;
	int Current_Item=0;
	
		
	SubMenu_Order=SysMenu_FindOrder(index);
	
	if (SubMenu_Order!=88)
	{
		for(i=0;i<SysMenu_SubItem_Num[SubMenu_Order];i++)
		{
			Current_Item=SysMenu_SubItem_Index[SubMenu_Order]+i;
			
			if (Current_Item!=index)
				MENU_DisableItem(SysMenu_Root,Current_Item);
			
		}
		
	}
	
	MENU_EnableItem(SysMenu_Root,index);
	
	
	
}



WM_HWIN SysMenu_Create()
{
		SysMenu_FrameWin_Create();
		
		SysMenu_Handler=SysMenu_Item_Create();
		
		WM_SetFocus(SysMenu_Handler);
		
		return SysMenu_FrameWin_Handler;

	
	
}




WM_HWIN SysMenu_Show(WM_HWIN NextWin)
{


	WM_SetDesktopColor(GUI_BLACK);
	
	if (SysMenu_Handler==NULL)
		SysMenu_Create();
	else
		WM_ShowWindow(SysMenu_FrameWin_Handler);


	WM_BringToTop(SysMenu_FrameWin_Handler);
	WM_SetFocus(SysMenu_FrameWin_Handler);
	
	if (NextWin!=NULL)
		Next_Win_Handler=NextWin;

	return SysMenu_FrameWin_Handler;
	
}

void SysMenu_Hide()
{
	if (SysMenu_Handler==NULL)
		SysMenu_Create();
		
	else
		WM_HideWindow(SysMenu_FrameWin_Handler);


	if (Next_Win_Handler!=NULL)
	{
		
		WM_ShowWindow(Next_Win_Handler);

		//MainMenu_Show(NULL);
		
		WM_BringToTop(Next_Win_Handler);
		WM_SetFocus(Next_Win_Handler);
	}
		
	
}



