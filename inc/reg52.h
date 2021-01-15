/******************************************************************************
 Copyright (c) 2005 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: Mcu_reg.h
 [Date]: 12-Jan-2005
 [Comment]:
 MCU register definition.
 [Reversion History]:
*******************************************************************************/
#ifndef _MCU_REG_H_
#define _MCU_REG_H_

// System
//#include <REG52.H> // for the intended 8052 derivative
#include <INTRINS.H>
#include "board.h"
/*--------------------------------------------------------------------------
reg52.h

Header file for generic 80C52 and 80C32 microcontroller.
Copyright (c) 1988-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __REG52_H__
	#define __REG52_H__

	/* BYTE Registers */
	sfr P0 = 0x80;
	sfr P1 = 0x90;
	sfr P2 = 0xA0;
	sfr P3 = 0xB0;
	sfr PSW = 0xD0;
	sfr ACC = 0xE0;
	sfr B = 0xF0;
	sfr SP = 0x81;
	sfr DPL = 0x82;
	sfr DPH = 0x83;
	sfr PCON = 0x87;
	sfr TCON = 0x88;
	sfr TMOD = 0x89;
	sfr TL0 = 0x8A;
	sfr TL1 = 0x8B;
	sfr TH0 = 0x8C;
	sfr TH1 = 0x8D;
	sfr IE = 0xA8;
	sfr IP = 0xB8;
	sfr SCON = 0x98;
	sfr SBUF = 0x99;

	/* 8052 Extensions */
	sfr T2CON = 0xC8;
	sfr RCAP2L = 0xCA;
	sfr RCAP2H = 0xCB;
	sfr TL2 = 0xCC;
	sfr TH2 = 0xCD;


	/* BIT Registers */
	/* PSW */
	sbit CY = PSW ^ 7;
	sbit AC = PSW ^ 6;
	sbit F0 = PSW ^ 5;
	sbit RS1 = PSW ^ 4;
	sbit RS0 = PSW ^ 3;
	sbit OV = PSW ^ 2;
	sbit P = PSW ^ 0; //8052 only

	/* TCON */
	sbit TF1 = TCON ^ 7;
	sbit TR1 = TCON ^ 6;
	sbit TF0 = TCON ^ 5;
	sbit TR0 = TCON ^ 4;
	sbit IE1 = TCON ^ 3;
	sbit IT1 = TCON ^ 2;
	sbit IE0 = TCON ^ 1;
	sbit IT0 = TCON ^ 0;

	/* IE */
	sbit EA = IE ^ 7;
	sbit ET2 = IE ^ 5; //8052 only
	sbit ES = IE ^ 4;
	sbit ET1 = IE ^ 3;
	sbit EX1 = IE ^ 2;
	sbit ET0 = IE ^ 1;
	sbit EX0 = IE ^ 0;

	/* IP */
	sbit PT2 = IP ^ 5;
	sbit PS = IP ^ 4;
	sbit PT1 = IP ^ 3;
	sbit PX1 = IP ^ 2;
	sbit PT0 = IP ^ 1;
	sbit PX0 = IP ^ 0;

	/* P3 */
	sbit RD = P3 ^ 7;
	sbit WR = P3 ^ 6;
	sbit T1 = P3 ^ 5;
	sbit T0 = P3 ^ 4;
	sbit INT1 = P3 ^ 3;
	sbit INT0 = P3 ^ 2;
	sbit TXD = P3 ^ 1;
	sbit RXD = P3 ^ 0;

	/* SCON */
	sbit SM0 = SCON ^ 7;
	sbit SM1 = SCON ^ 6;
	sbit SM2 = SCON ^ 5;
	sbit REN = SCON ^ 4;
	sbit TB8 = SCON ^ 3;
	sbit RB8 = SCON ^ 2;
	sbit TI = SCON ^ 1;
	sbit RI = SCON ^ 0;

	/* P1 */
	sbit T2EX = P1 ^ 1; // 8052 only
	sbit T2 = P1 ^ 0; // 8052 only

	/* T2CON */
	sbit TF2 = T2CON ^ 7;
	sbit EXF2 = T2CON ^ 6;
	sbit RCLK = T2CON ^ 5;
	sbit TCLK = T2CON ^ 4;
	sbit EXEN2 = T2CON ^ 3;
	sbit TR2 = T2CON ^ 2;
	sbit C_T2 = T2CON ^ 1;
	sbit CP_RL2 = T2CON ^ 0;

#endif

// MCU pin definition
sbit P0_0 = P0 ^ 0;
sbit P0_1 = P0 ^ 1;
sbit P0_2 = P0 ^ 2;
sbit P0_3 = P0 ^ 3;
sbit P0_4 = P0 ^ 4;
sbit P0_5 = P0 ^ 5;
sbit P0_6 = P0 ^ 6;
sbit P0_7 = P0 ^ 7;

sbit P1_0 = P1 ^ 0;
sbit P1_1 = P1 ^ 1;
sbit P1_2 = P1 ^ 2;
sbit P1_3 = P1 ^ 3;
sbit P1_4 = P1 ^ 4;
sbit P1_5 = P1 ^ 5;
sbit P1_6 = P1 ^ 6;
sbit P1_7 = P1 ^ 7;

sbit P2_0 = P2 ^ 0;
sbit P2_1 = P2 ^ 1;
sbit P2_2 = P2 ^ 2;
sbit P2_3 = P2 ^ 3;
sbit P2_4 = P2 ^ 4;
sbit P2_5 = P2 ^ 5;
sbit P2_6 = P2 ^ 6;
sbit P2_7 = P2 ^ 7;

sbit P3_0 = P3 ^ 0;
sbit P3_1 = P3 ^ 1;
sbit P3_2 = P3 ^ 2;
sbit P3_3 = P3 ^ 3;
sbit P3_4 = P3 ^ 4;
sbit P3_5 = P3 ^ 5;
sbit P3_6 = P3 ^ 6;
sbit P3_7 = P3 ^ 7;


sfr CKCON = 0x8E;
sfr WDTCON = 0xD8;
sfr T2MOD = 0xC9;
sfr P4EnOn = 0xDA;
sfr P4 = 0xEB;


// sbit P4_0 = P4 ^ 0;
// sbit P4_1 = P4 ^ 1;
// sbit P4_2 = P4 ^ 2;
// sbit P4_3 = P4 ^ 3;
// sbit P4_4 = P4 ^ 4;
// sbit P4_5 = P4 ^ 5;
// sbit P4_6 = P4 ^ 6;
// sbit P4_7 = P4 ^ 7;


#define XFR_ADDR ((unsigned char xdata*)0xC000)
#define P5 (XFR_ADDR[0x79])
#define P5_0 (XFR_ADDR[0x70])
#define P5_1 (XFR_ADDR[0x71])
#define P5_2 (XFR_ADDR[0x72])
#define P5_3 (XFR_ADDR[0x73])
#define P5_IO_Ctrl (XFR_ADDR[0x78])

#define P6 (XFR_ADDR[0x89])
#define P6_0 (XFR_ADDR[0x80])
#define P6_1 (XFR_ADDR[0x81])
#define P6_2 (XFR_ADDR[0x82])
#define P6_3 (XFR_ADDR[0x83])
#define P6_4 (XFR_ADDR[0x84])
#define P6_5 (XFR_ADDR[0x85])
#define P6_6 (XFR_ADDR[0x86])
#define P6_7 (XFR_ADDR[0x87])
#define P6_IO_Ctrl (XFR_ADDR[0x88])

#define PWDT (XFR_ADDR[0x08])
#define PWDT1 (XFR_ADDR[0x09])

#define PKEYADC1 (XFR_ADDR[0x20]) // Keypad ADC channel 1 value
#define PKEYADC2 (XFR_ADDR[0x21]) // Keypad ADC channel 2 value
#define PKEYADC3 (XFR_ADDR[0x22]) // Keypad ADC channel 3 value

#define P0SEL (XFR_ADDR[0x30]) // 0 = P1.x ctrl, 1 = P1IO.x ctrl.
#define P0IO (XFR_ADDR[0x31]) // 0 = input, 1 = output.

#define P1SEL (XFR_ADDR[0x33]) // 0 = P1.x ctrl, 1 = P1IO.x ctrl.
#define P1IO (XFR_ADDR[0x34])// 0 = input, 1 = output.

#define P4IN (XFR_ADDR[0x3B])// 0 = input, 1 = output.
#define P4SEL (XFR_ADDR[0x3C])// 0 = P1.x ctrl, 1 = P1IO.x ctrl.
#define P4IO (XFR_ADDR[0x3D])// 0 = input, 1 = output.

#define MCUXFR_40_SSPI_WD0 (XFR_ADDR[0x40])
#define MCUXFR_41_SSPI_WD1 (XFR_ADDR[0x41])
#define MCUXFR_42_SSPI_WD2 (XFR_ADDR[0x42])
#define MCUXFR_43_SSPI_WD3 (XFR_ADDR[0x43])
#define MCUXFR_44_SSPI_WD4 (XFR_ADDR[0x44])
#define MCUXFR_4C_SSPI_RD3 (XFR_ADDR[0x4C])
#define MCUXFR_48_SSPI_TRIG (XFR_ADDR[0x48])
#define MCUXFR_49 (XFR_ADDR[0x49])

#define MCUXFR_19_DDC2BI_ID (XFR_ADDR[0x19])
#define MCUXFR_18_DDC2BI_CTRL (XFR_ADDR[0x18])
#define MCUXFR_11_DDC2BI_FLAG (XFR_ADDR[0x11])
#define MCUXFR_10_DDC2BI_INT_EN (XFR_ADDR[0x10])
#define MCUXFR_12_DDC2BI_W_BUF (XFR_ADDR[0x12])
#define MCUXFR_13_DDC2BI_R_BUF (XFR_ADDR[0x13])

#define WORD_LOW_BYTE(w) (((BYTE*)(&w))[1])
#define WORD_HIGH_BYTE(w) (((BYTE*)(&w))[0])
#endif
