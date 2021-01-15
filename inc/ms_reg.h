//
// MST7XXX registers define
// 2005/1/6
//
#define BK0_00_REGBK 0x00 // Register Bank Select
#define AINC_B _BIT3 // Serial bus address auto increase (Enable|Disable)
#define REG_BANK_MASK 0x07 // [1:0]:Register Bank Select
#define REG_BANK_SCALER 0x0 // Scaler Bank
#define REG_BANK1_ADC_ACE_MCU 0x1 // ADC/ACE/MCU Bank
#define REG_BANK2_VD 0x2 // Video Decoder Front End Bank
#define REG_BANK3_COMB 0x3 // Video Decoder 2D Comb Filter Bank
#define REG_BANK4_LVDS_CCFL 0x4
#define REG_BANK5_MGD 0x05
#define REG_BANK6s00_ADCATOP 0x06
#define REG_BANK6s01_ADCDTOP 0x16
#define REG_BANK6s02_ADCDTOP2 0x26
#define REG_BANK7_CHIPTOP 0x07

//=====================================================================
// Bank = 00 (Scaler Register)
// Double buffer control
#define BK0_01_DBFC 0x01 // enable dobule buffer while vertical blanking
#define DBC_B _BIT0 // Enable or Disable
//DBL[1:0]
#define DBL_0 0 // Keep old register value
#define DBL_1 2 // Load new data (auto reset to 00 when load finish)
#define DBL_2 4 // Automatically load data at VSYNC blanking
#define DBL_3 6 // Reserved

#define BK0_02_ISELECT 0x02
#define EXTVD_B _BIT0 // External Video Decoder select
#define BYPASSMD_B _BIT1 // By pass mode for interlace-input-interlace-output
#define IHSU_B _BIT2 // Input Sync Usage
#define ICS_B _BIT3 // CSC function enable
#define COMP_B _BIT4 // CSYNC/SOG select (only useful when STYPE = 00)
#define NIS_B _BIT7 // Input Source Enable
#define STYPE_Mask 0x60 // [6:5]:Input Sync Tpye


#define BK0_03_IPCTRL2 0x03
#define HWRP_B _BIT0 // input horizontal wrap
#define VWRP_B _BIT1 // input vertical wrap
#define ESLS_B _BIT2 // early sample line select
#define VSE_B _BIT3 // input vsync reference edge
#define HSE_B _BIT4 // input hsync reference edge
#define IVSD_B _BIT5 // vsync delay select
#define VDS_AVG_B _BIT6 // input data double sample using average
#define VDS_EN_B _BIT7 // input data double sample Enable

#define BK0_04_ISCTRL 0x04
#define MVD_SEL_Mask 0x03 // [1:0]:MVD Mode Select
#define MVD_SELCVBS 0x0 // CVBS
#define MVD_SELSVideo 0x1 // S-Video
#define MVD_SELYCbCr 0x2 // YCbCr
#define MVD_SELRGB 0x3 // RGB
#define ISSM_B _BIT2 // Input sync sample mode (Glitch-removal)
#define HSFL_B _BIT3 // Input HSYNC Filter on
#define DEGR_Mask 0x70 // [6:4]:DE or HSYNC post Glitch removal Range
#define DDE_B _BIT7 // Direct DE mode for CCIR input

// Input image sample range
#define BK0_05_SPRVST_L 0x05 // Image vertical sample star point, count by input HSYNC
#define BK0_06_SPRVST_H 0x06 // [10:0]
#define BK0_07_SPRHST_L 0x07 // Image horizontal sample star point, count by input dot clock
#define BK0_08_SPRHST_H 0x08 // [10:0]
#define BK0_09_SPRVDC_L 0x09 // Image vertical resolution (vertical display enable area count by line)
#define BK0_0A_SPRVDC_H 0x0A // [10:0]
#define BK0_0B_SPRHDC_L 0x0B // Image horizontal resolution (vertical display enable area count by pixel)
#define BK0_0C_SPRHDC_H 0x0C // [10:0]
#define BK0_0D_LYL 0x0D // Lock Y line [3:0]

#define BK0_0E_INTLX 0x0E
#define IntLac_LockAVG_B _BIT3 //
#define VDOE_B _BIT4 // Video reference Edge (for non-standard signal)

#define BK0_0F_ASCTRL 0x0F
#define OVER_B _BIT0 // Over run status(RO)
#define UNDER_B _BIT1 // Under run status(RO)
#define INTLAC_SETSTD_B _BIT2 // NTSC/PAL Setting in Manual Mode Under run status
#define INTLAC_MANSTD_B _BIT3 // NTSC/PAL Manual Mode
#define DLINE_Mask 0x30 // [5:4]:Delay Line
#define IVB_B _BIT7 // Input VSYNC Blanking Status(RO)

#define BK0_10_COCTRL1 0x10
#define CTA_B _BIT0 // Coast to ADC
#define COVS_B _BIT1 // Coast VSYNC Select
#define EXVS_B _BIT2 // External VSYNC polarity (only used when COVS is 1)
#define CSCM_B _BIT3 // Composite SYNC cut mode
#define DLYV_B _BIT4 // Analog Delay Line for component analog Video input
#define ASIS_B _BIT5 // Analog Video Input Select(0:PC 1:Component analog video)

#define BK0_11_COCTRL2 0x11 // Front tuning (Coast start from 1~256 HSYNC leading edge) COST[7:0]
#define BK0_12_COCTRL3 0x12 // End tuning (Coast end at 1~256 HSYNC leading edge) COEND[7:0]

// Interrupt setting
#define BK0_16_INTCTROL 0x16
#define INTT_B _BIT0 // Interrupt Trigger
#define TRGC_B _BIT1 // Trigger Condition
#define OVSI_B _BIT2 // Output VSYNC interrupt generated Condition
#define IVSI_B _BIT3 // Input VSYNC interrupt generated Condition
#define CHG_HMD_B _BIT7 // H Change Mode for INT

#define BK0_17_INTPULSE 0x17 // Interrupt Pulse Width by reference clock (BK0_17_INTPULSE[7:0])
#define BK0_18_INTSTA 0x18 // Interrupt Status byte A
#define BK0_19_INTENA 0x19 // Interrupt Enable control byte A
#define BK0_1A_INTSTB 0x1A // Interrupt Status byte B
#define BK0_1B_INTENB 0x1B // Interrupt Enable control byte B
#define BK0_1C_INTSTC 0x1C // Interrupt Status byte C
#define BK0_1D_INTENC 0x1D // Interrupt Enable control byte C
#define BK0_1E_INTSTD 0x1E // Interrupt Status byte D
#define BK0_1F_INTEND 0x1F // Interrupt Enable control byte D

// PLL control
#define BK0_21_PLLCTRL2 0x21
#define MPL_PD_B _BIT0 // Master PLL Power down
#define MPL_RST_B _BIT1 // Master PLL reset
#define MPL_POR_B _BIT2 // Master PLL power on reset
#define MPL_K_B _BIT3 // Master PLL Post output frequency divided by 2
#define OLP_PD_B _BIT4 // output PLL power down
#define OLP_RST_B _BIT5 // output PLL reset
#define OLP_POR_B _BIT6 // output PLL power on reset

#define BK0_22_MPL_M 0x22
// [7:5] MP_ICTRL[2:0] Master PLL Current Contrl
// [4:0] MPL_M[4:0] Master PLL divider
#define BK0_23_OPL_CTL0 0x23

// [3:0] OPL_N[3:0] Output PLL feedback divider
#define SDMD_B _BIT5 // Output PLL spread spectrum Mode
#define SSC_EN_B _BIT6 // Output PLL spread spectrum


#define BK0_24_OPL_CTL1 0x24
// [7:6] SCTRL[1:0] SSC Control
// [4:3] OPL_P[1:0] Output PLL post divider
// [2:0] OPL_ICTRL Output PLL Current Control

// Output PLL Set
#define BK0_25_OPL_SET0 0x25 // Output PLL set:OPL_SET[7:0]
#define BK0_26_OPL_SET1 0x26 // OPL_SET[15:8]
#define BK0_27_OPL_SET2 0x27 // OPL_SET[23:16]
#define BK0_28_OPL_STEP0 0x28 // Output PLL spread spectrun step:OPL_STEP[7:0]
#define BK0_29_OPL_STEP1 0x29
// [2:0] OPL_STEP[10:8]
#define OPL_EXTSEL_B _BIT5 // Output PLL external clock select
#define OPL_EXTEN_B _BIT6 // Output PLL external clock mode enable
#define OPL_BYPS_B _BIT7 // Bypass output PLL

#define BK0_2A_OPL_SPAN0 0x2A // Output PLL spread spectrum span: OPL_SPAN[7:0]
#define BK0_2B_OPL_SPAN1 0x2B
// [6:0] OPL_SPAN[14:8]
#define READ_FRAME_B _BIT7 // 0/1: OPL_SET stores line-based/frame-based value

#define BK0_2C_MPL_TST 0x2C // MPL_TEST[7:0]
#define BK0_2D_OPL_TSTA0 0x2D // OPL_TESTA[7:0]
#define BK0_2E_OPL_TSTA1 0x2E // OPL_TESTA[15:8]
#define BK0_2F_OPL_TSTD 0x2F // OPL_TEST[7:0]

// Horizontal scaling ratio
#define BK0_30_SRH_L 0x30 // SRH[7:0]
#define BK0_31_SRH_M 0x31 // SRH[15:8]
#define BK0_32_SRH_H 0x32
// [3:0] SRH[19:16]
#define SENH_B _BIT7 // Enable Horizontal scaling
#define CBILINEAR_B _BIT6 // Complmental Bi-Linear Enable
#define FORCEBICOLOR_B _BIT5 // 0:Chrominance using same setting as Luminance defined by _BIT6
// 1:Chrominance always using Bi-Linear algorithm
// Vertical scaling ratio
#define BK0_33_SRV_L 0x33 // SRV[7:0]
#define BK0_34_SRV_M 0x34 // SRV[15:8]
#define BK0_35_SRV_H 0x35
// [5:0] SRV[21:16]
#define SENV_B _BIT7 // Enable Vertical scaling

#define BK0_36_VDSUSG 0x36
#define LBICLK_DIV2_B _BIT1 // Line-buffer clock frequency is divider by 2
#define VSFIELDINV_B _BIT2 // Offset inverting for even/odd scaling
#define VSFIELDEN_B _BIT3 // Enable offset for even/odd scaling
#define ODCLK_DIV3_B _BIT4 // Output clock is 1/3 frequency of opll output
#define LB_NOGATEMD_B _BIT5 // Line-buffer always live
#define LBI_ODCLKMD_B _BIT6 // Line-buffer using output clock
#define LBI_IDCLKMD_B _BIT7 // Line-buffer using input clock

// Non-Linear scaling
#define BK0_38_NLDTI 0x38
//[6:0] NLDIO[6:0] Non-Linear scaling section Initial Offset
#define NL_EN_B _BIT7 // Non-Linear scaling enable

#define BK0_39_NLDT0 0x39 // Non-Linear scaling Delta for Section 0, bit 7 is sign bit
#define BK0_3A_NLDT1 0x3A // Non-Linear scaling Delta for Section 1, bit 7 is sign bit
#define BK0_3B_NLDC0 0x3B // Non-Linear scaling Section 0 Dot Count/2
#define BK0_3C_NLDC1 0x3C // Non-Linear scaling Section 1 Dot Count/2
#define BK0_3D_NLDC2 0x3D // Non-Linear scaling Section 2 Dot Count/2


// Display Timing
#define BK0_40_VFDEST_L 0x40 // Output frame DE Vertical Start [7:0]
#define BK0_41_VFDEST_H 0x41 // VFDEST[10:8] at [2:0]
#define BK0_42_HFDEST_L 0x42 // Output frame DE Horizontal Start [7:0]
#define BK0_43_HFDEST_H 0x43 // HFDEST[10:8] at [2:0]
#define BK0_44_VFDEEND_L 0x44 // Output frame DE Vertical END [7:0]
#define BK0_45_VFDEEND_H 0x45 // VFDEEND[10:8] at [2:0]
#define BK0_46_HFDEEND_L 0x46 // Output frame DE Horizontal END [7:0]
#define BK0_47_HFDEEND_H 0x47 // HFDEEND[10:8] at [2:0]


// Scaling image window size
#define BK0_48_SIHST_L 0x48 // Scaling Image window Horizontal Start [7:0]
#define BK0_49_SIHST_H 0x49 // SIHST[10:8] at [2:0]
#define BK0_4A_SIVEND_L 0x4A // Scaling Image window Vertical END [7:0]
#define BK0_4B_SIVEND_H 0x4B // SIVEND[10:8] at [2:0]
#define BK0_4C_SIHEND_L 0x4C // Scaling Image window Horizontal END [7:0]
#define BK0_4D_SIHEND_H 0x4D // SIHEND[10:8] at [2:0]

// Output sync timing
#define BK0_4E_VDTOT_L 0x4E // Output Vertical Total [7:0]
#define BK0_4F_VDTOT_H 0x4F // VDTOT[10:8] at [2:0]
#define BK0_50_VSST_L 0x50 // Output VSYNC start ( only useful when AOVS=1) [7:0]
#define BK0_51_VSST_H 0x51 // VSST[10:8] at [2:0]
#define VSRU_B _BIT3 // VSYNC Register Usage
#define BK0_52_VSEND_L 0x52 // Output VSYNC END ( only useful when AOVS=1) [7:0]
#define BK0_53_VSEND_H 0x53 // VSEND[10:8] at [2:0]
#define BK0_54_HDTOT_L 0x54 // Output Horizontal Total [7:0]
#define BK0_55_HDTOT_H 0x55 // HDTOT[10:8] at [2:0]
#define BK0_56_HSEND 0x56 // Output HSYNC pulse width

// Output sync control
#define BK0_57_OSCTRL1 0x57
#define CTRL_B _BIT0 // ATCTRL function enable
#define AHRT_B _BIT1 // Auto H total and Read start Tuning enable
#define SCAL_1_B _BIT2 // Scaling range add 1
#define HSRM_B _BIT5 // HSYNC Remove Mode
#define LCM_B _BIT6 // Frame Lock Mode
#define AVOS_B _BIT7 // Auto Output VSYNC

// Brightness control
#define BK0_58_BRIGHTNESS_EN 0x58
#define BRI_EN_B _BIT0 // Brightness function enable
#define BK0_59_BRI_R 0x59 // Brightness coefficient - Red color
#define BK0_5A_BRI_G 0x5A // Brightness coefficient - Green color
#define BK0_5B_BRI_B 0x5B // Brightness coefficient - Blue color

// Frame color
#define BK0_5C_FRAME_COLOR_1 0x5C
#define FC_EN_B _BIT0 // Enable frame color
//[7:6]: frame color G[4:3]
//[5:1]: frame color B[7:3]
#define BK0_5D_FRAME_COLOR_2 0x5D
//[7:3]: frame color R[7:3]
//[2:0]: frame color G[7:5]
#define BK0_5E_PATTERN 0x5E
#define REVERSE_B _BIT0 // BK0_5E_PATTERN white
#define BLACK_B _BIT1 // BK0_5E_PATTERN black
#define WHITE_B _BIT2 // BK0_5E_PATTERN reverse

// External OSD control
#define BK0_5F_EXT_OSD_CNTRL 0x5F
#define B_KEY_B _BIT0 // Key B color selected
#define G_KEY_B _BIT1 // Key G color selected
#define R_KEY_B _BIT2 // Key R color selected
#define EN_NOTEKEY_B _BIT3 // Enable inverse color key
#define EN_CKEY_B _BIT4 // Enable color key
#define EOSDEXT_Mask 0x60 // Data extend mode
#define EN_EXTOSD_B _BIT7 // Enable external osd function

// Dither function control
#define BK0_60_DITHCTRL 0x60
#define DITH_B _BIT0 // Enable Dither function
#define OBN_B _BIT1 // Output Bits Number 0/1:8/6
#define TROT_B _BIT2 // Temporal coefficient Rotate
#define SROT_B _BIT3 // Spatial coefficient Rotate
#define DITHB_Mask 0x30 // [5:4]:Dither coefficient for B channel
#define DITHG_Mask 0xC0 // [7:6]:Dither coefficient for G channel

#define BK0_61_DITHCOEF 0x61
#define BR_Mask 0x03 // [1:0]:Bottom - Right dither coefficient
#define BL_Mask 0x0C // [3:2]:Bottom - Left dither coefficient
#define TR_Mask 0x30 // [5:4]:Top - right dither coefficient
#define TL_Mask 0xC0 // [7:6]:Top - Left dither coefficient

#define BK0_62_DITHCTL1 0x62
#define ABM_Mask 0x07 // [2:0]:Alpha Blending Mode
#define DITHERMINUS_B _BIT3
#define PSEUDO_EN_B _BIT4
#define AUTODITHER_B _BIT5
#define NDMD_B _BIT6 // Noise Dithering Method
#define PSRD_B _BIT7 // Disable Pandom, reset every 4 frames

#define BK0_63_OSD_CTL 0x63
#define OBM_Mask 0x07 // [2:0]:Osd Blend Mode
#define NBM_B _BIT3 // New Blend Method
#define CKIND_Mask 0xF0 // [7:4]:Color Index of Color Key

// Color Matrix function
#define BK0_64_CM11_L 0x64 // Color Matrix Coefficient 11 [7:0]
#define BK0_65_CM11_H 0x65 // CM11[12:8] at [4:0]
#define BK0_66_CM12_L 0x66 // Color Matrix Coefficient 12 [7:0]
#define BK0_67_CM12_H 0x67 // CM12[12:8] at [4:0]
#define BK0_68_CM13_L 0x68 // Color Matrix Coefficient 13 [7:0]
#define BK0_69_CM13_H 0x69 // CM13[12:8] at [4:0]
#define BK0_6A_CM21_L 0x6A // Color Matrix Coefficient 21 [7:0]
#define BK0_6B_CM21_H 0x6B // CM21[12:8] at [4:0]
#define BK0_6C_CM22_L 0x6C // Color Matrix Coefficient 22 [7:0]
#define BK0_6D_CM22_H 0x6D // CM22[12:8] at [4:0]
#define BK0_6E_CM23_L 0x6E // Color Matrix Coefficient 23 [7:0]
#define BK0_6F_CM23_H 0x6F // CM23[12:8] at [4:0]
#define BK0_70_CM31_L 0x70 // Color Matrix Coefficient 31 [7:0]
#define BK0_71_CM31_H 0x71 // CM31[12:8] at [4:0]
#define BK0_72_CM32_L 0x72 // Color Matrix Coefficient 32 [7:0]
#define BK0_73_CM32_H 0x73 // CM32[12:8] at [4:0]
#define BK0_74_CM33_L 0x74 // Color Matrix Coefficient 33 [7:0]
#define BK0_75_CM33_H 0x75 // CM33[12:8] at [4:0]

#define BK0_76_COL_MATRIX_CTL 0x76
#define BRAN_B _BIT0 // Blue Range 0/1:0~255/128~127
#define GRAN_B _BIT1 // Green Range 0/1:0~255/128~127
#define RRAN_B _BIT2 // Red Range 0/1:0~255/128~127
#define CMC_B _BIT4 // Color Matrix Control 1:Enable
#define CMRND_B _BIT5 // Color Matrix Rounding Control 1:Enable

//
#define BK0_77_FBL_CTL 0x77
#define SLN_Mask 0x07 // [2:0]: Shift Line Numbers
#define ODDF_B _BIT3 // Shift Odd Field

#define BK0_78_LCK_VCNT_L 0x78 // Lock vtotal[7:0]
#define BK0_79_LCK_VCNT_H 0x79 // Lock_vcnt[10:8] at [2:0]
#define BK0_7A_CAP_VCNT_L 0x7A // cap vtotal[7:0]
#define BK0_7B_CAP_VCNT_H 0x7B // cap_vcnt[10:8] at [2:0]
#define BK0_7C_CAP_HCNT_L 0x7C // cap htotal[7:0]
#define BK0_7D_CAP_HCNT_H 0x7D // cap_hcnt[10:8] at [2:0]
#define BK0_7E_EST_VCNT_L 0x7E // est vtotal[7:0]
#define BK0_7F_EST_VCNT_H 0x7F // est_vcnt[10:8] at [2:0]
#define BK0_80_EST_HCNT_L 0x80 // est htotal[7:0]
#define BK0_81_EST_HCNT_H 0x81 // est_hcnt[10:8] at [2:0]

#define BK0_82_SSC_TLRN 0x82 // SSC tolerance
#define BK0_83_DELTA_L 0x83 // delta[7:0]
#define BK0_84_DELTA_H 0x84 // delta[12:8] at [4:0]
#define BK0_85_SSC_SHIFT 0x85 // SSC shift
#define BK0_86_FNTN_TEST 0x86

#define LM_SWAP8_B _BIT0 // Output channel MSB LSB swap(8 bits)
#define LM_SWAP6_B _BIT1 // Output channel MSB LSB swap(6 bits)
#define RB_SWAP_B _BIT2 // Output channel R B swap

#define SL_HS_REMVOE_B _BIT3 // Short line hs remove

#define BK0_87_DEBUG 0x87
#define PTEN_B _BIT3 // PLL test register protect bit
#define BP_B _BIT4
#define ECOK_B _BIT6 // Select external odclk

#define BK0_88_SL_CNTRL_1 0x88
#define FREEZE_SHORTLINE_B _BIT0 // Stop Short Line Update
#define SHORTLINE_FIELD_B _BIT1 // Select short line field
#define INTERLX_CAP_EN_B _BIT2 // Interlance capture enable
#define LIM_HS_B _BIT5 // Limit hs period enable

#define BK0_89_SL_TUNE_1 0x89
#define LOCK_THRESHOLD_Mask 0x1F // [4:0]:Lock_threshold
#define TUNE_COEF_Mask 0xE0 // [7:5]:Tune_coef

#define BK0_8A_SL_TUNE_2 0x8A // Limit_d5d6d7_H:Limit PLL_SET high byte
#define BK0_8B_SL_TUNE_3 0x8B // Limit_d5d6d7_L:Limit PLL_SET low byte
#define BK0_8C_TARGET_SL_L 0x8C // TARGET_SL[7:0]
#define BK0_8D_TARGET_SL_H 0x8D // TARGET_SL[11:8] at [3:0]
#define BK0_8E_REM_L 0x8E
#define BK0_8F_REM_H 0x8F

// Gamma I/O access
#define BK0_90_GAMMA_EN 0x90
#define GAMMA_EN_B _BIT0 // Gamma enable
#define ADR_INC_EN_B _BIT1 // Address increase enable

#define BK0_91_GAMMA_ADR_PORT 0x91
#define BK0_92_GAMMA_DAT_PORT 0x92

//
#define BK0_93_RBIAS 0x93
#define BK0_94_RRATIO 0x94
#define BK0_95_GBIAS 0x95
#define BK0_96_GRATIO 0x96
#define BK0_97_BBIAS 0x97
#define BK0_98_BRATIO 0x98
#define BK0_99_RBIASN 0x99
#define BK0_9A_RRATION 0x9A
#define BK0_9B_GBIASN 0x9B
#define BK0_9C_GRATION 0x9C
#define BK0_9D_BBIASN 0x9D
#define BK0_9E_BRATION 0x9E


// OSD I/O access
#define BK0_A0_OSDIOA 0xA0
#define ORBR_B _BIT0 // Enable OSD Register Burst Read Mode
#define ORBW_B _BIT1 // Enable OSD Register Burst Write Mode
#define DA_B _BIT2 // Enable OSD Display Attribute I/O Access
#define DC_B _BIT3 // Enable OSD Display Code I/O Access
#define RF_B _BIT4 // Enable OSD RAM Font I/O Access
#define CLR_B _BIT6 // OSD clear bit
#define TOSBM_B _BIT7 // Enable OSD SRAM I/O Access Burst Mode

#define BK0_A1_OSDRA 0xA1 // [5:0]:OSD Register Address Port
#define BK0_A2_OSDRD 0xA2 // OSD Register Data Port

#define BK0_A3_RAMFA 0xA3 // OSD Ram Font Address Port
#define BK0_A4_RAMFD 0xA4 // OSD Ram Font Data Port

#define BK0_A5_DISPCA_L 0xA5 // OSD Display code Address Port
#define BK0_A6_DISPCA_H 0xA6 // [2:0]: OSD Display code Address Port [10:8]
#define BK0_A7_DISPCD 0xA7 // OSD Display code Data Port

#define BK0_A8_DISPAA_L 0xA8 // OSD display Attribute Address Port
#define BK0_A9_DISPAA_H 0xA9 // [2:0]:OSD display Attribute Address Port [10:8]
#define BK0_AA_DISPAD 0xAA // OSD display Attribute Data Port

//
#define BK0_B0_LINE_SHIFT 0xB0
#define LINE_SHIFT_NUM_Mask 0x07 // [2:0]:line shift numbers
#define FIELD_INV_VS_B _BIT3 // line shift vs field inverse

#define BK0_B1_SYNC_CONTROL 0xB1
#define HS_INV_B _BIT0 // Ohs inverse
#define VS_INV_B _BIT1 // Ovs inverse
#define DE_INV_B _BIT2 // Ode inverse
#define CLK_INV_B _BIT3 // Odclk inverse
#define CLK_DLY_SEL_Mask 0xF0 // [7:4]:Select odclk delay

#define BK0_B2_SYNC_SEL 0xB2
#define DATA_SKEW_Mask 0x03 // [1:0]:Bus data skew select
#define SEL_HDE_B _BIT2 // Select hde output to hs pin
#define SEL_VDE_B _BIT3 // Select vde output to vs pin

#define BK0_B3_SVM_CLK 0xB3
#define SVM_CLKDLY_Mask 0x0F // [3:0]:Svm clock delay select
#define SVM_CLK_INV_B _BIT4 // Svm clock inverse

#define BK0_C0 0xC0
#define BK0_C1 0xC1
#define BK0_C2 0xC2
#define BK0_C3 0xC3
#define BK0_C4 0xC4
#define BK0_C5 0xC5

#define BK0_C8_ATGCTRL 0xC8
#define ATGE_B _BIT0 // Auto Gain Function Enable
#define ATGR_B _BIT1 // Auto Gain Result Ready(RO)
#define ATGM_B _BIT2 // Auto Gain Mode
#define AGR_B _BIT3 // Auto Gain Result slecction
#define ACE_B _BIT4 // ADC Calibration Enable
#define MAXB_B _BIT5 // Max value flag for blue channel(RO)
#define MAXG_B _BIT6 // Max value flag for green channel(RO)
#define MAXR_B _BIT7 // Max value flag for red channel(RO)

#define BK0_C9_ATGST 0xC9
#define MINB_B _BIT0 // Min value flag for blue channel(RO)
#define MING_B _BIT1 // Min value flag for green channel(RO)
#define MINR_B _BIT2 // Min value flag for red channel(RO)
#define CALB_B _BIT3 // Calibration value flag for Blue channel(RO)
#define CALG_B _BIT4 // Calibration value flag for Green channel(RO)
#define CALR_B _BIT5 // Calibration value flag for Red channel(RO)
#define VCLP_B _BIT7 // Video auto gain mode 0/1:RGB/YPbPr mode

#define BK0_CA_ATFCHSEL 0xCA
// [2:0] Auto Gain R/G/B channel min/max value select
// [5:4] Auto Phase R/G/B channel select
#define MIN_R 0x00
#define MIN_G 0x01
#define MIN_B 0x02
#define MAX_R 0x03
#define MAX_G 0x04
#define MAX_B 0x05

#define BK0_CB_ATOCTRL 0xCB
#define ATOE_B _BIT0 // Auto position function enable
#define ATOR_B _BIT1 // Auto position result Ready(RO)
#define ATOM_B _BIT2 // Auto position function mode
#define JITR_B _BIT3 // Jitter function Result(RO)
#define JITM_B _BIT4 // Jitter function Mode
#define JITS_B _BIT6 // Jitter Software clear
#define JITLR_B _BIT7 // Jitter function (0/1)Left/Right result for D6h and D7h

#define BK0_CC_AOVDV 0xCC
// [7:4] Auto position Valid Data Value

#define BK0_CD_ATGVALUE 0xCD // Auto Gain result based on CAh[2:0](RO)
#define BK0_CE_AOVST_L 0xCE // Auto position detected result Vertical Starting point(RO)
#define BK0_CF_AOVST_H 0xCF // [2:0]:AOVST[10:8](RO)
#define BK0_D0_AOHST_L 0xD0 // Auto position detected result Horizontal Starting point(RO)
#define BK0_D1_AOHST_H 0xD1 // [2:0]:AOHST[10:8](RO)
#define BK0_D2_AOVEND_L 0xD2 // Auto position detected result Vertical End point(RO)
#define BK0_D3_AOVEND_H 0xD3 // [2:0]:AOVEND[10:8](RO)
#define BK0_D4_AOHEND_L 0xD4 // Auto position detected result Horizontal End point(RO)
#define BK0_D5_AOHEND_H 0xD5 // [2:0]:AOHEND[10:8](RO)
#define BK0_D6_JLR_L 0xD6 // Jitter function detected Left/Right most point state(RO)
#define BK0_D7_JLR_H 0xD7 // [2:0]:JLR[10:8](RO)
#define BK0_D8_ANRF 0xD8
// [2:0] Auto Noise Level
#define BGEN_B _BIT4 // Background Noise reduction Enable
#define HNEN_B _BIT5 // High level Noise reduction Enable

#define BK0_D9_ATPGTH 0xD9 // Auto Phase Gray scale Threshold for BK0_DE_ATPV3 when BK0_DF_ATPV4=0
#define BK0_DA_ATPTTH 0xDA // Auto Phase Text Threshold for BK0_DF_ATPV4
#define BK0_DB_ATPCTRL 0xDB
#define ATPE_B _BIT0 // Auto Phase function Enable
#define ATPR_B _BIT1 // Auto Phase Result Ready(RO)
#define APMASK_Mask 0x1C // Noise Mask
#define TXT_B _BIT5 // Text detect(RO)
#define GRY_B _BIT6 // Gray scale detect(RO)
#define ATP_ELTRMD_B _BIT7 // Enable auto-position filter mode

#define BK0_DC_ATPV1 0xDC // Auto Phase Value(RO) ATPVALUE[7:0]
#define BK0_DD_ATPV2 0xDD // [7:0]:ATPVALUE[15:8]
#define BK0_DE_ATPV3 0xDE // [7:0]:ATPVALUE[23:16]
#define BK0_DF_ATPV4 0xDF // [7:0]:ATPVALUE[31:24]

//
#define BK0_E0_PDMD0 0xE0
#define FSCCLK_INV_B _BIT0 // Sub-carrier clock inverting
#define IDCLK_INV_B _BIT1 // Scaler input sample clock inverting
#define EOCLK_INV_B _BIT2 // External OSD sample clock inverting
#define MCUCLKDIV2_B _BIT3 // MCU clock select, 0/1:crystal clock/1/2 crystal clock
#define CMBCLK_GAT_B _BIT4 // Disable MVD comb-filter clock
#define AUXCLK_GAT_B _BIT5 // Disable MVD MCU-support clock
#define GCLK_Mask 0xC0 // [7:6]:Gated Clock for SRAM

#define BK0_E1_PDMD1 0xE1
#define FSCCLK_GAT_B _BIT0 // Disable MVD digital front-end clock
#define IDCLK_GAT_B _BIT1 // Disable scaler clock
#define VDCLK_GAT_B _BIT2 // Disable CCIR and MVD interface clock
#define ADCCLK_GAT_B _BIT3 // Disable 3-channel ADC digital clock
#define PCCLK_GAT_B _BIT4 // Disable CRT output support clock
#define OSDCLK_GAT_B _BIT5 // Disable OSD clock
#define BIUCLK_GAT_B _BIT6 // Disable register interface clock
#define PDALL_B _BIT7 // All chip power down

#define BK0_E2_SWRST0 0xE2
#define SWR_B _BIT0 // Software Reset (reset all digital core except registers)
#define OSDR_B _BIT1 // Reset internal OSD
#define OP2R_B _BIT3 // Reset Display Port
#define OP1R_B _BIT4 // Reset Scaler
#define IPR_B _BIT5 // Reset Digital Input Port
#define ADCR_B _BIT6 // Reset ADC
#define REGR_B _BIT7 // Reset Register

#define BK0_E3_SWRST1 0xE3
#define GMCR_B _BIT4 // Reset GMC digital tune
#define MCUR_B _BIT5 // Reset Embedded MCU
#define VCFR_B _BIT6 // Reset Video Decoder Comb Filter
#define VFER_B _BIT7 // Reset Video Decoder Front End

#define BK0_E4_ISOVRD 0xE4
#define INTJ_B _BIT0 // Interlace judgment
#define UINT_B _BIT1 // User defined 0/1:Non-interlace/Interlace, active when INTJ=1
#define IHSJ_B _BIT2 // Input HSYNC polarity judgment; 1:Defined by user (UHSP)
#define UHSP_B _BIT3 // User defined inpt HSYNC Polarity; 0/1:Low/High
#define IVSJ_B _BIT4 // Input VSYNC polarity judgment; 1:Defined by user (UVSP)
#define UVSP_B _BIT5 // User defined inpt VSYNC Polarity; 0/1:Low/High
#define CSHS_B _BIT6 // HSYNC in coast; 0/1:HSYOUT/Re-shaped HSYNC
#define SL_B _BIT7 // Shift Line; 0/1:Method 0/Method 1 for interlace mode

#define BK0_E5_MDCTRL 0xE5
#define IFI_B _BIT0 // Interlace Field inverting
#define INTF_SEL_B _BIT1 // Interlace Field detect method select
#define VEXF_B _BIT2 // Use Video External Field
#define VFIV_B _BIT3 // Video Filed Inversion
#define FIELD_ABSMD_B _BIT4 // Field Position Absolute Value Mode
#define VERR_B _BIT5 // Video CCIR656 Error correct
#define IP_TEST_MD_Mask 0xC0 // [7:6]:IP test-bus selection

#define BK0_E6_HSPW 0xE6 // HS Pulse width(RO)
#define BK0_E7_VFREE 0xE7
#define MIN_VTT_Mask 0x3F // [5:0]:Minimum VTT to free run
#define AUTOOPCOAST_B _BIT6 // Enable auto-coast-for-output
#define AUTOOPCOAST_CLR_B _BIT7 // Set auto-coast-for-output status

#define BK0_E8_HSTOL 0xE8
#define HSTOL_Mask 0x3F // [5:0]:HSYNC Tolerance
#define LN4_DETMD_B _BIT6 // 4 Line Detect Mode for Hs, DE
#define VS2HS_B _BIT7 // Input VSYNC too close to input HSYNC(RO)

#define BK0_E9_VSTOL 0xE9
#define VSTOL_Mask 0x0F // [3:0]:VSYNC Tolerance
#define HVTT_LOSE_MD_B _BIT4 // HVtt lose mode
#define HTT_FILTERMD_B _BIT5 // Htt Filter Mode
#define AUTONOSIGNAL_B _BIT6 // Enable auto-no-signal function
#define AUTONOSIGNAL_CLR_B _BIT7 // Set auto-no-signal status

#define BK0_EA_HSPRD_L 0xEA // Input Horizontal Period, count by reference clock [7:0](RO)
#define BK0_EB_HSPRD_H 0xEB // HSPRD[12:8] at [4:0](RO)
#define BK0_EC_VTOTAL_L 0xEC // Input Vertical Total Lenght, count by HSYNC [7:0](RO)
#define BK0_ED_VTOTAL_H 0xED // VTOTAL[10:8] at [2:0](RO)
#define BK0_EE_PDMD2 0xEE

#define BK0_EF_STATUS2 0xEF //(RO)
#define IVSP_B _BIT0 // Incoming input VSYNC polarity detecting result by this chip
#define IHSP_B _BIT1 // Incoming input HSYNC polarity detecting result by this chip
#define INTF_B _BIT2 // Input odd/Even:1/0 field detecting result by this chip
#define INTM_B _BIT3 // Interlace/Non-interlace:1/0 detecting result by this chip
#define CSD_B _BIT4 // CSYNC Detected status; 1:Input is detected as CSYNC
#define STD_PAL_B _BIT5 // 0/1:NTSC/PAL
#define HTT_CHG_CS_B _BIT7 // Htotal change in CSOG


// Chip ID and Version
#define BK0_F0_CHIP_ID 0xF0 // Chip id is 70h
#define BK0_F1_CHIP_VERSION 0xF1 // Chip version is 00h


#define BK0_F4_TRISTATE 0xF4
#define CLK_TRI_B _BIT0 // Output clk BK0_F4_TRISTATE
#define DE_TRI_B _BIT1 // Output de BK0_F4_TRISTATE
#define HS_TRI_B _BIT2 // Output hs BK0_F4_TRISTATE
#define VS_TRI_B _BIT3 // Output vs BK0_F4_TRISTATE
#define OBUS_TRI_B _BIT4 // Output bus BK0_F4_TRISTATE

// Test function control registers
#define BK0_F7_TEST_BUS_SELECT 0xF7
#define BK0_F8_TEST_MODE 0xF8
#define BK0_F9_BIST_RESULT 0xF9
#define BK0_FA_BIST_RESULT_L 0xFA
#define BK0_FB_BIST_RESULT_H 0xFB
#define BK0_FE_BOUNDING_INF 0xFE
#define BK0_FF_BOUNDING_MISC 0xFF

//=====================================================================
// Bank = 01 (ACE Register)
#define BK1_01_DBFC 0x01 // enable dobule buffer while vertical blanking
#define BK1_02_PLLDIVM 0x02 // PLL divider (HTotal)
#define BK1_03_PLLDIVL 0x03

#define BK1_04_RGAIN_ADC 0x04
#define BK1_05_GGAIN_ADC 0x05
#define BK1_06_BGAIN_ADC 0x06
#define BK1_07_ROFFS_ADC 0x07
#define BK1_08_GOFFS_ADC 0x08
#define BK1_09_BOFFS_ADC 0x09
#define BK1_0A 0x0A
#define BK1_0B 0x0B
#define BK1_0C_GCTRL 0x0C
#define BK1_0D_BWCOEF 0x0D
#define BK1_0E_FCOEF 0x0E
#define BK1_0F_DCOEF 0x0F
//Clock Phase control
#define BK1_10_CLKCTRL1 0x10
#define BK1_11_CLKCTRL2 0x11
#define BK1_12_VCOCTRL 0x12
#define BK1_13_RT_CT 0x13
#define BK1_14_SOG_LVL 0x14
#define BK1_16_DITHCTRL 0x16
#define BK1_18_CALEN 0x18
#define BK1_19_CALCTL 0x19

#define BK1_1F 0x1F
#define BK1_22_TESTD2 0x22
#define BK1_23_FPLL_STATUS 0x23
#define BK1_24 0x24
#define BK1_25 0x25
#define BK1_29 0x29
#define BK1_2B 0x2B
#define BK1_2C 0x2C
#define BK1_2D 0x2D
#define BK1_2F 0x2F
#define BK1_31 0x31
#define BK1_32 0x32
#define BK1_33 0x33
#define BK1_34 0x34
#define BK1_35 0x35
#define BK1_36 0x36
#define BK1_3D 0x3D
#define BK1_3E 0x3E
#define BK1_3F 0x3F

#define BK1_41 0x41
#define BK1_42 0x42
#define BK1_43_BVOM_DC 0x43 // Tune VCOM_DC (2v~1.255V)
#define BK1_44_BVOM_OUT 0x44 // Tune VCOM_OUT (0.74v~2.22V)
#define BK1_45 0x45
#define BK1_46 0x46
#define BK1_47 0x47
#define BK1_48 0x48
#define BK1_49 0x49
#define BK1_4A 0x4A
#define BK1_4B 0x4B
#define BK1_4C 0x4C
#define BK1_4D 0x4D
#define BK1_4E 0x4E
#define BK1_4F 0x4F

#define BK1_50_LPF_TAP1 0x50 // [5:0]:LPF Coefficient 1
#define BK1_51_LPF_TAP2 0x51 // [5:0]:LPF Coefficient 2
#define BK1_52_LPF_TAP3 0x52 // [5:0]:LPF Coefficient 3
#define BK1_53_LPF_TAP4 0x53 // [5:0]:LPF Coefficient 4
#define BK1_54_LPF_TAP5 0x54 // [5:0]:LPF Coefficient 5
#define BK1_55_LPF_CTL 0x55
//#define MACE_PER 0x55
// #define GATING_CS_B _BIT0 // CSC dynamic colock control
// #define GATING_LPFTAP_B _BIT1 // LPFTAP dynamic colock control
// #define GATING_LPF_B _BIT2 // LPF dynamic colock control
// #define GATING_PEAK_B _BIT3 // Peak dynamic colock control
// #define GATING_BEFCC_B _BIT4 // BW and FCC dynamic colock control
#define BK1_56_FCC_CB_1T 0x56 // FCC Cb 1T
#define BK1_57_FCC_CR_1T 0x57 // FCC Cr 1T
#define BK1_58_FCC_CB_2T 0x58 // FCC Cb 2T
#define BK1_59_FCC_CR_2T 0x59 // FCC Cr 2T
#define BK1_5A_FCC_CB_3T 0x5A // FCC Cb 3T
#define BK1_5B_FCC_CR_3T 0x5B // FCC Cr 3T
#define BK1_5C_FCC_CB_4T 0x5C // FCC Cb 4T
#define BK1_5D_FCC_CR_4T 0x5D // FCC Cr 4T
#define BK1_5E_FCC_CB_5T 0x5E // FCC Cb 5T
#define BK1_5F_FCC_CR_5T 0x5F // FCC Cr 5T
#define BK1_60_FCC_CB_6T 0x60 // FCC Cb 6T
#define BK1_61_FCC_CR_6T 0x61 // FCC Cr 6T
#define BK1_62_FCC_CB_7T 0x62 // FCC Cb 7T
#define BK1_63_FCC_CR_7T 0x63 // FCC Cr 7T
#define BK1_64_FCC_CB_8T 0x64 // FCC Cb 8T
#define BK1_65_FCC_CR_8T 0x65 // FCC Cr 8T
#define BK1_66_FCC_CB_9T 0x66 // FCC Cb 9T
#define BK1_67_FCC_CR_9T 0x67 // FCC Cr 9T
#define BK1_68_FCC_WIN1 0x68 // [1:0]:Cr D1D;[3:2]:Cr D1U;[5:4]:Cb D1D;[7:6]:Cb D1U
#define BK1_69_FCC_WIN2 0x69 // [1:0]:Cr D2D;[3:2]:Cr D2U;[5:4]:Cb D2D;[7:6]:Cb D2U
#define BK1_6A_FCC_WIN3 0x6A // [1:0]:Cr D3D;[3:2]:Cr D3U;[5:4]:Cb D3D;[7:6]:Cb D3U
#define BK1_6B_FCC_WIN4 0x6B // [1:0]:Cr D4D;[3:2]:Cr D4U;[5:4]:Cb D4D;[7:6]:Cb D4U
#define BK1_6C_FCC_WIN5 0x6C // [1:0]:Cr D5D;[3:2]:Cr D5U;[5:4]:Cb D5D;[7:6]:Cb D5U
#define BK1_6D_FCC_WIN6 0x6D // [1:0]:Cr D6D;[3:2]:Cr D6U;[5:4]:Cb D6D;[7:6]:Cb D6U
#define BK1_6E_FCC_WIN7 0x6E // [1:0]:Cr D7D;[3:2]:Cr D7U;[5:4]:Cb D7D;[7:6]:Cb D7U
#define BK1_6F_FCC_WIN8 0x6F // [1:0]:Cr D8D;[3:2]:Cr D8U;[5:4]:Cb D8D;[7:6]:Cb D8U
#define BK1_70_FCC_WIN9 0x70 // [1:0]:Cr D9D;[3:2]:Cr D9U
#define BK1_71_FCC_Y_TH 0x71 // FCC Y Threshold
#define BK1_72_FCC_K1K2 0x72 // [3:0]:FCC K T2;[7:4]:FCC K T1
#define BK1_73_FCC_K3K4 0x73 // [3:0]:FCC K T4;[7:4]:FCC K T3
#define BK1_74_FCC_K5K6 0x74 // [3:0]:FCC K T6;[7:4]:FCC K T5
#define BK1_75_FCC_K7K8 0x75 // [3:0]:FCC K T8;[7:4]:FCC K T7
#define BK1_76_FCC_CTRL 0x76
#define M_FCC_T1_T2_B _BIT0 // FCC T1 and T2 Enable
#define M_FCC_T3_B _BIT1 // FCC T3 Enable
#define M_FCC_T4_B _BIT2 // FCC T4 Enable
#define M_FCC_T5_B _BIT3 // FCC T5 Enable
#define M_FCC_T6_B _BIT4 // FCC T6 Enable
#define M_FCC_T7_B _BIT5 // FCC T7 Enable
#define M_FCC_T8_B _BIT6 // FCC T8 Enable
#define M_FCC_T9_B _BIT7 // FCC T9 Enable

#define BK1_77_APP_CTRL 0x77
#define CSC_EN_B _BIT0 // CSC Enable
#define LPFTAP_EN_B _BIT1 // LPFTAP Enable
#define MPEN_B _BIT2 // Peak Enable
#define MLEN_B _BIT3 // BK1_7A_LTI Enable
#define MLME_B _BIT4 // LTI_MED Enable
#define MCEN_B _BIT5 // BK1_7D_CTI Enable
#define MCME_B _BIT6 // CTI_MED Enable

#define BK1_78_PEAK_BAND1 0x78 // [5:0]:Band 1 Coefficient;[7:6]:Band 1 Step
#define BK1_79_PEAK_BAND2 0x79 // [5:0]:Band 2 Coefficient;[7:6]:Band 2 Step
#define BK1_7A_LTI 0x7A // [5:0]:BK1_7A_LTI Coefficient;[7:6]:BK1_7A_LTI Step
#define BK1_7B_TERM_SEL 0x7B // Peaking Select
#define BK1_7C_CROING 0x7C // Coring Threshold
#define BK1_7D_CTI 0x7D // [4:0]:BK1_7D_CTI Coefficient;[6:5]:BK1_7D_CTI Step
#define BK1_7E_VIP_Y_CTRL 0x7E
#define MBLEEN_B _BIT0 // BLE Enable
#define MWLEEN_B _BIT1 // WLE Enable
#define BK1_7F_MAX_PIX 0x7F // [7:0]:Max Pixel
#define BK1_80_MIN_PIX 0x80 // [5:0]:Min Pixel
#define BK1_81_EGE_BAND1_POS 0x81 // Edge Band 1 Coefficient (positive threshold)
#define BK1_82_EGE_BAND1_NEG 0x82 // Edge Band 1 Coefficient (negaitive threshold)
#define BK1_83_EGE_BAND2_POS 0x83 // Edge Band 2 Coefficient (positive threshold)
#define BK1_84_EGE_BAND2_NEG 0x84 // Edge Band 2 Coefficient (negaitive threshold)


#define BK1_85_M_BRI 0x85 // Main window Brightness
#define BK1_86_EGE_LTI_POS 0x86 // Edge BK1_7A_LTI Coefficient (positive threshold)
#define BK1_87_EGE_LTI_NEG 0x87 // Edge BK1_7A_LTI Coefficient (negaitive threshold)
#define BK1_88_YC_LPF 0x88
#define B2DEN_B _BIT2 // Band 2 differentiate enable
#define B1DEN_B _BIT3 // Band 1 differentiate enable
#define Y_LPF_MD_Mask 0x30 // [5:4]:Y LPF mode
#define C_LPF_MD_Mask 0xC0 // [7:6]:C LPF mode

#define BK1_89 0x89
#define BK1_8A 0x8A
#define BK1_8B 0x8B
#define BK1_8C 0x8C
#define BK1_8D 0x8D
#define BK1_8E 0x8E
#define BK1_8F 0x8F

#define BK1_90_SARADC_CTRL 0x90
#define SAR_CH_SEL_Mask 0x03 // [1:0]:Channel selection in single channel mode
#define SAR_SINGLE_B _BIT4 // Enable single channel mode
#define SAR_FREERUN_B _BIT5 // SARADC sample mode 1/0:freerun/one shot mode
#define SAR_PD_B _BIT6 // SARADC power down
#define SAR_START_B _BIT7 // SARADC sample start (W) ready(R)

#define BK1_91_SARADC_SAMPRD 0x91 // SARADC input sample period in one shot mode
#define BK1_92_SARADC_AISEL 0x92 // [3:0]:Input select of PAD_SAR_GPIO 0/1:Digital/Analog
#define BK1_93_SARADC_TEST 0x93
#define BK1_94_SAR_CH1_UPB 0x94 // [5:0]:The voltage upper bound in MCU sleep mode for Channel 1 keypad wake up
#define BK1_95_SAR_CH1_LOB 0x95 // [5:0]:The voltage lower bound in MCU sleep mode for Channel 1 keypad wake up
#define BK1_96_SAR_CH2_UPB 0x96 // [5:0]:The voltage upper bound in MCU sleep mode for Channel 2 keypad wake up
#define BK1_97_SAR_CH2_LOB 0x97 // [5:0]:The voltage lower bound in MCU sleep mode for Channel 2 keypad wake up
#define BK1_98_SAR_CH3_UPB 0x98 // [5:0]:The voltage upper bound in MCU sleep mode for Channel 3 keypad wake up
#define BK1_99_SAR_CH3_LOB 0x99 // [5:0]:The voltage lower bound in MCU sleep mode for Channel 3 keypad wake up
#define BK1_9C 0x9C

#define BK1_A0_RG_DRV 0xA0
//[1:0] Pad R[3:0] driving select
//[3:2] Pad R[7:4] driving select
//[5:4] Pad G[3:0] driving select
//[7:6] Pad G[7:4] driving select

#define BK1_A1_BS_DRV 0xA1
//[1:0] Pad B[3:0] driving select
//[3:2] Pad B[7:4] driving select
//[5:4] Pad Vsync driving select
//[7:6] Pad Hsync driving select

#define BK1_A2_CTR_DRV 0xA2
//[1:0] Pad DE driving select
//[3:2] Pad CLK driving select
//[5:4] Pad PWM1 driving select
//[7:6] Pad PWM2 driving select

#define BK1_A3_EPD_R 0xA3 // Enable pull down R channel
#define BK1_A4_EPD_G 0xA4 // Enable pull down G channel
#define BK1_A5_EPD_B 0xA5 // Enable pull down B channel
#define BK1_A6_EPD_CTRL 0xA6
#define EPD_VS _BIT0 // Enable pull down in VS pad
#define EPD_HS _BIT1 // Enable pull down in HS pad
#define EPD_DE _BIT2 // Enable pull down in DE pad
#define EPD_CLK _BIT3 // Enable pull down in CLK pad
#define EPD_PWM1 _BIT4 // Enable pull down in PWM1 pad
#define EPD_PWM2 _BIT5 // Enable pull down in PWM2 pad

#define BK1_A7_PD_HSIN 0xA7
#define BK1_A8_SET_XTAL 0xA8
#define BK1_A9_PD_VDAC 0xA9
#define PD_ALL_B _BIT0 // Power down all
#define PD_R_B _BIT1 // Power down R channel
#define PD_G_B _BIT2 // Power down G channel
#define PD_B_B _BIT3 // Power down B channel

#define BK1_AA_VDAC_ADJ1 0xAA
#define BK1_AB_VDAC_ADJ2 0xAB
#define BK1_AC_EN_CDAC 0xAC
#define EN_ALL_B _BIT0 // Enable all
#define EN_R_B _BIT1 // Enable R channel
#define EN_G_B _BIT2 // Enable G channel
#define EN_B_B _BIT3 // Enable B channel
#define EN_SVM_B _BIT4 // Enable SVM channel
#define BGT_B _BIT5 //


#define BK1_B0_SVMCTL0 0xB0
#define SMTE_B _BIT6 // SVM Main window Tap Enable
#define SMEN_B _BIT7 // SVM Main window Enable
#define SMFT_Mask 0x30 // [5:4]:SVM Main window Filter Tap

#define BK1_B1_SVMCTL1 0xB1
#define SCORING_Mask 0x0F // [3:0]:SVM Coring
#define SVMBYS_Mask 0x30 // [5:4]:SVM Bypass Y Select
#define SINV_B _BIT6 // SMV polarity Invert
#define OSDY_B _BIT7 // OSD color Space; 1:YUV color space

#define BK1_B2_SVMLMT 0xB2 // SVM Limit
#define BK1_B3_SMSG 0xB3
#define SMGAIN_Mask 0x0F // [3:0]:SVM Main window Gain
#define SMSTEP_Mask 0x70 // [6:4]:SVM Main window Step

#define BK1_B4_SVMADJ 0xB4
#define SVMDLY_Mask 0x1F // [4:0]:SVM Delay adjust
#define SVMPIP_Mask 0x60 // [6:5]:SVM pipe adjust

#define BK1_B5_OVERLAP_SEL 0xB5
#define SVM_SD_DLY_Mask 0x1F // [4:0]:SVM Slow down delay
#define OVERLAP_SEL_Mask 0x60 // [6:5]:Overlap Select
#define SVM_SEP_DLY_B _BIT7 // SVM Separate Delay Enable

#define BK1_B6_LCK_THR_FPLL 0xB6 // Lock threshold
#define BK1_B7_LMT_LPLL_OFST_L 0xB7 // Limit lpll offset L
#define BK1_B8_LMT_LPLL_OFST_H 0xB8 // Limit lpll offset H
#define BK1_B9_COEF_FPLL 0xB9
// [3:0] Tune coeff RK
// [7:4] Tune coeff

#define BK1_BA_RK_HOLD_GAIN_L 0xBA // [7:0]:Rk hold gain L
#define BK1_BB_RK_HOLD_GAIN_H 0xBB // [3:0]:Rk hold gain H
#define BK1_BE_LPLL_STLMT_L 0xBE // Fpll set limit L
#define BK1_BF_LPLL_STLMT_H 0xBF // Fpll set limit H
#define BK1_C0_TUNE_FRAME_NO 0xC0
#define TUNE_FRAME_NO_Mask 0x03 // Frame pll tune times
#define BOND_OVER_WRITE_EN_B _BIT7 // Bonding over write enable

#define BK1_C1_BND_RST 0xC1 // Bonding reset
#define BK1_C2_LMT_ADD_NMB 0xC2 // Limit adjust number in acc_fpll mode
#define BK1_C3_IVS_DIFF_THR 0xC3 // Input VS different threshold
#define BK1_C4_IVS_STALBE_THR 0xC4 // Input VS stable threshold
#define BK1_C5_CH_CH_MODE 0xC5
#define BK1_C7_IVS_PRD_NUM_L 0xC7 // [7:0]:Count number per input VS low byte
#define BK1_C8_IVS_PRD_NUM_H 0xC8 // [3:0]:Count number per input VS high 4bits

#define BK1_CB_IPOL_SET1 0xCB //POL_PVI_10IN 3 POL Output to SEQ_MOD Pin if EFh[7] = 0. 20060413
// TCON signal control
#define BK1_CD_GPO_OEV2_WIDTH 0xCD
#define BK1_CE_GPO_OEV3_WIDTH 0xCE
#define BK1_CF_GPO_OEV_DELTA 0xCF

#define BK1_D0_PTC_MODE1 0xD0
#define LINE_SHIFT_B _BIT0 // Enable Field line shift
#define FIELD_SELECT_B _BIT1 // Select field inverse from ip
#define EARLY_VS_B _BIT2 // Early vs
#define FRAME_INV_EN_B _BIT4 // Frame inverse enable
#define DOU_EXTR_MODE_Mask 0x30 // [5:4]:
#define TC_MODE_B _BIT7 // Enable TC signal output

#define BK1_D1_PTC_MODE2 0xD1
#define U_D_B _BIT0 // U_D
#define L_R_B _BIT1 // L_R
#define STVLR_SEL_B _BIT2 // 0/1:STVR/STVL
#define STHLR_SEL_B _BIT3 // 0/1:STHR/STHL
#define TCCLK_MODE_B _BIT4 // Select 3 tc clk or 1 tc clk
#define SEQ_MODE_B _BIT5 // Clock output mode 0/1:single clock/three clock
#define TCCLK_INV_B _BIT6 // Enable 3clk invverse
#define TCCLK_CONF_B _BIT7 // Enable 13 clk swap

#define BK1_D2_PTC_MODE3 0xD2
#define FRP_VCOM_INV_B _BIT0 // VCOM inverse to FRP
#define LINE_INV_DISABLE_B _BIT1 // Disable Line inverse
#define FIELD_IN_SELECT_B _BIT2 // Select field source
#define OEV2_EN_B _BIT3 // Enable OEV2(Duplicate 2/3 line mode)
#define OEV3_EN_B _BIT4 // Enable OEV3(Duplicate 2/3 line mode)
#define DF_EXT_LINE_B _BIT5 // Enable Different frame, different extract line mode
#define LG_MODE_B _BIT6 // Enable LG panel mode
#define SET_TCCLK23_VALUE_B _BIT7 // Set tcclk23 High/Low

#define BK1_D3_LN_EXTR_CNT_LMT 0xD3
//[7:4]:LINE_MXTR_CNT_LIMIT2[3:0] Line extract/duplicatte counter2
//[3:0]:LINE_MXTR_CNT_LIMIT1[3:0] Line extract/duplicatte counter1
#define BK1_D4_LN_EXTR_SET1_H 0xD4 // Line extract/duplicatte set1 high byte
#define BK1_D5_LN_EXTR_SET1_L 0xD5 // Line extract/duplicatte set1 low byte
#define BK1_D6_LN_EXTR_SET2_H 0xD6 // Line extract/duplicatte set2 high byte
#define BK1_D7_LN_EXTR_SET2_L 0xd7 // Line extract/duplicatte set2 low byte
#define BK1_D8_EXTR_STT_LN1 0xD8 // Line extract/duplicatte start line 1
#define BK1_D9_EXTR_END_LN1 0xD9 // Line extract/duplicatte end line 1
#define BK1_DA_EXTR_STT_LN2 0xDA // Line extract/duplicatte start line 2
#define BK1_DB_EXTR_END_LN2 0xDB // Line extract/duplicatte end line 2


#define BK1_DC_GPO_FRP_TRAN 0xDC // [6:0]:FRP transition position;[7]:Output invert
#define BK1_DD_GPO_STH_STT 0xDD // [6:0]:STH pulse start position;[7]:Output invert
#define BK1_DE_GPO_STH_WIDTH 0xDE // [5:0]:STH pulse width
#define BK1_DF_GPO_OEH_STT 0xDF // [6:0]:OEH pulse start position;[7]:Output invert
#define BK1_E0_GPO_OEH_WIDTH 0xE0 // [5:0]:OEH pulse width
#define BK1_E1_GPO_OEV_STT 0xE1 // [6:0]:OEV pulse start position;[7]:Output invert
#define BK1_E2_GPO_OEV_WIDTH 0xE2 // [5:0]:OEV pulse width
#define BK1_E3_GPO_CKV_STT 0xE3 // [6:0]:CKV pulse start position;[7]:Output invert
#define BK1_E4_GPO_CKV_STT2 0xE4 // [5:0]:CKV pulse start2 position
#define BK1_E5_GPO_CKV_WIDTH 0xE5 // [6:0]:CKV pulse width
#define BK1_E6_GPO_STV_LN_TH 0xE6 // [5:0]:STV line position; [6]:STV width is 1 line
#define BK1_E7_GPO_STV_STT 0xE7 // [6:0]:STV pulse start position;[7]:Output invert
#define BK1_E8_GPO_STV_WIDTH 0xE8 // [5:0]:STV pulse width
#define BK1_E9_GPO_OEV2_STT 0xE9
#define BK1_EA_GPO_OEV3_STT 0xEA
#define BK1_EB_HSTT_DLY_L 0xEB
#define BK1_EC_HSTT_DLY_H 0xEC
#define BK1_ED_CLK_DLY_SYNC_OUT 0xED // [3:0]:Tcclk delay selsect
#define BK1_EE_GPO_CKV_END2 0xEE
#define BK1_EF_Q1H_SETTING 0xEF
// Whatch Dog
#define BK1_F0_WDT0 0xF0
#define WDT_EN_B _BIT5 // Watch Dog Timer Enable
#define WDT_LD_B _BIT6 // Watch Dog Timer Load Value by SW
#define WDT_TESTMD_B _BIT7 // CSOG test mode for WDT counter

#define BK1_F1_WDT1 0xF1 // Watch Dog Timer Width
#define BK1_F2_WRLOCK0 0xF2
#define WRLOCK0_B _BIT7 // 1:Register lock

// pwm control
#define BK1_F3_PWMCLK 0xF3
#define PCLK_B _BIT0 // PWM1/2 base Clock select 1:14.318MHz/4
#define EP1EN_B _BIT1 // Enhance PWM1 Enable
#define P1POL_B _BIT2 // PWM1 Polarity when enhance PWM1 enable
#define EP2EN_B _BIT3 // Enhance PWM2 Enable
#define P2POL_B _BIT4 // PWM2 Polarity when enhance PWM2 enable
#define P1REN_B _BIT5 // PWM1 Reset every frame enable
#define P2REN_B _BIT6 // PWM2 Reset every frame enable
#define DB_EN_B _BIT7 // Double Buffer enable

#define BK1_F4_PWM1C 0xF4 // [6:0]:PWM1 Coarse adjustment; [7]:PWM1 polarity
#define BK1_F5_PWM2C 0xF5 // [6:0]:PWM2 Coarse adjustment; [7]:PWM2 polarity

#define BK1_F6_PWM1EPL 0xF6 // Enhance PWM0 Period [7:0]
#define BK1_F7_PWM1EPH 0xF7 // Enhance PWM0 Period [15:8]
#define BK1_F8_PWM2EPL 0xF8 // Enhance PWM1 Period [7:0]
#define BK1_F9_PWM2EPH 0xF9 // Enhance PWM1 Period [15:8]

#define BK1_FA_PWM5L 0xFA // PWM5 Period [7:0]
#define BK1_FB_PWM5H 0xFB // PWM5 Period [12:8] at [4:0]
#define BK1_FC_PWM6L 0xFC // PWM6 Period [7:0]
#define BK1_FD_PWM6H 0xFD // PWM6 Period [12:8] at [4:0]

//=====================================================================
// Bank = 02 (Video Decoder Register)
#define BK2_01 0x01
#define BK2_02 0x02
#define BK2_03 0x03
#define BK2_04 0x04
#define BK2_07 0x07
#define BK2_08 0x08
#define BK2_09 0x09
#define BK2_0F 0x0F // Soft Reset
#define BK2_10 0x10

#define BK2_14_SOFT_RST 0x14 // Soft Reset
#define BK2_15_FPGA_CTRL 0x15
#define BK2_17_FSC_SEL 0x17
#define BK2_18_CSTATE_CTRL 0x18
#define BK2_19_MVDET_EN 0x19
#define BK2_1A_SVD_EN 0x1A

#define BK2_1E_REG_DSP_EN 0x1E
#define BK2_1F 0x1F
#define BK2_20_APLL_CTRL1 0x20
#define BK2_21_APLL_CTRL2 0x21
#define BK2_22_APLL_CTRL3 0x22
#define BK2_23_APLL_TRANGE 0x23
#define BK2_24_APL_K1_NOISY 0x24
#define BK2_25_APL_K2_NOISY 0x25
#define BK2_26_APL_K1_NORMAL 0x26
#define BK2_27_APL_K2_NORMAL 0x27
#define BK2_28_APL_K1_VCR 0x28
#define BK2_29_APL_K2_VCR 0x29
#define BK2_2A_MODE_PFSC 0x2A
#define BK2_2B_VDFD_CTRL1 0x2B
#define BK2_2C_VDFD_CTRL2 0x2C
#define BK2_2D_VDFD_CTRL3 0x2D
#define BK2_2E_APL_PHS_OFST 0x2E
#define BK2_2F_BLACK_SEL 0x2F

#define BK2_30_CLAMP_CTRL 0x30
#define BK2_31_CLAMP_COEF1 0x31
#define BK2_32_CLAMP_COEF2 0x32
#define BK2_33_CLAMP_COEF3 0x33
#define BK2_34_CLAMP_COEF4 0x34
#define BK2_35_CLAMP_REF_SEL1 0x35
#define BK2_36_CLAMP_COEF5 0x36
#define BK2_37_CLAMP_REF_SEL2 0x37
#define BK2_38_VSTROBE_LIMIT 0x38
#define BK2_39_VSTROBE_PROTECT 0x39
#define BK2_3A 0x3A
#define BK2_3B_HV_VEXTH 0x3B
#define BK2_3C_HV_CTRL1 0x3C
#define BK2_3D_V_POSTCOAST 0x3D

#define BK2_3F 0x3F

#define BK2_40_PGA_CTRL1 0x40
#define BK2_41_PGA_TOP_TH 0x41
#define BK2_42_PGA_BOT_TH 0x42
#define BK2_43_AGC_CTRL1 0x43
#define BK2_44_AGC_FINE 0x44
#define BK2_45_AGC_CTRL2 0x45
#define BK2_46_AGC_K_CTRL 0x46
#define BK2_47_AGC_CTRL3 0x47
#define BK2_48_PGA_SWTICH_TH1 0x48
#define BK2_49_PGA_SWTICH_TH2 0x49
#define BK2_4A_AGC_LOWTH 0x4A
#define BK2_4B_PGA_OFST 0x4B
#define BK2_4C_BRST_WINDOW1 0x4C
#define BK2_4D_BRST_WINDOW2 0x4D
#define BK2_4E_BK_WINDOW1 0x4E
#define BK_WINDOW2 0x4F
#define BK2_4F_BK_WINDOW2 0x50

#define BK2_53_BRST_MAG_REF 0x53
#define BK2_54_BRST_WINDOW3 0x54
#define BK2_55_COLOR_OFF 0x55
#define BK2_56_FSC443_357DECT1 0x56
#define BK2_57_FSC443_357DECT2 0x57
#define BK2_58_FSC443_357DECT3 0x58
#define BK2_59_FSC443_357DECT4 0x59
#define BK2_5A_BRST_UNKNOW_TH 0x5A
#define BK2_5B_FSC443_357DECT5 0x5B
#define BK2_5C_FSC443_357DECT6 0x5C
#define BK2_5D_ACC_CRTL 0x5D
#define BK2_5E_ACC_GAIN 0x5E
#define BK2_5F 0x5F

#define BK2_60_WP_CTRL1 0x60
#define BK2_61 0x61
#define BK2_62 0x62
#define BK2_63 0x63
#define BK2_64 0x64
#define BK2_65_AGC_CTRL4 0x65
#define BK2_66_WP_CTRL2 0x66
#define BK2_67_WP_REDO 0x67
#define BK2_68_CLK_CTRL1 0x68
#define BK2_69_SRC_CTRL1 0x69
#define BK2_6A_VCR_DETECT1 0x6A
#define BK2_6B_VCR_DETECT2 0x6B
#define BK2_6C 0x6C
#define BK2_6D 0x6D
#define BK2_6E 0x6E
#define BK2_6F 0x6F

#define BK2_70_INI_CTRL1 0x70
#define BK2_71 0x71
#define BK2_72 0x72
#define BK2_73_INI_CTRL2 0x73
#define BK2_74 0x74
#define BK2_75 0x75
#define BK2_76_656_CTRL1 0x76
#define BK2_77 0x77
#define BK2_78 0x78
#define BK2_79_656_HDES1 0x79
#define BK2_7A 0x7A
#define BK2_7B_656_HDEW 0x7B
#define BK2_7C 0x7C
#define BK2_7D_NOISE_MLINE 0x7D
#define BK2_7E_656_CTRL2 0x7E
#define BK2_7F 0x7F

#define BK2_80_NCO_FSC0_H 0x80
#define BK2_81_NCO_FSC0_M 0x81
#define BK2_82_NCO_FSC0_L 0x82
#define BK2_83_NCO_FSC1_H 0x83
#define BK2_84_NCO_FSC1_M 0x84
#define BK2_85_NCO_FSC1_L 0x85
#define BK2_86_NCO_FSC2_H 0x86
#define BK2_87_NCO_FSC2_M 0x87
#define BK2_88_NCO_FSC2_L 0x88
#define BK2_89_NCO_FSC3_H 0x89
#define BK2_8A_NCO_FSC3_M 0x8A
#define BK2_8B_NCO_FSC3_L 0x8B
#define BK2_8C 0x8C
#define BK2_8D 0x8D
#define BK2_8E 0x8E
#define BK2_8F_FSC_TABLE 0x8F

#define BK2_90 0x90
#define BK2_91 0x91
#define BK2_92 0x92
#define BK2_93 0x93
#define BK2_94_SPL_SPD_CTRL1 0x94
#define BK2_95_SPL_SPD_CTRL2 0x95
#define BK2_96_EDGES_NOISY_TH 0x96
#define BK2_97_EDGES_CLEAN_TH 0x97
#define BK2_98_SYNC_WIN_CTRL1 0x98
#define BK2_99_SYNC_WIN_CTRL2 0x99
#define BK2_9A_SYNC_CTRL1 0x9A
#define BK2_9B_SYNC_CTRL2 0x9B
#define BK2_9C_SYNC_CTRL3 0x9C
#define BK2_9D_DPL_NSPL_HIGH 0x9D
#define BK2_9E_DPL_NSPL_LOW 0x9E
#define BK2_9F 0x9F

#define BK2_A0_DPL_K1_FORCE 0xA0
#define BK2_A1_DPL_K2_FORCE 0xA1
#define BK2_A2_DPL_K1_NOISY 0xA2
#define BK2_A3_DPL_K2_NOISY 0xA3
#define BK2_A4_DPL_K1_VCR 0xA4
#define BK2_A5_DPL_K2_VCR 0xA5
#define BK2_A6_DPL_K1_VCR_V 0xA6
#define BK2_A7_DPL_K2_VCR_V 0xA7
#define BK2_A8_DPL_K1_FAST 0xA8
#define BK2_A9_DPL_K2_FAST 0xA9
#define BK2_AA_DPL_CTRL1 0xAA
#define BK2_AB 0xAB
#define BK2_AC 0xAC
#define BK2_AD 0xAD
#define BK2_AE_DPL_COAST_CTRL 0xAE
#define BK2_AF_DPL_CTRL2 0xAF

#define BK2_B0 0xB0
#define BK2_B1 0xB1
#define BK2_B2 0xB2
#define BK2_B3 0xB3
#define BK2_B4 0xB4
#define BK2_B5 0xB5
#define BK2_B6 0xB6
#define BK2_B7 0xB7
#define BK2_B8 0xB8
#define BK2_B9 0xB9
#define BK2_BA 0xBA
#define BK2_BB 0xBB
#define BK2_BC 0xBC
#define BK2_BD 0xBD
#define BK2_BE 0xBE
#define BK2_BF 0xBF

#define BK2_C0 0xC0
#define BK2_C1 0xC1
#define BK2_C2 0xC2
#define BK2_C3 0xC3
#define BK2_C4 0xC4
#define BK2_C5 0xC5
#define BK2_C6 0xC6
#define BK2_C7 0xC7
#define BK2_C8 0xC8
#define BK2_C9 0xC9
#define BK2_CA 0xCA
#define BK2_CB 0xCB
#define BK2_CC 0xCC
#define BK2_CD 0xCD
#define BK2_CE 0xCE
#define BK2_CF 0xCF

#define BK2_D0 0xD0
#define BK2_D1 0xD1
#define BK2_D2 0xD2
#define BK2_D3 0xD3
#define BK2_D4 0xD4
#define BK2_D5 0xD5
#define BK2_D6 0xD6
#define BK2_D7 0xD7
#define BK2_D8 0xD8
#define BK2_D9 0xD9
#define BK2_DA 0xDA
#define BK2_DB 0xDB
#define BK2_DC 0xDC
#define BK2_DD 0xDD
#define BK2_DE 0xDE
#define BK2_DF 0xDF

#define BK2_E0 0xE0
#define BK2_E1 0xE1
#define BK2_E2 0xE2
#define BK2_E3 0xE3
#define BK2_E4 0xE4
#define BK2_E5 0xE5
#define BK2_E6 0xE6
#define BK2_E7 0xE7
#define BK2_E8 0xE8
#define BK2_E9 0xE9
#define BK2_EA 0xEA
#define BK2_EB 0xEB
#define BK2_EC 0xEC
#define BK2_ED 0xED
#define BK2_EE 0xEE
#define BK2_EF 0xEF

#define BK2_F0 0xF0
#define BK2_F1 0xF1
#define BK2_F2 0xF2
#define BK2_F3 0xF3
#define BK2_F4 0xF4
#define BK2_F5 0xF5
#define BK2_F6 0xF6
#define BK2_F7 0xF7
#define BK2_F8 0xF8
#define BK2_F9 0xF9
#define BK2_FA 0xFA
#define BK2_FB 0xFB
#define BK2_FC 0xFC
#define BK2_FD 0xFD
#define BK2_FE 0xFE
#define BK2_FF 0xFF

//=====================================================================
// Bank = 03 (Comb-Filter Register)

#define BK3_10_COMBCFGA 0x10
#define BK3_11_COMBCFGB 0x11
#define BK3_12 0x12
#define BK3_13 0x13
#define BK3_14 0x14
#define BK3_15 0x15
#define BK3_16 0x16
#define BK3_17 0x17

#define BK3_18_HORSTPOS 0x18
#define BK3_19_DEVST 0x19

#define BK3_1C_CTRLSWCH 0x1C
#define BK3_1D_DACSELA 0x1D
#define BK3_1E_DACSELB 0x1E
#define BK3_1F_DACSELC 0x1F
#define BK3_20_COMB2DCFGA 0x20
#define BK3_21_COMB2DCFGB 0x21
#define BK3_22_COMB2DCFGC 0x22
#define BK3_23_COMB2DCFGD 0x23
#define BK3_24_TH2DHOR 0x24
#define BK3_25_TLRNLUMA 0x25
#define BK3_26_THCRMAERR 0x26
#define BK3_27_THHORCHKV 0x27
#define BK3_28_TH2DVER 0x28

#define BK3_2F 0x2F

#define BK3_40_TIMDETCFGA 0x40
#define BK3_41_TIMDETCFGB 0x41
#define BK3_42_TIMDETCFGC 0x42
#define BK3_43_SYNC_LVL_TLRN 0x43
#define BK3_44_HSLK_THU 0x44
#define BK3_45_HSLK_THL 0x45

#define BK3_48_BSTLVL_TH 0x48
#define BK3_49_VCRCST_LEN 0x49
#define BK3_4A_BSTSRT_THU 0x4A
#define BK3_4B_BSTSRT_THL 0x4B
#define BK3_4C_DEGDETCFG 0x4C
#define BK3_4D_TH_BURST 0x4D
#define BK3_4E_TLRNSWCHERR 0x4E

#define BK3_50 0x50
#define BK3_51 0x51
#define BK3_52 0x52
#define BK3_53 0x53

#define BK3_60_IMGCTRL 0x60
#define BK3_61_RSP_NTM 0x61
#define BK3_62 0x62

#define BK3_63_REG_CTST 0x63
#define BK3_64_REG_BRHT 0x64
#define BK3_65_REG_SAT 0x65
#define BK3_66_SENSCTST 0x66
#define BK3_67_SENSBRHT 0x67
#define BK3_68_SENSSAT 0x68
#define BK3_69_TLRNCTST 0x69
#define BK3_6A_TLRNBRHT 0x6A
#define BK3_6B_TLRNSAT 0x6B
#define BK3_6C_MAXLUMA 0x6C
#define BK3_6D_MAX_BRHT_SFT 0x6D
#define BK3_6E_MAX_SAT 0x6E
#define BK3_6F_MAX_CRMA 0x6F
#define BK3_70_COMB_STSA 0x70
#define BK3_71_COMB_STSB 0x71
#define BK3_72_COMB_STSC 0x72
#define BK3_76_DET_BST_HGHT 0x76
#define BK3_78_DBGMD 0x78
#define BK3_79_DBGPATRN 0x79
#define BK3_7A_DBGSELA 0x7A
#define BK3_7B_DBGSELB 0x7B

#define BK3_80_CC00 0x80
#define BK3_81_CC01 0x81
#define BK3_82_CC02 0x82
#define BK3_83_CC03 0x83
#define BK3_84_CC04 0x84
#define BK3_85_CC05 0x85
#define BK3_86_CC06 0x86
#define BK3_87_CC07 0x87
#define BK3_88_CC08 0x88
#define BK3_89_CC09 0x89
#define BK3_8A_CC0A 0x8A
#define BK3_8B_CC0B 0x8B
#define BK3_8C_CC0C 0x8C
#define BK3_8D_CC0D 0x8D
#define BK3_8E_CC0E 0x8E
#define BK3_8F_CC0F 0x8F
#define BK3_90_CC10 0x90
#define BK3_91_CC11 0x91
#define BK3_92_CC12 0x92
#define BK3_93_CC13 0x93
#define BK3_94_CC14 0x94
#define BK3_95_CC15 0x95
#define BK3_96_CC16 0x96
#define BK3_97_CC17 0x97
#define BK3_98_CC18 0x98
#define BK3_99_CC19 0x99
#define BK3_9A_CC1A 0x9A
#define BK3_9B_CC1B 0x9B
#define BK3_9C_CC1C 0x9C
#define BK3_9D_CC1D 0x9D
#define BK3_9E_CC1E 0x9E
#define BK3_9F_CC1F 0x9F

#define BK3_A1_SCM_IDSET1 0xA1
#define BK3_A2 0xA2

#define BK3_A4_LINE_START_A 0xA4
#define BK3_A5_LINE_START_B 0xA5

#define BK3_A7_LINE_LENGTH 0xA7
#define BK3_A8_ACT_MULTIPLE 0xA8
#define BK3_A9 0xA9
#define BK3_AA 0xAA
#define BK3_AB 0xAB
#define BK3_AC 0xAC
#define BK3_AD 0xAD
#define BK3_AE 0xAE
#define BK3_AF 0xAF

#define BK3_B0 0xB0
#define BK3_B1 0xB1
#define BK3_B2 0xB2
#define BK3_B3 0xB3
#define BK3_B4 0xB4
#define BK3_B5 0xB5

#define BK3_B9 0xB9

#define BK3_C5 0xC5

#define BK3_F2_WR_LK1 0xF2
#define BK3_F3_PWMCLK 0xF3
#define BK3_F4_PWM3C 0xF4
#define BK3_F5_PWM4C 0xF5
#define BK3_F6_PWM3EPL 0xF6
#define BK3_F7_PWM3EPH 0xF7
#define BK3_F8_PWM4EPL 0xF8
#define BK3_F9_PWM4EPH 0xF9
//=====================================================================
// Bank = 04 (LVDS & CCFL Register)
#define BK4_19 0x19 // LVDS_CTRL
#define BK4_1C 0x1C // TTL Driving
#define BK4_1E 0x1E // MOD_CTRL
#define BK4_20 0x20
#define BK4_21 0x21 // MOD_SEL1
#define BK4_22 0x22 // LVDS_T0
#define BK4_27 0x27 //Linix 20100929
#define BK4_28 0x28 //Linix 20100929
#define BK4_29 0x29
#define BK4_2A 0x2A
#define BK4_2B 0x2B
#define BK4_2C 0x2C
#define BK4_2D 0x2D

#define BK4_6B 0x6B
#define BK4_6C 0x6C
#define BK4_6D 0x6D
#define BK4_6E 0x6E
#define BK4_6F 0x6F

#define BK4_70 0x70
#define BK4_71 0x71
#define BK4_72 0x72
#define BK4_73 0x73
#define BK4_74 0x74
#define BK4_75 0x75
#define BK4_76 0x76
#define BK4_77 0x77
#define BK4_78 0x78
#define BK4_79 0x79
#define BK4_7A 0x7A
#define BK4_7B 0x7B
#define BK4_7C 0x7C
#define BK4_7D 0x7D
#define BK4_7E 0x7E
#define BK4_7F 0x7F

#define BK4_80 0x80
#define BK4_81 0x81
#define BK4_82 0x82
#define BK4_83 0x83
#define BK4_84 0x84
#define BK4_85 0x85
#define BK4_86 0x86
#define BK4_87 0x87
#define BK4_88 0x88
#define BK4_89 0x89
#define BK4_8A 0x8A
#define BK4_8B 0x8B
#define BK4_8C 0x8C
#define BK4_8D 0x8D
#define BK4_8E 0x8E
#define BK4_8F 0x8F

#define BK4_90 0x90
#define BK4_91 0x91
#define BK4_92 0x92
#define BK4_93 0x93
#define BK4_94 0x94
#define BK4_95 0x95
#define BK4_96 0x96
#define BK4_97 0x97
#define BK4_98 0x98
#define BK4_99 0x99
#define BK4_9A 0x9A
#define BK4_9B 0x9B
#define BK4_9C 0x9C
#define BK4_9D 0x9D
#define BK4_9E 0x9E
#define BK4_9F 0x9F

#define BK4_A0 0xA0
#define BK4_A1 0xA1
#define BK4_A2 0xA2
#define BK4_A3 0xA3
#define BK4_A4 0xA4
#define BK4_A5 0xA5
#define BK4_A6 0xA6
#define BK4_A7 0xA7
#define BK4_A8 0xA8
#define BK4_A9 0xA9
#define BK4_AA 0xAA
#define BK4_AB 0xAB
#define BK4_AC 0xAC
#define BK4_AD 0xAD
#define BK4_AE 0xAE
#define BK4_AF 0xAF

#define BK4_B0 0xB0
#define BK4_B1 0xB1
#define BK4_B2 0xB2
//Bank5 MGD
#define BK5_10 0x10 //88L
#define BK5_11 0x11 //88H
#define BK5_12 0x12 //89L
#define BK5_13 0x13 //89H
#define BK5_14 0x14 //8AL
#define BK5_15 0x15 //8AH
#define BK5_16 0x16 //8BL
#define BK5_17 0x17 //8BH
#define BK5_18 0x18 //8CL
#define BK5_19 0x19 //8CH
#define BK5_1A 0x1A //8DL
#define BK5_1B 0x1B //8DH
#define BK5_1C 0x1C //8EL
#define BK5_1D 0x1D //8EH
#define BK5_1E 0x1E //8FL
#define BK5_1F 0x1F //8FH
#define BK5_20 0x20 //90L
#define BK5_21 0x21 //90H
#define BK5_22 0x22 //91L
#define BK5_23 0x23 //91H
#define BK5_24 0x24 //92L
#define BK5_25 0x25 //92H
#define BK5_26 0x26 //93L
#define BK5_27 0x27 //93H
#define BK5_28 0x28 //94L
#define BK5_29 0x29 //94H
#define BK5_2A 0x2A //95L
#define BK5_2B 0x2B //95H
#define BK5_2C 0x2C //96L
#define BK5_2D 0x2D //96H
#define BK5_2E 0x2E //97L
#define BK5_2F 0x2F //97H
#define BK5_30 0x30 //98L
#define BK5_31 0x31 //98H
#define BK5_32 0x32 //99L
#define BK5_33 0x33 //99H
#define BK5_34 0x34 //9AL
#define BK5_35 0x35 //9AH
#define BK5_36 0x36 //9BL
#define BK5_37 0x37 //9BH
#define BK5_38 0x38 //9CL
#define BK5_39 0x39 //9CH
#define BK5_3A 0x3A //9DL
#define BK5_3B 0x3B //9DH
#define BK5_3C 0x3C //9EL
#define BK5_3D 0x3D //9EH
#define BK5_3E 0x3E //9FL
#define BK5_3F 0x3F //9FH
#define BK5_40 0x40 //A0L
#define BK5_41 0x41 //A0H
#define BK5_42 0x42 //A1L
#define BK5_43 0x43 //A1H
#define BK5_44 0x44 //A2L
#define BK5_45 0x45 //A2H
#define BK5_46 0x46 //A3L
#define BK5_47 0x47 //A3H
#define BK5_48 0x48 //A4L
#define BK5_49 0x49 //A4H
#define BK5_4A 0x4A //A5L
#define BK5_4B 0x4B //A5H
#define BK5_4C 0x4C //A6L
#define BK5_4D 0x4D //A6H
#define BK5_4E 0x4E //A7L
#define BK5_4F 0x4F //A7H
#define BK5_50 0x50 //A8L
#define BK5_51 0x51 //A8H
#define BK5_52 0x52 //A9L
#define BK5_53 0x53 //A9H
#define BK5_54 0x54 //AAL
#define BK5_55 0x55 //AAH
#define BK5_56 0x56 //ABL
#define BK5_57 0x57 //ABH
#define BK5_58 0x58 //ACL
#define BK5_59 0x59 //ACH
#define BK5_5A 0x5A //ADL
#define BK5_5B 0x5B //ADH
#define BK5_5C 0x5C //AEL
#define BK5_5D 0x5D //AEH
#define BK5_5E 0x5E //AFL
#define BK5_5F 0x5F //AFH
#define BK5_60 0x60 //B0L
#define BK5_61 0x61 //B0H
#define BK5_62 0x62 //B1L
#define BK5_63 0x63 //B1H
#define BK5_64 0x64 //B2L
#define BK5_65 0x65 //B2H
#define BK5_66 0x66 //B3L
#define BK5_67 0x67 //B3H
#define BK5_68 0x68 //B4L
#define BK5_69 0x69 //B4H
#define BK5_6A 0x6A //B5L
#define BK5_6B 0x6B //B5H
#define BK5_6C 0x6C //B6L
#define BK5_6D 0x6D //B6H
#define BK5_6E 0x6E //B7L
#define BK5_6F 0x6F //B7H
#define BK5_70 0x70 //B8L
#define BK5_71 0x71 //B8H
#define BK5_72 0x72 //B9L
#define BK5_73 0x73 //B9H
#define BK5_74 0x74 //BAL
#define BK5_75 0x75 //BAH
#define BK5_76 0x76 //BBL
#define BK5_77 0x77 //BBH
#define BK5_78 0x78 //BCL
#define BK5_79 0x79 //BCH
#define BK5_7A 0x7A //BDL
#define BK5_7B 0x7B //BDH
#define BK5_7C 0x7C //BEL
#define BK5_7D 0x7D //BEH
#define BK5_7E 0x7E //BFL
#define BK5_7F 0x7F //BFH

#define BK5_80 0x80
#define BK5_81 0x81
#define BK5_82 0x82
#define BK5_83 0x83
#define BK5_84 0x84
#define BK5_85 0x85
#define BK5_86 0x86
#define BK5_87 0x87
#define BK5_88 0x88
#define BK5_89 0x89
#define BK5_8A 0x8A
#define BK5_8B 0x8B
#define BK5_8C 0x8C
#define BK5_8D 0x8D
#define BK5_8E 0x8E
#define BK5_8F 0x8F
#define BK5_90 0x90
#define BK5_91 0x91
#define BK5_92 0x92
#define BK5_93 0x93
#define BK5_94 0x94
#define BK5_95 0x95
#define BK5_96 0x96
#define BK5_97 0x97
#define BK5_98 0x98
#define BK5_99 0x99
#define BK5_9A 0x9A
#define BK5_9B 0x9B
#define BK5_9C 0x9C
#define BK5_9D 0x9D
#define BK5_9E 0x9E
#define BK5_9F 0x9F

#define BK5_A0 0xA0
#define BK5_A1 0xA1
#define BK5_A2 0xA2
#define BK5_A3 0xA3
#define BK5_A4 0xA4
#define BK5_A5 0xA5
#define BK5_A6 0xA6
#define BK5_A7 0xA7
#define BK5_A8 0xA8
#define BK5_A9 0xA9
#define BK5_AA 0xAA
#define BK5_AB 0xAB
#define BK5_AC 0xAC
#define BK5_AD 0xAD
#define BK5_AE 0xAE
#define BK5_AF 0xAF
#define BK5_B0 0xB0
#define BK5_B1 0xB1
#define BK5_B2 0xB2
#define BK5_B3 0xB3
#define BK5_B4 0xB4
#define BK5_B5 0xB5
#define BK5_B6 0xB6
#define BK5_B7 0xB7
#define BK5_B8 0xB8
#define BK5_B9 0xB9
#define BK5_BA 0xBA
#define BK5_BB 0xBB
#define BK5_BC 0xBC
#define BK5_BD 0xBD
#define BK5_BE 0xBE
#define BK5_BF 0xBF

#define BK5_C0 0xC0
#define BK5_C1 0xC1
#define BK5_C2 0xC2
#define BK5_C3 0xC3
#define BK5_C4 0xC4
#define BK5_C5 0xC5
#define BK5_C6 0xC6
#define BK5_C7 0xC7
#define BK5_C8 0xC8
#define BK5_C9 0xC9
#define BK5_CA 0xCA
#define BK5_CB 0xCB
#define BK5_CC 0xCC
#define BK5_CD 0xCD
#define BK5_CE 0xCE
#define BK5_CF 0xCF
#define BK5_D0 0xD0
#define BK5_D1 0xD1
#define BK5_D2 0xD2
#define BK5_D3 0xD3
#define BK5_D4 0xD4
#define BK5_D5 0xD5
#define BK5_D6 0xD6
#define BK5_D7 0xD7
#define BK5_D8 0xD8
#define BK5_D9 0xD9
#define BK5_DA 0xDA
#define BK5_DB 0xDB
#define BK5_DC 0xDC
#define BK5_DD 0xDD
#define BK5_DE 0xDE
#define BK5_DF 0xDF

#define BK5_E0 0xE0
#define BK5_E1 0xE1
#define BK5_E2 0xE2
#define BK5_E3 0xE3
#define BK5_E4 0xE4
#define BK5_E5 0xE5
#define BK5_E6 0xE6
#define BK5_E7 0xE7
#define BK5_E8 0xE8
#define BK5_E9 0xE9
#define BK5_EA 0xEA
#define BK5_EB 0xEB
#define BK5_EC 0xEC
#define BK5_ED 0xED
#define BK5_EE 0xEE
#define BK5_EF 0xEF
#define BK5_F0 0xF0
#define BK5_F1 0xF1
#define BK5_F2 0xF2
#define BK5_F3 0xF3
#define BK5_F4 0xF4
#define BK5_F5 0xF5
#define BK5_F6 0xF6
#define BK5_F7 0xF7
#define BK5_F8 0xF8
#define BK5_F9 0xF9
#define BK5_FA 0xFA
#define BK5_FB 0xFB
#define BK5_FC 0xFC
#define BK5_FD 0xFD
#define BK5_FE 0xFE
#define BK5_FF 0xFF
// Bank5 ,16bit register addr mode
#define BK5_88h 0x10 //88L
#define BK5_89h 0x12 //89L
#define BK5_8Ah 0x14 //8AL
#define BK5_8Bh 0x16 //8BL
#define BK5_8Ch 0x18 //8CL
#define BK5_8Dh 0x1A //8DL
#define BK5_8Eh 0x1C //8EL
#define BK5_8Fh 0x1E //8FL
#define BK5_90h 0x20 //90L
#define BK5_91h 0x22 //91L
#define BK5_92h 0x24 //92L
#define BK5_93h 0x26 //93L
#define BK5_94h 0x28 //94L
#define BK5_95h 0x2A //95L
#define BK5_96h 0x2C //96L
#define BK5_97h 0x2E //97L
#define BK5_98h 0x30 //98L
#define BK5_99h 0x32 //99L
#define BK5_9Ah 0x34 //9AL
#define BK5_9Bh 0x36 //9BL
#define BK5_9Ch 0x38 //9CL
#define BK5_9Dh 0x3A //9DL
#define BK5_9Eh 0x3C //9EL
#define BK5_9Fh 0x3E //9FL
#define BK5_A0h 0x40 //A0L
#define BK5_A1h 0x42 //A1L
#define BK5_A2h 0x44 //A2L
#define BK5_A3h 0x46 //A3L
#define BK5_A4h 0x48 //A4L
#define BK5_A5h 0x4A //A5L
#define BK5_A6h 0x4C //A6L
#define BK5_A7h 0x4E //A7L
#define BK5_A8h 0x50 //A8L
#define BK5_A9h 0x52 //A9L
#define BK5_AAh 0x54 //AAL
#define BK5_ABh 0x56 //ABL
#define BK5_ACh 0x58 //ACL
#define BK5_ADh 0x5A //ADL
#define BK5_AEh 0x5C //AEL
#define BK5_AFh 0x5E //AFL
#define BK5_B0h 0x60 //B0L
#define BK5_B1h 0x62 //B1L
#define BK5_B2h 0x64 //B2L
#define BK5_B3h 0x66 //B3L
#define BK5_B4h 0x68 //B4L
#define BK5_B5h 0x6A //B5L

//BK6 sub_bank0 ADC ATOP
#define BK6s00_00_ADC_ATOP 0x00 //00L
#define BK6s00_01_ADC_ATOP 0x01 //00H
#define BK6s00_02_ADC_ATOP 0x02 //01L
#define BK6s00_03_ADC_ATOP 0x03 //01H
#define BK6s00_04_ADC_ATOP 0x04 //02L
#define BK6s00_05_ADC_ATOP 0x05 //02H
#define BK6s00_06_ADC_ATOP 0x06 //03L
#define BK6s00_07_ADC_ATOP 0x07 //03H
#define BK6s00_08_ADC_ATOP 0x08 //04L
#define BK6s00_09_ADC_ATOP 0x09 //04H
#define BK6s00_0A_ADC_ATOP 0x0A //05L
#define BK6s00_0B_ADC_ATOP 0x0B //05H
#define BK6s00_0C_ADC_ATOP 0x0C //06L
#define BK6s00_0D_ADC_ATOP 0x0D //06H
#define BK6s00_0E_ADC_ATOP 0x0E //07L
#define BK6s00_0F_ADC_ATOP 0x0F //07H
#define BK6s00_10_ADC_ATOP 0x10 //08L
#define BK6s00_11_ADC_ATOP 0x11 //08H
#define BK6s00_12_ADC_ATOP 0x12 //09L
#define BK6s00_13_ADC_ATOP 0x13 //09H
#define BK6s00_14_ADC_ATOP 0x14 //0AL
#define BK6s00_15_ADC_ATOP 0x15 //0AH
#define BK6s00_16_ADC_ATOP 0x16 //0BL
#define BK6s00_17_ADC_ATOP 0x17 //0BH
#define BK6s00_18_ADC_ATOP 0x18 //0CL
#define BK6s00_19_ADC_ATOP 0x19 //0CH
#define BK6s00_1A_ADC_ATOP 0x1A //0DL
#define BK6s00_1B_ADC_ATOP 0x1B //0DH
#define BK6s00_1C_ADC_ATOP 0x1C //0EL
#define BK6s00_1D_ADC_ATOP 0x1D //0EH
#define BK6s00_1E_ADC_ATOP 0x1E //0FL
#define BK6s00_1F_ADC_ATOP 0x1F //0FH
#define BK6s00_20_ADC_ATOP 0x20 //10L
#define BK6s00_21_ADC_ATOP 0x21 //10H
#define BK6s00_22_ADC_ATOP 0x22 //11L
#define BK6s00_23_ADC_ATOP 0x23 //11H
#define BK6s00_24_ADC_ATOP 0x24 //12L
#define BK6s00_25_ADC_ATOP 0x25 //12H
#define BK6s00_26_ADC_ATOP 0x26 //13L
#define BK6s00_27_ADC_ATOP 0x27 //13H
#define BK6s00_28_ADC_ATOP 0x28 //14L
#define BK6s00_29_ADC_ATOP 0x29 //14H
#define BK6s00_2A_ADC_ATOP 0x2A //15L
#define BK6s00_2B_ADC_ATOP 0x2B //15H
#define BK6s00_2C_ADC_ATOP 0x2C //16L
#define BK6s00_2D_ADC_ATOP 0x2D //16H
#define BK6s00_2E_ADC_ATOP 0x2E //17L
#define BK6s00_2F_ADC_ATOP 0x2F //17H
#define BK6s00_30_ADC_ATOP 0x30 //18L
#define BK6s00_31_ADC_ATOP 0x31 //18H
#define BK6s00_32_ADC_ATOP 0x32 //19L
#define BK6s00_33_ADC_ATOP 0x33 //19H
#define BK6s00_34_ADC_ATOP 0x34 //1AL
#define BK6s00_35_ADC_ATOP 0x35 //1AH
#define BK6s00_36_ADC_ATOP 0x36 //1BL
#define BK6s00_37_ADC_ATOP 0x37 //1BH
#define BK6s00_38_ADC_ATOP 0x38 //1CL
#define BK6s00_39_ADC_ATOP 0x39 //1CH
#define BK6s00_3A_ADC_ATOP 0x3A //1DL
#define BK6s00_3B_ADC_ATOP 0x3B //1DH
#define BK6s00_3C_ADC_ATOP 0x3C //1EL
#define BK6s00_3D_ADC_ATOP 0x3D //1EH
#define BK6s00_3E_ADC_ATOP 0x3E //1FL
#define BK6s00_3F_ADC_ATOP 0x3F //1FH
#define BK6s00_40_ADC_ATOP 0x40 //20L
#define BK6s00_41_ADC_ATOP 0x41 //20H
#define BK6s00_42_ADC_ATOP 0x42 //21L
#define BK6s00_43_ADC_ATOP 0x43 //21H
#define BK6s00_44_ADC_ATOP 0x44 //22L
#define BK6s00_45_ADC_ATOP 0x45 //22H
#define BK6s00_46_ADC_ATOP 0x46 //23L
#define BK6s00_47_ADC_ATOP 0x47 //23H
#define BK6s00_48_ADC_ATOP 0x48 //24L
#define BK6s00_49_ADC_ATOP 0x49 //24H
#define BK6s00_4A_ADC_ATOP 0x4A //25L
#define BK6s00_4B_ADC_ATOP 0x4B //25H
#define BK6s00_4C_ADC_ATOP 0x4C //26L
#define BK6s00_4D_ADC_ATOP 0x4D //26H
#define BK6s00_4E_ADC_ATOP 0x4E //27L
#define BK6s00_4F_ADC_ATOP 0x4F //27H
#define BK6s00_50_ADC_ATOP 0x50 //28L
#define BK6s00_51_ADC_ATOP 0x51 //28H
#define BK6s00_52_ADC_ATOP 0x52 //29L
#define BK6s00_53_ADC_ATOP 0x53 //29H
#define BK6s00_54_ADC_ATOP 0x54 //2AL
#define BK6s00_55_ADC_ATOP 0x55 //2AH
#define BK6s00_56_ADC_ATOP 0x56 //2BL
#define BK6s00_57_ADC_ATOP 0x57 //2BH
#define BK6s00_58_ADC_ATOP 0x58 //2CL
#define BK6s00_59_ADC_ATOP 0x59 //2CH
#define BK6s00_5A_ADC_ATOP 0x5A //2DL
#define BK6s00_5B_ADC_ATOP 0x5B //2DH
#define BK6s00_5C_ADC_ATOP 0x5C //2EL
#define BK6s00_5D_ADC_ATOP 0x5D //2EH
#define BK6s00_5E_ADC_ATOP 0x5E //2FL
#define BK6s00_5F_ADC_ATOP 0x5F //2FH
#define BK6s00_60_ADC_ATOP 0x60 //30L
#define BK6s00_61_ADC_ATOP 0x61 //30H
#define BK6s00_62_ADC_ATOP 0x62 //31L
#define BK6s00_63_ADC_ATOP 0x63 //31H
#define BK6s00_64_ADC_ATOP 0x64 //32L
#define BK6s00_65_ADC_ATOP 0x65 //32H
#define BK6s00_66_ADC_ATOP 0x66 //33L
#define BK6s00_67_ADC_ATOP 0x67 //33H
#define BK6s00_68_ADC_ATOP 0x68 //34L
#define BK6s00_69_ADC_ATOP 0x69 //34H
#define BK6s00_6A_ADC_ATOP 0x6A //35L
#define BK6s00_6B_ADC_ATOP 0x6B //35H
#define BK6s00_6C_ADC_ATOP 0x6C //36L
#define BK6s00_6D_ADC_ATOP 0x6D //36H
#define BK6s00_6E_ADC_ATOP 0x6E //37L
#define BK6s00_6F_ADC_ATOP 0x6F //37H
#define BK6s00_70_ADC_ATOP 0x70 //38L
#define BK6s00_71_ADC_ATOP 0x71 //38H
#define BK6s00_72_ADC_ATOP 0x72 //39L
#define BK6s00_73_ADC_ATOP 0x73 //39H
#define BK6s00_74_ADC_ATOP 0x74 //3AL
#define BK6s00_75_ADC_ATOP 0x75 //3AH
#define BK6s00_76_ADC_ATOP 0x76 //3BL
#define BK6s00_77_ADC_ATOP 0x77 //3BH
#define BK6s00_78_ADC_ATOP 0x78 //3CL
#define BK6s00_79_ADC_ATOP 0x79 //3CH
#define BK6s00_7A_ADC_ATOP 0x7A //3DL
#define BK6s00_7B_ADC_ATOP 0x7B //3DH
#define BK6s00_7C_ADC_ATOP 0x7C //3EL
#define BK6s00_7D_ADC_ATOP 0x7D //3EH
#define BK6s00_7E_ADC_ATOP 0x7E //3FL
#define BK6s00_7F_ADC_ATOP 0x7F //3FH
#define BK6s00_80_ADC_ATOP 0x80 //40L
#define BK6s00_81_ADC_ATOP 0x81 //40H
#define BK6s00_82_ADC_ATOP 0x82 //41L
#define BK6s00_83_ADC_ATOP 0x83 //41H
#define BK6s00_84_ADC_ATOP 0x84 //42L
#define BK6s00_85_ADC_ATOP 0x85 //42H
#define BK6s00_86_ADC_ATOP 0x86 //43L
#define BK6s00_87_ADC_ATOP 0x87 //43H
#define BK6s00_88_ADC_ATOP 0x88 //44L
#define BK6s00_89_ADC_ATOP 0x89 //44H
#define BK6s00_8A_ADC_ATOP 0x8A //45L
#define BK6s00_8B_ADC_ATOP 0x8B //45H
#define BK6s00_8C_ADC_ATOP 0x8C //46L
#define BK6s00_8D_ADC_ATOP 0x8D //46H
#define BK6s00_8E_ADC_ATOP 0x8E //47L
#define BK6s00_8F_ADC_ATOP 0x8F //47H
#define BK6s00_90_ADC_ATOP 0x90 //48L
#define BK6s00_91_ADC_ATOP 0x91 //48H
#define BK6s00_92_ADC_ATOP 0x92 //49L
#define BK6s00_93_ADC_ATOP 0x93 //49H
#define BK6s00_94_ADC_ATOP 0x94 //4AL
#define BK6s00_95_ADC_ATOP 0x95 //4AH
#define BK6s00_96_ADC_ATOP 0x96 //4BL
#define BK6s00_97_ADC_ATOP 0x97 //4BH
#define BK6s00_98_ADC_ATOP 0x98 //4CL
#define BK6s00_99_ADC_ATOP 0x99 //4CH
#define BK6s00_9A_ADC_ATOP 0x9A //4DL
#define BK6s00_9B_ADC_ATOP 0x9B //4DH
#define BK6s00_9C_ADC_ATOP 0x9C //4EL
#define BK6s00_9D_ADC_ATOP 0x9D //4EH
#define BK6s00_9E_ADC_ATOP 0x9E //4FL
#define BK6s00_9F_ADC_ATOP 0x9F //4FH
#define BK6s00_A0_ADC_ATOP 0xA0 //50L
// Bank6 subbank0 ,16bit register addr mode
#define BK6s00_00h_ADC_ATOP 0x00 //00L
#define BK6s00_01h_ADC_ATOP 0x02 //01L
#define BK6s00_02h_ADC_ATOP 0x04 //02L
#define BK6s00_03h_ADC_ATOP 0x06 //03L
#define BK6s00_04h_ADC_ATOP 0x08 //04L
#define BK6s00_05h_ADC_ATOP 0x0A //05L
#define BK6s00_06h_ADC_ATOP 0x0C //06L
#define BK6s00_07h_ADC_ATOP 0x0E //07L
#define BK6s00_08h_ADC_ATOP 0x10 //08L
#define BK6s00_09h_ADC_ATOP 0x12 //09L
#define BK6s00_0Ah_ADC_ATOP 0x14 //0AL
#define BK6s00_0Bh_ADC_ATOP 0x16 //0BL
#define BK6s00_0Ch_ADC_ATOP 0x18 //0CL
#define BK6s00_0Dh_ADC_ATOP 0x1A //0DL
#define BK6s00_0Eh_ADC_ATOP 0x1C //0EL
#define BK6s00_0Fh_ADC_ATOP 0x1E //0FL
#define BK6s00_10h_ADC_ATOP 0x20 //10L
#define BK6s00_11h_ADC_ATOP 0x22 //11L
#define BK6s00_12h_ADC_ATOP 0x24 //12L
#define BK6s00_13h_ADC_ATOP 0x26 //13L
#define BK6s00_14h_ADC_ATOP 0x28 //14L
#define BK6s00_15h_ADC_ATOP 0x2A //15L
#define BK6s00_16h_ADC_ATOP 0x2C //16L
#define BK6s00_17h_ADC_ATOP 0x2E //17L
#define BK6s00_18h_ADC_ATOP 0x30 //18L
#define BK6s00_19h_ADC_ATOP 0x32 //19L
#define BK6s00_1Ah_ADC_ATOP 0x34 //1AL
#define BK6s00_1Bh_ADC_ATOP 0x36 //1BL
#define BK6s00_1Ch_ADC_ATOP 0x38 //1CL
#define BK6s00_1Dh_ADC_ATOP 0x3A //1DL
#define BK6s00_1Eh_ADC_ATOP 0x3C //1EL
#define BK6s00_1Fh_ADC_ATOP 0x3E //1FL
#define BK6s00_20h_ADC_ATOP 0x40 //20L
#define BK6s00_21h_ADC_ATOP 0x42 //21L
#define BK6s00_22h_ADC_ATOP 0x44 //22L
#define BK6s00_23h_ADC_ATOP 0x46 //23L
#define BK6s00_24h_ADC_ATOP 0x48 //24L
#define BK6s00_25h_ADC_ATOP 0x4A //25L
#define BK6s00_26h_ADC_ATOP 0x4C //26L
#define BK6s00_27h_ADC_ATOP 0x4E //27L
#define BK6s00_28h_ADC_ATOP 0x50 //28L
#define BK6s00_29h_ADC_ATOP 0x52 //29L
#define BK6s00_2Ah_ADC_ATOP 0x54 //2AL
#define BK6s00_2Bh_ADC_ATOP 0x56 //2BL
#define BK6s00_2Ch_ADC_ATOP 0x58 //2CL
#define BK6s00_2Dh_ADC_ATOP 0x5A //2DL
#define BK6s00_2Eh_ADC_ATOP 0x5C //2EL
#define BK6s00_2Fh_ADC_ATOP 0x5E //2FL
#define BK6s00_30h_ADC_ATOP 0x60 //30L
#define BK6s00_31h_ADC_ATOP 0x62 //31L
#define BK6s00_32h_ADC_ATOP 0x64 //32L
#define BK6s00_33h_ADC_ATOP 0x66 //33L
#define BK6s00_34h_ADC_ATOP 0x68 //34L
#define BK6s00_35h_ADC_ATOP 0x6A //35L
#define BK6s00_36h_ADC_ATOP 0x6C //36L
#define BK6s00_37h_ADC_ATOP 0x6E //37L
#define BK6s00_38h_ADC_ATOP 0x70 //38L
#define BK6s00_39h_ADC_ATOP 0x72 //39L
#define BK6s00_3Ah_ADC_ATOP 0x74 //3AL
#define BK6s00_3Bh_ADC_ATOP 0x76 //3BL
#define BK6s00_3Ch_ADC_ATOP 0x78 //3CL
#define BK6s00_3Dh_ADC_ATOP 0x7A //3DL
#define BK6s00_3Eh_ADC_ATOP 0x7C //3EL
#define BK6s00_3Fh_ADC_ATOP 0x7E //3FL
#define BK6s00_40h_ADC_ATOP 0x80 //40L
#define BK6s00_41h_ADC_ATOP 0x82 //41L
#define BK6s00_42h_ADC_ATOP 0x84 //42L
#define BK6s00_43h_ADC_ATOP 0x86 //43L
#define BK6s00_44h_ADC_ATOP 0x88 //44L
#define BK6s00_45h_ADC_ATOP 0x8A //45L
#define BK6s00_46h_ADC_ATOP 0x8C //46L
#define BK6s00_47h_ADC_ATOP 0x8E //47L
#define BK6s00_48h_ADC_ATOP 0x90 //48L
#define BK6s00_49h_ADC_ATOP 0x92 //49L
#define BK6s00_4Ah_ADC_ATOP 0x94 //4AL
#define BK6s00_4Bh_ADC_ATOP 0x96 //4BL
#define BK6s00_4Ch_ADC_ATOP 0x98 //4CL
#define BK6s00_4Dh_ADC_ATOP 0x9A //4DL
#define BK6s00_4Eh_ADC_ATOP 0x9C //4EL
#define BK6s00_4Fh_ADC_ATOP 0x9E //4FL
#define BK6s00_50h_ADC_ATOP 0xA0 //50L
#define BK6s00_51h_ADC_ATOP 0xA2 //51L
#define BK6s00_52h_ADC_ATOP 0xA4 //52L
#define BK6s00_53h_ADC_ATOP 0xA6 //53L
#define BK6s00_54h_ADC_ATOP 0xA8 //54L
#define BK6s00_55h_ADC_ATOP 0xAA //55L
#define BK6s00_56h_ADC_ATOP 0xAC //56L
#define BK6s00_57h_ADC_ATOP 0xAE //57L
#define BK6s00_58h_ADC_ATOP 0xB0 //58L
#define BK6s00_59h_ADC_ATOP 0xB2 //59L
#define BK6s00_5Ah_ADC_ATOP 0xB4 //5AL
#define BK6s00_5Bh_ADC_ATOP 0xB6 //5BL
#define BK6s00_5Ch_ADC_ATOP 0xB8 //5CL
#define BK6s00_5Dh_ADC_ATOP 0xBA //5DL
#define BK6s00_5Eh_ADC_ATOP 0xBC //5EL
#define BK6s00_5Fh_ADC_ATOP 0xBE //5FL
#define BK6s00_60h_ADC_ATOP 0xC0 //60L
#define BK6s00_61h_ADC_ATOP 0xC2 //61L
#define BK6s00_62h_ADC_ATOP 0xC4 //62L
#define BK6s00_63h_ADC_ATOP 0xC6 //63L
#define BK6s00_64h_ADC_ATOP 0xC8 //64L
#define BK6s00_65h_ADC_ATOP 0xCA //65L
#define BK6s00_66h_ADC_ATOP 0xCC //66L
#define BK6s00_67h_ADC_ATOP 0xCE //67L
#define BK6s00_68h_ADC_ATOP 0xD0 //68L
#define BK6s00_69h_ADC_ATOP 0xD2 //69L
#define BK6s00_6Ah_ADC_ATOP 0xD4 //6AL
#define BK6s00_6Bh_ADC_ATOP 0xD6 //6BL
#define BK6s00_6Ch_ADC_ATOP 0xD8 //6CL
#define BK6s00_6Dh_ADC_ATOP 0xDA //6DL
#define BK6s00_6Eh_ADC_ATOP 0xDC //6EL
#define BK6s00_6Fh_ADC_ATOP 0xDE //6FL
#define BK6s00_70h_ADC_ATOP 0xE0 //70L
#define BK6s00_71h_ADC_ATOP 0xE2 //71L
#define BK6s00_72h_ADC_ATOP 0xE4 //72L
#define BK6s00_73h_ADC_ATOP 0xE6 //73L
#define BK6s00_74h_ADC_ATOP 0xE8 //74L
#define BK6s00_75h_ADC_ATOP 0xEA //75L
#define BK6s00_76h_ADC_ATOP 0xEC //76L
#define BK6s00_77h_ADC_ATOP 0xEE //77L
#define BK6s00_78h_ADC_ATOP 0xF0 //78L
#define BK6s00_79h_ADC_ATOP 0xF2 //79L
#define BK6s00_7Ah_ADC_ATOP 0xF4 //7AL
#define BK6s00_7Bh_ADC_ATOP 0xF6 //7BL
#define BK6s00_7Ch_ADC_ATOP 0xF8 //7CL
#define BK6s00_7Dh_ADC_ATOP 0xFA //7DL
#define BK6s00_7Eh_ADC_ATOP 0xFC //7EL
#define BK6s00_7Fh_ADC_ATOP 0xFE //7FL
//BK6 sub_bank1 ADC DTOP
#define BK6s01_00_ADC_DTOP 0x00 //00L
#define BK6s01_01_ADC_DTOP 0x01 //00H
#define BK6s01_02_ADC_DTOP 0x02 //01L
#define BK6s01_03_ADC_DTOP 0x03 //01H
#define BK6s01_04_ADC_DTOP 0x04 //02L
#define BK6s01_05_ADC_DTOP 0x05 //02H
#define BK6s01_06_ADC_DTOP 0x06 //03L
#define BK6s01_07_ADC_DTOP 0x07 //03H
#define BK6s01_08_ADC_DTOP 0x08 //04L
#define BK6s01_09_ADC_DTOP 0x09 //04H
#define BK6s01_0A_ADC_DTOP 0x0A //05L
#define BK6s01_0B_ADC_DTOP 0x0B //05H
#define BK6s01_0C_ADC_DTOP 0x0C //06L
#define BK6s01_0D_ADC_DTOP 0x0D //06H
#define BK6s01_0E_ADC_DTOP 0x0E //07L
#define BK6s01_0F_ADC_DTOP 0x0F //07H
#define BK6s01_10_ADC_DTOP 0x10 //08L
#define BK6s01_11_ADC_DTOP 0x11 //08H
#define BK6s01_12_ADC_DTOP 0x12 //09L
#define BK6s01_13_ADC_DTOP 0x13 //09H
#define BK6s01_14_ADC_DTOP 0x14 //0AL
#define BK6s01_15_ADC_DTOP 0x15 //0AH
#define BK6s01_16_ADC_DTOP 0x16 //0BL
#define BK6s01_17_ADC_DTOP 0x17 //0BH
#define BK6s01_18_ADC_DTOP 0x18 //0CL
#define BK6s01_19_ADC_DTOP 0x19 //0CH
#define BK6s01_1A_ADC_DTOP 0x1A //0DL
#define BK6s01_1B_ADC_DTOP 0x1B //0DH
#define BK6s01_1C_ADC_DTOP 0x1C //0EL
#define BK6s01_1D_ADC_DTOP 0x1D //0EH
#define BK6s01_1E_ADC_DTOP 0x1E //0FL
#define BK6s01_1F_ADC_DTOP 0x1F //0FH
#define BK6s01_20_ADC_DTOP 0x20 //10L
#define BK6s01_21_ADC_DTOP 0x21 //10H
#define BK6s01_22_ADC_DTOP 0x22 //11L
#define BK6s01_23_ADC_DTOP 0x23 //11H
#define BK6s01_24_ADC_DTOP 0x24 //12L
#define BK6s01_25_ADC_DTOP 0x25 //12H
#define BK6s01_26_ADC_DTOP 0x26 //13L
#define BK6s01_27_ADC_DTOP 0x27 //13H
#define BK6s01_28_ADC_DTOP 0x28 //14L
#define BK6s01_29_ADC_DTOP 0x29 //14H
#define BK6s01_2A_ADC_DTOP 0x2A //15L
#define BK6s01_2B_ADC_DTOP 0x2B //15H
#define BK6s01_2C_ADC_DTOP 0x2C //16L
#define BK6s01_2D_ADC_DTOP 0x2D //16H
#define BK6s01_2E_ADC_DTOP 0x2E //17L
#define BK6s01_2F_ADC_DTOP 0x2F //17H
#define BK6s01_30_ADC_DTOP 0x30 //18L
#define BK6s01_31_ADC_DTOP 0x31 //18H
#define BK6s01_32_ADC_DTOP 0x32 //19L
#define BK6s01_33_ADC_DTOP 0x33 //19H
#define BK6s01_34_ADC_DTOP 0x34 //1AL
#define BK6s01_35_ADC_DTOP 0x35 //1AH
#define BK6s01_36_ADC_DTOP 0x36 //1BL
#define BK6s01_37_ADC_DTOP 0x37 //1BH
#define BK6s01_38_ADC_DTOP 0x38 //1CL
#define BK6s01_39_ADC_DTOP 0x39 //1CH
#define BK6s01_3A_ADC_DTOP 0x3A //1DL
#define BK6s01_3B_ADC_DTOP 0x3B //1DH
#define BK6s01_3C_ADC_DTOP 0x3C //1EL
#define BK6s01_3D_ADC_DTOP 0x3D //1EH
#define BK6s01_3E_ADC_DTOP 0x3E //1FL
#define BK6s01_3F_ADC_DTOP 0x3F //1FH
#define BK6s01_40_ADC_DTOP 0x40 //20L
#define BK6s01_41_ADC_DTOP 0x41 //20H
#define BK6s01_42_ADC_DTOP 0x42 //21L
#define BK6s01_43_ADC_DTOP 0x43 //21H
#define BK6s01_44_ADC_DTOP 0x44 //22L
#define BK6s01_45_ADC_DTOP 0x45 //22H
#define BK6s01_46_ADC_DTOP 0x46 //23L
#define BK6s01_47_ADC_DTOP 0x47 //23H
#define BK6s01_48_ADC_DTOP 0x48 //24L
#define BK6s01_49_ADC_DTOP 0x49 //24H
#define BK6s01_4A_ADC_DTOP 0x4A //25L
#define BK6s01_4B_ADC_DTOP 0x4B //25H
#define BK6s01_4C_ADC_DTOP 0x4C //26L
#define BK6s01_4D_ADC_DTOP 0x4D //26H
#define BK6s01_4E_ADC_DTOP 0x4E //27L
#define BK6s01_4F_ADC_DTOP 0x4F //27H
#define BK6s01_50_ADC_DTOP 0x50 //28L
#define BK6s01_51_ADC_DTOP 0x51 //28H
#define BK6s01_52_ADC_DTOP 0x52 //29L
#define BK6s01_53_ADC_DTOP 0x53 //29H
#define BK6s01_54_ADC_DTOP 0x54 //2AL
#define BK6s01_55_ADC_DTOP 0x55 //2AH
#define BK6s01_56_ADC_DTOP 0x56 //2BL
#define BK6s01_57_ADC_DTOP 0x57 //2BH
#define BK6s01_58_ADC_DTOP 0x58 //2CL
#define BK6s01_59_ADC_DTOP 0x59 //2CH
#define BK6s01_5A_ADC_DTOP 0x5A //2DL
#define BK6s01_5B_ADC_DTOP 0x5B //2DH
#define BK6s01_5C_ADC_DTOP 0x5C //2EL
#define BK6s01_5D_ADC_DTOP 0x5D //2EH
#define BK6s01_5E_ADC_DTOP 0x5E //2FL
#define BK6s01_5F_ADC_DTOP 0x5F //2FH
#define BK6s01_60_ADC_DTOP 0x60 //30L
#define BK6s01_61_ADC_DTOP 0x61 //30H
#define BK6s01_62_ADC_DTOP 0x62 //31L
#define BK6s01_63_ADC_DTOP 0x63 //31H
#define BK6s01_64_ADC_DTOP 0x64 //32L
#define BK6s01_65_ADC_DTOP 0x65 //32H
#define BK6s01_66_ADC_DTOP 0x66 //33L
#define BK6s01_67_ADC_DTOP 0x67 //33H
#define BK6s01_68_ADC_DTOP 0x68 //34L
#define BK6s01_69_ADC_DTOP 0x69 //34H
#define BK6s01_6A_ADC_DTOP 0x6A //35L
#define BK6s01_6B_ADC_DTOP 0x6B //35H
#define BK6s01_6C_ADC_DTOP 0x6C //36L
#define BK6s01_6D_ADC_DTOP 0x6D //36H
#define BK6s01_6E_ADC_DTOP 0x6E //37L
#define BK6s01_6F_ADC_DTOP 0x6F //37H
#define BK6s01_70_ADC_DTOP 0x70 //38L
#define BK6s01_71_ADC_DTOP 0x71 //38H
#define BK6s01_72_ADC_DTOP 0x72 //39L
#define BK6s01_73_ADC_DTOP 0x73 //39H
#define BK6s01_74_ADC_DTOP 0x74 //3AL
#define BK6s01_75_ADC_DTOP 0x75 //3AH
#define BK6s01_76_ADC_DTOP 0x76 //3BL
#define BK6s01_77_ADC_DTOP 0x77 //3BH
#define BK6s01_78_ADC_DTOP 0x78 //3CL
#define BK6s01_79_ADC_DTOP 0x79 //3CH
#define BK6s01_7A_ADC_DTOP 0x7A //3DL
#define BK6s01_7B_ADC_DTOP 0x7B //3DH
#define BK6s01_7C_ADC_DTOP 0x7C //3EL
#define BK6s01_7D_ADC_DTOP 0x7D //3EH
#define BK6s01_7E_ADC_DTOP 0x7E //3FL
#define BK6s01_7F_ADC_DTOP 0x7F //3FH
#define BK6s01_80_ADC_DTOP 0x80 //40L
#define BK6s01_81_ADC_DTOP 0x81 //40H
#define BK6s01_82_ADC_DTOP 0x82 //41L
#define BK6s01_83_ADC_DTOP 0x83 //41H
#define BK6s01_84_ADC_DTOP 0x84 //42L
#define BK6s01_85_ADC_DTOP 0x85 //42H
#define BK6s01_86_ADC_DTOP 0x86 //43L
#define BK6s01_87_ADC_DTOP 0x87 //43H
#define BK6s01_88_ADC_DTOP 0x88 //44L
#define BK6s01_89_ADC_DTOP 0x89 //44H
#define BK6s01_8A_ADC_DTOP 0x8A //45L
#define BK6s01_8B_ADC_DTOP 0x8B //45H
#define BK6s01_8C_ADC_DTOP 0x8C //46L
#define BK6s01_8D_ADC_DTOP 0x8D //46H
#define BK6s01_8E_ADC_DTOP 0x8E //47L
#define BK6s01_8F_ADC_DTOP 0x8F //47H
#define BK6s01_90_ADC_DTOP 0x90 //48L
#define BK6s01_91_ADC_DTOP 0x91 //48H
#define BK6s01_92_ADC_DTOP 0x92 //49L
#define BK6s01_93_ADC_DTOP 0x93 //49H
#define BK6s01_94_ADC_DTOP 0x94 //4AL
#define BK6s01_95_ADC_DTOP 0x95 //4AH
#define BK6s01_96_ADC_DTOP 0x96 //4BL
#define BK6s01_97_ADC_DTOP 0x97 //4BH
#define BK6s01_98_ADC_DTOP 0x98 //4CL
#define BK6s01_99_ADC_DTOP 0x99 //4CH
#define BK6s01_9A_ADC_DTOP 0x9A //4DL
#define BK6s01_9B_ADC_DTOP 0x9B //4DH
#define BK6s01_9C_ADC_DTOP 0x9C //4EL
#define BK6s01_9D_ADC_DTOP 0x9D //4EH
#define BK6s01_9E_ADC_DTOP 0x9E //4FL
#define BK6s01_9F_ADC_DTOP 0x9F //4FH
#define BK6s01_A0_ADC_DTOP 0xA0 //50L
#define BK6s01_A1_ADC_DTOP 0xA1 //50H
#define BK6s01_A2_ADC_DTOP 0xA2 //51L
#define BK6s01_A3_ADC_DTOP 0xA3 //51H
#define BK6s01_A4_ADC_DTOP 0xA4 //52L
#define BK6s01_A5_ADC_DTOP 0xA5 //52H
#define BK6s01_A6_ADC_DTOP 0xA6 //53L
#define BK6s01_A7_ADC_DTOP 0xA7 //53H
#define BK6s01_A8_ADC_DTOP 0xA8 //54L
#define BK6s01_A9_ADC_DTOP 0xA9 //54H
#define BK6s01_AA_ADC_DTOP 0xAA //55L
#define BK6s01_AB_ADC_DTOP 0xAB //55H
#define BK6s01_AC_ADC_DTOP 0xAC //56L
#define BK6s01_AD_ADC_DTOP 0xAD //56H
#define BK6s01_AE_ADC_DTOP 0xAE //57L
#define BK6s01_AF_ADC_DTOP 0xAF //57H
#define BK6s01_B0_ADC_DTOP 0xB0 //58L
#define BK6s01_B1_ADC_DTOP 0xB1 //58H
#define BK6s01_B2_ADC_DTOP 0xB2 //59L
#define BK6s01_B3_ADC_DTOP 0xB3 //59H
#define BK6s01_B4_ADC_DTOP 0xB4 //5AL
#define BK6s01_B5_ADC_DTOP 0xB5 //5AH
#define BK6s01_B6_ADC_DTOP 0xB6 //5BL
#define BK6s01_B7_ADC_DTOP 0xB7 //5BH
#define BK6s01_B8_ADC_DTOP 0xB8 //5CL
#define BK6s01_B9_ADC_DTOP 0xB9 //5CH
#define BK6s01_BA_ADC_DTOP 0xBA //5DL
#define BK6s01_BB_ADC_DTOP 0xBB //5DH
#define BK6s01_BC_ADC_DTOP 0xBC //5EL
#define BK6s01_BD_ADC_DTOP 0xBD //5EH
#define BK6s01_BE_ADC_DTOP 0xBE //5FL
#define BK6s01_BF_ADC_DTOP 0xBF //5FH
#define BK6s01_C0_ADC_DTOP 0xC0 //60L
#define BK6s01_C1_ADC_DTOP 0xC1 //60H
#define BK6s01_C2_ADC_DTOP 0xC2 //61L
#define BK6s01_C3_ADC_DTOP 0xC3 //61H
#define BK6s01_C4_ADC_DTOP 0xC4 //62L
#define BK6s01_C5_ADC_DTOP 0xC5 //62H
#define BK6s01_C6_ADC_DTOP 0xC6 //63L
#define BK6s01_C7_ADC_DTOP 0xC7 //63H
#define BK6s01_C8_ADC_DTOP 0xC8 //64L
#define BK6s01_C9_ADC_DTOP 0xC9 //64H
#define BK6s01_CA_ADC_DTOP 0xCA //65L
#define BK6s01_CB_ADC_DTOP 0xCB //65H
// Bank6 subbank1 ,16bit register addr mode
#define BK6s01_00h_ADC_DTOP 0x00
#define BK6s01_01h_ADC_DTOP 0x02
#define BK6s01_02h_ADC_DTOP 0x04
#define BK6s01_03h_ADC_DTOP 0x06
#define BK6s01_04h_ADC_DTOP 0x08
#define BK6s01_05h_ADC_DTOP 0x0A
#define BK6s01_06h_ADC_DTOP 0x0C
#define BK6s01_07h_ADC_DTOP 0x0E
#define BK6s01_08h_ADC_DTOP 0x10
#define BK6s01_09h_ADC_DTOP 0x12
#define BK6s01_0Ah_ADC_DTOP 0x14
#define BK6s01_0Bh_ADC_DTOP 0x16
#define BK6s01_0Ch_ADC_DTOP 0x18
#define BK6s01_0Dh_ADC_DTOP 0x1A
#define BK6s01_0Eh_ADC_DTOP 0x1C
#define BK6s01_0Fh_ADC_DTOP 0x1E
#define BK6s01_10h_ADC_DTOP 0x20
#define BK6s01_11h_ADC_DTOP 0x22
#define BK6s01_12h_ADC_DTOP 0x24
#define BK6s01_13h_ADC_DTOP 0x26
#define BK6s01_14h_ADC_DTOP 0x28
#define BK6s01_15h_ADC_DTOP 0x2A
#define BK6s01_16h_ADC_DTOP 0x2C
#define BK6s01_17h_ADC_DTOP 0x2E
#define BK6s01_18h_ADC_DTOP 0x30
#define BK6s01_19h_ADC_DTOP 0x32
#define BK6s01_1Ah_ADC_DTOP 0x34
#define BK6s01_1Bh_ADC_DTOP 0x36
#define BK6s01_1Ch_ADC_DTOP 0x38
#define BK6s01_1Dh_ADC_DTOP 0x3A
#define BK6s01_1Eh_ADC_DTOP 0x3C
#define BK6s01_1Fh_ADC_DTOP 0x3E
#define BK6s01_20h_ADC_DTOP 0x40
#define BK6s01_21h_ADC_DTOP 0x42
#define BK6s01_22h_ADC_DTOP 0x44
#define BK6s01_23h_ADC_DTOP 0x46
#define BK6s01_24h_ADC_DTOP 0x48
#define BK6s01_25h_ADC_DTOP 0x4A
#define BK6s01_26h_ADC_DTOP 0x4C
#define BK6s01_27h_ADC_DTOP 0x4E
#define BK6s01_28h_ADC_DTOP 0x50
#define BK6s01_29h_ADC_DTOP 0x52
#define BK6s01_2Ah_ADC_DTOP 0x54
#define BK6s01_2Bh_ADC_DTOP 0x56
#define BK6s01_2Ch_ADC_DTOP 0x58
#define BK6s01_2Dh_ADC_DTOP 0x5A
#define BK6s01_2Eh_ADC_DTOP 0x5C
#define BK6s01_2Fh_ADC_DTOP 0x5E
#define BK6s01_30h_ADC_DTOP 0x60
#define BK6s01_31h_ADC_DTOP 0x62
#define BK6s01_32h_ADC_DTOP 0x64
#define BK6s01_33h_ADC_DTOP 0x66
#define BK6s01_34h_ADC_DTOP 0x68
#define BK6s01_35h_ADC_DTOP 0x6A
#define BK6s01_36h_ADC_DTOP 0x6C
#define BK6s01_37h_ADC_DTOP 0x6E
#define BK6s01_38h_ADC_DTOP 0x70
#define BK6s01_39h_ADC_DTOP 0x72
#define BK6s01_3Ah_ADC_DTOP 0x74
#define BK6s01_3Bh_ADC_DTOP 0x76
#define BK6s01_3Ch_ADC_DTOP 0x78
#define BK6s01_3Dh_ADC_DTOP 0x7A
#define BK6s01_3Eh_ADC_DTOP 0x7C
#define BK6s01_3Fh_ADC_DTOP 0x7E
#define BK6s01_40h_ADC_DTOP 0x80
#define BK6s01_41h_ADC_DTOP 0x82
#define BK6s01_42h_ADC_DTOP 0x84
#define BK6s01_43h_ADC_DTOP 0x86
#define BK6s01_44h_ADC_DTOP 0x88
#define BK6s01_45h_ADC_DTOP 0x8A
#define BK6s01_46h_ADC_DTOP 0x8C
#define BK6s01_47h_ADC_DTOP 0x8E
#define BK6s01_48h_ADC_DTOP 0x90
#define BK6s01_49h_ADC_DTOP 0x92
#define BK6s01_4Ah_ADC_DTOP 0x94
#define BK6s01_4Bh_ADC_DTOP 0x96
#define BK6s01_4Ch_ADC_DTOP 0x98
#define BK6s01_4Dh_ADC_DTOP 0x9A
#define BK6s01_4Eh_ADC_DTOP 0x9C
#define BK6s01_4Fh_ADC_DTOP 0x9E
#define BK6s01_50h_ADC_DTOP 0xA0
#define BK6s01_51h_ADC_DTOP 0xA2
#define BK6s01_52h_ADC_DTOP 0xA4
#define BK6s01_53h_ADC_DTOP 0xA6
#define BK6s01_54h_ADC_DTOP 0xA8
#define BK6s01_55h_ADC_DTOP 0xAA
#define BK6s01_56h_ADC_DTOP 0xAC
#define BK6s01_57h_ADC_DTOP 0xAE
#define BK6s01_58h_ADC_DTOP 0xB0
#define BK6s01_59h_ADC_DTOP 0xB2
#define BK6s01_5Ah_ADC_DTOP 0xB4
#define BK6s01_5Bh_ADC_DTOP 0xB6
#define BK6s01_5Ch_ADC_DTOP 0xB8
#define BK6s01_5Dh_ADC_DTOP 0xBA
#define BK6s01_5Eh_ADC_DTOP 0xBC
#define BK6s01_5Fh_ADC_DTOP 0xBE
#define BK6s01_60h_ADC_DTOP 0xC0
#define BK6s01_61h_ADC_DTOP 0xC2
#define BK6s01_62h_ADC_DTOP 0xC4
#define BK6s01_63h_ADC_DTOP 0xC6
#define BK6s01_64h_ADC_DTOP 0xC8
#define BK6s01_65h_ADC_DTOP 0xCA
#define BK6s01_66h_ADC_DTOP 0xCC
#define BK6s01_67h_ADC_DTOP 0xCE
#define BK6s01_68h_ADC_DTOP 0xD0
#define BK6s01_69h_ADC_DTOP 0xD2
#define BK6s01_6Ah_ADC_DTOP 0xD4
#define BK6s01_6Bh_ADC_DTOP 0xD6
#define BK6s01_6Ch_ADC_DTOP 0xD8
#define BK6s01_6Dh_ADC_DTOP 0xDA
#define BK6s01_6Eh_ADC_DTOP 0xDC
#define BK6s01_6Fh_ADC_DTOP 0xDE

//BK6 sub_bank2 ADC DTOP2
#define BK6s02_00_ADC_DTOP2 0x00 //00L
#define BK6s02_01_ADC_DTOP2 0x01 //00H
#define BK6s02_02_ADC_DTOP2 0x02 //01L
#define BK6s02_03_ADC_DTOP2 0x03 //01H
#define BK6s02_04_ADC_DTOP2 0x04 //02L
#define BK6s02_05_ADC_DTOP2 0x05 //02H
#define BK6s02_06_ADC_DTOP2 0x06 //03L
#define BK6s02_07_ADC_DTOP2 0x07 //03H
#define BK6s02_08_ADC_DTOP2 0x08 //04L
#define BK6s02_09_ADC_DTOP2 0x09 //04H
#define BK6s02_0A_ADC_DTOP2 0x0A //05L
#define BK6s02_0B_ADC_DTOP2 0x0B //05H
#define BK6s02_0C_ADC_DTOP2 0x0C //06L
#define BK6s02_0D_ADC_DTOP2 0x0D //06H
#define BK6s02_0E_ADC_DTOP2 0x0E //07L
#define BK6s02_0F_ADC_DTOP2 0x0F //07H
#define BK6s02_10_ADC_DTOP2 0x10 //08L
#define BK6s02_11_ADC_DTOP2 0x11 //08H
#define BK6s02_12_ADC_DTOP2 0x12 //09L
#define BK6s02_13_ADC_DTOP2 0x13 //09H
#define BK6s02_14_ADC_DTOP2 0x14 //0AL
#define BK6s02_15_ADC_DTOP2 0x15 //0AH
#define BK6s02_16_ADC_DTOP2 0x16 //0BL
#define BK6s02_17_ADC_DTOP2 0x17 //0BH
#define BK6s02_18_ADC_DTOP2 0x18 //0CL
#define BK6s02_19_ADC_DTOP2 0x19 //0CH
#define BK6s02_1A_ADC_DTOP2 0x1A //0DL
#define BK6s02_1B_ADC_DTOP2 0x1B //0DH
#define BK6s02_1C_ADC_DTOP2 0x1C //0EL
#define BK6s02_1D_ADC_DTOP2 0x1D //0EH
#define BK6s02_1E_ADC_DTOP2 0x1E //0FL
#define BK6s02_1F_ADC_DTOP2 0x1F //0FH
#define BK6s02_20_ADC_DTOP2 0x20 //10L
#define BK6s02_21_ADC_DTOP2 0x21 //10H
#define BK6s02_22_ADC_DTOP2 0x22 //11L
#define BK6s02_23_ADC_DTOP2 0x23 //11H
#define BK6s02_24_ADC_DTOP2 0x24 //12L
#define BK6s02_25_ADC_DTOP2 0x25 //12H
#define BK6s02_26_ADC_DTOP2 0x26 //13L
#define BK6s02_27_ADC_DTOP2 0x27 //13H
#define BK6s02_28_ADC_DTOP2 0x28 //14L
#define BK6s02_29_ADC_DTOP2 0x29 //14H
#define BK6s02_2A_ADC_DTOP2 0x2A //15L
#define BK6s02_2B_ADC_DTOP2 0x2B //15H
#define BK6s02_2C_ADC_DTOP2 0x2C //16L
#define BK6s02_2D_ADC_DTOP2 0x2D //16H
#define BK6s02_2E_ADC_DTOP2 0x2E //17L
#define BK6s02_2F_ADC_DTOP2 0x2F //17H
#define BK6s02_30_ADC_DTOP2 0x30 //18L
#define BK6s02_31_ADC_DTOP2 0x31 //18H
#define BK6s02_32_ADC_DTOP2 0x32 //19L
#define BK6s02_33_ADC_DTOP2 0x33 //19H
#define BK6s02_34_ADC_DTOP2 0x34 //1AL
#define BK6s02_35_ADC_DTOP2 0x35 //1AH
#define BK6s02_36_ADC_DTOP2 0x36 //1BL
#define BK6s02_37_ADC_DTOP2 0x37 //1BH
#define BK6s02_38_ADC_DTOP2 0x38 //1CL
#define BK6s02_39_ADC_DTOP2 0x39 //1CH
#define BK6s02_3A_ADC_DTOP2 0x3A //1DL
#define BK6s02_3B_ADC_DTOP2 0x3B //1DH
#define BK6s02_3C_ADC_DTOP2 0x3C //1EL
#define BK6s02_3D_ADC_DTOP2 0x3D //1EH
#define BK6s02_3E_ADC_DTOP2 0x3E //1FL
#define BK6s02_3F_ADC_DTOP2 0x3F //1FH
#define BK6s02_40_ADC_DTOP2 0x40 //20L
#define BK6s02_41_ADC_DTOP2 0x41 //20H
#define BK6s02_42_ADC_DTOP2 0x42 //21L
#define BK6s02_43_ADC_DTOP2 0x43 //21H
#define BK6s02_44_ADC_DTOP2 0x44 //22L
#define BK6s02_45_ADC_DTOP2 0x45 //22H
#define BK6s02_46_ADC_DTOP2 0x46 //23L
#define BK6s02_47_ADC_DTOP2 0x47 //23H
#define BK6s02_48_ADC_DTOP2 0x48 //24L
#define BK6s02_49_ADC_DTOP2 0x49 //24H
#define BK6s02_4A_ADC_DTOP2 0x4A //25L
#define BK6s02_4B_ADC_DTOP2 0x4B //25H
#define BK6s02_4C_ADC_DTOP2 0x4C //26L
#define BK6s02_4D_ADC_DTOP2 0x4D //26H
#define BK6s02_4E_ADC_DTOP2 0x4E //27L
#define BK6s02_4F_ADC_DTOP2 0x4F //27H
#define BK6s02_50_ADC_DTOP2 0x50 //28L
#define BK6s02_51_ADC_DTOP2 0x51 //28H
#define BK6s02_52_ADC_DTOP2 0x52 //29L
#define BK6s02_53_ADC_DTOP2 0x53 //29H
#define BK6s02_54_ADC_DTOP2 0x54 //2AL
#define BK6s02_55_ADC_DTOP2 0x55 //2AH
#define BK6s02_56_ADC_DTOP2 0x56 //2BL
#define BK6s02_57_ADC_DTOP2 0x57 //2BH
#define BK6s02_58_ADC_DTOP2 0x58 //2CL
#define BK6s02_59_ADC_DTOP2 0x59 //2CH
#define BK6s02_5A_ADC_DTOP2 0x5A //2DL
#define BK6s02_5B_ADC_DTOP2 0x5B //2DH
#define BK6s02_5C_ADC_DTOP2 0x5C //2EL
#define BK6s02_5D_ADC_DTOP2 0x5D //2EH
#define BK6s02_5E_ADC_DTOP2 0x5E //2FL
#define BK6s02_5F_ADC_DTOP2 0x5F //2FH
#define BK6s02_60_ADC_DTOP2 0x60 //30L
#define BK6s02_61_ADC_DTOP2 0x61 //30H
#define BK6s02_62_ADC_DTOP2 0x62 //31L
#define BK6s02_63_ADC_DTOP2 0x63 //31H
#define BK6s02_64_ADC_DTOP2 0x64 //32L
#define BK6s02_65_ADC_DTOP2 0x65 //32H
#define BK6s02_66_ADC_DTOP2 0x66 //33L
#define BK6s02_67_ADC_DTOP2 0x67 //33H
#define BK6s02_68_ADC_DTOP2 0x68 //34L
#define BK6s02_69_ADC_DTOP2 0x69 //34H
#define BK6s02_6A_ADC_DTOP2 0x6A //35L
#define BK6s02_6B_ADC_DTOP2 0x6B //35H
#define BK6s02_6C_ADC_DTOP2 0x6C //36L
#define BK6s02_6D_ADC_DTOP2 0x6D //36H
#define BK6s02_6E_ADC_DTOP2 0x6E //37L
#define BK6s02_6F_ADC_DTOP2 0x6F //37H
#define BK6s02_70_ADC_DTOP2 0x70 //38L
#define BK6s02_71_ADC_DTOP2 0x71 //38H
#define BK6s02_72_ADC_DTOP2 0x72 //39L
#define BK6s02_73_ADC_DTOP2 0x73 //39H
#define BK6s02_74_ADC_DTOP2 0x74 //3AL
#define BK6s02_75_ADC_DTOP2 0x75 //3AH
#define BK6s02_76_ADC_DTOP2 0x76 //3BL
#define BK6s02_77_ADC_DTOP2 0x77 //3BH
#define BK6s02_78_ADC_DTOP2 0x78 //3CL
#define BK6s02_79_ADC_DTOP2 0x79 //3CH
#define BK6s02_7A_ADC_DTOP2 0x7A //3DL
#define BK6s02_7B_ADC_DTOP2 0x7B //3DH
#define BK6s02_7C_ADC_DTOP2 0x7C //3EL
#define BK6s02_7D_ADC_DTOP2 0x7D //3EH
#define BK6s02_7E_ADC_DTOP2 0x7E //3FL
#define BK6s02_7F_ADC_DTOP2 0x7F //3FH
#define BK6s02_80_ADC_DTOP2 0x80 //40L
#define BK6s02_81_ADC_DTOP2 0x81 //40H
#define BK6s02_82_ADC_DTOP2 0x82 //41L
#define BK6s02_83_ADC_DTOP2 0x83 //41H
#define BK6s02_84_ADC_DTOP2 0x84 //42L
#define BK6s02_85_ADC_DTOP2 0x85 //42H
#define BK6s02_86_ADC_DTOP2 0x86 //43L
#define BK6s02_87_ADC_DTOP2 0x87 //43H
#define BK6s02_88_ADC_DTOP2 0x88 //44L
#define BK6s02_89_ADC_DTOP2 0x89 //44H
#define BK6s02_8A_ADC_DTOP2 0x8A //45L
#define BK6s02_8B_ADC_DTOP2 0x8B //45H
#define BK6s02_8C_ADC_DTOP2 0x8C //46L
#define BK6s02_8D_ADC_DTOP2 0x8D //46H
#define BK6s02_8E_ADC_DTOP2 0x8E //47L
#define BK6s02_8F_ADC_DTOP2 0x8F //47H
#define BK6s02_90_ADC_DTOP2 0x90 //48L
#define BK6s02_91_ADC_DTOP2 0x91 //48H
#define BK6s02_92_ADC_DTOP2 0x92 //49L
#define BK6s02_93_ADC_DTOP2 0x93 //49H
#define BK6s02_94_ADC_DTOP2 0x94 //4AL
#define BK6s02_95_ADC_DTOP2 0x95 //4AH
#define BK6s02_96_ADC_DTOP2 0x96 //4BL
#define BK6s02_97_ADC_DTOP2 0x97 //4BH
#define BK6s02_98_ADC_DTOP2 0x98 //4CL
#define BK6s02_99_ADC_DTOP2 0x99 //4CH
#define BK6s02_9A_ADC_DTOP2 0x9A //4DL
#define BK6s02_9B_ADC_DTOP2 0x9B //4DH
#define BK6s02_9C_ADC_DTOP2 0x9C //4EL
#define BK6s02_9D_ADC_DTOP2 0x9D //4EH
#define BK6s02_9E_ADC_DTOP2 0x9E //4FL
#define BK6s02_9F_ADC_DTOP2 0x9F //4FH
#define BK6s02_A0_ADC_DTOP2 0xA0 //50L
#define BK6s02_A1_ADC_DTOP2 0xA1 //50H
#define BK6s02_A2_ADC_DTOP2 0xA2 //51L
#define BK6s02_A3_ADC_DTOP2 0xA3 //51H
#define BK6s02_A4_ADC_DTOP2 0xA4 //52L
#define BK6s02_A5_ADC_DTOP2 0xA5 //52H
#define BK6s02_A6_ADC_DTOP2 0xA6 //53L
#define BK6s02_A7_ADC_DTOP2 0xA7 //53H
#define BK6s02_A8_ADC_DTOP2 0xA8 //54L
#define BK6s02_A9_ADC_DTOP2 0xA9 //54H
#define BK6s02_AA_ADC_DTOP2 0xAA //55L
#define BK6s02_AB_ADC_DTOP2 0xAB //55H
#define BK6s02_AC_ADC_DTOP2 0xAC //56L
#define BK6s02_AD_ADC_DTOP2 0xAD //56H
#define BK6s02_AE_ADC_DTOP2 0xAE //57L
#define BK6s02_AF_ADC_DTOP2 0xAF //57H
#define BK6s02_B0_ADC_DTOP2 0xB0 //58L
#define BK6s02_B1_ADC_DTOP2 0xB1 //58H
#define BK6s02_B2_ADC_DTOP2 0xB2 //59L
#define BK6s02_B3_ADC_DTOP2 0xB3 //59H
#define BK6s02_B4_ADC_DTOP2 0xB4 //5AL
#define BK6s02_B5_ADC_DTOP2 0xB5 //5AH
#define BK6s02_B6_ADC_DTOP2 0xB6 //5BL
#define BK6s02_B7_ADC_DTOP2 0xB7 //5BH
#define BK6s02_B8_ADC_DTOP2 0xB8 //5CL
#define BK6s02_B9_ADC_DTOP2 0xB9 //5CH
#define BK6s02_BA_ADC_DTOP2 0xBA //5DL
#define BK6s02_BB_ADC_DTOP2 0xBB //5DH
#define BK6s02_BC_ADC_DTOP2 0xBC //5EL
#define BK6s02_BD_ADC_DTOP2 0xBD //5EH
#define BK6s02_BE_ADC_DTOP2 0xBE //5FL
#define BK6s02_BF_ADC_DTOP2 0xBF //5FH
#define BK6s02_C0_ADC_DTOP2 0xC0 //60L
#define BK6s02_C1_ADC_DTOP2 0xC1 //60H
#define BK6s02_C2_ADC_DTOP2 0xC2 //61L
#define BK6s02_C3_ADC_DTOP2 0xC3 //61H
#define BK6s02_C4_ADC_DTOP2 0xC4 //62L
#define BK6s02_C5_ADC_DTOP2 0xC5 //62H
#define BK6s02_C6_ADC_DTOP2 0xC6 //63L
#define BK6s02_C7_ADC_DTOP2 0xC7 //63H
#define BK6s02_C8_ADC_DTOP2 0xC8 //64L
#define BK6s02_C9_ADC_DTOP2 0xC9 //64H
#define BK6s02_CA_ADC_DTOP2 0xCA //65L
#define BK6s02_CB_ADC_DTOP2 0xCB //65H
#define BK6s02_CC_ADC_DTOP2 0xCC //66L
#define BK6s02_CD_ADC_DTOP2 0xCD //66H
#define BK6s02_CE_ADC_DTOP2 0xCE //67L
#define BK6s02_CF_ADC_DTOP2 0xCF //67H
#define BK6s02_D0_ADC_DTOP2 0xD0 //68L
#define BK6s02_D1_ADC_DTOP2 0xD1 //68H
#define BK6s02_D2_ADC_DTOP2 0xD2 //69L
#define BK6s02_D3_ADC_DTOP2 0xD3 //69H
#define BK6s02_D4_ADC_DTOP2 0xD4 //6AL
#define BK6s02_D5_ADC_DTOP2 0xD5 //6AH
#define BK6s02_D6_ADC_DTOP2 0xD6 //6BL
#define BK6s02_D7_ADC_DTOP2 0xD7 //6BH
#define BK6s02_D8_ADC_DTOP2 0xD8 //6CL
#define BK6s02_D9_ADC_DTOP2 0xD9 //6CH
#define BK6s02_DA_ADC_DTOP2 0xDA //6DL
#define BK6s02_DB_ADC_DTOP2 0xDB //6DH
#define BK6s02_DC_ADC_DTOP2 0xDC //6EL
#define BK6s02_DD_ADC_DTOP2 0xDD //6EH
#define BK6s02_DE_ADC_DTOP2 0xDE //6FL
#define BK6s02_DF_ADC_DTOP2 0xDF //6FH
#define BK6s02_E0_ADC_DTOP2 0xE0 //70L
#define BK6s02_E1_ADC_DTOP2 0xE1 //70H
#define BK6s02_E2_ADC_DTOP2 0xE2 //71L
#define BK6s02_E3_ADC_DTOP2 0xE3 //71H
#define BK6s02_E4_ADC_DTOP2 0xE4 //72L
#define BK6s02_E5_ADC_DTOP2 0xE5 //72H
#define BK6s02_E6_ADC_DTOP2 0xE6 //73L
#define BK6s02_E7_ADC_DTOP2 0xE7 //73H
#define BK6s02_E8_ADC_DTOP2 0xE8 //74L
#define BK6s02_E9_ADC_DTOP2 0xE9 //74H
#define BK6s02_EA_ADC_DTOP2 0xEA //75L
#define BK6s02_EB_ADC_DTOP2 0xEB //75H
#define BK6s02_EC_ADC_DTOP2 0xEC //76L
#define BK6s02_ED_ADC_DTOP2 0xED //76H
#define BK6s02_EE_ADC_DTOP2 0xEE //77L
#define BK6s02_EF_ADC_DTOP2 0xEF //77H
#define BK6s02_F0_ADC_DTOP2 0xF0 //78L
#define BK6s02_F1_ADC_DTOP2 0xF1 //78H
#define BK6s02_F2_ADC_DTOP2 0xF2 //79L
#define BK6s02_F3_ADC_DTOP2 0xF3 //79H
#define BK6s02_F4_ADC_DTOP2 0xF4 //7AL
#define BK6s02_F5_ADC_DTOP2 0xF5 //7AH
#define BK6s02_F6_ADC_DTOP2 0xF6 //7BL
#define BK6s02_F7_ADC_DTOP2 0xF7 //7BH
#define BK6s02_F8_ADC_DTOP2 0xF8 //7CL
#define BK6s02_F9_ADC_DTOP2 0xF9 //7CH
#define BK6s02_FA_ADC_DTOP2 0xFA //7DL
#define BK6s02_FB_ADC_DTOP2 0xFB //7DH
#define BK6s02_FC_ADC_DTOP2 0xFC //7EL
#define BK6s02_FD_ADC_DTOP2 0xFD //7EH
#define BK6s02_FE_ADC_DTOP2 0xFE //7FL
#define BK6s02_FF_ADC_DTOP2 0xFF //7FH
// Bank6 subbank2 ,16bit register addr mode
#define BK6s02_00h_ADC_DTOP2 0x00 //00L
#define BK6s02_01h_ADC_DTOP2 0x02 //01L
#define BK6s02_02h_ADC_DTOP2 0x04 //02L
#define BK6s02_03h_ADC_DTOP2 0x06 //03L
#define BK6s02_04h_ADC_DTOP2 0x08 //04L
#define BK6s02_05h_ADC_DTOP2 0x0A //05L
#define BK6s02_06h_ADC_DTOP2 0x0C //06L
#define BK6s02_07h_ADC_DTOP2 0x0E //07L
#define BK6s02_08h_ADC_DTOP2 0x10 //08L
#define BK6s02_09h_ADC_DTOP2 0x12 //09L
#define BK6s02_0Ah_ADC_DTOP2 0x14 //0AL
#define BK6s02_0Bh_ADC_DTOP2 0x16 //0BL
#define BK6s02_0Ch_ADC_DTOP2 0x18 //0CL
#define BK6s02_0Dh_ADC_DTOP2 0x1A //0DL
#define BK6s02_0Eh_ADC_DTOP2 0x1C //0EL
#define BK6s02_0Fh_ADC_DTOP2 0x1E //0FL
#define BK6s02_10h_ADC_DTOP2 0x20 //10L
#define BK6s02_11h_ADC_DTOP2 0x22 //11L
#define BK6s02_12h_ADC_DTOP2 0x24 //12L
#define BK6s02_13h_ADC_DTOP2 0x26 //13L
#define BK6s02_14h_ADC_DTOP2 0x28 //14L
#define BK6s02_15h_ADC_DTOP2 0x2A //15L
#define BK6s02_16h_ADC_DTOP2 0x2C //16L
#define BK6s02_17h_ADC_DTOP2 0x2E //17L
#define BK6s02_18h_ADC_DTOP2 0x30 //18L
#define BK6s02_19h_ADC_DTOP2 0x32 //19L
#define BK6s02_1Ah_ADC_DTOP2 0x34 //1AL
#define BK6s02_1Bh_ADC_DTOP2 0x36 //1BL
#define BK6s02_1Ch_ADC_DTOP2 0x38 //1CL
#define BK6s02_1Dh_ADC_DTOP2 0x3A //1DL
#define BK6s02_1Eh_ADC_DTOP2 0x3C //1EL
#define BK6s02_1Fh_ADC_DTOP2 0x3E //1FL
#define BK6s02_20h_ADC_DTOP2 0x40 //20L
#define BK6s02_21h_ADC_DTOP2 0x42 //21L
#define BK6s02_22h_ADC_DTOP2 0x44 //22L
#define BK6s02_23h_ADC_DTOP2 0x46 //23L
#define BK6s02_24h_ADC_DTOP2 0x48 //24L
#define BK6s02_25h_ADC_DTOP2 0x4A //25L
#define BK6s02_26h_ADC_DTOP2 0x4C //26L
#define BK6s02_27h_ADC_DTOP2 0x4E //27L
#define BK6s02_28h_ADC_DTOP2 0x50 //28L
#define BK6s02_29h_ADC_DTOP2 0x52 //29L
#define BK6s02_2Ah_ADC_DTOP2 0x54 //2AL
#define BK6s02_2Bh_ADC_DTOP2 0x56 //2BL
#define BK6s02_2Ch_ADC_DTOP2 0x58 //2CL
#define BK6s02_2Dh_ADC_DTOP2 0x5A //2DL
#define BK6s02_2Eh_ADC_DTOP2 0x5C //2EL
#define BK6s02_2Fh_ADC_DTOP2 0x5E //2FL
#define BK6s02_30h_ADC_DTOP2 0x60 //30L
#define BK6s02_31h_ADC_DTOP2 0x62 //31L
#define BK6s02_32h_ADC_DTOP2 0x64 //32L
#define BK6s02_33h_ADC_DTOP2 0x66 //33L
#define BK6s02_34h_ADC_DTOP2 0x68 //34L
#define BK6s02_35h_ADC_DTOP2 0x6A //35L
#define BK6s02_36h_ADC_DTOP2 0x6C //36L
#define BK6s02_37h_ADC_DTOP2 0x6E //37L
#define BK6s02_38h_ADC_DTOP2 0x70 //38L
#define BK6s02_39h_ADC_DTOP2 0x72 //39L
#define BK6s02_3Ah_ADC_DTOP2 0x74 //3AL
#define BK6s02_3Bh_ADC_DTOP2 0x76 //3BL
#define BK6s02_3Ch_ADC_DTOP2 0x78 //3CL
#define BK6s02_3Dh_ADC_DTOP2 0x7A //3DL
#define BK6s02_3Eh_ADC_DTOP2 0x7C //3EL
#define BK6s02_3Fh_ADC_DTOP2 0x7E //3FL
#define BK6s02_40h_ADC_DTOP2 0x80 //40L
#define BK6s02_41h_ADC_DTOP2 0x82 //41L
#define BK6s02_42h_ADC_DTOP2 0x84 //42L
#define BK6s02_43h_ADC_DTOP2 0x86 //43L
#define BK6s02_44h_ADC_DTOP2 0x88 //44L
#define BK6s02_45h_ADC_DTOP2 0x8A //45L
#define BK6s02_46h_ADC_DTOP2 0x8C //46L
#define BK6s02_47h_ADC_DTOP2 0x8E //47L
#define BK6s02_48h_ADC_DTOP2 0x90 //48L
#define BK6s02_49h_ADC_DTOP2 0x92 //49L
#define BK6s02_4Ah_ADC_DTOP2 0x94 //4AL
#define BK6s02_4Bh_ADC_DTOP2 0x96 //4BL
#define BK6s02_4Ch_ADC_DTOP2 0x98 //4CL
#define BK6s02_4Dh_ADC_DTOP2 0x9A //4DL
#define BK6s02_4Eh_ADC_DTOP2 0x9C //4EL
#define BK6s02_4Fh_ADC_DTOP2 0x9E //4FL
#define BK6s02_50h_ADC_DTOP2 0xA0 //50L
#define BK6s02_51h_ADC_DTOP2 0xA2 //51L
#define BK6s02_52h_ADC_DTOP2 0xA4 //52L
#define BK6s02_53h_ADC_DTOP2 0xA6 //53L
#define BK6s02_54h_ADC_DTOP2 0xA8 //54L
#define BK6s02_55h_ADC_DTOP2 0xAA //55L
#define BK6s02_56h_ADC_DTOP2 0xAC //56L
#define BK6s02_57h_ADC_DTOP2 0xAE //57L
#define BK6s02_58h_ADC_DTOP2 0xB0 //58L
#define BK6s02_59h_ADC_DTOP2 0xB2 //59L
#define BK6s02_5Ah_ADC_DTOP2 0xB4 //5AL
#define BK6s02_5Bh_ADC_DTOP2 0xB6 //5BL
#define BK6s02_5Ch_ADC_DTOP2 0xB8 //5CL
#define BK6s02_5Dh_ADC_DTOP2 0xBA //5DL
#define BK6s02_5Eh_ADC_DTOP2 0xBC //5EL
#define BK6s02_5Fh_ADC_DTOP2 0xBE //5FL
#define BK6s02_60h_ADC_DTOP2 0xC0 //60L
#define BK6s02_61h_ADC_DTOP2 0xC2 //61L
#define BK6s02_62h_ADC_DTOP2 0xC4 //62L
#define BK6s02_63h_ADC_DTOP2 0xC6 //63L
#define BK6s02_64h_ADC_DTOP2 0xC8 //64L
#define BK6s02_65h_ADC_DTOP2 0xCA //65L
#define BK6s02_66h_ADC_DTOP2 0xCC //66L
#define BK6s02_67h_ADC_DTOP2 0xCE //67L
#define BK6s02_68h_ADC_DTOP2 0xD0 //68L
#define BK6s02_69h_ADC_DTOP2 0xD2 //69L
#define BK6s02_6Ah_ADC_DTOP2 0xD4 //6AL
#define BK6s02_6Bh_ADC_DTOP2 0xD6 //6BL
#define BK6s02_6Ch_ADC_DTOP2 0xD8 //6CL
#define BK6s02_6Dh_ADC_DTOP2 0xDA //6DL
#define BK6s02_6Eh_ADC_DTOP2 0xDC //6EL
#define BK6s02_6Fh_ADC_DTOP2 0xDE //6FL
#define BK6s02_70h_ADC_DTOP2 0xE0 //70L
#define BK6s02_71h_ADC_DTOP2 0xE2 //71L
#define BK6s02_72h_ADC_DTOP2 0xE4 //72L
#define BK6s02_73h_ADC_DTOP2 0xE6 //73L
#define BK6s02_74h_ADC_DTOP2 0xE8 //74L
#define BK6s02_75h_ADC_DTOP2 0xEA //75L
#define BK6s02_76h_ADC_DTOP2 0xEC //76L
#define BK6s02_77h_ADC_DTOP2 0xEE //77L
#define BK6s02_78h_ADC_DTOP2 0xF0 //78L
#define BK6s02_79h_ADC_DTOP2 0xF2 //79L
#define BK6s02_7Ah_ADC_DTOP2 0xF4 //7AL
#define BK6s02_7Bh_ADC_DTOP2 0xF6 //7BL
#define BK6s02_7Ch_ADC_DTOP2 0xF8 //7CL
#define BK6s02_7Dh_ADC_DTOP2 0xFA //7DL
#define BK6s02_7Eh_ADC_DTOP2 0xFC //7EL
#define BK6s02_7Fh_ADC_DTOP2 0xFE //7FL
//BK7 CHIP TOP
#define BK7_00_CHIPTOP 0x00 //00L
#define BK7_01_CHIPTOP 0x01 //00H
#define BK7_02_CHIPTOP 0x02 //01L
#define BK7_03_CHIPTOP 0x03 //01H
#define BK7_04_CHIPTOP 0x04 //02L
#define BK7_05_CHIPTOP 0x05 //02H
#define BK7_06_CHIPTOP 0x06 //03L
#define BK7_07_CHIPTOP 0x07 //03H
#define BK7_08_CHIPTOP 0x08 //04L
#define BK7_09_CHIPTOP 0x09 //04H
#define BK7_0A_CHIPTOP 0x0A //05L
#define BK7_0B_CHIPTOP 0x0B //05H
#define BK7_0C_CHIPTOP 0x0C //06L
#define BK7_0D_CHIPTOP 0x0D //06H
#define BK7_0E_CHIPTOP 0x0E //07L
#define BK7_0F_CHIPTOP 0x0F //07H
#define BK7_10_CHIPTOP 0x10 //08L
#define BK7_11_CHIPTOP 0x11 //08H
#define BK7_12_CHIPTOP 0x12 //09L
#define BK7_13_CHIPTOP 0x13 //09H
#define BK7_14_CHIPTOP 0x14 //0AL
#define BK7_15_CHIPTOP 0x15 //0AH
#define BK7_16_CHIPTOP 0x16 //0BL
#define BK7_17_CHIPTOP 0x17 //0BH
#define BK7_18_CHIPTOP 0x18 //0CL
#define BK7_19_CHIPTOP 0x19 //0CH
#define BK7_1A_CHIPTOP 0x1A //0DL
#define BK7_1B_CHIPTOP 0x1B //0DH
#define BK7_1C_CHIPTOP 0x1C //0EL
#define BK7_1D_CHIPTOP 0x1D //0EH
#define BK7_1E_CHIPTOP 0x1E //0FL
#define BK7_1F_CHIPTOP 0x1F //0FH
#define BK7_20_CHIPTOP 0x20 //10L
#define BK7_21_CHIPTOP 0x21 //10H
#define BK7_22_CHIPTOP 0x22 //11L
#define BK7_23_CHIPTOP 0x23 //11H
#define BK7_24_CHIPTOP 0x24 //12L
#define BK7_25_CHIPTOP 0x25 //12H
#define BK7_26_CHIPTOP 0x26 //13L
#define BK7_27_CHIPTOP 0x27 //13H
#define BK7_28_CHIPTOP 0x28 //14L
#define BK7_29_CHIPTOP 0x29 //14H
#define BK7_2A_CHIPTOP 0x2A //15L
#define BK7_2B_CHIPTOP 0x2B //15H
#define BK7_2C_CHIPTOP 0x2C //16L
#define BK7_2D_CHIPTOP 0x2D //16H
#define BK7_2E_CHIPTOP 0x2E //17L
#define BK7_2F_CHIPTOP 0x2F //17H
#define BK7_30_CHIPTOP 0x30 //18L
#define BK7_31_CHIPTOP 0x31 //18H
#define BK7_32_CHIPTOP 0x32 //19L
#define BK7_33_CHIPTOP 0x33 //19H
#define BK7_34_CHIPTOP 0x34 //1AL
#define BK7_35_CHIPTOP 0x35 //1AH
#define BK7_36_CHIPTOP 0x36 //1BL
#define BK7_37_CHIPTOP 0x37 //1BH
#define BK7_38_CHIPTOP 0x38 //1CL
#define BK7_39_CHIPTOP 0x39 //1CH
#define BK7_3A_CHIPTOP 0x3A //1DL
#define BK7_3B_CHIPTOP 0x3B //1DH
#define BK7_3C_CHIPTOP 0x3C //1EL
#define BK7_3D_CHIPTOP 0x3D //1EH
#define BK7_3E_CHIPTOP 0x3E //1FL
#define BK7_3F_CHIPTOP 0x3F //1FH
#define BK7_40_CHIPTOP 0x40 //20L
#define BK7_41_CHIPTOP 0x41 //20H
#define BK7_42_CHIPTOP 0x42 //21L
#define BK7_43_CHIPTOP 0x43 //21H
#define BK7_44_CHIPTOP 0x44 //22L
#define BK7_45_CHIPTOP 0x45 //22H
#define BK7_46_CHIPTOP 0x46 //23L
#define BK7_47_CHIPTOP 0x47 //23H
#define BK7_48_CHIPTOP 0x48 //24L
#define BK7_49_CHIPTOP 0x49 //24H
#define BK7_4A_CHIPTOP 0x4A //25L
#define BK7_4B_CHIPTOP 0x4B //25H
#define BK7_4C_CHIPTOP 0x4C //26L
#define BK7_4D_CHIPTOP 0x4D //26H
#define BK7_4E_CHIPTOP 0x4E //27L
#define BK7_4F_CHIPTOP 0x4F //27H
#define BK7_50_CHIPTOP 0x50 //28L
#define BK7_51_CHIPTOP 0x51 //28H
#define BK7_52_CHIPTOP 0x52 //29L
#define BK7_53_CHIPTOP 0x53 //29H
#define BK7_54_CHIPTOP 0x54 //2AL
#define BK7_55_CHIPTOP 0x55 //2AH
#define BK7_56_CHIPTOP 0x56 //2BL
#define BK7_57_CHIPTOP 0x57 //2BH
#define BK7_58_CHIPTOP 0x58 //2CL
#define BK7_59_CHIPTOP 0x59 //2CH
#define BK7_5A_CHIPTOP 0x5A //2DL
#define BK7_5B_CHIPTOP 0x5B //2DH
#define BK7_5C_CHIPTOP 0x5C //2EL
#define BK7_5D_CHIPTOP 0x5D //2EH
#define BK7_5E_CHIPTOP 0x5E //2FL
#define BK7_5F_CHIPTOP 0x5F //2FH
#define BK7_60_CHIPTOP 0x60 //30L
#define BK7_61_CHIPTOP 0x61 //30H
#define BK7_62_CHIPTOP 0x62 //31L
#define BK7_63_CHIPTOP 0x63 //31H
#define BK7_64_CHIPTOP 0x64 //32L
#define BK7_65_CHIPTOP 0x65 //32H
#define BK7_66_CHIPTOP 0x66 //33L
#define BK7_67_CHIPTOP 0x67 //33H
#define BK7_68_CHIPTOP 0x68 //34L
#define BK7_69_CHIPTOP 0x69 //34H
#define BK7_6A_CHIPTOP 0x6A //35L
#define BK7_6B_CHIPTOP 0x6B //35H
#define BK7_6C_CHIPTOP 0x6C //36L
#define BK7_6D_CHIPTOP 0x6D //36H
#define BK7_6E_CHIPTOP 0x6E //37L
#define BK7_6F_CHIPTOP 0x6F //37H
#define BK7_70_CHIPTOP 0x70 //38L
#define BK7_71_CHIPTOP 0x71 //38H
#define BK7_72_CHIPTOP 0x72 //39L
#define BK7_73_CHIPTOP 0x73 //39H
#define BK7_74_CHIPTOP 0x74 //3AL
#define BK7_75_CHIPTOP 0x75 //3AH
#define BK7_76_CHIPTOP 0x76 //3BL
#define BK7_77_CHIPTOP 0x77 //3BH
#define BK7_78_CHIPTOP 0x78 //3CL
#define BK7_79_CHIPTOP 0x79 //3CH
#define BK7_7A_CHIPTOP 0x7A //3DL
#define BK7_7B_CHIPTOP 0x7B //3DH
#define BK7_7C_CHIPTOP 0x7C //3EL
#define BK7_7D_CHIPTOP 0x7D //3EH
#define BK7_7E_CHIPTOP 0x7E //3FL
#define BK7_7F_CHIPTOP 0x7F //3FH
#define BK7_80_CHIPTOP 0x80 //40L
#define BK7_81_CHIPTOP 0x81 //40H
#define BK7_82_CHIPTOP 0x82 //41L
#define BK7_83_CHIPTOP 0x83 //41H
#define BK7_84_CHIPTOP 0x84 //42L
#define BK7_85_CHIPTOP 0x85 //42H
#define BK7_86_CHIPTOP 0x86 //43L
#define BK7_87_CHIPTOP 0x87 //43H
#define BK7_88_CHIPTOP 0x88 //44L
#define BK7_89_CHIPTOP 0x89 //44H
#define BK7_8A_CHIPTOP 0x8A //45L
#define BK7_8B_CHIPTOP 0x8B //45H
#define BK7_8C_CHIPTOP 0x8C //46L
#define BK7_8D_CHIPTOP 0x8D //46H
#define BK7_8E_CHIPTOP 0x8E //47L
#define BK7_8F_CHIPTOP 0x8F //47H
#define BK7_90_CHIPTOP 0x90 //48L
#define BK7_91_CHIPTOP 0x91 //48H
#define BK7_92_CHIPTOP 0x92 //49L
#define BK7_93_CHIPTOP 0x93 //49H
#define BK7_94_CHIPTOP 0x94 //4AL
#define BK7_95_CHIPTOP 0x95 //4AH
#define BK7_96_CHIPTOP 0x96 //4BL
#define BK7_97_CHIPTOP 0x97 //4BH
#define BK7_98_CHIPTOP 0x98 //4CL
#define BK7_99_CHIPTOP 0x99 //4CH
#define BK7_9A_CHIPTOP 0x9A //4DL
#define BK7_9B_CHIPTOP 0x9B //4DH
#define BK7_9C_CHIPTOP 0x9C //4EL
#define BK7_9D_CHIPTOP 0x9D //4EH
#define BK7_9E_CHIPTOP 0x9E //4FL
#define BK7_9F_CHIPTOP 0x9F //4FH
#define BK7_A0_CHIPTOP 0xA0 //50L
#define BK7_A1_CHIPTOP 0xA1 //50H
#define BK7_A2_CHIPTOP 0xA2 //51L
#define BK7_A3_CHIPTOP 0xA3 //51H
#define BK7_A4_CHIPTOP 0xA4 //52L
#define BK7_A5_CHIPTOP 0xA5 //52H
#define BK7_A6_CHIPTOP 0xA6 //53L
#define BK7_A7_CHIPTOP 0xA7 //53H
#define BK7_A8_CHIPTOP 0xA8 //54L
#define BK7_A9_CHIPTOP 0xA9 //54H
#define BK7_AA_CHIPTOP 0xAA //55L
#define BK7_AB_CHIPTOP 0xAB //55H
#define BK7_AC_CHIPTOP 0xAC //56L
#define BK7_AD_CHIPTOP 0xAD //56H
#define BK7_AE_CHIPTOP 0xAE //57L
#define BK7_AF_CHIPTOP 0xAF //57H
#define BK7_B0_CHIPTOP 0xB0 //58L
#define BK7_B1_CHIPTOP 0xB1 //58H
#define BK7_B2_CHIPTOP 0xB2 //59L
#define BK7_B3_CHIPTOP 0xB3 //59H
#define BK7_B4_CHIPTOP 0xB4 //5AL
#define BK7_B5_CHIPTOP 0xB5 //5AH
#define BK7_B6_CHIPTOP 0xB6 //5BL
#define BK7_B7_CHIPTOP 0xB7 //5BH
#define BK7_B8_CHIPTOP 0xB8 //5CL
#define BK7_B9_CHIPTOP 0xB9 //5CH
#define BK7_BA_CHIPTOP 0xBA //5DL
#define BK7_BB_CHIPTOP 0xBB //5DH
#define BK7_BC_CHIPTOP 0xBC //5EL
#define BK7_BD_CHIPTOP 0xBD //5EH
#define BK7_BE_CHIPTOP 0xBE //5FL
#define BK7_BF_CHIPTOP 0xBF //5FH
#define BK7_C0_CHIPTOP 0xC0 //60L
#define BK7_C1_CHIPTOP 0xC1 //60H
#define BK7_C2_CHIPTOP 0xC2 //61L
#define BK7_C3_CHIPTOP 0xC3 //61H
#define BK7_C4_CHIPTOP 0xC4 //62L
#define BK7_C5_CHIPTOP 0xC5 //62H
#define BK7_C6_CHIPTOP 0xC6 //63L
#define BK7_C7_CHIPTOP 0xC7 //63H
#define BK7_C8_CHIPTOP 0xC8 //64L
#define BK7_C9_CHIPTOP 0xC9 //64H
#define BK7_CA_CHIPTOP 0xCA //65L
#define BK7_CB_CHIPTOP 0xCB //65H
#define BK7_CC_CHIPTOP 0xCC //66L
#define BK7_CD_CHIPTOP 0xCD //66H
#define BK7_CE_CHIPTOP 0xCE //67L
#define BK7_CF_CHIPTOP 0xCF //67H
#define BK7_D0_CHIPTOP 0xD0 //68L
#define BK7_D1_CHIPTOP 0xD1 //68H
#define BK7_D2_CHIPTOP 0xD2 //69L
#define BK7_D3_CHIPTOP 0xD3 //69H
#define BK7_D4_CHIPTOP 0xD4 //6AL
#define BK7_D5_CHIPTOP 0xD5 //6AH
#define BK7_D6_CHIPTOP 0xD6 //6BL
#define BK7_D7_CHIPTOP 0xD7 //6BH
#define BK7_D8_CHIPTOP 0xD8 //6CL
#define BK7_D9_CHIPTOP 0xD9 //6CH
#define BK7_DA_CHIPTOP 0xDA //6DL
#define BK7_DB_CHIPTOP 0xDB //6DH
#define BK7_DC_CHIPTOP 0xDC //6EL
#define BK7_DD_CHIPTOP 0xDD //6EH
#define BK7_DE_CHIPTOP 0xDE //6FL
#define BK7_DF_CHIPTOP 0xDF //6FH
#define BK7_E0_CHIPTOP 0xE0 //70L
#define BK7_E1_CHIPTOP 0xE1 //70H
#define BK7_E2_CHIPTOP 0xE2 //71L
#define BK7_E3_CHIPTOP 0xE3 //71H
#define BK7_E4_CHIPTOP 0xE4 //72L
#define BK7_E5_CHIPTOP 0xE5 //72H
#define BK7_E6_CHIPTOP 0xE6 //73L
#define BK7_E7_CHIPTOP 0xE7 //73H
#define BK7_E8_CHIPTOP 0xE8 //74L
#define BK7_E9_CHIPTOP 0xE9 //74H
#define BK7_EA_CHIPTOP 0xEA //75L
#define BK7_EB_CHIPTOP 0xEB //75H
#define BK7_EC_CHIPTOP 0xEC //76L
#define BK7_ED_CHIPTOP 0xED //76H
#define BK7_EE_CHIPTOP 0xEE //77L
#define BK7_EF_CHIPTOP 0xEF //77H
#define BK7_F0_CHIPTOP 0xF0 //78L
#define BK7_F1_CHIPTOP 0xF1 //78H
#define BK7_F2_CHIPTOP 0xF2 //79L
#define BK7_F3_CHIPTOP 0xF3 //79H
#define BK7_F4_CHIPTOP 0xF4 //7AL
#define BK7_F5_CHIPTOP 0xF5 //7AH
#define BK7_F6_CHIPTOP 0xF6 //7BL
#define BK7_F7_CHIPTOP 0xF7 //7BH
#define BK7_F8_CHIPTOP 0xF8 //7CL
#define BK7_F9_CHIPTOP 0xF9 //7CH
#define BK7_FA_CHIPTOP 0xFA //7DL
#define BK7_FB_CHIPTOP 0xFB //7DH
#define BK7_FC_CHIPTOP 0xFC //7EL
#define BK7_FD_CHIPTOP 0xFD //7EH
#define BK7_FE_CHIPTOP 0xFE //7FL
#define BK7_FF_CHIPTOP 0xFF //7FH
// Bank7,16bit register addr mode
#define BK7_00h_CHIPTOP 0x00 //00L
#define BK7_01h_CHIPTOP 0x02 //01L
#define BK7_02h_CHIPTOP 0x04 //02L
#define BK7_03h_CHIPTOP 0x06 //03L
#define BK7_04h_CHIPTOP 0x08 //04L
#define BK7_05h_CHIPTOP 0x0A //05L
#define BK7_06h_CHIPTOP 0x0C //06L
#define BK7_07h_CHIPTOP 0x0E //07L
#define BK7_08h_CHIPTOP 0x10 //08L
#define BK7_09h_CHIPTOP 0x12 //09L
#define BK7_0Ah_CHIPTOP 0x14 //0AL
#define BK7_0Bh_CHIPTOP 0x16 //0BL
#define BK7_0Ch_CHIPTOP 0x18 //0CL
#define BK7_0Dh_CHIPTOP 0x1A //0DL
#define BK7_0Eh_CHIPTOP 0x1C //0EL
#define BK7_0Fh_CHIPTOP 0x1E //0FL
#define BK7_10h_CHIPTOP 0x20 //10L
#define BK7_11h_CHIPTOP 0x22 //11L
#define BK7_12h_CHIPTOP 0x24 //12L
#define BK7_13h_CHIPTOP 0x26 //13L
#define BK7_14h_CHIPTOP 0x28 //14L
#define BK7_15h_CHIPTOP 0x2A //15L
#define BK7_16h_CHIPTOP 0x2C //16L
#define BK7_17h_CHIPTOP 0x2E //17L
#define BK7_18h_CHIPTOP 0x30 //18L
#define BK7_19h_CHIPTOP 0x32 //19L
#define BK7_1Ah_CHIPTOP 0x34 //1AL
#define BK7_1Bh_CHIPTOP 0x36 //1BL
#define BK7_1Ch_CHIPTOP 0x38 //1CL
#define BK7_1Dh_CHIPTOP 0x3A //1DL
#define BK7_1Eh_CHIPTOP 0x3C //1EL
#define BK7_1Fh_CHIPTOP 0x3E //1FL
#define BK7_20h_CHIPTOP 0x40 //20L
#define BK7_21h_CHIPTOP 0x42 //21L
#define BK7_22h_CHIPTOP 0x44 //22L
#define BK7_23h_CHIPTOP 0x46 //23L
#define BK7_24h_CHIPTOP 0x48 //24L
#define BK7_25h_CHIPTOP 0x4A //25L
#define BK7_26h_CHIPTOP 0x4C //26L
#define BK7_27h_CHIPTOP 0x4E //27L
#define BK7_28h_CHIPTOP 0x50 //28L
#define BK7_29h_CHIPTOP 0x52 //29L
#define BK7_2Ah_CHIPTOP 0x54 //2AL
#define BK7_2Bh_CHIPTOP 0x56 //2BL
#define BK7_2Ch_CHIPTOP 0x58 //2CL
#define BK7_2Dh_CHIPTOP 0x5A //2DL
#define BK7_2Eh_CHIPTOP 0x5C //2EL
#define BK7_2Fh_CHIPTOP 0x5E //2FL
#define BK7_30h_CHIPTOP 0x60 //30L
#define BK7_31h_CHIPTOP 0x62 //31L
#define BK7_32h_CHIPTOP 0x64 //32L
#define BK7_33h_CHIPTOP 0x66 //33L
#define BK7_34h_CHIPTOP 0x68 //34L
#define BK7_35h_CHIPTOP 0x6A //35L
#define BK7_36h_CHIPTOP 0x6C //36L
#define BK7_37h_CHIPTOP 0x6E //37L
#define BK7_38h_CHIPTOP 0x70 //38L
#define BK7_39h_CHIPTOP 0x72 //39L
#define BK7_3Ah_CHIPTOP 0x74 //3AL
#define BK7_3Bh_CHIPTOP 0x76 //3BL
#define BK7_3Ch_CHIPTOP 0x78 //3CL
#define BK7_3Dh_CHIPTOP 0x7A //3DL
#define BK7_3Eh_CHIPTOP 0x7C //3EL
#define BK7_3Fh_CHIPTOP 0x7E //3FL
#define BK7_40h_CHIPTOP 0x80 //40L
#define BK7_41h_CHIPTOP 0x82 //41L
#define BK7_42h_CHIPTOP 0x84 //42L
#define BK7_43h_CHIPTOP 0x86 //43L
#define BK7_44h_CHIPTOP 0x88 //44L
#define BK7_45h_CHIPTOP 0x8A //45L
#define BK7_46h_CHIPTOP 0x8C //46L
#define BK7_47h_CHIPTOP 0x8E //47L
#define BK7_48h_CHIPTOP 0x90 //48L
#define BK7_49h_CHIPTOP 0x92 //49L
#define BK7_4Ah_CHIPTOP 0x94 //4AL
#define BK7_4Bh_CHIPTOP 0x96 //4BL
#define BK7_4Ch_CHIPTOP 0x98 //4CL
#define BK7_4Dh_CHIPTOP 0x9A //4DL


#define DSP_10 0x10
#define DSP_11 0x11
#define DSP_20 0x20
#define DSP_21 0x21
#define DSP_14 0x14
#define DSP_18 0x18
#define DSP_2A 0x2A
#define DSP_3C 0x3C
#define DSP_84 0x84
#define DSP_00 0x00
#define DSP_0F 0x0F
#define DSP_3A 0x3A
#define DSP_3B 0x3B

//=====================================================================

//---------------------------OSD register-------------------
// osd double buffer control
#define OSD_01_OSDDBC 0x01
// osd start position
#define OSD_02_OHSTA_L 0x02
#define OSD_03_OHSTA_H 0x03
#define OSD_04_OVSTA_L 0x04
#define OSD_05_OVSTA_H 0x05
// osd size controol
#define OSD_06_OSDW 0x06
#define OSD_07_OSDH 0x07
// osd space control
#define OSD_08_OHSPA 0x08
#define OSD_09_OVSPA 0x09
#define OSD_0A_OSPW 0x0A
#define OSD_0B_OSPH 0x0B
// internal osd control
#define OSD_0C_IOSDC1 0x0C
#define MWIN_B _BIT0
#define OSD_0D_IOSDC2 0x0D
#define OSD_0E_IOSDC3 0x0E
#define OSD_10_IOSDC4 0x10
//osd windodw shadow control
#define OSD_0F_OSHC 0x0F
//osd code buffer offset/ base address
#define OSD_12_OCBUFO 0x12
#define OSD_13_OSDBA_L 0x13
#define OSD_14_OSDBA_H 0x14
// osd gradually color control
#define OSD_15_GCCTRL 0x15
#define OSD_16_GRADCLR 0x16
// osd horizontal gradullay color
#define OSD_17_HGRADCR 0x17
#define OSD_18_HGRADCG 0x18
#define OSD_19_HGRADCB 0x19
#define OSD_1A_HGRADSR 0x1A
#define OSD_1B_HGRADSG 0x1B
#define OSD_1C_HGRADSB 0x1C
// osd vertical gradullay color
#define OSD_1D_VGRADCR 0x1D
#define OSD_1E_VGRADCG 0x1E
#define OSD_1F_VGRADCB 0x1F
#define OSD_20_VGRADSR 0x20
#define OSD_21_VGRADSG 0x21
#define OSD_22_VGRADSB 0x22
//
#define OSD_26_TIMECTRL 0x26
#define OSD_27_OSDRTP 0x27
// osd color palette
#define OSD_28_CLR0R 0x28
#define OSD_29_CLR0G 0x29
#define OSD_2A_CLR0B 0x2A
#define OSD_2B_CLR1R 0x2B
#define OSD_2C_CLR1G 0x2C
#define OSD_2D_CLR1B 0x2D
#define OSD_2E_CLR2R 0x2E
#define OSD_2F_CLR2G 0x2F
#define OSD_30_CLR2B 0x30
#define OSD_31_CLR3R 0x31
#define OSD_32_CLR3G 0x32
#define OSD_33_CLR3B 0x33
#define OSD_34_CLR4R 0x34
#define OSD_35_CLR4G 0x35
#define OSD_36_CLR4B 0x36
#define OSD_37_CLR5R 0x37
#define OSD_38_CLR5G 0x38
#define OSD_39_CLR5B 0x39
#define OSD_3A_CLR6R 0x3A
#define OSD_3B_CLR6G 0x3B
#define OSD_3C_CLR6B 0x3C
#define OSD_3D_CLR7R 0x3D
#define OSD_3E_CLR7G 0x3E
#define OSD_3F_CLR7B 0x3F
//
#define OSD_40_SCRLSPD 0x40
#define OSD_41_SCRLLINE 0x41
#define OSD_42_UNDERLINE 0x42
#define OSD_43_TRUNCATE 0x43
#define OSD_44_ITALIC 0x44
#define OSD_45_MISC_CTL 0x45
#define OSD_46_OSD4CFFA 0x46


//---------------------------MCU register-------------------
// ISP control
#define sfRegs ((unsigned char volatile xdata *)0xC000)
#define ISP_DEVA 0xC000 // ISP device address
#define ISP_PWD1 0xC001 // ISP password 1
#define ISP_PWD2 0xC002 // ISP password 2
#define ISP_PWD3 0xC003 // ISP password 3
#define ISP_PWD4 0xC004 // ISP password 4
#define ISP_PWD5 0xC005 // ISP password 5
#define SOFT_ISP 0xC006 // Write 93h to enable ISP mode

// Watch dog control
#define WDT_KEY_L 0xC008 // Default:0xAA
#define WDT_KEY_H 0xC009 // Default:0x55

// Serial DEBUG control
#define SR_DB_CTRL 0xC00A //[7:1]:Serial DEBUG mode device address;[0]:Disable

// DDC2BI control
#define DDC2BI_INT_EN 0xC010 // DDC 2Bi interrupt enable

#define DDC2BI_FLAG 0xC011 // DDC 2Bi interrupt flag and clear
#define DDC2BI_W_BUF 0xC012 // DDC 2Bi write, MCU read buffer
#define DDC2BI_R_BUF 0xC013 // DDC 2Bi read, MCU write buffer
#define DDC2BI_CTRL 0xC018 //
#define DDC2BI_ID 0xC019 //


// I/O port control
#define P0_CTRL 0xC030 // MCU port 0 output enable control
#define P0_OE 0xC031 // MCU port 0 output enable
#define P0_IN 0xC032 // MCU port 0 output enable from output data
#define P1_CTRL 0xC033 // MCU port 1 output enable control
#define P1_OE 0xC034 // MCU port 1 output enable
#define P1_IN 0xC035 // MCU port 1 output enable from output data
#define P2_CTRL 0xC036 // MCU port 2 output enable control
#define P2_OE 0xC037 // MCU port 2 output enable
#define P2_IN 0xC038 // MCU port 2 output enable from output data
#define P3_CTRL 0xC039 // MCU port 3 output enable control
#define P3_OE 0xC03A // MCU port 3 output enable
#define P3_IN 0xC03B // MCU port 3 output enable from output data
#define P4_CTRL 0xC03C // MCU port 4 output enable control
#define P4_OE 0xC03D // MCU port 4 output enable
#define P4_IN 0xC03E // MCU port 4 output enable from output data


// Parallel flash ISP control
#define ISP_PA_0 0xC050 // Parallel flash ISP address[7:0]
#define ISP_PA_1 0xC051 // Parallel flash ISP address[15:8]
#define ISP_PA_2 0xC052 // [1:0]:Parallel flash ISP address[17:16]
#define ISP_PD_W 0xC053 // Parallel flash ISP write data
#define ISP_PCTR 0xC054 // Parallel flash ISP control
#define ISP_PD_R 0xC055 // Parallel flash ISP mode read data

//=====================================================================


