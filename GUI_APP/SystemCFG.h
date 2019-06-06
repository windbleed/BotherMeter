/*********************************************************************

This Unit include System parameter class.

it define th system parameter data sturcture, including echoboard 

character in it.

support saveing to file and read from file

also it support the CCSDQ Frame creation for both channel A and B.


				Made by softwind 
				20190603

*************************************************************************/ 
#ifndef SysCFG_Unit
#define SysCFG_Unit


#define SysCFG_Item_GainA_Index 		0
#define SysCFG_Item_GainB_Index 		1
#define SysCFG_Item_TVGA_Index 			2
#define SysCFG_Item_TVGB_Index 			3
#define SysCFG_Item_PulseWidth_Index 	4
#define SysCFG_Item_MeasureRange_Index 	5
#define SysCFG_Item_Channel_Index 		6
#define SysCFG_Item_TxPwr_Index 		7
#define SysCFG_Item_Mode_Index 			8
#define SysCFG_Item_ColorNum_Index 		9
#define SysCFG_Item_DynamicRange_Index 	10
#define SysCFG_Item_CurrentChannel_Index 	11


#define SysCFG_Item_Hour_Index 			12
#define SysCFG_Item_Min_Index 			13
#define SysCFG_Item_Sec_Index 			14


#define SysCFG_Item_Year_Index 			15
#define SysCFG_Item_Month_Index 		16
#define SysCFG_Item_Day_Index 			17

#define SysCFG_Item_FrameRate_Index 	20
#define SysCFG_Item_TBS_Index 			21
#define SysCFG_Item_KH_Index 			22
#define SysCFG_Item_DepthRef_Index 		23
#define SysCFG_Item_LocSensorA_Index 	24
#define SysCFG_Item_LocSensorB_Index 	25


#define SysCFG_Item_Language_Index 		26
#define SysCFG_Item_StoreInterval_Index 27
#define SysCFG_Item_HistoryReview_Index	28
#define SysCFG_Item_VolLimit_Index 		29
#define SysCFG_Item_LowWater_Index 		30
#define SysCFG_Item_HighWater_Index 	31



typedef struct TimeStamp
{
    unsigned char 	Hour;
    unsigned char 	Min;
	unsigned char   Sec;

}Time_Stamp_T;


typedef struct DateStamp
{
    int 	Year;
    unsigned char 	Month;
	unsigned char   Day;

}Date_Stamp_T;


typedef struct ebCFG
{
    unsigned char 	GainA;				//1~30
    unsigned char 	GainB;				//1~30
	unsigned char   TVGA;				//1~30
	unsigned char 	TVGB;				//1~30
	unsigned char   PulseWidth;			//0~3  0:Low 1:Mid 2:High 3:Auto
	int   			MeasureRange;		//5/10/20/40/100/200/400/800
	unsigned char   Channel;			//1~3 1:A 2:B 3:A&B
	unsigned char   TxPwr;				//0~3  0:low 1: Mid 2:High	3:Auto
	unsigned char   Mode;				//0~2  0:Auto-1 1:Auto-2  2:Manual
	unsigned char   ColorBarNum;		//3~7
	unsigned char  	DynamicRange;		//3~6
	unsigned char   CurrentChannel;		//1~2


}EBCFG_T;

typedef struct SysCFG_Unit
{

	EBCFG_T    		EchoboardConfig;
	Time_Stamp_T    Setting_Time;
	Date_Stamp_T	Setting_Date;
	int        		FrameRate;
	int        		TBS;					//Transducer Below WATER Surface Unit mm
	int				KH;					    //Heigh of Vessel Keel Unit cm= 0.01m
	unsigned char   DepthRef;				//0: Water Surface 1: Transducer 2:Keel
	unsigned char 	Loc_SensorA;			//0: fore 1:Mid	2:Back
	unsigned char   Loc_SensorB;			//0: fore 1:Mid	2:Back
	unsigned char 	Language;				//0:Chinese	1:English
	unsigned char 	Store_Interval;			//0: close |1sec|5sec|30sec|60sec
	unsigned char   HistoryReviewMode;		//0: forward 1: backward 2: play on the according direction 3:None
	int           Warn_Lack_Voltage;		//Warn trigger belwo 22.0V unit  0.1V
	int           Warn_Low_Deep_Water;		//Warn trigger:warter deep below  this unit cm=0.01m
	int           Warn_High_Deep_Water;		//Warn trigger: water deep above  this unit cm=0.01m


}SysCFG_T;

typedef struct CCSDQ_Frame
{

	unsigned char 	GainA;				//'A'~'^''
    unsigned char 	GainB;				//'A'~'^''
	unsigned char   TVGA;				//'A'~'^''
	unsigned char 	TVGB;				//'A'~'^''
	unsigned char   PulseWidth;			//'A'~'D' 
	unsigned char   MeasureRange;		//'A'~'H'	5/10/20/40/100/200/400/800
	unsigned char   Channel;			//'A'~'C' 1:A 2:B 3:A&B
	unsigned char   TXPwr;				//'A'~'D'  0:low 1: Mid 2:High	3:Auto
	unsigned char   Mode;				//'A'~'C'  0:Auto-1 1:Auto-2  2:Manual
	unsigned char   ColorBarNum;		//'A'~'E'
	unsigned char  	DynamicRange;		//'A'~'D'
	unsigned char   CurrentChannel;		//'A'~'B'
	

}CCSDQ_Frame_T;




static char *SysCFG_CCSDQ;

static void SysCFG_Cal_CCSDQ_CheckSUm(void);

static void SysCFG_Fill_CCSDQ_Array(void);

extern char * SysCFG_Create_CCSDQ(int sensorMode);

extern void SysCFG_Init(void);


//extern SysCFG_T * SysCFG_Get_SysCFG(void);

extern int  SysCFG_Get_SysCFG(int ItemIndex);

extern void SysCFG_Set_SysCFG(int ItemIndex, int value);

extern void SysCFG_SaveToFile(void);

extern void SysCFG_GetFromFile(void);







#endif
