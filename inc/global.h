#include "board.h"
#include "mode.h"
#include "userprefdef.h"

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifdef _GLOBAL_C_
	#define _GLOBALDEC_
#else
	#define _GLOBALDEC_ extern
#endif

//_GLOBALDEC_ BYTE XDATA g_ucP4Value;
_GLOBALDEC_ BYTE XDATA g_ucSleepTime;
_GLOBALDEC_ BYTE XDATA VD_Type;
_GLOBALDEC_ bit g_b100mSArrival;
_GLOBALDEC_ BYTE g_ucmSCounter;
_GLOBALDEC_ BYTE XDATA g_uc100mSCounter;
_GLOBALDEC_ BYTE XDATA g_ucSecond;
_GLOBALDEC_ bit g_bForceColorEnable;

_GLOBALDEC_ BYTE XDATA g_ucSyncMaxStableCounter;


#if SYSTEM_BOOT_UP_QUICKLY_ENABLE
	_GLOBALDEC_ BOOL XDATA g_bOSDLoadFlag;
#endif

_GLOBALDEC_ BYTE XDATA g_ucModeDetectCounter;
_GLOBALDEC_ BYTE XDATA g_ucOsdCounter;
_GLOBALDEC_ BYTE XDATA g_ucPowerDownCounter;
_GLOBALDEC_ BYTE XDATA g_ucTimingChangeDebounce;
_GLOBALDEC_ BYTE XDATA g_ucSaveIndex;
_GLOBALDEC_ BYTE XDATA g_ucUratProgramCount;
_GLOBALDEC_ BYTE XDATA g_ucCaptionPosition;
_GLOBALDEC_ BYTE XDATA g_uwSleepTimeCounter;

#if RM_EEPROM_TYPE<RM_TYPE_SST512
	_GLOBALDEC_ BYTE XDATA g_ucLastVideoAGC;
	_GLOBALDEC_ BYTE XDATA g_ucVideoAGCCount;
#endif
_GLOBALDEC_ WORD XDATA g_uwVideoAGC;

_GLOBALDEC_ BYTE XDATA g_ucPhaseErrorDetectCounter;

_GLOBALDEC_ BYTE XDATA g_ucTimeHour;
_GLOBALDEC_ BYTE XDATA g_ucTimeMinute;
_GLOBALDEC_ BYTE XDATA g_ucONTimeHour;
_GLOBALDEC_ BYTE XDATA g_ucONTimeMinute;
_GLOBALDEC_ BYTE XDATA g_ucOFFTimeHour;
_GLOBALDEC_ BYTE XDATA g_ucOFFTimeMinute;

_GLOBALDEC_ BYTE XDATA g_ucSwapLeftSerNum;
_GLOBALDEC_ BYTE XDATA g_ucCopyLeftSerNum;

_GLOBALDEC_ BOOL XDATA g_bTVAutoScanChannelEnable;
_GLOBALDEC_ BOOL XDATA g_bTVManualSearchEnable;
_GLOBALDEC_ BOOL XDATA g_bTVManualStore;
_GLOBALDEC_ BOOL XDATA g_bTVAutoScanChannelBreak;
_GLOBALDEC_ BOOL XDATA g_bTVManualScanChannelBreak;
_GLOBALDEC_ BOOL XDATA g_bManualScanDirection;
_GLOBALDEC_ BYTE XDATA g_ucAFCTuneCounter;
_GLOBALDEC_ BOOL XDATA g_bProgramFlash;
_GLOBALDEC_ BOOL XDATA g_bFlashReadOK;

_GLOBALDEC_ InputModeType code tStandardMode[];
_GLOBALDEC_ InputResolutionType code tStandardModeResolution[];

_GLOBALDEC_ NonLinearCurveType XDATA g_NLCContrast;
_GLOBALDEC_ NonLinearCurveType XDATA g_NLCBrightness;
_GLOBALDEC_ NonLinearCurveType XDATA g_NLCSaturation;


//========================================================================

_GLOBALDEC_ InputTimingType XDATA g_InputTiming;
_GLOBALDEC_ VideoSettingType XDATA g_VideoSetting;
_GLOBALDEC_ ModeSettingType XDATA g_ModeSetting;

_GLOBALDEC_ BYTE g_ucInputTimingStableCounter;
//========================================================================
_GLOBALDEC_ XDATA BYTE g_ucOverScanH;
_GLOBALDEC_ XDATA BYTE g_ucOverScanV;

_GLOBALDEC_ XDATA WORD g_wHorizontalPeriod; // horizontal period, count by reference clock
_GLOBALDEC_ XDATA WORD g_wVerticalTotal; // vertical total, count by HSync

//========================================================================
//yurian for calendar
_GLOBALDEC_ DWORD XDATA temp_total_day;
_GLOBALDEC_ WORD XDATA gc_solar_calendar_year;
_GLOBALDEC_ BYTE XDATA gc_solar_calendar_month;
_GLOBALDEC_ BYTE XDATA gc_solar_calendar_date;
_GLOBALDEC_ BYTE XDATA gc_lunar_calendar_year;
_GLOBALDEC_ BYTE XDATA gc_lunar_calendar_month;
_GLOBALDEC_ BYTE XDATA gc_lunar_calendar_date;
_GLOBALDEC_ BYTE XDATA start_day_of_week;
_GLOBALDEC_ BYTE XDATA gc_lunar_leap_month;
//========================================================================
_GLOBALDEC_ XDATA BYTE g_IrCodeParam[4];
//========================================================================
_GLOBALDEC_ XDATA BYTE ucUartCheckTick;

_GLOBALDEC_ XDATA BYTE g_ucSyncStableCounter;

_GLOBALDEC_ void Init_GlobalVariables ( void );
_GLOBALDEC_ void SlowTimeHandler ( void );

#define DefRedColor 0xAB // 96(0x60)
#define DefGreenColor 0xAB //
#define DefBlueColor 0xAB
#define MaxColorValue 0xFF

#define DefBrightness 50
#define MaxDefBrightness 100
#define MinDefBrightness 0

#define DefContrast 50
#define MaxDefContrast 100
#define MinDefContrast 0

#define DefVideoBrightness 50
#define MaxDefVideoBrightness 100
#define MinDefVideoBrightness 0

#define DefVideoContrast 50
#define MaxDefVideoContrast 100
#define MinDefVideoContrast 0

#define DefBacklight		0x28
#define MaxDefBacklight		0x52
#define MinDefBacklight		0x03

#define DefBacklightPWM		0x3F
#define MaxDefBacklightPWM	0x7F
#define MinDefBacklightPWM	0x02

#define DefVideoSaturation 50
#define MaxDefVideoSaturation 100
#define MinDefVideoSaturation 0

#define DefVideoHue 50
#define MaxDefVideoHue 100
#define MinDefVideoHue 0

#define DefYPbPrBrightness 50
#define MaxDefYPbPrBrightness 100
#define MinDefYPbPrBrightness 0

#define DefYPbPrContrast 50
#define MaxDefYPbPrContrast 100
#define MinDefYPbPrContrast 0

#define DefYPbPrSaturation 50
#define MaxDefYPbPrSaturation 100
#define MinDefYPbPrSaturation 0

#define DefOSDBlend 0
#define MaxOSDBlend 4
#define MinOSDBlend 0

#define ClockAdjRange 100

// Scaling function definition
// Image cutoff ratio for H = 3% (���k�U1.5%)
// Image cutoff ratio for V is not ready
#define SCAL_CUTOFF_H_PER 3
#define SCAL_CUTOFF_V_NUM 6
#define SCAL_CUTOFF_RESOL 100

// Image ratio for H:V = 40:30
#define SCAL_RATIO_NUMERATOR 40
#define SCAL_RATIO_DENOMINATOR 30

// Image ratio for Non-Linear scaling
#define SCAL_NON_LINEAR_RATIO 950
#define SCAL_NON_LINEAR_RESOL 1000

//============================================================================================
// current input timing information
#define SrcHPeriod g_InputTiming.HPeriod
#define SrcVTotal g_InputTiming.VTotal
#define g_ucSrcModeIndex g_InputTiming.ModeIndex
#define SrcFlags g_InputTiming.fFlags

//============================================================================================
#define DefaultVideoModeHTotal 919 //15.6KHz 60Hz
#define DefaultVideoModeVTotal 520
#define DefaultVideoPModeHTotal 454//31.5KHZ 60Hz
#define DefaultVideoPModeVTotal 525
#define DefVideoNtscModeVTotal 525
#define DefVideoPalModeVTotal 625
//============================================================================================
// VESA Standard mode default settings
#define StandardModeWidth tStandardModeResolution[StandardModeGroup].DispWidth
#define StandardModeHeight tStandardModeResolution[StandardModeGroup].DispHeight
#define StandardModeGroup tStandardMode[g_ucSrcModeIndex].ResIndex
#define StandardModeHStart tStandardMode[g_ucSrcModeIndex].HStart
#define StandardModeVStart tStandardMode[g_ucSrcModeIndex].VStart
#define StandardModeHTotal tStandardMode[g_ucSrcModeIndex].HTotal
#define StandardModeHFreq tStandardMode[g_ucSrcModeIndex].HFreq
#define StandardModeFlag tStandardMode[g_ucSrcModeIndex].Flags
#define StandardResolutionText StandardResolutionIndexText[StandardModeGroup]
//============================================================================================
//#define IsSVideoInUse() (g_VideoSetting.InputType==Input_SVIDEO1||g_VideoSetting.InputType==Input_SVIDEO2)
//#define IsTVInUse() (g_VideoSetting.InputType==Input_TV)
//#define IsVGAInUse() (g_VideoSetting.InputType==Input_VGA)
//#define IsCCIR656InUse() (g_VideoSetting.InputType==Input_CCIR656)
//#define IsSVideo1InUse() (g_VideoSetting.InputType==Input_SVIDEO1)
//#define IsSVideo2InUse() (g_VideoSetting.InputType==Input_SVIDEO2)
//#define IsYPbPrInUse() (g_VideoSetting.InputType==Input_YPBPR)

#define IsAVInUse() (g_VideoSetting.InputType == Input_CVBS1 | g_VideoSetting.InputType == Input_CVBS2)
#define IsCVBS1InUse() (g_VideoSetting.InputType == Input_CVBS1)
#define IsCVBS2InUse() (g_VideoSetting.InputType == Input_CVBS2)
#define IsCVBSInUse() (IsAVInUse())
#define IsVideoPortInUse() (IsCVBSInUse())

//#define IsAnalogPortInUse() (IsVGAInUse()||IsYPbPrInUse())
//=========================================================================
#define SyncLoss (bHSyncLoss|bVSyncLoss)
#define SyncPolarity(status) (status&0x03)
#define GetSyncPolarity(status) (1<<(status&0x03))

#define SyncLossState() (SrcFlags&SyncLoss)
#define UserModeFlag (SrcFlags&bUserMode)
#define UnsupportedModeFlag (SrcFlags&bUnsupportMode)

//=========================================================================
// Monitor status flags for storing into NVRAM
#define bPowerOnBit _BIT0 // system power on/off status
#define bFactoryModeBit _BIT1 // factory mode

#define PowerOnFlag (g_VideoSetting.MonitorFlag & bPowerOnBit)
#define Set_PowerOnFlag() (g_VideoSetting.MonitorFlag |= bPowerOnBit)
#define Clr_PowerOnFlag() (g_VideoSetting.MonitorFlag &= ~bPowerOnBit)

//=========================================================

// System status flags
_GLOBALDEC_ bit b_InputTimingChangeBit;
_GLOBALDEC_ bit b_PowerSavingBit;
_GLOBALDEC_ bit b_ForcePowerSavingBit;
_GLOBALDEC_ bit b_InputTimingStableBit;
_GLOBALDEC_ bit b_DoModeSettingBit;
_GLOBALDEC_ bit b_FreeRunModeBit;
_GLOBALDEC_ bit b_OsdTimeoutBit;
_GLOBALDEC_ bit b_SaveSettingBit;
_GLOBALDEC_ bit b_RxBusyBit;
_GLOBALDEC_ bit b_Dynamiccaption;

#define g_bInputTimingChangeFlag (b_InputTimingChangeBit)
#define PowerSavingFlag (b_PowerSavingBit)
#define ForcePowerSavingFlag (b_ForcePowerSavingBit)
#define InputTimingStableFlag (b_InputTimingStableBit)
#define DoModeSettingFlag (b_DoModeSettingBit)
#define FreeRunModeFlag (b_FreeRunModeBit)
#define RxBusyFlag (b_RxBusyBit)
#define OsdTimeoutFlag (b_OsdTimeoutBit)
#define SaveSettingFlag (b_SaveSettingBit)
#define DynamiccaptionFlag (b_Dynamiccaption)

#if Enable_Logo_Display
	_GLOBALDEC_ bit b_DrawLogoFlag;
	_GLOBALDEC_ bit b_OSDInitFlag;
	_GLOBALDEC_ BYTE XDATA ucLogoDisplayCounter;

	#define DrawLogoFlag (b_DrawLogoFlag)
	#define OSDInitFlag (b_OSDInitFlag)

	#define Set_OSDInitFlag() (b_OSDInitFlag=1)
	#define Clr_OSDInitFlag() (b_OSDInitFlag=0)

	#define Set_DrawLogoFlag() (b_DrawLogoFlag=1)
	#define Clr_DrawLogoFlag() (b_DrawLogoFlag=0)
#endif

#define Set_InputTimingChangedFlag() (b_InputTimingChangeBit=1)
#define Clr_InputTimingChangeFlag() (b_InputTimingChangeBit=0)

#define Set_PowerSavingFlag() (b_PowerSavingBit=1)
#define Clr_PowerSavingFlag() (b_PowerSavingBit=0)

#define Set_ForcePowerSavingFlag() (b_ForcePowerSavingBit=1)
#define Clr_ForcePowerSavingFlag() (b_ForcePowerSavingBit=0)

#define Set_InputTimingStableFlag() (b_InputTimingStableBit=1)
#define Clr_InputTimingStableFlag() (b_InputTimingStableBit=0)

#define Set_RxBusyFlag() (b_RxBusyBit=1)
#define Clr_RxBusyFlag() (b_RxBusyBit=0)

#define Set_DoModeSettingFlag() (b_DoModeSettingBit=1)
#define Clr_DoModeSettingFlag() (b_DoModeSettingBit=0)

#define Set_OsdTimeoutFlag() (b_OsdTimeoutBit=1)
#define Clr_OsdTimeoutFlag() (b_OsdTimeoutBit=0)

#define Set_FreeRunModeFlag() (b_FreeRunModeBit=1)
#define Clr_FreeRunModeFlag() (b_FreeRunModeBit=0)

#define Set_SaveSettingFlag() (b_SaveSettingBit=1)
#define Clr_SaveSettingFlag() (b_SaveSettingBit=0)

#define Set_DynamiccaptionFlag() (b_Dynamiccaption=1)
#define Clr_DynamiccaptionFlag() (b_Dynamiccaption=0)

//TVSystemFlag
_GLOBALDEC_ bit b_AFCDisableBit;
_GLOBALDEC_ bit b_ChannelAFCBit;
_GLOBALDEC_ bit b_ShowSourceFlagBit;
_GLOBALDEC_ bit b_ReDrawCurrentOSDBit;
_GLOBALDEC_ bit b_ChannelChangeFlagbit;
_GLOBALDEC_ bit b_SourceChangedFlagbit;

_GLOBALDEC_ bit b_TurnOnPanelFlagbit; // fast start ,for show the osd

#define AFCDisableFlag b_AFCDisableBit
#define ShowSourceFlag b_ShowSourceFlagBit
#define ReDrawCurrentOSDFlag b_ReDrawCurrentOSDBit

#define SourceChangedFlag b_SourceChangedFlagbit

#define Set_AFCDisableFlag() (b_AFCDisableBit=1)
#define Clr_AFCDisableFlag() (b_AFCDisableBit=0)

#define Set_ShowSourceFlag() (b_ShowSourceFlagBit=1)
#define Clr_ShowSourceFlag() (b_ShowSourceFlagBit=0)

#define Set_ReDrawCurrentOSDFlag() (b_ReDrawCurrentOSDBit=1)
#define Clr_ReDrawCurrentOSDFlag() (b_ReDrawCurrentOSDBit=0)

#define Set_SourceChangedFlag() (b_SourceChangedFlagbit = 1)
#define Clr_SourceChangedFlag() (b_SourceChangedFlagbit = 0)

//----------------------------------------------------------------

_GLOBALDEC_ BYTE XDATA g_ucTimerFlag;

#define b_SleepBit _BIT0
#define b_EnableTimeBit _BIT1
#define b_EnableOFFTimeBit _BIT2
#define b_EnableONTimeBit _BIT3
#define b_ForcePowerONFlagbit _BIT4
#define b_PowerONTimeEnableBit _BIT5
#define b_PowerOFFTimeEnableBit _BIT6

#define SleepFlag (g_ucTimerFlag&b_SleepBit)
#define EnableTimeFlag (g_ucTimerFlag&b_EnableTimeBit)
#define EnableOFFTimeFlag (g_ucTimerFlag&b_EnableOFFTimeBit)
#define EnableONTimeFlag (g_ucTimerFlag&b_EnableONTimeBit)
#define ForcePowerONFlag (g_ucTimerFlag&b_ForcePowerONFlagbit)
#define PowerONTimeEnableFlag (g_ucTimerFlag&b_PowerONTimeEnableBit)
#define PowerOFFTimeEnableFlag (g_ucTimerFlag&b_PowerOFFTimeEnableBit)


#define Set_SleepTimeoutFlag() (g_ucTimerFlag|=b_SleepBit)
#define Clr_SleepTimeoutFlag() (g_ucTimerFlag&=~b_SleepBit)

#define Set_EnableTimeFlag() (g_ucTimerFlag|=b_EnableTimeBit)
#define Clr_EnableTimeFlag() (g_ucTimerFlag&=~b_EnableTimeBit)

#define Set_EnableOFFTimeFlag() (g_ucTimerFlag|=b_EnableOFFTimeBit)
#define Clr_EnableOFFTimeFlag() (g_ucTimerFlag&=~b_EnableOFFTimeBit)

#define Set_EnableONTimeFlag() (g_ucTimerFlag|=b_EnableONTimeBit)
#define Clr_EnableONTimeFlag() (g_ucTimerFlag&=~b_EnableONTimeBit)

#define Set_ForcePowerONFlag() (g_ucTimerFlag|=b_ForcePowerONFlagbit)
#define Clr_ForcePowerONFlag() (g_ucTimerFlag&=~b_ForcePowerONFlagbit)

#define Set_PowerONTimeEnableFlag() (g_ucTimerFlag|=b_PowerONTimeEnableBit)
#define Clr_PowerONTimeEnableFlag() (g_ucTimerFlag&=~b_PowerONTimeEnableBit)

#define Set_PowerOFFTimeEnableFlag() (g_ucTimerFlag|=b_PowerOFFTimeEnableBit)
#define Clr_PowerOFFTimeEnableFlag() (g_ucTimerFlag&=~b_PowerOFFTimeEnableBit)


#endif
