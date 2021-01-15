#include "ms_reg.h"

#ifndef _PNL_LONGLAT_C501_H_
#define _PNL_LONGLAT_C501_H_

#include "devVD.h"

#define PanelName "PanelLONGLAT_C501"
#define WidePanel 1

#define PanelDither 6

#define PANEL_DOT_WIDTH 135 // unit: um
#define PANEL_DOT_HEIGHT 135 // unit: um

#define PANEL_TTL 1
#define PANEL_DIGITAL_TCON 0
#define PANEL_ANALOG_TCON 0
#define Panel_SPI 0

#define PanelSwapRB 0xFF
#define PanelSwap8BitML 0xFF
#define PanelSwap6BitML 0xFF

#define PanelDClkDelay 0
#define PanelInvDE 0
#define PanelInvDClk 0
#define PanelInvHSync 0xFF
#define PanelInvVSync 0

// driving current setting 0==>4mA, 1==>6mA, 2==>8mA ,3==>12mA
#define PanelDCLKCurrent 0 // Dclk current
#define PanelDECurrent 0 // DE signal current
#define PANELHSCURRENT 0 // HSYNC current
#define PANELVSCURRENT 0 // VSYNC current
#define PANELBMCURRENT 0 // B data High-Nibble current
#define PANELBLCURRENT 0 // B data Low-Nibble current
#define PANELGMCURRENT 0 // G data High-Nibble current
#define PANELGLCURRENT 0 // G data Low-Nibble current
#define PANELRMCURRENT 0 // R data High-Nibble current
#define PANELRLCURRENT 0 // R data Low-Nibble current
#define PANELADCLKCURRENT 0 // Analog Panel DCLK current

#if SYSTEM_BOOT_UP_QUICKLY_ENABLE
	#define PanelOnTiming1 20//20 // time between panel & data while turn on power
	#define PanelOnTiming2 20//20 // time between data & back light while turn on power
	#define PanelOffTiming1 2 // time between back light & data while turn off power
	#define PanelOffTiming2 2 // time between data & panel while turn off power
#else
	#define PanelOnTiming1 100 // time between panel & data while turn on power
	#define PanelOnTiming2 100 // time between data & back light while turn on power
	#define PanelOffTiming1 20 // time between back light & data while turn off power
	#define PanelOffTiming2 20 // time between data & panel while turn off power
#endif

#define PanelHSyncWidth 48
#define PanelHSyncBackPorch 40
#define PanelHSyncFrontPorth 40

#define PanelVSyncWidth 3
#define PanelVSyncBackPorch 29
#define PanelVSyncFrontPorch 29

#define PANEL_DE_VSTART 0
#define PanelHStart ( PanelHSyncWidth + PanelHSyncBackPorch )
#define PanelVStart ( PanelVSyncWidth + PanelVSyncBackPorch )

#define PanelWidth 800
#define PanelHeight 480

#define PanelHTotal 928
#define PanelVTotal 525

#define PanelVdeEnd PanelHeight
#define PanelVSiEnd PanelHeight //scaling image window vertical end

#define PanelMinHTotal 928 // 38.1584 MHz
#define PanelDCLK ( ( (DWORD) PanelHTotal * PanelVTotal * 60 ) / 1000000 )

// TCON setting

// PTC Mode setting
#define SET_PTC_MODE1 0x8C // PTC_MODE1(0xD0)
#define SET_PTC_MODE2_NOR 0x3E // BK1_D1_PTC_MODE2(0xD1) ORG:0x18
#define SET_PTC_MODE2_INV 0x31 // BK1_D1_PTC_MODE2(0xD1) ORG:0x18
#define SET_PTC_MODE3 0x82 // PTC_MODE3(0xD2)

// PTC Timing Setting
#define SET_FRP_TRAN 0x02 // GPO_FRP_TRAN(0xDC)
#define SET_STH_START 0x35 // GPO_STH_START(0xDD) ORG:0x2C
#define SET_STH_WIDTH 0x01 // GPO_STH_WIDTH(0xDE)
#define SET_OEH_START 0x00 // GPO_OEH_START(0xDF)
#define SET_OEH_WIDTH 0x2C // GPO_OEH_WIDTH(0xE0)
#define SET_OEV_START 0x6C // GPO_OEV_START(0xE1)
#define SET_OEV_WIDTH 0x29 // GPO_OEV_WIDTH(0xE2)
#define SET_CKV_START 0x2A // GPO_CKV_START(0xE3)
#define SET_CKV_START2 0x00 // GPO_CKV_START2(0xE4)
#define SET_CKV_WIDTH 0x1C // GPO_CKV_WIDTH(0xE5)
#define SET_STV_LINE_TH 0x45 // GPO_STV_LINE_TH(0xE6)
#define SET_STV_START 0x6F // GPO_STV_START(0xE7)
#define SET_STV_WIDTH 0x00 // GPO_STV_WIDTH(0xE8)
#define SET_OEV2_START 0x00 // GPO_OEV2_START(0xE9)
#define SET_OEV3_START 0x00 // GPO_OEV3_START(0xEA)
#define SET_H_ST_DLY_L 0x00 // H_ST_DLY_L(0xEB)
#define SET_H_ST_DLY_H 0x00 // H_ST_DLY_H(0xEC)
#define SET_CLK_DLY_SYNC_OUT 0x00 // CLK_DLY_SYNC_OUT(0xED)
#define SET_CKV_END2 0x00 // GPO_CKV_END2(0xEE)
#define SET_Q1H 0x00 // Q1H_SETTING(0xEF)


#define SET_OEV2_WIDTH 0x54 // GPO_OEV2_WIDTH(0xCD)
#define SET_OEV3_WIDTH 0x54 // GPO_OEV3_WIDTH(0xCE)
#define SET_OEV_DELTA 0x54 // GPO_OEV_DELTA(0xCF)

// VCOM setting
#define SET_BVOM_DC 0x80//0x7C //0xA0 //DEF_VCOM_DC // BVOM_DC(0x43)
#define SET_BVOM_OUT 0x80//0x72 //0x80 //DEF_VCOM_AC // BVOM_OUT(0x44)

// DAC setting
#define SET_VDAC_ADJ1 0x07 // VADC_ADJ1(0xAA)
#define SET_VDAC_ADJ2 0x00 // VDAC_ADJ2(0xAB)

// Video decoder
#define _656_PLL_VALUE 0x83 //BK2_9D_DPL_NSPL_HIGH
#define COCTRL1_VALUE 0x20

#define SVD_EN_VALUE0 0x40 //BK2_1A_SVD_EN

#define BK1_7B_TERM_SEL_VALUE 0xE4
#define BK1_7C_CROING_VALUE 0x64

#define PANEL_SYNC_MODE_1 1

#define ENABLE_VSYNC_CTL_AUTO_H_TOTAL 0
#define ENABLE_CHECK_AUTO_H_TOTAL 0

#define ENABLE_OVER_SCAN 0
#define VD_OVER_SCAN_H 00 // 1.0%
#define VD_OVER_SCAN_V 10 // 1.0%

#define BK0_03_SYNC_Sample_Edge 0x98

#define PANEL_LOCK_Y_LINE 2

#ifdef _VDCaptureSetting_

code _CaptureVideoWinType tMsVDCapture[SIG_NUMS] = // For internal VD
{
	#if (SCALER_TYPE == MARIA9 && ENABLE_VD_32FSC)

	{0xB0, 0x00, 1330, 485}, // NSTC
	{0x85, 0x1A, 1350, 576}, // PAL
	
	#else

	{0x85, 0x0E, PanelWidth, 480}, // NSTC
	{0x85, 0x1A, PanelWidth, 576}, // PAL

	#endif
};

#endif

#define FreeRunHTotal 0x3A0
#define PalHTotal 0x3A0
#define NtscHTotal 0x3A0

#if (defined (EnableUseModeTbl) && defined(_MSTAR_C_))
RegUnitType code tENDModeTbl[] =
{
	{_END_OF_TBL_, 0},
};

RegUnitType code tNtscModeTbl[] =
{
	// {BK0_00_REGBK,REG_BANK_SCALER},
	// {BK0_40_VFDEST_L, LOBYTE(PANEL_DE_VSTART)}, // vertical DE start
	// {BK0_41_VFDEST_H, HIBYTE(PANEL_DE_VSTART)}, // vertical DE start
	// {BK0_50_VSST_L, 0x00}, // vsync start position
	// {BK0_51_VSST_H, 0x02},
	// {BK0_52_VSEND_L, 0x0A}, // vsync start position
	// {BK0_53_VSEND_H, 0x02},
	{_END_OF_TBL_, 0x00},
};

RegUnitType code tPalModeTbl[] =
{
	// {BK0_00_REGBK,REG_BANK_SCALER},
	// {BK0_40_VFDEST_L, LOBYTE(PANEL_DE_VSTART)}, // vertical DE start
	// {BK0_41_VFDEST_H, HIBYTE(PANEL_DE_VSTART)}, // vertical DE start
	// {BK0_50_VSST_L, 0xFE}, // vsync start position
	// {BK0_51_VSST_H, 0x01},
	// {BK0_52_VSEND_L, 0x00}, // vsync start position
	// {BK0_53_VSEND_H, 0x02},
	{_END_OF_TBL_, 0x00},
};

RegUnitType code tTVSnowModeTbl[] =
{
	// {BK0_00_REGBK,REG_BANK_SCALER},
	// {BK0_33_SRV_L,0x00},
	// {BK0_34_SRV_M,0x00},
	// {BK0_35_SRV_H,0x88},
	// {BK0_40_VFDEST_L,0x10},
	// {BK0_41_VFDEST_H,0x00},
	// {BK0_44_VFDEEND_L,0xFE},
	// {BK0_45_VFDEEND_H,0x01},
	// {BK0_4A_SIVEND_L,0xFE},
	// {BK0_4B_SIVEND_H,0x01},
	// {BK0_57_OSCTRL1,0xD6},
	{_END_OF_TBL_, 0x00},
};

RegUnitType code tFreeRunModeTbl[] =
{
	// {BK0_00_REGBK,REG_BANK_SCALER},
	// {BK0_40_VFDEST_L,0x10},
	// {BK0_41_VFDEST_H,0x00},
	// {BK0_44_VFDEEND_L,0xFE},
	// {BK0_45_VFDEEND_H,0x01},
	// {BK0_4A_SIVEND_L,0xFE},
	// {BK0_4B_SIVEND_H,0x01},
	// {BK0_57_OSCTRL1,0x46},
	{_END_OF_TBL_, 0x00},
};

#endif
//*******************************************************************

//Ace setting
#define CbGain 0x80
#define CrGain 0x80

#define RedGain 0x80
#define GreenGain 0x80
#define BlueGain 0x80

#define INIT_VIDEO_CONTRAST_X0 60
#define INIT_VIDEO_CONTRAST_X1 80
#define INIT_VIDEO_CONTRAST_X2 110
#define INIT_VIDEO_CONTRAST_X3 130
#define INIT_VIDEO_CONTRAST_X4 150

#define INIT_VIDEO_BRIGHTNESS_X0 0x50
#define INIT_VIDEO_BRIGHTNESS_X1 0x70
#define INIT_VIDEO_BRIGHTNESS_X2 0x80
#define INIT_VIDEO_BRIGHTNESS_X3 0xa0
#define INIT_VIDEO_BRIGHTNESS_X4 0xc0

#define INIT_VIDEO_SATURATION_X0 0
#define INIT_VIDEO_SATURATION_X1 60
#define INIT_VIDEO_SATURATION_X2 140
#define INIT_VIDEO_SATURATION_X3 180
#define INIT_VIDEO_SATURATION_X4 200

#define INIT_MSVD_COMB_YGAIN 0xF0 //BK3_13
#define INIT_MSVD_COMB_CbGAIN 0x40 //BK3_14
#define INIT_MSVD_COMB_CrGAIN 0x40 //BK3_15

#define INIT_MSVD_COMB_CONTRAST 0x90
#define INIT_MSVD_COMB_BRIGHTNESS 0x90
#define INIT_MSVD_COMB_SATURATION 0x90
#define INIT_MSVD_TV_BRIGHTNESS 0x0CE // bk2_38[6] bk2_3a[7:0] MAXVALUE=0X1FF

#if (defined (EnableUseGammaTbl) && defined(_MSTAR_C_))
BYTE code tGammaTableNormal[3][33] =
{
	{
		0x00, 0x03, 0x07, 0x0C, 0x12, 0x19, 0x20, 0x28, 0x31, 0x3A, 0x43,
		0x4D, 0x57, 0x61, 0x6B, 0x75, 0x80, 0x8B, 0x95, 0x9F, 0xA9, 0xB3,
		0xBD, 0xC6, 0xCF, 0xD7, 0xDF, 0xE6, 0xEC, 0xF2, 0xF7, 0xFB, 0xFF,
	},
	{
		0x00, 0x03, 0x07, 0x0C, 0x12, 0x19, 0x20, 0x28, 0x31, 0x3A, 0x43,
		0x4D, 0x57, 0x61, 0x6B, 0x75, 0x80, 0x8B, 0x95, 0x9F, 0xA9, 0xB3,
		0xBD, 0xC6, 0xCF, 0xD7, 0xDF, 0xE6, 0xEC, 0xF2, 0xF7, 0xFB, 0xFF,
	},
	{
		0x00, 0x03, 0x07, 0x0C, 0x12, 0x19, 0x20, 0x28, 0x31, 0x3A, 0x43,
		0x4D, 0x57, 0x61, 0x6B, 0x75, 0x80, 0x8B, 0x95, 0x9F, 0xA9, 0xB3,
		0xBD, 0xC6, 0xCF, 0xD7, 0xDF, 0xE6, 0xEC, 0xF2, 0xF7, 0xFB, 0xFF,
	},
};
#endif

#if (defined (EnableColorMatrix) && defined(_GLOBAL_C_))
short code tVideoColorCorrectionMatrix[][3] =
{
	0x040D, -0x0010, 0x0002, 0x0012, 0x03C1, 0x002D, 0x002F, -0x0031,
	0x0402, -0x82E6, 0x4288, -0xCDBB, 0x0FA4, -0x962C, 0xDEF3, -0x5F3C,
	-0x5024, 0x61BF, 0xD7EF, -0xD116, 0xA1EE, 0x752C, -0xCBBB, 0x68B1,
	-0xC34B, 0x2996, -0xFE8B, 0xEBC9, -0xDC39, 0x1832, -0xD804, 0x27EE,
};
#endif

#if (defined (_EnableFCC_) && defined(_MSTAR_C_))
RegUnitType code tInitializeFCC[] =
{
	// Initialize MACE table
	{BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU},
	{BK1_56_FCC_CB_1T, 0x74}, // FCC_
	{BK1_57_FCC_CR_1T, 0x9B}, // FCC_
	{BK1_58_FCC_CB_2T, 0x6E}, // FCC_
	{BK1_59_FCC_CR_2T, 0xAC}, // FCC_
	{BK1_5A_FCC_CB_3T, 0xA5}, // FCC_
	{BK1_5B_FCC_CR_3T, 0x69}, // FCC_
	{BK1_5C_FCC_CB_4T, 0x5A}, // FCC_
	{BK1_5D_FCC_CR_4T, 0x9A}, // FCC_
	{BK1_5E_FCC_CB_5T, 0x5A}, // FCC_
	{BK1_5F_FCC_CR_5T, 0x75}, // FCC_
	{BK1_60_FCC_CB_6T, 0xB0}, // FCC_
	{BK1_61_FCC_CR_6T, 0x48}, // FCC_
	{BK1_62_FCC_CB_7T, 0x64}, // FCC_
	{BK1_63_FCC_CR_7T, 0xD8}, // FCC_
	{BK1_64_FCC_CB_8T, 0x80}, // FCC_
	{BK1_65_FCC_CR_8T, 0x80}, // FCC_
	{BK1_66_FCC_CB_9T, 0x80},//0x88}, // FCC_
	{BK1_67_FCC_CR_9T, 0xA0},// FCC_
	{BK1_68_FCC_WIN1, 0xA6}, // FCC_
	{BK1_69_FCC_WIN2, 0xBA}, // FCC_
	{BK1_6A_FCC_WIN3, 0xFB}, // FCC_
	{BK1_6B_FCC_WIN4, 0x73}, // FCC_
	{BK1_6C_FCC_WIN5, 0xFB}, // FCC_
	{BK1_6D_FCC_WIN6, 0xFB}, // FCC_
	{BK1_6E_FCC_WIN7, 0xFF}, // FCC_
	{BK1_6F_FCC_WIN8, 0x6A}, // FCC_
	{BK1_70_FCC_WIN9, 0x00}, // FCC_
	{BK1_71_FCC_Y_TH, 0xFF}, // FCC_
	{BK1_72_FCC_K1K2, 0x60}, // FCC_
	{BK1_73_FCC_K3K4, 0xFE}, // FCC_
	{BK1_74_FCC_K5K6, 0xCB}, // FCC_
	{BK1_75_FCC_K7K8, 0x85}, // FCC_
	// {BK1_76_FCC_CTRL, 0x2F}, // FCC_
	// {BK1_77_APP_CTRL, 0x7E}, // FCC_
	{BK1_78_PEAK_BAND1, 0x1D}, // FCC_
	{BK1_79_PEAK_BAND2, 0x58}, // FCC_
	// {BK1_7A_LTI, 0x98}, // FCC_
	{BK1_7D_CTI, 0x78},
	{BK1_7E_VIP_Y_CTRL, 0x03},
	{BK1_7F_MAX_PIX, 0x80}, // MAX_PIX
	{BK1_80_MIN_PIX, 0x40}, // MIN_PIX
	// {BK1_81_EGE_BAND1_POS,0x40},
	// {BK1_82_EGE_BAND1_NEG,0x60},
	// {BK1_84_EGE_BAND2_NEG,0x60},
	// {BK1_85_M_BRI,0x08},
	// {BK1_86_EGE_LTI_POS,0x10},
	// {BK1_87_EGE_LTI_NEG,0x20},
	// {BK1_88_YC_LPF, 0xBC},
	{BK1_89, 0x00},
	// {BK1_8A, 0x23},
	{BK1_8B, 0x43},
	{BK1_8C, 0xFF},
	{BK1_8D, 0xAE},
	{BK1_8E, 0x36},
	{BK1_8F, 0x01},
	{BK0_00_REGBK, REG_BANK_SCALER},

	{_END_OF_TBL_, 0x00}
};

RegUnitType code tVideoFCC[] =
{
	{BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU},

	{BK1_77_APP_CTRL, 0x7E}, // FCC_
	{BK1_85_M_BRI, 0x00},
	{BK1_88_YC_LPF, 0xBC},

	{BK0_00_REGBK, REG_BANK_SCALER},

	{_END_OF_TBL_, 0x00}
};

RegUnitType code t_AVInitializeFCC[] =
{
	{BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU},
	{BK1_76_FCC_CTRL, 0x6F}, // FCC_
	{BK1_7A_LTI, 0x98}, // FCC_
	{BK1_7C_CROING, 0x42},
	{BK1_81_EGE_BAND1_POS, 0x40},
	{BK1_82_EGE_BAND1_NEG, 0x60},
	{BK1_84_EGE_BAND2_NEG, 0x60},
	{BK1_86_EGE_LTI_POS, 0x10},
	{BK1_87_EGE_LTI_NEG, 0x20},
	{BK1_88_YC_LPF, 0x80},
	{BK1_8A, 0x23},
	{BK0_00_REGBK, REG_BANK_SCALER},

	{_END_OF_TBL_, 0x00},
};

RegUnitType code t_TVInitializeFCC[] =
{
	{BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU},
	{BK1_76_FCC_CTRL, 0x2D},
	{BK1_7A_LTI, 0x90},
	{BK1_7C_CROING, 0x42},
	{BK1_81_EGE_BAND1_POS, 0x00},
	{BK1_82_EGE_BAND1_NEG, 0x00},
	{BK1_84_EGE_BAND2_NEG, 0x00},
	{BK1_86_EGE_LTI_POS, 0x00},
	{BK1_87_EGE_LTI_NEG, 0x00},
	{BK1_88_YC_LPF, 0x9C},
	{BK1_8A, 0x43},
	{BK0_00_REGBK, REG_BANK_SCALER},

	{_END_OF_TBL_, 0x00},
};

#endif // _EnableFcc_

#endif
