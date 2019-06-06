#ifndef ViewA_Unit
#define ViewA_Unit

#include "GUI.h"
#include "FRAMEWIN.h"
#include "WM.h"

#include "stdlib.h"
#include <string.h>
#include <math.h>
#include "GRAPH.h"
#include "TEXT.h"


#define ViewA_Location_X    			0
#define	ViewA_Location_Y				50
#define ViewA_Width    				790
#define	ViewA_Heigth					520

#define ViewA_Scale_Num				10


#define ViewA_Border_Size			5
#define ViewA_FrameWin_Width    		(ViewA_Width+2*ViewA_Border_Size)
#define ViewA_FrameWin_Heigth		(ViewA_Heigth+2*ViewA_Border_Size)


#define ViewA_VScale_Location		(ViewA_Width-5)
#define ViewA_HScale_Location		30

#define ViewA_BK_Color				GUI_BLUE


#define	ViewA_VScale_Color			GUI_WHITE
#define	ViewA_HScale_Color			GUI_DARKGREEN

#define ViewA_Data_Color				GUI_WHITE



#define ViewA_Sub_Bk_Sel_Color		GUI_ORANGE
#define ViewA_Sub_Bk_Unsel_Color 	GUI_LIGHTGREEN


#define ViewA_Data_Font				GUI_FONT_D32
#define ViewA_Scale_Font				GUI_FONT_COMIC18B_ASCII
#define ViewA_Comment_Font			GUI_FONT_20_ASCII




#define ViewA_DeepStr_Location_X    		50
#define ViewA_DeepStr_Location_Y			450

#define ViewA_DeepStr_Width				120
#define ViewA_DeepStr_Heigth				60

#define ViewA_UnitStr_Location_X			150
#define ViewA_UnitStr_Location_Y			465


#define ViewA_SensorStr_Location_X      	55
#define ViewA_SensorStr_Location_Y		490

#define ViewA_SensorLoc_Location_X		130
#define ViewA_SensorLoc_Location_Y		490

#define ViewA_Comment_Width				80
#define ViewA_Comment_Heigth				20

#define ViewA_DeepData_Font				GUI_Font_D80
#define ViewA_Comment_Font				GUI_FONT_20_ASCII







#define MAX_ECHO_Type_Num				  7

#define ViewA_XYData_Max_Num         200



static void ViewA_FrameWin_Create(void);


static void ViewA_CallBack(WM_MESSAGE * pMsg);
static void ViewA_Frame_CallBack(WM_MESSAGE * pMsg);



static void ViewA_Init(void);


extern WM_HWIN ViewA_Show(WM_HWIN NextHWin);
extern void ViewA_Hide(void);

extern WM_HWIN ViewA_Create(void);

extern WM_HWIN ViewA_Get_Handler(void);

static void ViewA_Create_DeepData_Str(void);
static void ViewA_Create_Unit_Str(void);
static void ViewA_Create_SensorFreq_Str(void);
static void ViewA_Create_SensorLoc_Str(void);



extern void ViewA_Set_DeepData_Str(int value);
extern void ViewA_Set_Unit_Str(char * str);
extern void ViewA_Set_SensorFreq_Str(char * str);
extern void ViewA_Set_SensorLoc_Str(char * str);


#endif



