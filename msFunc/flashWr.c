/******************************************************************************
 Copyright (c) 2003 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: FlashWr.c
 [Date]: 25-Sep-2005
 [Comment]:

 [Reversion History]:
*******************************************************************************/
#define _FLASHWR_C_

#include "flashWr.h"
#include "uart.h"
#include "ram.h"

#if 0
typedef struct
{
	//BYTE name[20]; // 1
	DWORD size; // 2
	BYTE manufacturer_id; // 3
	BYTE device_id; // 4

	// command
	BYTE WREN; // 5
	BYTE WRDI; // 6
	BYTE RDSR; // 7
	BYTE WRSR; // 8
	BYTE READ; // 9
	BYTE FAST_READ; // 10
	BYTE PG_PROG; // 11
	BYTE SECTOR_ERASE; // 12
	BYTE BLOCK_ERASE; // 13
	BYTE CHIP_ERASE; // 14
	BYTE RDID; // 15

} SFlashType;
#endif

code SFlashType SupportSFlash[6] =
{
	// 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
	/*0*/{/*"SST25VF512A",*/0x10000, 0xBF, 0x48, 0x06, 0x04, 0x05, 0x01, 0x03, 0x0B, 0xAF, 0x20, 0xD8, 0x60, 0xAB},
	/*1*/{/*"PMC25LV512", */0x10000, 0x9D, 0x7B, 0x06, 0x04, 0x05, 0x01, 0x03, NULL, 0x02, 0xD7, 0xD8, 0xC7, 0xAB},
	/*2*/{/*"SST25VF010A",*/0x20000, 0xBF, 0x49, 0x06, 0x04, 0x05, 0x01, 0x03, 0x0B, 0xAF, 0x20, 0xD8, 0x60, 0xAB},
	/*3*/{/*"PMC25LV010", */0x20000, 0x9D, 0x7C, 0x06, 0x04, 0x05, 0x01, 0x03, NULL, 0x02, 0xD7, 0xD8, 0xC7, 0xAB},
	/*4*/{/*"AT25F512A", */0x10000, 0x1F, 0x65, 0x06, 0x04, 0x05, 0x01, 0x03, NULL, 0x02, 0x52, NULL, 0x62, 0x15},
	/*5*/{/*"AT25F1024", */0x20000, 0x1F, 0x60, 0x06, 0x04, 0x05, 0x01, 0x03, NULL, 0x02, 0x52, NULL, 0x62, 0x15},
};

/*
void MCU_Delay30us(void)
{
 BYTE i=5;
 while(i--)
 MCU_Delay1us();
}
*/

FlashProgErrorType MariaISP ( void )
{
	FlashProgErrorType ErrorFlag = FlashProgOK;

	sFlash = SupportSFlash[g_ucFlashType];
	mcuClrIntEn();

	//Step1:Enter ISP mode
	FlashProgStepIndicator ( EnterISP );
	FLashPutstr ( "\r\n1:Maria ISP" );

	if ( !EnterIspMode() )
	{
		ErrorFlag |= EnterIspModeErr;
		goto ProgEnd;
	}

	//Step2:Chip Erase
	FlashProgStepIndicator ( ChipErase );
	FLashPutstr ( "\r\n2:Chip Erase" );
	SFlashChip_Erase();

	#ifndef NO_BLANK_CHECK
	//Step3:Blanking Check
	FlashProgStepIndicator ( BlankingCheck );
	FLashPutstr ( "\r\n3:Blanking" );

	if ( !SFlashBlanking ( 0, sFlash.size ) )
	{
		ErrorFlag |= SFlashBlankingErr;
		goto ProgEnd;
	}

	#endif

	//Step4:Prog Flash
	FlashProgStepIndicator ( FlashProgram );
	FLashPutstr ( "\r\n4:Prog... " );
	SFlashProgram ( g_ucFlashType );

	//Step5:Verify
	FlashProgStepIndicator ( FlashVerify );
	FLashPutstr ( "\r\n5:Verify" );
	SFlashWrsr ( 0x0C );

	if ( !SFlashVerify ( 0, GetsFlashBufferSize() ) )
	{
		ErrorFlag |= SFlashVerifyErr;
		goto ProgEnd;
	}

	FLashPutstr ( "->OK" );

	//Step6:Exit ISP
ProgEnd:
	FlashProgStepIndicator ( ExitISP );
	ExitIspMode();
	FLashPutstr ( "\r\n6:Exit ISP\r\n" );

	WriterCounter.WDword++;
	rmPageWrite ( WRCOUNTER, & ( WriterCounter.Warray[0] ), 4 );

	mcuSetIntEn();
	return ErrorFlag;
}

BOOL EnterIspMode ( void )
{
	// 0x4D,0x53,0x54,0x41,0x52
	code BYTE enterISPdata[] = "MSTAR";
	BYTE addr = 0x20;

	// enter isp mode
	I2cWriteDatas ( enterISPdata, sizeof ( enterISPdata ), NULL, 0 );
	I2cReadDatas ( &addr, 1, &addr, 1 );

	if ( addr == 0xC0 )
	{
		return TRUE; // enter ok
	}

	else
	{
		return FALSE; // enter fail
	}
}

void ExitIspMode ( void )
{
	BYTE tdata = 0x24;

	// exit isp mode
	I2cWriteDatas ( &tdata, 1, NULL, 0 );
}

void SFlashChip_Erase ( void )
{
	//BYTE tdata[5]={SPI_WRITE,0x00,0x00,0x00,0x00};
	BYTE addr[2];

	SFlashWrsr ( 0x00 );
	SFlashWren();
	SFlashChecksr();

	addr[0] = SPI_WRITE;
	addr[1] = sFlash.CHIP_ERASE;
	I2cWriteDatas ( addr, 2, NULL, 0 );

	I2cWriteStop();
}

void SFlashWrsr ( BYTE tdata )
{
	BYTE buffer[3];

	SFlashChecksr();

	// for sst sflash (sst manufacturer id=0xBF )
	if ( sFlash.manufacturer_id == 0xBF )
	{
		buffer[0] = SPI_WRITE;
		buffer[1] = 0x50;
		I2cWriteDatas ( buffer, 2, NULL, 0 );

		I2cWriteStop();
	}

	buffer[0] = SPI_WRITE;
	buffer[1] = sFlash.WRSR;
	buffer[2] = tdata;
	I2cWriteDatas ( buffer, sizeof ( buffer ), NULL, 0 );

	I2cWriteStop();
}

void SFlashWren ( void )
{
	BYTE buffer[2];

	buffer[0] = SPI_WRITE;
	buffer[1] = sFlash.WREN;

	SFlashChecksr();
	I2cWriteDatas ( buffer, 2, NULL, 0 );

	I2cWriteStop();
}

void SFlashWrdi ( void )
{
	BYTE buffer[2];

	buffer[0] = SPI_WRITE;
	buffer[1] = sFlash.WRDI;

	SFlashChecksr();
	I2cWriteDatas ( buffer, 2, NULL, 0 );

	I2cWriteStop();
}

BOOL SFlashChecksr ( void )
{
	DWORD count = 1000;

	while ( count-- )
	{
		if ( ( SFlashRdsr() & 0x01 ) == 0x00 )
		{
			return TRUE;
		}

		MCU_Delay1us();
	}

	return FALSE;
}

BYTE SFlashRdsr ( void )
{
	BYTE buffer[2];

	buffer[0] = SPI_WRITE;
	buffer[1] = sFlash.RDSR;
	I2cWriteDatas ( buffer, 2, NULL, 0 );

	buffer[0] = SPI_READ;
	I2cReadDatas ( buffer, 1, &buffer[1], 1 );

	I2cWriteStop();

	return buffer[1];
}

#ifndef NO_BLANK_CHECK
BOOL SFlashBlanking ( DWORD address, WORD count )
{
	BYTE tdata[] = {SPI_WRITE, 0x03, 0x00, 0x00, 0x00};
	BOOL Flag;

	tdata[2] = address >> 16;
	tdata[3] = address >> 8;
	tdata[4] = address;

	tdata[1] = sFlash.READ;
	I2cWriteDatas ( tdata, sizeof ( tdata ), NULL, 0 );

	tdata[0] = SPI_READ;
	Flag = I2cReadBlank ( tdata, 1, count );

	I2cWriteStop();

	return Flag;
}
#endif

BOOL SFlashVerify ( DWORD address, WORD count )
{
	BYTE tdata[] = {SPI_WRITE, 0x03, 0x00, 0x00, 0x00};
	BOOL CheckSumOK;

	tdata[2] = address >> 16;
	tdata[3] = address >> 8;
	tdata[4] = address;

	tdata[1] = sFlash.READ;
	I2cWriteDatas ( tdata, sizeof ( tdata ), NULL, 0 );

	tdata[0] = SPI_READ;
	CheckSumOK = I2cReadVerify ( tdata, 1, count );

	I2cWriteStop();

	return CheckSumOK;
}
/*
void SFlashProgSST(AnsiString fileName)
{
 DWord count,size;
 Byte data[6];
 Byte addr[1];
 TMemoryStream *memStream=new TMemoryStream();

 memStream->LoadFromFile(fileName);

 size=memStream->Size;
 memStream->Read(sFlashBuffer,size);
 data[0]=SPI_WRITE;
 data[1]=sFlash.PG_PROG;
 data[2]=0x00; // address[23:16]
 data[3]=0x00; // address[15:8]
 data[4]=0x00; // address[7:0]
 data[5]=sFlashBuffer[0]; // first data

 SFlashWrsr(0x00);
 SFlashWren();
 SFlashChecksr();
 I2cWriteDatas(data,sizeof(data),NULL,0);

 addr[0]=SPI_STOP;
 I2cWriteDatas(addr,1,NULL,0);

 for(count=1;count<size;count++)
 {
 io->DelayUs(30);
 I2cWriteDatas(data,2,&sFlashBuffer[count],1);

 addr[0]=SPI_STOP;
 I2cWriteDatas(addr,1,NULL,0);
 }

 SFlashWrdi();
 SFlashChecksr();
 delete memStream;
}
*/
void SFlashProgramSST ( void )
{
	WORD count;
	BYTE tdata[6];

	tdata[0] = SPI_WRITE;
	tdata[1] = sFlash.PG_PROG;
	tdata[2] = 0x00; // address[23:16]
	tdata[3] = 0x00; // address[15:8]
	tdata[4] = 0x00; // address[7:0]
	tdata[5] = sFlashBuffer[0]; // first data

	SFlashWrsr ( 0x00 );
	SFlashWren();
	SFlashChecksr();

	I2cWriteDatas ( tdata, sizeof ( tdata ), NULL, 0 );
	I2cWriteStop();

	for ( count = 1; count < GetsFlashBufferSize(); count++ )
	{
		#ifdef DebugFlashData

		if ( ! ( count % 0x10 ) )
		{
			putstr ( "\r\n" );
		}

		printf ( " 0x%x", sFlashBuffer[count] );
		#endif

		{
			Pg_i2c_Start();
			Pg_i2c_SendByte ( SLAVEADDR );
			Pg_i2c_SendByte ( SPI_WRITE );
			Pg_i2c_SendByte ( sFlash.PG_PROG );
			Pg_i2c_SendByte ( sFlashBuffer[count] );
			Pg_i2c_Stop();
		}

		I2cWriteStop();
	}

	SFlashWrdi();
	SFlashChecksr();
}
void SFlashProgramPMC ( void )
{
	WORD count;
	WORD count1;
	WORD count2;

	BYTE tdata[5];
	BYTE BlockCount = 0;
	BYTE MaxBlockNum;
	BYTE k;

	MaxBlockNum = GetsFlashBufferSize() / 0x100 + 1;

	SFlashWrsr ( 0x00 );

	for ( BlockCount = 0; BlockCount < MaxBlockNum; BlockCount++ )
	{
		//SFlashWrsr(0x00);
		SFlashWren();
		SFlashChecksr();

		tdata[0] = SPI_WRITE;
		tdata[1] = sFlash.PG_PROG;
		tdata[2] = 0; // address[23:16]
		tdata[3] = ( BYTE ) ( BlockCount % 0x100 ); // address[15:8]
		tdata[4] = 0x00; // address[7:0]

		count1 = ( WORD ) ( BlockCount ) << 8;

		if ( BlockCount == MaxBlockNum - 1 )
		{
			count2 = GetsFlashBufferSize();
		}

		else
		{
			count2 = ( WORD ) ( BlockCount + 1 ) << 8;
		}

		Pg_i2c_Start();
		Pg_i2c_SendByte ( SLAVEADDR );

		for ( k = 0; k < sizeof ( tdata ); k++ )
		{
			Pg_i2c_SendByte ( tdata[k] );
		}

		for ( count = count1; count < count2; count++ )
		{
			Pg_i2c_SendByte ( sFlashBuffer[count] );
			#ifdef DebugFlashData

			if ( ! ( count % 0x10 ) )
			{
				putstr ( "\r\n" );
			}

			printf ( " 0x%x", sFlashBuffer[count] );
			#endif
		}

		I2cWriteStop();
	}

	I2cWriteDatas ( tdata, 2, NULL, 0 );
	SFlashWrdi();
	SFlashChecksr();
}

void SFlashProgram ( FlashType Flash )
{
	switch ( Flash )
	{
	case Flash_PMC512:
		SFlashProgramPMC();
		break;

	case Flash_SST512:
	default:
		SFlashProgramSST();
		break;
	}
}
//-----------------------------------------------------------

#ifndef NO_BLANK_CHECK
BOOL I2cReadBlank ( BYTE* paddr, WORD addrSize, WORD dataSize )
{
	WORD count;
	BYTE tdata;

	Pg_i2c_Start();
	Pg_i2c_SendByte ( SLAVEADDR );

	for ( count = 0; ( WORD ) count < addrSize; count++ )
	{
		Pg_i2c_SendByte ( paddr[count] );
	}

	Pg_i2c_Start();
	Pg_i2c_SendByte ( SLAVEADDR | 0x01 );

	for ( count = 0; count < dataSize - 1; count++ )
	{
		tdata = Pg_i2c_ReceiveByte ( PG_I2C_NON_ACKNOWLEDGE );

		if ( tdata != 0xFF )
		{
			return FALSE;
		}
	}

	//last BYTE
	{
		tdata = Pg_i2c_ReceiveByte ( PG_I2C_ACKNOWLEDGE );

		if ( tdata != 0xFF )
		{
			return FALSE;
		}
	}

	Pg_i2c_Stop();

	return TRUE;
}
#endif


BOOL I2cReadVerify ( BYTE* paddr, WORD addrSize, WORD dataSize )
{
	WORD count;
	BYTE tdata;
	BOOL ChkSum = TRUE;

	Pg_i2c_Start();
	Pg_i2c_SendByte ( SLAVEADDR );

	for ( count = 0; ( WORD ) count < addrSize; count++ )
	{
		Pg_i2c_SendByte ( paddr[count] );
	}

	Pg_i2c_Start();
	Pg_i2c_SendByte ( SLAVEADDR | 0x01 );

	for ( count = 0; count < dataSize - 1; count++ )
	{
		tdata = Pg_i2c_ReceiveByte ( 1 );

		#ifdef DebugFlashData

		if ( ! ( count % 0x10 ) )
		{
			putstr ( "\r\n" );
		}

		printf ( " 0x%x", tdata );
		#endif

		if ( tdata != sFlashBuffer[count] )
		{
			ChkSum = FALSE;
			break;
		}
	}

	//last byte
	{
		tdata = Pg_i2c_ReceiveByte ( 0 );

		#ifdef DebugFlashData

		if ( ! ( count % 0x10 ) )
		{
			putstr ( "\r\n" );
		}

		printf ( " 0x%x", tdata );
		#endif

		if ( tdata != sFlashBuffer[count] )
		{
			ChkSum = FALSE;
		}
	}

	Pg_i2c_Stop();

	return ChkSum;
}

void I2cReadDatas ( BYTE* paddr, BYTE addrSize, BYTE* pdatabuf, BYTE dataSize )
{
	BYTE k;

	Pg_i2c_Start();
	Pg_i2c_SendByte ( SLAVEADDR );

	for ( k = 0; k < addrSize; k++ )
	{
		Pg_i2c_SendByte ( paddr[k] );
	}

	Pg_i2c_Start();
	Pg_i2c_SendByte ( SLAVEADDR | 0x01 );

	for ( k = 0; k < dataSize - 1; k++ )
	{
		pdatabuf[k] = Pg_i2c_ReceiveByte ( 1 );
	}

	//last byte
	pdatabuf[k] = Pg_i2c_ReceiveByte ( 0 );

	Pg_i2c_Stop();
}

void I2cWriteDatas ( BYTE* paddr, BYTE addrSize, BYTE* pdatabuf, BYTE dataSize )
{
	BYTE k;

	Pg_i2c_Start();

	Pg_i2c_SendByte ( SLAVEADDR );

	for ( k = 0; k < addrSize; k++ )
	{
		Pg_i2c_SendByte ( paddr[k] );
	}

	for ( k = 0; k < dataSize; k++ )
	{
		Pg_i2c_SendByte ( pdatabuf[k] );
	}

	Pg_i2c_Stop();
}

void I2cWriteStop ( void )
{
	Pg_i2c_Start();
	Pg_i2c_SendByte ( SLAVEADDR );
	Pg_i2c_SendByte ( SPI_STOP );
	Pg_i2c_Stop();
}
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void Pg_i2cSetSCL_Chk ( bit bSet )
{
	BYTE ucDummy; // loop dummy

	Pg_i2cSetSCL ( bSet ); // set SCL pin

	if ( bSet == _HIGH ) // if set pin high
	{
		ucDummy = PG_I2C_CHECK_PIN_DUMMY; // initialize dummy

		while ( ( Pg_i2cSCL_PIN_STATUS() == _LOW ) && ( ucDummy-- ) )
			; // check SCL pull high
	}

}

// Set I2C SDA pin high/low
//
// Arguments: bSet - high/low bit
void Pg_i2cSetSDA_Chk ( bit bSet )
{
	BYTE ucDummy; // loop dummy

	Pg_i2cSetSDA ( bSet ); // set SDA pin

	if ( bSet == _HIGH ) // if set pin high
	{
		ucDummy = PG_I2C_CHECK_PIN_DUMMY; // initialize dummy

		while ( ( Pg_i2cSDA_PIN_STATUS() == _LOW ) && ( ucDummy-- ) )
			; // check SDA pull high
	}

}

void Pg_i2c_Start ( void )
{
	Pg_i2cSetSDA_Chk ( _HIGH );
	Pg_i2cSetSCL_Chk ( _HIGH );
	Pg_i2cSetSDA ( _LOW );
	Pg_i2cSetSCL ( _LOW );
}
// I2C stop signal.
// <comment>
// ____________
// SCL _______/
// _________
// SDA __________/
void Pg_i2c_Stop ( void )
{
	Pg_i2cSetSCL ( _LOW );
	Pg_i2cSetSDA ( _LOW );
	Pg_i2cSetSCL ( _HIGH );
	Pg_i2cSetSDA ( _HIGH );
}

BYTE Pg_i2c_ReceiveByte ( BOOL bAck )
{
	BYTE ucReceive = 0;
	BYTE ucMask = 0x80;


	while ( ucMask )
	{
		Pg_i2cSetSDA ( _HIGH );
		Pg_i2cSetSCL ( _HIGH );

		if ( Pg_i2cSDA_PIN_STATUS() == _HIGH )
		{
			ucReceive |= ucMask;
		}

		Pg_i2cSetSCL ( _LOW );

		ucMask >>= 1; // next
	} // while

	if ( bAck ) // acknowledge
	{
		Pg_i2cSetSDA_Chk ( PG_I2C_ACKNOWLEDGE );
	}

	else // non-acknowledge
	{
		Pg_i2cSetSDA_Chk ( PG_I2C_NON_ACKNOWLEDGE );
	}

	Pg_i2cSetSCL ( _HIGH );
	Pg_i2cSetSCL ( _LOW );


	return ucReceive;
}

bit Pg_i2c_SendByte ( BYTE ucVal )
{
	BYTE ucMask = 0x80;
	bit bAck; // acknowledge bit


	while ( ucMask )
	{
		if ( ucVal & ucMask )
		{
			Pg_i2cSetSDA ( _HIGH );
		}

		else
		{
			Pg_i2cSetSDA ( _LOW );
		}

		Pg_i2cSetSCL ( _HIGH );
		Pg_i2cSetSCL ( _LOW );

		ucMask >>= 1; // next
	} // while

	// recieve acknowledge
	Pg_i2cSetSDA ( _HIGH );
	Pg_i2cSetSCL ( _HIGH );
	bAck = Pg_i2cSDA_PIN_STATUS(); // recieve acknowlege
	Pg_i2cSetSCL ( _LOW );


	return ( bAck );
}

