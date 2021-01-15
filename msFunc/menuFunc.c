#define _MENUFUNC_C_

#include "types.h"
#include "board.h"
#include "global.h"
#include "keypadDef.h"
#include "menu.h"
#include "adjust.h"
#include "ms_reg.h"
#include "debug.h"
#include "msOSD.h"
#include "power.h"
#include "misc.h"
#include "autofunc.h"
#include "nvram.h"
#include "userPref.h"
#include "panel.h"
#include "mstar.h"
#include "ms_rwreg.h"
#include "adjust.h"
#include "mcu.h"
#include "menuStr.h"
#include "msACE.h"
#include "menuFunc.h"

extern BYTE OsdFontColor;

WORD DecIncValue ( MenuItemActionType action, WORD value, WORD minValue, WORD maxValue, BYTE step )
{
	if ( action == MIA_IncValue || action == MIA_InvDecValue )
	{
		if ( value >= maxValue )
		{
			return value;
		}

		minValue = value + step;

		if ( minValue > maxValue )
		{
			minValue = maxValue;
		}

		value = minValue;
	}

	else // Decrease value
	{
		if ( value <= minValue )
		{
			return value;
		}

		maxValue = value - step;

		if ( maxValue < minValue )
		{
			maxValue = minValue;
		}

		value = maxValue;
	}

	return value;
}

//==============================================for Video==================================
BOOL AdjustContrast ( MenuItemActionType action )
{
	WORD tempValue;

	tempValue = DecIncValue ( action, g_VideoSetting.VideoContrast, MinDefVideoContrast, MaxDefVideoContrast, 1 );

	if ( tempValue == g_VideoSetting.VideoContrast )
	{
		return FALSE;
	}

	g_VideoSetting.VideoContrast = tempValue;

	tempValue = usrNonLinearCalculate ( g_NLCContrast, g_VideoSetting.VideoContrast );

	msAdjustVideoContrast ( tempValue );

	return TRUE;
}

WORD GetContrastValue ( void )
{
	return g_VideoSetting.VideoContrast;
}
//====================================================
BOOL AdjustBrightness ( MenuItemActionType action )
{
	WORD tempValue;

	tempValue = DecIncValue ( action, g_VideoSetting.VideoBrightness, MinDefVideoBrightness, MaxDefVideoBrightness, 1 );

	if ( tempValue == g_VideoSetting.VideoBrightness )
	{
		return FALSE;
	}

	g_VideoSetting.VideoBrightness = tempValue;

	tempValue = usrNonLinearCalculate ( g_NLCBrightness, tempValue );
	msAdjustBrightness ( tempValue );

	return TRUE;
}

WORD GetBrightnessValue ( void )
{
	return g_VideoSetting.VideoBrightness;
}

//====================================================
WORD GetVideoHueValue ( void )
{
	return g_VideoSetting.VideoHue;
}

BOOL AdjustVideoHue ( MenuItemActionType action )
{
	WORD tempValue;

	tempValue = DecIncValue ( action, g_VideoSetting.VideoHue, MinDefVideoHue, MaxDefVideoHue, 1 );

	if ( tempValue == g_VideoSetting.VideoHue )
	{
		return FALSE;
	}

	g_VideoSetting.VideoHue = tempValue;
	msAdjustVideoHue ( g_VideoSetting.VideoHue );

	return TRUE;
}

//====================================================
BOOL AdjustSaturation ( MenuItemActionType action )
{
	WORD tempValue;

	tempValue = DecIncValue ( action, g_VideoSetting.VideoSaturation, MinDefVideoSaturation, MaxDefVideoSaturation, 2 );

	if ( tempValue == g_VideoSetting.VideoSaturation )
	{
		return FALSE;
	}

	g_VideoSetting.VideoSaturation = tempValue;

	tempValue = usrNonLinearCalculate ( g_NLCSaturation, g_VideoSetting.VideoSaturation );

	msAdjustVideoSaturation ( tempValue );

	return TRUE;
}

WORD GetSaturationValue ( void )
{
	return g_VideoSetting.VideoSaturation ;
}

BOOL AdjustSource ( void )
{
	g_VideoSetting.InputType += 1;
	g_VideoSetting.InputType %= Input_Nums;

	resetInput();

	Set_SaveSettingFlag();
	SaveUserPref();
	return TRUE;
}

void resetInput ( void )
{
	msSetInterrupt ( INTERRUPT_DISABLE );
	//msSetBlueScreen ( _ENABLE, FR_BLUE );
	Power_TurnOffPanel();
	
	Set_InputTimingChangedFlag();
	Clr_InputTimingStableFlag();
	Set_ShowSourceFlag();
	Set_SourceChangedFlag();
	msSetupInputPort();
}

WORD GetChromaModeValue ( void )
{
	return ( g_VideoSetting.VideoColorSys %= CHROMA_NUMS );
}

BOOL AdjustChromaMode ( MenuItemActionType action )
{
	if ( action == MIA_IncValue )
	{
		g_VideoSetting.VideoColorSys += 1;
	}

	else
	{
		g_VideoSetting.VideoColorSys += ( CHROMA_NUMS - 1 );
	}

	g_VideoSetting.VideoColorSys %= CHROMA_NUMS;

	SetChromaMode();
	//msForceChromaDetect ( g_VdInfo.ucVideoSystem );
	return TRUE;
}

BOOL ResetAllSettings ( void )
{
	InitVideoSetting();
	resetInput();
	Osd_Hide();
	g_ucOsdCounter = 0;
	Set_OsdTimeoutFlag();
	Set_SaveSettingFlag();
	return FALSE;
}

void SaveUserPref ( void )
{
	if ( SaveSettingFlag )
	{
		SaveVideoSetting();

		Clr_SaveSettingFlag();
		printMsg ( "save setting" );
	}
}

BOOL AdjustScaling ( MenuItemActionType action )
{
	action = action;
	g_VideoSetting.Scaling += 1;
	g_VideoSetting.Scaling %= Scaling_NUMS;
	msSetScaler();

	return TRUE;
}

BYTE usrNonLinearCalculate ( NonLinearCurveType NoLinear, BYTE AdjustValue )
{
	//dual direction
	BYTE rValue, ucXVStart, ucXVEnd, ucXStar, ucXEnd, ucStartPoint;
	WORD wDistance;
	BYTE temData = AdjustValue;

	if ( AdjustValue < NON_LINEAR_POINT_X1 )
	{
		ucXVStart = NoLinear.X0;
		ucXVEnd = NoLinear.X1;
		ucXStar = NON_LINEAR_POINT_X0;
		ucXEnd = NON_LINEAR_POINT_X1;
	}

	else if ( AdjustValue < NON_LINEAR_POINT_X2 )
	{
		ucXVStart = NoLinear.X1;
		ucXVEnd = NoLinear.X2;
		ucXStar = NON_LINEAR_POINT_X1;
		ucXEnd = NON_LINEAR_POINT_X2;
	}

	else if ( AdjustValue < NON_LINEAR_POINT_X3 )
	{
		ucXVStart = NoLinear.X2;
		ucXVEnd = NoLinear.X3;
		ucXStar = NON_LINEAR_POINT_X2;
		ucXEnd = NON_LINEAR_POINT_X3;
	}

	else
	{
		ucXVStart = NoLinear.X3;
		ucXVEnd = NoLinear.X4;
		ucXStar = NON_LINEAR_POINT_X3;
		ucXEnd = NON_LINEAR_POINT_X4;
	}

	if ( ucXVEnd > ucXVStart )
	{
		wDistance = ucXVEnd - ucXVStart;
		ucStartPoint = ucXVStart;
		temData = AdjustValue - ucXStar;
	}

	else
	{
		wDistance = ucXVStart - ucXVEnd;
		ucStartPoint = ucXVEnd;
		temData = ucXEnd - AdjustValue;
	}

	rValue = ( ( WORD ) wDistance * temData / ( ucXEnd - ucXStar ) ) + ucStartPoint;

	return rValue;
}

#if BACKLIGHT_PWM

#define PWM_FACTOR ( MaxDefBacklightPWM - MinDefBacklightPWM )
//#define PWM_FACTOR 0x7F
BOOL AdjustBacklight ( MenuItemActionType action )
{
	WORD tempValue;

	//WORD val = ( (WORD) g_VideoSetting.Backlight * 100 ) / PWM_FACTOR;
	
	tempValue = DecIncValue ( action, g_VideoSetting.Backlight, MinDefBacklightPWM, MaxDefBacklightPWM, 1 );
	
	// printf("\r\nbl:       %d", g_VideoSetting.Backlight);
	// printf("\r\ntempVal: %d", tempValue);

	if ( ( BYTE ) tempValue == g_VideoSetting.Backlight )
	{
		return FALSE;
	}

	//val = ( tempValue * PWM_FACTOR ) / 100;
	
	g_VideoSetting.Backlight = tempValue;
	msSetBacklight ( g_VideoSetting.Backlight );

	return TRUE;
}

WORD GetBacklightValue ( void )
{
	return ( (WORD) g_VideoSetting.Backlight * 100 ) / PWM_FACTOR;
}
#endif

#if LED_BACKLIGHT

BOOL AdjustBacklight ( MenuItemActionType action )
{
	//RANGE:
	// 0x3FF 10-bit max
	// 0x02 min ~2% duty
	// 0x52 max 70% duty
	WORD tempValue;

	tempValue = DecIncValue ( action, g_VideoSetting.Backlight, MinDefBacklight, MaxDefBacklight, 1 );

	if ( ( BYTE ) tempValue == g_VideoSetting.Backlight )
	{
		return FALSE;
	}

	g_VideoSetting.Backlight = tempValue;
	#if LED_BACKLIGHT
	msSetBacklight ( ( BYTE ) tempValue );
	#endif
	return TRUE;
}

WORD GetBacklightValue ( void )
{
	return g_VideoSetting.Backlight;
}

#endif

#if ( PANEL_DIGITAL_TCON || PANEL_ANALOG_TCON )	
//====================================================
BOOL AdjustVideoVCOMDC(MenuItemActionType action)
{

	WORD tempValue;
	WORD val = ( (WORD) g_VideoSetting.VcomDC * 100 ) / ( MaxDefBacklightPWM - MinDefBacklightPWM );
	
	// printf("\r\nvcom: %d",g_VideoSetting.VcomDC);
	// printf("\r\nval:  %d",val);
	
	tempValue = DecIncValue(action, val, 0 , 100, 3);

	if ( tempValue == val )
		return FALSE;

	val = ( tempValue * 255 ) / 100;
	
	// printf("\r\ntmpval: %d",tempValue);
	// printf("\r\nnval:   %d",val);
	
	g_VideoSetting.VcomDC = val;
	
	#if(SCALER_TYPE == MARIA9)
	
	#if(VCOM_DC_Ctrl == PWM_TYPE_PWM1)
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_F4_PWM1C, g_VideoSetting.VcomDC );
	
	#elif(VCOM_DC_Ctrl == PWM_TYPE_PWM2)
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_F5_PWM2C, g_VideoSetting.VcomDC );
	
	#elif(VCOM_DC_Ctrl == PWM_TYPE_PWM3)
	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
	msWriteByte ( BK3_F4_PWM3C, g_VideoSetting.VcomDC );
	
	#elif(VCOM_DC_Ctrl == PWM_TYPE_PWM4)
	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
	msWriteByte ( BK3_F5_PWM4C, g_VideoSetting.VcomDC );
	#endif
	
	#else
	
	msWriteByte ( BK1_43_BVOM_DC, g_VideoSetting.VcomDC );

	#endif
  
	// NVRam_WriteByte(nvrVideoAddr(VcomDC), g_VideoSetting.VcomDC);
	// g_VideoSetting.Checksum = usrCalCheckSum((BYTE *)&g_VideoSetting, (VideoSettingSize - CheckSumSize));
	// NVRam_WriteByte(nvrVideoAddr(Checksum),  g_VideoSetting.Checksum);

	msWriteByte(BK0_00_REGBK, REG_BANK_SCALER);

	return TRUE;
}

WORD GetVideoVCOMDCValue(void)
{
  return ( (WORD) g_VideoSetting.VcomDC * 100 ) / ( MaxDefBacklightPWM - MinDefBacklightPWM );
}
#endif

