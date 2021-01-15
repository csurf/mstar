#define _POWER_C_

#include "types.h"
#include "board.h"
#include "global.h"
#include "ms_reg.h"
#include "panel.h"
#include "misc.h"
#include "ms_rwreg.h"
#include "mstar.h"
#include "debug.h"
#include "msOSD.h"

#include "devVD.h"
#include "menuDef.h"
#include "menuFunc.h"

#define TurnOffOSD 1

void Power_TurnOffPanel ( void );
void Power_PowerOffSystem ( void );

//=============================================
#if Panel_SPI
extern void spi_WriteReg ( BYTE reg, BYTE val );

void PanelSPIInit ( void )
{
	printMsg ( "---PanelSPIInit---" );
	spi_WriteReg ( 0x05, 0x04 );
	spi_WriteReg ( 0x00, 0x0C );
	spi_WriteReg ( 0x01, 0xB0 );
	spi_WriteReg ( 0x0b, 0x80 );
	spi_WriteReg ( 0x2f, 0x7D );
	spi_WriteReg ( 0x16, 0x00 );
	spi_WriteReg ( 0x17, 0x65 );
	spi_WriteReg ( 0x18, 0x65 );
	spi_WriteReg ( 0x19, 0x67 );
	spi_WriteReg ( 0x1A, 0x76 );

	spi_WriteReg ( 0x3C, 0x80 );
	spi_WriteReg ( 0x3D, 0x7D );
	spi_WriteReg ( 0x3E, 0x00 );
	spi_WriteReg ( 0x3F, 0x65 );
	spi_WriteReg ( 0xA0, 0x65 );
	spi_WriteReg ( 0xA1, 0x67 );
	spi_WriteReg ( 0xA4, 0x76 );
	spi_WriteReg ( 0x2F, 0x79 );
	spi_WriteReg ( 0x2B, 0x01 );

	spi_WriteReg ( 0x04, 0x48 ); //LRUD
	spi_WriteReg ( 0x06, 0x8F );
	spi_WriteReg ( 0x07, 0x3F );
	spi_WriteReg ( 0x08, 0x04 );
}
#endif

// Control system power status
// caller : main()

void Power_PowerHandler ( void )
{
	if ( ForcePowerSavingFlag )
	{
		Clr_ForcePowerSavingFlag(); // clear force power saving flag

		if ( !PowerSavingFlag )
		{
			printMsg ( "enter power saving" );
			Power_PowerOffSystem();
		}
	}
}

void Power_PowerOnSystem ( void )
{
	Power_TurnOffPanel();
	msPowerUp();
	Clr_PowerSavingFlag();

	Set_InputTimingChangedFlag();
	SrcFlags |= SyncLoss;

	Clr_ForcePowerONFlag();
	Clr_EnableONTimeFlag();

	Set_ShowSourceFlag();
}

void Power_PowerOffSystem ( void )
{
	Power_TurnOffPanel();
	msPowerDown();
	Set_PowerSavingFlag();
	Clr_InputTimingChangeFlag();
	g_ucOsdCounter = 0;
	g_ucPowerDownCounter = 0;
	Clr_OsdTimeoutFlag();
	hw_SetTunerOff();
}

void Power_TurnOnPanel ( void )
{
	if ( b_TurnOnPanelFlagbit )
	{
		return;
	}

	printMsg ( "Power_TurnOnPanel" );
	//msSetBlueScreen( _ENABLE, FR_BLUE);

	#if ( PANEL_DIGITAL_TCON || PANEL_ANALOG_TCON ) //LSP2006-5-9
	
	#if ( SCALER_TYPE == MARIA9 ) //Linix 20100929
	msWriteByte ( BK0_00_REGBK, REG_BANK7_CHIPTOP );
	msWriteByteMask ( BK7_09_CHIPTOP, 0x00, 0x30 ); //Turn STVR/STHL
	msWriteByteMask ( BK7_0E_CHIPTOP, 0x00, 0x01 ); //Turn STVR/STHL
	msWriteByte ( BK0_00_REGBK, REG_BANK4_LVDS_CCFL );
	msWriteByte ( BK4_27, 0x00 ); //Turn on VCOMOUT
	
	#endif //End Linix 20100929
	
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // Switch to Bank 1 for TCON control
	msWriteByte ( BK1_D0_PTC_MODE1, SET_PTC_MODE1 ); // Enable TCON
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER ); // Switch to Bank 0

	#if PANEL_ANALOG_TCON
	
	#if ( SCALER_TYPE == MARIA9 ) //Linix 20100929
	msWriteByte ( BK0_00_REGBK, REG_BANK7_CHIPTOP );
	msWriteByteMask ( BK7_06_CHIPTOP, 0x0F, 0x0F ); //Increase VGH/VGL driving
	msWriteByteMask ( BK7_0B_CHIPTOP, 0x00, 0x06 ); //Turn VGH/VGL
	Delay1ms_AGC_Processor ( 500 ); //must delay after turn on VGH/VGL
	
	#else //End Linix 20100929
	
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // Switch to Bank 1 for TCON control
	msWriteByte ( BK1_4A, 0x00 ); // Turn on VGL and VGH
	msWriteByte ( BK1_4B, 0x40 );
	msWriteByte ( BK1_45, 0x00 );
	#endif
	
	#endif
	
	#endif

	#if ( PANEL_LVDS )
	msWriteByte ( BK0_00_REGBK, REG_BANK4_LVDS_CCFL ); // switch to Bank 4
	#if ( SCALER_TYPE == MARIA9 )
	msWriteByte ( BK4_1E, 0x04 );
	#else
	msWriteByte ( BK4_1E, 0x02 );
	#endif
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // switch to Bank 1
	msWriteByte ( BK1_AC_EN_CDAC, 0x01 );
	#endif
	
	//Delay1ms(PanelOnTiming1);
	Delay1ms_AGC_Processor ( PanelOnTiming1 );

	hw_SetPanelPower();

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER ); // Switch to Bank 0 for data output control
	msWriteByte ( BK0_F4_TRISTATE, 0x00 ); // Enable data output

	//Delay1ms(PanelOnTiming2);
	Delay1ms_AGC_Processor ( PanelOnTiming2 );

	#if Panel_SPI
	PanelSPIInit();
	#endif

	if ( g_bInputTimingChangeFlag )
	{
		Power_TurnOffPanel();
	}

	else
	{
		#if (CCFL_FUNCTION)
		msWriteByte ( BK0_00_REGBK, REG_BANK4_LVDS_CCFL );
		msWriteByte ( BK4_6B, 0xFF );
		msWriteByte ( BK4_9A, 0xCF );

		#if CCFL_BURST_MODE
		msWriteByte ( BK4_6E, 0x0D );
		#else
		msWriteByte ( BK4_6E, 0x0C );
		#endif

		if ( ! ( g_VdInfo.wVideoStatus & VD_VSYNC_50HZ ) )
		{
			msWriteByte ( BK4_AC, 0x61 );
		}

		else
		{
			msWriteByte ( BK4_AC, 0x81 );
		}

		#if (SCALER_TYPE == MARIA9)
		
		//W0481 33
		msWriteByte ( BK4_81, 0x22 );
		//W0482 33
		msWriteByte ( BK4_82, 0x22 );
		//W046D 03
		msWriteByte ( BK4_6D, 0x03 );

		Delay1ms_AGC_Processor ( 500 );

		//W0481 35
		//msWriteByte(BK4_81, 0x35);
		//W0482 35
		//msWriteByte(BK4_82, 0x35);
		//W0481 40
		//msWriteByte(BK4_81, 0x40);
		//W0482 40
		//msWriteByte(BK4_82, 0x40);
		//W0481 90
		msWriteByte ( BK4_81, 0x90 );
		//W0482 90
		msWriteByte ( BK4_82, 0x90 );

		#else
		
		msWriteByte ( BK4_6D, 0x03 );
		
		#endif
		
		msWriteByte ( BK4_6B, 0x00 );

		//msSetCCFLBrightness(); //csrf

		msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

		#else
		hw_SetBlacklit(); // Turn on backlight
		#endif
	}
	
	b_TurnOnPanelFlagbit = 1;
}

void Power_TurnOffPanel ( void )
{
	printMsg ( "Power_TurnOffPanel" );

	#if TurnOffOSD
	msWriteOSDByte ( OSD_01_OSDDBC, 0x00 ); // disable osd double buffer
	msWriteOSDByte ( OSD_0C_IOSDC1, 0 );
	//msWriteOSDByte(BK0_01_DBFC, 0x0); // disable double buffer
	//msWriteByte(OCTRL2, msReadByte(OCTRL2)|BLKS_B);
	Delay4us();
	#endif

	#if (CCFL_FUNCTION)
	msWriteByte ( BK0_00_REGBK, REG_BANK4_LVDS_CCFL );
	msWriteByte ( BK4_6B, 0xFF );
	msWriteByte ( BK4_6D, 0x00 );
	msWriteByte ( BK4_6E, 0x05 );
	msWriteByte ( BK4_6B, 0x00 );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	#else
	hw_ClrBlacklit(); // Turn off panel VDD
	#endif

	//hw_ClrBlacklit();
	Delay1ms ( PanelOffTiming1 );

	#if (PANEL_DIGITAL_TCON || PANEL_ANALOG_TCON)
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // Switch to Bank 1 for TCON control
	msWriteByte ( BK1_D0_PTC_MODE1, ( SET_PTC_MODE1 & 0x7F ) ); // Disable TCON
	#endif

	#if (PANEL_LVDS)
	msWriteByte ( BK0_00_REGBK, REG_BANK4_LVDS_CCFL ); // switch to Bank 4
	#if (SCALER_TYPE == MARIA9)
	msWriteByte ( BK4_1E, 0x02 );
	#else
	msWriteByte ( BK4_1E, 0x04 );
	#endif
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // switch to Bank 1
	msWriteByte ( BK1_AC_EN_CDAC, 0x00 );
	#endif

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER ); // Switch to Bank 0 for data output control
	msWriteByte ( BK0_F4_TRISTATE, 0x1F ); // Disable data output

	Delay1ms ( PanelOffTiming2 );
	// hw_ClrPanelPower();

	#if PANEL_ANALOG_TCON
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // Switch to Bank 1 for TCON control
	msWriteByte ( BK1_4A, 0x0F ); // Turn off VGL and VGH
	msWriteByte ( BK1_4B, 0x4C );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER ); // Switch to Bank 0
	#endif

	#if TurnOffOSD
	msWriteOSDByte ( OSD_01_OSDDBC, 0x5 ); // enable double
	#endif

	g_ucSyncMaxStableCounter = 150;
	b_TurnOnPanelFlagbit = 0;
}

