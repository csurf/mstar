#define MARIA2

#include "DSP_maria.h"
#include "DSP_rw.h"
#include "board.h"

#include "maria2_DSP.h"

bit g_bMaria2_100pin;

extern WORD XDATA g_wPreVpos;
extern WORD XDATA g_wFieldLineCuntPre;
extern XDATA WORD g_wFieldLineCunt;
extern WORD XDATA g_wField1LinesPre;
extern WORD XDATA g_wField2LinesPre;
extern XDATA WORD g_wField1Lines;
extern XDATA WORD g_wField2Lines;
extern BYTE xdata g_ucCuntPhaseV;
extern BYTE xdata g_ucCuntPhaseField;
extern BYTE xdata g_ucVstartTh;
extern BYTE idata g_ucUpdateVdebounce;
extern BYTE xdata g_ucVcrPauseCunt;
extern WORD xdata g_wVtotal[3];
extern WORD xdata g_wVtotalLatch;
extern WORD xdata g_wDetPhaseV[4];
extern BYTE xdata g_ucStableCunt;
extern BYTE xdata g_wVstartCnt;
extern BYTE xdata g_ucVstartTh;
extern BYTE xdata g_ucVcunt;
extern WORD xdata g_wStrbVcuntPre;
extern WORD xdata g_wStrbVcuntPreBak[2];
extern BYTE idata g_ucDebunceFieldErr;
extern BYTE xdata g_ucInterlaceCunt;
extern BYTE idata g_ucDSP_Ctl;
extern xdata BOOL g_bDSP_PhaseChange;
extern xdata BOOL g_bDSP_SupportTV;
extern WORD xdata g_wDefaultVTotal;

extern BYTE bdata V_Flag;
extern bit bVsyncReady;
extern bit bNonInter;
extern bit bVuseHW;

extern WORD xdata g_wVSyncHTotal;
extern bit g_bVdDsp_StopInt;

BYTE* VD_DSP_GetVersion ( void )
{
	return "M2 20070504"; // Modify checking bonding
}

void VD_VSync_SetHTotal ( WORD wHTotal )
{
	g_wVSyncHTotal = wHTotal;
}

// Default 656_setting:
#define DSP_656_F_TGL_1_VAL 0x08
#define DSP_656_V_SET_1_VAL 0x10
#define DSP_656_V_CLR_1_VAL 0x12
#define DSP_656_F_TGL_2_VAL 0x08
#define DSP_656_V_SET_2_VAL 0x10
#define DSP_656_V_CLR_2_VAL 0x12

xdata BYTE g_ucVSync656FieldTgl;
xdata BYTE g_ucVSync656VSet;
xdata BYTE g_ucVSync656VClr;

void VD_Vsync_Set656VPosition ( BYTE ucFieldTgl, BYTE ucVSet, BYTE ucVClr )
{
	g_ucVSync656FieldTgl = ucFieldTgl;
	g_ucVSync656VSet = ucVSet;
	g_ucVSync656VClr = ucVClr;
}

void SetVthreshold ( BYTE ucTh )
{
	g_ucVstartTh = ucTh;
}

//*********************************************************
// InitVSYNC :
//*********************************************************
void initVSYNC ( WORD wDefaultVTotal )
{
	g_wVtotalLatch = wDefaultVTotal;
	g_wVtotal[0] = g_wVtotal[1] = g_wVtotal[2] = wDefaultVTotal;

	V_Flag = 0;
	g_ucUpdateVdebounce = 0;
	//Set656VS();

	// mWriteDspRegW(0x8C, 0x10 - g_ucVsyncStart); // DSP_656_V_SET_1
	// mWriteDspRegW(0x86, 0x08 - g_ucVsyncStart); // DSP_656_F_TGL_1
	// mWriteDspRegW(0x90, 0x12 - g_ucVsyncStart); // DSP_656_V_CLR_1
	// mWriteDspRegW(0x8E, 0x10 - g_ucVsyncStart); // DSP_656_V_SET_2
	// mWriteDspRegW(0x88, 0x08 - g_ucVsyncStart); // DSP_656_F_TGL_2
	// mWriteDspRegW(0x92, 0x12 - g_ucVsyncStart); // DSP_656_V_CLR_2
	
	mWriteDspRegW ( 0x86, g_ucVSync656FieldTgl ); // DSP_656_F_TGL_1
	mWriteDspRegW ( 0x8C, g_ucVSync656VSet ); // DSP_656_V_SET_1
	mWriteDspRegW ( 0x90, g_ucVSync656VClr ); // DSP_656_V_CLR_1
	mWriteDspRegW ( 0x88, g_ucVSync656FieldTgl ); // DSP_656_F_TGL_2
	mWriteDspRegW ( 0x8E, g_ucVSync656VSet ); // DSP_656_V_SET_2
	mWriteDspRegW ( 0x92, g_ucVSync656VClr ); // DSP_656_V_CLR_2

	mWriteDspRegW ( 0x0e, 0x00f4 );
	mWriteDspRegW ( V_Total, wDefaultVTotal );
	g_ucVcrPauseCunt = 0;
	g_wField1Lines = 0;
	g_wField2Lines = 0;
	bVsyncReady = 0;
	bNonInter = 0;
	g_ucUpdateVdebounce = 0;
	mWriteDspRegW ( VPLL_MODE2, 0x0347 );

	g_ucStableCunt = 0;
	g_ucCuntPhaseField = 0;
	g_ucCuntPhaseV = 0;
	g_ucInterlaceCunt = 0;
	g_wVstartCnt = 0;
	g_ucVcunt = 0;
	bVuseHW = 0;
	SetVthreshold ( 0xff );
}

void VD_DSP_Init ( void )
{
	g_bVdDsp_StopInt = 1;
	g_ucDSP_Ctl = 0;

	g_bDSP_PhaseChange = 0;

	s_ucWriteIdx = 0;
	s_ucReadIdx = 0;

	#if ( MST_CHIP == MST720A )
	g_bMaria2_100pin = 1;
	#else
	g_bMaria2_100pin = 0;
	#endif

	g_bDSP_SupportTV = 1;
	// g_ucVsyncStart = 0;

	VD_Vsync_Set656VPosition ( DSP_656_F_TGL_1_VAL, DSP_656_V_SET_1_VAL, DSP_656_V_CLR_1_VAL );

	VD_DSP_GetVersion();
	VD_VSync_SetHTotal ( 858 );
}
void VD_DSP_Ctl ( BYTE ucCtl, WORD wDefaultVTotal )
{
	BYTE ucBank;
	BYTE ucBk2_07;

	g_bVdDsp_StopInt = 1; // function protect

	g_ucDSP_Ctl = ucCtl;

	ucBank = msReadByte ( BK0_00 ); // Backup original bank
	msWriteByte ( BK0_00, REG_BANK2_VD );
	ucBk2_07 = msReadByte ( BK2_07 );


	if ( ucCtl & VD_DSP_CTL_ENABLE )
	{
		#ifdef MARIA2
		mWriteDspRegW ( DSP_10, msReadDspRegW ( DSP_10 ) | 0x0001 ); // SW v sycn
		#endif
		
		#ifdef MARIA3
		mWriteDspRegW ( DSP_10, msReadDspRegW ( DSP_10 ) | 0x0081 ); // SW v sync
		#endif

		//fFlagDSP = 0;

		// Initialize V sync relative settings
		g_wDefaultVTotal = wDefaultVTotal;
		initVSYNC ( wDefaultVTotal );

		s_ucWriteIdx = 0;
		s_ucReadIdx = 0;
	}

	else
	{
		#ifdef MARIA2
		mWriteDspRegW ( DSP_10, msReadDspRegW ( DSP_10 ) & 0xFFFE );
		#endif
		
		#ifdef MARIA3
		mWriteDspRegW ( DSP_10, msReadDspRegW ( DSP_10 ) & 0xFF7E );
		#endif
	}

	msWriteByte ( BK2_07, ucBk2_07 );
	msWriteByte ( BK0_00, ucBank );

	g_bVdDsp_StopInt = 0;
}



