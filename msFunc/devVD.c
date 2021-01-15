#define _DEVVD_C_

#include <MATH.H>
#include "types.h"
#include "ms_reg.h"
#include "board.h"
#include "global.h"
#include "debug.h"
#include "ms_rwreg.h"
#include "misc.h"
#include "userPref.h"
#include "power.h"
#include "panel.h"
#include "mstar.h"
#include "devVD.h"
#include "msVD.h"
#include "adjust.h"
#include "devVD_User.h"
#include "menu.h"
#include "menuFunc.h"
#include "maria2_FSC.h"
#include "maria2_ACC.h"
#include "m2_VD_STD.h"
#include "m9_VD_AGC.h"

#if(ENABLE_VD_DSP)
	#include "maria2_DSP.h"
#endif

XDATA BYTE g_ucDetectInterlace_StableCounter;

// for 'no signal' color-fill screen
BYTE code tFreeRunColor[][2] =
{
	// BK0_5C, BK0_5D
	{ 0x00, 0x00, }, // FREE_RUN_COLOR_BLACK
	{ 0xFE | _BIT0, 0xFF, }, // FREE_RUN_COLOR_WHITE
	{ 0x3E | _BIT0, 0x00, }, // FREE_RUN_COLOR_BLUE
};

void vdInitVariable ( void )
{
	g_ucmsVDCtl = 0
		| MSVD_CTL_FLAG_DSP_STD
		| MSVD_CTL_FLAG_FSC_DETECT
		| MSVD_CTL_FLAG_ACC
		| MSVD_CTL_FLAG_COLOR_BURST_HANDLER
		| MSVD_CTL_FLAG_NOISE_HANDLER
		| MSVD_CTL_FLAG_COMB_LINE_BUF
		| MSVD_CTL_FLAG_VSYNC
		| MSVD_CTL_FLAG_COMB_HANDLER
		;

	g_ucmsVDCtl2 = 0
		| MSVD_CTL2_FLAG_AGC_MONITOR
		| MSVD_CTL2_FLAG_AGC_PROCESSOR
		| MSVD_CTL2_FLAG_HSYNC
		| MSVD_CTL2_FLAG_PATCH5
		| MSVD_CTL2_FLAG_PAL_SWITCH
		| MSVD_CTL2_FLAG_AFEC
		;

	g_ucMSVDDebug = 0;
	g_ucMSVDDebug2 = 0;

	g_VdInfo.wVideoStatus = VD_RESET_ON;
	g_VdInfo.ucVideoSystem = SIG_NONE;
	g_VdInfo.ucVideoStableCounter = 0;
	g_VdInfo.ucVideoPollingCounter = 0;
	g_VdInfo.bVideoDoModeSetting = FALSE;

	#ifdef VD_PATCH_002
	g_msVD_Patch002_LastVideoSystem = 0xFF;
	#endif

	#ifdef VD_PATCH_003

	if ( VD_Type < MARIA2_E )
	{
		msVD_Patch_003 ( 0 );
	}

	#endif

	#ifdef VD_PATCH_005
	msVD_Patch_005 ( 100 );
	#endif

	#if ENABLE_VD_DSP
	VD_Vsync_Set656VPosition ( DSP_656_F_TGL_1_VAL, 0x09, DSP_656_V_CLR_1_VAL );
	#endif
	
	msDSP_Std_Init();
	msVD_FSC_Init();

	msVD_FSC_SetNoiseModeLevel ( 12, 13 );
	msVD_FSC_SetColorKillNoise ( 0xC0, 0xD0 ); //0xE0, 0xF0);
	//msVD_FSC_SetColorKillBurst( BYTE ucBurstOn, BYTE ucBurstOff );
	
	#if 0//(SCALER_TYPE==MARIA9)
	msVD_FSC_SetColorKillLevel ( 0x12, 0x10, 0x80, 0x90 );
	#else
	msVD_FSC_SetColorKillLevel ( 0x23, 0x18, 0x50, 0x60 );
	#endif

	msVDAcc_Ctl ( 0 );
	msVDAcc_Init();

	#if RM_EEPROM_TYPE < RM_TYPE_SST512
	g_uwVideoAGC = ( WORD ) ( g_VideoSetting.videoAGC << 8 );
	g_ucLastVideoAGC = g_VideoSetting.videoAGC;
	g_ucVideoAGCCount = 0;
	#else
	g_uwVideoAGC = 0x0800;
	#endif

	VD_AGC_Init();

	#if ( SCALER_TYPE != MARIA9 )
	VD_AGC_SetStartGain ( g_uwVideoAGC );
	VD_AGC_SetNoSyncGain ( g_uwVideoAGC );
	VD_AGC_SetMaxGain ( 0x2f00 );
	#endif

	#if ENABLE_VD_DSP
	// for dsp 20060311 only, not mature yet
	SetVthreshold ( 0x20 );
	#endif
	
	msVDForceSystem ( VD_FORCE_AUTO );

	msVDNoiseHandlerInit();
	g_ucOverScanH = VD_OVER_SCAN_H;
	g_ucOverScanV = VD_OVER_SCAN_V;
	g_ucAFECHnadler_LaseDplSel = 0xff;

	#if( ENABLE_SW_DETECT_COLOR_STD )

	if ( VD_Type >= MARIA2_E )
	{
		msVDDetectColorStdInit();
	}

	#endif

	#if ( SCALER_TYPE == MARIA9 )//Fix Gain
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	msWriteByte ( BK2_43_AGC_CTRL1, 0x14/*0x74*/ );
	msWriteByte ( BK2_44_AGC_FINE, 0x40/*0x90*/ );
	msWriteBit ( BK2_3F, 1, _BIT3 );
	msWriteBit ( BK2_10, 1, _BIT2 );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	#endif

}

void vdMonitorInput ( void )
{
	WORD wCurSyncStatus; // video status
	BYTE ucStableCounter;
	BYTE ucNoiseMag;

	// msDSP_Std_GetBurstMag();

	if ( !PowerOnFlag )
	{
		return;
	}

	if ( g_VdInfo.ucVideoPollingCounter )
	{
		return;
	}

	g_VdInfo.ucVideoPollingCounter = 20; // reset counter

	// csrf
	// reset causing window change
	if ( g_bInputTimingChangeFlag )
	{
		g_VdInfo.wVideoStatus = VD_RESET_ON;
		Clr_InputTimingChangeFlag();
	}

	wCurSyncStatus = msVDGetSyncStatus();
	//printf("\r\nwCurSyncStatus: 0x%x", wCurSyncStatus);
	
	if ( ( wCurSyncStatus & VD_MODE_DETECT_MASK ) != ( g_VdInfo.wVideoStatus & VD_MODE_DETECT_MASK ) ) // Sync change
	{
		//ucNoiseMag = msVDGetCurNoiseMag();
		ucNoiseMag = msDSP_Std_GetNoiseMag();

		// csrf
		// we need to fix/disable
		if (0 && !SourceChangedFlag )
		{
			//if( (wCurSyncStatus&(VD_FSC_TYPE|VD_PAL_SWITCH|VD_VSYNC_50HZ))
			// != (g_VdInfo.wVideoStatus&(VD_FSC_TYPE|VD_PAL_SWITCH|VD_VSYNC_50HZ)) )

			if ( ( ( ( wCurSyncStatus & ( VD_FSC_TYPE | VD_PAL_SWITCH ) ) != ( g_VdInfo.wVideoStatus & ( VD_FSC_TYPE | VD_PAL_SWITCH ) ) ) && ( ucNoiseMag < 0x50 ) )
				|| ( ( wCurSyncStatus & ( VD_VSYNC_50HZ ) ) != ( g_VdInfo.wVideoStatus & ( VD_VSYNC_50HZ ) ) )
				|| ( ( wCurSyncStatus & ( VD_HSYNC_LOCKED ) ) != ( g_VdInfo.wVideoStatus & ( VD_HSYNC_LOCKED ) ) )
			)
			{
				//msSetBlueScreen( _ENABLE, FR_BLACK); // setup freerun mode
				g_VdInfo.wVideoStatus |= VD_RESET_ON;

				if ( ! ( wCurSyncStatus & VD_HSYNC_LOCKED ) )
				{
					printMsg("[vdMonitorInput]");
					msVDReset();
				}
			}
		}

		if ( ( wCurSyncStatus & VD_MODE_DETECT_MASK ) == ( g_wLastSyncStatus & VD_MODE_DETECT_MASK ) )
		{
			if ( g_VdInfo.ucVideoStableCounter < 0xFF )
			{
				g_VdInfo.ucVideoStableCounter ++;
			}

			if ( ! ( wCurSyncStatus & VD_HSYNC_LOCKED ) )
			{
				ucStableCounter = VD_NO_INPUT_STABLE_COUNT;
			}

			else
			{
				ucStableCounter = VD_INPUT_STABLE_COUNT;
			}

			if ( g_VdInfo.ucVideoStableCounter >= ucStableCounter )
			{
				//printf ( "Video Status: %x\r\n", wCurSyncStatus );
				g_VdInfo.wVideoStatus = wCurSyncStatus; // set flag
				g_VdInfo.bVideoDoModeSetting = TRUE; // set mode flag
				
				#if ( SCALER_TYPE != MARIA9 )
				{ // Leng Add For VDReset 20101008
					BYTE ucBank,DSP10_Value;
					
					ucBank = msReadByte( BK0_00_REGBK );
					msWriteByte( BK0_00_REGBK, REG_BANK2_VD );
					DSP10_Value=msVDDSPReadByte( DSP_10);
					if(DSP10_Value!=0x85)
					{	            
						msVDReset();
						Set_InputTimingChangeFlag();
						g_VdInfo.bVideoDoModeSetting = FALSE;
					}
					msWriteByte( BK0_00_REGBK, ucBank );
				}
				#endif
				
				#ifdef VD_PATCH_002

				if ( msVD_Patch_002 ( wCurSyncStatus ) )
				{
					g_VdInfo.wVideoStatus = VD_RESET_ON;
					g_VdInfo.bVideoDoModeSetting = FALSE;
				}

				#endif
			}
		}

		else // Current status != last status
		{
			g_VdInfo.ucVideoStableCounter = 0;
		}
	}

	else // Current status == current global flag
	{
		g_VdInfo.ucVideoStableCounter = 0;
	}

	if ( g_ucSyncMaxStableCounter )
	{
		if ( ( --g_ucSyncMaxStableCounter ) == 0 )
		{
			printMsg ( "force turn on panel" );
			g_VdInfo.bVideoDoModeSetting = TRUE;
			//g_VdInfo.wVideoStatus|=~VD_HSYNC_LOCKED;
			g_VdInfo.ucVideoStableCounter = 0;
		}
	}

	// Current status == system status
	if ( ( wCurSyncStatus & VD_MODE_DETECT_MASK ) == ( g_VdInfo.wVideoStatus & VD_MODE_DETECT_MASK ) )
	{
		// Polling input and doing something
		if ( wCurSyncStatus & VD_HSYNC_LOCKED ) //&& IsSrcHasSignal())
		{
			msDetectInterlace ( 0 ); // Normal polling interlace

			#if( ENABLE_MONITOR_SIGNAL )
			msMonitorSignal ( 0 ); // Normal monitor input signal
			#endif
		}

		// Patch ...
		// if( IsSrcUseInternalVD() ) // Status stable
		{
			#ifdef VD_PATCH_003

			if ( VD_Type < MARIA2_E )
			{
				if ( g_VdInfo.ucVideoSystem == SIG_NTSC )
				{
					msVD_Patch_003 ( 1 );
				}

				else
				{
					msVD_Patch_003 ( 0 );
				}
			}

			#endif

			#ifdef VD_PATCH_004

			if ( wCurSyncStatus & VD_HSYNC_LOCKED ) // && IsSrcHasSignal())
			{
				msVD_Patch_004 ( _ENABLE );
			}

			else
			{
				msVD_Patch_004 ( _DISABLE );
			}

			#endif
		}
	}

	// Save current status for next mode detect
	g_wLastSyncStatus = wCurSyncStatus;
}

void vdModeHandler(void)
{
	//WORD val = msDSP_Std_GetBurstMag();
	
	if( g_VdInfo.bVideoDoModeSetting )
	{
		WORD wTemp;
		WORD wStatus = g_VdInfo.wVideoStatus;

		g_bForceColorEnable=FALSE;
		g_VdInfo.bVideoDoModeSetting = FALSE;
		Clr_SourceChangedFlag();

		printMsg("[vdModeHandler]");

		// Check signal type
		if( g_VideoSetting.VideoColorSys == CHROMA_NTSC )
		{
			g_VdInfo.ucVideoSystem = SIG_NTSC;
			g_ucSrcModeIndex = MD_720x480_60I;
		}else
		{
			g_VdInfo.ucVideoSystem = SIG_PAL;
			g_ucSrcModeIndex = MD_720x576_50I;
		}
		g_InOutCtl.bInterlace = 1;
		
		if( wStatus & VD_HSYNC_LOCKED ) // Has signal
		{
			msSetUserPref();  // Leng Add 20110513 For NTSC VideoHue Setup

			wTemp = wStatus;
			
			//g_InOutCtl.bInterlace = 1;
			
			//g_VdInfo.ucVideoSystem = msVDGetVideoSystem( wStatus );
			//msVD_FSM_Reset();
			
			//msSetBlueScreen( _DISABLE, FR_BLACK);
			//msForceChromaDetect(g_VdInfo.ucVideoSystem);
			
			#if( ENABLE_MONITOR_SIGNAL )
			msMonitorSignal(MONITOR_SIGNAL_INIT);
			#endif
		}
		else // No signal
		{
			printMsg("-no sync");
			
			//g_VdInfo.ucVideoSystem = SIG_NONE;
			//g_ucSrcModeIndex = MD_TVsnow;
			// g_InOutCtl.bInterlace = 1;
			g_bForceColorEnable = 0;

			if(g_VideoSetting.VideoColorSys == CHROMA_NTSC)
				wTemp = VD_FSC_3579;
			else
				wTemp = VD_FSC_4433 | VD_VSYNC_50HZ;

			//msVDReset();
			//SetOutputTimingAndWindow( OUTPUT_SNOW );

			#ifdef VD_PATCH_001
			msVD_Patch_001();
			#endif
		}
		
		msVDSetupMode( wTemp, g_VdInfo.ucVideoSystem );
		msCommSetupMode();
		SetOutputTimingAndWindow(OUTPUT_SIG); // VD mode change: Has signal
		msSetScaler();
		
		msSetBlueScreen( _DISABLE, FR_BLACK);
		g_ucSyncMaxStableCounter=0;

		ResetOsdTimer();//for reset source menu

		// if(! g_SignalInitFlag)
		// {
			// msSetBlueScreen( _DISABLE, FR_BLACK);
			// g_SignalInitFlag = 1;
		// }
		
		if (PowerOnFlag)
		{
			Power_TurnOnPanel();
		}
	}
}

void msForceFSC( BYTE ucVidType)
{
	BYTE ucBank;
	BYTE val = 0x80; // 000: 4.43361875MHz => PAL
	
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK2_VD );
	
	if (ucVidType == SIG_NTSC)
	{
		val = 0xA0; // 010: 3.579545MHz => NTSC
	}
	printf("\r\n[ForceFSC] %d",val);
	
	msWriteByteMask( BK2_2A_MODE_PFSC, ( val ), 0xF0);
	msWriteByteMask ( BK2_55_COLOR_OFF, 0x00, 0xC0 ); //force auto color kill
	
	msWriteByte ( BK0_00_REGBK, ucBank );
}

BOOL msForceChromaDetect ( BYTE ucSignalType )
{
	BYTE uctempcolorsys;
	BOOL btempcolorforce = TRUE;

	uctempcolorsys = g_VideoSetting.VideoColorSys;

	switch ( ucSignalType )
	{
	case SIG_PAL:
		if ( uctempcolorsys == CHROMA_PAL )
		{
			btempcolorforce = FALSE;
		}

		break;

	case SIG_NTSC:
	default:
		if ( uctempcolorsys == CHROMA_NTSC )
		{
			btempcolorforce = FALSE;
		}

		break;
	}

	g_bForceColorEnable = btempcolorforce;

	// csrf:
	// we use auto color detect
	// so these calls are disabled
	if ( btempcolorforce )
	{
		msVDColorKill ( TRUE );
	}

	else
	{
		msVDColorKill ( FALSE );
	}

	return btempcolorforce;
}

void msDetectInterlace ( BYTE ucFlag )
{
	bit bInterlace;

	BYTE ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	// Read scaler report status
	bInterlace = msGetInterlaceBit();

	if ( bInterlace != g_bDetectInterlace_LastInterlaceFlag )
	{
		g_ucDetectInterlace_StableCounter++;
	}

	else
	{
		g_ucDetectInterlace_StableCounter = 0;
	}

	if ( ( ucFlag & _BIT0 ) || ( g_ucDetectInterlace_StableCounter > 20 ) )
	{
		g_ucDetectInterlace_StableCounter = 0;
		g_bDetectInterlace_LastInterlaceFlag = bInterlace;

		if ( bInterlace )
		{
			msWriteBit ( BK0_0E_INTLX, 1, _BIT3 ); // to be checked!!
			msWriteByteMask ( BK0_36_VDSUSG, 0x0C, 0x0C );
			putstr ( "\r\nInterlace" );
		}

		else // Non-interlace
		{
			msWriteBit ( BK0_0E_INTLX, 0, _BIT3 );
			msWriteByteMask ( BK0_36_VDSUSG, 0x00, 0x0C );
			putstr ( "\r\nNon-Interlace" );
		}

		msLineBufferDelayCtl ( bInterlace ); // For detect interlace
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

BOOL msGetInterlaceBit ( void )
{
	BOOL bInterlace = 0;
	BYTE ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	if ( msReadByte ( BK0_EF_STATUS2 ) &_BIT3 )
	{
		bInterlace = 1;
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
	return bInterlace;
}

void msFieldDetectCtl ( void )
{
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	
	msWriteByte ( BK0_E4_ISOVRD, 0x03 ); // force interlaced input

	#if (ENABLE_VD_DSP)
	msWriteByte ( BK0_E5_MDCTRL, 0x04 ); // 20051114
	#elif(ENABLE_SW_FIELD)
	msWriteByte ( BK0_E5_MDCTRL, 0x04 ); // 20060116
	#else
	msWriteByte ( BK0_E5_MDCTRL, 0x00 );
	#endif

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msLPFCtl ( BYTE ucLPFParaIdx )
{
	BYTE ucBank;
	BYTE code tLPFPara[][5] =
	{
		{ 0x7E, 0x04, 0x3C, 0x04, 0x1C }, // VD 358
		{ 0x7F, 0x03, 0x3C, 0x05, 0x1A }, // VD 443
		{ 0x42, 0x01, 0x3C, 0x07, 0x14 }, // TV, Strong
		{ 0x3F, 0x03, 0x3C, 0x05, 0x1A }, // TV, Normal
		{ 0x7F, 0x04, 0x3C, 0x04, 0x1A }, // AV
	};

	BYTE i;

	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, 1 );

	if ( ucLPFParaIdx == LPF_CTL_TURN_OFF )
	{
		msWriteBit ( BK1_55_LPF_CTL, 0, _BIT6 );
	}

	else
	{
		for ( i = 0; i < 5; ++ i )
		{
			msWriteByte ( BK1_50_LPF_TAP1 + i, tLPFPara[ucLPFParaIdx][i] );
		}

		if ( ucLPFParaIdx == LPF_CTL_TV_STRONG )
		{
			msWriteBit ( BK1_55_LPF_CTL, 1, _BIT6 );
		}

		else
		{
			msWriteBit ( BK1_55_LPF_CTL, 0, _BIT6 );
		}
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msSetBlueScreen ( BOOL bEnable, BYTE ucColor )
{
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	if ( bEnable )
	{
		//msFPLLCtl( FPLL_STOP );
		msWriteBit ( BK0_02_ISELECT, _ENABLE, _BIT7 );
		msSetupFreeRunMode ( DEFAULT_OUTPUT_V_FREQ );

		// Set screen color
		msWriteByte ( BK0_5C_FRAME_COLOR_1, tFreeRunColor[ucColor][0] );
		msWriteByte ( BK0_5D_FRAME_COLOR_2, tFreeRunColor[ucColor][1] );
	}
	else // Disable blue screen
	{
		msWriteBit ( BK0_02_ISELECT, _DISABLE, _BIT7 ); // Disable freerun
	}

	#if (SCALER_TYPE == MARIA9)
	msADCSelfMismatchCal_CVBS_SVIDEO_Y();
	#endif
	
	msWriteByte ( BK0_00_REGBK, ucBank );
}

#if( ENABLE_MONITOR_SIGNAL )
XDATA BYTE g_ucMonitorSignal_ChangeCounter;
void msMonitorSignal ( BYTE ucFlag )
{
	XDATA WORD wInHP;
	XDATA WORD wInVT;
	XDATA DWORD dwInHF;

	bit bHSyncChange = 0;
	bit bVTotalChange = 0;


	if ( ucFlag & MONITOR_SIGNAL_INIT )
	{
		g_ucMonitorSignal_ChangeCounter = 0;
		return;
	}

	if ( g_wMonitorSignal_Timer )
	{
		return;
	}

	g_wMonitorSignal_Timer = 100;


	wInHP = msGetVideoHPeriod ( 0 );

	if ( wInHP == 0 ) // H invalid
	{
		return;
	}

	dwInHF = MST_CLOCK_HZ / wInHP;

	wInVT = msVDGetVTotal();

	if ( abs ( g_InOutCtl.inHPeriod - wInHP ) >= 20 ) // Nelson Modify 2006-05-15
	{
		bHSyncChange = 1;
		bVTotalChange = 1;
	}

	else if ( ( abs ( g_InOutCtl.inVTotal - wInVT ) >= 50 ) ) // Nelson Modify 2006-05-15
	{
		bVTotalChange = 1;
	}


	if ( bHSyncChange || bVTotalChange )
	{
		++ g_ucMonitorSignal_ChangeCounter;

		if ( g_ucMonitorSignal_ChangeCounter >= 10 )
		{
			g_ucMonitorSignal_ChangeCounter = 0;
		}

		else
		{
			bHSyncChange = 0;
			bVTotalChange = 0;
		}
	}

	else
	{
		g_ucMonitorSignal_ChangeCounter = 0;
	}

	if ( bHSyncChange || bVTotalChange )
	{
		if ( bHSyncChange )
		{
			g_InOutCtl.inHPeriod = wInHP;
			g_InOutCtl.inHFreq = dwInHF;
		}

		g_InOutCtl.inVTotal = wInVT;

		msProgDigitalWin ( OUTPUT_FREERUN );
		SetOutputClock ( OUTPUT_FREERUN );
	}
}
#endif
