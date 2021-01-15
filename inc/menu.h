#ifndef _MENU_H_
#define _MENU_H_

#include "menuDef.h"

#ifdef _MENU_C_
	#define _MENUDEC_
#else
	#define _MENUDEC_ extern
#endif

typedef enum
{
	BTN_UP,
	BTN_DOWN,
	BTN_Menu,
	BTN_LEFT,
	BTN_RIGHT,
	BTN_SourceSwitch,
	BTN_Power,
	BTN_Nothing
} ButtonType;

_MENUDEC_ BYTE g_ucMenuPageIndex;
_MENUDEC_ BYTE g_ucMenuItemIndex;

_MENUDEC_ void Menu_InitVariable ( void );
_MENUDEC_ void Menu_OsdHandler ( void );
_MENUDEC_ BOOL ResetOsdTimer ( void );
_MENUDEC_ void DrawShowSourcemenu ( void );
_MENUDEC_ void ReDrawCurrentOSDItem ( BYTE item );

_MENUDEC_ BYTE GetMenuItemIndex ( BYTE g_ucMenuPageIndex );
_MENUDEC_ BYTE GetPrevItem ( MenuItemType* menuItem );
_MENUDEC_ BYTE GetNextItem ( MenuItemType* menuItem );
_MENUDEC_ BOOL ExecuteKeyEvent ( MenuItemActionType menuAction );

_MENUDEC_ void DrawOsdMenu ( void );
_MENUDEC_ void DrawOsdMenuItem ( BYTE drawIndex, MenuItemType* menuItem );
_MENUDEC_ void DrawOsdMenuItemText ( BYTE itemIndex, MenuItemType* menuItem );
_MENUDEC_ void DrawOsdMenuItemValue ( BYTE itemIndex, DrawValueType* valueItem );
_MENUDEC_ void DrawOsdMenuItemNumber ( BYTE itemIndex, DrawNumberType* numberItem );
_MENUDEC_ void DrawOsdMenuItemGauge ( BYTE itemIndex, DrawGaugeType* gaugeItem );
_MENUDEC_ void DrawOsdMenuItemRadioGroup ( BYTE itemIndex, DrawRadioGroupType* RadioItem );

_MENUDEC_ void MenuStatusCHK ( void );
_MENUDEC_ void EventProcess ( ButtonType ucKeyButton );
_MENUDEC_ void EventRepeatProcess ( BYTE ucKeyCode, BYTE ucTicks );
_MENUDEC_ void MenuProcessKey ( BYTE menuAction );
#endif
