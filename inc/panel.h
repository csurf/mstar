//panle define

#if (PANEL_TYPE==PanelPVI05_AT)
	#include "pnl_PVI05_AT.h"
#elif (PANEL_TYPE==PanelTMD07_AT)
	#include "pnl_TMD070_AT.h"
#elif (PANEL_TYPE==PanelAU07_AT)
	#include "pnl_AU07_AT.h"
#elif (PANEL_TYPE==PanelPVI07_AT)
	#include "pnl_PVI07_AT.h"
#elif (PANEL_TYPE==PanelSHARP08_DT)
	#include "pnl_SHARP08_D.h"
#elif (PANEL_TYPE==PanelLG064_DT)
	#include "pnl_LG064_D.h"
#elif (PANEL_TYPE==PanelLG07_AT)
	#include "pnl_LG07_AT.h"
#elif (PANEL_TYPE==PanelSHARP09_DT)
	#include "pNL_SHARP92_D.h"
#elif (PANEL_TYPE==PanelAU102_DT)
	#include "pNL_AU102_DT.h"
#elif (PANEL_TYPE==PanelPVI08W_AT)
	#include "pNL_PVI08W_AT.h"
#elif (PANEL_TYPE==PanelPVI10_AT)
	#include "pNL_PVI10_AT.h"
#elif (PANEL_TYPE==PanelLG065_AT)
	#include "pNL_LG065_AT.h"
#elif (PANEL_TYPE==PanelINNPLUX08_DT)
	#include "pNL_INNOLUX08_DT.h"
#elif (PANEL_TYPE==PanelPVI025_AT)
	#include "pNL_PVI025_AT.h"
#elif (PANEL_TYPE==PanelAU065W_AT)
	#include "pNL_AU065W_AT.h"
#elif (PANEL_TYPE==PanelCPT07_AT)
	#include "pNL_CPT07_AT.h"
#elif (PANEL_TYPE==PanelPVI08_AT)
	#include "pNL_PVI08_AT.h"
#elif (PANEL_TYPE==PanelChiLin084_AT)
	#include "pnl_ChiLin084_AT.h"
#elif (PANEL_TYPE==PanelPVI030_AT)
	#include "pNL_PVI030_AT.h"
#elif (PANEL_TYPE==PanelHSD09_AT)
	#include "pnl_HSD09_AT.h"
#elif (PANEL_TYPE==PanelINNOLUX0843_DT)
	#include "pnl_INNOLUX0843_D.h"
#elif (PANEL_TYPE==PanelAT08TN52_D)
	#include "pnl_AT08TN52_D.h"
#elif (PANEL_TYPE==PanelFG035_D)
	#include "pnl_FG035_D.h"
#elif (PANEL_TYPE==PanelKD040G1A1_DT)
	#include "pnl_KD040G1A1_DT.h"
#elif (PANEL_TYPE==PanelHSD07_D)
	#include "pnl_HSD07_D.h"
#elif (PANEL_TYPE==PNL_CM106_V)
	#include "pNL_CM106_V.h"
#elif (PANEL_TYPE==PanelCMO_N10106_LVDS1024X600)
	#include "pnl_CMO_N10106_LVDS1024X600.h"
#elif (PANEL_TYPE==PanelCMO_N10106_LVDS1024X768)
	#include "pnl_CMO_N10106_LVDS1024X768.h"
#elif (PANEL_TYPE==PanelCPT12_LVDS)
	#include "pnl_CPT12_LVDS.h"
#elif (PANEL_TYPE==PanelB089AW01_LVDS)
	#include "pnl_B089AW01_LVDS.h"
#elif (PANEL_TYPE==Pnl_A121EW02_LVDS)
	#include "pnl_A121EW02_LVDS.h"
#elif (PANEL_TYPE==Pnl_HSD121PHW1_LVDS)
	#include "pnl_HSD121PHW1_LVDS.h"
#elif (PANEL_TYPE==Pnl_LP156WH2_LVDS)
	#include "pnl_LP156WH2_LVDS.h"
#elif (PANEL_TYPE==PanelHSD050)
	#include "pnl_HSD050IDW1.h"
#elif (PANEL_TYPE==Pnl_AU08_D)
	#include "pnl_AU08_D.h"
#elif (PANEL_TYPE==PanelLONGLAT_C501)
	#include "pnl_LONGLAT_C501.h"
#endif

#ifndef PANEL_LVDS
	#define PANEL_LVDS 0
#endif

// Ouput Clock PLL
#if( MST_CLOCK_KHZ == 12000 ) // 12MHz*18=216MHz
	#define PANEL_MASTER_PLL_DIVIDER 0x12 // MM
	#elif( MST_CLOCK_KHZ == 24000 ) // 24MHz*9=216MHz
	#define PANEL_MASTER_PLL_DIVIDER 0x09 // MM
#else // ( MST_CLOCK_HZ == CRYSTAL_14318000 ) 14.31818MHz*15=214.7737
	#define PANEL_MASTER_PLL_DIVIDER 0x0F// MM
#endif

#define DEFAULT_OUTPUT_V_FREQ 60

#define PANEL_FREE_RUN_DCLK PanelDCLK * 1000000

#define PANEL_FREE_RUN_DCLK_FACTOR ( ( ( (DWORD) MST_CLOCK_HZ / 4000 * 524288ul ) / ( PANEL_FREE_RUN_DCLK / 4000 ) ) * PANEL_MASTER_PLL_DIVIDER )

