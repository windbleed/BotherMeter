#ifndef MainMenu_Unit
#define MainMenu_Unit

#include "GUI.h"
#include "MENU.h"
#include "FRAMEWIN.h"
#include "WM.h"
#include "MESSAGEBOX.h"

#include "EmWinHZFont.h"


#include <stdio.h>


#define MainMenu_Location_X    		280
#define	MainMenu_Location_Y			100
#define MainMenu_Width    			240
#define	MainMenu_Heigth				380


#define MainMenu_Border_Size		5
#define MainMenu_FrameWin_Width    	(MainMenu_Width+2*MainMenu_Border_Size)
#define MainMenu_FrameWin_Heigth	(MainMenu_Heigth+2*MainMenu_Border_Size)

#define MainMenu_Frame_Color        GUI_CYAN

#define MainMenu_BK_Color_SEL		GUI_ORANGE
#define MainMenu_BK_Color_UnSel		GUI_WHITE

#define	MainMenu_Sub_Sel_Color		GUI_BLACK
#define MainMenu_Sub_Unsel_Color	GUI_GRAY

#define MainMenu_Sub_Bk_Sel_Color	GUI_ORANGE
#define MainMenu_Sub_Bk_Unsel_Color GUI_LIGHTGREEN


#define MainMenu_Font				  GUI_FontHZ24
//GUI_FONT_COMIC24B_ASCII
#define MainMenu_Sub_Font			GUI_FONT_COMIC18B_ASCII
#define MainMenu_Sub_Font_Small     GUI_FONT_COMIC18B_ASCII

#define MainMenu_Index_SetSmallFont 2


#define ID_MENU             (GUI_ID_USER +  0)


extern int MainMenu_Setup_Measure_Range;

static void MainMenu_FrameWin_Create(void);

static void MainMenu_AddMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags);

static void MainMenu_CallBack(WM_MESSAGE * pMsg);

static void MainMenu_Active_Sel_Item(int index);

static WM_HWIN MainMenu_Item_Create(void);

static int MainMenu_FindOrder(int index);

static void MainMenu_Channel_Sel(int index);
static void MainMenu_FrameRate_Set(int index);
static void MainMenu_Range_Adj(int index);
static void MainMenu_Pwr_Set(int index);
static void MainMenu_Mode_Set(int index);
static void MainMenu_GainA_Set(int index);
static void MainMenu_GainB_Set(int index);
static void MainMenu_WarnDeep_Set(int index);
static void MainMenu_Date_Set(int index);
static void MainMenu_Time_Set(int index);
static void MainMenu_NextPage(int index);

static void MainMenu_MessageBox(const char * pText, const char * pCaption) ;



extern WM_HWIN MainMenu_Create(void);
extern WM_HWIN MainMenu_Show(WM_HWIN NextWin);
extern void MainMenu_Hide(void);

extern void MainMenu_Get_InputBox(int menuItemIndex,int value);







#endif
