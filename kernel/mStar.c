#define _MSTAR_C_

#define _VDCaptureSetting_

#include <MATH.H>
#include "types.h"
#include "global.h"
#include "board.h"
#include "mcu.h"
#include "ms_reg.h"
#include "panel.h"
#include "adjust.h"
#include "valuetbl.h"
#include "mstar.h"

#include "ms_rwreg.h"
#include "debug.h"
#include "misc.h"
#include "power.h"
#include "detect.h"
#include "msOSD.h"
#include "extlib.h"
#include "msACE.h"
#include "userPref.h"
#include "devVD.h"
#include "msVD.h"
#include "devVD_User.h"

#include "maria2_FSC.h"
#include "m9_VD_AGC.h"
#include "m2_VD_STD.h"

#if(ENABLE_VD_DSP)
	#include "maria2_DSP.h"
#endif

#if (SCALER_TYPE == MARIA9)
	#define SRCTYPE_VGA 1
	#define SRCTYPE_YCBCR 2
	#define SRCTYPE_CVBS 3
	#define SRCTYPE_SVIDEO 4
#endif

//*******************************************************************
//
// Constant Definition
//
//*******************************************************************
//14.318 * 15 * 8 / 4 = 429.54, 429.54 << 19 = 225202667.52, 429.54 << 3 = 8 = 3436.32

#define DClkFactor 225202667ul

//*******************************************************************
//
// extern declaration
//
//*******************************************************************

//*******************************************************************
//
// local declaration
//
//*******************************************************************

#define SSCSTEP 0x119
#define SSCSPAN 0xEC

//*******************************************************************
//
//*******************************************************************
// Function Name: msInit(void)
//
// Description: Initialize mStar chip while 1st power on system
//
// Caller: msInitADC(), msInitTCON, msSetupFreeRunMode()
// msSetupInputPort() in mStar.c
// msWriteByte(), msWriteWord() in ms_rwreg.c
// msWriteDDC1(), msWriteDDC2() in ddc.c
// msInitGamma() in gamma.c
// Osd_InitOSD() in osd.c
// Callee: Init_Device() in main.c
//*******************************************************************

#ifdef EnableUseModeTbl

DynamicLoadModeTblType code tModeIndexTbl[] =
{
	{
		1 << Input_CVBS1 | 1 << Input_CVBS2, //|1<<Input_TV,
			MD_720x576_50I,
			tPalModeTbl,
	},

	{
		1 << Input_CVBS1 | 1 << Input_CVBS2, //|1<<Input_TV,
			MD_720x480_60I,
			tNtscModeTbl,
	},

	{
		1 << Input_CVBS1 | 1 << Input_CVBS2,
			MD_FreeRun,
			tFreeRunModeTbl,
	},

	{
		1 << Input_CVBS1 | 1 << Input_CVBS2, //1<<Input_TV,
			MD_TVsnow,
			tTVSnowModeTbl,
	},

	{
		_END_OF_TBL_,
		0,
		tENDModeTbl
	},
};
#endif

#if (SCALER_TYPE==MARIA9)
#if FUN_MGD
void msInitializeChip_MGD ( void )
{
	BYTE ucBank = msReadByte ( BK0_00_REGBK );
	// MGD initial process
	msWriteByte ( BK0_00_REGBK, REG_BANK4_LVDS_CCFL ); // switch to Bank 4
	//msWriteByte(BK4_6B, 0x80);//This statement needs to be located at the BL on process
	msWriteByte ( BK4_9A, 0xCF );
	msWriteByte ( BK4_A7, 0xF3 );

	msWriteByte ( BK0_00_REGBK, REG_BANK5_MGD ); // switch to Bank 5
	msWriteByte ( BK5_D7, 0x01 ); // set H active = 480 , 0x1e0
	msWriteByte ( BK5_D6, 0xE0 );
	msWriteByte ( BK5_D9, 0x00 ); // set V active = 234 , 0xea
	msWriteByte ( BK5_D8, 0xEA );

	msWriteByte ( BK5_DA, 0x08 ); // H blanking
	msWriteByte ( BK5_A5, 0xA0 ); // PWM period H byte ,read 0xdc
	msWriteByte ( BK5_A7, 0xAA ); // PWM duty H byte , read 0xdd for current value

	msWriteByte ( BK5_DA, 0x08 ); // H blanking
	msWriteByte ( BK5_AD, 0x18 ); // DLC on set 0xad[3] =1

	msWriteByte ( BK5_9A, 0x96 ); // Y gain
	msWriteByte ( BK5_9F, 0x03 ); // Y gain offset
	msWriteByte ( BK5_9E, 0xFC ); // Y gain offset
	msWriteByte ( BK5_A2, 0x20 ); // DLC gain
	msWriteByte ( BK5_A1, 0x0C ); // DLC gain offset
	msWriteByte ( BK5_A0, 0x00 ); // DLC gain offset
	msWriteByte ( BK0_00_REGBK, ucBank );
}
#endif
#endif

void msInit ( void )
{
	BYTE ucBank = msReadByte ( BK0_00_REGBK );
	
	msWriteRegsTbl ( tInitializeScaler );
	
	#ifdef _EnableFCC_
	msWriteRegsTbl ( tInitializeFCC );
	#endif
	
	msWriteRegsTbl ( tInitializeADC );
	
	#if PANEL_TTL
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_C1_BND_RST, 0x21 );
	msWriteByte ( BK1_C0_TUNE_FRAME_NO, 0x80 );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	
	#endif

	#if ( SCALER_TYPE == MARIA9 )
	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	msWrite2BytesMask_16bitADDR ( BK6s00_34h_ADC_ATOP, _BIT12, _BIT12 | _BIT11 | _BIT10 ); //ATOP_34[12:10] = 3?h100 // For ADC current change to 22mA
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByteMask ( BK0_23_OPL_CTL0, 2, 0x0F );
	msWriteByteMask ( BK0_24_OPL_CTL1, 3, 0x07 );
	msWriteByteMask ( BK0_2E_OPL_TSTA1, 1, 0x03 );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	#if ( PANEL_ANALOG_TCON ) // DYSON 101006 // Linix 20100929
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_C0_TUNE_FRAME_NO, 0x80 );
	msWriteByte ( BK1_C1_BND_RST, 0x68 ); //Set Bonding Overwrite
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	
	#elif ( PANEL_TTL )
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_C0_TUNE_FRAME_NO, 0x80 );
	msWriteByte ( BK1_C1_BND_RST, 0x42 ); //Set Bonding Overwrite
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	
	#else
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_C0_TUNE_FRAME_NO, 0x80 );
	msWriteByte ( BK1_C1_BND_RST, 0x22 ); //Set Bonding Overwrite
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER ); //END DYSON 101006
	
	#endif

	// #if 1//(IR_FORMAT!=IR_NONE) //Linix 20101004
	msWriteByte ( BK0_00_REGBK, REG_BANK7_CHIPTOP );
	msWriteByteMask ( BK7_09_CHIPTOP, 0x00, 0x02 );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	// #endif //End Linix 20101004
	
	#endif

	#ifdef P6_GPIO_Enable
	msWriteBit ( BK0_5E_PATTERN, _ENABLE, _BIT6 ); // Nelson Switch ITU656 to P6 port 2006-01-25
	#endif

	#ifdef P5_GPIO_Enable
	msWriteBit ( BK0_5E_PATTERN, _ENABLE, _BIT7 );
	#endif
	
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // select register bank ADC
	msWriteByte ( BK1_0C_GCTRL, 0x02 );

	#if ( PANEL_DIGITAL_TCON || PANEL_ANALOG_TCON )
	
	msWriteRegsTbl ( tInitializeTCON );
	//VCOM SETTING
	
	#if ( SCALER_TYPE == MARIA9 )
	
	#if(VCOM_DC_Ctrl == PWM_TYPE_PWM1)
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_F4_PWM1C, g_VideoSetting.VcomDC );
	
	#elif(VCOM_DC_Ctrl == PWM_TYPE_PWM2)
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_F5_PWM2C, g_VideoSetting.VcomDC );
	
	#elif(VCOM_DC_Ctrl == PWM_TYPE_PWM3)
	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
	msWriteByte ( BK3_F4_PWM3C, g_VideoSetting.VcomDC );
	
	#elif(VCOM_DC_Ctrl == PWM_TYPE_PWM4)
	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
	msWriteByte ( BK3_F5_PWM4C, g_VideoSetting.VcomDC );
	#endif
	
	#else
	
	msWriteByte ( BK1_43_BVOM_DC, g_VideoSetting.VcomDC );

	#endif
	
	#else
	
	msWriteByte ( BK1_D0_PTC_MODE1, 0x0C ); // Disable TCON function
	
	#endif


#if BACKLIGHT_PWM == PWM_TYPE_PWM3
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK0_87_DEBUG, _BIT3 | _BIT1 );
#endif

	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_4E, ( msReadByte ( 0x4E ) | _BIT0 ) );

	msWriteByte(BK1_F6_PWM1EPL, 0x00);
	msWriteByte(BK1_F7_PWM1EPH, 0x01);
	
	// msWriteByte(BK1_F4_PWM1C, 0xFF);
	// msWriteByte ( BK1_F6_PWM1EPL, 0x00 );
	// msWriteByte ( BK1_F7_PWM1EPH, 0x01 );

	msWriteByteMask ( BK1_92_SARADC_AISEL, KEY_PORT, 0x07 );

	msWriteByte ( BK1_94_SAR_CH1_UPB, 0x3F );
	msWriteByte ( BK1_95_SAR_CH1_LOB, 0x05 );
	msWriteByte ( BK1_96_SAR_CH2_UPB, 0x3F );
	msWriteByte ( BK1_97_SAR_CH2_LOB, 0x00 );
	msWriteByte ( BK1_98_SAR_CH3_UPB, 0x3F );
	msWriteByte ( BK1_99_SAR_CH3_LOB, 0x00 );

	msWriteByte ( BK1_7B_TERM_SEL, BK1_7B_TERM_SEL_VALUE );
	msWriteByte ( BK1_7C_CROING, BK1_7C_CROING_VALUE );

	msWriteRegsTbl ( tInitializeVFE );
	msWriteRegsTbl ( tInitializeVCE );

	#if (CCFL_FUNCTION)
	msWriteRegsTbl ( tInitializeCCFL );
	#endif
	
	#if (PANEL_LVDS)
	msWriteRegsTbl ( tInitializeLVDS );
	#endif

	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	msWriteByteMask ( BK2_9A_SYNC_CTRL1, 0x01, 0x01 );
	msWriteBit ( BK2_38_VSTROBE_LIMIT, HIBYTE ( INIT_MSVD_TV_BRIGHTNESS ) & 0x10, _BIT6 );
	msWriteByte ( BK2_3A, LOBYTE ( INIT_MSVD_TV_BRIGHTNESS ) );

	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );

	if ( VD_Type == MARIA2_D )
	{
		msWriteByte ( BK3_B9, 0x01 );
	}

	else if ( VD_Type >= MARIA2_E )
	{
		msWriteByte ( BK3_B9, 0x05 );
	}

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteBit ( BK0_F7_TEST_BUS_SELECT, 1, _BIT6 );
	msWriteByte ( BK0_F8_TEST_MODE, 0 );
	msWriteByte ( BK0_FF_BOUNDING_MISC, 0x02 );
	msWriteBit ( BK0_F7_TEST_BUS_SELECT, 0, _BIT6 );

	#if ( SCALER_TYPE == MARIA9 )
	M9initAGC_U01();
	#if FUN_MGD
	msInitializeChip_MGD();
	#endif
	
	msWriteByte ( BK0_00_REGBK, REG_BANK7_CHIPTOP );
	
	#if ( MARIA9_VERSION == MARIA9_B )
	msWriteByte ( BK7_04_CHIPTOP, 0x1A ); //Set SAR clock divider as 16=> 27MHz/16 is SAR clock
	msWriteByte ( BK7_60_CHIPTOP, 0x80 ); //Set as SAR freerun mode
	#endif

	#if ( PANEL_DIGITAL_TCON || PANEL_TTL || PANEL_LVDS )
	msWriteByte ( BK7_09_CHIPTOP, 0x00 );
	msWriteByte ( BK7_0A_CHIPTOP, 0x00 );
	msWriteByte ( BK7_0B_CHIPTOP, 0x00 );
	msWriteByte ( BK7_0C_CHIPTOP, 0x00 );
	msWriteByte ( BK7_0D_CHIPTOP, 0x00 );
	msWriteByte ( BK7_0E_CHIPTOP, 0x00 );
	msWriteByte ( BK7_0F_CHIPTOP, 0x00 );
	#endif

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	#endif
}

void OSDGammaInit ( void )
{
	Osd_InitOSD();
	msInitGamma(); // programming gamma table
}

//*******************************************************************
// Function Name: msSetupInputPort
//
// Decscription: setup input port registers for
// Analog/Digital/YCbCr(Video) input
//
// caller: mSar_WriteByte(), msReadByte() in ms_rwreg.c
// callee: msMonitorInputTiming() in detect.c
//*******************************************************************
#if ((MST_CHIP == MST716A) || (MST_CHIP == MST717A) || (MST_CHIP == MST726A))
void SwitchInputPort ( InputPortType PortSwitch )
{
	BYTE bk1_2F_value;
	BYTE bk1_90_mask = 0;

	switch ( PortSwitch )
	{
	case Input_CVBS1:
		bk1_2F_value = CVBS1_RealPortSet;
		break;

	case Input_CVBS2:
		bk1_2F_value = CVBS2_RealPortSet;
		break;

	default:
		break;
	}

	#ifdef _EnableFCC_
	msWriteRegsTbl ( tVideoFCC );
	msWriteRegsTbl(t_TVInitializeFCC);
	msWriteRegsTbl ( t_AVInitializeFCC );
	#endif
	
	//if (bk1_2F_value==PORT_CVBS_SV1C)
	//bk1_90_mask=_BIT3;

	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_2F, bk1_2F_value );

	bk1_2F_value = msReadByte ( BK1_90_SARADC_CTRL );
	bk1_2F_value &= ~_BIT3;
	msWriteByte ( BK1_90_SARADC_CTRL, bk1_2F_value | bk1_90_mask );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
}
#elif (MST_CHIP == MST710A )
void SwitchInputPort ( InputPortType PortSwitch )
{
	BYTE bk1_2F_value;
	BYTE bk1_90_mask = 0;

	switch ( PortSwitch )
	{
		case Input_CVBS1:
			bk1_2F_value = CVBS1_RealPortSet;
			break;

		case Input_CVBS2:
			bk1_2F_value = CVBS1_RealPortSet;
			break;

		default:
			break;
	}

	#ifdef _EnableFCC_
	msWriteRegsTbl ( tVideoFCC ); // Nelson 2006-03-25 Add
	msWriteRegsTbl(t_TVInitializeFCC);
	// msWriteRegsTbl ( t_AVInitializeFCC );
	#endif

	if ( bk1_2F_value == PORT_CVBS_SV1C )
	{
		bk1_90_mask = _BIT3;
	}

	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_2F, bk1_2F_value );

	bk1_2F_value = msReadByte ( BK1_90_SARADC_CTRL );
	bk1_2F_value &= ~_BIT3;
	msWriteByte ( BK1_90_SARADC_CTRL, bk1_2F_value | bk1_90_mask );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
}

#elif (MST_CHIP == MST720A || MST_CHIP == MST712CX)
void SwitchInputPort ( InputPortType PortSwitch )
{
	BYTE bk1_2F_value;
	BYTE bk1_90_mask = 0;

	switch ( PortSwitch )
	{
	case Input_CVBS1:
		bk1_2F_value = CVBS1_RealPortSet;
		//bk1_90_mask=_BIT3;
		break;

	case Input_CVBS2:
		bk1_2F_value = CVBS2_RealPortSet;
		//bk1_90_mask=_BIT3;
		break;
		// case Input_SVIDEO1:
		// default:
		// bk1_2F_value=SVIDEO1_RealPortSet;
		// break;
	}

	#ifdef _EnableFCC_
	msWriteRegsTbl ( tVideoFCC ); // Nelson 2006-03-25 Add
	msWriteRegsTbl(t_TVInitializeFCC);
	msWriteRegsTbl ( t_AVInitializeFCC );
	#endif
	
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_2F, bk1_2F_value );

	bk1_2F_value = msReadByte ( BK1_90_SARADC_CTRL );
	bk1_2F_value &= ~_BIT3;
	msWriteByte ( BK1_90_SARADC_CTRL, bk1_2F_value | bk1_90_mask );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
}

#elif (MST_CHIP >= MST702)
void SwitchInputPort ( InputPortType PortSwitch )
{
	BYTE bk6_03_mask;

	switch ( PortSwitch )
	{
		case Input_CVBS1:
			bk6_03_mask = CVBS1_RealPortSet;
			break;

		case Input_CVBS2:
			bk6_03_mask = CVBS2_RealPortSet;
			break;

		default:
			break;
	}

	#ifdef _EnableFCC_
	msWriteRegsTbl ( tVideoFCC ); // Nelson 2006-03-25 Add
	msWriteRegsTbl(t_TVInitializeFCC);
	msWriteRegsTbl ( t_AVInitializeFCC );
	#endif
	
	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	msWrite2BytesMask_16bitADDR ( BK6s00_03h_ADC_ATOP, bk6_03_mask, 0xFF );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
}

#endif


void SetChromaMode ( void )
{
	BYTE ucBank, val;
	switch ( g_VideoSetting.VideoColorSys % CHROMA_NUMS )
	{
	case CHROMA_PAL:
		val = 0x02;
		break;

	case CHROMA_NTSC:
	default:
		val = 0x01;
		break;
	}
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
	msWriteByteMask ( BK3_1C_CTRLSWCH, val, 0x03 );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msLineBufferDelayCtl ( BOOL bInterlace )
{
	BYTE ucBank, ucTmp = 0;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	if ( bInterlace )
	{
		ucTmp = 0x10;
	}

	else
	{
		ucTmp = 0x20;
	}

	msWriteByte ( BK0_0F_ASCTRL, ucTmp );
	msWriteByte ( BK0_00_REGBK, ucBank );
}

// BYTE msCalculateVSyncTime(void)
// {
// WORD wHFreqX10; // horizontal frequency

// wHFreqX10 = msCalculateHFreqX10( (WORD)msGetHorizontalPeriod() ); // calculate HSync frequency
// return (BYTE)((( (WORD)msGetVerticalTotal() * 10 ) + (wHFreqX10 / 2)) / wHFreqX10);
// }


// <Function>: msSetInterrupt
//
// <Description>: Set chip interrrupt.
//
// <Parameter>: - <Flow> - <Description>
//-----------------------------------------------------------------------------
// IntSel - In - interrupt setting
void msSetInterrupt ( msInterruptType IntSel )
{
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	msWriteByte ( BK0_1D_INTENC, 0x00 ); // Interrupt enable control byte C
	msWriteByte ( BK0_1F_INTEND, 0x00 ); // Interrupt enable control byte D

	switch ( IntSel )
	{
	case INTERRUPT_PC:
		msWriteByte ( BK0_1F_INTEND, 0x0E ); // V change,H loss,V loss
		break;

	case INTERRUPT_YPBPR:
		msWriteByte ( BK0_1F_INTEND, 0x06 ); // H loss,V loss
		break;

	case INTERRUPT_INPUT_VSYNC:
		msWriteByte ( BK0_1D_INTENC, 0x40 ); // H loss,V loss
		break;

	default:
		break;
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void ChipPowerUpcontrol ( void )
{
	BYTE vbk0_e0, vbk0_e1, vbk1_31, vbk1_32, ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );

	vbk0_e0 = 0x80;
	vbk0_e1 = 0x1C;
	vbk1_31 = 0x24;
	vbk1_32 = 0x76;
	
	#if (SCALER_TYPE==MARIA9)
	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	msWrite2BytesMask_16bitADDR ( BK6s00_04h_ADC_ATOP, 0/*0x0200*/, 0x7FFF );
	msWrite2BytesMask_16bitADDR ( BK6s00_05h_ADC_ATOP, 0x0, 0x0007 );
	#endif

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER ); // switch to Bank 1
	msWriteByte ( BK0_E0_PDMD0, vbk0_e0 );
	msWriteByte ( BK0_E1_PDMD1, vbk0_e1 );
	Delay1ms ( 5 );
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // switch to Bank 1
	msWriteByte ( BK1_31, vbk1_31 );
	msWriteByte ( BK1_32, vbk1_32 );

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msNLCCurveInit ( void )
{
	g_NLCContrast.X0 = INIT_VIDEO_CONTRAST_X0;
	g_NLCContrast.X1 = INIT_VIDEO_CONTRAST_X1;
	g_NLCContrast.X2 = INIT_VIDEO_CONTRAST_X2;
	g_NLCContrast.X3 = INIT_VIDEO_CONTRAST_X3;
	g_NLCContrast.X4 = INIT_VIDEO_CONTRAST_X4;

	g_NLCBrightness.X0 = INIT_VIDEO_BRIGHTNESS_X0;
	g_NLCBrightness.X1 = INIT_VIDEO_BRIGHTNESS_X1;
	g_NLCBrightness.X2 = INIT_VIDEO_BRIGHTNESS_X2;
	g_NLCBrightness.X3 = INIT_VIDEO_BRIGHTNESS_X3;
	g_NLCBrightness.X4 = INIT_VIDEO_BRIGHTNESS_X4;

	g_NLCSaturation.X0 = INIT_VIDEO_SATURATION_X0;
	g_NLCSaturation.X1 = INIT_VIDEO_SATURATION_X1;
	g_NLCSaturation.X2 = INIT_VIDEO_SATURATION_X2;
	g_NLCSaturation.X3 = INIT_VIDEO_SATURATION_X3;
	g_NLCSaturation.X4 = INIT_VIDEO_SATURATION_X4;
}

#if (SCALER_TYPE == MARIA9)
void NEW_ADCSetting ( void )
{
	BYTE XDATA ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	//input mux setup
	msWrite2BytesMask_16bitADDR ( BK6s00_01h_ADC_ATOP, _BIT1, _BIT2 | _BIT1 | _BIT0 );
	//input mux
	msWrite2BytesMask_16bitADDR ( BK6s00_02h_ADC_ATOP, 0, _BIT14 );
	msWrite2BytesMask_16bitADDR ( BK6s00_02h_ADC_ATOP, 0, _BIT7 | _BIT6 );
	msWrite2BytesMask_16bitADDR ( BK6s00_02h_ADC_ATOP, _BIT4, _BIT5 | _BIT4 );
	msWrite2BytesMask_16bitADDR ( BK6s00_02h_ADC_ATOP, 0, _BIT3 | _BIT2 );
	msWrite2BytesMask_16bitADDR ( BK6s00_03h_ADC_ATOP, _BIT11 + _BIT8/*5*/, _BIT12 | _BIT11 | _BIT9 | _BIT8 );
	//Clock Setup
	msWrite2BytesMask_16bitADDR ( BK6s00_06h_ADC_ATOP, 0x04D8, 0x07FF );
	msWrite2BytesMask_16bitADDR ( BK6s00_45h_ADC_ATOP, _BIT0, _BIT1 | _BIT0 );
	//msWrite2BytesMask_16bitADDR(BK6s00_39h_ADC_ATOP,0x0,_BIT12);
	msWrite2BytesMask_16bitADDR ( BK6s00_22h_ADC_ATOP, 0x30, 0x00FF );
	//CVBS active filter
	msWrite2BytesMask_16bitADDR ( BK6s00_28h_ADC_ATOP, 1, 0x000F );
	//Vclamp
	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	msWrite2BytesMask_16bitADDR ( BK6s00_28h_ADC_ATOP, _BIT8/*1*/, _BIT8 );
	//SOG
	//msWrite2BytesMask_16bitADDR(BK6s00_29h_ADC_ATOP,_BIT13,_BIT13);
	//msWrite2BytesMask_16bitADDR(BK6s00_2Ah_ADC_ATOP,0/*1*/,_BIT3|_BIT2|_BIT1|_BIT0);//Sel SOG0
	//msWrite2BytesMask_16bitADDR(BK6s00_2Bh_ADC_ATOP,0x20,0x003F);
	//msWrite2BytesMask_16bitADDR(BK6s00_2Bh_ADC_ATOP,0,_BIT11|_BIT10);
	msWrite2BytesMask_16bitADDR ( BK6s00_2Ch_ADC_ATOP, _BIT0, _BIT0 ); //power down SOG
	//HSYNC,VSYNC
	msWrite2BytesMask_16bitADDR ( BK6s00_20h_ADC_ATOP, 0, _BIT2 | _BIT1 | _BIT0 );

	//VD PLL
	#if ENABLE_VD_32FSC
	msWrite2BytesMask_16bitADDR ( BK6s00_0Ah_ADC_ATOP, 0xC100, 0xFF00 );
	#else//For 8FSC
	msWrite2BytesMask_16bitADDR ( BK6s00_0Ah_ADC_ATOP, 0xB000, 0xFF00 );
	#endif

	//ATOP_34[12:10] = 3��h100 // For ADC current change to 22mA
	msWrite2BytesMask_16bitADDR ( BK6s00_34h_ADC_ATOP, _BIT12, _BIT12 | _BIT11 | _BIT10 );
	//gain offset setup
	msWriteByte ( BK0_00_REGBK, REG_BANK6s01_ADCDTOP );
	msWrite2BytesMask_16bitADDR ( BK6s01_51h_ADC_DTOP, 0x57, 0x007F );
	msWrite2BytesMask_16bitADDR ( BK6s01_51h_ADC_DTOP, _BIT10 | _BIT8, _BIT10 | _BIT9 | _BIT8 );
	//adcg gain offset
	msWrite2BytesMask_16bitADDR ( BK6s01_47h_ADC_DTOP, 0x3C0, 0x0FFF );
	msWrite2BytesMask_16bitADDR ( BK6s01_49h_ADC_DTOP, 0x3C0, 0x7FFF );
	msWriteByte ( BK0_00_REGBK, REG_BANK7_CHIPTOP );
	#if ENABLE_VD_32FSC
	msWrite2BytesMask_16bitADDR ( BK7_22h_CHIPTOP, 0, _BIT3 | _BIT2 );
	#else//For 8FSC
	msWrite2BytesMask_16bitADDR ( BK7_22h_CHIPTOP, _BIT5 | _BIT3 | _BIT1, 0x003F );
	#endif


	//Auto phase
	msWriteByte ( BK0_00_REGBK, REG_BANK6s01_ADCDTOP );
	msWrite2BytesMask_16bitADDR ( BK6s01_5Ch_ADC_DTOP, _BIT2/*1*/, _BIT2 );
	msWrite2BytesMask_16bitADDR ( BK6s01_44h_ADC_DTOP, _BIT14/*4*/, _BIT14 | _BIT13 | _BIT12 );
	msWrite2BytesMask_16bitADDR ( BK6s01_47h_ADC_DTOP, _BIT14/*4*/, _BIT14 | _BIT13 | _BIT12 );
	msWrite2BytesMask_16bitADDR ( BK6s01_4Ah_ADC_DTOP, _BIT14/*4*/, _BIT14 | _BIT13 | _BIT12 );

	msWriteByte ( BK0_00_REGBK, ucBank );
}
#endif

void msSetupInputPort ( void )
{
	// printf ( "\r\n InputPort=%x", g_VideoSetting.InputType );
	SwitchInputPort ( g_VideoSetting.InputType );
	ChipPowerUpcontrol();
	msNLCCurveInit();

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK0_0D_LYL, 0x03 );

	msWriteByte ( BK0_10_COCTRL1, COCTRL1_VALUE );

	//msWriteByte( BK0_00_REGBK, REG_BANK3_COMB );
	//msWriteBit( BK3_11_COMBCFGB, 1, _BIT5 ); // Patch IC
	
	msWriteByte(BK0_00_REGBK, REG_BANK_SCALER);
	msWriteBit( BK0_0E_INTLX, 0, _BIT4);	
			
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_24, 0x40 );
	msWriteByte ( BK1_25, 0x01 ); // FPLL_DIVN => Divide by 2
	msWriteByte ( BK1_29, 0x1F ); // 20051007
	msWriteByte ( BK1_2C, 0xF0 ); // 20050624 David.Shen: I clamp

	// Reset ADC register for internal VD
	msWriteByte ( BK1_04_RGAIN_ADC, 0x80 );
	msWriteByte ( BK1_05_GGAIN_ADC, 0x80 );
	msWriteByte ( BK1_06_BGAIN_ADC, 0x80 );
	msWriteByte ( BK1_07_ROFFS_ADC, 0x80 );
	msWriteByte ( BK1_08_GOFFS_ADC, 0x80 );
	msWriteByte ( BK1_09_BOFFS_ADC, 0x80 );
	msWriteByte ( BK1_18_CALEN, 0 );

	if( g_ucmsVDCtl & MSVD_CTL_FLAG_NOISE_HANDLER )
	{
		msVDNoiseHandlerReset();
	}

	#if (SCALER_TYPE==MARIA9)
	NEW_ADCSetting ( );
	#endif
	
	msWriteRegsTbl ( tProgMsAvPort ); // program CVBS port
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	msWriteByteMask ( BK2_1A_SVD_EN, 0x00, 0xC0 ); // Disable SV
	msWriteBit ( BK2_1F, 0, _BIT7 ); // Disable clamp C
	msWriteByte ( BK2_7F, 0x63 );
	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
	msWriteBit ( BK3_10_COMBCFGA, 0, _BIT7 ); // Enable comb filter
	msWriteBit ( BK3_A1_SCM_IDSET1, 0, _BIT3 ); // Disable Secam-SV

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msVDCombLineBufferCtl ( MSVD_COMB_LINE_BUFFER_CTL_HW_AUTO );

	// tv settings
	// #if (SCALER_TYPE==MARIA9)
	// NEW_ADCSetting(SRCTYPE_CVBS);
	// #endif
	// msWriteByte(BK0_00_REGBK, REG_BANK2_VD);
	// msWriteBit( BK2_38_VSTROBE_LIMIT, 1,_BIT7);

	// msWriteByte(BK0_00_REGBK, REG_BANK3_COMB);
	// msWriteByte( BK3_63_REG_CTST, 0x80);
	// msWriteByte( BK3_64_REG_BRHT, 0x80);
	// msWriteByte( BK3_2F, 0x00 ); // IF_COEF for tuner input
	// msWriteByte(BK3_24_TH2DHOR, 0x0A); // C-Trap disable: For PAL-DEM
	// msWriteByteMask(BK3_21_COMB2DCFGB, 0x00, 0x08); //

	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	msWriteBit ( BK2_38_VSTROBE_LIMIT, 0, _BIT7 );

	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
	msWriteByte ( BK3_63_REG_CTST, INIT_MSVD_COMB_CONTRAST );
	msWriteByte ( BK3_64_REG_BRHT, INIT_MSVD_COMB_BRIGHTNESS );
	//msWriteByte( BK3_2F, 0x00 );
	
	msWriteByte ( BK3_24_TH2DHOR, 0x20 ); // C-Trap disable: For PAL-DEM
	msWriteByteMask ( BK3_21_COMB2DCFGB, 0x08, 0x08 ); //

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	
	msLineBufferDelayCtl ( 0 ); // For Change source
	msFieldDetectCtl();

	#if(ENABLE_VD_DSP)
	//g_ucmsVDCtl |= MSVD_CTL_FLAG_VSYNC;
	#endif
	
	//msVD_FSM_Reset();
	
	msVDReset(); // When change source

	msSetUserPref();
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
}
//*******************************************************************
// Function Name: msPowerUp
//
// Decscription: Power on chip from power down mode
//
// callee: msWriteByte() in ms_rwreg.c
//
// caller: Power_PowerOnSystem() in power.c
//*******************************************************************
/*
void msPowerUp ( void )
{
 msWriteByte ( BK0_21_PLLCTRL2, 0 ); // power on master & output PLL
 msWriteByte ( BK0_E2_SWRST0, OP2R_B | ADCR_B ); // reset graphic port RO register
 msWriteByte ( BK0_E2_SWRST0, 0 );

 ChipPowerUpcontrol();

 Delay1ms ( 5 ); //(50);
 msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // switch to Bank 1

#if PANEL_ANALOG_TCON
 msWriteByte ( BK1_A9_PD_VDAC, 0x00 );
#else
 msWriteByte ( BK1_4C, 0x5F );
#endif

 msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER ); // switch to Bank 0
 Delay1ms ( 5 ); //(50);
 msWriteByte ( BK0_F4_TRISTATE, 0 );

#if ENABLE_MCU_USE_INTERNAL_CLOCK
 if ( g_bMcuUseNewClock == 0 )
 {
 McuUseInternalClock();
 }
#endif
}
*/

// <Function>: msSoftwareReset
//
// <Description>: MST chip software reset.
//
// <Parameter>: - <Flow> - <Description>
//-----------------------------------------------------------------------------
// ucParam - In - Software reset parameter
// ucDelayTime - In - Delay time(unit: 1ms)
void msSoftwareReset ( BYTE wParam, BYTE ucDelayTime )
{
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK0_E2_SWRST0, wParam );
	Delay1ms ( ucDelayTime );
	msWriteByte ( BK0_E2_SWRST0, 0x00 );
}

//*******************************************************************
// Function Name: msPowerDown
//
// Decscription: Power down chip
//
// callee: msWriteByte() in ms_rwreg.c
//
// caller: Power_PowerOffSystem() in power.c
//*******************************************************************
void msPowerDown ( void )
{
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	#if ENABLE_MCU_USE_INTERNAL_CLOCK
	msWriteByte ( BK0_EE_PDMD2, 0 );
	g_bMcuUseNewClock = 0;
	#endif

	msWriteByte ( BK0_F4_TRISTATE, 0xFF );
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // switch to Bank 1
	msWriteByte ( BK1_31, 0x7F );
	msWriteByte ( BK1_32, 0xFF );

	msWriteByte ( BK1_45, 0x01 );

	#if PANEL_ANALOG_TCON
	msWriteByte ( BK1_A9_PD_VDAC, 0x0F );
	#else
	msWriteByte ( BK1_4C, 0x5F );
	#endif

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER ); // switch to Bank 0
	msWriteByte ( BK0_E0_PDMD0, 0xB0 );
	msWriteByte ( BK0_E1_PDMD1, 0xFF );

	#if (SCALER_TYPE==MARIA9)
	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	msWrite2BytesMask_16bitADDR ( BK6s00_04h_ADC_ATOP, 0x07FFF, 0x07FFF );
	msWrite2BytesMask_16bitADDR ( BK6s00_05h_ADC_ATOP, 0x0007, 0x0007 );
	#endif

	msWriteByte ( BK0_00_REGBK, ucBank );

	TH1 = TIMER1_MODE2_TH1; // set timer1(buad rate)
	TR1 = 1; // timer1 run
	PX1 = 1; // set INT1 priority high //Nicolee 20051231 add for low power mode ir power on set

}

#if LED_BACKLIGHT 
void msSetBacklight ( BYTE val )
{
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK4_LVDS_CCFL );

	msWriteByte ( BK4_6B, 0xFF ); // unlock PWM settings
	msWriteByte ( BK4_9A, 0xCF ); // unlock reg key=0xCF
	msWriteByte ( BK4_B0,  val );
	msWriteByte ( BK4_B1, 0x00 ); // ignore high 2-bits
	msWriteByte ( BK4_6B, 0x00 ); // lock PWM settings

	msWriteByte ( BK0_00_REGBK, ucBank );
}
#endif

#if BACKLIGHT_PWM == PWM_TYPE_PWM3 
void msSetBacklight ( BYTE val )
{
// #define BK3_F3_PWMCLK 0xF3
// #define BK3_F4_PWM3C 0xF4
// #define BK3_F5_PWM4C 0xF5
// #define BK3_F6_PWM3EPL 0xF6
// #define BK3_F7_PWM3EPH 0xF7
// #define BK3_F8_PWM4EPL 0xF8
// #define BK3_F9_PWM4EPH 0xF9

	BYTE ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );

	msWriteByte ( BK3_F3_PWMCLK, 0x07 );
	msWriteByte ( BK3_F4_PWM3C, ~val & ~0x80 );
	msWriteByte ( BK3_F6_PWM3EPL, 0xFF );
	msWriteByte ( BK3_F7_PWM3EPH, 0x7F );

	msWriteByte ( BK0_00_REGBK, ucBank );
}
#endif

#ifdef EnableUseGammaTbl
void LoadGammaTbl ( void )
{
	BYTE i;
	BYTE count;

	msWriteByte ( BK0_91_GAMMA_ADR_PORT, 0x00 );
	msWriteByte ( BK0_90_GAMMA_EN, msReadByte ( BK0_90_GAMMA_EN ) | _BIT1 );

	for ( i = 0; i < 3; i++ )
	{
		for ( count = 0; count < 33; count++ )
		{
			msWriteByte ( BK0_92_GAMMA_DAT_PORT, tGammaTableNormal[i][count] );
		}
	}
}
#endif

void msInitGamma ( void )
{
	msWriteByte ( BK0_90_GAMMA_EN, GAMMA_EN_B );
	#ifdef EnableUseGammaTbl
	LoadGammaTbl();
	#endif
}

void SystemDelay_translate_To_Dsp_Processor ( BYTE wDelaycount )
{
	BYTE i;

	for ( i = 0; i < wDelaycount; i ++ )
	{
		Delay1ms ( 10 );
		#if( ENABLE_VD_DSP&&((DSP_RUN_MODE == DSP_RUN_MODE_POLLING)||(DSP_RUN_MODE == DSP_RUN_MODE_TIMER_AND_POLLING)) )

		if ( g_ucmsVDCtl & MSVD_CTL_FLAG_VSYNC )
		{
			VD_DSP();
		}

		#endif
	}
}

void Delay1ms_AGC_Processor ( WORD wDelaycount )
{
	if ( PowerOnFlag )
	{
		AGC_Processor();

		while ( wDelaycount )
		{
			if ( wDelaycount > 20 )
			{
				Delay1ms ( 20 );
				wDelaycount -= 20;
				AGC_Processor();
			}

			else
			{
				Delay1ms ( wDelaycount );
				wDelaycount = 0;
			}
		}

		AGC_Processor();
	}

	else
	{
		Delay1ms ( wDelaycount );
	}
}

WORD GetStdModeHFreq ( BYTE ucModeIdx )
{
	return tStandardMode[ucModeIdx].HFreq;
}

WORD GetStdModeHTotal ( BYTE ucModeIdx )
{
	return tStandardMode[ucModeIdx].HTotal;
}

WORD msCalculateHFreqX10 ( WORD wHPeriod )
{
	return ( ( ( ( DWORD ) MST_CLOCK_KHZ * 10 ) + ( wHPeriod / 2 ) ) / wHPeriod ); // kHz
}

WORD msGetHorizontalPeriod ( void )
{
	WORD wHorizontalPeriod;
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	wHorizontalPeriod = ( msReadWord ( BK0_EB_HSPRD_H ) & MST_H_PERIOD_MASK );
	msWriteByte ( BK0_00_REGBK, ucBank );
	return wHorizontalPeriod;
}

WORD msGetVerticalTotal ( void )
{
	WORD wVerticalTotal;
	BYTE ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	wVerticalTotal = ( msReadWord ( BK0_ED_VTOTAL_H ) & MST_V_TOTAL_MASK );

	msWriteByte ( BK0_00_REGBK, ucBank );
	return wVerticalTotal;
}

void GetInputSignalHV ( void )
{
	g_InOutCtl.inHPeriod = msGetVideoHPeriod ( 2 );
	g_InOutCtl.inVTotal = msVDGetVTotal();
	g_InOutCtl.inHFreq = MST_CLOCK_HZ / g_InOutCtl.inHPeriod;
	g_InOutCtl.inOutVFreq = ( g_InOutCtl.inHFreq + ( g_InOutCtl.inVTotal / 2 ) ) / g_InOutCtl.inVTotal;

	if ( g_InOutCtl.bInterlace )
	{
		g_InOutCtl.inOutVFreq *= 2;
	}

	// printf("\r\n\r\ninHP=%d",g_InOutCtl.inHPeriod);
	// printf("\r\ninHF=%d",g_InOutCtl.inHFreq);
	// printf("\r\ninVT=%d",g_InOutCtl.inVTotal);
	// printf("\r\nInOutVFreq=%d", g_InOutCtl.inOutVFreq);
}

void msSetOutputSyncControl ( BYTE ucOutputTimingCtl )
{
	BYTE ucBk0_57;

	ucBk0_57 = _BIT6; // Frame lock mode 1

	#if (PANEL_SYNC_MODE_1)
	ucBk0_57 |= _BIT7; // Output v sync manually
	#endif

	ucBk0_57 |= _BIT2; // Scaling range add 1

	if ( ! ( ucOutputTimingCtl & OUTPUT_FREERUN ) )
	{
		ucBk0_57 |= _BIT1;
	}

	msWriteByte_Bank_BackupBank ( REG_BANK_SCALER, BK0_57_OSCTRL1, ucBk0_57 );
}

void SetScalingRatio ( BOOL bInterlace )
{
	BYTE ucBank; // bank buffer
	DWORD dwTemp;
	WORD wInputVSize;

	ucBank = msReadByte ( BK0_00_REGBK ); // store bank
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	g_WindowInfo.V_DisSize = PanelVSiEnd;

	// printf("\r\nSCALING_H_IN=%d", SCALING_H_IN);
	// printf("\r\nSCALING_H_OUT=%d", SCALING_H_OUT);
	// printf("\r\nSCALING_V_IN=%d", SCALING_V_IN);
	// printf("\r\nSCALING_V_OUT=%d", SCALING_V_OUT);

	// Horizontal
	if ( SCALING_H_IN == SCALING_H_OUT )
	{
		dwTemp = 0;
		g_WindowInfo.H_ScalingRatioInfo = SCALING_RATIO_TYPE_NATIVE;
	}

	else
	{
		if ( SCALING_H_IN < SCALING_H_OUT )
		{
			g_WindowInfo.H_ScalingRatioInfo = SCALING_RATIO_TYPE_UP;
			dwTemp = 0;
		}

		else // if( SCALING_H_IN > SCALING_H_OUT )
		{
			g_WindowInfo.H_ScalingRatioInfo = SCALING_RATIO_TYPE_DOWN;
			dwTemp = ScalingRatio_H ( SCALING_H_IN, SCALING_H_OUT );

			// printf("ScalingRatio_H===%x", dwTemp / 0x100); //get high 2 bytes

			dwTemp &= 0xFFF000;

			if ( dwTemp > 0xFF000 )
			{
				dwTemp |= 0x800000;
			}

			else
			{
				dwTemp |= 0xC00000;
			}
		}
	}

	msWrite3Bytes ( BK0_32_SRH_H, dwTemp );

	wInputVSize = SCALING_V_IN;

	// Vertical
	if ( bInterlace )
	{
		wInputVSize = wInputVSize / 2;
	}

	if ( wInputVSize == SCALING_V_OUT )
	{
		dwTemp = 0;
		g_WindowInfo.V_ScalingRatioInfo = SCALING_RATIO_TYPE_NATIVE;
	}

	else
	{
		if ( wInputVSize < SCALING_V_OUT )
		{
			g_WindowInfo.V_ScalingRatioInfo = SCALING_RATIO_TYPE_UP;
		}

		else // ( wInputVSize > SCALING_V_OUT ) // Scaling down
		{
			g_WindowInfo.V_ScalingRatioInfo = SCALING_RATIO_TYPE_DOWN;
		}

		#if (ENABLE_V_PRE_SCALING_DOWN)

		if ( g_WindowInfo.V_ScalingRatioInfo & SCALING_RATIO_FLAG_PRE )
		{
			dwTemp = PRE_SCALING_RATIO_V ( SCALING_V_IN, SCALING_V_OUT );

			if ( bInterlace )
			{
				dwTemp = dwTemp << 1;
			}

			dwTemp |= 0xC00000;
		}

		else
		#endif
		{
			dwTemp = ScalingRatio_V ( SCALING_V_IN, SCALING_V_OUT );

			if ( bInterlace )
			{
				dwTemp = ( dwTemp + 1 ) >> 1;
			}

			dwTemp &= 0xFFF000;

			if ( dwTemp > 0x3FFFFF )
			{
				dwTemp = 0x3FFFFF;
			}

			dwTemp &= 0x3FFFFF;
			dwTemp |= 0x800000;
		}
	}

	//printf("\r\nVScaleRatio=0x%xXX", dwTemp>>8);

	msWrite3Bytes ( BK0_35_SRV_H, dwTemp );

	#if(ENABLE_V_PRE_SCALING_DOWN)

	if ( ( g_WindowInfo.V_ScalingRatioInfo & SCALING_RATIO_FLAG_PRE ) && ( !bInterlace ) )
	{
		msWriteBit ( BK0_C3, 1, _BIT6 );
	}

	else
	{
		msWriteBit ( BK0_C3, 0, _BIT6 );
	}

	#endif

	msWriteByte ( BK0_00_REGBK, ucBank ); // recovery bank
}

void CalculateAspectRatio ( void )
{
	#if(ENABLE_OVER_SCAN)
	WORD wTemp;
	BYTE ucOverScanH;
	BYTE ucOverScanV;

	// Get over scan ratio
	ucOverScanH = g_ucOverScanH;
	ucOverScanV = g_ucOverScanV;

	// Cal Over scan
	if ( ucOverScanH )
	{
		wTemp = ( DWORD ) g_WindowInfo.H_CapSize * g_ucOverScanH / 1000;
		//g_WindowInfo.H_CapStart += wTemp;
		g_WindowInfo.H_CapSize -= ( 2 * wTemp );
	}

	if ( ucOverScanV )
	{
		wTemp = ( DWORD ) g_WindowInfo.V_CapSize * g_ucOverScanV / 1000;
		//g_WindowInfo.V_CapStart += wTemp;
		g_WindowInfo.V_CapSize -= ( 2 * wTemp );
	}

	#endif
}

void msSetupFreeRunMode ( BYTE ucVFreq )
{
	BYTE ucBank; // bank buffer

	ucBank = msReadByte ( BK0_00_REGBK ); // backup bank
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	//printf("\r\nSetFreeRunMode(%d)", ucVFreq);

	g_InOutCtl.inOutVFreq = ucVFreq;

	SetDisplayWindow();

	msSetOutputTiming ( OUTPUT_FREERUN );
	msWriteRegsTbl ( tFreeRunModeTbl );

	Set_FreeRunModeFlag();

	msWriteByte ( BK0_00_REGBK, ucBank ); // recovery bank
}

void msSetOutputTiming ( BYTE ucOutputTimingCtl )
{
	BYTE ucBank; // bank buffer
	ucBank = msReadByte ( BK0_00_REGBK ); // store bank

	//printf("\r\nmsSetOutputTiming(%x)", ucOutputTimingCtl);

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	msSetOutputSyncControl ( ucOutputTimingCtl );

	if ( ucOutputTimingCtl & OUTPUT_FREERUN )
	{
		msWriteWord ( BK0_4F_VDTOT_H, PanelVTotal - 1 ); // output vtotal
		msWriteWord ( BK0_55_HDTOT_H, PanelHTotal - 1 ); // output htotal
	}

	else // OUTPUT_SIG & OUTPUT_SNOW
	{
		msWriteWord ( BK0_4F_VDTOT_H, 0x7FF ); // output vtotal
	}

	SetOutputClock ( ucOutputTimingCtl );
	msWriteByte ( BK0_00_REGBK, ucBank );
}

void SetCaptureWindow()
{
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK ); // store bank
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	msWriteWord ( BK0_06_SPRVST_H, g_WindowInfo.V_CapStart );
	msWriteWord ( BK0_08_SPRHST_H, g_WindowInfo.H_CapStart );
	msWriteWord ( BK0_0A_SPRVDC_H, g_WindowInfo.V_CapSize );
	msWriteWord ( BK0_0C_SPRHDC_H, g_WindowInfo.H_CapSize + 8 );

	#if(ENABLE_MONITOR_VTOTAL)
	msMonitorVTotal ( 1 ); // Init
	#endif

	msWriteByte ( BK0_00_REGBK, ucBank ); // recovery bank
}

void SetDisplayWindow()
{
	BYTE ucBank; // bank buffer

	ucBank = msReadByte ( BK0_00_REGBK ); // store bank value
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	msWriteWord ( BK0_49_SIHST_H, PanelHStart ); // Scaling Image H start
	msWriteWord ( BK0_4D_SIHEND_H, PanelHStart + PanelWidth - 1 ); // Scaling Image H end

	msWriteWord ( BK0_41_VFDEST_H, PANEL_DE_VSTART ); // DE start
	msWriteWord ( BK0_45_VFDEEND_H, PanelVdeEnd - 1 ); // DE end

	msWriteWord ( BK0_4B_SIVEND_H, PanelVSiEnd - 1 ); // Scaling image end

	msWriteByte ( BK0_00_REGBK, ucBank ); // restore bank value
}

void msProgDigitalWin ( BYTE ucOutputTimingCtl )
{
	BYTE ucVideoSystem;

	if ( IsSrcHasSignal() && ( ( ucOutputTimingCtl & 3 ) == 0 ) )
	{
		ucVideoSystem = g_VdInfo.ucVideoSystem;
	}

	else // No signal or Freerun
	{
		if ( g_InOutCtl.inOutVFreq == 50 )
		{
			ucVideoSystem = SIG_PAL;
		}

		else
		{
			ucVideoSystem = SIG_NTSC;
		}
	}

	g_WindowInfo.H_CapStart = tMsVDCapture[ucVideoSystem].VideoHStart;
	g_WindowInfo.V_CapStart = tMsVDCapture[ucVideoSystem].VideoVStart;

	g_WindowInfo.H_CapSize = tMsVDCapture[ucVideoSystem].HRange;
	g_WindowInfo.V_CapSize = tMsVDCapture[ucVideoSystem].VRange;

	CalculateAspectRatio();
	//SetDisplayWindow();
	SetCaptureWindow();
	// SetScalingRatio ( 1 );
	msSetScaler();
	
}

BOOL IsSrcHasSignal ( void )
{
	if ( ( g_VdInfo.ucVideoSystem == SIG_NONE ) || ( ( g_VdInfo.wVideoStatus & VD_HSYNC_LOCKED ) == 0 ) )
	{
		return FALSE;
	}

	return TRUE;
}

void SetOutputTimingAndWindow ( BYTE ucOutputTimingCtl )
{
	// Get input sync info
	if ( IsSrcHasSignal() )
	{
		GetInputSignalHV();
	}

	else // No signal or Freerun
	{
		g_InOutCtl.inOutVFreq = 60;

		if ( g_InOutCtl.inOutVFreq == 50 )
		{
			g_InOutCtl.inHFreq = 15625;
			g_InOutCtl.inVTotal = 625;
		}

		else // 60 Hz
		{
			g_InOutCtl.inHFreq = 15734;
			g_InOutCtl.inVTotal = 525;
		}

		g_InOutCtl.inHPeriod = MST_CLOCK_HZ / g_InOutCtl.inHFreq;
	}

	msProgDigitalWin ( ucOutputTimingCtl );
	msSetOutputTiming ( ucOutputTimingCtl ); // This function must after msProgDigitalWin()
}

void msSetScaler ( void )
{
	#if ( ! WidePanel )
	msLoadModeIndexTBL ( tModeIndexTbl );
	#else

	BYTE ucBank;
	WORD ulNewHsize, uwInput_H_Resol, uwTemp;
	DWORD ulH_Scaling_Factor, ulTemp;

	SetScalingRatio ( g_InOutCtl.bInterlace );

	ucBank = msReadByte ( BK0_00_REGBK ); // store bank
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER ); // bank 1

	if ( g_VideoSetting.Scaling == Scaling_Full )
	{
		// Mask the front and back block
		msWriteWord ( BK0_5D_FRAME_COLOR_2, 0x9EF ); //BK0_5C_FRAME_COLOR_1, BK0_5D_FRAME_COLOR_2


		msWriteWord ( BK0_49_SIHST_H, PanelHStart ); // horizontal DE start
		msWriteWord ( BK0_43_HFDEST_H, PanelHStart ); // horizontal DE start

		msWriteWord ( BK0_4D_SIHEND_H, ( PanelHStart + PanelWidth - 1 ) ); // Image H end
		msWriteWord ( BK0_47_HFDEEND_H, ( PanelHStart + PanelWidth - 1 ) ); // horizontal DE end

		msLoadModeIndexTBL ( tModeIndexTbl );
	}

	else
	{
		msWriteByte ( BK0_38_NLDTI, 0x00 ); // Disable Nonlinear scaling function

		// ulNewHsize=PANEL_DOT_HEIGHT;//X*4/3=>4:3,X/3=>3dot in 1 pixel
		// ulNewHsize=ulNewHsize*PanelHeight;
		// ulNewHsize=ulNewHsize/PANEL_DOT_WIDTH;
		// ulNewHsize=(ulNewHsize*SCAL_RATIO_NUMERATOR)/(SCAL_RATIO_DENOMINATOR*3);

		ulNewHsize = PanelWidth * 3 / 4;
		uwInput_H_Resol = msReadWord ( BK0_0C_SPRHDC_H );//Get Input H resolution

		//New start point
		uwTemp = PanelHStart + ( ( PanelWidth - ulNewHsize ) / 2 ) ;
		msWriteWord ( BK0_49_SIHST_H, uwTemp ); //new Start //BK0_48_SIHST_L, BK0_49_SIHST_H

		//msWriteWord ( BK0_43_HFDEST_H, PanelHStart ); //uwTemp );

		// New end point
		msWriteWord ( BK0_4D_SIHEND_H, uwTemp + ulNewHsize ); //new End //BK0_4C_SIHEND_L, BK0_4D_SIHEND_H

		//msWriteWord ( BK0_47_HFDEEND_H, PanelHStart + PanelWidth ); // horizontal DE end

		// printf ( "\r\nNewHSize: %d", ulNewHsize );
		// printf ( "\r\nstart: %d", uwTemp );
		// printf ( "\r\ninput res: %d", uwInput_H_Resol );

		// Get new scaling factor
		ulH_Scaling_Factor = ( DWORD ) ulNewHsize << 20 ;
		ulTemp = ( DWORD ) uwInput_H_Resol * ( SCAL_CUTOFF_RESOL - SCAL_CUTOFF_H_PER );
		ulH_Scaling_Factor /= ( ulTemp / SCAL_CUTOFF_RESOL );

		// Mask the front and back block
		msWriteWord ( BK0_5D_FRAME_COLOR_2, 0x00 ); //BK0_5C_FRAME_COLOR_1, BK0_5D_FRAME_COLOR_2

		ulH_Scaling_Factor += 0xC00; //0xc00 get from fine tune
		msWriteWord ( BK0_31_SRH_M, ( unsigned int ) ( ulH_Scaling_Factor & 0xFFF000 ) ); //BK0_30_SRH_L,BK0_31_SRH_M
		msWriteByte ( BK0_32_SRH_H, ( unsigned char ) ( ( ulH_Scaling_Factor & 0x0F0000 ) >> 16 ) + 0xC0 );


		// if(g_VdInfo.ucVideoSystem==SIG_NTSC)
			// msWriteRegsTbl(t4_3NtscModeTbl);
		// else
			// msWriteRegsTbl(t4_3PalModeTbl);
	}

	msWriteByte ( BK0_00_REGBK, ucBank ); // bank 1

	#endif
}

void msSetLineBufferClock ( BYTE ucModeIdx, BYTE ucOutputClock )
{
	BYTE ucInputClock;
	BYTE ucBank;
	BYTE ucBk0_36_val = 0; // Use default clock

	ucInputClock = ( ( float ) GetStdModeHTotal ( ucModeIdx ) * GetStdModeHFreq ( ucModeIdx ) ) / 10000;

	if ( ucInputClock > 50 )
	{
		ucBk0_36_val = 0x80; // Using input clock
	}

	else
	{
		ucInputClock = 50;
	}

	if ( ucOutputClock > ucInputClock )
	{
		ucBk0_36_val = 0x40; // Using output clock
	}

	ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, 0 );
	msWriteByteMask ( BK0_36_VDSUSG, ucBk0_36_val, 0xC0 );

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msSetOutputFreeRunClock ( BYTE ucVFreq )
{
	BYTE ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	#if PANEL_ANALOG_TCON

	if ( ucVFreq != 60 )
	{
		msWrite3Bytes ( BK0_27_OPL_SET2, PANEL_FREE_RUN_DCLK_FACTOR * 60 / ucVFreq / 3 );
	}

	else
	{
		msWrite3Bytes ( BK0_27_OPL_SET2, PANEL_FREE_RUN_DCLK_FACTOR / 3 );
	}

	#else

	if ( ucVFreq != 60 )
	{
		msWrite3Bytes ( BK0_27_OPL_SET2, PANEL_FREE_RUN_DCLK_FACTOR * 60 / ucVFreq );
	}

	else
	{
		msWrite3Bytes ( BK0_27_OPL_SET2, PANEL_FREE_RUN_DCLK_FACTOR );
	}

	#endif

	msSetLineBufferClock ( MD_720x480_60I, PANEL_FREE_RUN_DCLK / 1000000 );

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void SetOutputClock ( BYTE ucOutputTimingCtl )
{
	//printf("\r\nmsSetOutputClock(%x)", ucOutputTimingCtl);

	WatchDogClear();

	if ( ucOutputTimingCtl & OUTPUT_FREERUN )
	{
		msSetOutputFreeRunClock ( 60 );
	}

	else // OUTPUT_SIG && OUTPUT_SNOW
	{
		msLCDSetClock();
	}

	WatchDogClear();
}

void msLCDSetClock ( void )
{
	BYTE ucBank;
	XDATA WORD wInputHPeriod; // horizontal period

	XDATA WORD wOutputClock;
	XDATA DWORD dwClockFactor; // clock factor

	wInputHPeriod = g_InOutCtl.inHPeriod;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	wInputHPeriod *= 16;

	// Cal output clock
	// if expansion, chip will assume output clock is faster than input clock,

	//(SCALING_FORMULA)
	#if 1
	wOutputClock = ( ( ( float ) PanelMinHTotal * ( PanelHeight - 1 ) * MST_CLOCK_KHZ * 16 ) + 500 ) / ( ( float ) wInputHPeriod * ( g_WindowInfo.V_CapSize - 1 ) * 1000 );
	#else
	wOutputClock = ( ( ( float ) PanelMinHTotal * ( PanelHeight ) * MST_CLOCK_KHZ * 16 ) + 500 ) / ( ( float ) wInputHPeriod * ( g_WindowInfo.V_CapSize ) * 1000 );
	#endif

	if ( g_InOutCtl.bInterlace )
	{
		wOutputClock *= 2;
	}

	//(SCALING_FORMULA)
	#if 1
	dwClockFactor = ( ( float ) wInputHPeriod * ( g_WindowInfo.V_CapSize - 1 ) * 524288ul * PANEL_MASTER_PLL_DIVIDER ) / ( ( float ) PanelMinHTotal * ( PanelHeight - 1 ) * 16 );
	#else
	dwClockFactor = ( ( float ) wInputHPeriod * ( g_WindowInfo.V_CapSize ) * 524288ul * PANEL_MASTER_PLL_DIVIDER ) / ( ( float ) PanelMinHTotal * ( PanelHeight ) * 16 );
	#endif

	if ( g_InOutCtl.bInterlace )
	{
		dwClockFactor /= 2;
	}

	#if (PANEL_ANALOG_TCON)
	dwClockFactor /= 3;
	#endif

	//dwClockFactor = 7909;

	// printf("\r\ndwClockFactor %d", dwClockFactor);
	// printf("\r\nwOutputClock %d", wOutputClock);
	// printf ( "\r\nDclk %dMhz", 2 * ( DClkFactor + ( dwClockFactor / 2 ) ) / dwClockFactor );

	#if (SCALER_TYPE == MARIA9)
	#if (PANEL_LVDS) //Linix 20100929
	msWrite3Bytes ( BK0_27_OPL_SET2, dwClockFactor >> 1 );
	#else
	msWrite3Bytes ( BK0_27_OPL_SET2, dwClockFactor );
	#endif

	#else

	msWrite3Bytes ( BK0_27_OPL_SET2, dwClockFactor );
	#endif

	msSetLineBufferClock ( g_ucSrcModeIndex, wOutputClock );

	msWriteByte ( BK0_00_REGBK, ucBank );
}

#if(ENABLE_MONITOR_VTOTAL)

XDATA WORD g_wMsMonitorVTotal_OriginalVCapsize;
XDATA WORD g_wMsMonitorVTotal_LastVTotal;
XDATA WORD g_wMsMonitorVTotal_VTotalChangeCnt;

void msMonitorVTotal ( BYTE ucFlag )
{
	BYTE ucBank;
	WORD wCurVTotal;
	bit bVTotalChange = 0;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	wCurVTotal = msVDGetVTotal();

	if ( ucFlag & 1 ) // Reset
	{
		g_wMsMonitorVTotal_OriginalVCapsize = msReadWord ( BK0_0A_SPRVDC_H );
		g_wMsMonitorVTotal_VTotalChangeCnt = 0;
		g_wMsMonitorVTotal_LastVTotal = 0;
		bVTotalChange = 1;
	}

	else
	{
		if ( wCurVTotal != g_wMsMonitorVTotal_LastVTotal )
		{
			g_wMsMonitorVTotal_VTotalChangeCnt ++;

			if ( g_wMsMonitorVTotal_VTotalChangeCnt >= 5 )
			{
				bVTotalChange = 1;
				g_wMsMonitorVTotal_VTotalChangeCnt = 0;
			}
		}

		else
		{
			g_wMsMonitorVTotal_VTotalChangeCnt = 0;
		}
	}

	if ( bVTotalChange )
	{
		WORD wCurVCapsize;

		wCurVCapsize = msReadWord ( BK0_0A_SPRVDC_H );

		// printf("\r\nwCurVTotal: %d", wCurVTotal);
		// printf("\r\nwCurVCapsize: %d", wCurVCapsize);


		if ( ( wCurVCapsize + V_CAP_SIZE_SAFE_RANGE ) > wCurVTotal )
		{
			msWriteWord ( BK0_0A_SPRVDC_H, ( wCurVTotal - V_CAP_SIZE_SAFE_RANGE ) );
		}

		else
		{
			if ( ( g_wMsMonitorVTotal_OriginalVCapsize != wCurVCapsize )
				&& ( ( g_wMsMonitorVTotal_OriginalVCapsize + V_CAP_SIZE_SAFE_RANGE ) <= wCurVTotal ) )
			{
				msWriteWord ( BK0_0A_SPRVDC_H, g_wMsMonitorVTotal_OriginalVCapsize );
			}
		}

		g_wMsMonitorVTotal_LastVTotal = wCurVTotal;
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}
#endif

#if(ENABLE_CHECK_AUTO_H_TOTAL)

WORD msCalculateVFreqX10 ( WORD wHFreq, WORD wVTotal )
{
	return ( ( ( ( DWORD ) wHFreq * 1000 ) + ( wVTotal / 2 ) ) / wVTotal ); // Hz
}

void msCheckBK0_57_Value ( void )
{
	bit bCurAutoHTotalOn ;
	bit bCurSyncStable = 0;
	BYTE ucBank;

	//analog source needs auto htotal, or screen will be wrong (???)
	if ( FreeRunModeFlag )
	{
		msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
		msWriteBit ( BK0_57_OSCTRL1, 1, _BIT1 );
		return;
	}

	if ( g_wCheckBK0_57_Timer )
	{
		return;
	}

	g_wCheckBK0_57_Timer = 10;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	if ( msReadByte ( BK0_57_OSCTRL1 ) & _BIT1 )
	{
		bCurAutoHTotalOn = 1;
	}

	if ( ( msVDGetSyncStatus() & VD_HSYNC_LOCKED ) &&
		( msVDCheckScalerStatus ( 0 ) == 0 ) &&
		( msDSP_Std_GetNoiseMag() < 0xE0 ) )
	{
		bCurSyncStable = 1;
	}

	if ( bCurAutoHTotalOn )
	{
		g_ucCheckSyncCounter = 0;
		g_ucSyncStableCounter = 0;

		if ( !bCurSyncStable )
		{
			msWriteBit ( BK0_57_OSCTRL1, 0, _BIT1 ); // Turn off auto h total

			if ( ( g_VdInfo.ucVideoSystem == SIG_NTSC )  )
			{
				msWriteWord ( BK0_55_HDTOT_H, NtscHTotal ); // output htotal
			}

			else if ( g_VdInfo.ucVideoSystem == SIG_NONE )
			{
				msWriteWord ( BK0_55_HDTOT_H, FreeRunHTotal );
			}

			else
			{
				msWriteWord ( BK0_55_HDTOT_H, PalHTotal ); // output htotal
			}

			// printf ( "\r\nTurn off auto H:Noise=%x", msDSP_Std_GetNoiseMag() );
		}
	}

	else // Current auto h total is off
	{
		if ( g_ucCheckSyncCounter < 20 )
		{
			g_ucCheckSyncCounter ++;

			if ( bCurSyncStable )
			{
				g_ucSyncStableCounter ++;

				if ( ( g_ucCheckSyncCounter == 20 ) && ( g_ucSyncStableCounter == 20 ) )
				{
					// Turn on auto h total
					msWriteBit ( BK0_57_OSCTRL1, 1, _BIT1 );
printf ( "\r\nTurn on auto H:Noise=%x", msDSP_Std_GetNoiseMag() );
				}
			}

							// 	else
			{
				g_ucCheckSyncCounter = 0;
				g_ucSyncStableCounter = 0;
			}
		}

		else// if( g_ucCheckSyncCounter == 10 )
		{
			g_ucCheckSyncCounter = 0;
			g_ucSyncStableCounter = 0;
		}
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}
#endif
