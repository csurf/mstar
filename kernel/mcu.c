#define _MCU_C_

#include "types.h"
#include "global.h"
#include "board.h"
#include "misc.h"
#include "debug.h"
#include "reg52.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "mcu.h"
#include "panel.h"

void Init_MCU ( void )
{
	EA = 0;
	g_bMcuUseNewClock = 0;

	Init_IOPorts();
	Init_SerialPort();
	Init_Timer();
	Init_ExternalInterrupt();
	
	EA = 1;
}

// Initialize I/O setting
void Init_IOPorts ( void )
{
	PWDT = 0x50;
	PWDT1 = 0xA0;
	WDTCON = 0x00; // disable WDT.

	//600ms
	CKCON = 0x98;

	// P0 = 0x00;
	// P0SEL = 0xF9;
	// P0IO = 0xF9;

	P1SEL = 0xFF;
	P1IO = 0xFF;

	// g_ucP4Value=Init_P4_Value;
	// P4 = g_ucP4Value;

	#ifdef P6_GPIO_Enable
	P6_IO_Ctrl |= 0xF0;
	P6 |= Init_P6_Value;
	#endif

	#ifdef P5_GPIO_Enable
	P5_IO_Ctrl |= 0x0F;
	P5 |= Init_P5_Value;
	#endif

	#if ( MST_CHIP >= MST702 )
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK7_08_CHIPTOP, 0xFF );
	msWriteByte ( BK0_00_REGBK, REG_BANK7_CHIPTOP );
	#endif

	#if Panel_SPI
	hw_SetSPCK();
	hw_SetSPDA();
	hw_ClrSPENB();
	#endif
}

/* initialize 8051 CPU timer & interrupt routine */
/* TCON.7( TF1): Timer 1 overflow flag */
/* TCON.6( TR1): Timer 1 stop/start bit */
/* TCON.5( TF0): Timer 0 overflow flag */
/* TCON.4( TR0): Timer 0 stop/start bit */
/* TCON.3( IE1): Timer 1 INT1 interrupt flag */
/* TCON.2( IT1): Timer 1 INT1 interrupt style setup*/
/* TCON.1( IE0): Timer 0 /INT0 interrupt flag */
/* TCON.0( IT0): Timer 0 /INT0 interrupt style setup */

void Init_ExternalInterrupt ( void )
{
	//INT0 setting
	//for DDC2BI
	IT0 = 0; // set INT0 type(edge triger)
	PX0 = 1; // set INT0 priority high
	EX0 = 1; // enable INT0 interrupt

	//INT1 setting
	IT1 = 1; // set INT1 type(edge triger)

	#if ENABLE_MCU_USE_INTERNAL_CLOCK

	if ( MCU_CLOCK_DIVIDER > 8 )
	{
		PX1 = 1; // set INT1 priority high
	}

	else
	{
		PX1 = 0; // set INT1 priority high
	}

	#else
	PX1 = 1; // set INT1 priority high
	#endif

	EX1 = 1; // enable INT1 interrupt

	//TIMER0 setting
	//McuInitTimer0();

	//Timer1 setting for uart

	//TIMER2 setting
	T2CON = 0x00;
	T2MOD = 0x00;

	EA = 1; // interrupt enable
}

void Init_Timer ( void )
{
	TMOD = ( TMOD & 0xf0 ) | 0x01; // set TIMER0 mode 1
	PT0 = 0; // set TIMER0 priority low
	TR0 = 1; // TIMER0 enable
	ET0 = 1; // enable TIMER0 interrupt
}

/*----------Timer 2 -------------------*/
/* T2CON.7( TF2): overflow flag */
/* T2CON.6( EXF2): extern enable flag */
/* T2CON.5( RCLK): receive clock */
/* T2CON.4( TCLK): transfer clock */
/* T2CON.3( EXEN2): extern enable flag */
/* T2CON.2( TR2): stop/start timer 2 */
/* T2CON.1( C_T2): intern clock(0)/extern counter(1) switch */
/* T2CON.0(CP_RL2): capture flag */

void Init_SerialPort ( void )
{
	// timer1, mode 2, 8-bit auto reload
	TMOD = ( TMOD & 0x0f ) | 0x20; // timer1, mode 2, 8-bit reload

	// Timer1: Uart baudrate generator
	TH1 = TIMER1_MODE2_TH1; // set timer1(buad rate)
	TR1 = 1; // timer1 run

	// UART
	SCON = 0x50; // mode 1, 8-bit UART, enable receive

	if ( _SMOD )
	{
		PCON |= 0x80;
	}

	RI = 0;
	TI = 0; // clear transfer flag

	PS = 0; // set uart priority low
	ES = _DEBUG_EXTDEV_EN_;// 1; // enable uart interrupt
	// reset Uart variables

	g_UartCommand.Index = 0;

	g_bDebugASCIICommandFlag = _DISABLE;
	g_bDebugProgStopFlag = FALSE;
}

#if ENABLE_MCU_USE_INTERNAL_CLOCK
void McuUseInternalClock ( void )
{
	WORD wTmp;
	#if (SCALER_TYPE==MARIA9)
	BYTE ucBank = msReadByte ( BK0_00_REGBK );
	#endif

	wTmp = ( ( DWORD ) NEW_MCU_XTAL_CLK_HZ * _SMOD + NEW_MCU_XTAL_CLK_HZ + ( TIMER1_MODE2_DIVIDER / 2 ) ) / TIMER1_MODE2_DIVIDER;
	//printf("\r\nNew TIMER1_MODE2_TH1=%d", wTmp);

	#if(SCALER_TYPE==MARIA9)
	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	msWrite2BytesMask_16bitADDR ( BK6s00_70h_ADC_ATOP, 0, _BIT0 ); //Enable MPLL
	msWriteByte ( BK0_00_REGBK, ucBank );
	#endif

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK0_EE_PDMD2, BK0_EE_VAL );

	ES = 0;
	TR1 = 0;
	RI = 0;
	TI = 0; // clear transfer flag

	TH1 = 256 - wTmp;
	g_bMcuUseNewClock = 1;

	TR1 = 1;
	ES = _DEBUG_EXTDEV_EN_;// 1;
}
#endif

#if(ENABLE_WATCH_DOG)
void McuWatchDogSetTimer ( EnuWatchDogTime WatchDogType )
{
	if ( WatchDogType == WatchDogTime_5S ) //5 s'
	{
		CKCON = 0xD8;
	}

	else //600 ms
	{
		CKCON = 0x98;
	}
}

void WatchDogClear ( void )
{
	WDTCON = 1;
}
#else
void WatchDogClear ( void )
{}
#endif
