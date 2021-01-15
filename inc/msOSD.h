#ifndef _MSOSD_H_
#define _MSOSD_H_

#ifdef _MSOSD_C_
	#define _MSOSDDEC_
#else
	#define _MSOSDDEC_ extern
#endif

#define OSD_0_INDEX 0x30

#define InvertOSD_IO_WRITE_END _BIT7

#define InvertOSD_IO_BURST_MODE _BIT3
#define InvertOSD_PALETTE_IO_ACCESS _BIT2
#define InvertOSD_IO_AUTO_INCREASE _BIT1

#define DoubleXSize 0
#define DoubleYSize 0

#define ColorFontStart 200

//===================================================================================

#define GaugeFontStart 0xF0
#define GaugeFontEnd 0xF1
#define GaugeFont0_4 0x12
#define GaugeFont1_4 0x13
#define GaugeFont2_4 0x14
#define GaugeFont3_4 0x15
#define GaugeFont4_4 0x16

#define Num2ASCII(Num) (Num+0x30)

typedef enum _InvertDRamBusType
{
	InvertDRAM_CODE_BUS = 0x10,
	InvertDRAM_ATTRIBUTE_BUS = 0x20,
	InvertDRAM_MONO_FONT_BUS = 0x30,
	InvertDRAM_COLOR_FONT_BUS = 0x40,
	InvertDRAM_TEXTURE_BUS = 0x50,
	InvertDRAM_CPU_READ_BUS = 0x60,
	InvertCOMPRESS_DATA = 0x01,

	InvertDRAM_NULL_BUS = 0x00
} InvertDRamBusType;

_MSOSDDEC_ BYTE OsdWindowWidth;
_MSOSDDEC_ BYTE OsdWindowHeight;

_MSOSDDEC_ BYTE msReadOSDByte ( BYTE address );
_MSOSDDEC_ void msWriteOSDByte ( BYTE address, BYTE value );
_MSOSDDEC_ void Osd_DrawNum ( BYTE xPos, BYTE yPos, WORD value );
_MSOSDDEC_ void Osd_DrawLargeNum ( BYTE xPos, BYTE yPos, WORD value );

_MSOSDDEC_ void Osd_DrawStr ( BYTE xPos, BYTE yPos, BYTE* str );
_MSOSDDEC_ void Osd_DrawRealStr ( BYTE xPos, BYTE yPos, BYTE* str );
_MSOSDDEC_ void Osd_DrawHex ( BYTE xPos, BYTE yPos, WORD value );
_MSOSDDEC_ void Osd_SetPosition ( BYTE xPos, BYTE yPos );
_MSOSDDEC_ void Osd_SetWindowSize ( BYTE width, BYTE height );
_MSOSDDEC_ void Osd_SetTextColor ( BYTE foreColor, BYTE backColor );
_MSOSDDEC_ void Osd_DrawChar ( BYTE xPos, BYTE yPos, BYTE ch );
_MSOSDDEC_ void Osd_DrawGauge ( BYTE xPos, BYTE yPos, BYTE length, BYTE value );
_MSOSDDEC_ void Osd_Show ( void );
_MSOSDDEC_ void Osd_Hide ( void );
_MSOSDDEC_ void Osd_InitOSD ( void );

_MSOSDDEC_ void Osd_DrawPropStr ( BYTE xPos, BYTE yPos, BYTE* str );
_MSOSDDEC_ void DrawNum ( BYTE xPos, BYTE yPos, char len, WORD value );

_MSOSDDEC_ void Osd_LoadOsdFont ( void ); //shmily

_MSOSDDEC_ void Osd_LoadFont ( BYTE addr, BYTE* fontPtr, WORD num );
_MSOSDDEC_ void Osd_LoadColor ( BYTE* colorPtr, BYTE num );
_MSOSDDEC_ void Osd_LoadInvertFont ( BYTE ucType, BYTE ucAddr, BYTE* pFont, WORD wNum );

_MSOSDDEC_ void msWriteInvertMonoCompressTblBurst ( BYTE ucReg, BYTE* pTable, WORD wNum );

#endif

