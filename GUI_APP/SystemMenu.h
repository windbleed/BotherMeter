#ifndef SysMenu_Unit
#define SysMenu_Unit

#include "GUI.h"
#include "MENU.h"
#include "FRAMEWIN.h"
#include "WM.h"
#include "MESSAGEBOX.h"




#include <stdio.h>


#define SysMenu_Location_X    	280
#define	SysMenu_Location_Y			100
#define SysMenu_Width    			240
#define	SysMenu_Heigth				201


#define SysMenu_Border_Size		5
#define SysMenu_FrameWin_Width    	(SysMenu_Width+2*SysMenu_Border_Size)
#define SysMenu_FrameWin_Heigth	(SysMenu_Heigth+2*SysMenu_Border_Size)

#define SysMenu_Frame_Color        GUI_CYAN

#define SysMenu_BK_Color_SEL		GUI_ORANGE
#define SysMenu_BK_Color_UnSel		GUI_WHITE

#define	SysMenu_Sub_Sel_Color		GUI_BLACK
#define SysMenu_Sub_Unsel_Color	GUI_GRAY

#define SysMenu_Sub_Bk_Sel_Color	GUI_ORANGE
#define SysMenu_Sub_Bk_Unsel_Color GUI_LIGHTGREEN


#define SysMenu_Font				 GUI_FontHZ24
//GUI_FONT_COMIC24B_ASCII
#define SysMenu_Sub_Font			GUI_FONT_COMIC18B_ASCII
#define SysMenu_Sub_Font_Small     GUI_FONT_COMIC18B_ASCII

#define SysMenu_Index_SetSmallFont 2


#define ID_MENU             (GUI_ID_USER +  0)


extern int SysMenu_Setup_Measure_Range;

static void SysMenu_FrameWin_Create(void);

static void SysMenu_AddMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags);

static void SysMenu_CallBack(WM_MESSAGE * pMsg);

static void SysMenu_Active_Sel_Item(int index);

static WM_HWIN SysMenu_Item_Create(void);

static int SysMenu_FindOrder(int index);

static void SysMenu_Language_Set(int index);

static void SysMenu_Sim_Set(int index);
static void SysMenu_StoreInterval_Set(int index);

static void SysMenu_HistoryReview_Set(int index);

static void SysMenu_FactorySetting_Set(int index);

static void SysMenu_NextPage(int index);

static void SysMenu_MessageBox(const char * pText, const char * pCaption) ;



extern WM_HWIN SysMenu_Create(void);
extern WM_HWIN SysMenu_Show(WM_HWIN NextWin);
extern void SysMenu_Hide(void);


#endif
