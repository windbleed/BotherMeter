#ifndef DeepDataBuffer_Unit
#define DeepDataBuffer_Unit

#include "SystemCFG.h"

#define Max_Frame_Num 	200
#define Max_Column_Num	500

#define NULL_NOD        0x55



typedef struct DataNode
{
    unsigned short 	ColorID;
    unsigned short 	Depth;

}Data_Node_T;

/*
typedef struct TimeStamp
{
    unsigned char 	Hour;
    unsigned char 	Min;
	unsigned char   Second;

}Time_Stamp_T;
*/


typedef struct DataBufferFrame
{
	Time_Stamp_T 	DeepDataBuffer_TimeStamp;
	
	int          	DeepDataBuffer_Start_Column_Pt;

	int 			DeepDataBuffer_End_Column_Pt;
	
	int 			DeepDataBuffer_Next_Append_Pt;

	int 			DeepDataBuffer_Column_Num;
	
	int 			DeepDataBuffer_Num;
	
	
	Data_Node_T DeepDataBuffer_FrameArray[Max_Frame_Num][Max_Column_Num]; 	
	
}Buffer_Frame_T;


extern   Buffer_Frame_T     	DeepDataBuffer_Frame;							//should be located on external sdram

extern 	Data_Node_T 			DeepDataBuffer_CurrentColumn[Max_Column_Num];	//should be locaated on external sdram



extern void DeepDataBuffer_Insert_Column(Data_Node_T *pCurrentData,int Col_length);

static void DeepDataBuffer_Roll_Frame(void);

extern void DeepDataBuffer_Append_Column(Data_Node_T *pCurrentData, int length);

static void DeepDataBuffer_Clear_Frame(void);



extern unsigned char DeepDataBuffer_IsColumnValid(int ColumnIndex);

extern unsigned char DeepDataBuffer_IsDataValid(int ColumnIndex, int RowIndex);

extern Data_Node_T * DeepDataBuffer_GetColumn(int ColumnIndex);

extern int  DeepDataBuffer_Get_Frame_Column_Num(void);

extern unsigned char DeepDataBuffer_IsFrameFull(void);

static void DeepDataBuffer_Save_Frame(void);

static void DeepDataBuffer_Get_TimeStamp(void);

extern unsigned char DeepDataBuffer_IsEmpty(void);

extern void DeepDataBuffer_Init();

//extern void DeepDataBuffer_Create_SimData();

//extern Data_Node_T *  DeepDataBuffer_Create_SimColumn();

#endif
