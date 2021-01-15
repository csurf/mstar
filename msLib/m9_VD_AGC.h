#ifndef __M9_VD_AGC_H
#define __M9_VD_AGC_H

// This function must be called before other AGC relative function
void VD_AGC_Init ( void );

// track synctip on S_WhitePeaking state
// 0 = not tracking (default)
// 1 = tracking
#define VD_AGC_TRACK_ENABLE 0x40
#define VD_AGC_CTL_ENABLE 0x80

void VD_AGC_Ctl ( BYTE ucCtl );

// ucStd:
// 0 -> 60Hz
// 1 -> 50Hz
void VD_AGC_SetFscThreshold ( BYTE ucStd );

// Specify the first gain when sync found
void VD_AGC_SetStartGain ( WORD wGain );

// Specify the gain when no sync
void VD_AGC_SetNoSyncGain ( WORD wNoSyncGain );

void VD_AGC_SetMaxGain ( WORD wMaxGain );

void VD_AGC_MonitorStatus ( void );

//void VD_AGC_Processor(void);

BYTE* VD_AGC_GetVersion ( void );

// Change current gain
void VD_AGC_ResetGain ( WORD wGain );

// Get current gain
// bit[13:12]= 00 -> 0.5 gain
// bit[13:12]= 01 -> 1.0 gain
// bit[13:12]= 10 -> 2.0 gain
// bit[11:0]: FINE_GAIN
WORD VD_AGC_GetCurGain ( void );


WORD VD_AGC_GetSyncMag ( void );

//For New T3 AGC
void M9initAGC ( void );
void AGC_Processor ( void );
void M9initAGC_U01 ( void );

#endif
