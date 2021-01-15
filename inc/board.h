// MSTAR SCALER CHIP FIRMWARE
//=======================================================
#include "reg52.h"

#ifndef _BOARD_H_
#define _BOARD_H_

#define BD_DEMO_702		0
#define BD_DEMO_703		1
#define BD_DEMO_705		2
#define DX_703_5IN		3
#define BG_ZCD706_5IN	4
#define BG_QN706_43_5IN	5

#define BD_TYPE BG_ZCD706_5IN

//-----------EEprom Define-------------------

#define RM_TYPE_24C02 0
#define RM_TYPE_24C04 1
#define RM_TYPE_24C08 2
#define RM_TYPE_24C16 3
#define RM_TYPE_24C32 4
#define RM_TYPE_SST512 5
#define RM_TYPE_SST010 6
#define RM_TYPE_PMC512 7
#define RM_TYPE_PMC010 8
#define RM_TYPE_SAI512 9
#define RM_TYPE_SAI010 10

//-------SFD_ADDRESS Define----------------

#define LOAD_4K_TO 0x0000
#define SFD_ADDRESS 0xE000

//-----------Chip Define-------------------

#define MST710A		1
#define MST716A		2
#define MST720A		3
#define MST717A		4
#define MST726A		5
#define MST712CX	6

#define MST702 20
#define MST703 21
#define MST705 22
#define MST706 23

//--------- TV System selection-----------

#define TV_NONE 0
#define TV_NTSC 1
#define TV_PAL	2

//-----------PWM Define--------------------

#define PWM_TYPE_NONE 0
#define PWM_TYPE_PWM1 1
#define PWM_TYPE_PWM2 2
#define PWM_TYPE_PWM3 3
#define PWM_TYPE_PWM4 4

//-----------Panel Define-------------------

//analog panels
#define PanelLG07_AT 0
#define PanelAU07_AT 1
#define PanelPVI05_AT 2
#define PanelTMD07_AT 3
#define PanelPVI07_AT 4
#define PanelPVI08W_AT 5
#define PanelPVI10_AT 6
#define PanelLG065_AT 7
#define PanelPVI025_AT 8
#define PanelAU065W_AT 9
#define PanelCPT07_AT 10
#define PanelPVI08_AT 11
#define PanelPVI030_AT 12
#define PanelChiLin084_AT 13
#define PanelHSD09_AT 14

//digital panels -- please don't change order
#define PanelSHARP08_DT 80
#define PanelLG064_DT 81
#define PanelSHARP09_DT 82
#define PanelAU102_DT 83
#define PanelINNPLUX08_DT 84
#define PanelINNOLUX0843_DT 85
#define PanelAT08TN52_D 86
#define PanelFG035_D 87
#define PanelKD040G1A1_DT 88
#define PanelHSD07_D 89
#define PNL_CM106_V 90
#define PanelCMO_N10106_LVDS1024X600 91
#define PanelCMO_N10106_LVDS1024X768 92
#define PanelCPT12_LVDS 93 //csrf check for dups
#define PanelCPT102_LVDS 94 // ''
#define PanelB089AW01_LVDS 95
#define Pnl_A121EW02_LVDS 96
#define Pnl_HSD121PHW1_LVDS 97
#define Pnl_LP156WH2_LVDS 98
#define Pnl_AU08_D 99
#define PanelHSD050 100
#define PanelLONGLAT_C501 101

//-----------Key Define-------------------
#define Single_ADCKey 0
#define Dual_ADCKey 1
#define Single_ADCKey_3Key 2
#define KEY_NONE 10

#define SAR0 _BIT0
#define SAR1 _BIT1
#define SAR2 _BIT2

//-----------Misc Define-------------------

#define SOG_ENABLE 0
#define ENABLE_DDC2BI 0

//--------System boot up quickly define------------------------

#define SYSTEM_BOOT_UP_QUICKLY_ENABLE 0

//-------------------------------
#define ENABLE_VD_32FSC 1
//-------------------------------------------------------

#if(BD_TYPE == BD_DEMO_702)
	#include "bd_demo_702.h"
	#elif(BD_TYPE == DX_703_5IN)
	#include "dX_703_5inch.h"
	#elif(BD_TYPE == BD_DEMO_705)
	#include "bd_demo_705.h"
	#elif(BD_TYPE == BG_ZCD706_5IN)
	#include "bg_zcd706_5in.h"
	#elif(BD_TYPE == BG_QN706_43_5IN)
	#include "bg_qn706_43_5in.h"
#endif

#define MARIA2_X 0
#define MARIA9 1
#define MARIA9_B 2

#define MARIA9_VERSION 1

#if(MST_CHIP >= MST702 )
	#define SCALER_TYPE MARIA9
#else
	#define SCALER_TYPE MARIA2_X
#endif

#ifndef VCOM_DC_Ctrl
	#define VCOM_DC_Ctrl PWM_TYPE_NONE
#endif

//RD feedback, NEW ADC structure doesn't need offset caliberation,
#ifndef ENABLE_FW_ADC_OFFSET
	#define ENABLE_FW_ADC_OFFSET 0
#endif

//-------------------------------------------------------
#define Enable_Logo_Display 0
//-------------------------------------------------------
#define ENABLE_MCU_USE_INTERNAL_CLOCK 1 // 12M--->27M
#define ENABLE_WATCH_DOG 1
//-------------------------------------------------------
#define ENABLE_V_PRE_SCALING_DOWN 0
//-------------------------------------------------------
#define ENABLE_CBCR 0
#define UsePWMBrightness 1
//-------------------------------------------------------
#define ENABLE_MONITOR_VTOTAL 0
//-------------------------------------------------------
#define INT_PERIOD 1
#define UseIsr 1

#define SystemTick 10 //1s//10
#define T100MsTick 100

#define SERIAL_BAUD_RATE 9600

// MCU timer0
#define ISR_TIMER0_INTERVAL 1 // unit: 1ms

#if ENABLE_MCU_USE_INTERNAL_CLOCK

	#define MCU_CLOCK_DIVIDER 6 // => 216/6=36MHz: This speed is too fast for serial flash
	//#define MCU_CLOCK_DIVIDER 8 // => 216/8=27MHz
	//#define MCU_CLOCK_DIVIDER 10 // => 216/10=21.6MHz
	//#define MCU_CLOCK_DIVIDER 12 // => 216/12=18MHz
	//#define MCU_CLOCK_DIVIDER 14 // => 216/14=15.4MHz
	//#define MCU_CLOCK_DIVIDER 16 // => 216/16=13.5MHz

	#define BK0_EE_VAL (0x80 | (((MCU_CLOCK_DIVIDER - 4) / 2) << 4 ))

	#define NEW_MCU_XTAL_CLK_HZ (216000000ul / MCU_CLOCK_DIVIDER)
	#define NEW_MCU_XTAL_CLK_KHZ (NEW_MCU_XTAL_CLK_HZ / 1000)
	#define NEW_MCU_XTAL_CLK_MHZ (NEW_MCU_XTAL_CLK_KHZ / 1000)
#endif

#define MCU_XTAL_CLK_HZ 12000000ul
#define MST_CLOCK_HZ 12000000ul

#define MST_CLOCK_KHZ (MST_CLOCK_HZ/1000)
#define MST_CLOCK_MHZ (MST_CLOCK_KHZ/1000)

#define MCU_XTAL_CLK_KHZ (MCU_XTAL_CLK_HZ / 1000)
#define MCU_XTAL_CLK_MHZ (MCU_XTAL_CLK_KHZ / 1000)

// 4 clock count
#define ISR_TIMER0_COUNTER (65536 - (MCU_XTAL_CLK_KHZ * ISR_TIMER0_INTERVAL + 2) / 4)

#if ENABLE_MCU_USE_INTERNAL_CLOCK
	#define NEW_ISR_TIMER0_COUNTER (65536 - (NEW_MCU_XTAL_CLK_KHZ * ISR_TIMER0_INTERVAL + 2) / 4)
#endif

#define TIMER1_MODE2_DIVIDER ((DWORD)SERIAL_BAUD_RATE*(32 * 4)) // 4 clock count
#define _SMOD 0

#define TIMER1_MODE2_TH1 (256-((DWORD)MCU_XTAL_CLK_HZ*_SMOD+MCU_XTAL_CLK_HZ+(TIMER1_MODE2_DIVIDER/2))/TIMER1_MODE2_DIVIDER)

#define MCU_MACHINE_CYCLE 12 // unit: oscillatory cycle

#if ENABLE_MCU_USE_INTERNAL_CLOCK
	#define MCU_MICROSECOND_NOP_NUM ((NEW_MCU_XTAL_CLK_MHZ + (MCU_MACHINE_CYCLE / 2)) / MCU_MACHINE_CYCLE)
#else
	#define MCU_MICROSECOND_NOP_NUM ((MCU_XTAL_CLK_MHZ + (MCU_MACHINE_CYCLE / 2)) / MCU_MACHINE_CYCLE)
#endif


#define HFreq(hPeriod) ((DWORD)MST_CLOCK_KHZ*10+hPeriod/2)/hPeriod
#define VFreq(hFreq, vTotal) ((DWORD)hFreq*1000+vTotal/2)/vTotal

#define I2C_CHECK_PIN_TIME 1000 // unit: 1 us
#define I2C_CHECK_PIN_CYCLE 8 // cycle of check pin loopp
#define I2C_CHECK_PIN_DUMMY ((I2C_CHECK_PIN_TIME / I2C_CHECK_PIN_CYCLE) * MCU_MICROSECOND_NOP_NUM)

#define NON_LINEAR_POINT_X0 0
#define NON_LINEAR_POINT_X1 30
#define NON_LINEAR_POINT_X2 50
#define NON_LINEAR_POINT_X3 80
#define NON_LINEAR_POINT_X4 100

#endif
/***********************************************************************************/
