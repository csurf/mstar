#define _MENUSTR_C_

#include "types.h"
#include "board.h"
#include "global.h"
#include "keypadDef.h"
#include "menuDef.h"
#include "menutext.h"
#include "menuFunc.h"
#include "debug.h"

BYTE* ContrastText ( void )
{
	return strContrast;
}

BYTE* BrightnessText ( void )
{
	return strBrightness;
}

BYTE* SaturationText ( void )
{
	return strSaturation;
}

BYTE* ScalingText ( void )
{
	return strScalingText;
}
BYTE* VideoHueText ( void )
{
	return strVideoHue;
}
BYTE* BacklightText ( void )
{
	return strBacklight;
}

BYTE* ResetText ( void )
{
	return strReset;
}

BYTE* HandIcon ( void )
{
	return strHandIcon;
}

BYTE* CurrentChromaModeText ( void )
{
	BYTE ucTemp;
	ucTemp = GetChromaModeValue();
	return strCurrentChromaMode[ucTemp];
}

// BYTE* SourceInputText ( void )
// {
// return strSourceInput;
// }

BYTE* VideoStdText ( void )
{
	return strVideoStandard;
}

BYTE* SourceText ( void )
{
	switch ( g_VideoSetting.InputType )
	{
		default:
		case Input_CVBS1:
		return strSourceText_AV[0];

	case Input_CVBS2:
		return strSourceText_AV[1];
	}
}

BYTE* Scaling_ModeText ( void )
{
	return strScaling_ModeText[g_VideoSetting.Scaling];
}
