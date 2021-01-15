#if(VGA_ENABLE||YPBPR_ENABLE)

#ifndef _AUTOFUNC_H_
#define _AUTOFUNC_H_

#ifdef _AUTOFUNC_C_
	#define _AUTOFUNCDEC_
#else
	#define _AUTOFUNCDEC_ extern
#endif

// Option
//#define AUTO_DEBUG_EN
#define AUTO_PHASE_METHOD 0 // 0 = found maximum
// 1 = found minimum
#define ADJUST_CLOCK_RANGE 100

// combination 4 bytes
typedef union _DWordType
{
	struct
	{
		BYTE _byte3;
		BYTE _byte2;
		BYTE _byte1;
		BYTE _byte0;
	} separate;

	DWORD total;
} DWordType;

typedef enum _AutoTuneType
{
	AUTO_TUNE_NULL = 0x00,

	// Basic auto-tune
	AUTO_TUNE_VALID_DATA = _BIT0,
	AUTO_TUNE_POSITION = _BIT1,
	AUTO_TUNE_FREQ = _BIT2,
	AUTO_TUNE_PHASE = _BIT3,
	AUTO_TUNE_BASIC = _BIT0 | _BIT1 | _BIT2 | _BIT3,

	// Auto-tune RGB Color
	AUTO_TUNE_RGB_OFFSET = _BIT4,
	AUTO_TUNE_RGB_GAIN = _BIT5,
	AUTO_TUNE_RGB_COLOR = _BIT4 | _BIT5,

	// Auto-tune YUV Color
	AUTO_TUNE_YUV_COLOR = _BIT6,

	// Advance auto-tune
	AUTO_TUNE_ADVANCE = _BIT0 | _BIT1 | _BIT2 | _BIT3 | _BIT4 | _BIT5
} AutoTuneType;

// Generator (Pattern name) Y level PbPr level
// FLUKE 54200 SMTPE 100 IRE 75 IRE
// FLUKE 54200 COL_75_0 75 IRE 75 IRE
// FLUKE 54200 COL_100_0 100 IRE 75 IRE
// QuantumData TVBar100 100 IRE 100 IRE
// QuantumData TVBar_75 100 IRE 75 IRE

#define Y_AUTO_COLOR_75IRE 0 // 0: 100IRE / 1: 75IRE
#define PbPr_AUTO_COLOR_75IRE 0//1 // 0: 100IRE / 1: 75IRE

#if Y_AUTO_COLOR_75IRE
	#define Y_MAX_VALUE 180 // For 75IRE Y value
	#define Y_MIN_VALUE 16
#else
	#define Y_MAX_VALUE 235 // For 100IRE Y value
	#define Y_MIN_VALUE 16
#endif

#if PbPr_AUTO_COLOR_75IRE
	#define PbPr_MAX_VALUE 212 // For 75IRE PbPr value
	#define PbPr_MIN_VALUE 44
#else
	#define PbPr_MAX_VALUE 240 // For 100IRE PbPr value
	#define PbPr_MIN_VALUE 16
#endif
#if ENABLE_FW_ADC_OFFSET
	#define Y_AUTO_ACTIVE_RANGE (Y_MAX_VALUE - Y_MIN_VALUE)
	#define PbPr_AUTO_ACTIVE_RANGE (PbPr_MAX_VALUE - PbPr_MIN_VALUE)
	#define Y_AUTO_MIN_VALUE (Y_MIN_VALUE - 16)+1
	#define PbPr_AUTO_MIN_VALUE (PbPr_MIN_VALUE)+1

#else
	#define Y_AUTO_ACTIVE_RANGE Y_MAX_VALUE - Y_MIN_VALUE
	#define PbPr_AUTO_ACTIVE_RANGE PbPr_MAX_VALUE - PbPr_MIN_VALUE
	#define Y_AUTO_MIN_VALUE Y_MIN_VALUE - 16
	#define PbPr_AUTO_MIN_VALUE PbPr_MIN_VALUE
#endif

#define AUTO_PATCH_01 // Auto gain failed
#if(ENABLE_WATCH_DOG)
	_AUTOFUNCDEC_ void Delay1ms_WatchDog ( WORD wValue );
#else
	#define Delay1ms_WatchDog(t) Delay1ms(t)
#endif


_AUTOFUNCDEC_ BOOL msAutoGeometry ( AutoTuneType AutoParam );
_AUTOFUNCDEC_ BOOL msAutoCheckSyncLoss ( void );
_AUTOFUNCDEC_ BOOL msAutoSetValidData ( BYTE ucVSyncTime );
_AUTOFUNCDEC_ void msAutoWaitStatusReady ( BYTE ucRegIndex, BYTE ucRegMask );
_AUTOFUNCDEC_ WORD msAutoGetPosition ( BYTE ucRegIndex, BYTE ucVSyncTime );
_AUTOFUNCDEC_ BOOL msAutoTunePosition ( BYTE ucVSyncTime );
_AUTOFUNCDEC_ BYTE msAutoGetTransPos ( BYTE ucVSyncTime );
_AUTOFUNCDEC_ WORD msAutoGetActualWidth ( BYTE ucVSyncTime );
_AUTOFUNCDEC_ BOOL msAutoTuneHTotal ( BYTE ucVSyncTime );
_AUTOFUNCDEC_ DWORD msAutoGetPhaseVal ( void );
_AUTOFUNCDEC_ BOOL msAutoTunePhase ( BYTE ucVSyncTime );
_AUTOFUNCDEC_ BOOL msAutoTuneOffset ( BYTE ucVSyncTime );
_AUTOFUNCDEC_ BOOL msAutoTuneGain ( BYTE ucVSyncTime );
_AUTOFUNCDEC_ BOOL msAutoColorYUV ( BYTE ucVSyncTime );
_AUTOFUNCDEC_ BOOL msADCAutoColor ( BYTE ucVSyncTime );
#endif
#endif
