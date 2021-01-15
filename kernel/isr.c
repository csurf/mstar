#include "types.h"
#include "board.h"
#include "global.h"
#include "power.h"
#include "debug.h"

#include "devVD.h"
#include "msVD.h"
#include "mcu.h"
#include "panel.h"
#include "m9_VD_AGC.h"
#include "m2_VD_STD.h"
#include "ms_rwreg.h"
#include "reg52.h"
#include "mstar.h"

#if(ENABLE_VD_DSP)
	#include "maria2_DSP.h"
#endif

#define ReSyncTick 255

void EXT0Interrupt ( void ) interrupt 0
{}
void EXT1Interrupt ( void ) interrupt 2
{}
void Time1Interrupt ( void ) interrupt 3
{}
void isrTimer2_S ( void ) interrupt 5
{}

void Time0Interrupt ( void ) interrupt 1
{
	// Reset timer0
	#if ENABLE_MCU_USE_INTERNAL_CLOCK
	if ( g_bMcuUseNewClock )
	{
		TH0 = HIBYTE ( NEW_ISR_TIMER0_COUNTER );
		TL0 = LOBYTE ( NEW_ISR_TIMER0_COUNTER );
	}

	else
	#endif
	{
		TH0 = HIBYTE ( ISR_TIMER0_COUNTER );
		TL0 = LOBYTE ( ISR_TIMER0_COUNTER );
	}

	// video mode detect counter
	if ( g_VdInfo.ucVideoPollingCounter )
	{
		g_VdInfo.ucVideoPollingCounter--;
	}

	switch ( ( g_ucmSCounter & 0x7 ) )
	{
	case 0:
		#if( ENABLE_VD_DSP && ( DSP_RUN_MODE == DSP_RUN_MODE_TIMER_AND_POLLING ) )
		if( g_ucmsVDCtl & MSVD_CTL_FLAG_VSYNC )
		{
			VD_DSP_Int();
		}
		#endif
		break;

	case 2:
	case 6:
		if( g_ucmsVDCtl & MSVD_CTL_FLAG_DSP_STD ) // For debug
		{
			msDSP_Std_Processor();
		}
		break;

	case 1:
	case 3:
	case 5:
	case 7:
		if ( g_ucmsVDCtl2 & MSVD_CTL2_FLAG_AGC_MONITOR )
		{
			VD_AGC_MonitorStatus();
		}

		// cs ENABLED
		#if( ENABLE_SW_DETECT_COLOR_STD )

		if ( VD_Type >= MARIA2_E )
		{
			msVDDetectColorStd();
		}

		#endif

		break;

	default:
		break;
	}

	// cs ENABLED
	#if( ENABLE_HSYNC_HANDLER )

	if ( g_ucVDHSyncHandler_Timer )
	{
		g_ucVDHSyncHandler_Timer --;
	}

	#endif

	// cs DISABLED
	#if( ENABLE_MONITOR_SIGNAL )

	if ( g_wMonitorSignal_Timer )
	{
		g_wMonitorSignal_Timer --;
	}

	#endif

	// cs DISABLED
	#ifdef VD_PATCH_005

	if ( g_msVD_Patch005_Timer )
	{
		g_msVD_Patch005_Timer --;
	}

	#endif

	// cs ENABLED
	#if( ENABLE_PAL_SWITCH_HANDLER )

	if ( g_ucPalSwitchHandler_Timer )
	{
		g_ucPalSwitchHandler_Timer --;
	}

	#endif

	if ( g_wVDColorBurstHandlerTimer )
	{
		g_wVDColorBurstHandlerTimer --;
	}

	if ( g_ucMSVDNoiseHandlerTimer )
	{
		g_ucMSVDNoiseHandlerTimer --;
	}


	if ( ( --g_ucmSCounter ) == 0 )
	{
		g_b100mSArrival = 1;
		g_ucmSCounter = T100MsTick;
	}

	#if( ENABLE_VSYNC_CTL_AUTO_H_TOTAL)

	if ( g_wCheckBK0_57_Timer )
	{
		g_wCheckBK0_57_Timer --;
	}

	#endif
}

// Uart Interrupt
void uartInterrupt ( void ) interrupt 4
{
	// EA = 0; // disable all interrupt

	#if _DEBUG_EXTDEV_EN_
	if ( !_testbit_ ( TI ) ) // check translate interrupt
	{
		ucUartCheckTick = 2;

		RI = 0; // clear recieve interrupt

		g_UartCommand.Buffer[g_UartCommand.Index] = SBUF; // recieve byte

		// check command buffer index
		if ( UART_EXT )
		{
			if ( g_UartCommand.Index == 0 ) // check 1st data
			{
				g_UartCommand.Index++; // for get UART_CMD_EXT_LENGTH
			}

			else
			{
				if ( g_UartCommand.Index < UART_CMD_EXT_LENGTH ) // still read command
				{
					g_UartCommand.Index++; // next index of command buffer
				}

				if ( g_UartCommand.Index >= UART_CMD_EXT_LENGTH ) // read command ok
				{
					g_bUartDetected = TRUE; // command buffer recieve ok
					g_UartCommand.Index = 0; // reset index of command buffer
					ucUartCheckTick = 0;
				}
			}
		}

		else
		{
			if ( g_UartCommand.Index < UART_CMD_LENGTH ) // still read command
			{
				g_UartCommand.Index++; // next index of command buffer
			}

			if ( g_UartCommand.Index >= UART_CMD_LENGTH ) // read command ok
			{
				g_bUartDetected = TRUE; // command buffer recieve ok
				g_UartCommand.Index = 0; // reset index of command buffer
				ucUartCheckTick = 0;
			}
		}
	} // if TI

	#endif
	// EA = 1; // release EA bit
}
