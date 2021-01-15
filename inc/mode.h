#ifndef _MODE_H_
#define _MODE_H_

#ifdef _MODE_C_
	#define _MODEDEC_
#else
	#define _MODEDEC_ extern
#endif

#define bVSyncNegative _BIT0
#define bHSyncNegative _BIT1
#define bHSyncLoss _BIT2
#define bVSyncLoss _BIT3
#define bInterlaceMode _BIT4
#define bUnsupportMode _BIT5
#define bUserMode _BIT6
#define bVideoMode _BIT7

#if(SCALER_TYPE == MARIA9)
typedef enum
{
	PORT_SV0 = _BIT6 | _BIT1,
	PORT_SV1 = _BIT6 | _BIT4 | _BIT1 | _BIT0,

	PORT_CVBS_SV0Y = _BIT1,
	PORT_CVBS_SV0C = _BIT2,
	PORT_CVBS_SV1Y = _BIT1 | _BIT0,
	PORT_CVBS_SV1C = _BIT2 | _BIT0,

} InputPort_BK1_2F_Type;
#else
typedef enum
{
	PORT_CVBS1 = 0,
	PORT_CVBS2 = _BIT3,
	PORT_SV1 = _BIT4,
	PORT_SV2 = _BIT3 | _BIT4,

	PORT_CVBS_SV1Y = _BIT4,
	PORT_CVBS_SV2Y = _BIT3 | _BIT4,
	PORT_CVBS_SV1C = 0,
	PORT_CVBS_SV2C = _BIT3,

	PORT_YPbPr = _BIT3 | _BIT5,
	PORT_VGA = _BIT5,
} InputPort_BK1_2F_Type;
#endif

// HpVp->3, HpVn->2, HnVp->1, HnVn->0
/************************************************/
#define SyncHpVp _BIT3 // Sync Polarity
#define SyncHpVn _BIT2
#define SyncHnVp _BIT1
#define SyncHnVn _BIT0

typedef enum
{
	Full,
	LetterBox,
	ScalingEnd
} ModeScaling;

typedef enum
{
	Res_720x480,
	Res_720x576,
	Res_1280x480,
	Res_1600x600,
	Res_1440x480,
	Res_1440x576,
	Res_960x1080,
	Max_Res,
} ResolutionType;

typedef enum
{
	MD_720x480_60I,
	MD_720x576_50I,
	MD_720x480_60P,
	MD_720x576_50P,
	MD_1280x720_60P,
	MD_1280x720_50P,

	MD_1920x1080_60I,
	MD_1920x1080_50I,
	MD_1920x1080_60P,
	MD_1920x1080_50P,
	MD_FreeRun,
	MD_TVsnow,
	MD_MAX_INDEX,
} ModeType;

typedef struct
{
	BYTE fFlags;
	WORD HPeriod;
	WORD VTotal;
	BYTE ModeIndex;
} InputTimingType;

typedef struct
{
	WORD DispWidth;
	WORD DispHeight;
} InputResolutionType;

typedef struct
{
	BYTE Reg;
	BYTE Value;
} RegUnitType;

typedef struct
{
	BYTE Flags;
	ResolutionType ResIndex;
	WORD HFreq;
	WORD VFreq;
	WORD HTotal;
	WORD VTotal;
	WORD HStart;
	WORD VStart;
	BYTE HSyncTolerence;
	BYTE VSyncTolerence;
} InputModeType;


typedef struct
{
	BYTE InputType;
	BYTE ModeIndex;
	RegUnitType* PtrRegTbl;
} DynamicLoadModeTblType;

#define _END_OF_TBL_ 255

#endif
