//Project File
//=======================================================
#define MST_CHIP MST703
#define RM_EEPROM_TYPE RM_TYPE_PMC010
#define TUNER_TYPE TUNER_NONE
#define PANEL_TYPE PanelHSD050
#define KEY_TYPE Single_ADCKey_3Key
#define KEY_PORT SAR0
#define TV_SYSTEM TV_NTSC
//PanelHSD050
//==========Source DEFINE ====================================
#define TV_ENABLE 0
#define VGA_ENABLE 0
#define YPBPR_ENABLE 0
#define CCIR656_ENABLE 0
#define CCIR656_OUT_ENABLE 0

#define VCOM_DC_Ctrl PWM_TYPE_NONE

//==========DSP DEFINE ==========================================

#define ENABLE_VD_DSP 1
#define ENABLE_SECAM 0
#define CCFL_FUNCTION 1
#define CCFL_BURST_MODE 0
#define LED_BACKLIGHT 1
#define FUN_MGD 0

//==========I/O setting==================================
#define hwBlacklit_Pin
#define hw_SetBlacklit()
#define hw_ClrBlacklit()

#define hwPanelPower_Pin P4
#define hw_SetPanelPower() (P4 |= _BIT0)
#define hw_ClrPanelPower() (P4 &= (~_BIT0))

#define hwTuner_pin P0_0
#define hw_SetTunerOn() hwTuner_pin=0
#define hw_SetTunerOff() hwTuner_pin=1

#define hwI2C_SCL_Pin P0_3
#define hwI2C_SDA_Pin P0_4

#define hwI2C_SCL_Pin_STATUS (hwI2C_SCL_Pin)
#define hwI2C_SDA_Pin_STATUS (hwI2C_SDA_Pin)

#define hw_SetGreenLed()

#define hw_ClrGreenLed()

//===========================Panel R/L U/D Setting================================
// GPIO enable Output enable Output value Input value
//PWM1D BK7_09[2]=1 BK7_19[2]=0 BK7_11[2] BK7_21[2]
#define hw_SetPanelInvert() \
	msWriteByte(BK0_00_REGBK, REG_BANK7_CHIPTOP);\
	msWriteBit(BK7_09_CHIPTOP, 1, _BIT2);\
	msWriteBit(BK7_19_CHIPTOP, 0, _BIT2);\
	msWriteBit(BK7_11_CHIPTOP, 0, _BIT2);\
	msWriteByte(BK0_00_REGBK, REG_BANK_SCALER);

#define hw_ClrPanelInvert() \
	msWriteByte(BK0_00_REGBK, REG_BANK7_CHIPTOP);\
	msWriteBit(BK7_09_CHIPTOP, 1, _BIT2);\
	msWriteBit(BK7_19_CHIPTOP, 0, _BIT2);\
	msWriteBit(BK7_11_CHIPTOP, 1, _BIT2);\
	msWriteByte(BK0_00_REGBK, REG_BANK_SCALER);


#define hw_SetPanel_UD() {\
		msWriteByte(BK0_00_REGBK, REG_BANK7_CHIPTOP);\
		msWriteBit(BK7_08_CHIPTOP, 1, _BIT5);\
		msWriteBit(BK7_18_CHIPTOP, 0, _BIT5);\
		msWriteBit(BK7_10_CHIPTOP, 1, _BIT5);\
		msWriteByte(BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU);\
	}
#define hw_ClrPanel_UD() {\
		msWriteByte(BK0_00_REGBK, REG_BANK7_CHIPTOP);\
		msWriteBit(BK7_08_CHIPTOP, 1, _BIT5);\
		msWriteBit(BK7_18_CHIPTOP, 0, _BIT5);\
		msWriteBit(BK7_10_CHIPTOP, 0, _BIT5);\
		msWriteByte(BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU);\
	}

//=================================================================

#if(KEY_TYPE == Single_ADCKey)
	#define KEY_AD_L0 0x00
	#define KEY_AD_L1 0x09
	#define KEY_AD_L2 0x14
	#define KEY_AD_L3 0x1F
	#define KEY_AD_L4 0x26
	#define KEY_AD_L5 0x30
	#define KEY_AD_L6 0x3A
	#define KEY_AD_DELTA 0x03 // tolerance

	#elif(KEY_TYPE == Single_ADCKey_3Key)
	#define KEY_AD_L0 0x0A // DOWN
	#define KEY_AD_L1 0x1F // MIDDLE/SELECT
	#define KEY_AD_L2 0x2A // UP
	#define KEY_AD_DELTA 0x03// tolerance

	#elif(KEY_TYPE == Dual_ADCKey)
	#define KEY_AD_L0 0x00
	#define KEY_AD_L1 0x0B
	#define KEY_AD_L2 0x1B
	#define KEY_AD_L3 0x29
	#define KEY_AD_DELTA 0x03 // tolerance
#endif
//=================================================================

typedef enum
{
	Input_CVBS1,
	Input_CVBS2,
	Input_Nums,
	Input_Nothing,
	Input_AllPort = 0xFF
} InputPortType;

// #define CVBS1_RealPortSet PORT_CVBS_SV1C
// #define CVBS2_RealPortSet PORT_CVBS_SV0C
#define CVBS1_RealPortSet PORT_CVBS_SV1Y
#define CVBS2_RealPortSet PORT_CVBS_SV1C

#define TV_RealPortSet PORT_CVBS_SV1Y
#define CVBS3_RealPortSet PORT_CVBS_SV1Y
#define CVBS4_RealPortSet PORT_CVBS_SV1C
#define CVBS5_RealPortSet PORT_CVBS_SV1C
#define CVBS6_RealPortSet PORT_CVBS_SV1C
#define SVIDEO1_RealPortSet PORT_SV0
#define SVIDEO2_RealPortSet PORT_SV1
#define VGA_RealPortSet PORT_VGA
#define YPbPr_RealPortSet PORT_YPbPr

