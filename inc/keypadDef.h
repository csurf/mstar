#include "board.h"
typedef enum
{
	KEY_UP,
	KEY_DOWN,
	KEY_MENU,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SOURCE,
	KEY_POWER,
	KEY_NOTHING
} KeypadMaskType;

typedef enum
{
	ADCKEY1,
	#if (KEY_TYPE == Dual_ADCKey)
	ADCKEY2,
	#endif
	ADCKEYNUMS,
} ADCType;


