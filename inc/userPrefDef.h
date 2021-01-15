#include <STDDEF.H>

typedef WORD TypCheckSum;

typedef struct
{
	BYTE ucVersion;
	BYTE MonitorFlag;
	BYTE OsdHStart;
	BYTE OsdVStart;
	BYTE OsdTime;
	BYTE InputType;
	BYTE VideoBrightness;
	BYTE VideoContrast;
	BYTE VideoSaturation;
	BYTE VideoHue;
	BYTE VideoColorSys;
	WORD Backlight;
	BYTE Scaling;
	BYTE VcomDC;
	BYTE videoAGC;
	BYTE Checksum;
} VideoSettingType ;

typedef struct
{
	WORD HTotal;
	WORD HStart;
	WORD VStart;
	WORD AutoHStart;
	WORD AutoVStart;
	BYTE Phase;
	BYTE AutoTimes;
	BYTE checksum;
} ModeSettingType;

typedef struct
{
	WORD HorFreq;
	WORD VerFreq;
	BYTE Flags;
} ModeInfoType;

typedef enum
{
	Scaling_Full,
	Scaling_4_3,
	Scaling_NUMS
} ScalingType;

typedef struct _NonLinearCurveType
{
	BYTE X0;
	BYTE X1;
	BYTE X2;
	BYTE X3;
	BYTE X4;
} NonLinearCurveType;

typedef enum
{
	CHROMA_NTSC,
	CHROMA_PAL,
	CHROMA_NUMS
} EnuCChromaSystem;

typedef enum
{
	MARIA1 = 11,
	MARIA2 = 21,
	MARIA2_B = 22,
	MARIA2_D = 24,
	MARIA2_E = 25,
	MARIA2_F = 25,
	MARIA2_G = 26,
	MARIA3 = 31,
	MARIA_Type_NUMS
} MARIAScalerType;

typedef struct
{
	BYTE VideoHStart; // H capture start
	BYTE VideoVStart; // V capture start
	WORD HRange; // H capture range
	WORD VRange; // V capture range
} _CaptureVideoWinType;

typedef struct
{
	BYTE SVideoHStart; // H capture start
	BYTE SVideoVStart; // V capture start
} _CaptureSvideoWinStartType;

#define DoAFCFlag _BIT3
#define ColorSysMask (_BIT4|_BIT5|_BIT6)

#define ModeCSValue 0x91
#define VideoVersion 0x57
#define BoardVersion 0x45

//==========================================================================

#define NumberOfMode 50
#define UserModeNumber 5
#define NVRamAddress_Base 0

#define VideoSettingSize sizeof(VideoSettingType)
#define ModeSettingSize sizeof(ModeSettingType)
#define ModeInfoSize sizeof(ModeInfoType)
#define CheckSumSize 1

typedef enum
{
	BoardChkSumAddr = NVRamAddress_Base,
	VideoSettingAddr = NVRamAddress_Base + 0x10,
} NVRamAddress;

#define nvrVideoAddr(member) VideoSettingAddr+offsetof(VideoSettingType, member)
