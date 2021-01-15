/******************************************************************************
 Copyright (c) 2003 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: Debug.c
 [Date]:
 [Comment]:
 Uart subroutines.
 [Reversion History]:
*******************************************************************************/

#define _DEBUG_C_

// Common
#include <MATH.H>
#include "types.h"
#include "board.h"
#include "global.h"

#include "panel.h"
#include "misc.h"
#include "ms_rwreg.h"
#include "reg52.h"
#include "ms_reg.h"
#include "power.h"
#include "msOSD.h"
#include "nvram.h"

#include "keypadDef.h"

#include "msACE.h"
#include "menu.h"
#include "menuFunc.h"
#include "userPref.h"
#include "devVD.h"
#include "msVD.h"

#include "m2_VD_STD.h"
#include "maria2_FSC.h"
#include "maria2_ACC.h"

#if ( ENABLE_VD_DSP )

#include "maria2_DSP.h"
extern BYTE idata g_ucDSP_Ctl;
//#define DSP_MARIA_DEBUG

#ifdef DSP_MARIA_DEBUG
extern XDATA BYTE g_dspDebugFlag;
extern XDATA BYTE g_dspDebugInfoIdx;
extern XDATA BYTE g_dspDebugInfo[64];
#endif

#endif

// Debug FSC lib
extern XDATA WORD g_wFSCBurstMag;
extern BYTE s_ucFSCBurstOn;
extern BYTE s_ucFSCBurstOff;
extern XDATA BYTE g_ucFSCNoiseMag;
extern XDATA BYTE s_ucFSCNoiseOn;
extern XDATA BYTE s_ucFSCNoiseOff;
extern XDATA BYTE g_ucFSCPhaseErrorAvg;
extern XDATA BYTE s_ucFSCPhaseErrorLevelOn;
extern XDATA BYTE s_ucFSCPhaseErrorLevelOff;
extern BYTE OsdFontColor;

extern BYTE xdata g_ucAgcState;
extern HLdata xdata g_unSyncMagnitude; // average 64 lines Sync magnitude

// Internal
#include "debug.h"
// Test command
#if 0
void Test_CalClock ( BOOL bInterlaceMode )
{
	XDATA WORD wInputHPeriod; // horizontal period
	XDATA WORD wHFreq;
	XDATA WORD wInputVTotal;
	XDATA WORD wVFreq;
	XDATA WORD wOutputHTotal;
	XDATA WORD wOutputVTotal;
	XDATA DWORD dwClockFactor; // clock factor

	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	wInputHPeriod = msGetHorizontalPeriod();
	wHFreq = msCalculateHFreqX10 ( wInputHPeriod ); // Cal H freq
	wInputVTotal = msGetVerticalTotal();
	wVFreq = msCalculateVFreqX10 ( wHFreq, wInputVTotal ) * 2; // Cal V freq

	printf ( "\r\nInputHPeriod=%d", wInputHPeriod );
	printf ( "\r\nInputVTotal=%d", wInputVTotal );
	printf ( "\r\nInputHFreq=%d*10KHz", wHFreq );
	printf ( "\r\nInputVFreq=%d*10Hz", wVFreq );

	wOutputHTotal = PANEL_HTOTAL;
	wOutputVTotal = PANEL_VTOTAL;
	printf ( "\r\nClock:OutputHTotal=%d", wOutputHTotal );
	printf ( "\r\nClock:OutputVTotal=%d", wOutputVTotal );

	dwClockFactor = ( ( float ) wInputHPeriod * wInputVTotal * 524288ul * PANEL_MASTER_PLL_DIVIDER ) /
		( ( float ) wOutputHTotal * wOutputVTotal );

	if ( IsSrcUseDigitalPort() || bInterlaceMode )
	{
		dwClockFactor /= 2;
	}

	printf ( "\r\nSET=%x,", ( dwClockFactor >> 16 ) );
	printf ( "%x", ( WORD ) dwClockFactor );

	dwClockFactor = ( ( ( DWORD ) wInputVTotal - 1 ) * 1048576ul / ( wOutputVTotal - 1 ) + 1 );

	if ( IsSrcUseDigitalPort() || bInterlaceMode )
	{
		dwClockFactor /= 2;
	}

	printf ( "\r\nV ScalingRatio=%x,", ( dwClockFactor >> 16 ) );
	printf ( "%x", ( WORD ) dwClockFactor );

	// putstr("\r\n------------------------------------");
	// {
	// XDATA WORD wImgHeight;
	// wImgHeight = g_WindowInfo.V_CapSize;
	// printf("\r\nImgHigh=%d", wImgHeight);
	//
	// dwClockFactor = ((float)wInputHPeriod*(wImgHeight - 1)*524288ul*PANEL_MASTER_PLL_DIVIDER) /
	// ((float)wOutputHTotal * (540 - 1));
	// if( IsSrcUseDigitalPort() || bInterlaceMode )
	// dwClockFactor /= 2;
	// printf("\r\nSET2=%x,", (dwClockFactor>>16) );
	// printf("%x", (WORD)dwClockFactor );
	//
	// dwClockFactor = ( ((DWORD)wImgHeight-1) * 1048576ul / (540-1) + 1 );
	// if( IsSrcUseDigitalPort() || bInterlaceMode )
	// dwClockFactor /= 2;
	// printf("\r\nV ScalingRatio2=%x,", (dwClockFactor>>16) );
	// printf("%x", (WORD)dwClockFactor );
	// }

	msWriteByte ( BK0_00_REGBK, ucBank );
}
#endif

/*
void PrintModeSetting(void)
{

 printf( "\r\nModeIndex=%d", g_ModeSetting.ModeIndex );
 printf( "\r\nHorizontalStart=%d", g_ModeSetting.HorizontalStart );
 printf( "\r\nVerticalStart=%d", g_ModeSetting.VerticalStart );
 printf( "\r\nHorizontalTotal=%d", g_ModeSetting.HorizontalTotal );
 printf( "\r\nPhase=%d", g_ModeSetting.Phase );
 printf( "\r\nDefaultHStart=%d", g_ModeSetting.DefaultHStart );
 printf( "\r\nAutoSign=%d", g_ModeSetting.AutoSign );
 printf( "\r\nModeSettingCS=%d", g_ModeSetting.ModeSettingCS );
}
*/

void dumpVideoSettings(void)
{
	printf("\r\nBrightness: %d", g_VideoSetting.VideoBrightness);
	printf("\r\nContrast: %d", g_VideoSetting.VideoContrast );
	printf("\r\nColor: %d", g_VideoSetting.VideoSaturation );
	printf("\r\nBacklight: %d\r\n", g_VideoSetting.Backlight );

	// g_VideoSetting.VideoHue );
	// g_VideoSetting.VideoSharpness );
}

void ExecTestCommand ( void )
{
	BYTE ucBank = msReadByte ( 0 );

	putchar ( 0xC6 );
	switch ( g_UartCommand.Buffer[_UART_CMD_INDEX1_] )
	{
		case 0x50:
			// if enable g_bDebugProgStopFlag, the program will halt, and only Uart function will be run
			g_bDebugProgStopFlag = !g_bDebugProgStopFlag;

			if ( g_bDebugProgStopFlag )
			{
				putstr ( "\r\n<Debug>" );
				EX0 = 0;
				EX1 = 0;
			}

			else
			{
				putstr ( "\r\n<Free>" );
				EX0 = 1;
				EX1 = 1;
			}
			break;

		case 0x91:
			dumpVideoSettings();
			break;

		// Keypad Emulator ////////////////////
		case 0x63: // Keypad_UP
			EventProcess ( KEY_UP );
			break;

		case 0x73: // Keypad_MENU
			EventProcess ( KEY_MENU );
			break;
			
		case 0x83: // Keypad_DOWN
			EventProcess ( KEY_DOWN );
			break;

		case 0x98:
			printf ( "\r\ng_ucMenuPageIndex == %x", g_ucMenuPageIndex );
			printf ( "\r\ng_ucMenuItemIndex == %x", g_ucMenuItemIndex );
			break;

		// case 0xD1:
			// {
				// WORD wStatus = msVDGetSyncStatus();
				// PrintVDStatus ( wStatus );
				// Test_CalClock(1);
			// }
			// break;

		case 0xD2:
			msVDReset();
			break;

		case 0xD3:
			printf ( "\r\n VdStatus=%x", msVDGetSyncStatus() );
			printf ( "\r\n g_VdInfo.wVideoStatus=%x", g_VdInfo.wVideoStatus );
			break;
		
		case 0xD4: 
			msVD_FSM_Reset();
			break;
		
		case 0xD8:
			//msAutoGeometry(AUTO_TUNE_YUV_COLOR);
			//usrSaveAdcSetting(ADC_SET_YPBPR); // save YPbPr setting(manufactory)
			break;

		case 0xD9:
			msVD_FSC_Detect();
			break;

		// if enable g_bDebugASCIICommandFlag,
		// it means the program is received command that user use ASCII command type in debug tool software.
		// and the program should respond the register value by message type (printf)
		// test command + 0xF0 -> disable
		// test command + 0xF1 -> enable
		case 0xF0:
			g_bDebugASCIICommandFlag = _DISABLE;
			break;

		case 0xF1:
			g_bDebugASCIICommandFlag = _ENABLE;
			break;

		case 0xF2:
			P4SEL = g_UartCommand.Buffer[_UART_CMD_INDEX2_];
			P4IO = g_UartCommand.Buffer[_UART_CMD_INDEX2_];
			printf ( "\r\n P4 CONTROL=%x", g_UartCommand.Buffer[_UART_CMD_INDEX2_] );
			break;

		case 0xF3:
			P4 = g_UartCommand.Buffer[_UART_CMD_INDEX2_];
			printf ( "\r\n P4 =%x", g_UartCommand.Buffer[_UART_CMD_INDEX2_] );
			break;

		case 0xF4:
			printf ( "\r\n P4 Read Data=%x", P4 );
			break;

	//	case 0xFD:
	//		PrintModeSetting();
	//		break;

		// case 0xfe: // Display system flag
			// putstr("\r\nSystemInfo:");
			// printf("\r\n_ucSysStatus=%x", g_SystemInfo._ucSysStatus);
			// printf("\r\n_ucInputSrcType=%x", g_SystemInfo._ucInputSrcType);
			// printf("\r\n_inputPortType=%x", g_SystemInfo._inputPortType);
			// printf("\r\n_ucSignalColorType=%x", g_SystemInfo._ucSignalColorType);
			// break;

		case 0xff55: // Here will never called! For disable some uncall warning
			break;
	}
	putchar(0xC7);
	msWriteByte ( BK0_00_REGBK, ucBank );
}

void uartDecodeCommand ( void )
{
	if ( _testbit_ ( g_bUartDetected ) ) // check command flag
	{
		//putstr("\r\nDecode UartCmd");
		uartDecodeNormalCommand();
	}
}

// Decode Uart command
//0 SCALER
//1 ADC
//2 VD
//3 COMB
//4 ??
//5 DSP
// OSD
//===== RESTORE =====
//6 MCU
//A DEBUG1
//B Debug2
//C debug3

void uartDecodeNormalCommand ( void )
{
	BYTE ucBank;
	
	putchar ( 0xC6 );
	{
		ucBank = msReadByte ( BK0_00_REGBK );

		switch ( UART_CMD )
		{
		/*
		case kEnter_ISP:
		{
		// new check ISP command
		if (g_UartCommand.Buffer[_UART_CMD_INDEX1_] != 0x55 ||
		g_UartCommand.Buffer[_UART_CMD_INDEX2_] != 0xaa)
		break;

		putstr("\r\n- Isp -");
		#if(PANEL_TYPE_SEL!=PNL_DAC_CRT)
		pwPanelOffSequence();
		#endif

		#if( MCU_SEL==MCU_W78E65 )
		CHPENR = 0x87; // CHPENR = 0x59, enable CHPCON register write attribute
		CHPENR = 0x59; // CHPENR = 0x59, enable CHPCON register write attribute
		CHPCON = 0x03; // CHPCON = 0x03, enter in-system programming mode
		CHPENR = 0x00; // CHPENR = 0x00, disable CHPCON write attribute

		TR0 = 0; // Timer0 stop
		IP = 0x00; // Set interrupt priority

		EA = 1; // Set single interrupt
		ET0 = 1; // Enable TIMER0 iterrrupt
		// Timer0 interrupt enable for wake-up from INDLE mode

		// Set time for enter ISP mode about 1.676 us
		TL0 = 0xf0; // TL0 = 0xf0
		TH0 = 0xff; // TH0 = 0xff
		TMOD |= 0x01; // Set Timer0 mode 1 (16-bit timer)
		TR0 = 1; // Start Timer0
		PCON = 0x01; // Enter IDLE mode for launching the in-system programmability
		#endif
		#if(MCU_SEL==MCU_W77E532)
		//P4 = 0x00;

		IE = 0;
		TCON = 0;

		TA = 0xAA;
		TA = 0x55;
		TURBO_CHPCON = 0x03; // CHPCON = 0x03, enter in-system programming mode
		TA = 0x00;

		TR0 = 0; // Timer0 stop
		IP = 0x00; // Set interrupt priority

		EA = 1; // Set single interrupt
		ET0 = 1; // Enable TIMER0 iterrrupt
		// Timer0 interrupt enable for wake-up from INDLE mode

		// Set time for enter ISP mode about 1.676 us
		TL0 = 0xf0; // TL0 = 0xf0
		TH0 = 0xff; // TH0 = 0xff
		TMOD |= 0x01; // Set Timer0 mode 1 (16-bit timer)
		TR0 = 1; // Start Timer0
		PCON = 0x01; // Enter IDLE mode for launching the in-system programmability
		#endif
		break;
		}
		*/
		
		/*
		case kWrite_MST_Bank0:
		{
		msWriteByte(BK0_00_REGBK, REG_BANK_SCALER);
		msWriteByte(UART_CMD_MS_REG, UART_CMD_MS_DAT);
		if (!g_bDebugASCIICommandFlag) putchar(0xF1);
		break;
		}
		case kRead_MST_Bank0:
		{
		msWriteByte(BK0_00_REGBK, REG_BANK_SCALER);
		UART_CMD_MS_DAT = msReadByte(UART_CMD_MS_REG);
		putchar(0xF2);
		putchar(UART_CMD_MS_DAT);
		if (g_bDebugASCIICommandFlag)
		{
		printf("BK0[0x%x]=", UART_CMD_MS_REG);
		printf("0x%x \r\n", UART_CMD_MS_DAT);
		}
		break;
		}
		case kWrite_MST_Bank1:
		{
		msWriteByte(BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU);
		msWriteByte(UART_CMD_MS_REG, UART_CMD_MS_DAT);
		if (!g_bDebugASCIICommandFlag) putchar(0xF1);
		break;
		}
		case kRead_MST_Bank1:
		{
		msWriteByte(BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU);
		UART_CMD_MS_DAT = msReadByte(UART_CMD_MS_REG);
		putchar(0xF2);
		putchar(UART_CMD_MS_DAT);
		if (g_bDebugASCIICommandFlag)
		{
		printf("BK1[0x%x]=", UART_CMD_MS_REG);
		printf("0x%x \r\n", UART_CMD_MS_DAT);
		}
		break;
		}
		case kWrite_MST_Bank2:
		{
		msWriteByte(BK0_00_REGBK, 2);
		msWriteByte(UART_CMD_MS_REG, UART_CMD_MS_DAT);
		if (!g_bDebugASCIICommandFlag) putchar(0xF1);
		break;
		}
		case kRead_MST_Bank2:
		{
		msWriteByte(BK0_00_REGBK, 2);
		UART_CMD_MS_DAT = msReadByte(UART_CMD_MS_REG);
		putchar(0xF2);
		putchar(UART_CMD_MS_DAT);
		if (g_bDebugASCIICommandFlag)
		{
		printf("BK2[0x%x]=", UART_CMD_MS_REG);
		printf("0x%x \r\n", UART_CMD_MS_DAT);
		}
		break;
		}
		case kWrite_MST_Bank3:
		{
		msWriteByte(BK0_00_REGBK, 3);
		msWriteByte(UART_CMD_MS_REG, UART_CMD_MS_DAT);
		if (!g_bDebugASCIICommandFlag) putchar(0xF1);
		break;
		}
		case kRead_MST_Bank3:
		{
		msWriteByte(BK0_00_REGBK, 3);
		UART_CMD_MS_DAT = msReadByte(UART_CMD_MS_REG);
		putchar(0xF2);
		putchar(UART_CMD_MS_DAT);
		if (g_bDebugASCIICommandFlag)
		{
		printf("BK3[0x%x]=", UART_CMD_MS_REG);
		printf("0x%x \r\n", UART_CMD_MS_DAT);
		}
		break;
		}
		case kWrite_MST_Bank4:
		{
		msWriteByte(BK0_00_REGBK, 0x04);
		msWriteByte(UART_CMD_MS_REG, UART_CMD_MS_DAT);
		if (!g_bDebugASCIICommandFlag) putchar(0xF1);
		break;
		}
		case kRead_MST_Bank4:
		{
		msWriteByte(BK0_00_REGBK, 0x04);
		UART_CMD_MS_DAT = msReadByte(UART_CMD_MS_REG);
		putchar(0xF2);
		putchar(UART_CMD_MS_DAT);
		//putchar(0);
		if (g_bDebugASCIICommandFlag)
		{
		printf("BK4[0x%x]=", UART_CMD_MS_REG);
		printf("0x%x \r\n", UART_CMD_MS_DAT);
		}
		break;
		}
		case kWrite_MST_Bank5:
		{
		msWriteByte(BK0_00_REGBK, 2);
		if ((UART_CMD_MS_REG&0x01) == 1)
		msVDDSPWriteByte(UART_CMD_MS_REG-1, msVDDSPReadByte(UART_CMD_MS_REG-1));

		msVDDSPWriteByte(UART_CMD_MS_REG, UART_CMD_MS_DAT);

		if ((UART_CMD_MS_REG&0x01) == 0)
		msVDDSPWriteByte(UART_CMD_MS_REG+1, msVDDSPReadByte(UART_CMD_MS_REG+1));

		if (!g_bDebugASCIICommandFlag) putchar(0xF1);
		}
		break;
		case kRead_MST_Bank5:
		{
		msWriteByte(BK0_00_REGBK, 2);
		UART_CMD_MS_DAT = msVDDSPReadByte(UART_CMD_MS_REG);
		putchar(0xF2);
		putchar(UART_CMD_MS_DAT);
		if (g_bDebugASCIICommandFlag)
		{
		printf("SFR[0x%x]=", UART_CMD_MS_REG);
		printf("0x%x \r\n", UART_CMD_MS_DAT);
		}
		}
		break;
		*/
		
		case kWrite_MST_Bank_n:
			{
				switch ( UART_CMD_MS_BANK )
				{
				case UART_OSD_BANK:
					msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
					msWriteOSDByte ( UART_CMD_MS_REGINDEX, UART_CMD_MS_REGDATA );
					break;

				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					msWriteByte ( BK0_00_REGBK, UART_CMD_MS_BANK );
					msWriteByte ( UART_CMD_MS_REGINDEX, UART_CMD_MS_REGDATA );
					break;

				case 8: // MCU SFR
					sfRegs[UART_CMD_MS_REGINDEX] = UART_CMD_MS_REGDATA;
					break;

				case 9: // DSP
					msWriteByte ( BK0_00_REGBK, 2 );

					if ( ( UART_CMD_MS_REGINDEX & 0x01 ) == 1 )
					{
						msVDDSPWriteByte ( UART_CMD_MS_REGINDEX - 1, msVDDSPReadByte ( UART_CMD_MS_REGINDEX - 1 ) );
					}

					msVDDSPWriteByte ( UART_CMD_MS_REGINDEX, UART_CMD_MS_REGDATA );

					if ( ( UART_CMD_MS_REGINDEX & 0x01 ) == 0 )
					{
						msVDDSPWriteByte ( UART_CMD_MS_REGINDEX + 1, msVDDSPReadByte ( UART_CMD_MS_REGINDEX + 1 ) );
					}

					break;

				case 0xA: // Debug1
					{
						switch ( UART_CMD_MS_REGINDEX )
						{
						case 0:
							g_ucmsVDCtl = UART_CMD_MS_REGDATA;
							break;

						case 1:
							g_ucmsVDCtl2 = UART_CMD_MS_REGDATA;
							break;

						case 2:
							g_ucMSVDDebug = UART_CMD_MS_REGDATA;
							break;

						case 3:
							g_ucMSVDDebug2 = UART_CMD_MS_REGDATA;
							break;

						case 4:
							g_ucDebugFlag = UART_CMD_MS_REGDATA;
							break;
						}

						break;
					} // End of case 0xA

				case 0x0B: // Debug2
					{
						switch ( UART_CMD_MS_REGINDEX )
						{
							#if(ENABLE_VD_DSP)

						case 0:
							g_ucDSP_Ctl = UART_CMD_MS_REGDATA;
							break;
							#ifdef DSP_MARIA_DEBUG

						case 1:
							g_dspDebugInfoIdx = UART_CMD_MS_REGDATA;
							break;

						case 2:
							g_dspDebugFlag = UART_CMD_MS_REGDATA;
							break;
							#endif
							#endif

						case 3:
							//g_wFSCBurstMag = UART_CMD_MS_REGDATA;
							break;

						case 4:
							s_ucFSCBurstOn = UART_CMD_MS_REGDATA;
							break;

						case 5:
							s_ucFSCBurstOff = UART_CMD_MS_REGDATA;
							break;

						case 6:
							//g_ucFSCNoiseMag = UART_CMD_MS_REGDATA;
							break;

						case 7:
							s_ucFSCNoiseOn = UART_CMD_MS_REGDATA;
							break;

						case 8:
							s_ucFSCNoiseOff = UART_CMD_MS_REGDATA;
							break;

						case 9:
							//g_ucFSCPhaseErrorAvg = UART_CMD_MS_REGDATA;
							break;

						case 0xA:
							s_ucFSCPhaseErrorLevelOn = UART_CMD_MS_REGDATA;
							break;

						case 0xB:
							s_ucFSCPhaseErrorLevelOff = UART_CMD_MS_REGDATA;
							break;

						}

						break;
					}
				}

				if ( !g_bDebugASCIICommandFlag )
				{
					putchar ( 0xF1 );
				}

				break;
			}

		case kRead_MST_Bank_n:
			{
				UART_CMD_MS_REGDATA = 0;

				switch ( UART_CMD_MS_BANK )
				{
				case UART_OSD_BANK:
					msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
					UART_CMD_MS_REGDATA = msReadOSDByte ( UART_CMD_MS_REGINDEX );
					break;

				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
					msWriteByte ( BK0_00_REGBK, UART_CMD_MS_BANK );
					UART_CMD_MS_REGDATA = msReadByte ( UART_CMD_MS_REGINDEX );
					break;

				case 8: // MCU SFR
					UART_CMD_MS_REGDATA = sfRegs[UART_CMD_MS_REGINDEX];
					break;

				case 9: // DSP
					msWriteByte ( BK0_00_REGBK, 2 );
					UART_CMD_MS_REGDATA = msVDDSPReadByte ( UART_CMD_MS_REGINDEX );
					break;

				case 0xA:
					{
						switch ( UART_CMD_MS_REGINDEX )
						{
						case 0:
							UART_CMD_MS_REGDATA = g_ucmsVDCtl;
							break;

						case 1:
							UART_CMD_MS_REGDATA = g_ucmsVDCtl2;
							break;

						case 2:
							UART_CMD_MS_REGDATA = g_ucMSVDDebug;
							break;

						case 3:
							UART_CMD_MS_REGDATA = g_ucMSVDDebug2;
							break;

						case 4:
							UART_CMD_MS_REGDATA = g_ucDebugFlag;
							break;

						case 0x10:
							UART_CMD_MS_REGDATA = msDSP_Std_GetNoiseMag();
							break;
							
						case 0x11:
							UART_CMD_MS_REGDATA = msVDGetColorLockBit();
							break;
							
						case 0x12:
							UART_CMD_MS_REGDATA = msDSP_Std_GetPhaseError();
							break;

						case 0x13:
							UART_CMD_MS_REGDATA = msVD_FSC_GetColorBurstStatus();
							break;

						case 0x14:
							UART_CMD_MS_REGDATA = msDSP_Std_GetBurstMag();
							break;
							
						case 0x15:
							UART_CMD_MS_REGDATA = msDSP_Std_GetBurstMag() >> 8;
							break;
							
						case 0x20:
							UART_CMD_MS_REGDATA = msVDGetSyncStatus();
							break;

						case 0x21:
							UART_CMD_MS_REGDATA = msVDGetSyncStatus() >> 8;
							break;
						}

						break;
					} // End of case 0xA

				case 0xB:
					{
						#if(ENABLE_VD_DSP)
						#ifdef DSP_MARIA_DEBUG

						if ( UART_CMD_MS_REGINDEX >= 0x10 && UART_CMD_MS_REGINDEX < 0x50 )
						{
							UART_CMD_MS_REGDATA = g_dspDebugInfo[ ( UART_CMD_MS_REGINDEX - 0x10 )];
						}

						else
						#endif
						#endif
						{
							switch ( UART_CMD_MS_REGINDEX )
							{
								#if(ENABLE_VD_DSP)

							case 0:
								UART_CMD_MS_REGDATA = g_ucDSP_Ctl;
								break;
								#ifdef DSP_MARIA_DEBUG

							case 1:
								UART_CMD_MS_REGDATA = g_dspDebugInfoIdx;
								break;

							case 2:
								UART_CMD_MS_REGDATA = g_dspDebugFlag;
								break;
								#endif
								#endif

							case 3:
								UART_CMD_MS_REGDATA = g_wFSCBurstMag;
								break;

							case 4:
								UART_CMD_MS_REGDATA = s_ucFSCBurstOn;
								break;

							case 5:
								UART_CMD_MS_REGDATA = s_ucFSCBurstOff;
								break;

							case 6:
								UART_CMD_MS_REGDATA = g_ucFSCNoiseMag;
								break;

							case 7:
								UART_CMD_MS_REGDATA = s_ucFSCNoiseOn;
								break;

							case 8:
								UART_CMD_MS_REGDATA = s_ucFSCNoiseOff;
								break;

							case 9:
								UART_CMD_MS_REGDATA = g_ucFSCPhaseErrorAvg;
								break;

							case 0xA:
								UART_CMD_MS_REGDATA = s_ucFSCPhaseErrorLevelOn;
								break;

							case 0xB:
								UART_CMD_MS_REGDATA = s_ucFSCPhaseErrorLevelOff;
								break;
							}
						}

						break;
					}
				
				
				case 0xC:
					{
						#define MS_REG(addr)		(((unsigned char xdata*)0)[addr])
						UART_CMD_MS_REGDATA = MS_REG(UART_CMD_MS_REGINDEX << 8 |  UART_CMD_MS_REGDATA);
					}
				
				} // End of switch( UART_CMD_MS_BANK )

				putchar ( 0xF2 );
				putchar ( UART_CMD_MS_REGDATA );

				if ( g_bDebugASCIICommandFlag )
				{
					printf ( "\r\nBK%x", UART_CMD_MS_BANK );
					printf ( "[0x%x]=", UART_CMD_MS_REGINDEX );
					printf ( "0x%x\r\n", UART_CMD_MS_REGDATA );
				}
				break;
			}

		case kWrite_MST_OSD:
			{
				msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
				msWriteOSDByte ( UART_CMD_MS_REG, UART_CMD_MS_DAT );

				if ( !g_bDebugASCIICommandFlag )
				{
					putchar ( 0xF1 );
				}
			}
			break;

		case kRead_MST_OSD:
			{
				msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
				UART_CMD_MS_DAT = msReadOSDByte ( UART_CMD_MS_REG );
				putchar ( 0xF2 );
				putchar ( UART_CMD_MS_DAT );

				if ( g_bDebugASCIICommandFlag )
				{
					printf ( "OSD[0x%x]=", UART_CMD_MS_REG );
					printf ( "0x%x \r\n", UART_CMD_MS_DAT );
				}
			}
			break;

		case kWrite_MCU:
			{
				switch ( UART_CMD_MS_REG )
				{
				case MCU_P0:
					P0 = UART_CMD_MS_DAT;
					break;

				case MCU_P1:
					P1 = UART_CMD_MS_DAT;;
					break;

				case MCU_P2:
					P2 = UART_CMD_MS_DAT;;
					break;

				case MCU_P3:
					P3 = UART_CMD_MS_DAT;;
					break;

				case MCU_P4:
					P4 = UART_CMD_MS_DAT;
					break;

				case MCU_TCON:
					TCON = UART_CMD_MS_DAT;;
					break;

				case MCU_TMOD:
					TMOD = UART_CMD_MS_DAT;;
					break;

				case MCU_PCON:
					PCON = UART_CMD_MS_DAT;;
					break;

				case MCU_IE:
					IE = UART_CMD_MS_DAT;;
					break;

				case MCU_IP:
					IP = UART_CMD_MS_DAT;;
					break;

				case MCU_SCON:
					SCON = UART_CMD_MS_DAT;;
					break;
				}

				if ( !g_bDebugASCIICommandFlag )
				{
					putchar ( 0xF1 );
				}
			}
			break;

		case kRead_MCU:
			{
				UART_CMD_MS_DAT = 0;

				switch ( UART_CMD_MS_REG )
				{
				case MCU_P0:
					UART_CMD_MS_DAT = P0;
					break;

				case MCU_P1:
					UART_CMD_MS_DAT = P1;
					break;

				case MCU_P2:
					UART_CMD_MS_DAT = P2;
					break;

				case MCU_P3:
					UART_CMD_MS_DAT = P3;
					break;

				case MCU_P4:
					UART_CMD_MS_DAT = P4;
					break;
					
				case MCU_TCON:
					UART_CMD_MS_DAT = TCON;
					break;

				case MCU_TMOD:
					UART_CMD_MS_DAT = TMOD;
					break;

				case MCU_PCON:
					UART_CMD_MS_DAT = PCON;
					break;

				case MCU_IE:
					UART_CMD_MS_DAT = IE;
					break;

				case MCU_IP:
					UART_CMD_MS_DAT = IP;
					break;

				case MCU_SCON:
					UART_CMD_MS_DAT = SCON;
					break;
				}

				putchar ( 0xF2 );
				putchar ( UART_CMD_MS_DAT );

				if ( g_bDebugASCIICommandFlag )
				{
					printf ( "0x%x \r\n", UART_CMD_MS_DAT );
				}
			}
			break;

		case kWrite_MCU_XDATA:
			{
				XBYTE[MAKEWORD ( UART_CMD_MCU_IDX_H, UART_CMD_MCU_IDX_L )] = UART_CMD_MCU_DATA;;

				if ( !g_bDebugASCIICommandFlag )
				{
					putchar ( 0xF1 );
				}
			}
			break;

		case kRead_MCU_XDATA:
			{
				UART_CMD_MCU_DATA = XBYTE[MAKEWORD ( UART_CMD_MCU_IDX_H, UART_CMD_MCU_IDX_L )];
				
				putchar ( 0xF2 );
				putchar ( UART_CMD_MCU_DATA );

				if ( g_bDebugASCIICommandFlag )
				{
					printf ( "XDATA: 0x%x \r\n", UART_CMD_MCU_DATA );
				}
			}
			break;

		// Test Only
		case kTest_Command:
			ExecTestCommand();
			break;

		} // switch

		msWriteByte ( BK0_00_REGBK, ucBank );
	}
	putchar ( 0xC7 );
}

#if (_DEBUG_PRINT_EN_)
void putSIOChar ( unsigned char sendData )
{
	EA = 0; // disable all interrupt

	SBUF = sendData; // transfer to uart

	// wait transfer completing
	while ( 1 )
	{
		if ( TI )
		{
			break; // check flag
		}
	}

	TI = 0; // clear flag

	EA = 1; // release all interrupt
}
#endif

// Put character to uart
//
// Arguments: ucVal - output character
void putchar ( BYTE ucVal )
{
	#if (_DEBUG_RW_REG_EN_||_DEBUG_PRINT_EN_)


	ES = 0; // disable uart interrupt

	SBUF = ucVal; // transfer to uart
	// wait transfer completing

	while ( 1 )
	{
		if ( TI )
		{
			break; // check flag
		}
	}

	TI = 0; // clear flag

	ES = _DEBUG_EXTDEV_EN_;// 1; // release uart interrupt
	#else
	ucVal = ucVal;
	#endif
}

// Put string to uart.
//
// Arguments: pFmt - string address
#if (_DEBUG_PRINT_EN_)
void putstr ( BYTE* pFmt )
{
	BYTE ucBff; // character buffer

	while ( 1 )
	{
		ucBff = *pFmt; // get a character

		if ( ucBff == _EOS_ ) // check end of string
		{
			break;
		}

		putchar ( ucBff ); // put a character

		pFmt++; // next
	} // while
}
#endif
/*
// Put string to uart with variable argument
//
// Arguments: pFmt - string address
// wVal - print variable
#if (_DEBUG_PRINT_EN_)

void IntToStr( WORD wVal, BYTE ucBase, BYTE* pBuf )
{
 BOOL bShowZero = FALSE;
 WORD wDivider;
 BYTE ucDisp;

 if( 0 == wVal )
 {
 pBuf[0] = '0';
 pBuf[1] = '\0';
 return;
 }

 if( 16 == ucBase )
 wDivider = 0x1000;
 else
 wDivider = 10000;

 while( wDivider )
 {
 ucDisp = wVal/wDivider;
 wVal = wVal%wDivider;

 if( ucDisp )
 bShowZero = TRUE;

 if( ucDisp || bShowZero )
 {
 if( ucDisp < 10 )
 *pBuf = '0' + ucDisp;
 else
 *pBuf = 'A' + ucDisp - 10;
 pBuf ++;
 }

 if( 16 == ucBase )
 wDivider /= 0x10;
 else
 wDivider /= 10;
 }
 *pBuf = '\0';
}
 #endif

XDATA BYTE s_Buf[6];
void printf( BYTE code *pFmt, WORD wVal )
{
#if (_DEBUG_PRINT_EN_)

 BYTE ucBff;

 while( ucBff = *(pFmt++) )
 {
 if(ucBff == '%') // check special case
 {
 switch( *(pFmt++) ) // check next character
 {
 case 'x': // hexadecimal number
 case 'X':
 IntToStr( wVal, 16, s_Buf );
 putstr( s_Buf );
 break;
 case 'd': // decimal number
 case 'i':
 IntToStr( wVal, 10, s_Buf );
 putstr( s_Buf );
 break;
 } // switch
 }
 else // general
 putchar(ucBff); // put a character
 } // while
 #endif
}
*/

#define _EOS_ '\0' // end of string

void printMsg ( char* str )
{
	#if (_DEBUG_PRINT_EN_)

	BYTE ucBff;

	putSIOChar ( ( char ) '\r' );
	putSIOChar ( ( char ) '\n' );

	while ( 1 )
	{
		ucBff = *str;

		if ( ucBff == _EOS_ )
		{
			break;
		}

		putSIOChar ( ucBff );

		str++;
	}

	#else
	str = str;
	#endif
}

void printf ( char* str, WORD value )
{
	#if (_DEBUG_PRINT_EN_)

	char sendData;//=Send_MsgValue;

	while ( sendData = * ( str++ ) )
	{
		if ( sendData == ( char ) '%' ) // %
		{
			sendData = * ( str++ );

			if ( sendData == ( char ) 'd' || sendData == ( char ) 'x' ) // d
			{
				if ( value )
				{
					BOOL noneZero = FALSE;
					WORD divider = 10000;
					char dispValue;

					if ( sendData == ( char ) 'x' )
					{
						divider = 0x1000;
					}

					while ( divider )
					{
						dispValue = value / divider;
						value -= dispValue * divider;

						if ( dispValue )
						{
							noneZero = TRUE;
						}

						if ( noneZero )
						{
							if ( dispValue > 9 )
							{
								dispValue += 55;
							}

							else
							{
								dispValue += 0x30;
							}

							putSIOChar ( dispValue );
						}

						if ( sendData == ( char ) 'd' )
						{
							divider /= 10;
						}

						else
						{
							divider /= 0x10;
						}
					}
				}

				else
				{
					putSIOChar ( '0' );
				}
			}
		}

		else
		{
			putSIOChar ( sendData );
		}
	}

	#else
	str = str;
	value = value;
	#endif
}
