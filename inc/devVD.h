#ifndef _DEVVD_H_
#define _DEVVD_H_

#ifdef _DEVVD_C_
	#define _DEVVDDEC_
#else
	#define _DEVVDDEC_ extern
#endif

#ifdef _MSVD_C_
	#define _MSVDDEC_
#else
	#define _MSVDDEC_ extern
#endif


typedef enum _vdSignalType
{
	SIG_NTSC,// M
	SIG_PAL,// B/G, D/K, I, H, N
	SIG_NUMS, // signal number
	SIG_NONE = -1
} vdSignalType;


typedef enum _FreeRunBoardColor
{
	FR_BLACK,
	FR_WHITE,
	FR_BLUE,
} FreeRunBoardColor;

typedef enum _LPFCtrlType
{
	LPF_CTL_VD_358,
	LPF_CTL_VD_443,
	LPF_CTL_TV_STRONG,
	LPF_CTL_TV_NORMAL,
	LPF_CTL_TURN_OFF = 0xff
} LPFCtrlType;

typedef enum _VdFroceFscType
{
	VD_FORCE_FSC_443,
	VD_FORCE_FSC_358
} VdFroceFscType;

typedef enum _MSVDCombLineBufCtlType
{
	MSVD_COMB_LINE_BUFFER_CTL_HW_AUTO,
	MSVD_COMB_LINE_BUFFER_CTL_SW
} MSVDCombLineBufCtlType;
typedef struct _StuVDInfo
{
	WORD wVideoStatus;
	vdSignalType ucVideoSystem;
	BYTE ucVideoStableCounter;
	BYTE ucVideoPollingCounter;
	BOOL bVideoDoModeSetting;
} StuVDInfo;

typedef struct _StuVideoSystemInfo
{
	WORD _wHTotal;
	WORD _wHActive;
} StuVideoSystemInfo;

typedef struct _StuCCIR656Info
{
	BYTE ucSyncStatus;
	BYTE ucSystemFlag;
	BOOL bNoSyncstable;
	BOOL bSyncstable;
	BYTE ucSyncStableCounter;
	BYTE ucNoSyncStableCounter;
} StuCCIR656Info;

// Definition
// video decoder status
#define VD_HSYNC_LOCKED _BIT15
#define VD_SYNC_LOCKED _BIT14

#define VD_VSYNC_50HZ _BIT13
#define VD_INTERLACED _BIT12
#define VD_MACROVISION _BIT11

#define VD_COLOR_LOCKED _BIT9
#define VD_PAL_SWITCH _BIT8

#define VD_FSC_TYPE ( _BIT7 | _BIT6 | _BIT5 | _BIT4 )

#define VD_FSC_3579 ( _BIT4 ) // NTSC
#define VD_FSC_4433 ( _BIT5 ) // PAL
#define VD_FSC_NONE ( _BIT6 ) // NONE

//#define VD_FSC_3582 ( _BIT5 ) // PAL(Nc)
//#define VD_FSC_4285 ( _BIT6 | _BIT7 ) // SECAM
//#define VD_FSC_4XXX ( _BIT6 )

#define VD_RESET_ON _BIT3
#define VD_STD_TYPE 0x0007


//#define VD_MODE_DETECT_MASK (VD_HSYNC_LOCKED|VD_VSYNC_50HZ|VD_FSC_TYPE|VD_PAL_SWITCH|VD_RESET_ON)
#define VD_MODE_DETECT_MASK ( VD_HSYNC_LOCKED | VD_VSYNC_50HZ | (_BIT6|_BIT7) | VD_PAL_SWITCH | VD_RESET_ON )

// Video status 2 for Debug
#define VD_H_PERIOD_INVALID _BIT0
#define VD_H_FREQ_INVALID _BIT1
#define VD_V_TOTAL_INVALID _BIT2
#define VD_V_FREQ_INVALID _BIT3

// video polling

#if SYSTEM_BOOT_UP_QUICKLY_ENABLE
	#define VD_NO_INPUT_STABLE_COUNT 7
	#define VD_INPUT_STABLE_COUNT 7
#else
	#define VD_NO_INPUT_STABLE_COUNT 20
	#define VD_INPUT_STABLE_COUNT 20
#endif

// csrf
#undef VD_INPUT_STABLE_COUNT
#define VD_INPUT_STABLE_COUNT 7

#define VD_VSYNC_CHANGE_COUNT 3
#define VD_FORCE_AUTO 0
#define VD_FORCE_PAL 1 // 443 50Hz
#define VD_FORCE_NTSC_443 2 // 443 60Hz
#define VD_FORCE_PAL_358 3 // 358 ( 60Hz -> PAL_M, 50Hz -> PAL_NC )
#define VD_FORCE_NTSC 4 // 358 60Hz
#define VD_FORCE_SECAM 5 // 428 50Hz
_DEVVDDEC_ XDATA BYTE g_ucMSVDForceSystem;


#define VD_PATCH_001 // PAL-N -> (PAL+No burst) ==> VD state machine abnormal
// #define VD_PATCH_002 // PAL-M -> NTSC ==> VD color abnormal
// #define VD_PATCH_003 // NTSC -> PAL-M ==> VD color abnormal
// #define VD_PATCH_004 // NTSC <-> PAL ==> Scaler Vtotal != VD vtotal
// #define VD_PATCH_005 // VD output H freq abnormal

#define ENABLE_MONITOR_SIGNAL 1
#if( ENABLE_MONITOR_SIGNAL )
	_DEVVDDEC_ XDATA WORD g_wMonitorSignal_Timer;
	#define MONITOR_SIGNAL_INIT _BIT7
	_DEVVDDEC_ void msMonitorSignal ( BYTE ucFlag );
#endif


#define VTotaltolerance 10

#define VD_COLOR_BURST_HANDLER_RESET _BIT7

#define ENABLE_FOLLOW_MODE_AUTO_CLOCK 1

#define MSVD_CTL_FLAG_VSYNC _BIT0
#define MSVD_CTL_FLAG_DSP_STD _BIT1
#define MSVD_CTL_FLAG_FSC_DETECT _BIT2
#define MSVD_CTL_FLAG_ACC _BIT3
#define MSVD_CTL_FLAG_COLOR_BURST_HANDLER _BIT4
#define MSVD_CTL_FLAG_NOISE_HANDLER _BIT5
#define MSVD_CTL_FLAG_COMB_LINE_BUF _BIT6
#define MSVD_CTL_FLAG_COMB_HANDLER _BIT7

#define MSVD_CTL2_FLAG_AGC_MONITOR _BIT0
#define MSVD_CTL2_FLAG_AGC_PROCESSOR _BIT1
#define MSVD_CTL2_FLAG_VCR _BIT2
#define MSVD_CTL2_FLAG_SECAM _BIT3
#define MSVD_CTL2_FLAG_HSYNC _BIT4
#define MSVD_CTL2_FLAG_PATCH5 _BIT5
#define MSVD_CTL2_FLAG_PAL_SWITCH _BIT6
#define MSVD_CTL2_FLAG_AFEC _BIT7

#define DSP_RUN_MODE_NONE 1
#define DSP_RUN_MODE_POLLING 2
//#define DSP_RUN_MODE_INT 3
#define DSP_RUN_MODE_TIMER_AND_POLLING 4

#if( ENABLE_VD_DSP )
	#define DSP_RUN_MODE DSP_RUN_MODE_TIMER_AND_POLLING
#else
	#define DSP_RUN_MODE DSP_RUN_MODE_NONE
#endif

#define OUTPUT_SIG 0
#define OUTPUT_FREERUN _BIT0
#define OUTPUT_SNOW _BIT1

#define AFCTUNEINITCOUNT 0x80
#define AFCTUNERANGE 20
#define AFCTUNEMINCOUNT AFCTUNEINITCOUNT-AFCTUNERANGE
#define AFCTUNEMAXCOUNT AFCTUNEINITCOUNT+AFCTUNERANGE

_DEVVDDEC_ BYTE g_ucmsVDCtl2;
_DEVVDDEC_ BYTE g_ucmsVDCtl;

_DEVVDDEC_ XDATA BOOL g_bVDCurLineLockStatus;
_DEVVDDEC_ bit g_bVDColorBurstHandler_LastColorBurstStatus;
_DEVVDDEC_ bit g_bDetectInterlace_LastInterlaceFlag;
_DEVVDDEC_ XDATA BYTE g_ucMSVDSwitchLineLockCnt;
_DEVVDDEC_ XDATA WORD g_wVDColorBurstHandlerTimer;
_DEVVDDEC_ XDATA BYTE g_ucVDColorBurstHandlerStableCounter;
_DEVVDDEC_ XDATA StuVDInfo g_VdInfo;
_DEVVDDEC_ XDATA BYTE g_ucAGCGain;
_DEVVDDEC_ XDATA WORD g_wLastSyncStatus;

#ifdef VD_PATCH_002
	_DEVVDDEC_ XDATA BYTE g_msVD_Patch002_LastVideoSystem;
#endif

_DEVVDDEC_ XDATA BYTE g_ucMSVDNoiseHandlerTimer;

#if CCIR656_ENABLE
	_DEVVDDEC_ XDATA StuCCIR656Info g_CCIR656Info;
#endif

#define VSYNC_NEGATIVE_B _BIT0
#define HSYNC_NEGATIVE_B _BIT1
#define DEMODULATION_MODE1_B _BIT2
#define INTERLANCE_MODE_B _BIT3
#define CSYNC_MODE_B _BIT4
#define PAL_MODE_B _BIT5
#define NO_HSYNC_B _BIT6
#define NO_VSYNC_B _BIT7
#define SYNC_LOSS_MASK (NO_HSYNC_B+NO_VSYNC_B)

#define SYNC_CHECK_TIMES 20
#define SYNC_STABLE_TIMES 6

#define INPUT_TIMING_CHANGE_FLAG _BIT0
#define NO_INPUT_SIGNAL_FLAG _BIT1
#define INPUT_SIGNAL_STABLE_FLAG _BIT2
#define SAVE_SETTING_FLAG _BIT3
#define FIRST_AC_ON_FLAG _BIT4
#define ENTER_SPI_DEBUG _BIT5

_DEVVDDEC_ BYTE msSyncDetect ( void );
_DEVVDDEC_ void msCCIR656Detect ( void );
_DEVVDDEC_ void msCCIR656ModeHandler ( void );
//========================================================================

_DEVVDDEC_ BOOL msForceChromaDetect ( BYTE ucSignalType );
_DEVVDDEC_ void msForceFSC( BYTE ucVidType);

_DEVVDDEC_ void msVDNoiseHandlerInit ( void );
_DEVVDDEC_ void msVDNoiseHandler ( void );
_DEVVDDEC_ void msVDNoiseHandlerReset ( void );

_DEVVDDEC_ void msVDDSPWriteByte ( BYTE ucAddr, BYTE ucData );
_DEVVDDEC_ BYTE msDecoderSyncDetect ( void );
//_DEVVDDEC_ void SetColorSystem(StuChannelData ChannelData);
_DEVVDDEC_ void vdMonitorInput ( void );
_DEVVDDEC_ void vdModeHandler ( void );
_DEVVDDEC_ void vdInitVariable ( void );
_DEVVDDEC_ void msVDColorKill ( BOOL bColorKill );
_DEVVDDEC_ void msLPFCtl ( BYTE ucLPFParaIdx );
_DEVVDDEC_ void msVDColorBurstHandler ( BYTE ucFlag );
_DEVVDDEC_ WORD msVDGetSyncStatus ( void );
_DEVVDDEC_ BOOL msVDGetSyncStable ( BYTE ucStableCount, BYTE wMaxTime );
_DEVVDDEC_ void msFieldDetectCtl ( void );
_DEVVDDEC_ BYTE msVDGetVideoSystem ( WORD wVideoStatus );
_DEVVDDEC_ WORD msVDDSPRead2Bytes ( BYTE ucAddr );
_DEVVDDEC_ BYTE msVDDSPReadByte ( BYTE ucAddr );
_DEVVDDEC_ void msVDCombLineBufferCtl ( BYTE flag );
_DEVVDDEC_ bit msVDGetColorLockBit ( void );
_DEVVDDEC_ void msVDSetupMode ( WORD wStatus, BYTE ucSignalType );

_DEVVDDEC_ BOOL msGetInterlaceBit ( void );
_DEVVDDEC_ void msDetectInterlace ( BYTE ucFlag );

_DEVVDDEC_ void msSetBlueScreen ( BOOL bEnable, BYTE ucColor );
_DEVVDDEC_ void msCommSetupMode ( void );
_DEVVDDEC_ void msVDForceSystem ( BYTE ucSystem );

_DEVVDDEC_ void msVDLineLockCtl ( BOOL bLock );
_DEVVDDEC_ void PrintVDStatus ( WORD wStatus );
_DEVVDDEC_ WORD msVDGetVTotal ( void );
_DEVVDDEC_ BYTE msVDSpecialRead ( BYTE ucMux, BYTE ucAddr );

_DEVVDDEC_ void msVDCombHandler ( void );
_DEVVDDEC_ WORD msGetVideoHPeriod ( BYTE ucFlag );
_DEVVDDEC_ void Fsm_ResetHandle ( void );

#define ENABLE_VCR_HANDLER 0

#if(ENABLE_VCR_HANDLER)
	_DEVVDDEC_ XDATA BYTE g_ucVDVCRHandler_Ctl;
	//_DEVVDDEC_ XDATA BYTE g_ucVDVCRHandler_Timer;
	#define MSVD_VCR_CTL_HW_AUTO 0
	#define MSVD_VCR_CTL_SW_AUTO 1
	#define MSVD_VCR_CTL_FORCE_NON_VCR 2
	#define MSVD_VCR_CTL_FORCE_VCR 3
	_DEVVDDEC_ void msVDVCRHandler ( void );
#endif

#define ENABLE_HSYNC_HANDLER 1

#if( ENABLE_HSYNC_HANDLER )
	_DEVVDDEC_ XDATA BYTE g_ucVDHSyncHandler_Timer;
	void msVDHSyncHandlerReset ( void );
	void msVDHSyncHandler ( void );
#endif

//_DEVVDDEC_ XDATA BYTE g_ucAFECHnadler_Timer;
_DEVVDDEC_ XDATA BYTE g_ucAFECHnadler_LaseDplSel;
_DEVVDDEC_ void msVDAFECHandler ( void );

#ifdef VD_PATCH_001
	// Call this function one time when no signal
	_DEVVDDEC_ BOOL msVD_Patch_001 ( void );
#endif

#ifdef VD_PATCH_002
	// Call this function when mode change!
	_DEVVDDEC_ BOOL msVD_Patch_002 ( WORD wVDStatus );
#endif

#ifdef VD_PATCH_003
	_DEVVDDEC_ BOOL msVD_Patch_003 ( BYTE ucFlag );
#endif

#ifdef VD_PATCH_004
	_DEVVDDEC_ void msVD_Patch_004 ( BOOL bEnable );
#endif

#ifdef VD_PATCH_005
	_DEVVDDEC_ XDATA BYTE g_msVD_Patch005_Timer;
	_DEVVDDEC_ void msVD_Patch_005 ( BYTE ucResetTime );
#endif

_DEVVDDEC_ XDATA BYTE g_ucMSVDDebug; // For debug
_DEVVDDEC_ XDATA BYTE g_ucMSVDDebug2; // For debug

_DEVVDDEC_ BYTE msVDCheckScalerStatus ( BYTE ucCheckFlag );
_DEVVDDEC_ void msVideoAGCHandle ( void );

#endif
