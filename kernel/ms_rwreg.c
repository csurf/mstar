#define _MSRWREG_C_

#include <INTRINS.H>
#include "types.h"
#include "board.h"
#include "global.h"
#include "ms_reg.h"
#include "misc.h"
#include "debug.h"

extern void Delay4us ( void );

#define Delay1us() _nop_()//;_nop_()

#define MS_REG(addr) (((unsigned char xdata*)0)[addr])

BYTE msReadByte ( BYTE addr )
{
	//return MS_REG(addr);
	return * ( ( BYTE pdata* ) addr );
}

WORD msReadWord ( BYTE addr )
{
	WORD value;
	value = msReadByte ( addr );
	value = ( value << 8 ) | msReadByte ( addr - 1 );
	return value;
}

void msWriteByte ( BYTE addr, BYTE value )
{
	//MS_REG(addr)=value;
	* ( ( BYTE pdata* ) addr ) = value;
}

void msWriteWord ( BYTE addr, WORD value )
{
	msWriteByte ( addr - 1, value & 0xFF );
	msWriteByte ( addr, value >> 8 );
}

void msWriteByte_Bank_BackupBank ( BYTE ucBank, BYTE ucReg, BYTE ucData )
{
	BYTE ucBackupBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, ucBank );
	msWriteByte ( ucReg, ucData );

	msWriteByte ( BK0_00_REGBK, ucBackupBank );
}

/*
void msWriteByteMask_Bank_BackupBank(BYTE ucBank, BYTE ucReg, BYTE ucValue, BYTE ucMask)
{
 BYTE ucBackupBank = msReadByte( BK0_00_REGBK);
 BYTE uc;

 msWriteByte( BK0_00_REGBK, ucBank );

 uc = msReadByte(ucReg) & (~ucMask);
 msWriteByte( ucReg, ( uc | (ucValue & ucMask)) );

 msWriteByte( BK0_00_REGBK, ucBackupBank );
}
*/

void msWriteTBL ( BYTE addr, BYTE* tbl, WORD count, BYTE inc )
{
	while ( count-- )
	{
		msWriteByte ( addr, * ( tbl++ ) );
	}

	inc = 0;
}

void msWriteRegsTbl ( RegUnitType* pTable )
{
	BYTE ucIndex; // register index

	while ( 1 )
	{
		ucIndex = pTable->Reg; // get register index

		if ( ucIndex == _END_OF_TBL_ ) // check end of table
		{
			break;
		}

		msWriteByte ( ucIndex, pTable->Value ); // write register
		pTable++; // next
	} // while
}

void msLoadModeIndexTBL ( DynamicLoadModeTblType* pTable )
{
	BYTE ucBank;
	RegUnitType* RegType;
	RegType = pTable->PtrRegTbl;

	ucBank = msReadByte ( BK0_00_REGBK );

	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );

	while ( 1 )
	{
		if ( pTable->InputType == _END_OF_TBL_ )
		{
			break;
		}

		if ( ( ( 1 << g_VideoSetting.InputType ) & ( pTable->InputType ) ) \
			&& ( g_ucSrcModeIndex == pTable->ModeIndex ) )
		{
			while ( 1 )
			{
				if ( RegType->Reg == _END_OF_TBL_ ) // check end of table
				{
					break;
				}

				msWriteByte ( RegType->Reg, RegType->Value ); // write register
				RegType++; // next
			}
		}

		pTable++;
		RegType = pTable->PtrRegTbl;
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

void msWriteByteMask ( BYTE ucReg, BYTE ucValue, BYTE ucMask )
{
	BYTE uc;

	uc = msReadByte ( ucReg ) & ( ~ucMask );
	msWriteByte ( ucReg, ( uc | ( ucValue & ucMask ) ) );
}

/*
void msWriteByte_Bank( BYTE ucBank, BYTE ucReg, BYTE ucData )
{
 msWriteByte( BK0_00_REGBK, ucBank );
 msWriteByte( ucReg, ucData );
}
*/

void msWriteBit ( BYTE ucReg, BOOL bBit, BYTE ucBitPos )
{
	BYTE ucValue;

	ucValue = msReadByte ( ucReg );

	if ( bBit )
	{
		ucValue = ucValue | ucBitPos;
	}

	else
	{
		ucValue = ucValue & ( ~ucBitPos );
	}

	msWriteByte ( ucReg, ucValue );
}

void msWrite3Bytes ( BYTE ucReg, DWORD dwValue )
{
	msWriteByte ( ucReg, ( BYTE ) ( dwValue / 0x10000 ) );
	msWriteByte ( ucReg - 1, ( BYTE ) ( dwValue / 0x100 ) );
	msWriteByte ( ucReg - 2, ( BYTE ) ( dwValue ) );
}

#if ( SCALER_TYPE == MARIA9 )//RegADDR_16bit access
void msWrite2BytesMask_16bitADDR ( BYTE ucReg_16bitmode, WORD uwValue, WORD uwMask )
{
	BYTE uc, ucValueL, ucValueH, ucMaskL, ucMaskH;

	ucValueL = ( BYTE ) uwValue;
	ucValueH = WORD_HIGH_BYTE ( uwValue );
	ucMaskL = ( BYTE ) uwMask;
	ucMaskH = WORD_HIGH_BYTE ( uwMask );

	uc = msReadByte ( ucReg_16bitmode ) & ( ~ucMaskL );
	msWriteByte ( ucReg_16bitmode, ( uc | ( ucValueL & ucMaskL ) ) );

	uc = msReadByte ( ucReg_16bitmode + 1 ) & ( ~ucMaskH );
	msWriteByte ( ucReg_16bitmode + 1, ( uc | ( ucValueH & ucMaskH ) ) );
}
#endif

