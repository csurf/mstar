
typedef signed char Schar;
typedef signed int Sint;
typedef signed long Slong;

typedef bit BIT;
typedef unsigned char UCHAR;
typedef unsigned char BYTE;
typedef unsigned int UINT;
typedef unsigned int WORD;
typedef unsigned long ULONG;
typedef unsigned long DWORD;

typedef unsigned char* PUCHAR;
typedef BYTE* PBYTE;
typedef UINT* PUINT;
typedef WORD* PWORD;
typedef ULONG* PULONG;
typedef DWORD* PDWORD;
typedef void* PVOID;

#define DATA data
#define BDATA bdata
#define IDATA idata
#define PDATA pdata
#define XDATA xdata
#define RDATA code

#define CBYTE ((unsigned char volatile code *) 0)
#define DBYTE ((unsigned char volatile data *) 0)
#define PBYTE ((unsigned char volatile pdata *) 0)
#define XBYTE ((unsigned char volatile xdata *) 0)
#define IBYTE ((unsigned char volatile idata *) 0)

// Macro
#define HIBYTE_REF(addr) (*((BYTE *) & (addr)))
#define LOBYTE_REF(addr) (*((BYTE *) & (addr + 1)))
#define MAKEWORD(value1, value2) (((WORD)(value1)) * 0x100) + (value2)
#define MAKEUINT(value1, value2) (((WORD)(value1)) * 0x100) + (value2)
#define H2BYTE(value) ((BYTE)((value) / 0x10000))
#define HIBYTE(value) ((BYTE)((value) / 0x100))
#define LOBYTE(value) ((BYTE)(value))

#define HINIBBLE(value) ((value) / 0x10)
#define LONIBBLE(value) ((value) & 0x0f)

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a ,b) (((a) < (b)) ? (a) : (b))

// Others
#define _ENABLE 1
#define _DISABLE 0

typedef enum BOOL_enum
{
	FALSE,
	TRUE
} BOOL;

#define _HIGH 1
#define _LOW 0

typedef union _HiLo
{
	BYTE b[2];
	WORD w;
} HLdata;
typedef union _HiLoDW
{
	BYTE b[4];
	WORD w[2];
	DWORD d;
} HLdw;
#define H 0
#define L 1

#define I2C_ACKNOWLEDGE _LOW
#define I2C_NON_ACKNOWLEDGE _HIGH

#define _BIT0 0x0001
#define _BIT1 0x0002
#define _BIT2 0x0004
#define _BIT3 0x0008
#define _BIT4 0x0010
#define _BIT5 0x0020
#define _BIT6 0x0040
#define _BIT7 0x0080
#define _BIT8 0x0100
#define _BIT9 0x0200
#define _BIT10 0x0400
#define _BIT11 0x0800
#define _BIT12 0x1000
#define _BIT13 0x2000
#define _BIT14 0x4000
#define _BIT15 0x8000

#define _bit0_(val) ((bit)(val & _BIT0))
#define _bit1_(val) ((bit)(val & _BIT1))
#define _bit2_(val) ((bit)(val & _BIT2))
#define _bit3_(val) ((bit)(val & _BIT3))
#define _bit4_(val) ((bit)(val & _BIT4))
#define _bit5_(val) ((bit)(val & _BIT5))
#define _bit6_(val) ((bit)(val & _BIT6))
#define _bit7_(val) ((bit)(val & _BIT7))
#define _bit8_(val) ((bit)(val & _BIT8))
#define _bit9_(val) ((bit)(val & _BIT9))
#define _bit10_(val) ((bit)(val & _BIT10))
#define _bit11_(val) ((bit)(val & _BIT11))
#define _bit12_(val) ((bit)(val & _BIT12))
#define _bit13_(val) ((bit)(val & _BIT13))
#define _bit14_(val) ((bit)(val & _BIT14))
#define _bit15_(val) ((bit)(val & _BIT15))

