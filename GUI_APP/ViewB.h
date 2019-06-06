#ifndef ViewB_Unit
#define ViewB_Unit



#include "GUI.h"
#include "FRAMEWIN.h"
#include "WM.h"

#include "stdlib.h"
#include <string.h>
#include <math.h>
#include "GRAPH.h"
#include "TEXT.h"


#define ViewB_Location_X    			0
#define	ViewB_Location_Y				50
#define ViewB_Width    				790
#define	ViewB_Heigth					520

#define ViewB_Scale_Num				10


#define ViewB_Border_Size			5
#define ViewB_FrameWin_Width    		(ViewB_Width+2*ViewB_Border_Size)
#define ViewB_FrameWin_Heigth		(ViewB_Heigth+2*ViewB_Border_Size)


#define ViewB_VScale_Location		(ViewB_Width-5)
#define ViewB_HScale_Location		30

#define ViewB_BK_Color				GUI_BLUE


#define	ViewB_VScale_Color			GUI_WHITE
#define	ViewB_HScale_Color			GUI_DARKGREEN

#define ViewB_Data_Color				GUI_WHITE



#define ViewB_Sub_Bk_Sel_Color		GUI_ORANGE
#define ViewB_Sub_Bk_Unsel_Color 	GUI_LIGHTGREEN


#define ViewB_Data_Font				GUI_FONT_D32
#define ViewB_Scale_Font				GUI_FONT_COMIC18B_ASCII
#define ViewB_Comment_Font			GUI_FONT_20_ASCII




#define ViewB_DeepStr_Location_X    		50
#define ViewB_DeepStr_Location_Y			450

#define ViewB_DeepStr_Width				120
#define ViewB_DeepStr_Heigth				60

#define ViewB_UnitStr_Location_X			150
#define ViewB_UnitStr_Location_Y			465


#define ViewB_SensorStr_Location_X      	55
#define ViewB_SensorStr_Location_Y		490

#define ViewB_SensorLoc_Location_X		130
#define ViewB_SensorLoc_Location_Y		490

#define ViewB_Comment_Width				80
#define ViewB_Comment_Heigth				20

#define ViewB_DeepData_Font				GUI_Font_D80
#define ViewB_Comment_Font				GUI_FONT_20_ASCII







#define MAX_ECHO_Type_Num				  7

#define ViewB_XYData_Max_Num         200



static void ViewB_FrameWin_Create(void);


static void ViewB_CallBack(WM_MESSAGE * pMsg);

static void ViewB_Frame_CallBack(WM_MESSAGE * pMsg);

static void ViewB_Init(void);




extern WM_HWIN ViewB_Show(WM_HWIN NextHWin);
extern void ViewB_Hide(void);

extern WM_HWIN ViewB_Create(void);

extern WM_HWIN ViewB_Get_Handler(void);

static void ViewB_Create_DeepData_Str(void);
static void ViewB_Create_Unit_Str(void);
static void ViewB_Create_SensorFreq_Str(void);
static void ViewB_Create_SensorLoc_Str(void);




extern void ViewB_Set_Unit_Str(char * str);
extern void ViewB_Set_SensorFreq_Str(char * str);
extern void ViewB_Set_SensorLoc_Str(char * str);




#endif
