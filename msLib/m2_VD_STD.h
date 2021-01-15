#ifndef __MARIA2_VD_STD_H
#define __MARIA2_VD_STD_H

BYTE* msDSP_Std_GetVersion ( void );

void msDSP_Std_Init ( void );

void msDSP_Std_Processor ( void );

BYTE msDSP_Std_GetNoiseMag ( void );
BYTE msDSP_Std_GetHSyncEdge ( void );
WORD msDSP_Std_GetBurstMag ( void );
BYTE msDSP_Std_GetPhaseError ( void );
BYTE msDSP_Std_GetSecamPhaseError ( void );

extern bit g_bTVSnow;

#endif
