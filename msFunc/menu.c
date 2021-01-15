#define _MENU_C_

#include <STDLIB.H>
#include <STRING.H>
#include "types.h"
#include "board.h"
#include "global.h"
#include "keypadDef.h"
#include "menu.h"
#include "keypad.h"
#include "ms_rwreg.h"
#include "msOSD.h"
#include "menuFunc.h"
#include "menuStr.h"
#include "menutbl.h"
#include "ms_reg.h"
#include "debug.h"
#include "misc.h"
#include "nvram.h"
#include "adjust.h"
#include "userPref.h"
#include "power.h"
#include "panel.h"
#include "mstar.h"
#include "devVD.h"
#include "menuFunc.h"

#define CurrentMenu tblMenus[g_ucMenuPageIndex]
#define PrevMenuPage CurrentMenu.PrevPage
#define CurrentMenuItems CurrentMenu.MenuItems
#define MenuItemCount CurrentMenu.ItemCount
#define CurrentMenuTimeOut CurrentMenu.TimeOut

#define CurrentMenuItem CurrentMenu.MenuItems[g_ucMenuItemIndex]
#define NextMenuPage CurrentMenuItem.NextPage
#define CurrentMenuItemFunc CurrentMenuItem.KeyFunction
//#define KeyEvent CurrentMenuItem.KeyEvents[KeypadButton]

#define ucHoldCount 10
#define ucRptCount 1

//========================================================================
BOOL ResetOsdTimer ( void )
{
	BYTE tempValue = g_VideoSetting.OsdTime;

	if ( tempValue == 0 )
	{
		g_ucOsdCounter = 2;
	}

	else if ( tempValue == 1 )
	{
		g_ucOsdCounter = 5;
	}

	else if ( tempValue == 2 )
	{
		g_ucOsdCounter = 10;
	}

	else if ( tempValue == 3 )
	{
		g_ucOsdCounter = 15;
	}

	else if ( tempValue == 4 )
	{
		g_ucOsdCounter = 30;
	}

	else
	{
		g_ucOsdCounter = 60;
	}

	if ( CurrentMenuTimeOut & mtbIndividualTimeOut )
	{
		g_ucOsdCounter = CurrentMenuTimeOut & ~mtbIndividualTimeOut; //Vick :Disable OSD timer out
	}

	Clr_OsdTimeoutFlag();
	return TRUE;
}

void Menu_InitVariable ( void )
{
	g_ucMenuPageIndex = RootMenu;
	g_ucMenuItemIndex = 0;
	g_ucOsdCounter = 0;
}

void Menu_OsdHandler ( void )
{
	Key_ScanKeypad();

	// OSD auto-disable timer expired,
	// so must do OSD close & clean-up
	if ( OsdTimeoutFlag )
	{
		Clr_OsdTimeoutFlag();

		// we're inside a menu page,
		// so we must reset back to root (empty) menu page
		if ( g_ucMenuPageIndex > RootMenu )
		{
			g_ucMenuPageIndex = RootMenu;
			g_ucMenuItemIndex = 0;
			// initiate a redraw
			ExecuteKeyEvent ( MIA_RedrawMenu );
			// save the user settings
			SaveUserPref();
		}
	}
}

void EventProcess ( BYTE ucKeyCode )
{
	BYTE ucEvent = MIA_Nothing;

	g_ucKeyRptCount = 0;
	g_ucNextRptCount = ucHoldCount ;

	if ( ( CurrentMenuItem.KeyEvents[ucKeyCode].cConditions & INPUT_PRESS ) && ( CurrentMenuItem.KeyEvents[ucKeyCode].InputType & 1 << g_VideoSetting.InputType ) )
	{
		ucEvent = CurrentMenuItem.KeyEvents[ucKeyCode].PressKeyEvent;
	}

	// printf ( "\r\ng_ucMenuPageIndex: %d", g_ucMenuPageIndex );
	// printf ( "\r\nucEvent: %d", ucEvent );
	MenuProcessKey ( ucEvent );
}

void EventRepeatProcess ( BYTE ucKeyCode, BYTE ucTicks )
{
	BYTE ucEvent = MIA_Nothing;

	if ( ( CurrentMenuItem.KeyEvents[ucKeyCode].cConditions & INPUT_HOLD ) && ( CurrentMenuItem.KeyEvents[ucKeyCode].InputType & 1 << g_VideoSetting.InputType ) )
	{
		g_ucKeyRptCount++;

		if ( g_ucKeyRptCount >= ( g_ucNextRptCount * ucTicks ) )
		{
			ucEvent = CurrentMenuItem.KeyEvents[ucKeyCode].PressKeyEvent;
			g_ucKeyRptCount = 0;
			g_ucNextRptCount = ucRptCount;
		}
	}

	MenuProcessKey ( ucEvent );
}

void MenuProcessKey ( BYTE menuAction )
{
	if ( menuAction )
	{
		if ( !PowerOnFlag )
		{
			menuAction = MIA_Nothing;
		}

		// printf ( "\r\nmenuAction: %d", menuAction );
		if ( ExecuteKeyEvent ( menuAction ) )
		{
			ResetOsdTimer();
			Clr_OsdTimeoutFlag();
		}
	}
}

BOOL ExecuteKeyEvent ( MenuItemActionType menuAction )
{
	BOOL processEvent = TRUE;
	BYTE tempValue;

	while ( processEvent )
	{
		processEvent = FALSE;

		switch ( menuAction )
		{
		case MIA_IncValue:
		case MIA_DecValue:

			if ( CurrentMenuItemFunc.AdjustFunction )
			{
				if ( CurrentMenuItemFunc.AdjustFunction ( menuAction ) )
				{
					DrawOsdMenuItemValue ( g_ucMenuItemIndex, CurrentMenuItem.DisplayValue );
					Set_SaveSettingFlag();
				}
			}

			break;

		case MIA_NextItem:
		case MIA_PrevItem:
			tempValue = g_ucMenuItemIndex;

			if ( menuAction == MIA_NextItem )
			{
				g_ucMenuItemIndex = GetNextItem ( CurrentMenuItems );
			}

			else
			{
				g_ucMenuItemIndex = GetPrevItem ( CurrentMenuItems );
			}

			if ( tempValue != g_ucMenuItemIndex )
			{
				DrawOsdMenuItem ( tempValue, &CurrentMenuItems[tempValue] );
				DrawOsdMenuItem ( g_ucMenuItemIndex, &CurrentMenuItem );
				SystemDelay_translate_To_Dsp_Processor ( 5 );
			}

			break;

		case MIA_JumpAdjustItem:
		case MIA_JumpNaviItem:
			tempValue = g_ucMenuItemIndex;
			g_ucMenuItemIndex += ( ( menuAction == MIA_JumpAdjustItem ) ? 1 : -1 );
			DrawOsdMenuItem ( tempValue, &CurrentMenuItems[tempValue] );
			DrawOsdMenuItem ( g_ucMenuItemIndex, &CurrentMenuItem );
			//Delay1ms(300);
			break;

		case MIA_GotoNext:
		case MIA_GotoPrev:
			tempValue = g_ucMenuPageIndex;
			g_ucMenuPageIndex = ( menuAction == MIA_GotoNext ) ? NextMenuPage : PrevMenuPage;
			g_ucMenuItemIndex = GetMenuItemIndex ( tempValue );

			if ( g_ucMenuPageIndex == RootMenu )
			{
				SaveUserPref();
			}

		//Delay1ms(150);

		// if(g_ucMenuPageIndex == FunctionMenu || g_ucMenuPageIndex == SystemMenu)
		// {
		// BYTE kk;
		// Osd_SetTextColor(CP_GrayColor, CP_GrayColor);
		// for (kk = 3; kk <= 9; kk++)
		// Osd_DrawStr(0, kk, " ");
		// }

		case MIA_RedrawMenu:
			DrawOsdMenu();

			if ( CurrentMenu.ExecFunction )
			{
				tempValue = CurrentMenu.ExecFunction();
			}

			if ( ! ( CurrentMenu.Flags & mpbStay ) )
			{
				processEvent = TRUE;
				menuAction = MIA_GotoPrev;
			}

			break;

		case MIA_ExecFunc:
			if ( CurrentMenuItemFunc.ExecFunction )
			{
				tempValue = 0;
				tempValue = CurrentMenuItemFunc.ExecFunction();

				if ( ! tempValue )
				{
					return FALSE;
				}

				processEvent = FALSE;
			}

			break;

		case MIA_Power:
			// if (PowerOnFlag)
			// g_ucMenuPageIndex = PowerOffMenu;
			// else
			// g_ucMenuPageIndex = PowerOnMenu;

			g_ucMenuItemIndex = 0;
			menuAction = MIA_RedrawMenu;
			processEvent = TRUE;
			break;

		case MIA_Source:
			AdjustSource();
			break;

		default:
			return FALSE;
			break;
		}
	}

	return TRUE;
}

void DrawOsdMenu ( void )
{
	BOOL redrawFlags;
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	if ( CurrentMenu.Flags & mpbInvisible )
	{
		Osd_Hide();
	}

	else
	{
		BYTE i;

		// setup osd window & position
		redrawFlags = FALSE;

		if ( CurrentMenu.XSize != OsdWindowWidth || CurrentMenu.YSize != OsdWindowHeight || ! ( msReadOSDByte ( OSD_0C_IOSDC1 ) & MWIN_B ) )
		{
			redrawFlags = TRUE;
		}

		if ( redrawFlags )
		{
			Osd_Hide();
			Osd_SetWindowSize ( CurrentMenu.XSize, CurrentMenu.YSize );

			if ( CurrentMenu.Flags & mpbSetItemTop )
			{
				Osd_SetPosition ( ( 99 - g_VideoSetting.Scaling * 15 ), 5 );
				msWriteByte ( BK0_63_OSD_CTL, 0x0F );
			}

			else
			{
				Osd_SetPosition ( 50, 50 );
				msWriteByte ( BK0_63_OSD_CTL, 0x03 );
			}

			for ( i = 0; i < MenuItemCount; i++ )
			{
				DrawOsdMenuItem ( i, &CurrentMenu.MenuItems[i] );
			}

			DrawOsdMenuItem ( g_ucMenuItemIndex, &CurrentMenu.MenuItems[g_ucMenuItemIndex] ); //ZWTAN 20050711

			Osd_Show();
		}

		else
		{
			for ( i = 0 ; i < MenuItemCount; i++ )
			{
				DrawOsdMenuItem ( i, &CurrentMenu.MenuItems[i] );
			}

			DrawOsdMenuItem ( g_ucMenuItemIndex, &CurrentMenu.MenuItems[g_ucMenuItemIndex] );
			Osd_Show();
		}
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void DrawOsdMenuItem ( BYTE itemIndex, MenuItemType* menuItem )
{
	if ( menuItem->Flags & mibInvisible )
	{
		return;
	}

	if ( menuItem->Flags & mibSelectable && itemIndex == g_ucMenuItemIndex )
	{
		Osd_SetTextColor ( menuItem->SelForeColor, menuItem->SelBackColor );
	}

	else
	{
		Osd_SetTextColor ( menuItem->ForeColor, menuItem->BackColor );
	}

	DrawOsdMenuItemText ( itemIndex, menuItem );

	if ( &CurrentMenuItem == menuItem || menuItem->Flags & mibDrawValue )
	{
		if ( & ( menuItem->DisplayValue ) )
		{
			DrawOsdMenuItemValue ( itemIndex, ( menuItem->DisplayValue ) ); //->DisplayValue);
		}
	}
}

void DrawOsdMenuItemText ( BYTE itemIndex, MenuItemType* menuItem )
{
	if ( menuItem->DisplayText == NULL )
	{
		return;
	}

	if ( menuItem->DrawItemMethod == DWI_Icon || menuItem->DrawItemMethod == DWI_Text )
	{
		Osd_DrawStr ( menuItem->XPos, menuItem->YPos, menuItem->DisplayText() );
	}

	else // full text
	{
		BYTE i;
		BYTE xPos;

#define len itemIndex
		len = strlen ( menuItem->DisplayText() );

		if ( menuItem->DrawItemMethod == DWI_FullText )
		{
			xPos = menuItem->XPos;
		}

		else if ( menuItem->DrawItemMethod == DWI_FullCenterText || menuItem->DrawItemMethod == DWI_CenterText )
		{
			xPos = ( OsdWindowWidth - len ) / 2; // get center position
		}

		Osd_DrawStr ( xPos, menuItem->YPos, menuItem->DisplayText() );

		if ( menuItem->DrawItemMethod != DWI_CenterText ) // full text
		{
			for ( i = 0; i < xPos; i++ )
			{
				Osd_DrawChar ( i, menuItem->YPos, ' ' ); // fill space
			}

			for ( i = xPos + len; i < OsdWindowWidth; i++ )
			{
				Osd_DrawChar ( i, menuItem->YPos, ' ' );
			}
		}

#undef len
	}
}

void DrawOsdMenuItemValue ( BYTE itemIndex, DrawValueType* valueItem )
{
	while ( 1 )
	{
		if ( valueItem->DrawNumber )
		{
			DrawOsdMenuItemNumber ( itemIndex, valueItem->DrawNumber );
		}

		if ( valueItem->DrawGauge )
		{
			DrawOsdMenuItemGauge ( itemIndex, valueItem->DrawGauge );
		}

		if ( valueItem->DrawRadioGroup )
		{
			DrawOsdMenuItemRadioGroup ( itemIndex, valueItem->DrawRadioGroup );
		}

		if ( valueItem->Flags & dwiEnd )
		{
			break;
		}

		valueItem++;
	}
}

void DrawOsdMenuItemNumber ( BYTE itemIndex, DrawNumberType* numberItem )
{
	if ( itemIndex == g_ucMenuItemIndex ) //Vick Add
	{
		Osd_SetTextColor ( numberItem->SelForeColor, numberItem->SelBackColor );
	}

	else
	{
		Osd_SetTextColor ( numberItem->ForeColor, numberItem->BackColor );
	}

#define xPos itemIndex
	xPos = numberItem->XPos;

	if ( xPos == 0xFF )
	{
		xPos = ( OsdWindowWidth - 4 ) / 2 - 1;
	}

	if ( numberItem->Flags & dwiHex )
	{
		Osd_DrawHex ( xPos, numberItem->YPos, numberItem->GetValue() );
	}

	else if ( numberItem->Flags & dwiLargeNum )
	{
		Osd_DrawLargeNum ( xPos, numberItem->YPos, numberItem->GetValue() );
	}

	else
	{
		Osd_DrawNum ( xPos, numberItem->YPos, numberItem->GetValue() );
	}

#undef xPos
}

void DrawOsdMenuItemGauge ( BYTE itemIndex, DrawGaugeType* gaugeItem )
{
	if ( itemIndex == g_ucMenuItemIndex )
	{
		Osd_SetTextColor ( gaugeItem->SelForeColor, gaugeItem->SelBackColor );
	}

	else
	{
		Osd_SetTextColor ( gaugeItem->ForeColor, gaugeItem->BackColor );
	}

#define xPos itemIndex
	xPos = gaugeItem->XPos;

	if ( xPos == 0xFF )
	{
		xPos = ( OsdWindowWidth - gaugeItem->Length ) / 2;
	}

	Osd_DrawGauge ( xPos, gaugeItem->YPos, gaugeItem->Length, gaugeItem->GetValue() );
#undef xPos
}

void DrawFullCenterText ( BYTE xPos, BYTE yPos, BYTE* str )
{
	BYTE i, len;

	if ( xPos == 0xFF )
	{
		len = strlen ( str );
		xPos = ( OsdWindowWidth - len ) / 2;

		for ( i = 2; i < xPos; i++ )
		{
			Osd_DrawChar ( i, yPos, ' ' );
		}

		for ( i = xPos + len; i < OsdWindowWidth - 2; i++ )
		{
			Osd_DrawChar ( i, yPos, ' ' );
		}
	}

	Osd_DrawStr ( xPos, yPos, str );
}

void DrawOsdMenuItemRadioGroup ( BYTE itemIndex, DrawRadioGroupType* radioItem )
{
	RadioTextType* radioText;
	BYTE i = 0;
	radioText = radioItem->RadioText;

	if ( radioText )
	{
		if ( radioItem->GetValue )
		{
			i = radioItem->GetValue();
		}

		if ( radioItem->Flags & dwiSingleRadioItem )
		{
			radioText += i;
			i = 0;
		}

		while ( 1 )
		{
			// set high color
			if ( radioText->DisplayText )
			{
				if ( radioItem->Flags & dwiValueSelectRadioItemColor )
				{
					if ( !i )
					{
						Osd_SetTextColor ( radioText->SelForeColor, radioText->SelBackColor );
					}

					else
					{
						Osd_SetTextColor ( radioText->ForeColor, radioText->BackColor );
					}
				}

				else
				{
					if ( itemIndex == g_ucMenuItemIndex )
					{
						Osd_SetTextColor ( radioText->SelForeColor, radioText->SelBackColor );
					}

					else
					{
						Osd_SetTextColor ( radioText->ForeColor, radioText->BackColor );
					}
				}

				DrawFullCenterText ( radioText->XPos, radioText->YPos, radioText->DisplayText() );
			}

			if ( radioText->Flags & dwiEnd )
			{
				break;
			}

			radioText ++;
			i--;
		}
	}
}

BYTE GetPrevItem ( MenuItemType* menuItem )
{
	signed char i;

	if ( g_ucMenuItemIndex )
	{
		for ( i = g_ucMenuItemIndex - 1; i >= 0; i-- )
		{
			if ( menuItem[i].Flags & mibSelectable )
			{
				return i;
			}
		}
	}

	for ( i = MenuItemCount - 1; i >= 0; i-- )
	{

		if ( menuItem[i].Flags & mibFactoryItem )
		{
			continue;
		}

		if ( menuItem[i].Flags & mibConditionEnableItem && !EnableTimeFlag )
		{
			continue;
		}

		// if (menuItem[i].Flags&mibTVItem && !IsTVInUse())
		// continue;

		if ( menuItem[i].Flags & mibSelectable )
		{
			return i;
		}
	}

	return g_ucMenuItemIndex;
}

BYTE GetNextItem ( MenuItemType* menuItem )
{
	BYTE i;

	if ( g_ucMenuItemIndex < MenuItemCount - 1 ) // current item is not last item.
	{
		for ( i = g_ucMenuItemIndex + 1; i < MenuItemCount; i++ )
		{

			if ( menuItem[i].Flags & mibFactoryItem )
			{
				continue;
			}

			if ( menuItem[i].Flags & mibConditionEnableItem && !EnableTimeFlag )
			{
				continue;
			}

			if ( menuItem[i].Flags & mibSelectable )
			{
				return i;
			}
		}
	}

	for ( i = 0; i < g_ucMenuItemIndex; i++ )
	{

		if ( menuItem[i].Flags & mibFactoryItem )
		{
			continue;
		}

		if ( menuItem[i].Flags & mibConditionEnableItem && !EnableTimeFlag )
		{
			continue;
		}

		if ( menuItem[i].Flags & mibSelectable )
		{
			return i;
		}
	}

	return g_ucMenuItemIndex;
}

BYTE GetMenuItemIndex ( BYTE g_ucMenuPageIndex )
{
	g_ucMenuPageIndex = g_ucMenuPageIndex;
	return 0;
}

void DrawShowSourcemenu ( void )
{
	g_ucMenuPageIndex = ShowSourceMenu;
	g_ucMenuItemIndex = 0;
	ExecuteKeyEvent ( MIA_RedrawMenu );
	ResetOsdTimer();
}

void MenuStatusCHK ( void )
{
	if ( g_ucMenuPageIndex > ShowSourceMenu )
	{
		return;
	}

	if ( ShowSourceFlag /* || ! ( g_VdInfo.wVideoStatus & VD_HSYNC_LOCKED )*/  )
	{
		DrawShowSourcemenu();
		Clr_ShowSourceFlag();
		g_ucOsdCounter = 0;
	}
}
