#ifndef __DSP_MARIA_H_
#define __DSP_MARIA_H_

//#include "typedef.h"
#include "types.h"

#define DSP_FIFO_SIZE 16

extern XDATA BYTE s_ucWriteIdx;
extern XDATA BYTE s_ucReadIdx;
extern XDATA HLdata s_awVPos[DSP_FIFO_SIZE];
extern XDATA HLdata s_awStrbVcunt[DSP_FIFO_SIZE];

#define BK0_00 0x00
#define REG_BANK_MASK 0x07
#define REG_BANK_SCALER 0x00 // Scaler bank
#define REG_BANK1_ADC_ACE_MCU 0x01 // ADC/DVI receiver bank
#define REG_BANK2_VD 0x02 // Video Decoder Front End

#define BK0_54 0x54
#define BK0_55 0x55
#define BK0_57 0x57
#define BK2_07 0x07
#define BK2_1E 0x1E
#define DSP_00 0x00
#define DSP_0E 0x0E
#define DSP_0F 0x0F
#define DSP_10 0x10
#define DSP_14 0x14

#ifdef MARIA2
	#define REG_BANK3_COMB 0x03 // Video Decoder 2D Comb Filter
	#define BK0_F7 0xF7
	#define BK0_FE 0xFE
	//#define BK3_72 0x72
	#define BK3_B8 0xB8
#endif

#ifdef MARIA3
	#define DSP_12 0x12
	//#define REG_BANK6_COMB 0x06 // Video Decoder 2D Comb Filter
	//#define BK6_E2 0xE2
#endif

//*************************************
#define V_Total 0x00
#define StrbVcunt 0x02
#define ITU_656_F 0x40
#define DeltaVcunt 0x04
#define V_Position 0x06 // Free run counter
#define V_STROBE_LOCAT 0x08
#define LINE_COUNTER 0x0A
#define VPLL_MODE2 0x0C
#define REG_DSP_EN 0x10
#define REG_DSP_EN2 0x12
#define SPL_LENG 0x16
#define ADC_OVERATIO 0x18
#define StatusCOMB 0x1C
#define CVBS_MAX_L 0x1E //Max CVBS signal
#define SelNTSC 0x01
#define SelPAL 0x02
#define NTSC_PAL 0x03 // 01 = NTSC, 10 = PAL. 00 = No colorBurst.
#define Sel625 0x04 // 0 = 525, 1 = 625
#define SelFSC 0x08 // 0 = 3.5x, 1 = 4.43
#define SelInter 0x10 // 0 = progressive, 1 = interlaced.
#define StatusDSP 0x22
#define SYNC_FOUND 0x40
#define BOT_FOLWR 0xBC
//#define BKPRH_LVL 0x26
#define BOT_HSYNC 0x28
#define NOISE_MAG 0x2A
#define ADCTOP_FOLWER 0x2C
#define ACC_C_PEAK 0x2E
#define BRST_PHS 0x32
#define BRST_MAG 0x34
#define BRST_ACC_MAG 0x36
#define HSYNC_WIDTH 0x3A
#define SPL_NSPL 0x3C
#define HSYNC_EDGE 0x3B
#define SPL_PD_reg 0x3E
#define BKPRH_LVL 0x40 // Latch value
#define SCM_MAG 0x42
#define SCM_LT 0x04
#define SCM_MValid 0x08
#define FSC_TST_MAG_010 0x48
#define FSC_TST_MAG_101 0x4A
#define HCNT_SNAP_A 0x4C
#define HCNT_SNAP_B 0x4E
#define APL_FREQ_IDEAL 0x52
#define APL_FREQ_ERR 0x54
#define DPL_PD 0x56
#define BOT_AVIDEO 0x58
#define CSH_LOW_RATIO 0x5A
#define SAMPLE_CUNT 0x60
#define DSP_IQ_STATUS 0x69
#define DSP_OVFL 0x20
#define DSP_DEC_VALID 0x40
#define DSP_PKDET_RDY 0x80
#define DSP_UV_ACC_OUT 0x6A
#define DSP_I_DEC 0x6C
#define DSP_Q_DEC 0x6E
#define DSP_DF 0x7C
#define DSP_DF_VALID 0x7E
#define AGC_FINE_PRE 0x80
#define DSP_AGC_DONE 0x82
#define DSP_MISC 0x84
#define VCR_FOUND 0x01
#define EDGES_NOISY 0x02
#define MACROVISION_FOUND 0x04
#define SCMID_RESULT 0x18
#define SCM_DSP_SIGN 0x40
#define DSP_656_F_TGL_1 0x86
#define DSP_656_F_TGL_2 0x88
#define DSP_FREEZ_656_F 0x8A
#define DSP_656_V_SET_1 0x8C
#define DSP_656_V_SET_2 0x8E
#define DSP_656_V_CLR_1 0x90
#define DSP_656_V_CLR_2 0x92
#define DSP_VSYNC_EVEN 0x94
#define DSP_VSYNC_ODD 0x96
#define DSP_CLAMP_DSM 0x98
#define DSP_CLAMP_DSM_C 0x9A
#define DSP_PAR_FSC_SEL 0x9C
#define FSC443 0x00
#define FSC4285 0x01
#define FSC35795 0x02
#define FSC35756 0x04
#define FSC35820 0x06
#define FSC_TST_RESULT 0x9E
#define DSP_APL_K2 0xA0
#define DSP_APL_K1 0xA1
#define DSP_CTRL_STATE 0xA2
#define DSP_BLANK_LVL 0xA4
#define DSP_BLACK_LVL 0xA6
#define DSP_NTSC_PAL 0xA8
#define PAL_SWITCH_SIGN 0x04
#define DSP_SLICE_LVL 0xAA
#define DSP_SLICE_LVL2 0xAC
#define ACC_GAIN 0xAE
#define DSP_BRST_END 0xB8
#define DSP_BKPRH_END 0xB9
#define DPL_PD_MAX_VCR 0xBE
#define OP1_H 0xE0
#define OP1_L 0xE1
#define OP2_H 0xE2
#define OP2_L 0xE3
#define CmdALU 0xE4
#define CmdClear 0x00
#define CmdRightShift 0x10
#define CmdLeftShift 0x20
#define CmdMultiply 0x40
#define EnInt 0xFA
#define IntFlag 0xFC // bit0 : AGC_START : Horizontal data ready
// 1 : LINE_START
// 2 : V_STROBE : VSYNC leading edge
// 3 : VSYNC trailing edge
// 4 : DSP_V : V count overflow.
#define StatusVD 0xFE
//************************************* Global constants definition.
#define cChgVCR 0x01 // 1 = VCR mode changed.
#define cChgNoise 0x02 // 1 = noise magnitude changed.
#define cChgMV 0x04 // 1 = Macrovision mode changed.
#define cChgSTD 0x08 // 1 = TV standard changed.
#define cChgSyncLoss 0x20 // 1 = input signal level changed.
#define cChgLineSTD 0x40 // 1 = input lines changed.
#define cChgBurst 0x80 // 1 = Burst Lock status changed.
#define TASK_VCR_NR_MV 0
#define TASK_AGC 1
#define TASK_ACC 2
#define TASK_FSC_DETECT 3
#define TASK_STD_DETECT 4
#define TASK_FSC_SHIFT 5

//************************************* DSP.C
void InitDSP();
void DSP();
int Abs ( int v );
//************************************* VSYNC.C
void initVSYNC ( WORD wDefaultVTotal );
void SyncLossVSYNC();
void TaskVSYNC();
//*********************************************************
// variables definition :
//*********************************************************
//************************************* DSP.C
//extern bit bVCR_Det; // 1 = VCR mode detected.
//extern bit bSyncLoss;
//extern bit bDetLevelOK;
//extern bit bMV_Det;

//************************************* VSYNC.C
extern WORD xdata g_wVtotalLatch;

#endif
