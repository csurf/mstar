/******************************************************************************
 Copyright (c) 2003 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: debug.h
 [Date]:
 [Comment]:
 Debug header file.
 [Reversion History]:
*******************************************************************************/
#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef _DEBUG_C_
	#define _DEBUGDEC_
#else
	#define _DEBUGDEC_ extern
#endif

// Uart Protocol Command Definition
#define kWrite_MST_Bank0	0x1E
#define kRead_MST_Bank0		0x1F

#define kWrite_MST_Bank1	0x1C
#define kRead_MST_Bank1		0x1D

#define kWrite_MST_Bank2	0x18
#define kRead_MST_Bank2		0x19

#define kWrite_MST_Bank3	0x16
#define kRead_MST_Bank3		0x17

#define kWrite_MST_Bank4	0x14
#define kRead_MST_Bank4		0x15

#define kWrite_MST_Bank5	0x0E
#define kRead_MST_Bank5		0x0D

//#define kWrite_MST_Bank6	0x06
//#define kRead_MST_Bank6	0x05
//#define kWrite_MST_Bank7	0x04
//#define kRead_MST_Bank7	0x03

#define kWrite_MST_Bank_n	0x01
#define kRead_MST_Bank_n	0x02

#define kWrite_MST_OSD		0x1A
#define kRead_MST_OSD		0x1B

#define kWrite_EEPROM		0x12
#define kRead_EEPROM		0x13

#define kWrite_Device		0x10
#define kRead_Device_B8		0x11
#define kRead_Device_B16	0x0F

#define kWrite_VPC32xx_FP	0x0B
#define kRead_VPC32xx_FP	0x0C

#define kWrite_MCU			0x07
#define kRead_MCU			0x08

#define kRead_MCU_XDATA		0x04
#define kWrite_MCU_XDATA	0x05

#define kEnter_ISP			0x00
#define kEnterFlashIsp		0x03

// Test
#define kTest_Command		0x09

#define DEV_MICRONAS_AUDIO	0x01
#define DEV_PHLIPS_TUNER	0x02
#define DEV_EEPROM_HDCP		0x03

#define URCMD_MICRONAS_AUDIO_WRITE	0
#define URCMD_MICRONAS_AUDIO_READ	1

#define URCMD_PHLIPS_TUNER_SET_FREQ		0
#define URCMD_PHLIPS_TUNER_GET_STATUS	1

#define URCMD_EEPROM_HDCP_GET_ADDR		0
#define URCMD_EEPROM_HDCP_WRITE			1
#define URCMD_EEPROM_HDCP_WRITE_END		2
#define URCMD_EEPROM_HDCP_GET_CHECKSUM	3

#define cmdExitFlashIspMode		0x00
#define cmdEraseFlash			0x01
#define cmdSetFlashRwAddress	0x02
#define cmdCheckSumCompare		0x03
#define cmdFlashCurrentRead		0x04
#define cmdSetFlashType			0x05
#define cmdFlashCurrentWrite	0x06
#define cmdFlashCurrentWriteOne	0x07

// Debug option.If disable all, please modify project file.
#if SYSTEM_BOOT_UP_QUICKLY_ENABLE
	#define _DEBUG_PRINT_EN_ 0//1 //For printf,putchar and putstr
	#define _DEBUG_EXTDEV_EN_ 0 //For extend device
	#define _DEBUG_TESTCOMMAND_EN_ 0//1 //For virtual IR and keypad
	#define _DEBUG_RW_REG_EN_ 0//1 //For Mstar,EEPROM and MCU
#else
	#define _DEBUG_PRINT_EN_ 1 //For printf,putchar and putstr
	#define _DEBUG_EXTDEV_EN_ 1 //For extend device
	#define _DEBUG_TESTCOMMAND_EN_ 1 //For virtual IR and keypad
	#define _DEBUG_RW_REG_EN_ 1 //For Mstar,EEPROM and MCU
#endif

// Debug subroutines
#define DPUTSTR( pcStr ) putstr( pcStr )

_DEBUGDEC_ void uartDecodeCommand ( void );
_DEBUGDEC_ void uartDecodeNormalCommand ( void );

#define UART_CMD_LENGTH (g_UartCommand.Buffer[_UART_CMD_CODE_] >> 5)
#define UART_CMD (g_UartCommand.Buffer[_UART_CMD_CODE_] & 0x1F)
#define UART_CMD_MS_REG (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_MS_DAT (g_UartCommand.Buffer[_UART_CMD_INDEX2_])

// for MST Banks
#define UART_MCU2_BANK 0x1E
#define UART_OSD_BANK 0x21
#define UART_DSP_BANK 0x1F // VD Dsp
#define UART_PARA_BANK 0x20 // VD Dsp parameter
#define UART_XDATA_BANK 0x1D // VD Dsp xdata

#define UART_CMD_MS_BANK (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_MS_REGINDEX (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_CMD_MS_REGDATA (g_UartCommand.Buffer[_UART_CMD_INDEX3_])

#define UART_CMD_XDATA_ADD_H (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_CMD_XDATA_ADD_L (g_UartCommand.Buffer[_UART_CMD_INDEX3_])
#define UART_CMD_XDATA_DATA (g_UartCommand.Buffer[_UART_CMD_INDEX4_])

// for MST Banks
#define UART_CMD_MCU_IDX_H (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_MCU_IDX_L (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_CMD_MCU_DATA (g_UartCommand.Buffer[_UART_CMD_INDEX3_])

// for EXT Command
#define UART_EXT (UART_CMD_LENGTH == 7)
#define UART_CMD_EXT_LENGTH (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_EXT_DEV (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_EXT_CMD (g_UartCommand.Buffer[_UART_CMD_INDEX3_])
#define UART_EXT_CMD_MS_DAT1 (g_UartCommand.Buffer[_UART_CMD_INDEX4_])
#define UART_EXT_CMD_MS_DAT2 (g_UartCommand.Buffer[_UART_CMD_INDEX5_])
#define UART_EXT_CMD_MS_DAT3 (g_UartCommand.Buffer[_UART_CMD_INDEX6_])
#define UART_EXT_CMD_MS_DAT4 (g_UartCommand.Buffer[_UART_CMD_INDEX7_])
#define UART_EXT_CMD_MS_DAT5 (g_UartCommand.Buffer[_UART_CMD_INDEX8_])
#define UART_EXT_CMD_MS_DAT6 (g_UartCommand.Buffer[_UART_CMD_INDEX9_])
#define UART_EXT_CMD_MS_DAT7 (g_UartCommand.Buffer[_UART_CMD_INDEX10_])
#define UART_EXT_CMD_MS_DAT8 (g_UartCommand.Buffer[_UART_CMD_INDEX11_])
#define UART_EXT_CMD_MS_DAT9 (g_UartCommand.Buffer[_UART_CMD_INDEX12_])
#define UART_EXT_CMD_MS_DAT10 (g_UartCommand.Buffer[_UART_CMD_INDEX13_])
#define UART_EXT_CMD_MS_DAT11 (g_UartCommand.Buffer[_UART_CMD_INDEX14_])
#define UART_EXT_CMD_MS_DAT12 (g_UartCommand.Buffer[_UART_CMD_INDEX15_])
#define UART_EXT_CMD_MS_DAT13 (g_UartCommand.Buffer[_UART_CMD_INDEX16_])

#define UART_CMD_FLASH_LENGTH (g_UartCommand.Buffer[_UART_CMD_CODE_] >> 3)
#define UART_CMD_FLASH_ADDR0 (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_FLASH_ADDR1 (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_CMD_FLASH_ADDR2 (g_UartCommand.Buffer[_UART_CMD_INDEX3_])
#define UART_CMD_FLASH_DATA (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_FLASH_CMD (g_UartCommand.Buffer[_UART_CMD_CODE_] & 0x07)

#define _EOS_ '\0' // end of string

// Uart command structure
typedef enum _UartCommadEnumType
{
	_UART_CMD_CODE_,
	_UART_CMD_INDEX1_,
	_UART_CMD_INDEX2_,
	_UART_CMD_INDEX3_,
	_UART_CMD_INDEX4_,
	_UART_CMD_INDEX5_,
	_UART_CMD_INDEX6_,
	_UART_CMD_INDEX7_,
	_UART_CMD_INDEX8_,
	_UART_CMD_INDEX9_,
	_UART_CMD_INDEX10_,
	_UART_CMD_INDEX11_,
	_UART_CMD_INDEX12_,
	_UART_CMD_INDEX13_,
	_UART_CMD_INDEX14_,
	_UART_CMD_INDEX15_,
	_UART_CMD_INDEX16_,

	_UART_CMD_LENGTH_
} UartCommadEnumType;

typedef struct _UartCommadType
{
	BYTE Buffer[_UART_CMD_LENGTH_]; // command buffer
	// [Length+Command] - [Byte 2] - [Byte 3] - [Byte 4] - [Byte 5]
	BYTE Index; // buffer index

} UartCommadType;

typedef enum
{
	MCU_P0,
	MCU_P1,
	MCU_P2,
	MCU_P3,
	MCU_P4,
	MCU_TCON,
	MCU_TMOD,
	MCU_PCON,
	MCU_IE,
	MCU_IP,
	MCU_SCON
} MCU_Reg;

// Uart Variables
_DEBUGDEC_ bit g_bUartDetected; // decode command flag

_DEBUGDEC_ bit g_bUartDisable; // uart output command flag

_DEBUGDEC_ bit g_bDebugASCIICommandFlag;
_DEBUGDEC_ bit g_bDebugProgStopFlag;
// For test
_DEBUGDEC_ XDATA BYTE g_ucDebugFlag;

_DEBUGDEC_ XDATA UartCommadType g_UartCommand; // Uart command struct
//_UARTDEC_ XDATA BOOL g_bFlashIspMode;
//_UARTDEC_ XDATA BYTE g_bFlashType; // 4 - VD, 5 - Teletext
_DEBUGDEC_ BYTE ReSyncCounter;

// Uart subroutines
#if (_DEBUG_PRINT_EN_)
	void putstr ( BYTE* pFmt );
#else
	#define putstr(pFmt)
#endif
_DEBUGDEC_ void putchar ( BYTE ucVal );
_DEBUGDEC_ void printMsg ( char* str );
_DEBUGDEC_ void printf ( char* str, WORD value );
_DEBUGDEC_ void putstr ( char* str );
#endif
