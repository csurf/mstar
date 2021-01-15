#ifndef __MARIA2_DSP_H
#define __MARIA2_DSP_H

// This function must called before all other function
void VD_DSP_Init ( void );

// Control DSP:
// bit0: 1 -> Enable SW DSP; 0 -> Disable SW DSP
// bit1: 1 -> force vtotal
// bit2: 1 -> Auto switch to freerun when H unlock
#define VD_DSP_CTL_ENABLE _BIT0
#define VD_DSP_CTL_FORCE_VTOTAL _BIT1
#define VD_DSP_CTL_SET_SCALER_H_TOTAL _BIT2
#define VD_DSP_CTL_DISABLE_AUTO_H_TOTAL _BIT3
#define VD_DSP_CTL_DISABLE_ADJUST_PHASE _BIT4
#define VD_DSP_CTL_ENABLE_HW_PHASE _BIT5
#define VD_DSP_CTL_ENABLE_VBI _BIT6

void VD_DSP_Ctl ( BYTE ucCtl, WORD wDefaultVTotal );

// Call this function at main loop
void VD_DSP ( void );

// Call this function at ISR
void VD_DSP_Int ( void );

// Get version for debug
BYTE* VD_DSP_GetVersion ( void );

// Force adjust phase every ucTh times
void SetVthreshold ( BYTE ucTh );

// Default 656_setting:
#define DSP_656_F_TGL_1_VAL 0x08
#define DSP_656_V_SET_1_VAL 0x10
#define DSP_656_V_CLR_1_VAL 0x12
#define DSP_656_F_TGL_2_VAL 0x08
#define DSP_656_V_SET_2_VAL 0x10
#define DSP_656_V_CLR_2_VAL 0x12

void VD_Vsync_Set656VPosition ( BYTE ucFieldTgl, BYTE ucVSet, BYTE ucVClr );

void VD_VSync_SetHTotal ( WORD wHTotal );

extern xdata BOOL g_bDSP_PhaseChange;
extern BYTE idata g_ucDSP_Ctl;

extern bit g_bMaria2_100pin;

#endif
