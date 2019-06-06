/************************************************************************
*                                                                    	*
*            Outline Framewin class for BotherMeter              		*
*              															*
*                                                                  		*
*        ------------------------Made by Softwind  20190509    			*
*                                                                   	*
*************************************************************************
*/

// USER START (Optionally insert additional includes)
// USER END

#include "DIALOG.h"
#include "OutlineFrame.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_FRAMEWIN_0 (GUI_ID_USER + 110)
#define ID_HEADER_0 (GUI_ID_USER + 111)
#define ID_HEADER_1 (GUI_ID_USER + 112)
#define ID_TEXT_0 (GUI_ID_USER + 113)
#define ID_TEXT_1 (GUI_ID_USER + 114)
#define ID_TEXT_2 (GUI_ID_USER + 115)
#define ID_TEXT_3 (GUI_ID_USER + 116)
#define ID_TEXT_4 (GUI_ID_USER + 117)
#define ID_TEXT_5 (GUI_ID_USER + 118)
#define ID_TEXT_6 (GUI_ID_USER + 119)
#define ID_TEXT_7 (GUI_ID_USER + 120)
#define ID_TEXT_8 (GUI_ID_USER + 121)
#define ID_TEXT_9 (GUI_ID_USER + 122)
#define ID_TEXT_10 (GUI_ID_USER + 123)
#define ID_TEXT_11 (GUI_ID_USER + 124)
#define ID_TEXT_12 (GUI_ID_USER + 125)

#define ID_BUTTON_0 (GUI_ID_USER + 127)
#define ID_BUTTON_1 (GUI_ID_USER + 128)
#define ID_BUTTON_2 (GUI_ID_USER + 129)


static int Button_Status =0;

// USER START (Optionally insert additional defines)
// USER END

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

// USER START (Optionally insert additional static data)
// USER END

/*********************************************************************
*
*       _aDialogCreate
*/
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
  { FRAMEWIN_CreateIndirect, "Framewin", ID_FRAMEWIN_0, 0, 0, 800, 600, 0, 0x0, 0 },
  { HEADER_CreateIndirect, "Header", ID_HEADER_0, 0, 0, 800, 50, 0, 0x0, 0 },
  { HEADER_CreateIndirect, "Header", ID_HEADER_1, 0, 575, 800, 25, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "N:XX:XX:XX", ID_TEXT_0, 12, 2, 134, 50, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "E:XX:XX:XX", ID_TEXT_1, 12, 26, 135, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "PCF:1/1", ID_TEXT_2, 385, 5, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "DFT:2.0", ID_TEXT_3, 385, 28, 93, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "DBS:1.0", ID_TEXT_4, 485, 5, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "ALM:4.0", ID_TEXT_5, 485, 28, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "GainA:1.0", ID_TEXT_6, 585, 4, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "GainB:2.0", ID_TEXT_7, 585, 28, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "TvgA:1.0", ID_TEXT_8, 685, 5, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "TvgB:1.0", ID_TEXT_9, 685, 28, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "Manual Mode", ID_TEXT_10, 9, 577, 133, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "2019/5/9", ID_TEXT_11, 622, 577, 80, 20, 0, 0x0, 0 },
  { TEXT_CreateIndirect, "18:18:18", ID_TEXT_12, 717, 577, 80, 20, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_0, 120, 576, 108, 16, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_1, 10, 576, 108, 16, 0, 0x0, 0 },
  { BUTTON_CreateIndirect, "Button", ID_BUTTON_2, 230, 576, 108, 16, 0, 0x0, 0 },
  // USER START (Optionally insert additional widgets)
  // USER END
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
*
*       _cbDialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  int     NCode;
  int     Id;
  // USER START (Optionally insert additional variables)
  // USER END

  switch (pMsg->MsgId) 
  {


    case WM_TIMER: 
    

      if( Button_Status==0)
      {
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
        BUTTON_SetFont(hItem,GUI_FONT_13_ASCII);
        BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_BLACK);
  
     
        BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,GUI_YELLOW);
        Button_Status=1;
      }
      else
      {
        hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
        BUTTON_SetFont(hItem, GUI_FONT_16B_ASCII);
        BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_RED);


        BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,GUI_ORANGE);
        Button_Status=0;
      }

      WM_RestartTimer(pMsg->Data.v, 200); 

    break;
  

  case WM_INIT_DIALOG:
    //
    // Initialization of 'Framewin'
    //
    hItem = pMsg->hWin;
    FRAMEWIN_SetTitleHeight(hItem, 14);
    FRAMEWIN_SetTitleVis(hItem, 0);
    //
    // Initialization of 'N:XX:XX:XX'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_0);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'E:XX:XX:XX'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_1);
    TEXT_SetFont(hItem, GUI_FONT_24_ASCII);
    //
    // Initialization of 'PCF:1/1'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_2);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'DFT:2.0'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_3);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'DBS:1.0'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_4);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'ALM:4.0'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_5);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'GainA:1.0'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_6);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'GainB:2.0'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_7);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'TvgA:1.0'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_8);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'TvgB:1.0'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_9);
    TEXT_SetFont(hItem, GUI_FONT_COMIC18B_1);
    //
    // Initialization of 'Manual Mode'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_10);
    TEXT_SetFont(hItem, GUI_FONT_16_ASCII);
    //
    // Initialization of '2019/5/9'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_11);
    TEXT_SetFont(hItem, GUI_FONT_16_ASCII);
    //
    // Initialization of '18:18:18'
    //
    hItem = WM_GetDialogItem(pMsg->hWin, ID_TEXT_12);
    TEXT_SetFont(hItem, GUI_FONT_16_ASCII);
    
    
	
	  // init Head0&1
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_0);
	
	  HEADER_SetSkinClassic(hItem);
	  HEADER_SetBkColor(hItem,GUI_WHITE);
	
	
	
	  hItem = WM_GetDialogItem(pMsg->hWin, ID_HEADER_1);

	  HEADER_SetSkinClassic(hItem);
	  HEADER_SetBkColor(hItem,GUI_WHITE);

    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_0);
    BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_WHITE);
    BUTTON_SetFont(hItem, GUI_FONT_16_ASCII);
    BUTTON_SetText(hItem, "Voltage:18V");
    //BUTTON_SetSkinClassic(hItem);
    BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,GUI_ORANGE);
   
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_1);
    BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_DARKGREEN);
    BUTTON_SetFont(hItem, GUI_FONT_16_ASCII);
    BUTTON_SetText(hItem, "Deep Safe");
    //BUTTON_SetSkinClassic(hItem);
    BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,GUI_LIGHTGREEN);

   
    hItem = WM_GetDialogItem(pMsg->hWin, ID_BUTTON_2);
    BUTTON_SetTextColor(hItem,BUTTON_CI_UNPRESSED,GUI_DARKGREEN);
    BUTTON_SetFont(hItem, GUI_FONT_16_ASCII);
    BUTTON_SetText(hItem, "SD Insert");
    //BUTTON_SetSkinClassic(hItem);
    BUTTON_SetBkColor(hItem,BUTTON_CI_UNPRESSED,GUI_LIGHTGREEN);
	
	
   
    break;
    case WM_NOTIFY_PARENT:
      Id    = WM_GetId(pMsg->hWinSrc);
      NCode = pMsg->Data.v;
      switch(Id) 
      {
        case ID_HEADER_0: // Notifications sent by 'Header'
          switch(NCode) 
          {
            case WM_NOTIFICATION_CLICKED:
       
            break;
            case WM_NOTIFICATION_RELEASED:
        
            break;
            case WM_NOTIFICATION_MOVED_OUT:
        
            break;
      
          }
        break;

        case ID_HEADER_1: // Notifications sent by 'Header'
          switch(NCode) 
          {
            case WM_NOTIFICATION_CLICKED:
        
            break;
            case WM_NOTIFICATION_RELEASED:
        
            break;
            case WM_NOTIFICATION_MOVED_OUT:
        
            break;
     
          }
        break;
      
        case ID_BUTTON_0: // Notifications sent by 'Button'
          switch(NCode) 
          {
            case WM_NOTIFICATION_CLICKED:
      
            break;
            case WM_NOTIFICATION_RELEASED:
     
            break;
      
          }
        break;

        case ID_BUTTON_1: // Notifications sent by 'Button'
          switch(NCode) 
          {
            case WM_NOTIFICATION_CLICKED:
    
            break;
            case WM_NOTIFICATION_RELEASED:
     
            break;
      
          }
          break;
        case ID_BUTTON_2: // Notifications sent by 'Button'
          switch(NCode) 
          {
            case WM_NOTIFICATION_CLICKED:
     
            break;
            case WM_NOTIFICATION_RELEASED:
      
            break;
     
          }
        break;
   
      }
    break;
 
    default:
      WM_DefaultProc(pMsg);
    break;
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       CreateFramewin
*/
WM_HWIN OutlineFrame_CreateFramewin(void) 
{
    WM_HWIN hWin;
    WM_HTIMER hTimer; 

    hWin = GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), _cbDialog, WM_HBKWIN, 0, 0);
    hTimer =WM_CreateTimer(WM_GetClientWindow(hWin),0,200,0);
  
    return hWin;
}

// USER START (Optionally insert additional public code)
// USER END

/*************************** End of file ****************************/
