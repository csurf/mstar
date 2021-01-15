#ifndef _MCU_H_
#define _MCU_H_

#ifdef _MCU_C_
	#define _MCUDEC_
#else
	#define _MCUDEC_ extern
#endif

_MCUDEC_ bit g_bMcuUseNewClock;

_MCUDEC_ void Init_MCU ( void );

typedef enum
{
	WatchDogTime_5S,
	WatchDogTime_500MS,
	WatchDogTime_NUMS
} EnuWatchDogTime;

#if(ENABLE_WATCH_DOG)
	void McuWatchDogSetTimer ( EnuWatchDogTime WatchDogType );
#endif

void WatchDogClear ( void );

#if ENABLE_MCU_USE_INTERNAL_CLOCK
	_MCUDEC_ void McuUseInternalClock ( void );
#endif
_MCUDEC_ void Init_ExternalInterrupt ( void );
_MCUDEC_ void Init_Timer ( void );
_MCUDEC_ void Init_SerialPort ( void );
_MCUDEC_ void Init_IOPorts ( void );
#endif
