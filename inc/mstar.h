#ifndef _MSTAR_H_
#define _MSTAR_H_

#ifdef _MSTAR_C_
	#define _MSCTLDEC_
#else
	#define _MSCTLDEC_ extern
#endif

typedef enum
{
	FPLL_STOP,
	// FPLL_TUNE_CLK_ONLY,
	FPLL_TUNE_LINE_ONLY,
	FPLL_TUNE_CLK_LINE_FOR_PC_YPBPR,
	FPLL_TUNE_CLK_LINE_FOR_VIDEO,
} EnuFpllCtl;

// interrrupt setting
typedef enum _msInterruptType
{
	INTERRUPT_DISABLE,
	INTERRUPT_PC, // V change,H loss,V loss
	INTERRUPT_YPBPR, // H loss,V loss
	INTERRUPT_INPUT_VSYNC
} msInterruptType;

#define LONG_COUNT_HPERIOD_ON _BIT0
#define LONG_COUNT_HPERIOD_OFF 0
#define LONG_COUNT_CAL_ON _BIT1
#define LONG_COUNT_CAL_OFF 0

#define V_CAP_SIZE_SAFE_RANGE 25

#define MST_H_PERIOD_MASK 0x1fff
#define MST_V_TOTAL_MASK 0x07ff

typedef struct
{
	BOOL bInterlace;
	WORD inHPeriod;
	DWORD inHFreq;
	WORD inVTotal;
	BYTE inOutVFreq;
} StruInOutCtl;

_MSCTLDEC_ XDATA StruInOutCtl g_InOutCtl;

#define SCALING_RATIO_TYPE_NATIVE 0
#define SCALING_RATIO_TYPE_UP 1
#define SCALING_RATIO_TYPE_DOWN 2
#define SCALING_RATIO_FLAG_PRE _BIT2

typedef struct
{
	WORD H_CapStart;
	WORD V_CapStart;
	WORD H_CapSize;
	WORD V_CapSize;
	WORD V_DisSize;
	BYTE H_ScalingRatioInfo;
	BYTE V_ScalingRatioInfo;
} _WindowType;

_MSCTLDEC_ XDATA _WindowType g_WindowInfo;

#define SCALING_H_IN (g_WindowInfo.H_CapSize)
#define SCALING_H_OUT (PanelWidth)

#define SCALING_V_IN (g_WindowInfo.V_CapSize)
#define SCALING_V_OUT (g_WindowInfo.V_DisSize)

#define ScalingRatio_H( Input, Output ) ( ((DWORD) Output - 1 ) * 1048576ul / ( Input - 1 ) + 1 )
#define ScalingRatio_V( Input, Output ) ( ((DWORD) Input - 1 ) * 1048576ul / ( Output - 1 ) + 1 )

#define PRE_SCALING_RATIO_V(Input, Output) ( ((DWORD)Output) * 1048576ul / (Input) + 1 )


#if(ENABLE_MONITOR_VTOTAL)

	_DEVVDDEC_ void msMonitorVTotal ( BYTE ucFlag ); // Protect V capture size

#endif


#if(ENABLE_CHECK_AUTO_H_TOTAL) // Protect panel crash when mode change

_MSCTLDEC_ XDATA BOOL g_ucBK0_57_Value;
_MSCTLDEC_ XDATA BOOL g_bEnableAutoHTotal;
_MSCTLDEC_ XDATA BYTE g_ucCheckSyncCounter;
_MSCTLDEC_ XDATA BYTE g_wCheckBK0_57_Timer;
_MSCTLDEC_ void msCheckBK0_57_Value ( void );
_MSCTLDEC_ WORD msCalculateVFreqX10 ( WORD wHFreq, WORD wVTotal );

#endif

_MSCTLDEC_ void Delay1ms_AGC_Processor ( WORD wDelaycount );


_MSCTLDEC_ void msSetBacklight ( BYTE val );

_MSCTLDEC_ void msInit ( void );
_MSCTLDEC_ void OSDGammaInit ( void );
_MSCTLDEC_ void msPrepareForTimingChange ( void );
_MSCTLDEC_ void msPowerDown ( void );
_MSCTLDEC_ void msSoftwareReset ( BYTE wParam, BYTE ucDelayTime );
_MSCTLDEC_ void msPowerUp ( void );
_MSCTLDEC_ void msSetupInputPort ( void );
_MSCTLDEC_ void msSetInterrupt ( msInterruptType IntSel );
_MSCTLDEC_ void msSetupFreeRunMode ( BYTE ucVFreq );

_MSCTLDEC_ void msCheckCaptureSize ( void );

_MSCTLDEC_ void msInitTCON ( void );
_MSCTLDEC_ void msInitGamma ( void );
_MSCTLDEC_ void SetChromaMode ( void );
_MSCTLDEC_ void msLineBufferDelayCtl ( BOOL bInterlace );
_MSCTLDEC_ void SystemDelay_translate_To_Dsp_Processor ( BYTE wDelaycount );

_MSCTLDEC_ WORD msGetHorizontalPeriod ( void );
_MSCTLDEC_ WORD msGetVerticalTotal ( void );
_MSCTLDEC_ void GetInputSignalHV ( void );
_MSCTLDEC_ void msSetOutputSyncControl ( BYTE ucOutputTimingCtl );
_MSCTLDEC_ void SetScalingRatio ( BOOL bInterlace );
_MSCTLDEC_ void CalculateAspectRatio();
_MSCTLDEC_ void msSetOutputTiming ( BYTE ucOutputTimingCtl );
_MSCTLDEC_ void SetCaptureWindow();
_MSCTLDEC_ void SetDisplayWindow();

_MSCTLDEC_ void msProgDigitalWin ( BYTE ucOutputTimingCtl );

_MSCTLDEC_ void SetOutputTimingAndWindow ( BYTE ucOutputTimingCtl );
_MSCTLDEC_ void msSetLineBufferClock ( BYTE ucModeIdx, BYTE ucOutputClock );
_MSCTLDEC_ void msSetOutputFreeRunClock ( BYTE ucVFreq );
_MSCTLDEC_ void SetOutputClock ( BYTE ucOutputTimingCtl );
_MSCTLDEC_ void msLCDSetClock ( void );
_MSCTLDEC_ BOOL IsSrcHasSignal ( void );

_MSCTLDEC_ WORD GetStdModeHFreq ( BYTE ucModeIdx );
_MSCTLDEC_ WORD GetStdModeHTotal ( BYTE ucModeIdx );
_MSCTLDEC_ WORD GetStdModeHStart ( BYTE ucModeIdx );
_MSCTLDEC_ WORD GetStdModeVStart ( BYTE ucModeIdx );

_MSCTLDEC_ WORD msCalculateHFreqX10 ( WORD wHPeriod );
_MSCTLDEC_ BYTE msCalculateVSyncTime ( void );
_MSCTLDEC_ void msSetScaler ( void );

#endif
