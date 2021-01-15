#ifndef __DSP_RW_H
#define __DSP_RW_H

#include "DSP_maria.h"

//#include "typedef.h"

#define msRegs ((unsigned char volatile pdata *)0x0000)
#define msWriteByte(adr,val) (msRegs[(adr)]=(val))
#define msReadByte(adr) (msRegs[(adr)])

#define DSP_RW_USE_FUNCTION
#ifdef DSP_RW_USE_FUNCTION

BYTE msReadDspReg ( BYTE ucAdr );
void msWriteDspReg ( BYTE ucAdr, BYTE ucData );
WORD msReadDspRegW ( BYTE ucAdr );
void msWriteDspRegW ( BYTE ucAdr, WORD wData );

#define mReadDspReg(Adr, Data) { Data=msReadDspReg(Adr); }
#define mWriteDspReg(Adr, Data) { msWriteDspReg(Adr, Data); }
//#define mReadDspRegW(Adr, Data) { Data.w=msReadDspRegW(Adr); }
#define mWriteDspRegW(Adr, Data) { msWriteDspRegW(Adr, Data); }

BYTE msReadDspReg_Int ( BYTE ucAdr );
void msWriteDspReg_Int ( BYTE ucAdr, BYTE ucData );
WORD msReadDspRegW_Int ( BYTE ucAdr );
#define mReadDspReg_Int(Adr, Data) { Data=msReadDspReg_Int(Adr); }
#define mWriteDspReg_Int(Adr, Data) { msWriteDspReg_Int(Adr, Data); }
#define mReadDspRegW_Int(Adr, Data) { Data.w=msReadDspRegW_Int(Adr);}

#else

#define mReadDspReg(Adr, Data) {\
		msWriteByte( 0x07, Adr );\
		Data=msReadByte(0x09);\
	}
#define mWriteDspReg(Adr, Data) {\
		msWriteByte( 0x07, Adr );\
		msWriteByte( 0x08, Data );\
	}
#define mReadDspRegW(Adr, Data) {\
		mReadDspReg( Adr, Data.b[1] );\
		mReadDspReg( Adr+1, Data.b[0] );\
	}
#define mWriteDspRegW(Adr, Data) {\
		mWriteDspReg(Adr, Data);\
		mWriteDspReg(Adr+1, Data>>8);\
	}

#endif

#endif
