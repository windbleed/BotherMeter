#include "SystemCFG.h"

static SysCFG_T    SysCFG_System_Configurateion;

static CCSDQ_Frame_T 	SysCFG_CCSDQ_Frame;

static char *			SysCFG_File_Name="SysCFG.ini";


static char * SysCFG_CCSDQ="$CCSDQ,L,L,D,D,D,D,A,D,C,C,A,A*43\n\r";



void SysCFG_Init(void)
{

	SysCFG_System_Configurateion.EchoboardConfig.GainA=12;
	SysCFG_System_Configurateion.EchoboardConfig.GainB=12;
	SysCFG_System_Configurateion.EchoboardConfig.TVGA=4;
	SysCFG_System_Configurateion.EchoboardConfig.TVGB=4;
	SysCFG_System_Configurateion.EchoboardConfig.PulseWidth=3;

	SysCFG_System_Configurateion.EchoboardConfig.MeasureRange=2;
	SysCFG_System_Configurateion.EchoboardConfig.Channel=3;
	SysCFG_System_Configurateion.EchoboardConfig.TxPwr=3;
	SysCFG_System_Configurateion.EchoboardConfig.Mode=2;

	SysCFG_System_Configurateion.EchoboardConfig.ColorBarNum=5;
	SysCFG_System_Configurateion.EchoboardConfig.DynamicRange=3;

	SysCFG_System_Configurateion.EchoboardConfig.CurrentChannel=1;

	SysCFG_System_Configurateion.Setting_Time.Hour=14;
	SysCFG_System_Configurateion.Setting_Time.Min=30;
	SysCFG_System_Configurateion.Setting_Time.Sec=18;

	SysCFG_System_Configurateion.Setting_Date.Year=2019;
	SysCFG_System_Configurateion.Setting_Date.Month=6;
	SysCFG_System_Configurateion.Setting_Date.Day=6;

	SysCFG_System_Configurateion.FrameRate=1;

	SysCFG_System_Configurateion.TBS=0;
	SysCFG_System_Configurateion.KH=0;

	SysCFG_System_Configurateion.Loc_SensorA=0;
	SysCFG_System_Configurateion.Loc_SensorB=2;

	SysCFG_System_Configurateion.Language=0;
	SysCFG_System_Configurateion.Store_Interval=60;

	SysCFG_System_Configurateion.HistoryReviewMode=3;

	SysCFG_System_Configurateion.Warn_Lack_Voltage=22;

	SysCFG_System_Configurateion.Warn_Low_Deep_Water=5;
	SysCFG_System_Configurateion.Warn_High_Deep_Water=100;



}



static void SysCFG_Cal_CCSDQ_CheckSum(void)
{
	unsigned char tmp=0x00;
	unsigned char count=0;

	for(count=1;count<30;count++)
	{
		tmp=tmp^SysCFG_CCSDQ[count];
	}
	
	SysCFG_CCSDQ[31]=((tmp/16)<10)?(tmp/16+'0'):(tmp/16-10+'A');
	SysCFG_CCSDQ[32]=((tmp%16)<10)?(tmp%16+'0'):(tmp%16-10+'A');


	
};

char * SysCFG_Create_CCSDQ(int sensorMode)
{
	SysCFG_CCSDQ_Frame.GainA='A'+SysCFG_System_Configurateion.EchoboardConfig.GainA-1;
	SysCFG_CCSDQ_Frame.GainB='A'+SysCFG_System_Configurateion.EchoboardConfig.GainB-1;
	SysCFG_CCSDQ_Frame.TVGA='A'+SysCFG_System_Configurateion.EchoboardConfig.TVGA-1;
	SysCFG_CCSDQ_Frame.TVGB='A'+SysCFG_System_Configurateion.EchoboardConfig.TVGB-1;
	SysCFG_CCSDQ_Frame.PulseWidth='A'+SysCFG_System_Configurateion.EchoboardConfig.PulseWidth;

	switch(SysCFG_System_Configurateion.EchoboardConfig.MeasureRange)
	{
		case 5:
			SysCFG_CCSDQ_Frame.MeasureRange='A';
		break;
		case 10:
			SysCFG_CCSDQ_Frame.MeasureRange='B';
		break;
		case 20:
			SysCFG_CCSDQ_Frame.MeasureRange='C';
		break;
		case 40:
			SysCFG_CCSDQ_Frame.MeasureRange='D';
		break;
		case 100:
			SysCFG_CCSDQ_Frame.MeasureRange='E';
		break;
		case 200:
			SysCFG_CCSDQ_Frame.MeasureRange='F';
		break;
		case 400:
			SysCFG_CCSDQ_Frame.MeasureRange='G';
		break;
		case 800:
			SysCFG_CCSDQ_Frame.MeasureRange='H';
		break;
	}

	SysCFG_CCSDQ_Frame.Channel='A'+SysCFG_System_Configurateion.EchoboardConfig.Channel-1;
	SysCFG_CCSDQ_Frame.TXPwr='A'+SysCFG_System_Configurateion.EchoboardConfig.TxPwr;
	SysCFG_CCSDQ_Frame.Mode='A'+SysCFG_System_Configurateion.EchoboardConfig.Mode-1;
	SysCFG_CCSDQ_Frame.ColorBarNum='A'+SysCFG_System_Configurateion.EchoboardConfig.ColorBarNum-3;
	SysCFG_CCSDQ_Frame.DynamicRange='A'+SysCFG_System_Configurateion.EchoboardConfig.DynamicRange-3;
	SysCFG_CCSDQ_Frame.CurrentChannel='A'+SysCFG_System_Configurateion.EchoboardConfig.CurrentChannel-1;


	SysCFG_Fill_CCSDQ_Array();

	SysCFG_Cal_CCSDQ_CheckSum();

	return SysCFG_CCSDQ;
	
};

static void SysCFG_Fill_CCSDQ_Array(void)
{

	SysCFG_CCSDQ[7]=SysCFG_CCSDQ_Frame.GainA;
	SysCFG_CCSDQ[9]=SysCFG_CCSDQ_Frame.GainB;

	SysCFG_CCSDQ[11]=SysCFG_CCSDQ_Frame.TVGA;
	SysCFG_CCSDQ[13]=SysCFG_CCSDQ_Frame.TVGB;

	SysCFG_CCSDQ[15]=SysCFG_CCSDQ_Frame.PulseWidth;
	SysCFG_CCSDQ[17]=SysCFG_CCSDQ_Frame.MeasureRange;

	SysCFG_CCSDQ[19]=SysCFG_CCSDQ_Frame.Channel;

	SysCFG_CCSDQ[21]=SysCFG_CCSDQ_Frame.TXPwr;
	SysCFG_CCSDQ[23]=SysCFG_CCSDQ_Frame.Mode;

	SysCFG_CCSDQ[25]=SysCFG_CCSDQ_Frame.ColorBarNum;
	SysCFG_CCSDQ[27]=SysCFG_CCSDQ_Frame.DynamicRange;

	SysCFG_CCSDQ[29]=SysCFG_CCSDQ_Frame.CurrentChannel;



}



int  SysCFG_Get_SysCFG(int ItemIndex)
{

	switch(ItemIndex)
	{
	case SysCFG_Item_GainA_Index:

		return (SysCFG_System_Configurateion.EchoboardConfig.GainA);


	case SysCFG_Item_GainB_Index:

		return (SysCFG_System_Configurateion.EchoboardConfig.GainB);



	case SysCFG_Item_TVGA_Index:

		return (SysCFG_System_Configurateion.EchoboardConfig.TVGA);



	case SysCFG_Item_TVGB_Index:

		return(SysCFG_System_Configurateion.EchoboardConfig.TVGB);



	case SysCFG_Item_PulseWidth_Index:

		return(SysCFG_System_Configurateion.EchoboardConfig.PulseWidth);



	case SysCFG_Item_MeasureRange_Index:

		return(SysCFG_System_Configurateion.EchoboardConfig.MeasureRange);



	case SysCFG_Item_Channel_Index:

		return(SysCFG_System_Configurateion.EchoboardConfig.Channel);



	case SysCFG_Item_TxPwr_Index:

		return(SysCFG_System_Configurateion.EchoboardConfig.TxPwr);


	case SysCFG_Item_Mode_Index:

		return(SysCFG_System_Configurateion.EchoboardConfig.Mode);


	case SysCFG_Item_ColorNum_Index:

		return(SysCFG_System_Configurateion.EchoboardConfig.ColorBarNum);


	case SysCFG_Item_DynamicRange_Index:

		return(SysCFG_System_Configurateion.EchoboardConfig.DynamicRange);



	case SysCFG_Item_CurrentChannel_Index:

		return(SysCFG_System_Configurateion.EchoboardConfig.CurrentChannel);



	case SysCFG_Item_Hour_Index:

		return(SysCFG_System_Configurateion.Setting_Time.Hour);



	case SysCFG_Item_Min_Index:

		return(SysCFG_System_Configurateion.Setting_Time.Min);



	case SysCFG_Item_Sec_Index:

		return(SysCFG_System_Configurateion.Setting_Time.Sec);




	case SysCFG_Item_Year_Index:

		return(SysCFG_System_Configurateion.Setting_Date.Year);



	case SysCFG_Item_Month_Index:

		return(SysCFG_System_Configurateion.Setting_Date.Month);



	case SysCFG_Item_Day_Index:

		return(SysCFG_System_Configurateion.Setting_Date.Day);



	case SysCFG_Item_FrameRate_Index:

		return(SysCFG_System_Configurateion.FrameRate);



	case SysCFG_Item_TBS_Index:

		return(SysCFG_System_Configurateion.TBS);



	case SysCFG_Item_KH_Index:

		return(SysCFG_System_Configurateion.KH);



	case SysCFG_Item_DepthRef_Index:

		return(SysCFG_System_Configurateion.DepthRef);



	case SysCFG_Item_LocSensorA_Index:

		return(SysCFG_System_Configurateion.Loc_SensorA);



	case SysCFG_Item_LocSensorB_Index:

		return(SysCFG_System_Configurateion.Loc_SensorB);


	case SysCFG_Item_Language_Index:

		return(SysCFG_System_Configurateion.Language);



	case SysCFG_Item_StoreInterval_Index:

		return(SysCFG_System_Configurateion.Store_Interval);



	case SysCFG_Item_HistoryReview_Index:

		return(SysCFG_System_Configurateion.HistoryReviewMode);



	case SysCFG_Item_VolLimit_Index:

		return(SysCFG_System_Configurateion.Warn_Lack_Voltage);



	case SysCFG_Item_LowWater_Index:

		return(SysCFG_System_Configurateion.Warn_Low_Deep_Water);



	case SysCFG_Item_HighWater_Index:

		return(SysCFG_System_Configurateion.Warn_High_Deep_Water);





	default:

		break;



	}

	return 0;
};
void SysCFG_Set_SysCFG(int ItemIndex, int value)
{

	switch(ItemIndex)
	{
		case SysCFG_Item_GainA_Index:

			SysCFG_System_Configurateion.EchoboardConfig.GainA=value;

		break;

		case SysCFG_Item_GainB_Index:

			SysCFG_System_Configurateion.EchoboardConfig.GainB=value;

		break;

		case SysCFG_Item_TVGA_Index:

			SysCFG_System_Configurateion.EchoboardConfig.TVGA=value;

		break;

		case SysCFG_Item_TVGB_Index:

			SysCFG_System_Configurateion.EchoboardConfig.TVGB=value;

		break;

		case SysCFG_Item_PulseWidth_Index:

			SysCFG_System_Configurateion.EchoboardConfig.PulseWidth=value;

		break;

		case SysCFG_Item_MeasureRange_Index:

			SysCFG_System_Configurateion.EchoboardConfig.MeasureRange=value;

		break;

		case SysCFG_Item_Channel_Index:

			SysCFG_System_Configurateion.EchoboardConfig.Channel=value;

		break;

		case SysCFG_Item_TxPwr_Index:

			SysCFG_System_Configurateion.EchoboardConfig.TxPwr=value;

		break;

		case SysCFG_Item_Mode_Index:

			SysCFG_System_Configurateion.EchoboardConfig.Mode=value;

		break;

		case SysCFG_Item_ColorNum_Index:

			SysCFG_System_Configurateion.EchoboardConfig.ColorBarNum=value;

		break;

		case SysCFG_Item_DynamicRange_Index:

			SysCFG_System_Configurateion.EchoboardConfig.DynamicRange=value;

		break;

		case SysCFG_Item_CurrentChannel_Index:

			SysCFG_System_Configurateion.EchoboardConfig.CurrentChannel=value;

		break;

		case SysCFG_Item_Hour_Index:

			SysCFG_System_Configurateion.Setting_Time.Hour=value;

		break;

		case SysCFG_Item_Min_Index:

			SysCFG_System_Configurateion.Setting_Time.Min=value;

		break;

		case SysCFG_Item_Sec_Index:

			SysCFG_System_Configurateion.Setting_Time.Sec=value;

		break;


		case SysCFG_Item_Year_Index:

			SysCFG_System_Configurateion.Setting_Date.Year=value;

		break;

		case SysCFG_Item_Month_Index:

			SysCFG_System_Configurateion.Setting_Date.Month=value;

		break;

		case SysCFG_Item_Day_Index:

			SysCFG_System_Configurateion.Setting_Date.Day=value;

		break;

		case SysCFG_Item_FrameRate_Index:

			SysCFG_System_Configurateion.FrameRate=value;

		break;

		case SysCFG_Item_TBS_Index:

			SysCFG_System_Configurateion.TBS=value;

		break;

		case SysCFG_Item_KH_Index:

			SysCFG_System_Configurateion.KH=value;

		break;

		case SysCFG_Item_DepthRef_Index:

			SysCFG_System_Configurateion.DepthRef=value;

		break;

		case SysCFG_Item_LocSensorA_Index:

			SysCFG_System_Configurateion.Loc_SensorA=value;

		break;

		case SysCFG_Item_LocSensorB_Index:

			SysCFG_System_Configurateion.Loc_SensorB=value;

		break;
		case SysCFG_Item_Language_Index:

			SysCFG_System_Configurateion.Language=value;

		break;

		case SysCFG_Item_StoreInterval_Index:

			SysCFG_System_Configurateion.Store_Interval=value;

		break;

		case SysCFG_Item_HistoryReview_Index:

			SysCFG_System_Configurateion.HistoryReviewMode=value;

		break;

		case SysCFG_Item_VolLimit_Index:

			SysCFG_System_Configurateion.Warn_Lack_Voltage=value;

		break;

		case SysCFG_Item_LowWater_Index:

			SysCFG_System_Configurateion.Warn_Low_Deep_Water=value;

		break;

		case SysCFG_Item_HighWater_Index:

			SysCFG_System_Configurateion.Warn_High_Deep_Water=value;

		break;







	}

};

void SysCFG_SaveToFile(void)
{

};

void SysCFG_GetFromFile(void)
{

};
