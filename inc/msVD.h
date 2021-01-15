#ifndef _MSVD_H_
#define _MSVD_H_

#ifdef _MSVD_C_
	#define _MSVDDEC_
#else
	#define _MSVDDEC_ extern
#endif

_MSVDDEC_ XDATA BYTE g_ucNoiseDebounce;
_MSVDDEC_ bit bNoisy_Det;
_MSVDDEC_ XDATA BOOL bLastNoisyStatus;

#define ENABLE_PAL_SWITCH_HANDLER 0
#define ENABLE_SW_DETECT_COLOR_STD 0

#if( ENABLE_SW_DETECT_COLOR_STD == 1)

	#define DSP_COLOR_UNKNOWN 0
	#define DSP_COLOR_NTSC 1
	#define DSP_COLOR_PAL 2
	#define COLOR_STD_COUNT_MAX 20
	#define ENABLE_DEBUG_SW_DETECT_COLOR_STD 1

	_MSVDDEC_ XDATA BYTE g_ucVD_ColorStd;
	_MSVDDEC_ XDATA BYTE g_ucVD_ColorStdNew;
	_MSVDDEC_ XDATA BYTE g_ucVD_ColorStdChangeCounter;

	_MSVDDEC_ XDATA BYTE g_ucVD_ColorStdCounter;
	_MSVDDEC_ XDATA BYTE g_ucVD_ColorStdCounter_Unknown;
	_MSVDDEC_ XDATA BYTE g_ucVD_ColorStdCounter_Ntsc;
	_MSVDDEC_ XDATA BYTE g_ucVD_ColorStdCounter_Pal;

	#if( ENABLE_DEBUG_SW_DETECT_COLOR_STD == 1)
		_MSVDDEC_ XDATA BYTE g_ucVD_ColorStdCounterL_Unknown;
		_MSVDDEC_ XDATA BYTE g_ucVD_ColorStdCounterL_Ntsc;
		_MSVDDEC_ XDATA BYTE g_ucVD_ColorStdCounterL_Pal;
	#endif

	_MSVDDEC_ void msVDDetectColorStdInit ( void );
	_MSVDDEC_ void msVDDetectColorStd ( void );

#endif

typedef enum
{
	PAL_SWITCH_AUTO,
	PAL_SWITCH_FORCE_PAL,
	PAL_SWITCH_FORCE_NTSC,
	PAL_SWITCH_FORCE_NUM,
} PAL_SWITCH_FORCE_Type;

#if( ENABLE_PAL_SWITCH_HANDLER == 1)

	_MSVDDEC_ XDATA BYTE g_ucPalSwitchHandler_Timer;
	_MSVDDEC_ void msVDPalSwitchHandlerReset ( BYTE ucCtl );
	_MSVDDEC_ void msVDPalSwitchHandler ( void );
	_MSVDDEC_ void msVDPalSwitchCtl ( BYTE ucCtl );

#endif

//_MSVDDEC_ void CheckDSPVSYNC ( void );
_MSVDDEC_ void msVDReset ( void );
_MSVDDEC_ void msVD_FSM_Reset ( void );

#endif
