#define _MSOSD_C_

#include <STDLIB.H>
#include "types.h"
#include "ms_reg.h"
#include "board.h"
#include "global.h"
#include "debug.h"
#include "panel.h"
#include "mstar.h"
#include "misc.h"
#include "menuDef.h"
#include "font.h"
#include "extlib.h"
#include "ms_rwreg.h"
#include "msOSD.h"
#include "mcu.h"

//==================================================================================
// variable declaration
//
BYTE OsdWindowWidth = 10;
BYTE OsdWindowHeight = 10;
BYTE OsdFontColor = 0x01;

//==================================================================================
// Code start
void Osd_InitOSD ( void )
{
	// Osd transparency control
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	msSoftwareReset ( OSDR_B, 1 );

	msWriteByte ( BK0_A0_OSDIOA, 0x9E | _BIT6 ); // enable all OSD I/O channel and Clear OSD code&attr

	msWriteOSDByte ( OSD_0C_IOSDC1, 0x00 );

	msWriteByte ( BK0_62_DITHCTL1, 0x03 ); //for OSD Blending
	msWriteByte ( BK0_63_OSD_CTL, 0x03 ); //New Blending Level
	msWriteOSDByte ( OSD_01_OSDDBC, 0x5 ); // enable double
	msWriteOSDByte ( OSD_12_OCBUFO, 0x00 ); // disable OSD code buffer Base/Offset address
	msWriteOSDByte ( OSD_0E_IOSDC3, 0x00 ); //0x0F); // shadow function control

	msWriteOSDByte ( OSD_10_IOSDC4, 0x1B );
	msWriteOSDByte ( OSD_42_UNDERLINE, 0x0C );

	msWriteByte ( BK0_A0_OSDIOA, 0x9E );

	#if (SYSTEM_BOOT_UP_QUICKLY_ENABLE == 0)
	Osd_LoadInvertFont ( InvertDRAM_MONO_FONT_BUS | InvertCOMPRESS_DATA, 0, &tCompressMonoFontData, sizeof ( tCompressMonoFontData ) );
	WatchDogClear();

	// Osd_LoadFont ( ColorFontStart, &tOSDFont1, sizeof ( tOSDFont1 ) ); // load osd fonts
	//WatchDogClear();

	msWriteOSDByte ( OSD_46_OSD4CFFA, ColorFontStart );
	Osd_LoadColor ( &tOSDColorPalette0, sizeof ( tOSDColorPalette0 ) ); // load osd color
	//WatchDogClear();

	#endif

	msWriteByte ( BK0_00_REGBK, ucBank );
}

#if SYSTEM_BOOT_UP_QUICKLY_ENABLE

void Osd_LoadOsdFont ( void )
{
	// Osd transparency control
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	msWriteOSDByte ( OSD_0C_IOSDC1, 0x00 ); //osd hide

	Osd_LoadInvertFont ( InvertDRAM_MONO_FONT_BUS | InvertCOMPRESS_DATA, 0, &tCompressMonoFontData, sizeof ( tCompressMonoFontData ) );
	WatchDogClear();

	// Osd_LoadFont ( ColorFontStart, &tOSDFont1, sizeof ( tOSDFont1 ) ); // load osd fonts
	//WatchDogClear();

	msWriteOSDByte ( OSD_46_OSD4CFFA, ColorFontStart );
	Osd_LoadColor ( &tOSDColorPalette0, sizeof ( tOSDColorPalette0 ) ); // load osd color
	//WatchDogClear();

	msWriteByte ( BK0_00_REGBK, ucBank );
}

#endif

/*
void Osd_LoadFont ( BYTE addr, BYTE* fontPtr, WORD num )
{
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK0_A3_RAMFA, addr );
	msWriteTBL ( BK0_A4_RAMFD, fontPtr, num, 0 );
	msWriteByte ( BK0_00_REGBK, ucBank );
}
*/

void Osd_LoadColor ( BYTE* colorPtr, BYTE num )
{
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK0_A1_OSDRA, OSD_28_CLR0R );
	msWriteTBL ( BK0_A2_OSDRD, colorPtr, num, 0 );
	msWriteByte ( BK0_00_REGBK, ucBank );
}

// setup osd window size
void Osd_SetWindowSize ( BYTE width, BYTE height )
{
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );


	OsdWindowWidth = width & 0x3F;
	OsdWindowHeight = height & 0x1F;
	msWriteOSDByte ( OSD_06_OSDW, OsdWindowWidth - 1 );
	msWriteOSDByte ( OSD_07_OSDH, OsdWindowHeight - 1 );

	msWriteByte ( BK0_A0_OSDIOA, 0xDE ); // clear osd content
	ForceDelay1ms ( 3 );
	msWriteByte ( BK0_A0_OSDIOA, 0x9E );
	msWriteByte ( BK0_00_REGBK, ucBank );
}

// setup OSD window position
// takes into account panel dimensions
void Osd_SetPosition ( BYTE xPos, BYTE yPos )
{
	WORD posValue;
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );

	#if DoubleXSize
	posValue = ( ( DWORD ) xPos * ( PanelWidth - ( WORD ) OsdWindowWidth * 12 * 2 ) ) / 100 + ( PanelHStart - 48 );
	#else
	posValue = ( ( DWORD ) xPos * ( PanelWidth - ( WORD ) OsdWindowWidth * 12 ) ) / 100 + ( PanelHStart - 48 );
	#endif

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	//posValue=posValue/4;
	msWriteOSDByte ( OSD_02_OHSTA_L, posValue & 0xFF );
	msWriteOSDByte ( OSD_03_OHSTA_H, posValue >> 8 );

	#if DoubleYSize
	posValue = ( ( DWORD ) yPos * ( PanelHeight - ( WORD ) OsdWindowHeight * 18 * 2 ) ) / 100;
	#else
	posValue = ( ( DWORD ) yPos * ( PanelHeight - ( WORD ) OsdWindowHeight * 18 ) ) / 100;
	#endif

	//posValue=posValue/4;;
	msWriteOSDByte ( OSD_04_OVSTA_L, posValue & 0xFF );
	msWriteOSDByte ( OSD_05_OVSTA_H, posValue >> 8 );
	msWriteByte ( BK0_00_REGBK, ucBank );
}

void Osd_SetTextColor ( BYTE foreColor, BYTE backColor )
{
	OsdFontColor = ( foreColor & 0xF ) << 4 | ( backColor & 0xF );
}

void Osd_DrawChar ( BYTE xPos, BYTE yPos, BYTE ch )
{
	WORD tempValue;
	BYTE drawCode = TRUE;
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	if ( yPos & _BIT7 )
	{
		drawCode = FALSE;
	}

	yPos &= 0x3F; //~(_BIT7|_BIT6);

	tempValue = ( WORD ) yPos * OsdWindowWidth + xPos; // get real address
	msWriteWord ( BK0_A9_DISPAA_H, tempValue ); // display font attribute
	msWriteByte ( BK0_AA_DISPAD, OsdFontColor );

	if ( drawCode )
	{
		msWriteWord ( BK0_A6_DISPCA_H, tempValue ); // dispaly font code
		msWriteByte ( BK0_A7_DISPCD, tASCII2FONT[ch] );
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void Osd_DrawStr ( BYTE xPos, BYTE yPos, BYTE* str )
{
#define dispChar xPos
#define dispPtr yPos

	WORD tempValue;
	BYTE drawCode = TRUE;
	BYTE ucBank;

	if ( yPos & _BIT7 )
	{
		drawCode = FALSE;
	}

	yPos &= 0x3F; //~(_BIT7|_BIT6);

	ucBank = msReadByte ( BK0_00_REGBK );

	tempValue = ( WORD ) yPos * OsdWindowWidth + xPos; // get real address
	dispPtr = 0;
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteWord ( BK0_A9_DISPAA_H, tempValue );

	while ( dispChar = * ( str + dispPtr ) ) // display string font index
	{
		msWriteByte ( BK0_AA_DISPAD, OsdFontColor );
		dispPtr++;
	}

	if ( drawCode == TRUE )
	{
		dispPtr = 0;
		msWriteWord ( BK0_A6_DISPCA_H, tempValue );

		while ( dispChar = * ( str + dispPtr ) ) // display string font index
		{
			msWriteByte ( BK0_A7_DISPCD, tASCII2FONT[dispChar] );
			dispPtr++;
		}
	}

	msWriteByte ( BK0_00_REGBK, ucBank );

#undef dispChar
#undef dispPtr
}

void DrawNum ( BYTE xPos, BYTE yPos, char len, WORD value ) //int value)
{
	char _minus = 0;

	if ( value < 0 )
	{
		value = 0 - value;
		_minus = 1;
	}

	if ( value == 0 )
	{
		Osd_DrawChar ( xPos + ( len-- ), yPos, ( BYTE ) Num2ASCII ( 0 ) );
	}

	else
	{
		while ( value && len ) // translate integer to string
		{
			Osd_DrawChar ( xPos + ( len-- ), yPos, ( BYTE ) Num2ASCII ( value % 10 ) );
			value /= 10;
		}
	}

	if ( _minus && len >= 0 ) // add sign
	{
		Osd_DrawChar ( xPos + ( len-- ), yPos, ( BYTE ) '-' );
	}

	_minus = ( _minus ) ? ( 0 ) : ( 1 );

	for ( ; _minus <= len; _minus++ )
	{
		Osd_DrawChar ( xPos + _minus, yPos, ( BYTE ) ' ' );
	}
}

void Osd_DrawNum ( BYTE xPos, BYTE yPos, WORD value )
{
	DrawNum ( xPos, yPos, 3, value );
}

void Osd_DrawLargeNum ( BYTE xPos, BYTE yPos, WORD value )
{
	DrawNum ( xPos, yPos, 4, value );
}

void Osd_DrawGauge ( BYTE xPos, BYTE yPos, BYTE length, BYTE value )
{
	BYTE leadPtr;
	WORD tempValue;
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );

	if ( xPos == 0xF0 )
	{
		Osd_DrawChar ( 0, yPos, '-' );
		Osd_DrawChar ( length + 1, yPos, '+' );
		xPos = 0;
	}

	leadPtr = ( WORD ) value * length / 10; // resver 0.1

	#define i value

	tempValue = ( WORD ) yPos * OsdWindowWidth + ( xPos + 1 ); // get real address
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteWord ( BK0_A9_DISPAA_H, tempValue ); // display font attribute
	msWriteWord ( BK0_A6_DISPCA_H, tempValue ); // dispaly font code

	tempValue = leadPtr / 10;

	if ( tempValue == length && value < 100 )
	{
		tempValue--;
	}

	for ( i = 1; i <= tempValue; i++ ) // fill font with value
	{
		msWriteByte ( BK0_A7_DISPCD, tASCII2FONT[GaugeFont4_4] );
		msWriteByte ( BK0_AA_DISPAD, OsdFontColor );
	}

	i = i + 1;

	if ( i <= length ) // fill font without value
	{
		tempValue = ( WORD ) yPos * OsdWindowWidth + ( xPos + i ); // get real address
		msWriteWord ( BK0_A9_DISPAA_H, tempValue ); // display font attribute
		msWriteWord ( BK0_A6_DISPCA_H, tempValue ); // dispaly font code

		for ( ; i <= length; i++ )
		{
			msWriteByte ( BK0_A7_DISPCD, tASCII2FONT[GaugeFont0_4] );
			msWriteByte ( BK0_AA_DISPAD, OsdFontColor );
		}
	}

	#undef i

	if ( leadPtr < length * 10 )
	{
		value = leadPtr % 10;
		xPos += leadPtr / 10 + 1;
		leadPtr = ( ( WORD ) value * 12 + 5 ) / 10;

		if ( leadPtr < 3 && value )
		{
			leadPtr = 3;
		}

		Osd_DrawChar ( xPos, yPos, GaugeFont0_4 + leadPtr / 3 );
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void Osd_Show ( void )
{
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteOSDByte ( OSD_0C_IOSDC1, ( DoubleXSize << 4 ) | ( DoubleYSize << 6 ) | MWIN_B );

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void Osd_Hide ( void )
{
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	msWriteOSDByte ( OSD_0C_IOSDC1, 0x00 );
	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msWriteOSDByte ( BYTE address, BYTE value )
{
	BYTE ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	msWriteByte ( BK0_A1_OSDRA, address );
	msWriteByte ( BK0_A2_OSDRD, value );
	msWriteByte ( BK0_00_REGBK, ucBank );
}

BYTE msReadOSDByte ( BYTE address )
{
	BYTE UcTemp, ucBank;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	msWriteByte ( BK0_A1_OSDRA, address );
	UcTemp = msReadByte ( BK0_A2_OSDRD );
	msWriteByte ( BK0_00_REGBK, ucBank );
	return UcTemp;
}

// ============================
// Draw Hex for DEBUG
BYTE Hex2ASCII ( BYTE Num )
{
	return ( Num < 10 ) ? ( Num + 0x30 ) : ( Num + 0x37 );
}

void DrawHex ( BYTE xPos, BYTE yPos, WORD value )
{
	char len = 3;

	while ( value && len >= 0 )
	{
		Osd_DrawChar ( xPos + ( len-- ), yPos, ( BYTE ) Hex2ASCII ( value % 0x10 ) );
		value /= 0x10;
	}

	if ( len > 0 )
	{
		for ( value = 0; value <= len; value++ )
		{
			Osd_DrawChar ( xPos + value, yPos, ( BYTE ) '0' );
		}
	}
}

void Osd_DrawHex ( BYTE xPos, BYTE yPos, WORD value )
{
	DrawHex ( xPos, yPos, value );
}

void msWriteInvertMonoCompressTblBurst ( BYTE ucReg, BYTE* pTable, WORD wNum )
{
	BYTE ucLineCnt;
	BYTE ucTmp1, ucTmp2;
	BYTE ucData[3];
	BOOL bOdd = TRUE;
	BYTE uc1, uc2;

	while ( wNum )
	{
		WatchDogClear();
		// Get data
		ucTmp1 = * ( pTable++ );
		ucLineCnt = ( ucTmp1 >> 4 ) + 1;
		ucTmp1 &= 0x0f;
		ucTmp2 = * ( pTable++ );
		wNum -= 2;

		for ( uc1 = 0; uc1 < ucLineCnt; uc1++ )
		{
			if ( bOdd )
			{
				// Odd line
				bOdd = FALSE;
				ucData[0] = ucTmp1;
				ucData[1] = ucTmp2;
			}

			else
			{
				// Even line
				bOdd = TRUE;
				ucData[0] |= ( ucTmp1 << 4 );
				ucData[2] = ucTmp2;

				for ( uc2 = 0; uc2 < 3; uc2++ ) // Write 3 bytes to chip
				{
					msWriteByte ( ucReg, ucData[uc2] );
				}

			}
		}
	}

}

void Osd_LoadInvertFont ( BYTE ucType, BYTE ucAddr, BYTE* pFont, WORD wNum )
{
	BOOL bCompress = FALSE;
	BYTE ucBank;

	ucBank = msReadByte ( BK0_00_REGBK );

	if ( ucType & InvertCOMPRESS_DATA )
	{
		bCompress = TRUE;
		ucType &= ( ~InvertCOMPRESS_DATA );
	}

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	msWriteByte ( BK0_A3_RAMFA, ucAddr ); // OSD RAM font address
	//msWriteByte(BK0_A0_OSDIOA, ucType | InvertOSD_IO_BURST_MODE | InvertOSD_IO_AUTO_INCREASE); // write enable
	WatchDogClear();
	msWriteInvertMonoCompressTblBurst ( BK0_A4_RAMFD, pFont, wNum );
	//msWriteByte(BK0_A0_OSDIOA, InvertOSD_IO_WRITE_END | InvertOSD_IO_BURST_MODE | InvertOSD_IO_AUTO_INCREASE); // write end

	msWriteByte ( BK0_00_REGBK, ucBank );
}
