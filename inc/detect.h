#if(VGA_ENABLE||YPBPR_ENABLE)

#ifndef _DETECT_H_
#define _DETECT_H_

#ifdef _DETECT_C_
#define _DETECTDEC_
#else
#define _DETECTDEC_ extern
#endif



#define HPeriod_tolerance 15//10 // for mode change
#define VTotal_tolerance 15//10 // for mode change
// time of one loop is 34 when no input
#define ValidTimingStableCount 15//5//15
#define SyncLossStableCount 30//5//30

//#define HFreq_tolerance 15//15 // 1.5 KHz
//#define VFreq_tolerance 15//15 // 1.5 Hz
#define VTotal_Delta 50

#if (SCALER_TYPE == MARIA9)
#define MaxInputHFreq 855 // 80.0 KHz
#else
#define MaxInputHFreq 550//855 // 80.0 KHz
#endif
#define MinInputHFreq 100 //285 // 28.5 KHz
#if (SCALER_TYPE == MARIA9)
#define MaxInputVFreq 755//750 //
#define MinInputVFreq 470 // 50.0 Hz
#else
#define MaxInputVFreq 735 //
#define MinInputVFreq 400 // 50.0 Hz
#endif

_DETECTDEC_ void msMonitorInputTiming ( void );
_DETECTDEC_ void msModeHandler ( void );
_DETECTDEC_ BOOL msValidTimingDetect ( void );
_DETECTDEC_ BYTE msFineTuneDVIPhase ( BYTE channelReg, BYTE channel );
_DETECTDEC_ void msVideoModeHandler ( void );
_DETECTDEC_ BOOL msFindMode ( void );
_DETECTDEC_ BYTE msGetInputStatus ( void );
_DETECTDEC_ BOOL msSyncLossStateDetect ( void );
_DETECTDEC_ BOOL msValidTimingDetect ( void );
_DETECTDEC_ void msSetupADC ( void );
_DETECTDEC_ BOOL msSetupMode ( void );
_DETECTDEC_ void Menu_InitAction ( void );
_DETECTDEC_ BYTE msCalculateVSyncTime ( void );

_DETECTDEC_ void msProgAnalogWin();
_DETECTDEC_ WORD GetStdModeResH ( BYTE ucModeIdx );
_DETECTDEC_ WORD GetStdModeResV ( BYTE ucModeIdx );
_DETECTDEC_ WORD GetStdModeHStart ( BYTE ucModeIdx );
_DETECTDEC_ WORD GetStdModeVStart ( BYTE ucModeIdx );

#endif

#endif
