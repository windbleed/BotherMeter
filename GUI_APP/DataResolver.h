#ifndef DataResolver_Unit
#define DataResolver_Unit

#include "DeepDataBuffer.h"

typedef struct Para_TRXBoard
{
    unsigned char Gain_For_Chan1;
    unsigned char Gain_For_Chan2;
    unsigned char Tvg_For_Chan1;
    unsigned char Tvg_For_Chan2;
    unsigned char Pulse_Width;
    unsigned char Measure_Range;
    unsigned char Channel_Sel;
    unsigned char Tx_Power;
    unsigned char Trace_Mode;
    unsigned char Num_ColorBar;
    unsigned char Dynamic_Range;
    unsigned char Data_Channel;



}Para_TRXB;


extern Data_Node_T * DataResolver_Get_Package_From_Usart(unsigned char * Uart_RX_Buffer,int length);
extern int DataResolver_Get_DeepData(void);
extern int DataResolver_Get_ColumnNum(void);

#endif
