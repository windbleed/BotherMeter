/***************************************************************************************

This Unit was Input dialog, the function was get the input value (interger type)

from the dialog. the dialog location and size should keep alian with the menu

item which call it.

So the dialog should have the ability to move the loc from original to the 

according loc with select menu item.

and it receive the + - key input for value changing and enter key input for

the value input confirmation.



													Made by softwind
													20190604

****************************************************************************************/
#ifndef InputDialog_Unit
#define InputDialog_Unit

#include "DIALOG.h"

#define InputDialog_Loc_Original_X		525

#define InputDialog_Loc_Original_Y		100

#define InputDialog_Width				88

#define InputDialog_Heigh				25




extern WM_HWIN InputDialog_CreateWindow(void);

extern void InputDialog_MoveWindow(int menuItemIndex);


//extern WM_HWIN InputDialog_Show(WM_HWIN NextHWin);

extern WM_HWIN InputDialog_Show(WM_HWIN	NextHWin,int itemIndex);
extern void InputDialog_Hide(void);

extern void InputDialog_SetStyle(int Style);


#endif
