#include "types.h"
#include "board.h"
#include "global.h"
#include "mcu.h"

#include "menu.h"
#include "ms_reg.h"
#include "power.h"
#include "debug.h"
#include "ms_rwreg.h"
#include "msOSD.h"
#include "misc.h"
#include "nvram.h"
#include "panel.h"
#include "mstar.h"
#include "userPref.h"
#include "keypad.h"
#include "devVD.h"
#include "msVD.h"
#include "debug.h"

#include "maria2_FSC.h"
#include "maria2_ACC.h"
#include "m2_VD_STD.h"
#include "m9_VD_AGC.h"
#include "msVDField.h"

#if(ENABLE_VD_DSP)
	#include "maria2_DSP.h"
#endif

void Init_Device ( void );
void StartConfig ( void );
void SyncModeHandler ( void );
void VD_DSP_Processor ( void );

#if(RM_EEPROM_TYPE==RM_TYPE_PMC010)
	void msSPI_CheckWriteProtect ( void );
#endif



void VersionMsg ( void )
{
	#if SYSTEM_BOOT_UP_QUICKLY_ENABLE
	//dummy
	#else
	putstr ( "Mstar\r\n" );
	putstr ( "\r\n[Date]: " );
	putstr ( __DATE__ );
	putstr ( "\r\n[Time]: " );
	putstr ( __TIME__ );
	putstr ( "\r\nACC version: " );
	putstr ( msVDAcc_GetVersion() );
	// putstr ( "\r\nDSP version: " );
	// putstr ( VD_DSP_GetVersion() );
	putstr ( "\r\nFSC version: " );
	putstr ( msVD_FSC_GetVersion() );
	putstr ( "\r\nAGC version: " );
	putstr ( VD_AGC_GetVersion() );
	printf ( "\r\nMaria Ver: %d ", VD_Type );
	putstr ( "\r\nPanel: " );
	putstr ( PanelName );
	putstr ( "\r\n" );
	#endif
}


/*
void Load4K(void)
{
 BYTE xdata *dest;
 BYTE code *src;

 src = 0xf000; // Code
 dest = 0xf000; // SRam
 do {
 *dest = *src;
 src++;
 dest++;
 } while (dest != 0);
 //P3_4 = 0;
 sfRegs[0x9e]=0x0f;
 sfRegs[0x39]=0x10; //0x30 make address after 0xf000->code memory(address 0x0000)
 //0x10 make address after 0xf000->code memory(address 0xf000)
}
*/

#if( LOAD_4K_TO == 0x0000 ) // SRAM mapping to 0000
	code char dummy[16] _at_ 0x0FF8;
#endif

void Load4K ( void )
{
	BYTE xdata* dest;
	BYTE code* src;

	#if( LOAD_4K_TO == 0x0000 ) // SRAM mapping to 0000
	src = 0x0000; // Code
	dest = 0xf000; // SRam

	do
	{
		*dest = *src;
		src++;
		dest++;
		WDTCON = 1;
	}
	while ( dest != 0 );

	sfRegs[0x9e] = 0x0f;
	sfRegs[0x39] = 0x50; // 0x50 make address after 0xf000->code memory(address 0x0000)

#elif( LOAD_4K_TO == 0xF000 ) // SRAM mapping to F000
	src = 0xf000; // Code
	dest = 0xf000; // SRam

	do
	{
		*dest = *src;
		src++;
		dest++;
		WDTCON = 1;
	}
	while ( dest != 0 );

	sfRegs[0x9e] = 0x0f;
	sfRegs[0x39] = 0x10; // 0x10 make address after 0xf000->code memory(address 0xf000)
	#endif

	if ( VD_Type >= MARIA2_E )
	{
		sfRegs[0x39] |= 0x80; // Enable HW patch
	}
}

void main ( void )
{
	StartConfig();
	Init_MCU();

	#if(RM_EEPROM_TYPE==RM_TYPE_PMC010)
	msSPI_CheckWriteProtect();
	#endif

	Load4K();
	WatchDogClear();

	#if ( ENABLE_VD_DSP )
	VD_DSP_Init();
	WatchDogClear();
	#endif

	VersionMsg();
	WatchDogClear();

	Init_GlobalVariables();
	WatchDogClear();

	ReadSetting();
	// WatchDogClear();

	Set_PowerOnFlag();
	WatchDogClear();

	msInit();
	WatchDogClear();

	#if ENABLE_MCU_USE_INTERNAL_CLOCK
	McuUseInternalClock();
	//WatchDogClear();
	#endif

	vdInitVariable();
	// WatchDogClear();

	Init_Device();
	WatchDogClear();

	WatchDogClear();

	msSetupInputPort();
	WatchDogClear();

	OSDGammaInit();
	WatchDogClear();

	Menu_InitVariable();

	McuWatchDogSetTimer ( WatchDogTime_5S );

	SaveVideoSetting();

	while ( 1 )
	{
		WatchDogClear();

		//msDSP_Std_GetBurstMag();
		
		uartDecodeCommand(); // uart debug command

		if(g_bDebugProgStopFlag)
			continue;

		if ( PowerOnFlag )
		{
			VD_DSP_Processor();

			#if ( ENABLE_SW_FIELD )
			MSVD_FieldProcessor();
			#endif

			msVD_FSC_Detect();

			if ( g_ucmsVDCtl & MSVD_CTL_FLAG_NOISE_HANDLER )
			{
				msVDNoiseHandler();
			}
			
			if ( g_ucmsVDCtl & MSVD_CTL_FLAG_COLOR_BURST_HANDLER )
			{
				msVDColorBurstHandler ( 0 );
			}
			
			if ( ( g_ucmsVDCtl & MSVD_CTL_FLAG_ACC ) )
			{
				msVDAcc_Processor();
			}

			if ( g_ucmsVDCtl2 & MSVD_CTL2_FLAG_AFEC )
			{
				msVDAFECHandler();
			}


			// cs ENABLED
			#if( ENABLE_HSYNC_HANDLER )
			msVDHSyncHandler();
			#endif
		}

		SlowTimeHandler();

		VD_DSP_Processor();
		Menu_OsdHandler();

		// cs ENABLED
		#if( ENABLE_PAL_SWITCH_HANDLER == 1)

		if ( g_ucmsVDCtl2 & MSVD_CTL2_FLAG_PAL_SWITCH )
		{
			msVDPalSwitchHandler();
		}

		#endif

		VD_DSP_Processor();

		#if(ENABLE_MONITOR_VTOTAL == 1)
		msMonitorVTotal ( 0 );
		#endif

		vdMonitorInput();

		vdModeHandler();
		VD_DSP_Processor();
		Power_PowerHandler();

		VD_DSP_Processor();

		#if(ENABLE_CHECK_AUTO_H_TOTAL == 1)
		msCheckBK0_57_Value();
		#endif

		#if ( SYSTEM_BOOT_UP_QUICKLY_ENABLE == 1 )

		if ( g_bOSDLoadFlag == 1 )
		{
			Osd_LoadOsdFont();
			Set_ShowSourceFlag();
			g_bOSDLoadFlag = 0;
		}

		#endif

	}
}

// BYTE getCombStatus(void)
// {
	// BYTE ucBank;
	// BYTE val;
	// ucBank = msReadByte ( BK0_00_REGBK );
	// msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
	// val = msReadByte (BK3_72_COMB_STSC);
	// msWriteByte (BK0_00_REGBK, ucBank );
	// return val;
// }

void VD_DSP_Processor ( void )
{
	BYTE ucBank;

	if ( ! PowerOnFlag )
	{
		return;
	}

	if ( g_ucmsVDCtl2 & MSVD_CTL2_FLAG_AGC_PROCESSOR )
	{
		AGC_Processor();
	}

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
	
	#if( ((DSP_RUN_MODE == DSP_RUN_MODE_POLLING) || (DSP_RUN_MODE == DSP_RUN_MODE_TIMER_AND_POLLING)) )

	if ( g_ucmsVDCtl & MSVD_CTL_FLAG_VSYNC )
	{
		VD_DSP();

		if ( msVDGetVTotal() > 566 ) // 50Hz
		{
			msWriteByteMask ( BK3_40_TIMDETCFGA, 0x03, 0x03 ); // Force 625 lines
		}

		else
		{
			msWriteByteMask ( BK3_40_TIMDETCFGA, 0x02, 0x03 ); // Force 525 lines
		}

	}
	msWriteByte ( BK0_00_REGBK, ucBank );
	#endif

	#ifdef VD_PATCH_005

	if ( g_ucmsVDCtl2 & MSVD_CTL2_FLAG_PATCH5 )
	{
		msVD_Patch_005 ( 0 );
	}

	#endif
}

void Init_Device ( void )
{
	#ifdef USE_LED
	Power_TurnOnGreenLed();
	#endif

	#if PanelLG07_AT
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU ); // Switch to Bank 1 for Turn off VGH and VGL
	msWriteByte ( BK1_4A, 0x00 );
	msWriteByte ( BK1_4B, 0x40 );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER ); // Switch to Bank 0
	#endif
}

void StartConfig ( void )
{
	while ( ( msReadByte ( BK0_00_REGBK ) & 0xC0 ) != 0x80 )
	{
		WatchDogClear();
	}

	msChipVersionRead();

	#if ( SCALER_TYPE != MARIA9 )

	if ( VD_Type >= MARIA2_G )
	{
		msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
		msWriteBit ( BK0_F7_TEST_BUS_SELECT, 1, _BIT6 );
		msWriteByte ( BK0_F8_TEST_MODE, 0x00 );
		msWriteBit ( BK0_F7_TEST_BUS_SELECT, 0, _BIT6 );
	}

	#endif

	msSoftwareReset ( SWR_B | REGR_B, 1 );

	#if(MST_CHIP == MST712CX)
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK0_F7_TEST_BUS_SELECT, 0xC8 );
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_C0_TUNE_FRAME_NO, 0x80 );
	msWriteByte ( BK1_C1_BND_RST, 0x5A );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	#endif

	#if(SCALER_TYPE == MARIA9) 
	// must enable test bus in order to enable GPIO control 
	// after msSoftwareReset
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK0_F7_TEST_BUS_SELECT, 0xC8 );
	msWriteByte ( BK0_F8_TEST_MODE, 0x00 );
	
	#if PWM3D_PWM4D_SETUP_GPIO  
	// enable GPIO on PWM3D/4D pins
	msWriteBit(BK0_87_DEBUG, 0,_BIT1);
	#endif
	
	#endif
}

#if(RM_EEPROM_TYPE==RM_TYPE_PMC010)
void msSPI_CheckWriteProtect ( void )
{
	BYTE ucTmp;

	// Read serial flash status
	MCUXFR_40_SSPI_WD0 = 0x05;
	MCUXFR_48_SSPI_TRIG = 0xF9;
	ucTmp = MCUXFR_49;
	//printf("\r\nFlash status=%x", ucTmp);

	if ( ( ucTmp & _BIT7 ) == 0 || ( ucTmp & _BIT1 ) )
	{
		// Write Enable
		MCUXFR_40_SSPI_WD0 = 0x06;
		MCUXFR_48_SSPI_TRIG = 0xF9;

		// Write protect
		MCUXFR_40_SSPI_WD0 = 0x01;
		MCUXFR_41_SSPI_WD1 = 0x9C;
		MCUXFR_48_SSPI_TRIG = 0xF9;
	}
}
#endif

