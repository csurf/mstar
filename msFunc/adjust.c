#define _ADJUST_C_

#include <MATH.H>
#include "types.h"
#include "board.h"
#include "global.h"
#include "ms_reg.h"
#include "ms_rwreg.h"
#include "debug.h"
#include "msOSD.h"
#include "adjust.h"

#if (SCALER_TYPE == MARIA9)
// <Function>: ADCWaitStatusReady
//
// <Description>: Wait for status ready.
//
// <Parameter>: - <Flow> - <Description>
//-----------------------------------------------------------------------------
// ucRegIndex - In - Register index
// ucRegMask - In - Status mask
void msADCWaitStatusReady ( BYTE ucRegIndex, BYTE ucRegMask )
{

	WORD wDummy = 250; // loop dummy

	#if( ENABLE_MCU_USE_INTERNAL_CLOCK )
	wDummy = 1000;
	#endif

	while ( ! ( msReadByte ( ucRegIndex ) & ucRegMask ) && ( wDummy-- ) ) ;

}

// A. ADC_B (G ADC is used for CVBS Y) Self Mismatch Calibration:
// After VD clock is set,
// we start to calibrate differential ADC linear/offset/gain mismatches.
void msADCSelfMismatchCal_CVBS_SVIDEO_Y ( void )
{
	BYTE ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	//ATOP_28[8] = 1'b0 // Set VCLP equal to 0.8V
	msWrite2BytesMask_16bitADDR ( BK6s00_28h_ADC_ATOP, 0, _BIT8 );
	msWriteByte ( BK0_00_REGBK, REG_BANK6s02_ADCDTOP2 );
	//>>>>>>>>>>>>>>>>>Linear Mismatch Calibration:<<<<<<<<<<<<<<<<<<<<<<//
	//ADCG:
	//DTOPB_03[12:11] = 2'h1 // Set linear calibration mode only.
	msWrite2BytesMask_16bitADDR ( BK6s02_03h_ADC_DTOP2, _BIT11/*1*/, _BIT12 | _BIT11 );
	//DTOPB_7B[15:13] = 3��h0 // No need HSYNC/VSYNC pulse for mismatch calibration.
	msWrite2BytesMask_16bitADDR ( BK6s02_7Bh_ADC_DTOP2, 0, _BIT15 | _BIT14 | _BIT13 );
	//DTOPB_07[0] = 1��b1 // Set linear calibration long mode.
	msWrite2BytesMask_16bitADDR ( BK6s02_07h_ADC_DTOP2, 1, _BIT0 );
	//DTOPB_07[11:8] = 4��hE // Set analog PGA gain in linear calibration mode.
	msWrite2BytesMask_16bitADDR ( BK6s02_07h_ADC_DTOP2, 0x0E00, 0x0F00 );
	//DTOPB_07[15:12] = 4��hF // Set linear calibration reference voltage in 1.05v
	msWrite2BytesMask_16bitADDR ( BK6s02_07h_ADC_DTOP2, 0xF000, 0xF000 );
	//DTOPB_08[2:0] = 3��h7 // Set RGB linear calibration enable.
	msWrite2BytesMask_16bitADDR ( BK6s02_08h_ADC_DTOP2, 0x07, _BIT2 | _BIT1 | _BIT0 );
	//DTOPB_09[11:0] = 12'h03F // Set R/G/B linear calibration delay.
	msWrite2BytesMask_16bitADDR ( BK6s02_09h_ADC_DTOP2, 0x03F, 0x0FFF );
	//DTOPB_0A[7:0] = 8'hFF // Set R/G/B linear calibration duration
	msWrite2BytesMask_16bitADDR ( BK6s02_0Ah_ADC_DTOP2, 0xFF, 0x00FF );
	//DTOPB_0B[5] = 1��h0 // Set R linear calibration alternative disable.
	msWrite2BytesMask_16bitADDR ( BK6s02_0Bh_ADC_DTOP2, 0, _BIT5 );
	//DTOPB_0B[13] = 1��h0 // Set G linear calibration alternative disable.
	msWrite2BytesMask_16bitADDR ( BK6s02_0Bh_ADC_DTOP2, 0, _BIT13 );
	//DTOPB_0C[5] = 1��h0 // Set B linear calibration alternative disable.
	msWrite2BytesMask_16bitADDR ( BK6s02_0Ch_ADC_DTOP2, 0, _BIT5 );
	//DTOPB_05[2:0] = 3��h5 // Bypass R/B channel.
	msWrite2BytesMask_16bitADDR ( BK6s02_05h_ADC_DTOP2, 5, _BIT2 | _BIT1 | _BIT0 );
	//DTOPB_03[8] = 1��h1 // Set mismatch calibration start.
	msWrite2BytesMask_16bitADDR ( BK6s02_03h_ADC_DTOP2, _BIT8/*1*/, _BIT8 );
	//Wait DTOPB_46[15] = 1��h1 // Wait G linear calibration done.
	msADCWaitStatusReady ( BK6s02_46h_ADC_DTOP2 + 1, _BIT7 );

	//Offset/Gain Mismatch Calibration:
	//DTOPB_05[3] = 1��h1 // select self gain pulse active
	msWrite2BytesMask_16bitADDR ( BK6s02_05h_ADC_DTOP2, _BIT3/*1*/, _BIT3 );

	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	//ATOP_34[0] = 1��h1 // Set LDO enable.
	msWrite2BytesMask_16bitADDR ( BK6s00_34h_ADC_ATOP, 1, _BIT0 );
	//ATOP_34[3] = 1��h0 // Set trim_ldo_selection to TRIM path
	msWrite2BytesMask_16bitADDR ( BK6s00_34h_ADC_ATOP, 0, _BIT3 );

	msWriteByte ( BK0_00_REGBK, REG_BANK6s02_ADCDTOP2 );
	//DTOPB_3F[3:0] = 4��hE // Set gain calibration HVREF = 0.90v.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0E, 0x000F );
	//DTOPB_3F[7:4] = 4��hD // Set gain calibration LVREF = 0.65v.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0D0, 0x00F0 );
	//DTOPB_3F[11:8] = 4��h0 // Set analog PGA gain for 0.5V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x00, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h1 // Set analog PGA gain for 0.6V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT8/*1*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[3:0] = 4��hF // Set gain calibration HVREF = 1.05v.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0F, 0x000F );
	//DTOPB_3F[7:4] = 4��hB // Set gain calibration LVREF = 0.55v.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0B0, 0x00F0 );
	//DTOPB_3F[11:8] = 4��h2 // Set analog PGA gain for 0.7V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT9/*0x02*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*0x01*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h3 // Set analog PGA gain for 0.8V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT9 | _BIT8/*0x03*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h4 // Set analog PGA gain for 0.9V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT10/*0x04*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h5 // Set analog PGA gain for 1.0V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT10 | _BIT8/*0x05*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h6 // Set analog PGA gain for 1.1V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT10 | _BIT9/*0x06*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h7 // Set analog PGA gain for 1.2V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT10 | _BIT9 | _BIT8/*0x07*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h8 // Set analog PGA gain for 1.3V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT11/*0x08*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h9 // Set analog PGA gain for 1.4V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT11 | _BIT8/*0x09*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hA // Set analog PGA gain for 1.5V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT11 | _BIT9/*0x0A*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hB // Set analog PGA gain for 1.6V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT11 | _BIT9 | _BIT8/*0x0B*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hC // Set analog PGA gain for 1.7V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT11 | _BIT10/*0x0C*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hD // Set analog PGA gain for 1.8V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT11 | _BIT10 | _BIT8/*0x0D*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hE // Set analog PGA gain for 1.9V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0E00, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hF // Set analog PGA gain for 2.0V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0F00, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );

	//ADCG:
	//DTOPB_03[12:11] = 2'h2 // Set offset/gain calibration mode.
	msWrite2BytesMask_16bitADDR ( BK6s02_03h_ADC_DTOP2, _BIT12, _BIT12 | _BIT11 );
	//DTOPB_7B[15:13] = 3��h0 // No need HSYNC/VSYNC pulse for mismatch // calibration.
	msWrite2BytesMask_16bitADDR ( BK6s02_7Bh_ADC_DTOP2, 0, _BIT15 | _BIT14 | _BIT13 );
	//DTOPB_13[0] = 1��h1 // Set offset calibration long mode.
	msWrite2BytesMask_16bitADDR ( BK6s02_13h_ADC_DTOP2, 1, _BIT0 );
	//DTOPB_13[2] = 1��h1 // Set G offset calibration enable.
	msWrite2BytesMask_16bitADDR ( BK6s02_13h_ADC_DTOP2, _BIT2, _BIT2 );
	//DTOPB_14[11:0] = 12'h03F // Set G offset calibration delay.
	msWrite2BytesMask_16bitADDR ( BK6s02_14h_ADC_DTOP2, 0x03F, 0x0FFF );
	//DTOPB_15[7:0] = 8'hFF // Set G offset calibration duration
	msWrite2BytesMask_16bitADDR ( BK6s02_15h_ADC_DTOP2, 0x0FF, 0x00FF );
	//DTOPB_1F[0] = 1��h1 // Set gain calibration long mode.
	msWrite2BytesMask_16bitADDR ( BK6s02_1Fh_ADC_DTOP2, 1, _BIT0 );
	//DTOPB_1F[2] = 1��h1 // Set G gain calibration enable.
	msWrite2BytesMask_16bitADDR ( BK6s02_1Fh_ADC_DTOP2, _BIT2, _BIT2 );
	//DTOPB_1F[4] = 1��h1 // Set G gain calibration mismatch mode only.
	msWrite2BytesMask_16bitADDR ( BK6s02_1Fh_ADC_DTOP2, _BIT4, _BIT4 );
	//DTOPB_20[11:0] = 12'h03F // Set G gain calibration delay.
	msWrite2BytesMask_16bitADDR ( BK6s02_20h_ADC_DTOP2, 0x03F, 0x0FFF );
	//DTOPB_21[15:0] = 16'hFFFF// Set G gain calibration duration.
	msWrite2BytesMask_16bitADDR ( BK6s02_21h_ADC_DTOP2, 0xFFFF, 0xFFFF );
	//DTOPB_03[8] = 1��h1 // Set mismatch calibration start.
	msWrite2BytesMask_16bitADDR ( BK6s02_03h_ADC_DTOP2, _BIT8, _BIT8 );
	//Wait DTOPB_49[15] = 1��h1 // Wait G offset calibration done.
	msADCWaitStatusReady ( BK6s02_49h_ADC_DTOP2 + 1, _BIT7 );
	//Wait DTOPB_4C[15] = 1��h1 // Wait G gain calibration done.
	msADCWaitStatusReady ( BK6s02_4Ch_ADC_DTOP2 + 1, _BIT7 );
	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	//ATOP_28[8] = 1'b1 // Set VCLP return to 1.2V
	msWrite2BytesMask_16bitADDR ( BK6s00_28h_ADC_ATOP, _BIT8, _BIT8 );
	//Triggle Cal
	//msWriteByte( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	//msWrite2BytesMask_16bitADDR(BK6s00_29h_ADC_ATOP,_BIT13,_BIT13);
	msWriteByte ( BK0_00_REGBK, ucBank );
}
// B. ADC_A (R ADC is used for S-video Chroma) Self Mismatch Calibration:
// After VD clock is set,
// we start to calibrate differential ADC linear/offset/gain mismatched.
void msADCSelfMismatchCal_SVIDEO_C ( void )
{
	BYTE ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	//ATOP_28[8] = 1'b0 // Set VCLP equal to 0.8V
	msWrite2BytesMask_16bitADDR ( BK6s00_28h_ADC_ATOP, 0, _BIT8 );
	msWriteByte ( BK0_00_REGBK, REG_BANK6s02_ADCDTOP2 );
	//>>>>>>>>>>>>>>>>>Linear Mismatch Calibration:<<<<<<<<<<<<<<<<<<<<<<//
	//ADCR:
	//DTOPB_03[12:11] = 2'h1 // Set linear calibration mode only.
	msWrite2BytesMask_16bitADDR ( BK6s02_03h_ADC_DTOP2, _BIT11/*1*/, _BIT12 | _BIT11 );
	//DTOPB_7B[15:13] = 3��h0 // No need HSYNC/VSYNC pulse for mismatch calibration.
	msWrite2BytesMask_16bitADDR ( BK6s02_7Bh_ADC_DTOP2, 0, _BIT15 | _BIT14 | _BIT13 );
	//DTOPB_07[0] = 1��b1 // Set linear calibration long mode.
	msWrite2BytesMask_16bitADDR ( BK6s02_7Bh_ADC_DTOP2, 1, _BIT0 );
	//DTOPB_07[11:8] = 4��hE // Set analog PGA gain in linear calibration mode.
	msWrite2BytesMask_16bitADDR ( BK6s02_07h_ADC_DTOP2, 0x0E00, 0x0F00 );
	//DTOPB_07[15:12] = 4��hF // Set linear calibration reference voltage in 1.05v
	msWrite2BytesMask_16bitADDR ( BK6s02_07h_ADC_DTOP2, 0xF000, 0xF000 );
	//DTOPB_08[2:0] = 3��h7 // Set RGB linear calibration enable.
	msWrite2BytesMask_16bitADDR ( BK6s02_08h_ADC_DTOP2, 0x07, _BIT2 | _BIT1 | _BIT0 );
	//DTOPB_09[11:0] = 12'h03F // Set R/G/B linear calibration delay.
	msWrite2BytesMask_16bitADDR ( BK6s02_09h_ADC_DTOP2, 0x03F, 0x0FFF );
	//DTOPB_0A[7:0] = 8'hFF // Set R/G/B linear calibration duration
	msWrite2BytesMask_16bitADDR ( BK6s02_0Ah_ADC_DTOP2, 0xFF, 0x00FF );
	//DTOPB_0B[5] = 1��h0 // Set R linear calibration alternative disable.
	msWrite2BytesMask_16bitADDR ( BK6s02_0Bh_ADC_DTOP2, 0, _BIT5 );
	//DTOPB_0B[13] = 1��h0 // Set G linear calibration alternative disable.
	msWrite2BytesMask_16bitADDR ( BK6s02_0Bh_ADC_DTOP2, 0, _BIT13 );
	//DTOPB_0C[5] = 1��h0 // Set B linear calibration alternative disable.
	msWrite2BytesMask_16bitADDR ( BK6s02_0Ch_ADC_DTOP2, 0, _BIT5 );
	//DTOPB_05[2:0] = 3��h6 // Bypass G/B channel.
	msWrite2BytesMask_16bitADDR ( BK6s02_05h_ADC_DTOP2, _BIT2 | _BIT1/*6*/, _BIT2 | _BIT1 | _BIT0 );
	//DTOPB_03[8] = 1��h1 // Set mismatch calibration start.
	msWrite2BytesMask_16bitADDR ( BK6s02_03h_ADC_DTOP2, _BIT8/*1*/, _BIT8 );
	//Wait DTOPB_45[15] = 1��h1 // Wait R linear calibration done.
	msWrite2BytesMask_16bitADDR ( BK6s02_45h_ADC_DTOP2, _BIT15/*1*/, _BIT15 );

	//Offset/Gain Mismatch Calibration:
	//DTOPB_05[3] = 1��h1 // select self gain pulse active
	msWrite2BytesMask_16bitADDR ( BK6s02_05h_ADC_DTOP2, _BIT3/*1*/, _BIT3 );

	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	//ATOP_34[0] = 1��h1 // Set LDO enable.
	msWrite2BytesMask_16bitADDR ( BK6s00_34h_ADC_ATOP, 1, _BIT0 );
	//ATOP_34[3] = 1��h0 // Set trim_ldo_selection to TRIM path
	msWrite2BytesMask_16bitADDR ( BK6s00_34h_ADC_ATOP, 0, _BIT3 );

	msWriteByte ( BK0_00_REGBK, REG_BANK6s02_ADCDTOP2 );
	//DTOPB_3F[3:0] = 4��hE // Set gain calibration HVREF = 0.90v.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0xE, 0x000F );
	//DTOPB_3F[7:4] = 4��hD // Set gain calibration LVREF = 0.65v.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0xD0, 0x00F0 );
	//DTOPB_3F[11:8] = 4��h0 // Set analog PGA gain for 0.5V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h1 // Set analog PGA gain for 0.6V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT12/*0x01*/, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[3:0] = 4��hF // Set gain calibration HVREF = 1.05v.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0xE, 0x000F );
	//DTOPB_3F[7:4] = 4��hB // Set gain calibration LVREF = 0.55v.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0xB0, 0x00F0 );
	//DTOPB_3F[11:8] = 4��h2 // Set analog PGA gain for 0.7V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0200, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h3 // Set analog PGA gain for 0.8V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0300, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h4 // Set analog PGA gain for 0.9V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0400, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h5 // Set analog PGA gain for 1.0V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0500, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h6 // Set analog PGA gain for 1.1V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0600, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h7 // Set analog PGA gain for 1.2V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0700, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h8 // Set analog PGA gain for 1.3V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0800, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��h9 // Set analog PGA gain for 1.4V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0900, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hA // Set analog PGA gain for 1.5V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0A00, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hB // Set analog PGA gain for 1.6V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0B00, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hC // Set analog PGA gain for 1.7V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0C00, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hD // Set analog PGA gain for 1.8V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0D00, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hE // Set analog PGA gain for 1.9V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0E00, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );
	//DTOPB_3F[11:8] = 4��hF // Set analog PGA gain for 2.0V input level.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, 0x0F00, 0x0F00 );
	//DTOPB_3F[15] = 1��h1 // Write HVREF/LREF to internal registers.
	msWrite2BytesMask_16bitADDR ( BK6s02_3Fh_ADC_DTOP2, _BIT15/*1*/, _BIT15 );

	//ADCR:
	//DTOPB_03[12:11] = 2'h2 // Set offset/gain calibration mode.
	msWrite2BytesMask_16bitADDR ( BK6s02_03h_ADC_DTOP2, _BIT12/*0x02*/, _BIT12 | _BIT11 );
	//DTOPB_7B[15:13] = 3��h0 // No need HSYNC/VSYNC pulse for mismatch calibration.
	msWrite2BytesMask_16bitADDR ( BK6s02_7Bh_ADC_DTOP2, 0, 0xE000 );
	//DTOPB_13[0] = 1��h1 // Set offset calibration long mode.
	msWrite2BytesMask_16bitADDR ( BK6s02_13h_ADC_DTOP2, 1, _BIT0 );
	//DTOPB_13[1] = 1��h1 // Set R offset calibration enable.
	msWrite2BytesMask_16bitADDR ( BK6s02_13h_ADC_DTOP2, _BIT1/*1*/, _BIT1 );
	//DTOPB_14[11:0] = 12'h03F // Set R offset calibration delay.
	msWrite2BytesMask_16bitADDR ( BK6s02_14h_ADC_DTOP2, 0x03F, 0x0FFF );
	//DTOPB_15[7:0] = 8'hFF // Set R offset calibration duration
	msWrite2BytesMask_16bitADDR ( BK6s02_15h_ADC_DTOP2, 0xFF, 0x00FF );
	//DTOPB_1F[0] = 1��h1 // Set gain calibration long mode.
	msWrite2BytesMask_16bitADDR ( BK6s02_1Fh_ADC_DTOP2, 1, _BIT0 );
	//DTOPB_1F[1] = 1��h1 // Set R gain calibration enable.
	msWrite2BytesMask_16bitADDR ( BK6s02_1Fh_ADC_DTOP2, _BIT1/*1*/, _BIT1 );
	//DTOPB_1F[4] = 1��h1 // Set R gain calibration mismatch mode only.
	msWrite2BytesMask_16bitADDR ( BK6s02_1Fh_ADC_DTOP2, _BIT4/*1*/, _BIT4 );
	//DTOPB_20[11:0] = 12'h03F // Set R gain calibration delay.
	msWrite2BytesMask_16bitADDR ( BK6s02_20h_ADC_DTOP2, 0x03F, 0x0FFF );
	//DTOPB_21[15:0] = 16'hFFFF// Set R gain calibration duration.
	msWrite2BytesMask_16bitADDR ( BK6s02_21h_ADC_DTOP2, 0xFFFF, 0xFFFF );
	//DTOPB_03[8] = 1��h1 // Set mismatch calibration start.
	msWrite2BytesMask_16bitADDR ( BK6s02_03h_ADC_DTOP2, _BIT8, _BIT8 );
	//Wait DTOPB_48[15] = 1��h1 // Wait R offset calibration done.
	msADCWaitStatusReady ( BK6s02_48h_ADC_DTOP2 + 1, _BIT7 );
	//Wait DTOPB_4B[15] = 1��h1 // Wait R gain calibration done.
	msADCWaitStatusReady ( BK6s02_4Bh_ADC_DTOP2 + 1, _BIT7 );

	msWriteByte ( BK0_00_REGBK, REG_BANK6s00_ADCATOP );
	//ATOP_28[8] = 1'b1 // Set VCLP return to 1.2V
	msWrite2BytesMask_16bitADDR ( BK6s00_28h_ADC_ATOP, _BIT8, _BIT8 );

	msWriteByte ( BK0_00_REGBK, ucBank );
}
#endif
