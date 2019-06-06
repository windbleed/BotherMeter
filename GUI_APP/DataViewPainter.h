#ifndef DataViewPainter_Unit
#define DataViewPainter_Unit

#include "GUI.h"
#include "DeepDataBuffer.h"
#include "WM.h"
#include "TEXT.h"
#include "stdlib.h"
#include <string.h>
#include <math.h>

#define DataViewPainter_Width    				780
#define	DataViewPainter_Heigth					200

extern GUI_MEMDEV_Handle DataViewPainter_Memdev_Handler;

extern unsigned char DataViewPainter_IsColorBar_ON;




static void	DataViewPainter_Draw_Column(Data_Node_T * DataNode_Pt,int colNum);
static void	DataViewPainter_Draw_Node(int x, int y,int colorId,int dot_heigth);
extern void	DataViewPainter_Draw_ColorBar(void);
static void	DataViewPainter_Draw_TimeLine(void);
static void	DataViewPainter_Draw_DeepData(float value);
static void	DataViewPainter_Draw_Comment(char * sensorLoc,char * sensorFreq);

static void DataViewPainter_Serialize(void);
static char * float2str(float val, int precision, char *buf);		


//extern  void	DataViewPainter_Draw_Frame(Buffer_Frame_T * DataFrame_Pt);

extern 	void	DataViewPainter_Draw_Frame(WM_HWIN TargetWin,Buffer_Frame_T * DataFrame_Pt,int channelMode);



extern void DataViewPainter_Draw_Frame_on_Mem(Buffer_Frame_T * DataFrame_Pt);
extern void DataViewPainter_Reflash_From_Mem(void);

extern void DataViewPainter_Draw_Scale(WM_HWIN TargetWin,int channelMode);
extern void	DataViewPainter_Draw_ColorBar(void);

extern void DataViewPainter_Set_MeasureMax(int value);
extern void DataViewPainter_Set_DeepData_Str(TEXT_Handle tHandler,int value);

#endif
