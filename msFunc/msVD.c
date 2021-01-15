#define _MSVD_C_

#include <MATH.H>
#include "types.h"
#include "ms_reg.h"
#include "global.h"
#include "board.h"
#include "debug.h"
#include "ms_rwreg.h"
#include "misc.h"
#include "userPref.h"
#include "power.h"
#include "panel.h"
#include "mstar.h"
#include "devVD.h"
#include "adjust.h"

#include "maria2_FSC.h"
#include "maria2_ACC.h"
#include "m2_VD_STD.h"
#include "devVD_User.h"
#include "menu.h"
#include "msVD.h"

#include "m9_VD_AGC.h"

#include "msVDField.h"

#if(ENABLE_VD_DSP == 1)
	#include "maria2_DSP.h"
#endif


// h sync lock : DspReg[14.1] or DspReg[0x25]7:4(CTRL_STATE[3:0]) >= 6
// color lock : DspReg[0x25]7:4(CTRL_STATE[3:0]) == 8
// 50Hz : by DSP
// interlace : by scaler.
//
// BK2_01[2:0] => FREQ_FSC[2:0] ==> Detect Signal type
// 000: 4.43361875MHz.
// 010: 3.579545MHz.
// 100: 3.57561149MHz.
// 110: 3.58205625MHz
//
// BK2_01[7:4] => APLL_TRK_MD[3:0]
// 1000: APLL in tracking mode
// 0110: APLL in free run mode(no color)
//
// BK2_02[7:6] => APLL_LCK_STATE[1:0]
// 01: APLL in lock state(color on)
// xx: APLL not in lock yet(color off)
//
// BK2_02[5:4] => FRM_LNS[1:0]
// 00: Unknown
// 10: Above 575 lines
// 01: Below 575 lines
//
// BK2_02[3:2] => Lock color burst
// 01: Lock
// 10: No lock
//
// BK2_02[1:0] => TV_SYSTEM[1:0]
// 01: NTSC system
// 10: PAL system
//
// BK2_03[7] ==> VCR_MD ==> VCR mode detect
// ------------------------------------------------------------------
// When Bk2_04 = 0x04, Bk2_02 ==> Noise level
// When Bk2_04 = 0x08, Bk2_01 ==> Gain level
// ------------------------------------------------------------------
// How to judge these situation:
// VCR - Stop(OSD): Non-interlace
// VCR - Pause: Vtotal is different with normal play
// VCR : Vtotal is always change
// BK3_72[2:0]
// 000: NTSC(M)
// 001: NTSC(443)
// 010: PAL(M)
// 011: PAL(BDGHIN)
// 100: PAL(Nc)
// 111: Unknow => No signal
// Htotal*Vtotal
// NTSC(M) 910*525
// NTSC-443 1127.1*525
// PAL(M) 909*525
// PAL(BDGHIN) 1135*625+4
// PAL(Nc) 917*625+4
//
// NTSC(M) New capture = 720*910/858
// 3.58: 910 NTSC-M 525 NTSC
// 909 PAL-M 525 PAL
// 917 PAL-Nc 625
// 4.43:
// 1135 PAL-BDGHIN 625
// 1127 NTSC-443 525
// Use ShibaSoku TG35CX get some info:
// NTSC:
// FH=15.735KHz ==> HP=0x2FB
// FV=59.94Hz ==> VT=525
//-------------------------------------
// PAL:
// FH=15.625KHz ==> HP=0x334
// FV=50 ==> VT=625

//#define VD_FORCE_AUTO 0
//#define VD_FORCE_PAL 1 // 443 50Hz
//#define VD_FORCE_NTSC_443 2 // 443 60Hz
//#define VD_FORCE_PAL_358 3 // 358 ( 60Hz -> PAL_M, 50Hz -> PAL_NC )
//#define VD_FORCE_NTSC 4 // 358 60Hz
//#define VD_FORCE_SECAM 5 // 428 50Hz

WORD code tVideoSystemStdHTotal[SIG_NUMS] =
{
	910, // SIG_NTSC, // M
	1135, // SIG_PAL, // B/G, D/K, I, H, N
};

void msVDDSPWriteByte ( BYTE ucAddr, BYTE ucData )
{
	BYTE ucBk2_07 = msReadByte ( BK2_07 );

	msWriteByte ( BK2_07, ucAddr );
	msWriteByte ( BK2_08, ucData );
	
	msWriteByte ( BK2_07, ucBk2_07 );
}

BYTE msVDDSPReadByte ( BYTE ucAddr )
{
	BYTE ucTmp;
	BYTE ucBk2_07 = msReadByte ( BK2_07 );
	
	msWriteByte ( BK2_07, ucAddr );
	ucTmp = msReadByte ( BK2_09 );
	
	msWriteByte ( BK2_07, ucBk2_07 );
	return ucTmp;
}

WORD msVDDSPRead2Bytes ( BYTE ucAddr )
{
	return ( msVDDSPReadByte ( ucAddr ) + ( msVDDSPReadByte ( ucAddr + 1 ) << 8 ) );
}

BYTE msVDSpecialRead ( BYTE ucMux, BYTE ucAddr )
{
	BYTE ucBank;
	BYTE ucBackupBK2_04;
	BYTE ucTmp;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	ucBackupBK2_04 = msReadByte ( BK2_04 );
	msWriteByte ( BK2_04, ucMux );
	ucTmp = msReadByte ( ucAddr );
	msWriteByte ( BK2_04, ucBackupBK2_04 );
	msWriteByte ( BK0_00_REGBK, ucBank );
	return ucTmp;
}

void msVDReset ( void )
{
	BYTE ucBank = msReadByte ( BK0_00_REGBK );

	putstr ( "\r\n[Reset VD]" );

	#if( ENABLE_PAL_SWITCH_HANDLER == 1 )
	//if( g_ucmsVDCtl2&MSVD_CTL2_FLAG_PAL_SWITCH )
	msVDPalSwitchHandlerReset ( PAL_SWITCH_AUTO ); // Auto detect PAL/NTSC
	#endif

	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	//msWriteByteMask(BK2_21_APLL_CTRL2, 0x00, 0x06); // Auto detect PAL/NTSC

	msWriteBit ( BK2_14_SOFT_RST, 1, _BIT7 );
	Delay1ms ( 1 );
	msWriteBit ( BK2_14_SOFT_RST, 0, _BIT7 );
	Delay1ms ( 1 );

	if ( g_ucmsVDCtl2 & MSVD_CTL2_FLAG_AGC_PROCESSOR )
	{
		VD_AGC_Ctl ( VD_AGC_CTL_ENABLE );
	}

	#if(ENABLE_VD_DSP == 1)

	if ( g_ucmsVDCtl & MSVD_CTL_FLAG_VSYNC )
	{
		BYTE ucVSyncCtl = VD_DSP_CTL_ENABLE;

		#if(ENABLE_VSYNC_CTL_AUTO_H_TOTAL)
		ucVSyncCtl |= VD_DSP_CTL_DISABLE_AUTO_H_TOTAL;
		#endif

		#if ( TV_SYSTEM == TV_NTSC )
		VD_DSP_Ctl ( ucVSyncCtl, 525 ); // Enable DSP, 60Hz
		#else
		VD_DSP_Ctl ( ucVSyncCtl, 625 ); // Enable DSP, 50Hz
		#endif
	}

	#elif( ENABLE_SW_FIELD )
	msVDDSPWriteByte ( DSP_0F, 0x04 );
	#endif

	if ( g_ucmsVDCtl & MSVD_CTL_FLAG_NOISE_HANDLER )
	{
		msVDNoiseHandlerInit();
	}

	#if ( SCALER_TYPE != MARIA9 )
	//yurian for VD Reset DSP10 error
	{
		BYTE DSP10_Value = msVDDSPReadByte ( DSP_10 );

		while ( DSP10_Value != 0x85 )
		{
			Delay1ms ( 2 );
			msVDDSPWriteByte ( DSP_10, 0x85 );
			msVDDSPWriteByte ( DSP_11, 0x00 );
			Delay1ms ( 1 );
			DSP10_Value = msVDDSPReadByte ( DSP_10 );
		}
	}
	#endif
	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msVD_FSM_Reset ( void )
{
	BYTE ucBank = msReadByte ( BK0_00_REGBK );
	putstr ( "\r\n[Reset FSM]" );

	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	msWriteBit ( BK2_14_SOFT_RST, 1, _BIT6 );
	Delay1ms ( 1 );
	msWriteBit ( BK2_14_SOFT_RST, 0, _BIT6 );
	Delay1ms ( 1 );
	msWriteByte ( BK0_00_REGBK, ucBank );
}

WORD msVDGetVTotal ( void )
{
	BYTE ucBank;
	WORD wVTotal;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	wVTotal = msVDDSPRead2Bytes ( 0 );
	msWriteByte ( BK0_00_REGBK, ucBank );
	return wVTotal;
}

// ucFlag:
// [1:0]: 1 -> Always return a valid h freq
// 2 -> Return virtual H period
WORD msGetVideoHPeriod ( BYTE ucFlag )
{
	BYTE i;
	WORD wInHP;
	WORD wInHF;

	if ( ( ucFlag & 3 ) != 2 )
	{
		for ( i = 0; i < 10; ++ i )
		{
			wInHP = msGetHorizontalPeriod();

			if ( wInHP )
			{
				wInHF = MST_CLOCK_HZ / wInHP;

				if ( ( wInHF >= 13500 ) && ( wInHF <= 17800 ) )
				{
					return wInHP;
				}
			}
		}
	}

	// H period invalid...
	if ( ( ucFlag & 3 ) )
	{
		if ( msVDGetVTotal() > 566 )
		{
			return MST_CLOCK_HZ / 15625;
		}

		else
		{
			return MST_CLOCK_HZ / 15734;
		}
	}

	return 0;
}

#if(ENABLE_CHECK_AUTO_H_TOTAL == 1)

BYTE msVDCheckScalerStatus ( BYTE ucCheckFlag )
{
	BYTE ucStatus = 0;
	WORD wTmp;
	WORD wHFreq;
	WORD wVTotal;

	// Calculate H frequency ...
	wTmp = msGetHorizontalPeriod();

	if ( wTmp == 0x1fff || wTmp == 0 ) // Check H period
	{
		//printf("\r\nHP=%d", wTmp);
		ucStatus |= VD_H_PERIOD_INVALID;
	}

	else // H period is valid
	{
		wHFreq = msCalculateHFreqX10 ( wTmp ); // Cal H freq

		if ( wHFreq < 146 || wHFreq > 167 ) //200 ) // Hfreq < 14.6K, > 16.6K => freq invalid
		{
			ucStatus |= VD_H_FREQ_INVALID;
		}

		else // H freq is valid
		{
			if ( ucCheckFlag & VD_V_TOTAL_INVALID )
			{
				wVTotal = msVDGetVTotal(); // Get VTotal from VD
				wTmp = msGetVerticalTotal(); // Get VTotal from scaler

				// Check VD&Scaler VTotal
				if ( ( wVTotal < 420 ) || ( wVTotal > 730 )
					|| ( wTmp < 420 ) || ( wTmp > 730 )
					|| ( abs ( ( int ) wVTotal - wTmp ) > 50 ) ) // The VTotal of VD and Scaler is different!!
				{
					ucStatus |= VD_V_TOTAL_INVALID;
				}

				else // VTotal is valid
				{
					if ( ucCheckFlag & VD_V_FREQ_INVALID )
					{
						// Cal V freq
						wTmp = msCalculateVFreqX10 ( wHFreq, wTmp ) * 2;

						if ( wTmp < 440 || wTmp > 660 )
						{
							ucStatus |= VD_V_FREQ_INVALID;
						}
					}
				}
			}
		}
	}

	return ucStatus;
}
#endif

bit msVDGetColorLockBit ( void )
{
	// bit b;
	// b = (msDSP_Std_GetBurstMag() > 0x)
	return msVD_FSC_GetColorBurstStatus();
}

WORD msVDGetSyncStatus ( void )
{
	BYTE ucBank;
	BYTE ucTmp;
	WORD wVDStatus = 0;
	BYTE ucCombStatus;
	WORD wVDVtotal = msVDGetVTotal();

	ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
	ucCombStatus = msReadByte ( BK3_72_COMB_STSC );

	// Check V total
	#if( ENABLE_VD_DSP )

	if ( wVDVtotal > 566 ) // 625 lines
	{
		wVDStatus |= VD_VSYNC_50HZ;
	}

	#else

	if ( ucCombStatus & _BIT6 ) // 625 lines
	{
		wVDStatus |= VD_VSYNC_50HZ;
	}

	#endif


	// Fix issue w/ blue screen not appearing on signal loss 
	// when last Video level is too low (below 20%)
	if ( ( g_VdInfo.ucVideoSystem != SIG_NONE ) && ( ( ucCombStatus & _BIT3 ) != 0 ) ) // 20060908 kevin
	{
		AGC_Processor();
		//VD_AGC_Processor();
		Delay1ms_AGC_Processor ( 10 );

		msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
		ucCombStatus = msReadByte ( BK3_72_COMB_STSC );

		if ( ( g_VdInfo.ucVideoSystem != SIG_NONE ) && ( ( ucCombStatus & _BIT3 ) != 0 ) )
		{
			VD_AGC_ResetGain ( 0x1C00 );
		}
	}


	//if( 0 == (ucCombStatus&_BIT3) ) // Check comb: No input signal
	{
		msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

		if ( ( ( msVDSpecialRead ( 0x00, BK2_01 ) & 0xF0 ) >= 0x60 ) // Sync ctl state > 6
			&& ( msVDDSPReadByte ( 0x14 ) &_BIT1 ) ) // SYNC_FOUND
		{
			#if( ENABLE_VD_DSP )

			if ( wVDVtotal >= 420 && wVDVtotal <= 730 )
			#else
			if ( ( ucCombStatus & 0x07 ) != 7 )
			#endif
			{
				wVDStatus |= ( VD_HSYNC_LOCKED | VD_SYNC_LOCKED );

				// Check interlace
				if ( msGetInterlaceBit() )
				{
					wVDStatus |= VD_INTERLACED;
				}
			}
		}
	}

	// Get other VD status:
	if ( wVDStatus & VD_HSYNC_LOCKED )
	{
		// Check color
		// Get bk2_02 value
		ucTmp = msVDSpecialRead ( 0x00, BK2_02 );

		// Check Color burst lock
		if ( ( ucTmp & 0x0C ) == 0x04 )
		{
			wVDStatus |= VD_COLOR_LOCKED;
		}

		// Check FSC
		ucTmp = msVDSpecialRead ( 0x00, BK2_01 );

		switch ( ucTmp & 0x0F )
		{
		case 0:
			wVDStatus |= VD_FSC_4433;
			break;

		case 2:
			wVDStatus |= VD_FSC_3579;
			break;

		case 8:
			wVDStatus |= VD_FSC_NONE;
			break;

		// case 6:
			// wVDStatus |= VD_FSC_3582;
			// break;

		// case 1:
			// wVDStatus |= VD_FSC_4285;
			// break;
		}

		// Check PAL switch
		if ( g_ucMSVDForceSystem == VD_FORCE_AUTO )
		{
			if ( wVDStatus & VD_VSYNC_50HZ ) // 50 Hz
			{
				wVDStatus |= VD_PAL_SWITCH;
			}

			else // 60 Hz
			{
				// ucTmp = wVDStatus&VD_FSC_TYPE;
				// if( (ucTmp == VD_FSC_3579)
				// ||(ucTmp == VD_FSC_3575)
				// ||(ucTmp == VD_FSC_3582)
				// ||(ucTmp == VD_FSC_4433)
				// )
				{
					if ( VD_Type < MARIA2_E )
					{
						ucTmp = msVDSpecialRead ( 0x00, BK2_03 );

						if ( ucTmp & _BIT5 )
						{
							wVDStatus |= VD_PAL_SWITCH;
						}
					}

					#if( ENABLE_SW_DETECT_COLOR_STD )

					else if ( g_ucVD_ColorStd == DSP_COLOR_PAL )
					{
						wVDStatus |= VD_PAL_SWITCH;
					}

					#endif
				}
			}
		}

		else // Force color
		{
			if ( ( g_ucMSVDForceSystem == VD_FORCE_PAL ) || ( g_ucMSVDForceSystem == VD_FORCE_PAL_358 ) )
			{
				wVDStatus |= VD_PAL_SWITCH;
			}
		}

		//wVDStatus |= msVDGetVideoSystem( wVDStatus )
	}

	msWriteByte ( BK0_00_REGBK, ucBank );

	return wVDStatus;
}

// Std 50/60 Vtotal FSC HTotal Color
//-----------------------------------------
// NTSC 60 525 358 910
// PAL-M 60 525 358 909 PAL-Switch
// NTSC-443 60 525 443 1127
// PAL-60 60 525 443 1127 PAL-Switch
// xxx 50 625 358
// PAL-Nc 50 625 358 917 PAL-Switch
// xxx 50 625 443
// PAL 50 625 443 1135 PAL-Switch
// SECAM 50 625 428 1097

BYTE msVDGetVideoSystem ( WORD wVideoStatus )
{
	BYTE ucSignalType = SIG_NONE;

	putstr ( "\r\n" );

	if ( wVideoStatus & VD_HSYNC_LOCKED )
	{
		if ( wVideoStatus & VD_VSYNC_50HZ ) // 50Hz
		{
			switch ( wVideoStatus & VD_FSC_TYPE )
			{
				default:
				case VD_FSC_4433: // 4.43361875MHz, PAL or NTSC443 or PAL(60)
				ucSignalType = SIG_PAL;
				putstr ( "[PAL]" );
				break;

			}
		}

		else // 60Hz
		{
			switch ( wVideoStatus & VD_FSC_TYPE )
			{

			case VD_FSC_3579: // 3.579545MHz, NTSC
			//case VD_FSC_3575: // 3.57561149MHz,PAL(M)
			//case VD_FSC_3582: // 3.58205625MHz,PAL(Nc)
			default:
					ucSignalType = SIG_NTSC;
					putstr ( "[NTSC]" );

				break;
			}
		}
	}

	return ucSignalType;
}

void msVDColorKill ( BOOL bColorKill )
{
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

	if ( bColorKill ) // COLOR_OFF
	{
		printMsg ( "color OFF" );
		msWriteByteMask ( BK2_55_COLOR_OFF, 0xC0, 0xC0 );
		
		msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
		msWriteByteMask ( BK3_60_IMGCTRL, 0x80, 0xF0 ); // Disable Auto Chroma Gain

		if ( msDSP_Std_GetNoiseMag() < 10 )
		{
			msWriteByteMask ( BK3_21_COMB2DCFGB, 0x30, 0x70 ); // Notch mode of Y
		}
		else
		{
			msWriteByteMask ( BK3_21_COMB2DCFGB, 0x20, 0x70 ); // Notch mode of Y
		}

	}

	else // COLOR return
	{
		printMsg ( "color ON" );
		msWriteByteMask ( BK2_55_COLOR_OFF, 0x80, 0xC0 );
		
		msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
		msWriteByteMask ( BK3_21_COMB2DCFGB, 0x60, 0x70 ); // Notch mode of Y
		msWriteByteMask ( BK3_60_IMGCTRL, 0x90, 0xF0 ); // Enable HW Auto Chroma Gain
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msVDLineLockCtl ( BOOL bLock )
{
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

	if ( bLock )
	{
		msVDDSPWriteByte ( DSP_20, 0x00 );
		msVDDSPWriteByte ( DSP_21, 0x80 );
		
		//if( (g_VdInfo.wVideoStatus&VD_FSC_TYPE) != VD_FSC_4XXX ) // NTSC
		{
			msWriteBit ( BK2_23_APLL_TRANGE, 1, _BIT0 ); // 20060103.Daniel
			msWriteByte ( BK2_26_APL_K1_NORMAL, 0x04 ); // APL_K1: 20060328.CY.Ko
			msWriteByte ( BK2_27_APL_K2_NORMAL, 0 ); // APL_K2
		}
		
		g_bVDCurLineLockStatus = 1;
		putstr ( "\r\nLine Lock" );
	}

	else
	{
		msVDDSPWriteByte ( DSP_20, 0x00 );
		msVDDSPWriteByte ( DSP_21, 0x00 );
		msWriteBit ( BK2_23_APLL_TRANGE, 0, _BIT0 ); // 20060103.Daniel
		msWriteByte ( BK2_26_APL_K1_NORMAL, 0x10 ); // APL_K1: 20060328.CY.Ko
		msWriteByte ( BK2_27_APL_K2_NORMAL, 0x08 ); // APL_K2
		g_bVDCurLineLockStatus = 0;
		putstr ( "\r\nNo Line Lock" );
	}

	msVDCombLineBufferCtl ( MSVD_COMB_LINE_BUFFER_CTL_SW );

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msVDColorBurstHandler ( BYTE ucFlag )
{
	bit bCurColorBurstStatus;

	if ( g_bForceColorEnable )
	{
		return;
	}

	if ( ucFlag & VD_COLOR_BURST_HANDLER_RESET )
	{
		printMsg("[msVDColorBurstHandler] reset");
		msVDColorKill ( TRUE );
		msVDLineLockCtl ( _DISABLE );
		msDSP_Std_Init(); // ???

		msVD_FSC_ResetColorBurstStatus();

		bCurColorBurstStatus = 0;
		g_bVDColorBurstHandler_LastColorBurstStatus = 0;
		g_ucVDColorBurstHandlerStableCounter = 0;

		g_wVDColorBurstHandlerTimer = 100;
		return;
	}

	else if ( g_wVDColorBurstHandlerTimer != 0)
	{
		return;
	}


	g_wVDColorBurstHandlerTimer = 20;

	bCurColorBurstStatus = msVDGetColorLockBit();
	
	if ( bCurColorBurstStatus != g_bVDColorBurstHandler_LastColorBurstStatus )
	{
		// printf("\r\nbCurColorBurstStatus: %d",bCurColorBurstStatus);
		g_ucVDColorBurstHandlerStableCounter++;

		if ( g_ucVDColorBurstHandlerStableCounter >= 5 )
		{
			g_ucVDColorBurstHandlerStableCounter = 0;
			g_bVDColorBurstHandler_LastColorBurstStatus = bCurColorBurstStatus;

			if ( bCurColorBurstStatus ) // Has color
			{
				msVDColorKill ( FALSE );
			}

			else // No color
			{
				msVDColorKill ( TRUE );
			}

			g_wVDColorBurstHandlerTimer = 100;
		}
	}

	else
	{
		g_ucVDColorBurstHandlerStableCounter = 0;
	}

// return;

	// Line lock handler
	{
		bit bForceLineLock = 0;
		WORD val = msDSP_Std_GetBurstMag();
		// Detect if should line lock
		if ( ( g_bVDColorBurstHandler_LastColorBurstStatus == 0 ) // Color kill
			&& ( ( val  < 0x23 ) ) ) // No burst pattern
		{
			//printf("\r\nburstmag: %d", val);
			bForceLineLock = 1;
		}

		if ( bForceLineLock != g_bVDCurLineLockStatus )
		{
			g_ucMSVDSwitchLineLockCnt++;

			if ( g_ucMSVDSwitchLineLockCnt >= 5 )
			{
				g_ucMSVDSwitchLineLockCnt = 0;

				if ( bForceLineLock )
				{
					msVDLineLockCtl ( _ENABLE ); // Switch to line lock
					//putstr("\r\nLine lock");
				}

				else
				{
					msVDLineLockCtl ( _DISABLE ); // Switch to no line lock
					//putstr("\r\nNo Line lock");
				}
			}
		}

		else
		{
			g_ucMSVDSwitchLineLockCnt = 0;
		}
	}
}

code StuVideoSystemInfo tVideoSystemInfo[SIG_NUMS] =
{
	{ MSVD_HTOTAL_NTSC, MSVD_HACTIVE_NTSC },// SIG_NTSC, // M
	{ MSVD_HTOTAL_PAL, MSVD_HACTIVE_PAL },// SIG_PAL, // B/G, D/K, I, H, N
};

void msVDSetupMode ( WORD wStatus, BYTE ucSignalType )
{
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );
	
	// csrf
	// disable 
	msVDColorBurstHandler ( VD_COLOR_BURST_HANDLER_RESET );

	//if( g_ucmsVDCtl & MSVD_CTL_FLAG_NOISE_HANDLER )
	msVDNoiseHandlerReset();

	//if( g_ucmsVDCtl2 & MSVD_CTL2_FLAG_AGC_PROCESSOR )
	// {
		if ( wStatus & VD_HSYNC_LOCKED )
		{
			BYTE val = 0;
			if ( g_VideoSetting.VideoColorSys == CHROMA_PAL){
				val = 1;
			}
			VD_AGC_SetFscThreshold ( val );
		}
	// }

	#if( ENABLE_HSYNC_HANDLER )
	//if( g_ucmsVDCtl2 & MSVD_CTL2_FLAG_HSYNC )
	{
		msVDHSyncHandlerReset();
	}
	#endif

	// Setup VD H total and DE width
	{
		WORD wHTotal;
		WORD wHActive;

		if ( wStatus & VD_HSYNC_LOCKED )
		{
			wHTotal = tVideoSystemInfo[ucSignalType]._wHTotal;
			wHActive = tVideoSystemInfo[ucSignalType]._wHActive;
		}

		else
		{
			if ( wStatus & VD_VSYNC_50HZ )
			{
				wHTotal = tVideoSystemInfo[SIG_PAL]._wHTotal;
				wHActive = tVideoSystemInfo[SIG_PAL]._wHActive;
			}

			else
			{
				wHTotal = tVideoSystemInfo[SIG_NTSC]._wHTotal;
				wHActive = tVideoSystemInfo[SIG_NTSC]._wHActive;
			}
		}

		wHActive += 24;
		msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

		if ( wHActive > 1024 )
		{
			msWriteByte ( BK2_7B_656_HDEW, 0 ); // 656_HDEW
		}

		else
		{
			#if(PANEL_ANALOG_TCON)
			msWriteByte ( BK2_7B_656_HDEW, ( ( ( ( wHActive ) - 4 ) / 4 ) + 0x20 ) ); // 656_HDEW
			#else
			msWriteByte ( BK2_7B_656_HDEW, ( ( ( wHActive ) - 4 ) / 4 ) ); // 656_HDEW
			#endif
		}

		wHTotal -= 1;
		msWriteByte ( BK2_9D_DPL_NSPL_HIGH, ( wHTotal / 8 ) ); // bit3~10
		msWriteByte ( BK2_9E_DPL_NSPL_LOW, ( wHTotal & 7 ) << 5 ); // bit0~2
	}

	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );

	// if( wStatus & VD_VSYNC_50HZ ) // 50 Hz
	// {
		// msWriteByteMask(BK3_40, 0x03, 0x03); // Force 625 lines
	// }
	// else // 60 Hz
	// {
		// msWriteByteMask(BK3_40, 0x02, 0x03); // Force 525 lines
	// }

	if ( VD_Type == MARIA2_D )
	{
		msWriteByte ( BK3_6F_MAX_CRMA, 0x04 );
	}

	msWriteByteMask ( BK3_48_BSTLVL_TH, 0x00, 0x30 ); // Pipe delay off
	msWriteByteMask ( BK3_21_COMB2DCFGB, 0x07, 0x07 ); // Notch mode of C

	msWriteByte ( BK3_62, 0xA0 );
	msWriteByte ( BK3_2F, 0x00 );

	SetChromaMode();

	msVDCombLineBufferCtl ( MSVD_COMB_LINE_BUFFER_CTL_HW_AUTO );

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msCommSetupMode( void )
{
	msFieldDetectCtl();

	// Setup interlace relative register
	msDetectInterlace ( 1 ); // For setup mode

	//msLPFCtl ( LPF_CTL_TV_STRONG ); // for TV enable
	msLPFCtl ( LPF_CTL_TV_NORMAL );
}

#ifdef VD_PATCH_001
// Call this function one time when no signal
BOOL msVD_Patch_001 ( void )
{
	if ( ( msVDSpecialRead ( 0x00, BK2_01 ) & 0xF0 ) == 0x30 )
	{
		//msVDReset();
		msVD_FSM_Reset();
		return TRUE;
	}

	return FALSE;
}
#endif

#ifdef VD_PATCH_002
// Call this function when mode change!
BOOL msVD_Patch_002 ( WORD wVDStatus )
{
	bit bResult = 0;
	BYTE ucCurVideoSystem;

	//printf("\r\nmsVD_Patch_002(%x)", wVDStatus);

	ucCurVideoSystem = msVDGetVideoSystem ( wVDStatus );

	if ( VD_Type >= MARIA2_E ) //hyy 070416
	{
		if ( ucCurVideoSystem == SIG_NTSC )
		{
			//if( g_msVD_Patch002_LastVideoSystem != SIG_NTSC )
			if ( ( wVDStatus & VD_FSC_TYPE ) != VD_FSC_3579 )
			{
				putstr ( "\r\nPatch002: ?? --> NTSC" );
				bResult = 1;
			}
		}

		#if 1 //( ENABLE_SW_DETECT_COLOR_STD )

		else if ( ucCurVideoSystem == SIG_PAL_M )
		{
			//if( g_msVD_Patch002_LastVideoSystem != SIG_PAL_M )
			if ( ( wVDStatus & VD_FSC_TYPE ) != VD_FSC_3575 )
			{
				putstr ( "\r\nPatch002: ?? --> PAL_M" );
				bResult = 1;
			}
		}

		else if ( ucCurVideoSystem == SIG_PAL_NC )
		{
			if ( ( wVDStatus & VD_FSC_TYPE ) != VD_FSC_3582 )
			{
				putstr ( "\r\nPatch002: ?? --> PAL_N" );
				bResult = 1;
			}
		}

		#endif
	}

	else
	{
		if ( ucCurVideoSystem == SIG_NTSC )
		{
			//if( g_msVD_Patch002_LastVideoSystem != SIG_NTSC )
			if ( ( wVDStatus & VD_FSC_TYPE ) != VD_FSC_3579 )
			{
				putstr ( "\r\nPatch002: ?? --> NTSC" );
				bResult = 1;
			}
		}
	}

	if ( bResult )
	{
		// if ( ucCurVideoSystem == SIG_PAL_M || ucCurVideoSystem == SIG_PAL_NC )
		// {
			// msVD_FSM_Reset();
		// }

		// else
		// {
			msVD_FSM_Reset ();
		// }
	}

	g_msVD_Patch002_LastVideoSystem = ucCurVideoSystem;
	return bResult;
}
#endif

#ifdef VD_PATCH_003
XDATA BYTE g_msVD_Patch003_StableCounter;
BOOL msVD_Patch_003 ( BYTE ucFlag )
{
	if ( ( ucFlag == 0 ) || ( !msVDGetColorLockBit() ) )
	{
		g_msVD_Patch003_StableCounter = 0;
	}

	else
	{
		if ( ( msVDSpecialRead ( 0x0E, 0x01 ) > 0x70 )
			&& ( msDSP_Std_GetNoiseMag() < 0x20 ) ) // Clean signal
		{
			++ g_msVD_Patch003_StableCounter;

			if ( g_msVD_Patch003_StableCounter > 3 )
			{
				g_msVD_Patch003_StableCounter = 0;
				putstr ( "\r\nPatch003: Phase Error!" );
				msVD_FSM_Reset();
				return TRUE;
			}
		}

		else
		{
			g_msVD_Patch003_StableCounter = 0;
		}
	}

	return FALSE;
}
#endif

#ifdef VD_PATCH_004
XDATA g_msVD_Patch004_StableCounter;
void msVD_Patch_004 ( BOOL bEnable )
{
	if ( bEnable )
	{
		int iTmp = msVDGetVTotal();

		if ( abs ( iTmp - msGetVerticalTotal() ) >= 50 )
		{
			++ g_msVD_Patch004_StableCounter;
		}

		else
		{
			g_msVD_Patch004_StableCounter = 0;
		}

		if ( g_msVD_Patch004_StableCounter > 10 )
		{
			msVD_FSM_Reset();
			//msVDReset();
			g_msVD_Patch004_StableCounter = 0;
		}
	}

	else
	{
		g_msVD_Patch004_StableCounter = 0;
	}
}
#endif

#ifdef VD_PATCH_005
XDATA BYTE g_msVD_Patch005_VDAbnormalCounter;
void msVD_Patch_005 ( BYTE ucResetTime )
{

	if ( ucResetTime )
	{
		g_msVD_Patch005_VDAbnormalCounter = 0;
		g_msVD_Patch005_Timer = ucResetTime;
	}

	else
	{
		BYTE ucScalerStatus;

		if ( g_msVD_Patch005_Timer )
		{
			return;
		}

		g_msVD_Patch005_Timer = 10;

		ucScalerStatus = msVDCheckScalerStatus ( 0 );

		if ( ucScalerStatus != 0 )
		{
			g_msVD_Patch005_VDAbnormalCounter ++;

			if ( g_msVD_Patch005_VDAbnormalCounter > 3 )
			{
				g_msVD_Patch005_VDAbnormalCounter = 0;
				putstr ( "\r\n=====VD output abnormally=====" );
				// Reset VD
				msVD_FSM_Reset();
			}
		}

		else
		{
			g_msVD_Patch005_VDAbnormalCounter = 0;
		}
	}
}
#endif

void msVDCombLineBufferCtl ( BYTE flag )
{
	BYTE ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );

	if ( flag == MSVD_COMB_LINE_BUFFER_CTL_HW_AUTO )
	{
		msWriteByteMask ( BK3_50, 0x07, 0x07 ); // Line buffer free run mode: Auto
	}

	else
	{
		bit bCurLineLockStatus = 0;

		msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

		// Get line lock status
		if ( msVDDSPReadByte ( 0x21 ) &_BIT7 )
		{
			bCurLineLockStatus = 1;
		}

		msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );

		if ( bCurLineLockStatus ) // Current is line lock mode
		{
			if ( ( g_VdInfo.wVideoStatus & VD_FSC_TYPE ) == VD_FSC_4433 ) // PAL/NTSC443/SECAM
			{
				msWriteByteMask ( BK3_50, 0x05, 0x07 ); // Line buffer free run mode: Decided by register
			}

			else // NTSC
			{
				msWriteByteMask ( BK3_50, 0x02, 0x07 ); // Line buffer free run mode: Decided by register
			}
		}

		else // Current is not line lock mode
		{
				WORD wHTotal;

				msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
				wHTotal = msVDDSPRead2Bytes ( DSP_3C );
				//printf("\r\nAFEC:HTotal:%d", wHTotal);

				msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );

				if ( wHTotal > 1151 )
				{
					// Force 1151 pixel
					msWriteByteMask ( BK3_50, 0x06, 0x07 ); // Line buffer free run mode: Decided by register
					msWriteByte ( BK3_52, 0x7F ); // H return position L
					msWriteByte ( BK3_53, 0x04 ); // H return position H
				}

				else
				{
					msWriteByteMask ( BK3_50, 0x07, 0x07 ); // Line buffer free run mode: Auto
					//msWriteByte( BK3_52, 0x8E ); // H return position L
					//msWriteByte( BK3_53, 0x03 ); // H return position H
				}
		}
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msVDNoiseHandlerInit ( void )
{
	BYTE ucBank;
	WORD wTmp;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

	wTmp = msVDDSPRead2Bytes ( DSP_10 );

	wTmp |= 0x0080;
	msVDDSPWriteByte ( DSP_10, wTmp );
	msVDDSPWriteByte ( DSP_10 + 1, wTmp >> 8 );

	msVDNoiseHandlerReset();

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msVDNoiseHandlerReset ( void )
{
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

	g_ucNoiseDebounce = 0;
	bNoisy_Det = 0;
	bLastNoisyStatus = bNoisy_Det;

	msVDDSPWriteByte ( DSP_84, msVDDSPReadByte ( DSP_84 ) & ( ~_BIT1 ) ); // Clean mode
	msWriteByteMask ( BK2_38_VSTROBE_LIMIT, 0x03, 0x07 );
	msWriteByteMask ( BK2_97_EDGES_CLEAN_TH, 0x00, 0xC0 );
	msWriteByte ( BK2_73_INI_CTRL2, 0x10 ); // V-Slice=2/8,H-Slice=4/8
	msWriteByte ( BK2_79_656_HDES1, 0x17 );
	msWriteByte ( BK2_7A, 0x20 );

	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );

	msWriteByteMask ( BK3_6F_MAX_CRMA, 0x00, 0x03 ); // Cb/Cr low pass mode
	g_ucMSVDNoiseHandlerTimer = 200;

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msVDNoiseHandler ( void )
{
	BYTE ucBank;
	WORD wNoiseMag;

	if ( g_ucMSVDNoiseHandlerTimer )
	{
		return;
	}

	g_ucMSVDNoiseHandlerTimer = 20;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

	// Noise detection ...

	//wNoiseMag = msDSP_Std_GetNoiseMag();
	wNoiseMag = msVDDSPReadByte ( DSP_2A );

	if ( g_ucNoiseDebounce < 30 )
	{
		if ( wNoiseMag > 0x40 )
		{
			g_ucNoiseDebounce += 4;
		}

		else if ( wNoiseMag >= 0x30 )
		{
			g_ucNoiseDebounce += 2;
		}

		else if ( wNoiseMag > 0x28 )
		{
			g_ucNoiseDebounce ++;
		}
	}

	if ( g_ucNoiseDebounce != 0 )
	{
		if ( wNoiseMag < 0x10 )
		{
			if ( g_ucNoiseDebounce < 6 )
			{
				g_ucNoiseDebounce = 0;
			}

			else
			{
				g_ucNoiseDebounce -= 6;
			}
		}

		else if ( wNoiseMag < 0x20 )
		{
			g_ucNoiseDebounce --;
		}
	}

	if ( g_ucNoiseDebounce >= 30 )
	{
		bNoisy_Det = 1;
	}

	else if ( g_ucNoiseDebounce == 0 )
	{
		bNoisy_Det = 0;
	}

	if ( bLastNoisyStatus != bNoisy_Det )
	{
		if ( bNoisy_Det ) // Noise mode
		{
			putstr ( "\r\nNoise mode" );
			
			msVDDSPWriteByte ( DSP_84, msVDDSPReadByte ( DSP_84 ) | ( _BIT1 ) ); // Noise mode
			msWriteByteMask ( BK2_38_VSTROBE_LIMIT, 0x07, 0x07 );
			msWriteByteMask ( BK2_97_EDGES_CLEAN_TH, 0x80, 0xC0 ); // [7:6]='10' (slice input IIR8)
			msWriteByte ( BK2_73_INI_CTRL2, 0xF0 ); // V-Slice=6/8,H-Slice=6/8
			msWriteByte ( BK2_79_656_HDES1, 0x16 );
			msWriteByte ( BK2_7A, 0xA0 ); // HDES

			msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
			msWriteByteMask ( BK3_6F_MAX_CRMA, 0x03, 0x03 ); // Cb/Cr low pass mode

		}

		else // Clean mode
		{
			putstr ( "\r\nClean mode" );
			msVDDSPWriteByte ( DSP_84, msVDDSPReadByte ( DSP_84 ) & ( ~_BIT1 ) ); // Clean mode
			msWriteByteMask ( BK2_38_VSTROBE_LIMIT, 0x03, 0x07 );
			msWriteByteMask ( BK2_97_EDGES_CLEAN_TH, 0x00, 0xC0 ); // [7:6] = '00' (slice input CCTRAP)
			msWriteByte ( BK2_73_INI_CTRL2, 0x10 ); // V-Slice=2/8,H-Slice=4/8
			msWriteByte ( BK2_79_656_HDES1, 0x18 );
			msWriteByte ( BK2_7A, 0x20 ); // HDES

			msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );
			msWriteByteMask ( BK3_6F_MAX_CRMA, 0x00, 0x03 ); // Cb/Cr low pass mode
		}

		bLastNoisyStatus = bNoisy_Det;
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msVDCombHandler ( void )
{
	BYTE ucBank;
	WORD wHTotalDiff;

	// if( g_ucMsVDCombHandler_Timer )
	// return;

	// g_ucMsVDCombHandler_Timer = 100;

	ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

	wHTotalDiff = abs ( msVDDSPRead2Bytes ( 0x3C ) - tVideoSystemStdHTotal[g_VdInfo.ucVideoSystem] );

	msWriteByte ( BK0_00_REGBK, REG_BANK3_COMB );

	if ( ( msReadByte ( BK3_10_COMBCFGA ) & 3 ) == 2 ) // Current is 2D
	{
		if ( wHTotalDiff >= 6 )
		{
			msWriteByteMask ( BK3_10_COMBCFGA, 0x01, 0x07 ); // Switch to 1D
		}
	}

	else // Current is 1D
	{
		if ( wHTotalDiff <= 4 )
		{
			msWriteByteMask ( BK3_10_COMBCFGA, 0x02, 0x07 ); // Switch to 2D
		}
	}

	if ( g_ucmsVDCtl & MSVD_CTL_FLAG_COMB_LINE_BUF ) // For debug
	{
		msVDCombLineBufferCtl ( MSVD_COMB_LINE_BUFFER_CTL_SW );
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void Fsm_ResetHandle ( void )
{
	if ( g_VdInfo.wVideoStatus & VD_HSYNC_LOCKED && g_bVDColorBurstHandler_LastColorBurstStatus )
	{
		BYTE pe = msDSP_Std_GetPhaseError();
		BYTE nm = msDSP_Std_GetNoiseMag();
		
		if ( pe > 0x60 && nm < 0x20 )
		{
			g_ucPhaseErrorDetectCounter++;

			if ( g_ucPhaseErrorDetectCounter > 5 ) //csrf, increase threshold for resetting FSM
			{
				// printMsg("[Fsm_ResetHandle]");
				// printf("\r\nphase err: %d", pe);
				// printf("\r\nnoise mag: %d", nm);
				g_ucPhaseErrorDetectCounter = 0;
				msVD_FSM_Reset();
			}
		}

		else
		{
			g_ucPhaseErrorDetectCounter = 0;
		}
	}

	else
	{
		g_ucPhaseErrorDetectCounter = 0;
	}
}

void msVDForceSystem ( BYTE ucSystem )
{
	g_ucMSVDForceSystem = ucSystem;
}

#if( ENABLE_HSYNC_HANDLER == 1)
void msVDHSyncHandlerReset ( void )
{
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

	msWriteBit ( BK2_4E_BK_WINDOW1, 0, _BIT7 ); // Use defalut Back-Porch window center position

	msWriteByte ( BK0_00_REGBK, ucBank );
}
void msVDHSyncHandler ( void )
{
	BYTE ucBank;

	if ( g_ucVDHSyncHandler_Timer )
	{
		return;
	}

	g_ucVDHSyncHandler_Timer = 0xFF;

	ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

	if ( ( g_VdInfo.ucVideoSystem == SIG_NTSC ) && ( msVDDSPReadByte ( DSP_3A ) > 85 ) )
	{
		if ( ! ( msReadByte ( BK2_4E_BK_WINDOW1 ) &_BIT7 ) )
		{
			msWriteBit ( BK2_4E_BK_WINDOW1, 1, _BIT7 );
			msWriteByte ( BK2_4F_BK_WINDOW2, 0x76 ); // Right shift Back-Porch window center position
		}
	}

	else
	{
		if ( ( msReadByte ( BK2_4E_BK_WINDOW1 ) &_BIT7 ) )
		{
			msWriteBit ( BK2_4E_BK_WINDOW1, 0, _BIT7 ); // Use defalut Back-Porch window center position }
		}
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}
#endif

#if( ENABLE_PAL_SWITCH_HANDLER == 1)

void msVDPalSwitchCtl ( BYTE ucCtl )
{
	BYTE ucBank;

	if ( VD_Type == MARIA2_B )
	{
		return;
	}

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );

	if ( ucCtl == PAL_SWITCH_AUTO )
	{
		msWriteByteMask ( BK2_21_APLL_CTRL2, 0x00, 0x06 ); // Auto detect PAL/NTSC
	}

	else if ( ucCtl == PAL_SWITCH_FORCE_PAL )
	{
		msWriteByteMask ( BK2_21_APLL_CTRL2, 0x06, 0x06 ); // Force PAL
	}

	else if ( ucCtl == PAL_SWITCH_FORCE_NTSC )
	{
		msWriteByteMask ( BK2_21_APLL_CTRL2, 0x04, 0x06 ); // Force NTSC
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msVDPalSwitchHandlerReset ( BYTE ucCtl )
{
	msVDPalSwitchCtl ( ucCtl );
	g_ucPalSwitchHandler_Timer = 250;
}

void msVDPalSwitchHandler ( void )
{
	BYTE ucPalSwitchForceCtl = PAL_SWITCH_AUTO;
	WORD wStatus;
	WORD wVDModeDetectMask = ( VD_HSYNC_LOCKED | VD_VSYNC_50HZ | VD_FSC_TYPE | VD_RESET_ON );

	if ( g_ucPalSwitchHandler_Timer )
	{
		return;
	}

	g_ucPalSwitchHandler_Timer = 100;

	if ( ( g_VdInfo.ucVideoSystem == SIG_PAL_60 )
		|| ( g_VdInfo.ucVideoSystem == SIG_NTSC_443 )
	)
	{
		wVDModeDetectMask |= VD_PAL_SWITCH;
	}

	wStatus = msVDGetSyncStatus();

	if ( ( wStatus & VD_HSYNC_LOCKED ) // Has signal
		&& ( ( wStatus & wVDModeDetectMask ) == ( g_VdInfo.wVideoStatus & wVDModeDetectMask ) )
		&& ( msDSP_Std_GetNoiseMag() > 0x10 ) // Noisy signal
	)
	{
		switch ( g_VdInfo.ucVideoSystem )
		{
		case SIG_PAL:
		case SIG_PAL_NC:

			#if( ENABLE_SW_DETECT_COLOR_STD == 1)
		case SIG_PAL_M:
		case SIG_PAL_60:
			if ( VD_Type >= MARIA2_E )
			#endif
				ucPalSwitchForceCtl = PAL_SWITCH_FORCE_PAL;

			break;

			#if( ENABLE_SW_DETECT_COLOR_STD == 1)

		case SIG_NTSC:
		case SIG_NTSC_443:
		default:
			if ( VD_Type >= MARIA2_E )
			{
				ucPalSwitchForceCtl = PAL_SWITCH_FORCE_NTSC;
			}

			break;
			#endif

		}

		msVDPalSwitchCtl ( ucPalSwitchForceCtl );
	}

	else // No sync or Sync unstable or clean signal
	{
		msVDPalSwitchCtl ( PAL_SWITCH_FORCE_NTSC );
		g_ucPalSwitchHandler_Timer = 255;
	}
}

#endif

typedef enum _DplSel
{
	DPL_SEL_FAST,
	DPL_SEL_NORMAL,
	DPL_SEL_NORMAL2,
	DPL_SEL_NOISY,
	DPL_SEL_VCR,
	DPL_SEL_SYNC_50,
	DPL_SEL_SYNC_20,
	DPL_SEL_NO_COLOR,
	DPL_SEL_NUMS
} EnuDplSel;

code BYTE tDplCoef[DPL_SEL_NUMS][2] =
{
	// K1 K2
	{ 0x30, 0x65 }, // DPL_SEL_FAST,
	{ 0x2B, 0x40 }, // DPL_SEL_NORMAL,
	{ 0x2B, 0x40 }, // DPL_SEL_NORMAL2, noise > 0x10
	{ 0x2B, 0x40 }, // DPL_SEL_NOISY,
	{ 0x34, 0x2C }, // DPL_SEL_VCR,
	{ 0x1A, 0x35 }, // DPL_SEL_SYNC_50,
	{ 0x10, 0x10 }, // DPL_SEL_SYNC_20
	{ 0x01, 0x02 }, // DPL_SEL_NO_COLOR
};

void msVDAFECHandler ( void )
{
	BYTE ucBank;
	BYTE ucDplSel = DPL_SEL_NORMAL;

	// if( g_ucAFECHnadler_Timer )
	// return;
	// g_ucAFECHnadler_Timer = 50;

	if ( VD_AGC_GetSyncMag() < 130 ) // 50%
	{
		if ( VD_AGC_GetSyncMag() < 50 ) // 20%
		{
			ucDplSel = DPL_SEL_SYNC_20;
		}

		else
		{
			ucDplSel = DPL_SEL_SYNC_50;
		}
	}

	else
	{
		WORD wCurSyncStatus = msVDGetSyncStatus();

		if ( ( wCurSyncStatus & VD_MODE_DETECT_MASK ) != ( g_VdInfo.wVideoStatus & VD_MODE_DETECT_MASK ) ) // Sync change
		{
			ucDplSel = DPL_SEL_FAST;
		}

		else if ( bNoisy_Det )
		{
			ucDplSel = DPL_SEL_NOISY;
		}

		else
		{
			if ( g_ucAFECHnadler_LaseDplSel == DPL_SEL_NORMAL2 )
			{
				if ( msDSP_Std_GetNoiseMag() < 0x0D )
				{
					ucDplSel = DPL_SEL_NORMAL;
				}
			}

			else
			{
				if ( msDSP_Std_GetNoiseMag() >= 0x10 )
				{
					ucDplSel = DPL_SEL_NORMAL2;
				}

				else
				{
					ucDplSel = DPL_SEL_NORMAL;
				}
			}
		}
	}
	
	ucBank = msReadByte ( BK0_00_REGBK );
	
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	msWriteByte ( BK2_A0_DPL_K1_FORCE, tDplCoef[ucDplSel][0] | _BIT7 );
	msWriteByte ( BK2_A1_DPL_K2_FORCE, tDplCoef[ucDplSel][1] );

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msVideoAGCHandle ( void )
{
	#if ( RM_EEPROM_TYPE < RM_TYPE_SST512 )
	BYTE TempAGCValue;
	BYTE TempNoiseValue = msDSP_Std_GetNoiseMag();

	if ( TempNoiseValue >= 10 )
	{
		return;
	}

	TempAGCValue = ( VD_AGC_GetCurGain() >> 8 );

	if ( TempAGCValue == g_VideoSetting.videoAGC )
	{
		g_ucLastVideoAGC = g_VideoSetting.videoAGC;
		g_ucVideoAGCCount = 0;
	}

	else
	{
		if ( TempAGCValue == g_ucLastVideoAGC )
		{
			g_ucVideoAGCCount++;
		}

		else
		{
			g_ucLastVideoAGC = TempAGCValue;
			g_ucVideoAGCCount = 0;
		}
	}

	if ( g_ucVideoAGCCount > 50 )
	{
		g_ucVideoAGCCount = 0;

		if ( ( TempAGCValue >= 5 ) && ( TempAGCValue <= 12 ) )
		{
			g_VideoSetting.videoAGC = TempAGCValue;
			SaveVideoSetting();
		}
	}

	#endif
}

#if( ENABLE_SW_DETECT_COLOR_STD == 1)
// used to auto-detect incoming color (burst) standard

void msVDDetectColorStdInit ( void )
{
	g_ucVD_ColorStd = DSP_COLOR_UNKNOWN;
	g_ucVD_ColorStdNew = DSP_COLOR_UNKNOWN;
	g_ucVD_ColorStdChangeCounter = 0;
	g_ucVD_ColorStdCounter = 0;
	g_ucVD_ColorStdCounter_Unknown = 0;
	g_ucVD_ColorStdCounter_Ntsc = 0;
	g_ucVD_ColorStdCounter_Pal = 0;
}

void msVDDetectColorStd ( void )
{
	BYTE ucBank = msReadByte ( BK0_00_REGBK );
	BYTE ucBackupBK2_04;
	BYTE ucBurstPhaseDiff;


	if ( msDSP_Std_GetBurstMag() < 0x18 )
	{
		return;
	}

	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	ucBackupBK2_04 = msReadByte ( BK2_04 );

	msWriteByte ( BK2_04, 0x23 );
	ucBurstPhaseDiff = msReadByte ( BK2_01 );

	g_ucVD_ColorStdCounter ++;

	if ( ( ucBurstPhaseDiff < 32 ) || ( ucBurstPhaseDiff > 0xDF ) )
	{
		g_ucVD_ColorStdCounter_Ntsc ++;
	}

	else if ( ( ucBurstPhaseDiff < 0x60 ) || ( ucBurstPhaseDiff > 0x9F ) )
	{
		g_ucVD_ColorStdCounter_Pal ++;
	}

	else
	{
		g_ucVD_ColorStdCounter_Unknown ++;
	}

	if ( g_ucVD_ColorStdCounter >= COLOR_STD_COUNT_MAX )
	{
		g_ucVD_ColorStdCounter = 0;
		g_ucVD_ColorStdNew = g_ucVD_ColorStd;

		if ( ( g_ucVD_ColorStdCounter_Unknown > g_ucVD_ColorStdCounter_Ntsc ) && ( g_ucVD_ColorStdCounter_Unknown > g_ucVD_ColorStdCounter_Pal ) )
		{
			g_ucVD_ColorStdNew = DSP_COLOR_UNKNOWN;
		}

		else
		{
			if ( g_ucVD_ColorStdCounter_Ntsc > ( COLOR_STD_COUNT_MAX / 2 + 1 ) )
			{
				g_ucVD_ColorStdNew = DSP_COLOR_NTSC;
			}

			else if ( g_ucVD_ColorStdCounter_Pal > ( COLOR_STD_COUNT_MAX / 2 + 1 ) )
			{
				g_ucVD_ColorStdNew = DSP_COLOR_PAL;
			}
		}

		// if( g_dspDebugInfoIdx < 0x40 )
		// {
		// g_dspDebugInfo[g_dspDebugInfoIdx+0] = g_ucVD_ColorStd;
		// g_dspDebugInfo[g_dspDebugInfoIdx+1] = g_ucVD_ColorStdCounter_Ntsc;
		// g_dspDebugInfo[g_dspDebugInfoIdx+2] = g_ucVD_ColorStdCounter_Pal;
		// g_dspDebugInfo[g_dspDebugInfoIdx+3] = g_ucVD_ColorStdCounter_Unknown;
		// g_dspDebugInfo[g_dspDebugInfoIdx+4] = g_ucVD_ColorStdNew;
		// g_dspDebugInfoIdx += 8;
		// }

		if ( g_ucVD_ColorStdNew != g_ucVD_ColorStd )
		{
			g_ucVD_ColorStdChangeCounter ++;

			if ( g_ucVD_ColorStdChangeCounter > 2 )
			{
				g_ucVD_ColorStdChangeCounter = 0;
				g_ucVD_ColorStd = g_ucVD_ColorStdNew;
			}
		}

		else
		{
			g_ucVD_ColorStdChangeCounter = 0;
		}

		#if( ENABLE_DEBUG_SW_DETECT_COLOR_STD )
		g_ucVD_ColorStdCounterL_Unknown = g_ucVD_ColorStdCounter_Unknown;
		g_ucVD_ColorStdCounterL_Ntsc = g_ucVD_ColorStdCounter_Ntsc;
		g_ucVD_ColorStdCounterL_Pal = g_ucVD_ColorStdCounter_Pal;
		#endif
		g_ucVD_ColorStdCounter_Unknown = 0;
		g_ucVD_ColorStdCounter_Ntsc = 0;
		g_ucVD_ColorStdCounter_Pal = 0;
	}

	msWriteByte ( BK2_04, ucBackupBK2_04 );
	msWriteByte ( BK0_00_REGBK, ucBank );
}
#endif
