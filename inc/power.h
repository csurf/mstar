#ifndef _POWER_H_
#define _POWER_H_

#ifdef _POWER_C_
	#define _POWERDEC_
#else
	#define _POWERDEC_ extern
#endif


_POWERDEC_ void Power_PowerHandler ( void );
_POWERDEC_ void Power_PowerOnSystem ( void );
_POWERDEC_ void Power_PowerOffSystem ( void );
_POWERDEC_ void Power_TurnOnPanel ( void );
_POWERDEC_ void Power_TurnOffPanel ( void );
_POWERDEC_ void Power_TurnOnGreenLed ( void );
_POWERDEC_ void Power_TurnOffGreenLed ( void );
#endif
