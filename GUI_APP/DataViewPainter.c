/*****************************************************
*   	 Data View Painer  class
*   This object is for draw the picture on the memory device according to the deepdatabuffer.
*
*	Field:
			DataViewPainter_MemDevice
			DataViewPainter_ColorArray
			
			
	Method:		
			DataViewPainter_Draw_Scale
			DataViewPainter_Draw_Frame
			DataViewPainter_Draw_Column
			DataViewPainter_Draw_Nod
			DataViewPainter_Draw_ColorBar
			DataViewPainter_Draw_TimeLine
			DataViewPainter_Draw_DeepData
			DataViewPainter_Draw_Comment
			
			
*
*
*
******************************************************/
#include "DataViewPainter.h"
#include "ViewA.h"
#include "ViewB.h"
#include "MainMenu.h"


#define MAX_ECHO_Type_Num	7


static GUI_COLOR	ECHO_Data_Color[MAX_ECHO_Type_Num]=
{
	GUI_DARKRED,GUI_RED,GUI_LIGHTRED,GUI_YELLOW,GUI_GREEN,GUI_LIGHTCYAN,GUI_LIGHTBLUE
};

static int DataViewPainter_Measure_Max=40;



static int DataViewPainter_Horizontal_Step=1;

static int DataViewPainter_Horizontal_DataLine_Start=790;

static int DataViewPainter_Horizontal_DataLine_Stop=10;


static int ViewB_In_Two=0;

GUI_MEMDEV_Handle DataViewPainter_Memdev_Handler;




unsigned char DataViewPainter_IsColorBar_ON=1;


void DataViewPainter_Set_MeasureMax(int value)
{
	
	DataViewPainter_Measure_Max=value;
	
}


 void DataViewPainter_Create_Memdev()
{

	//GUI_SelectLayer(1);
	DataViewPainter_Memdev_Handler = GUI_MEMDEV_Create(10, 10, DataViewPainter_Width , DataViewPainter_Heigth);
	
	
	//DataViewPainter_Memdev_Handler = GUI_MEMDEV_CreateEx(0, 0, DataViewPainter_Width , DataViewPainter_Heigth,GUI_MEMDEV_HASTRANS);
}

void DataViewPainter_Set_DeepData_Str(TEXT_Handle tHandler,int value)
{
	char deepStr[10]="88.8";
	float result=(float)value/100;
	
	 sprintf("%s\n", float2str((float)result, 2, deepStr));
	 
	 
	 
	 TEXT_SetText(tHandler,deepStr);
	
}


static void	DataViewPainter_Draw_Column(Data_Node_T * DataNode_Pt,int colNum)
{
	Data_Node_T * dNode_Pt=DataNode_Pt;
	int dot_longer=(40/MainMenu_Setup_Measure_Range<1)?1:40/MainMenu_Setup_Measure_Range;
	
	
	while(dNode_Pt->ColorID!=NULL_NOD)
	{
		DataViewPainter_Draw_Node(colNum,dNode_Pt->Depth*(ViewA_Heigth-10)/MainMenu_Setup_Measure_Range/100,dNode_Pt->ColorID,dot_longer-1);
		dNode_Pt++;
	}
		
}

static void	DataViewPainter_Draw_Node(int x, int y,int colorId,int dot_heigth)
{
	int distance=0;

	if(ViewB_In_Two==0)
		distance=DataViewPainter_Horizontal_DataLine_Stop-199*DataViewPainter_Horizontal_Step;
	else
		distance=DataViewPainter_Horizontal_DataLine_Stop-199*DataViewPainter_Horizontal_Step*2;
	GUI_SetColor(ECHO_Data_Color[colorId-1]);
	
	//GUI_SetColor(GUI_WHITE);
	if (((x-1)*DataViewPainter_Horizontal_Step+distance-5)>=5)
		
	GUI_FillRect((x-1)*DataViewPainter_Horizontal_Step+distance-5,y+5,x*DataViewPainter_Horizontal_Step+distance-5,y+dot_heigth+5);
	//GUI_Exec();
	
	
}

void	DataViewPainter_Draw_ColorBar(void)
{
	GUI_SetColor(ECHO_Data_Color[0]);
	GUI_FillRect(10,350,35+10,350+25);
	 
    //painter.fillRect(QRect(0,325,35,25), QBrush(QColor(255,0,0)));
	GUI_SetColor(ECHO_Data_Color[1]);
	GUI_FillRect(10,325,35+10,325+25);
	
    //painter.fillRect(QRect(0,300,35,25), QBrush(QColor(253,152,0)));
	GUI_SetColor(ECHO_Data_Color[2]);
	GUI_FillRect(10,300,35+10,300+25);
	
	
    //painter.fillRect(QRect(0,275,35,25), QBrush(QColor(255,255,0)));
	GUI_SetColor(ECHO_Data_Color[3]);
	GUI_FillRect(10,275,35+10,275+25);
	
    //painter.fillRect(QRect(0,250,35,25), QBrush(QColor(0,255,0)));
	GUI_SetColor(ECHO_Data_Color[4]);
	GUI_FillRect(10,250,35+10,25+250);
	
    //painter.fillRect(QRect(0,225,35,25), QBrush(QColor(0,204,255)));
	GUI_SetColor(ECHO_Data_Color[5]);
	GUI_FillRect(10,225,35+10,225+25);
	
	
    //painter.fillRect(QRect(0,200,35,25), QBrush(QColor(51,102,255)));
	GUI_SetColor(ECHO_Data_Color[6]);
	GUI_FillRect(10,200,35+10,200+25);
}

static void	DataViewPainter_Draw_TimeLine(void)
{
	
}





void DataViewPainter_Select_Memory(void)
{
	GUI_MEMDEV_Select(DataViewPainter_Memdev_Handler);
}

void DataViewPainter_Select_LCD(void)
{
	
	GUI_MEMDEV_Select(0);
	
	
}

void DataViewPainter_Copyto_LCD(void)
{
	//GUI_MEMDEV_CopyToLCD(DataViewPainter_Memdev_Handler);
	
	GUI_MEMDEV_CopyToLCDAt(DataViewPainter_Memdev_Handler,15,15);
}


	


void	DataViewPainter_Draw_Frame(WM_HWIN TargetWin,Buffer_Frame_T * DataFrame_Pt,int channelMode)
{
	int i;
	
	
	int CurrentIndex;
	
	int TailIndex;
	
	
	
	if(TargetWin==ViewA_Get_Handler())
	{

		if (channelMode==3)    //ViewA call but two view shine,ViewA horizontal_end to 400-10
		{
			DataViewPainter_Horizontal_DataLine_Start=10;
			DataViewPainter_Horizontal_DataLine_Stop=400-10;
			
			DataViewPainter_Horizontal_Step=2;
			ViewB_In_Two=0;
		}
		else if  (channelMode==1)  //only ViewA
		{
			DataViewPainter_Horizontal_DataLine_Start=10;
			DataViewPainter_Horizontal_DataLine_Stop=800-10;
			
			DataViewPainter_Horizontal_Step=4;
			ViewB_In_Two=0;
			
		}
	}
	else if(TargetWin==ViewB_Get_Handler())
	{
		if (channelMode==3)             // ViewB and two view shine
		{
			DataViewPainter_Horizontal_DataLine_Start=410;
			DataViewPainter_Horizontal_DataLine_Stop=800-10;
			
			DataViewPainter_Horizontal_Step=2;

			ViewB_In_Two=1;
		}
		else if(channelMode==2)         //only viewB
		{

			DataViewPainter_Horizontal_DataLine_Start=10;
			DataViewPainter_Horizontal_DataLine_Stop=800-10;
			
			DataViewPainter_Horizontal_Step=4;
			
			ViewB_In_Two=0;
		}
		
		
		
	}
	
	
	
	
	
	CurrentIndex=DeepDataBuffer_Frame.DeepDataBuffer_Start_Column_Pt;
	
	TailIndex=DeepDataBuffer_Frame.DeepDataBuffer_End_Column_Pt;
	
	
	if(DeepDataBuffer_IsEmpty()!=0)
		return;

	
	for(i=0;i<Max_Frame_Num ;i++)
	{
		DataViewPainter_Draw_Column(DeepDataBuffer_Frame.DeepDataBuffer_FrameArray[CurrentIndex],Max_Frame_Num-i-1);
		
		CurrentIndex=(CurrentIndex>=1)?(CurrentIndex-1):(Max_Frame_Num-1);
		
	}
	
	//GUI_Delay(1);
	
	
}

void DataViewPainter_Draw_Frame_on_Mem(Buffer_Frame_T * DataFrame_Pt)
{
	
	
	DataViewPainter_Select_Memory();
	
	if(DataViewPainter_Memdev_Handler!=0)
	{
	
		GUI_MEMDEV_Clear(DataViewPainter_Memdev_Handler);
	
		//DataViewPainter_Draw_Frame(DataFrame_Pt);
	}
	

	
	
}


void DataViewPainter_Reflash_From_Mem()
{
	if (DataViewPainter_Memdev_Handler!=0)
	
		GUI_MEMDEV_WriteAt(DataViewPainter_Memdev_Handler, 10, 10);
		
		
	DataViewPainter_Select_LCD();
	
}

void DataViewPainter_Draw_Scale(WM_HWIN TargetWin,int channelMode)
{
    int low_measure_cross=0;
    int high_measure_cross=DataViewPainter_Measure_Max;
    int vertical_start_y=5;
    int vertical_end_y=ViewA_Heigth-5;//695;
    int horizon_start1_cross=ViewA_Width-15;//585;
    int horizon_start2_cross=ViewA_Width-35;//570;
    int horizon_end_cross=ViewA_Width-5;//600;
    int vertical_step=(vertical_end_y-vertical_start_y);
	
	int count;
	

	
	if(TargetWin==ViewA_Get_Handler())
	{

		if (channelMode==3)
		{
			horizon_start1_cross=ViewA_Width/2-20;//585;
			horizon_start2_cross=ViewA_Width/2-40;//570
			horizon_end_cross=ViewA_Width/2-8;
		}
		else if  (channelMode==1)
		{

			horizon_start1_cross=ViewA_Width-15;//585;
			horizon_start2_cross=ViewA_Width-35;//570
			horizon_end_cross=ViewA_Width-5;
		}
	}
	else if(TargetWin==ViewB_Get_Handler())
	{
		if (channelMode==3)
		{
			horizon_start1_cross=ViewB_Width/2-20;//585;
			horizon_start2_cross=ViewB_Width/2-40;//570
			horizon_end_cross=ViewB_Width/2-8;
		}
		else if(channelMode==2)
		{

			horizon_start1_cross=ViewB_Width-15;//585;
			horizon_start2_cross=ViewB_Width-35;//570
			horizon_end_cross=ViewB_Width-5;
		}
		
		
		
	}
   



	GUI_SetColor(GUI_WHITE);
	GUI_SetPenSize(2);

	GUI_DrawLine(horizon_end_cross,vertical_start_y,horizon_end_cross,vertical_end_y);





    for(count=0;count<=10;count++)
    {
		


           int   label_pos_x;
           int   label_pos_y;
			
			

           //font.setPointSize(15);

           //font.setLetterSpacing(QFont::AbsoluteSpacing,0);
           //painter.setFont(font);

		GUI_SetFont(ViewA_Scale_Font);
        //QString cross_label= tr("%1").arg(low_measure_cross+(high_measure_cross-low_measure_cross)*count/10);
		
		
        if((count%2)!=0)
			GUI_DrawLine(horizon_start1_cross,vertical_start_y+count*vertical_step/10,horizon_end_cross,vertical_start_y+count*vertical_step/10);
            //painter.drawLine(QPoint(horizon_start1_cross,vertical_start_y+count*vertical_step/10),QPoint(horizon_end_cross,vertical_start_y+count*vertical_step/10));

        else
        {

            if (count==0)
            {
                label_pos_x=horizon_start2_cross;
                label_pos_y=vertical_start_y+count*vertical_step/10+5;
            }
            else if(count==10)
            {
                //label_pos_x=horizon_start2_cross-40;
                //label_pos_y=vertical_start_y+count*vertical_step;
                label_pos_x=horizon_start2_cross;
                label_pos_y=vertical_start_y+count*vertical_step/10-18;
            }
            else
            {
                //label_pos_x=horizon_start2_cross-40;
                //label_pos_y=vertical_start_y+count*vertical_step+15;
                label_pos_x=horizon_start2_cross;
                label_pos_y=vertical_start_y+count*vertical_step/10-18;
            }

            if((low_measure_cross+(high_measure_cross-low_measure_cross)*count/10)<10)
            {

                label_pos_x=label_pos_x+20;
				
				GUI_DispDecAt(low_measure_cross+(high_measure_cross-low_measure_cross)*count/10,label_pos_x,label_pos_y,1);
            }
            else if ((low_measure_cross+(high_measure_cross-low_measure_cross)*count/10)<100)
            {
                 label_pos_x=label_pos_x+10;
				 
				 GUI_DispDecAt(low_measure_cross+(high_measure_cross-low_measure_cross)*count/10,label_pos_x,label_pos_y,2);
            }
            else
            {

                //label_pos_x=label_pos_x+5;
				GUI_DispDecAt(low_measure_cross+(high_measure_cross-low_measure_cross)*count/10,label_pos_x,label_pos_y,3);
            }

            //painter.drawLine(QPoint(horizon_start2_cross+5,vertical_start_y+count*vertical_step/10),QPoint(horizon_end_cross,vertical_start_y+count*vertical_step/10));
			GUI_DrawLine(horizon_start2_cross,vertical_start_y+count*vertical_step/10,horizon_end_cross,vertical_start_y+count*vertical_step/10);

           
			

            //painter.drawText(label_pos_x,label_pos_y,cross_label);
			
			//GUI_DispDecAt(low_measure_cross+(high_measure_cross-low_measure_cross)*count/10,label_pos_x,label_pos_y,3);
        }
    }

	//WM_SelectWindow(hWinOld);
    //  qDebug()<<this->height();
    //  qDebug()<<this->width();

	//GUI_Exec();

}

static char * float2str(float val, int precision, char *buf)
{
    char *cur, *end;
    
    sprintf(buf, "%.2f", val);
    if (precision < 6) {
        cur = buf + strlen(buf) - 1;
        end = cur - 6 + precision; 
        while ((cur > end) && (*cur == '0')) {
            *cur = '\0';
            cur--;
        }
    }
    
    return buf;
}
