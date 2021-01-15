#ifndef _MISC_H_
#define _MISC_H_

#ifdef _MISC_C_
	#define _MISCDEC_
#else
	#define _MISCDEC_ extern
#endif
//#define DELAY1MS_USE_TIMER0

#ifdef DELAY1MS_USE_TIMER0
	_MISCDEC_ XDATA WORD g_wDelay1msCounter;
#endif

// Definition
#define DELAY_MACHINE_CYCLE 12

#ifdef SERIAL_FLASH
	#if ENABLE_MCU_USE_INTERNAL_CLOCK
		#if( MCU_CLOCK_DIVIDER == 6 ) // 36MHz
			#define DELAY_1MS_PERIOD (148)
			#elif( MCU_CLOCK_DIVIDER == 8 ) // 27MHz
			#define DELAY_1MS_PERIOD (105)
			#elif( MCU_CLOCK_DIVIDER == 10 ) // 21.6MHz
			#define DELAY_1MS_PERIOD (78)
		#else //if( MCU_CLOCK_DIVIDER == 12 ) // 18MHz
			#define DELAY_1MS_PERIOD (60)
		#endif
	#else
		#define DELAY_1MS_PERIOD (MCU_XTAL_CLK_KHZ / 250)
	#endif
#endif

#ifndef DELAY_1MS_PERIOD
	// This value need fine tune
	#define DELAY_1MS_PERIOD ((MCU_XTAL_CLK_KHZ / MCU_MACHINE_CYCLE) / DELAY_MACHINE_CYCLE)
#endif

_MISCDEC_ void Delay4us ( void );
_MISCDEC_ void Delay1ms ( WORD msNums );
_MISCDEC_ void ForceDelay1ms ( WORD msNums );

#endif
