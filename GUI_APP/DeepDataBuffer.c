/*****************************************************
*    Deep Data Structure  class
*	Field:
			FrameDataList: 	2D Array element[200][20], 
					element is structure
					{bool valid, int depth(per 500), int Echo_Strenghth}
			
			CurrentData:	1D Array element[20],element as above
			
	Method:		
			DeepBuffer_InsertCurrentData();
*			DeepBuffer_RollFrame_ToLeft();
			
*
*
*
******************************************************
*/
#include "DeepDataBuffer.h"


Buffer_Frame_T     	DeepDataBuffer_Frame    __attribute__((at(0XC0200000)));							//should be located on external sdram

extern 	Data_Node_T 		DeepDataBuffer_CurrentColumn[Max_Column_Num];	//should be located on external sdram

static int 					DeepDataBuffer_CurrentColumn_Index=0;





extern void DeepDataBuffer_Init()
{
	
	DeepDataBuffer_Frame.DeepDataBuffer_Column_Num=0;
	
	DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt=0;
	DeepDataBuffer_Frame.DeepDataBuffer_End_Column_Pt=0;
	DeepDataBuffer_Frame.DeepDataBuffer_Next_Append_Pt=0;

	DeepDataBuffer_Clear_Frame();
	
	
}

static void DeepDataBuffer_Roll_Frame()
{
	int i;
	
	if (DeepDataBuffer_IsEmpty()==0x01)
		return;

	else if (DeepDataBuffer_IsFrameFull()==0x01)
	{
		DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt=(DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt+1)%Max_Frame_Num;
	
		
		DeepDataBuffer_Frame.DeepDataBuffer_End_Column_Pt=(DeepDataBuffer_Frame.DeepDataBuffer_End_Column_Pt+1)%Max_Frame_Num;
	}
	
	else
	{
		DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt=(DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt+1)%Max_Frame_Num;
			
		
	}
	
	
}


 unsigned char DeepDataBuffer_IsEmpty(void)
{
	if (DeepDataBuffer_Frame.DeepDataBuffer_Column_Num==0x00)
		return 1;
	else
		return 0;
}



extern void DeepDataBuffer_Append_Column(Data_Node_T *pCurrentData, int length)
{
	DeepDataBuffer_Roll_Frame();
	
	DeepDataBuffer_Insert_Column(pCurrentData,length);
	
}

static void DeepDataBuffer_Clear_Frame()
{
	int i;
	
	for (i=0;i<Max_Column_Num;i++)
		DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[i][0].ColorID=NULL_NOD;
		
	
}

static void DeepDataBuffer_Save_Frame()
{
	
}

static void DeepDataBuffer_Get_TimeStamp()
{
	
}

void DeepDataBuffer_Insert_Column(Data_Node_T *pCurrentData,int Col_length)
{
	
	int i=0;
	
	if (pCurrentData->ColorID==NULL_NOD)
		
		DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt][0].ColorID=
		NULL_NOD;
	
	
	
	else
	{
		for (i=0;i<Col_length;i++)
		{
			DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt][i].ColorID=
			pCurrentData[i].ColorID;
			
			DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt][i].Depth=
			pCurrentData[i].Depth;
		
				
		}
		DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt][i].ColorID=
		NULL_NOD;
	}
	
	
	if (DeepDataBuffer_IsFrameFull()==0x00)
	
		DeepDataBuffer_Frame.DeepDataBuffer_Column_Num++;
	
	
}

unsigned char DeepDataBuffer_IsFrameFull(void)
{
	if  (DeepDataBuffer_Frame.DeepDataBuffer_Column_Num==Max_Frame_Num)
		return 0x01;
	else 
		return 0x00;
	
}

unsigned char  DeepDataBuffer_IsColumnValid(int ColumnIndex)
{
	if(DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[ColumnIndex][0].ColorID!=NULL_NOD)
		return 0x01;
	else
		return 0x00;
	
}

unsigned char DeepDataBuffer_IsDataValid(int ColumnIndex, int RowIndex)
{
	if(DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[ColumnIndex][RowIndex].ColorID!=NULL_NOD)
		return 0x01;
	else
		return 0x00;
}

Data_Node_T * DeepDataBuffer_GetColumn(int ColumnIndex)
{
	
	return DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[ColumnIndex];
}

int  DeepDataBuffer_Get_Frame_Column_Num()
{
	return DeepDataBuffer_Frame.DeepDataBuffer_Column_Num;
	
}


void DeepDataBuffer_Create_SimData()
{
	int i;
	
	DeepDataBuffer_Frame.DeepDataBuffer_Column_Num=0;
	
	DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt=0;
	DeepDataBuffer_Frame.DeepDataBuffer_End_Column_Pt=0;

	for (i=0;i<200;i++)
	{
		
		DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[i][0].ColorID=NULL_NOD;
		
		//DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[i][0].Depth=300;
		
		//DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[i][1].ColorID=NULL_NOD;
	}
	
	
	
}

static Data_Node_T  SimColumn[3];

Data_Node_T * DeepDataBuffer_Create_SimColumn(void)
{
	
	int length=5;
	
	SimColumn[0].ColorID=0;
	SimColumn[0].Depth=95;
	
	SimColumn[1].ColorID=0;
	SimColumn[1].Depth=95;
	
	SimColumn[2].ColorID=0;
	SimColumn[2].Depth=95;
	
	SimColumn[3].ColorID=rand()%3+1;
	SimColumn[3].Depth=120+rand()%50;
	
	SimColumn[4].ColorID=rand()%3+2;
	SimColumn[4].Depth=200+rand()%100;
	
	
	SimColumn[5].ColorID=rand()%3+2;
	SimColumn[5].Depth=200+rand()%100;
	
	SimColumn[6].ColorID=rand()%3+2;
	SimColumn[6].Depth=200+rand()%100;
	
	SimColumn[7].ColorID=NULL_NOD;
	
	return SimColumn;
	
}
