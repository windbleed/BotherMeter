/****************************************************************
*   	 	Data Resolver  class
*   This object is for Resolve data  from usart Resolver to
		 Deep data buffer data structure.
*
*	Field:
			DataResolver_UartResolver_Handler
			DataResolver_Column_Data[500]
			DataResolver_Valid_Num
			
			
			
	Method:		
			DataResolver_Get_Package_From_Usart
			
			
			
*						Made by Softwind 2019/5/14
*
*
****************************************************************/
#include "DataResolver.h"

static Data_Node_T  	DataResolver_Column_Data[Max_Column_Num];

static Para_TRXB     	DataResolver_Para_Rx;


static int 				DataResolver_Measure_Range=0;

static int 				DataResolver_Columm_Count=0;


static int				DataResolver_Depth=0;

int DataResolver_Get_DeepData(void)
{
	
	return (DataResolver_Depth);
}



int DataResolver_Get_ColumnNum(void)
{
	
	return (DataResolver_Columm_Count);
}



Data_Node_T * DataResolver_Get_Package_From_Usart(unsigned char * Uart_RX_Buffer,int length)
{
	
	
	int i;

	int dolas_count=0;
	int star_count=0;
	int Sync_Loc=0;
	int Checksum_Loc=0;
	int End_Loc=0;
	int ValueM_Loc=0;
	int ValueN_Loc=0;
	int ImgData_Loc=0;
	int Comma_Count=0;
	int MeasureRange_Loc;
	int CurrentChannel_Loc;
	int ColorID_Loc=0;




	unsigned char Sync_found=0x00;
	unsigned char End_found=0x00;
	unsigned char Checksum_in_buf=0x00;
	
	
	

    int M=0;
    int N=0;

	    
    
    int ValueM_Length;
    int ValueN_Length;
    
	
	unsigned char  CheckSum=0x00;
	
	
	for(i=0;i<length;i++)
    {


        //获取同步信息 接收算法1

        if (Uart_RX_Buffer[i]=='$')
        {
            dolas_count++;
            if (dolas_count==1)
            {
                Sync_Loc=i;
                Sync_found=0x01;
            }
        }
        if (Uart_RX_Buffer[i]=='*')
        {
            star_count++;
            if (star_count==1)
            {
                End_Loc=i;
                End_found=0x01;
                Checksum_Loc=End_Loc+1;
            }
        }

        /*
        //获取同步信息 接收算法2

        if (Uart_RX_Buffer[i]=='$')
        {
            dolas_count++;
            if (dolas_count==2)
            {
                Sync_Loc=i;
                Sync_found=true;
            }
        }
        if (Uart_RX_Buffer[i]=='*')
        {
            star_count++;
            if (star_count==2)
            {
                End_Loc=i;
                End_found=true;
                Checksum_Loc=End_Loc+1;
            }
        }

        */

    }
    if((Sync_found==0x00)||(End_found=0x00))
        
	return 0x00;
   

    Checksum_in_buf=(Uart_RX_Buffer[Checksum_Loc]-'0')*16+(Uart_RX_Buffer[Checksum_Loc+1]-'0');



    //根据接收数据包取得帧特征值

    for(i=(Sync_Loc+2);i<End_Loc;i++)
    {
        if(Uart_RX_Buffer[i]==',')
        {
            Comma_Count++;

            switch(Comma_Count)
            {
                case 1:
                {
                    DataResolver_Para_Rx.Gain_For_Chan1=Uart_RX_Buffer[i+1];

                }
                break;
                case 2:
                {
                    DataResolver_Para_Rx.Gain_For_Chan2=Uart_RX_Buffer[i+1];
                }
                break;
                case 3:
                {
                    DataResolver_Para_Rx.Tvg_For_Chan1=Uart_RX_Buffer[i+1];
                }
                break;
                case 4:
                {
                    DataResolver_Para_Rx.Tvg_For_Chan2=Uart_RX_Buffer[i+1];

                }
                break;
                case 5:
                {
                    DataResolver_Para_Rx.Pulse_Width=Uart_RX_Buffer[i+1];

                }
                break;
                case 6:
                {
                    MeasureRange_Loc=i+1;
                    DataResolver_Para_Rx.Measure_Range=Uart_RX_Buffer[i+1];
                }
                break;
                case 7:
                {
                    DataResolver_Para_Rx.Channel_Sel=Uart_RX_Buffer[i+1];
                }
                break;
                case 8:
                {
                     DataResolver_Para_Rx.Tx_Power=Uart_RX_Buffer[i+1];

                }
                 break;
                case 9:
                {
                    DataResolver_Para_Rx.Trace_Mode=Uart_RX_Buffer[i+1];
                }
                break;
                case 10:
                {
                    ColorID_Loc=i+1;
                    DataResolver_Para_Rx.Num_ColorBar=Uart_RX_Buffer[i+1];

                }
                break;
                case 11:
                {
                    DataResolver_Para_Rx.Dynamic_Range=Uart_RX_Buffer[i+1];
                }
                break;
                case 12:
                {
                    CurrentChannel_Loc=i+1;
                    DataResolver_Para_Rx.Data_Channel=Uart_RX_Buffer[i+1];
                }
                break;
                case 13:
                {
                    ValueM_Loc=i+1;

                }
                break;
                case 14:
                {
                    ValueN_Loc=i+1;
                    ValueM_Length=ValueN_Loc-ValueM_Loc-1;



                }
                break;
                case 15:
                {
                    ImgData_Loc=i+1;
                    ValueN_Length=ImgData_Loc-ValueN_Loc-1;

                }
            break;

             }
        }



        CheckSum=CheckSum^Uart_RX_Buffer[i];


    }

    switch(DataResolver_Para_Rx.Measure_Range)
    {
        case 'A':DataResolver_Measure_Range=5;break;
        case 'B':DataResolver_Measure_Range=10;break;
        case 'C':DataResolver_Measure_Range=20;break;
        case 'D':DataResolver_Measure_Range=40;break;
        case 'E':DataResolver_Measure_Range=100;break;
        case 'F':DataResolver_Measure_Range=200;break;
        case 'G':DataResolver_Measure_Range=400;break;
        case 'H':DataResolver_Measure_Range=800;break;

    }

  
   
    //取得深度数据，时间戳、深度、色块值（回波强度）

	DataResolver_Columm_Count=0;

    for(i=ImgData_Loc;i<End_Loc;i++)
    {
        if(Uart_RX_Buffer[i]!='0')
        {



            DataResolver_Column_Data[DataResolver_Columm_Count].Depth=(i-ImgData_Loc)*DataResolver_Measure_Range/5;          //深度单位为厘米

            DataResolver_Column_Data[DataResolver_Columm_Count].ColorID=Uart_RX_Buffer[i]-'0';

            DataResolver_Columm_Count++;


        }
    }

	 DataResolver_Column_Data[DataResolver_Columm_Count].ColorID=NULL_NOD;




    //计算测量深度

    M=Uart_RX_Buffer[ValueM_Loc];


    N=Uart_RX_Buffer[ValueN_Loc];

    DataResolver_Depth=M*256+N;
	
	if (DataResolver_Columm_Count==0)
		
		return 0x00;
	else
		return DataResolver_Column_Data;




	
}