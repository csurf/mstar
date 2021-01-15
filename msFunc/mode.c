#define _MODE_C_

#include "types.h"
#include "board.h"
#include "mode.h"
#include "ms_reg.h"
#include "panel.h"

#define HFreq_tolerance 10 // 1 KHz
#define VFreq_tolerance 30 // 3 Hz

InputResolutionType code tStandardModeResolution[] =
{
	{720, 480}, //Res_720x480
	{720, 576}, //Res_720x576
	{1280, 480}, //Res_1280x480
	{1600, 600}, //Res_1600x600
	{1440, 480}, //Res_1440x480
	{1440, 576}, //Res_1440x576
	{960, 1080}, //Res_960x1080
};
//for display info
BYTE code StandardResolutionIndexText[Max_Res][11] =
{
	//123456789012345678901234567890

	{"720X480"},
	{"720X576"},
	{"640X480"}, //Res_1280x480
	{"800X600"}, //Res_1600x600
	{"720X480"}, //Res_1440x480
	{"720X576"}, //Res_1440x576
	{"1920X1080"}, //Res_960x1080
};

InputModeType code tStandardMode[] =
{
	// 720x576i 50Hz (YCbCr)//29
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn | bInterlaceMode | bVideoMode, // Flags
		#if(PanelWidth <= 720)
		Res_720x576, // ResIndex
		#else
		Res_1440x576, // ResIndex
		#endif
		156, 500, // HFreq, VFreq
		#if(PanelWidth <= 720)
		864, 625, // HTotal, VTotal
		#else
		( 864 + 80 ) * 2, 625, // HTotal, VTotal
		#endif
		200, 49, // HStart, VStart
		HFreq_tolerance, VFreq_tolerance, // HSyncTolerence // VSyncTolerence
	},

	// 720x480i 60Hz (YCbCr) //30
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn | bInterlaceMode | bVideoMode, // Flags
		#if(PanelWidth <= 720)
		Res_720x480, // ResIndex
		#else
		Res_1440x480, // ResIndex
		#endif
		156, 600, // HFreq, VFreq
		#if(PanelWidth <= 720)
		858, 525, // HTotal, VTotal
		#else
		( 858 + 80 ) * 2, 525, // HTotal, VTotal
		#endif
		169, 43,//37, // HStart, VStart
		HFreq_tolerance, VFreq_tolerance, // HSyncTolerence // VSyncTolerence
	},

	// 720x576p 50Hz (YPbPr) //31
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn | bVideoMode, // Flags
		#if(PanelWidth <= 720)
		Res_720x576, // ResIndex
		#else
		Res_1440x576, // ResIndex
		#endif
		315, 500, // HFreq, VFreq
		#if(PanelWidth <= 720)
		864, 625, // HTotal, VTotal
		#else
		( 864 + 80 ) * 2, 625, // HTotal, VTotal
		#endif
		200, 49, // HStart, VStart
		HFreq_tolerance, VFreq_tolerance, // HSyncTolerence // VSyncTolerence
	},

	// 720x480p 60Hz (YPbPr) //32
	{
		SyncHpVp | SyncHpVn | SyncHnVp | SyncHnVn | bVideoMode, // Flags
		#if(PanelWidth <= 720)
		Res_720x480, // ResIndex
		#else
		Res_1440x480, // ResIndex
		#endif
		315, 600, // HFreq, VFreq
		#if(PanelWidth <= 720)
		858, 525, // HTotal, VTotal
		#else
		( 858 + 80 ) * 2, 525, // HTotal, VTotal
		#endif
		169, 43, // HStart, VStart
		HFreq_tolerance, VFreq_tolerance, // HSyncTolerence // VSyncTolerence
	},

	//=-===IMPORTANT DON'T DELETE IT, OR IT WILL CAUSE LOOP INIFINITE//40
	{
		0, // Flags
		0, // ResIndex
		0, 0, // HFreq, VFreq
		0, 0, // HTotal, VTotal
		0, 0, // HStart, VStart
		0, 0, // HSyncTolerence // VSyncTolerence
	}
};
