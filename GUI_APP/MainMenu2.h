#ifndef MainMenu2_Unit
#define MainMenu2_Unit

#include "GUI.h"
#include "MENU.h"
#include "FRAMEWIN.h"
#include "WM.h"
#include "MESSAGEBOX.h"
#include "EmWinHZFont.h"




#include <stdio.h>


#define MainMenu2_Location_X    	280
#define	MainMenu2_Location_Y			100
#define MainMenu2_Width    			240
#define	MainMenu2_Heigth				305


#define MainMenu2_Border_Size		5
#define MainMenu2_FrameWin_Width    	(MainMenu2_Width+2*MainMenu2_Border_Size)
#define MainMenu2_FrameWin_Heigth	(MainMenu2_Heigth+2*MainMenu2_Border_Size)

#define MainMenu2_Frame_Color        GUI_CYAN

#define MainMenu2_BK_Color_SEL		GUI_ORANGE
#define MainMenu2_BK_Color_UnSel		GUI_WHITE

#define	MainMenu2_Sub_Sel_Color		GUI_BLACK
#define MainMenu2_Sub_Unsel_Color	GUI_GRAY

#define MainMenu2_Sub_Bk_Sel_Color	GUI_ORANGE
#define MainMenu2_Sub_Bk_Unsel_Color GUI_LIGHTGREEN


#define MainMenu2_Font				  GUI_FontHZ24
//GUI_FONT_COMIC24B_ASCII
#define MainMenu2_Sub_Font			GUI_FONT_COMIC18B_ASCII
#define MainMenu2_Sub_Font_Small     GUI_FONT_COMIC18B_ASCII

#define MainMenu2_Index_SetSmallFont 2


#define ID_MENU             (GUI_ID_USER +  0)


extern int MainMenu2_Setup_Measure_Range;

static void MainMenu2_FrameWin_Create(void);

static void MainMenu2_AddMenuItem(MENU_Handle hMenu, MENU_Handle hSubmenu, const char* pText, U16 Id, U16 Flags);

static void MainMenu2_CallBack(WM_MESSAGE * pMsg);

static void MainMenu2_Active_Sel_Item(int index);

static WM_HWIN MainMenu2_Item_Create(void);

static int MainMenu2_FindOrder(int index);

static void MainMenu2_PulseWidth_Sel(int index);

static void MainMenu2_DynamicRange_Set(int index);

static void MainMenu2_DepthRef_Set(int index);
static void MainMenu2_EchoThreshold_Set(int index);
static void MainMenu2_TVGA_Set(int index);

static void MainMenu2_TVGB_Set(int index);
static void MainMenu2_TBW_Set(int index);
static void MainMenu2_KeelHeight_Set(int index);
static void MainMenu2_NextPage(int index);
static void MainMenu2_MessageBox(const char * pText, const char * pCaption) ;



extern WM_HWIN MainMenu2_Create(void);
extern WM_HWIN MainMenu2_Show(WM_HWIN NextWin);
extern void MainMenu2_Hide(void);





#endif
