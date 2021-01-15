#ifndef _NVRAM_H_
#define _NVRAM_H_

#ifdef _NVRAM_C_
	#define _NVRAMDEC_
#else
	#define _NVRAMDEC_ extern
#endif

_NVRAMDEC_ void NVRam_WriteWord ( WORD addr, WORD value );
_NVRAMDEC_ void NVRam_ReadByte ( WORD addr, BYTE* value );
_NVRAMDEC_ void NVRam_WriteTbl ( WORD addr, BYTE* buffer, WORD count );
_NVRAMDEC_ void NVRam_ReadTbl ( WORD addr, BYTE* buffer, WORD count );
_NVRAMDEC_ void rmBurstWriteBytes ( WORD wIndex, BYTE* pBuf, WORD ucBufLen );

#if RM_EEPROM_TYPE>=RM_TYPE_SST512
	_NVRAMDEC_ void mstSaveDisplayData ( WORD address );
	_NVRAMDEC_ void mstLoadDisplayData ( WORD address );
#endif

#if RM_EEPROM_TYPE < RM_TYPE_SST512
	_NVRAMDEC_ void NVRam_WriteByte ( WORD addr, BYTE value );
#endif
#endif
