#define _KEYPAD_C_

#include <MATH.H>
#include "types.h"
#include "board.h"
#include "ms_reg.h"
#include "global.h"
#include "keypadDef.h"
#include "debug.h"
#include "misc.h"
#include "ms_rwreg.h"
#include "reg52.h"
#include "menu.h"
#include "keypad.h"

//===============================================================
#define MAX_KEYVALUE 0x3F
#define HIGHLEVEL 0x3A
#define KeyJitterCounter 15
#define KeyStableCounter 1
#define KEY_Idle 0xFF

#ifdef EXPAND_GPIO_74HC164

void Gpio_74HC164_Output_Value ( BYTE U8Value )
{
	BYTE index, Gpio_pin;
	Gpio_pin = U8Value ;

	for ( index = 0 ; index < 8 ; index++ )
	{
		IO_74HC164_SCK_LOW

		if ( Gpio_pin & 0x80 )
		{
			IO_74HC164_SDA_HIGH
		}

		else
		{
			IO_74HC164_SDA_LOW
		}

		Gpio_pin <<= 1;
		IO_74HC164_SCK_HIGH
	}
}
#endif

#if(MARIA9_VERSION == MARIA9_B)

WORD Key_ScanValue ( BYTE KeyAdcPort )
{
	BYTE ucBank, ucSARhigh6Bit, ucSARlow4Bit;
	ucBank = msReadByte ( BK0_00_REGBK );

	if ( KeyAdcPort == ADCKEY1 )
	{
		msWriteByte ( BK0_00_REGBK, REG_BANK7_CHIPTOP );
		ucSARlow4Bit = msReadByte ( BK7_9E_CHIPTOP );
		ucSARhigh6Bit = PKEYADC1 & 0x3F;
		g_ucCurrentKeyADC[KeyAdcPort] = ( ( WORD ) ucSARhigh6Bit << 4 ) | ( ucSARlow4Bit & 0x0F );
		// if(g_ucCurrentKeyADC[KeyAdcPort]<0x3e0)
			// printf("\r\nPKEYADC1=0x%x",g_ucCurrentKeyADC[KeyAdcPort]);
	}

	else
	{
		msWriteByte ( BK0_00_REGBK, REG_BANK7_CHIPTOP );
		ucSARlow4Bit = msReadByte ( BK7_9E_CHIPTOP );
		ucSARhigh6Bit = PKEYADC2 & 0x3F;
		g_ucCurrentKeyADC[KeyAdcPort] = ( ( WORD ) ucSARhigh6Bit << 4 ) | ( ( ucSARlow4Bit >> 4 ) & 0x0F );
		if(g_ucCurrentKeyADC[KeyAdcPort]<0x3e0)
		printf("\r\nPKEYADC1=0x%x",g_ucCurrentKeyADC[KeyAdcPort]);
	}

	//for SAR2
	/*
	msWriteByte(BK0_00_REGBK, REG_BANK7_CHIPTOP);
	ucSARlow4Bit = msReadByte(BK7_9F_CHIPTOP);
	ucSARhigh6Bit = PKEYADC3&0x3F;
	g_ucCurrentKeyADC[KeyAdcPort]=((WORD)ucSARhigh6Bit<<4)|(ucSARlow4Bit&0x0F);
	*/
	msWriteByte ( BK0_00_REGBK, ucBank );

	return g_ucCurrentKeyADC[KeyAdcPort];
}

#else

BYTE Key_ScanValue ( BYTE KeyAdcPort )
{
	BYTE i, ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	
	msWriteByte ( BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU );
	msWriteByte ( BK1_90_SARADC_CTRL, 0x50 ); // power down sar

	if ( KeyAdcPort == ADCKEY1 )
	{
		msWriteByte ( BK1_90_SARADC_CTRL, 0x10 );

		for ( i = 0; i < 20; i++ )
		{
			msWriteByte ( BK1_90_SARADC_CTRL, 0x90 );
		}

		g_ucCurrentKeyADC[KeyAdcPort] = PKEYADC1;

		//if(g_ucCurrentKeyADC[KeyAdcPort] < 0x3c)
			// printf("\r\nPKEYADC1=0x%x", g_ucCurrentKeyADC[KeyAdcPort]);
	}

	else
	{
		msWriteByte ( BK1_90_SARADC_CTRL, 0x11 );

		for ( i = 0; i < 20; i++ )
		{
			msWriteByte ( BK1_90_SARADC_CTRL, 0x91 );
		}

		g_ucCurrentKeyADC[KeyAdcPort] = PKEYADC2;

		//if(g_ucCurrentKeyADC[KeyAdcPort] < 0x3c)
		//printf("\r\nPKEYADC2=0x%x", g_ucCurrentKeyADC[KeyAdcPort]);
	}

	//for SAR2
	/*
	msWriteByte(BK1_90_SARADC_CTRL, 0x12);
	for( i=0;i<20;i++)
	msWriteByte(BK1_90_SARADC_CTRL, 0x92);
	*/
	msWriteByte ( BK0_00_REGBK, ucBank );

	return g_ucCurrentKeyADC[KeyAdcPort];
}

#endif

BYTE Key_GetKeypadStatus ( void )
{
	BYTE KeyData = KEY_NOTHING;

	#if(MARIA9_VERSION == MARIA9_B)
	WORD ADCValue;
	#else
	BYTE ADCValue;
	#endif

	#if(KEY_TYPE == Single_ADCKey_3Key)
	//------------------------------------------------
	ADCValue = Key_ScanValue ( ADCKEY1 );
	// printf("\r\nadc: 0x%x",ADCValue);
	
	if ( ADCValue < ( KEY_AD_L0 + KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_DOWN]++ > KeyStableCounter )
		{
			return KEY_DOWN;
		}
	}

	else if ( ADCValue < ( KEY_AD_L1 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L1 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_MENU]++ > KeyStableCounter )
		{
			return KEY_MENU;
		}
	}

	else if ( ADCValue < ( KEY_AD_L2 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L2 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_UP]++ > KeyStableCounter )
		{
			return KEY_UP;
		}
	}

	#endif

	#if(KEY_TYPE == Single_ADCKey)
	//------------------------------------------------
	ADCValue = Key_ScanValue ( ADCKEY1 );

	if ( ADCValue < ( KEY_AD_L0 + KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_POWER]++ > KeyStableCounter )
		{
			return KEY_POWER;
		}
	}

	else if ( ADCValue < ( KEY_AD_L1 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L1 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_SOURCE]++ > KeyStableCounter )
		{
			return KEY_SOURCE;
		}
	}

	else if ( ADCValue < ( KEY_AD_L2 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L2 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_MENU]++ > KeyStableCounter )
		{
			return KEY_MENU;
		}
	}

	else if ( ADCValue < ( KEY_AD_L3 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L3 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_RIGHT]++ > KeyStableCounter )
		{
			return KEY_RIGHT;
		}
	}

	else if ( ADCValue < ( KEY_AD_L4 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L4 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_LEFT]++ > KeyStableCounter )
		{
			return KEY_LEFT;
		}
	}

	else if ( ADCValue < ( KEY_AD_L5 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L5 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_UP]++ > KeyStableCounter )
		{
			return KEY_UP;
		}
	}

	else if ( ADCValue < ( KEY_AD_L6 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L6 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_DOWN]++ > KeyStableCounter )
		{
			return KEY_DOWN;
		}
	}

	#endif

	#if(KEY_TYPE == Dual_ADCKey)
	//------------------------------------------------
	ADCValue = Key_ScanValue ( ADCKEY1 );

	if ( ADCValue < ( KEY_AD_L0 + KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_RIGHT]++ > KeyStableCounter )
		{
			return KEY_RIGHT;
		}
	}

	else if ( ADCValue < ( KEY_AD_L1 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L1 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_LEFT]++ > KeyStableCounter )
		{
			return KEY_LEFT;
		}
	}

	else if ( ADCValue < ( KEY_AD_L2 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L2 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_UP]++ > KeyStableCounter )
		{
			return KEY_UP;
		}
	}

	else if ( ADCValue < ( KEY_AD_L3 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L3 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_DOWN]++ > KeyStableCounter )
		{
			return KEY_DOWN;
		}
	}

	ADCValue = Key_ScanValue ( ADCKEY2 );

	if ( ADCValue < ( KEY_AD_L0 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L0 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_POWER]++ > KeyStableCounter )
		{
			return KEY_POWER;
		}
	}

	else if ( ADCValue < ( KEY_AD_L1 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L1 - KEY_AD_DELTA ) )
	{
		if ( g_ucKeyStableCountBuff[KEY_MENU]++ > KeyStableCounter )
		{
			return KEY_MENU;
		}
	}

	else if ( ADCValue < ( KEY_AD_L2 + KEY_AD_DELTA ) && ADCValue > ( KEY_AD_L2 - KEY_AD_DELTA ) )
	{
		//printf("\r\nADCValue===<%x>", ADCValue);
		if ( g_ucKeyStableCountBuff[KEY_SOURCE]++ > KeyStableCounter )
		{
			return KEY_SOURCE;
		}

		f
	}

	#endif

	if ( !g_ucKeyCounter )
	{
		return KEY_NOTHING;
	}

	g_ucKeyCounter--;

	return KEY_Idle;
}

void Key_ScanKeypad ( void )
{
	BYTE keypadStatus;

	keypadStatus = Key_GetKeypadStatus();
	
	if ( keypadStatus != KEY_Idle )
	{		
		if ( keypadStatus != KEY_NOTHING )
		{
			// printf("\r\nkeypad: %d", keypadStatus);	
			if ( keypadStatus == g_ucLastKeypad )
			{
				EventRepeatProcess ( keypadStatus, 2 );
			}

			else
			{
				EventProcess ( keypadStatus );
			}
		}

		g_ucLastKeypad = keypadStatus;
		Key_KeyInit();
	}
}

void Key_KeyInit ( void )
{
	g_ucKeyCounter = KeyJitterCounter;

	g_ucKeyStableCountBuff[0] = 0;
	g_ucKeyStableCountBuff[1] = 0;
	g_ucKeyStableCountBuff[2] = 0;
	g_ucKeyStableCountBuff[3] = 0;
	g_ucKeyStableCountBuff[4] = 0;
	g_ucKeyStableCountBuff[5] = 0;
	g_ucKeyStableCountBuff[6] = 0;
	g_ucKeyStableCountBuff[7] = 0;
}

