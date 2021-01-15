#ifndef __MARIA2_ACC_H
#define __MARIA2_ACC_H

void msVDAcc_Init ( void );

// ucCtl:
// bit0: Chrom gain change speed
// 0 -> Normal mode
// 1 -> Fast mode
// bit1: Specify the target chrom
// 0 -> Auto
// 1 -> User specify ==> msVAAcc_SetTargetChrom( BYTE ucBurst );
void msVDAcc_Ctl ( BYTE ucCtl );

// Default parameter:
// ucBurst = 224 for NTSC
// ucBurst = 234 for PAL
void msVAAcc_SetTargetChrom ( BYTE ucBurst );

void msVDAcc_Processor ( void );

BYTE* msVDAcc_GetVersion ( void );


#endif
