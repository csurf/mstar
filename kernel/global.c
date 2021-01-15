//----------------------------------------------------
#define EnableColorMatrix

#define _GLOBAL_C_

#include "types.h"
#include "board.h"
#include "global.h"
#include "msACE.h"
#include "panel.h"
#include "menu.h"
#include "keypad.h"
#include "msOSD.h"
#include "menuStr.h"
#include "keypad.h"
#include "nvram.h"
#include "debug.h"
#include "menuFunc.h"
#include "power.h"
#include "mstar.h"

#ifdef EnableColorMatrix
void CopymatrixArray ( void )
{
	BYTE ucRow, ucCol;

	for ( ucRow = 0; ucRow != 3; ucRow++ )
	{
		for ( ucCol = 0; ucCol != 3; ucCol++ )
		{
			tColorCorrectionMatrix[ucRow][ucCol] = tVideoColorCorrectionMatrix[ucRow][ucCol];
		}
	}
}
#endif

void Init_GlobalVariables ( void )
{
	g_ucOsdCounter = 0;
	g_ucModeDetectCounter = 10;
	g_ucOsdCounter = 0;
	g_ucPowerDownCounter = 0;
	g_ucInputTimingStableCounter = 0;
	g_ucTimingChangeDebounce = 0;
	g_ucSaveIndex = 0; // g_ucSaveIndex
	g_ucUratProgramCount = 0;
	g_ucCaptionPosition = 0;
	g_ucSwapLeftSerNum = 0;
	g_ucCopyLeftSerNum = 0;
	g_uwSleepTimeCounter = 0;

	g_bForceColorEnable = 0;

	g_bDebugProgStopFlag = 0;

	g_ucSyncMaxStableCounter = 150;

	g_ucTimeHour = 0;
	g_ucTimeMinute = 0;
	g_ucONTimeHour = 0;
	g_ucONTimeMinute = 0;
	g_ucOFFTimeHour = 0;
	g_ucOFFTimeMinute = 0;

	b_TurnOnPanelFlagbit = 0;

	#if ( SYSTEM_BOOT_UP_QUICKLY_ENABLE == 1 )
	g_bOSDLoadFlag = 1;
	#endif

	Clr_InputTimingChangeFlag();
	Clr_PowerSavingFlag();
	Clr_ForcePowerSavingFlag();
	Clr_InputTimingStableFlag();
	Clr_DoModeSettingFlag();
	Clr_FreeRunModeFlag();
	Clr_OsdTimeoutFlag();
	Clr_SaveSettingFlag();
	Clr_RxBusyFlag();

	Clr_DynamiccaptionFlag();
	Clr_AFCDisableFlag();

	Clr_ShowSourceFlag();
	Clr_ReDrawCurrentOSDFlag();

	Clr_SourceChangedFlag(); //junjian 061205 for SECAM to NTSC

	g_ucTimerFlag = 0;

	g_bTVAutoScanChannelEnable = FALSE;
	g_bTVManualSearchEnable = FALSE;
	g_bTVAutoScanChannelBreak = FALSE;
	g_bTVManualStore = FALSE;
	g_bTVManualScanChannelBreak = FALSE;

	g_ucmSCounter = T100MsTick; // for System timer
	g_uc100mSCounter = SystemTick;
	g_ucSecond = 0;
	g_b100mSArrival = 0;

	g_bFlashReadOK = 0;

	g_ucMenuPageIndex = 0;
	g_ucMenuItemIndex = 0;

	ucUartCheckTick = 0;

	SrcFlags = SyncLoss;

	Key_KeyInit();

	// msACE libary initial
	InitACEVar();
	
	#ifdef EnableColorMatrix
	CopymatrixArray();
	#endif

}


void FlagCheckHandler ( void )
{
	MenuStatusCHK();

	// if(ReDrawCurrentOSDFlag) // for time set
	// {
	// ExecuteKeyEvent(MIA_RedrawMenu);
	// g_ucCaptionPosition=1;
	// Clr_DynamiccaptionFlag();
	// Clr_ReDrawCurrentOSDFlag();
	// }

	// if(ShowSourceFlag)
	// {
	// DrawShowSourcemenu();
	// Clr_ShowSourceFlag();
	// }
}


void SlowTimeHandler ( void )
{
	BOOL TOneMinArrival = FALSE;

	if ( g_b100mSArrival )
	{
		g_b100mSArrival = 0;

		msVDCombHandler();
		//Fsm_ResetHandle();
		msVideoAGCHandle();

		FlagCheckHandler();
		//-----100ms tick end---------------

		if ( -- ( g_uc100mSCounter ) == 0 )
		{
			//one second tick
			g_ucSecond++;
			g_uc100mSCounter = SystemTick;

			if ( ucUartCheckTick )
				if ( ( --ucUartCheckTick ) == 0 )
				{
					g_UartCommand.Index = 0;
				}

			if ( g_ucSecond == 60 )
			{
				g_ucSecond = 0;
				TOneMinArrival = TRUE;
			}

			if ( g_ucOsdCounter )
			{
				if ( --g_ucOsdCounter == 0 )
				{
					Set_OsdTimeoutFlag();
				}
			}
		}

		if ( g_ucPowerDownCounter )
			if ( --g_ucPowerDownCounter == 0 )
			{
				Set_ForcePowerSavingFlag();
			}
	}
}
