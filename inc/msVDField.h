#ifndef _MSVDFIELD_H_
#define _MSVDFIELD_H_

#include "board.h"

#if(ENABLE_VD_DSP)
	#define ENABLE_SW_FIELD 0
#else
	#define ENABLE_SW_FIELD 0
#endif

#if(ENABLE_SW_FIELD)

	void MSVD_FieldProcessor ( void );

#endif

#endif
