#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#ifdef _KEYPAD_C_
	#define _KEYPADDEC_
#else
	#define _KEYPADDEC_ extern
#endif

#define INPUT_PRESS _BIT0
#define INPUT_HOLD _BIT1

#if(MARIA9_VERSION == MARIA9_B)
	_KEYPADDEC_ XDATA WORD g_ucKeyStableCountBuff[8];
#else
	_KEYPADDEC_ XDATA BYTE g_ucKeyStableCountBuff[8];
#endif

_KEYPADDEC_ BYTE g_ucKeyCounter;
_KEYPADDEC_ BYTE g_ucLastKeypad;
_KEYPADDEC_ BYTE g_ucLastIRKey;
_KEYPADDEC_ BYTE g_ucKeyRptCount;
_KEYPADDEC_ BYTE g_ucNextRptCount;

//_KEYPADDEC_ BYTE KeypadButton;
#if(MARIA9_VERSION == MARIA9_B)
	_KEYPADDEC_ XDATA WORD g_ucCurrentKeyADC[2];
#else
	_KEYPADDEC_ XDATA BYTE g_ucCurrentKeyADC[2];
#endif

#ifdef EXPAND_GPIO_74HC164
	_KEYPADDEC_ void Gpio_74HC164_Output_Value ( BYTE U8Value );
#endif

_KEYPADDEC_ void Key_ScanKeypad ( void );
_KEYPADDEC_ void IRKeyProcess ( BYTE uckeypad );
_KEYPADDEC_ void Key_KeyInit ( void );
_KEYPADDEC_ void CheckFactoryKeyStatus ( void );

#endif
