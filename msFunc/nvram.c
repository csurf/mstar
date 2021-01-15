#define _NVRAM_C_

#include "types.h"
#include "board.h"
#include "misc.h"
#include "global.h"
#include "reg52.h"
#include "debug.h"
#include "mcu.h"

#define NVRAM_DEVICE 0xA0

#define rmCalDeviceAdr(wIndex) NVRAM_DEVICE|((HIBYTE(wIndex)&0x07)<<1)
#define HIBYTE(value) ((BYTE)((value) / 0x100))
#define LOBYTE(value) ((BYTE)(value))

#if RM_EEPROM_TYPE < RM_TYPE_SST512

#if (RM_EEPROM_TYPE == RM_TYPE_24C16)
	#define RM_PAGE_WRITE_LEN 16
#elif (RM_EEPROM_TYPE == RM_TYPE_24C32)
	#define RM_PAGE_WRITE_LEN 32
#endif

// <Function>: rmBurstReadBytes
//
// <Description>: EEPROM burst read bytes
//
// <Parameter>: - <Flow> - <Description>
// wIndex - In - index
// pBuf - Out - buffer pointer
// ucBufLen - In - buffer length
//-----------------------------------------------------------------------------
//

void rmBurstReadBytes ( WORD wIndex, BYTE* pBuf, WORD ucBufLen )
{
	#if (RM_EEPROM_TYPE == RM_TYPE_24C16)
	i2cBurstReadBytes ( rmCalDeviceAdr ( wIndex ), LOBYTE ( wIndex ), pBuf, ucBufLen );
	#elif (RM_EEPROM_TYPE == RM_TYPE_24C32)
	BYTE ucDummy; // loop dummy

	ucDummy = I2C_ACCESS_DUMMY_TIME;

	while ( ucDummy-- )
	{
		if ( i2c_AccessStart ( NVRAM_DEVICE, I2C_WRITE ) == FALSE )
		{
			continue;
		}

		if ( i2c_SendByte ( HIBYTE ( wIndex ) ) == I2C_NON_ACKNOWLEDGE ) // check non-acknowledge
		{
			continue;
		}

		if ( i2c_SendByte ( LOBYTE ( wIndex ) ) == I2C_NON_ACKNOWLEDGE ) // check non-acknowledge
		{
			continue;
		}

		if ( i2c_AccessStart ( NVRAM_DEVICE, I2C_READ ) == FALSE )
		{
			continue;
		}

		while ( ucBufLen-- ) // loop to burst read
		{
			*pBuf = i2c_ReceiveByte ( ucBufLen ); // receive byte

			pBuf++; // next byte pointer
		} // while

		break;
	} // while

	i2c_Stop();
	#endif
}
// <Function>: rmPageWrite
//
// <Description>: EEPROM page write

// <Parameter>: - <Flow> - <Description>
// wIndex - In - index
// pBuf - Out - buffer pointer
// ucBufLen - In - buffer length
//-----------------------------------------------------------------------------
//
#if (RM_EEPROM_TYPE == RM_TYPE_24C32)
void rmPageWrite ( WORD wIndex, BYTE* pBuf, BYTE ucBufLen )
{
	BYTE ucDummy; // loop dummy

	ucDummy = I2C_ACCESS_DUMMY_TIME;

	while ( ucDummy-- )
	{
		if ( i2c_AccessStart ( NVRAM_DEVICE, I2C_WRITE ) == FALSE )
		{
			continue;
		}

		if ( i2c_SendByte ( HIBYTE ( wIndex ) ) == I2C_NON_ACKNOWLEDGE ) // check non-acknowledge
		{
			continue;
		}

		if ( i2c_SendByte ( LOBYTE ( wIndex ) ) == I2C_NON_ACKNOWLEDGE ) // check non-acknowledge
		{
			continue;
		}

		while ( ucBufLen-- ) // loop of writting data
		{
			i2c_SendByte ( *pBuf ); // send byte

			pBuf++; // next byte pointer
		} // while

		break;
	} // while

	i2c_Stop();
}
#endif
// <Function>: rmBurstWriteBytes
//
// <Description>: EEPROM burst write bytes
//
// <Parameter>: - <Flow> - <Description>
// wIndex - In - index
// pBuf - Out - buffer pointer
// ucBufLen - In - buffer length
//-----------------------------------------------------------------------------
//
void rmBurstWriteBytes ( WORD wIndex, BYTE* pBuf, WORD ucBufLen )
{
	BYTE ucWriteCount; // write counter
	BYTE ucRemainLen; // i2c word address

	while ( 1 )
	{
		// check page write roll over
		if ( ucBufLen > RM_PAGE_WRITE_LEN )
		{
			ucWriteCount = RM_PAGE_WRITE_LEN;
		}

		else
		{
			ucWriteCount = ucBufLen;
		}

		// check word address higher than page write bits
		ucRemainLen = LOBYTE ( wIndex ) % RM_PAGE_WRITE_LEN;

		if ( ucRemainLen ) // check ramain
		{
			ucRemainLen = RM_PAGE_WRITE_LEN - ucRemainLen;

			if ( ucWriteCount > ucRemainLen ) // check not roll over
			{
				ucWriteCount = ucRemainLen;
			}
		}

		// EEPROM page write
		#if (RM_EEPROM_TYPE == RM_TYPE_24C16)
		i2cBurstWriteBytes ( rmCalDeviceAdr ( wIndex ), LOBYTE ( wIndex ), pBuf, ucWriteCount );
		#elif (RM_EEPROM_TYPE == RM_TYPE_24C32)
		rmPageWrite ( wIndex, pBuf, ucWriteCount );
		#endif
		// check end of buffer
		ucBufLen -= ucWriteCount;

		if ( ucBufLen == 0 )
		{
			break;
		}

		wIndex += ucWriteCount; // next word address
		pBuf += ucWriteCount; // next buffer pointer

		Delay1ms ( 1 );
	} // while

}

void NVRam_WriteByte ( WORD addr, BYTE value )
{
	rmBurstWriteBytes ( addr, &value, 1 );
}

void NVRam_WriteWord ( WORD addr, WORD value )
{
	BYTE ucBuf[2];
	ucBuf[0] = value & 0xFF;
	ucBuf[1] = ( value >> 8 ) & 0xFF;
	rmBurstWriteBytes ( addr, ucBuf, 2 );
}

void NVRam_ReadByte ( WORD addr, BYTE* value )
{
	rmBurstReadBytes ( addr, value, 1 );
}

void NVRam_WriteTbl ( WORD addr, BYTE* buffer, WORD count )
{
	rmBurstWriteBytes ( addr, buffer, count );
}

void NVRam_ReadTbl ( WORD addr, BYTE* buffer, WORD count )
{
	rmBurstReadBytes ( addr, buffer, count );
}

#else

typedef enum _FlashType
{
	FlashST = 0x20,
	FlashWinbond = 0xEF,
	FlashAtmel = 0x1F,
	FlashPMC = 0x9D,
	FlashSaiFun = 0x05,
	FlashEon = 0x1C,
	FlashSST = 0xBF,
	Flash_Num
} FlashType;

void mstSaveDisplayDataBanked ( WORD address )
{
	BYTE i, ChipId;
	BYTE code FlashID[3] = {0x9f, 0xab, 0x90};

	for ( i = 0; i <= 2; i++ )
	{
		MCUXFR_40_SSPI_WD0 = FlashID[i];
		MCUXFR_41_SSPI_WD1 = 0x00;
		MCUXFR_42_SSPI_WD2 = 0x00;
		MCUXFR_43_SSPI_WD3 = 0x00;
		MCUXFR_48_SSPI_TRIG = 0xc4;
		ChipId = MCUXFR_4C_SSPI_RD3; // PMC Manufacture ID =0x9d

		if ( ( i == 0 ) && ( ( ChipId == FlashST ) || ( ChipId == FlashAtmel ) ) )
		{
			break;
		}

		else if ( ( i == 1 ) && ( ( ChipId == FlashPMC ) || ( ChipId == FlashSST ) || ( ChipId == FlashSaiFun ) ) )
		{
			break;
		}

		//else FlashEon FlashWinbond
	}

	if ( ChipId == FlashPMC || ChipId == FlashWinbond ) // PMC & WINBOND
	{
		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xf8;

		// Write Status 0x00
		MCUXFR_40_SSPI_WD0 = 0x01;
		MCUXFR_41_SSPI_WD1 = 0x00;
		MCUXFR_48_SSPI_TRIG = 0xf9;

		// Write Enable WREN + Sector Erase
		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xf8;
		MCUXFR_40_SSPI_WD0 = 0xd7; // Sector Erase 0x00e000
		MCUXFR_41_SSPI_WD1 = 0;
		MCUXFR_42_SSPI_WD2 = ( BYTE ) ( address >> 8 );
		MCUXFR_43_SSPI_WD3 = 0;
		MCUXFR_48_SSPI_TRIG = 0xfb;
		Delay1ms ( 100 );

		// WREN + Write Byte
		for ( i = 0; i < sizeof ( g_VideoSetting ); i++ )
		{
			MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
			MCUXFR_48_SSPI_TRIG = 0xf8;
			MCUXFR_40_SSPI_WD0 = 0x02; //FlashWriteByte SST
			MCUXFR_41_SSPI_WD1 = 0;
			MCUXFR_42_SSPI_WD2 = ( BYTE ) ( address >> 8 );
			MCUXFR_43_SSPI_WD3 = i;
			MCUXFR_44_SSPI_WD4 = * ( &g_VideoSetting.ucVersion + i );
			MCUXFR_48_SSPI_TRIG = 0xfc;
			Delay1ms ( 5 );
		}

		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xf8;

		// Write Status 0x0C // 20051207 seven
		MCUXFR_40_SSPI_WD0 = 0x01;
		MCUXFR_41_SSPI_WD1 = 0x0C;
		MCUXFR_48_SSPI_TRIG = 0xf9;

		// Write disable : Reset write enable latch
		MCUXFR_40_SSPI_WD0 = 0x04; // Write disable
		MCUXFR_48_SSPI_TRIG = 0xf8;
		//sysWriteString("Save Flash Data finish.\x0d\x0a");

	}

	else if ( ChipId == FlashAtmel ) // SAIFUN flash
	{
		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xf8;

		// Write Status 0x00
		MCUXFR_40_SSPI_WD0 = 0x01;
		MCUXFR_41_SSPI_WD1 = 0x00;
		MCUXFR_48_SSPI_TRIG = 0xF9;

		// Write Enable WREN + Sector Erase
		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xF8;
		MCUXFR_40_SSPI_WD0 = 0x20; // Sector Erase 0x00e000
		MCUXFR_41_SSPI_WD1 = 0;
		MCUXFR_42_SSPI_WD2 = ( BYTE ) ( address >> 8 );
		MCUXFR_43_SSPI_WD3 = 0;
		MCUXFR_48_SSPI_TRIG = 0xFB;
		Delay1ms ( 20 );

		// WREN + Write Byte
		for ( i = 0; i < sizeof ( g_VideoSetting ); i++ )
		{
			MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
			MCUXFR_48_SSPI_TRIG = 0xF8;
			MCUXFR_40_SSPI_WD0 = 0x02; //FlashWriteByte SST
			MCUXFR_41_SSPI_WD1 = 0;
			MCUXFR_42_SSPI_WD2 = ( BYTE ) ( address >> 8 );
			MCUXFR_43_SSPI_WD3 = i;
			MCUXFR_44_SSPI_WD4 = * ( &g_VideoSetting.ucVersion + i );
			MCUXFR_48_SSPI_TRIG = 0xFC;
			Delay1ms ( 10 );
		}

		// Write Protect
		MCUXFR_40_SSPI_WD0 = 0x01;
		MCUXFR_41_SSPI_WD1 = 0x0C;
		MCUXFR_48_SSPI_TRIG = 0xF9;
	}

	else if ( ChipId == FlashEon ) // SAIFUN flash
	{
		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xf8;

		// Write Status 0x00
		MCUXFR_40_SSPI_WD0 = 0x01;
		MCUXFR_41_SSPI_WD1 = 0x00;
		MCUXFR_48_SSPI_TRIG = 0xF9;

		// Write Enable WREN + Sector Erase
		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xF8;
		MCUXFR_40_SSPI_WD0 = 0xD8; // Sector Erase 0x00e000
		MCUXFR_41_SSPI_WD1 = 0;
		MCUXFR_42_SSPI_WD2 = ( BYTE ) ( address >> 8 );
		MCUXFR_43_SSPI_WD3 = 0;
		MCUXFR_48_SSPI_TRIG = 0xFB;
		Delay1ms ( 10 );

		// WREN + Write Byte
		for ( i = 0; i < sizeof ( g_VideoSetting ); i++ )
		{
			MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
			MCUXFR_48_SSPI_TRIG = 0xF8;
			MCUXFR_40_SSPI_WD0 = 0x02; //FlashWriteByte SST
			MCUXFR_41_SSPI_WD1 = 0;
			MCUXFR_42_SSPI_WD2 = ( BYTE ) ( address >> 8 );
			MCUXFR_43_SSPI_WD3 = i;
			MCUXFR_44_SSPI_WD4 = * ( &g_VideoSetting.ucVersion + i );
			MCUXFR_48_SSPI_TRIG = 0xFC;
			Delay1ms ( 10 );
		}

		// Write Protect
		MCUXFR_40_SSPI_WD0 = 0x01;
		MCUXFR_41_SSPI_WD1 = 0x0C;
		MCUXFR_48_SSPI_TRIG = 0xF9;
	}

	else if ( ChipId == FlashSaiFun ) // SAIFUN flash
	{
		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xf8;

		// Write Status 0x00
		MCUXFR_40_SSPI_WD0 = 0x01;
		MCUXFR_41_SSPI_WD1 = 0x00;
		MCUXFR_48_SSPI_TRIG = 0xF9;

		// Write Enable WREN + Sector Erase
		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xF8;
		MCUXFR_40_SSPI_WD0 = 0x81; // Sector Erase 0x00e000
		MCUXFR_41_SSPI_WD1 = 0;
		MCUXFR_42_SSPI_WD2 = ( BYTE ) ( address >> 8 );
		MCUXFR_43_SSPI_WD3 = 0;
		MCUXFR_48_SSPI_TRIG = 0xFb;
		Delay1ms ( 6 );

		// WREN + Write Byte
		for ( i = 0; i < sizeof ( g_VideoSetting ); i++ )
		{
			MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
			MCUXFR_48_SSPI_TRIG = 0xF8;
			MCUXFR_40_SSPI_WD0 = 0x02; //FlashWriteByte SST
			MCUXFR_41_SSPI_WD1 = 0;
			MCUXFR_42_SSPI_WD2 = ( BYTE ) ( address >> 8 );
			MCUXFR_43_SSPI_WD3 = i;
			MCUXFR_44_SSPI_WD4 = * ( &g_VideoSetting.ucVersion + i );
			MCUXFR_48_SSPI_TRIG = 0xFC;
			Delay1ms ( 10 );
		}

		// Write Protect
		MCUXFR_40_SSPI_WD0 = 0x01;
		MCUXFR_41_SSPI_WD1 = 0x0C;
		MCUXFR_48_SSPI_TRIG = 0xF9;
	}

	else if ( ChipId == FlashSST ) // SST flash
	{
		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xc1;

		// disable Write Protect
		MCUXFR_40_SSPI_WD0 = 0x50;
		MCUXFR_41_SSPI_WD1 = 0x01;
		MCUXFR_42_SSPI_WD2 = 0x00;
		MCUXFR_48_SSPI_TRIG = 0xc8;

		// Write Enable WREN + Sector Erase
		MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
		MCUXFR_48_SSPI_TRIG = 0xc1;
		MCUXFR_40_SSPI_WD0 = 0x20; // Sector Erase 0x00e000
		MCUXFR_41_SSPI_WD1 = 0;
		MCUXFR_42_SSPI_WD2 = ( BYTE ) ( address >> 8 );
		MCUXFR_43_SSPI_WD3 = 0;
		MCUXFR_48_SSPI_TRIG = 0xc4;
		Delay1ms ( 25 ); //from spec page 19

		// WREN + Write Byte
		for ( i = 0; i < sizeof ( g_VideoSetting ); i++ )
		{
			MCUXFR_40_SSPI_WD0 = 0x06; // Write Enable WREN
			MCUXFR_48_SSPI_TRIG = 0xc1;
			MCUXFR_40_SSPI_WD0 = 0x02; //FlashWriteByte SST
			MCUXFR_41_SSPI_WD1 = 0;
			MCUXFR_42_SSPI_WD2 = ( BYTE ) ( address >> 8 );
			MCUXFR_43_SSPI_WD3 = i;
			MCUXFR_44_SSPI_WD4 = * ( &g_VideoSetting.ucVersion + i );
			MCUXFR_48_SSPI_TRIG = 0xc5;
			Delay1ms ( 5 );
		}

		// Enable Write Protect
		MCUXFR_40_SSPI_WD0 = 0x50;
		MCUXFR_41_SSPI_WD1 = 0x01;
		MCUXFR_42_SSPI_WD2 = 0x0c;
		MCUXFR_48_SSPI_TRIG = 0xc8;
	}
}

void mstSaveDisplayData ( WORD address )
{
	mstSaveDisplayDataBanked ( address );
	Delay1ms ( 100 );
	mstSaveDisplayDataBanked ( address + 0x1000 );
}

void mstLoadDisplayData ( WORD address )
{
	BYTE i;
	BYTE code* add;
	add = ( BYTE code* ) address;

	WatchDogClear();
	//printf("\r\nRD<%x>",address);

	for ( i = 0 ; i < sizeof ( g_VideoSetting ); i++ )
	{
		* ( &g_VideoSetting.ucVersion + i ) = * ( add + i );
	}

}

#if RM_EEPROM_TYPE < RM_TYPE_SST512
void NVRam_WriteByte ( WORD addr, BYTE value )
{
	addr = addr;
	value = value;
	mstSaveDisplayData ( SFD_ADDRESS );
}
#endif

void NVRam_WriteTbl ( WORD addr, BYTE* buffer, WORD count )
{
	addr = addr;
	buffer = buffer;
	count = count;
	mstSaveDisplayData ( SFD_ADDRESS );
}

#endif
