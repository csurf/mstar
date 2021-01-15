#include "autoFunc.h"

#ifndef _MENUTBLDEF_H_
#define _MENUTBLDEF_H_

// Key function definitions
KeyEventType code NaviKeyEvent[KEY_NOTHING] =
{
	//The order of this data must match the corresponding names in eKEY.
	{INPUT_PRESS | INPUT_HOLD, MIA_DecValue, Input_AllPort}, //KEY_UP
	{INPUT_PRESS | INPUT_HOLD, MIA_IncValue, Input_AllPort}, // KEY_DOWN
	{INPUT_PRESS, MIA_NextItem, Input_AllPort}, // KEY_MENU
	{INPUT_PRESS | INPUT_HOLD, MIA_DecValue, Input_AllPort}, // KEY_LEFT
	{INPUT_PRESS | INPUT_HOLD, MIA_IncValue, Input_AllPort}, // KEY_RIGHT
	{INPUT_PRESS, MIA_Source, Input_AllPort}, // KEY_SOURCE
	{INPUT_PRESS, MIA_Power, Input_AllPort}, // KEY_POWER
};

KeyEventType code ExecKeyEvent[KEY_NOTHING] =
{
	{INPUT_PRESS, MIA_ExecFunc, Input_AllPort}, // KEY_UP
	{INPUT_PRESS, MIA_ExecFunc, Input_AllPort}, // KEY_DOWN
	{INPUT_PRESS, MIA_NextItem, Input_AllPort}, // KEY_MENU
	{INPUT_PRESS, MIA_Nothing, Input_AllPort}, // KEY_LEFT
	{INPUT_PRESS, MIA_Nothing, Input_AllPort}, // KEY_RIGHT
	{INPUT_PRESS, MIA_Source, Input_AllPort}, // KEY_SOURCE
	{INPUT_PRESS, MIA_Power, Input_AllPort}, // KEY_POWER
};

KeyEventType code RootKeyEvent[KEY_NOTHING] =
{
	//The order of this data must match the corresponding names in eKEY.
	{INPUT_PRESS, MIA_Source, Input_AllPort}, // KEY_UP
	{INPUT_PRESS, MIA_Nothing, Input_AllPort}, // KEY_DOWN
	{INPUT_PRESS, MIA_GotoNext, Input_AllPort}, // KEY_MENU
	{INPUT_PRESS, MIA_Source, Input_AllPort}, // KEY_LEFT
	{INPUT_PRESS, MIA_IncValue, Input_AllPort}, //KEY_RIGHT
	{INPUT_PRESS, MIA_Source, Input_AllPort}, // KEY_SOURCE
	{INPUT_PRESS, MIA_Power, Input_AllPort}, // kEY_POWER
};

/*
KeyEventType code NothingKeyEvent[KEY_NOTHING] =
{
 //The order of this data must match the corresponding names in eKEY.
 {INPUT_PRESS, MIA_Nothing, Input_AllPort}, //key_UP
 {INPUT_PRESS, MIA_Nothing, Input_AllPort}, // key_DOWN
 {INPUT_PRESS, MIA_Nothing, Input_AllPort}, // key_Menu
 {INPUT_PRESS, MIA_Nothing, Input_AllPort}, //KET_left
 {INPUT_PRESS, MIA_Nothing, Input_AllPort}, //KEY_RIGHT
 {INPUT_PRESS, MIA_Source, Input_AllPort}, //KEY_SOURCE
 {INPUT_PRESS, MIA_Power, Input_AllPort}, // key_Power
};
*/

//====================================================================================

DrawValueType code DisplayValueNull[] =
{
	{
		dwiEnd,
		NULL,
		NULL,
		NULL
	}
};

//====================================================================================

MenuItemType code RootMenuItems[] =
{
	// virtual item
	{
		0, 1, // XPos, YPos;
		CP_WhiteColor1, CP_BlueColor, // ForeColor, BackColor;
		CP_RedColor, CP_BlueColor, // SelForeColor, SelBackColor;
		PictureMenu, //NextMenuPage;
		DWI_CenterText,// DrawMenuItemType;
		NULL, // DisplayText;
		RootKeyEvent,
		{
			NULL, // AdjustFunction
			NULL // ExecFunction
		},// DisplayValue;
		DisplayValueNull,
		mibSelectable // Flags
	}
};

#endif
