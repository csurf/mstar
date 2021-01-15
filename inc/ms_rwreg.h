#ifndef _MSRWREG_H_
#define _MSRWREG_H_

#ifdef _MSRWREG_C_
	#define _MSRWREGDEC_
#else
	#define _MSRWREGDEC_ extern
#endif


_MSRWREGDEC_ void msWriteByte ( BYTE addr, BYTE value );
_MSRWREGDEC_ void msWriteWord ( BYTE addr, WORD value );
_MSRWREGDEC_ BYTE msReadByte ( BYTE addr );
_MSRWREGDEC_ void msWriteDDRByte ( BYTE addr, BYTE value );
_MSRWREGDEC_ WORD msReadWord ( BYTE addr );
_MSRWREGDEC_ void msWriteTBL ( BYTE addr, BYTE* tbl, WORD count, BYTE inc );
_MSRWREGDEC_ void msWriteRegsTbl ( RegUnitType* pTable );
_MSRWREGDEC_ void msLoadModeIndexTBL ( DynamicLoadModeTblType* pTable );
_MSRWREGDEC_ void msWriteByteMask ( BYTE ucReg, BYTE ucValue, BYTE ucMask );
_MSRWREGDEC_ void msWriteByte_Bank_BackupBank ( BYTE ucBank, BYTE ucReg, BYTE ucData );
//_MSRWREGDEC_ void msWriteByteMask_Bank_BackupBank(BYTE ucBank, BYTE ucReg, BYTE ucValue, BYTE ucMask);
_MSRWREGDEC_ void msWriteBit ( BYTE ucReg, BOOL bBit, BYTE ucBitPos );
_MSRWREGDEC_ void msWrite3Bytes ( BYTE ucReg, DWORD dwValue );
#if (SCALER_TYPE == MARIA9)//RegADDR_16bit access
	_MSRWREGDEC_ void msWrite2BytesMask_16bitADDR ( BYTE ucReg_16bitmode, WORD uwValue, WORD uwMask );
#endif

#endif
