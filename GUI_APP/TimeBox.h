#ifndef TimeBox_Unit
#define TimeBox_Unit


#include "DIALOG.h"

#define TimeBox_Loc_Original_X		525

#define TimeBox_Loc_Original_Y		100

#define TimeBox_Width				162

#define TimeBox_Heigh				25


extern WM_HWIN TimeBox_CreateWindow(void);

extern void TimeBox_Hide(void);

//extern WM_HWIN TimeBox_Show(WM_HWIN	NextHWin);
extern WM_HWIN TimeBox_Show(WM_HWIN	NextHWin,int boxMode);

extern 	void TimeBox_MoveWindow(int menuItemIndex);
extern void TimeBox_SetStyle(int Style);			//0 is time 1 is date

#endif
