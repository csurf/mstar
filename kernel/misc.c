#define _MISC_C_

#include <INTRINS.H>
#include "types.h"
#include "board.h"
#include "global.h"
#include "misc.h"
#include "mcu.h"

void Delay4us ( void )
{
	#if MCU_XTAL_CLK_MHZ>=20
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	#endif
}

void ForceDelay1ms ( WORD msNums )
{
	WORD t;

	if ( msNums > 0 )
	{
		while ( msNums-- )
		{
			t = DELAY_1MS_PERIOD;

			while ( t-- );
		}
	}
}

// delay 1 millisecond.
//
// Arguments: wValue - delay counter
#ifdef DELAY1MS_USE_TIMER0 // Use timer0
void Delay1ms ( WORD wValue )
{
	if ( EA )
	{
		// Use timer0
		if ( wValue <= 1 )
		{
			wValue = 2;
		}

		g_wDelay1msCounter = wValue;

		while ( g_wDelay1msCounter )
		{
		} // while
	}
	else
	{
		WORD wCount; // loop counter

		while ( wValue-- )
		{
			wCount = DELAY_1MS_PERIOD; // reset loop counter

			while ( wCount-- ) ;
		} // while
	}
}
#else
void Delay1ms ( WORD wValue )
{
	WORD wCount; // loop counter

	while ( wValue-- )
	{
		wCount = DELAY_1MS_PERIOD; // reset loop counter
		//wCount = g_ucTestCnt; // reset loop counter

		WatchDogClear();

		while ( wCount-- ) ;
	} // while
}
#endif
