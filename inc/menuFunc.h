
#ifndef _MENUFUNC_H_
#define _MENUFUNC_H_

#ifdef _MENUFUNC_C_
	#define _MENUFUNCDEC_
#else
	#define _MENUFUNCDEC_ extern
#endif

//_MENUFUNCDEC_ BOOL ResetOsdTimer(void)
_MENUFUNCDEC_ WORD GetScale100Value ( WORD value, WORD minValue, WORD maxValue );
_MENUFUNCDEC_ WORD DecIncValue ( MenuItemActionType action, WORD value, WORD minValue, WORD maxValue, BYTE step );
_MENUFUNCDEC_ BOOL EnterRootMenu ( void );

//_MENUFUNCDEC_ WORD GetSourceValue(void);
_MENUFUNCDEC_ BOOL AdjustSource ( void );

_MENUFUNCDEC_ WORD GetSharpnessValue ( void );
_MENUFUNCDEC_ WORD GetSharpnessRealValue ( void );
_MENUFUNCDEC_ BOOL AdjustSharpness ( MenuItemActionType action );

_MENUFUNCDEC_ void resetInput ( void );
_MENUFUNCDEC_ BOOL ResetAllSettings ( void );
_MENUFUNCDEC_ BOOL SwitchSource ( void );

_MENUFUNCDEC_ BYTE usrNonLinearCalculate ( NonLinearCurveType NoLinear, BYTE AdjustValue );

//=====================================================================
//=====================================================================
//=====================================================================
_MENUFUNCDEC_ void SaveUserPref ( void );

_MENUFUNCDEC_ BOOL AdjustContrast ( MenuItemActionType action );
_MENUFUNCDEC_ WORD GetContrastValue ( void );

_MENUFUNCDEC_ BOOL AdjustBrightness ( MenuItemActionType action );
_MENUFUNCDEC_ WORD GetBrightnessValue ( void );

_MENUFUNCDEC_ BOOL AdjustSaturation ( MenuItemActionType action );
_MENUFUNCDEC_ WORD GetSaturationValue ( void );

_MENUFUNCDEC_ WORD GetVideoHueValue ( void );
_MENUFUNCDEC_ BOOL AdjustVideoHue ( MenuItemActionType action );

// _MENUFUNCDEC_ void msSetCCFLBrightness ( void );
_MENUFUNCDEC_ WORD GetBacklightValue ( void );
_MENUFUNCDEC_ BOOL AdjustBacklight ( MenuItemActionType action );

_MENUFUNCDEC_ BOOL AdjustVideoVCOMDC(MenuItemActionType action);
_MENUFUNCDEC_ WORD GetVideoVCOMDCValue(void);

_MENUFUNCDEC_ BOOL AdjustScaling ( MenuItemActionType action );
_MENUFUNCDEC_ WORD GetScalingValue(void);

// _MENUFUNCDEC_ BOOL FineTuneAdjust ( MenuItemActionType action );

_MENUFUNCDEC_ WORD GetChromaModeValue ( void );
_MENUFUNCDEC_ BOOL AdjustChromaMode ( MenuItemActionType action );

// _MENUFUNCDEC_ BOOL EnterPictureMenuExec ( void );

// _MENUFUNCDEC_ BOOL EnterFunctionMenuExec ( void );
// _MENUFUNCDEC_ BOOL EnterSystemMenuExec ( void );

#endif

