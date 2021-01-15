RegUnitType code tProgMsAvPort[] =
{
	{BK0_00_REGBK, REG_BANK_SCALER},
	{BK0_02_ISELECT, 0x0C}, // input inactive/freerun && composite sync
	{BK0_03_IPCTRL2, BK0_03_SYNC_Sample_Edge},
	{BK0_04_ISCTRL, 0x10}, //default value
	{BK0_10_COCTRL1, 0x20}, // COCTRL1: Analog Video Input Select

	{_END_OF_TBL_, 0x00},
};

RegUnitType code tInitializeScaler[] =
{
	// Initialize scaler table
	{BK0_00_REGBK, REG_BANK_SCALER},

	#if ( VCOM_DC_Ctrl == PWM_TYPE_PWM4 || VCOM_DC_Ctrl == PWM_TYPE_PWM3 )
	{BK0_87_DEBUG, _BIT3 | _BIT1},
	#else
	{BK0_87_DEBUG, _BIT3}, // 20051003 John: PLL test register protect
	#endif

	{BK0_01_DBFC, 0x00}, // Disable double buffer load at vertical blanking
	{BK0_02_ISELECT, 0x80}, //no input source, free run

	#if ( PANEL_ANALOG_TCON )
	{BK0_0D_LYL, 0x07}, // Lock Y line: 20051227.Daniel for weak signal cause panel crash
	{BK0_36_VDSUSG, 0x10},
	#else
	{BK0_0D_LYL, 0x03}, // Lock Y line: 20051227.Daniel for weak signal cause panel crash
	{BK0_36_VDSUSG, 0x00},
	#endif

	{BK0_0E_INTLX, 0x84}, // Using external field, enable long count
	{BK0_11_COCTRL2, 0x10},//08}, // enable coast window start for SOG/SOY(YPBPR)
	{BK0_12_COCTRL3, 0x10},//08}, // enable coast window end for SOG/SOY(YPBPR)

	{BK0_16_INTCTROL, 0x01}, // 060525 seven for SI2C

	// interrupt control
	{BK0_17_INTPULSE, 0x0f}, // interrupt pulse width by reference clock
	{BK0_18_INTSTA, 0x00}, // interrupt status byte A

	// clock generator
	{BK0_21_PLLCTRL2, 0x00}, // PLLCTRL2

	// master pll
	#if (MST_CLOCK_KHZ == 14318)
	{BK0_22_MPL_M, 0x6F}, // set master pll as 215 MHz & drive current
	#elif (MST_CLOCK_KHZ == 12000)
	{BK0_22_MPL_M, 0x72}, // set master pll as 215 MHz & drive current
	#endif

	// spectrum control
	#if( PANEL_TYPE == PanelCPT102_LVDS )
	{BK0_23_OPL_CTL0, 0x00}, //bit[4:0]=5'h0,LPLL_M =1
	#else
	{BK0_23_OPL_CTL0, 0x40}, //bit[4:0]=5'h0,LPLL_M =1
	#endif

	{BK0_28_OPL_STEP0, 0x19},

	#if( SCALER_TYPE == MARIA9 )
	{BK0_29_OPL_STEP1, 0x00},
	#else
	{BK0_29_OPL_STEP1, 0x01},
	#endif

	{BK0_2A_OPL_SPAN0, 0xec},
	{BK0_2B_OPL_SPAN1, 0x00}, // OPL_SET sotres frame-based value

	// output dclk setting
	{BK0_24_OPL_CTL1, 0x03 }, //bit[4:3]:LPLL_P; bit[2:0]:LPLL_ICTL =3'b011

	{BK0_2C_MPL_TST, 0xC0}, // 20050520 Hans for MariaC
	{BK0_2D_OPL_TSTA0, 0x00}, // 20051003 John

	#if (PANEL_LVDS)
	{BK0_2E_OPL_TSTA1, 0x01}, // bit[1:0]:LPLL_K =2'b01 ,bit[2]:LPLL_TYPE,"0":LVDS,"1":TTL
	#else
	{BK0_2E_OPL_TSTA1, _BIT2 | 0x01}, // bit[1:0]:LPLL_K =2'b01 ,bit[2]:LPLL_TYPE,"0":LVDS,"1":TTL
	#endif

	{BK0_40_VFDEST_L, LOBYTE ( PANEL_DE_VSTART ) }, // vertical DE start
	{BK0_41_VFDEST_H, HIBYTE ( PANEL_DE_VSTART ) }, // vertical DE start

	{BK0_42_HFDEST_L, LOBYTE ( PanelHStart ) }, // horizontal DE start
	{BK0_43_HFDEST_H, HIBYTE ( PanelHStart ) }, // horizontal DE start

	{BK0_44_VFDEEND_L, LOBYTE ( PanelHeight - 1 ) }, // vertical DE end
	{BK0_45_VFDEEND_H, HIBYTE ( PanelHeight - 1 ) }, // vertical DE end

	{BK0_46_HFDEEND_L, LOBYTE ( PanelHStart + PanelWidth ) }, // horizontal DE end
	{BK0_47_HFDEEND_H, HIBYTE ( PanelHStart + PanelWidth ) }, // horizontal DE end

	// scaling image window size
	{BK0_48_SIHST_L, LOBYTE ( PanelHStart ) }, // Image H start
	{BK0_49_SIHST_H, HIBYTE ( PanelHStart ) }, // Image H start
	{BK0_4C_SIHEND_L, LOBYTE ( PanelHStart + PanelWidth - 1 ) }, // Image H end
	{BK0_4D_SIHEND_H, HIBYTE ( PanelHStart + PanelWidth - 1 ) }, // Image H end

	{BK0_4A_SIVEND_L, LOBYTE ( PanelHeight - 1 ) }, // Image V end
	{BK0_4B_SIVEND_H, HIBYTE ( PanelHeight - 1 ) }, // Image V end

	// output Sync timing
	{BK0_4E_VDTOT_L, LOBYTE ( PanelVTotal - 1 ) }, // output vtotal
	{BK0_4F_VDTOT_H, HIBYTE ( PanelVTotal - 1 ) },


	#if ( PANEL_DIGITAL_TCON || PANEL_ANALOG_TCON )
	{BK0_50_VSST_L, LOBYTE ( ( PanelVTotal - PanelVStart ) | 0x800 ) }, // vsync start position
	{BK0_51_VSST_H, HIBYTE ( ( PanelVTotal - PanelVStart ) | 0x800 ) },
	#else
	{BK0_50_VSST_L, LOBYTE ( PanelVTotal - PanelVStart ) }, // vsync start position
	{BK0_51_VSST_H, HIBYTE ( PanelVTotal - PanelVStart ) },
	#endif

	{BK0_52_VSEND_L, LOBYTE ( PanelVTotal - PanelVSyncBackPorch ) }, // vsync end position
	{BK0_53_VSEND_H, HIBYTE ( PanelVTotal - PanelVSyncBackPorch ) },

	{BK0_54_HDTOT_L, LOBYTE ( PanelHTotal - 1 ) }, // output htotal
	{BK0_55_HDTOT_H, HIBYTE ( PanelHTotal - 1 ) },

	{BK0_56_HSEND, PanelHSyncWidth - 1 }, // hsync end

	// dither control
	#if PanelDither == 6

	#if ( PANEL_TYPE == PanelAU102_DT )
	{BK0_60_DITHCTRL, 0x0F},
	#elif ( PANEL_TYPE == PanelINNPLUX08_DT )
	{BK0_60_DITHCTRL, 0x03},
	#elif ( PANEL_TYPE == PanelCPT102_LVDS )
	{BK0_60_DITHCTRL, 0x03},
	#else
	{BK0_60_DITHCTRL, 0x05},
	#endif

	#else

	{BK0_60_DITHCTRL, 0x00},
	// {BK0_60_DITHCTRL, 0x0d}, //20050623 David tune for Gray levels is not smooth
	#endif

	{BK0_61_DITHCOEF, 0x2d}, // Dither coefficient

	{BK0_86_FNTN_TEST, ( ( PanelSwapRB & RB_SWAP_B ) | ( PanelSwap6BitML & LM_SWAP6_B ) | ( PanelSwap8BitML & LM_SWAP8_B ) ) },

	// output sync control
	{BK0_B1_SYNC_CONTROL, ( PanelDClkDelay << 4 ) | ( CLK_INV_B & PanelInvDClk ) | ( DE_INV_B & PanelInvDE ) | ( VS_INV_B & PanelInvVSync ) | ( HS_INV_B & PanelInvHSync ) },

	{BK0_89_SL_TUNE_1, 0x7F},

	{BK0_8A_SL_TUNE_2, 0x01}, // Auto tune clock factor limit
	{BK0_8B_SL_TUNE_3, 0x04}, // Auto tune clock factor limit

	// Initialize Common table

	{BK0_C4, 0xFF},
	{BK0_C5, 0x07}, //set max vtotal

	// initialize auto adjust
	{BK0_CB_ATOCTRL, 0x01}, // enable auto position
	{BK0_DB_ATPCTRL, 0x19}, // enable auto phase, mask 6 bits
	{BK0_C8_ATGCTRL, 0x00}, // disable auto Gain
	{BK0_DA_ATPTTH, 0x1c}, // auto phase text threshold for ATPV4

	// VSync status
	// {BK0_9B, 0x30}, // locking Htotal margin
	// {BK0_9E, 0x20}, // locking SSC margin

	// sync change tolerance
	{BK0_E8_HSTOL, 0x10},
	{BK0_E9_VSTOL, 0x08},

	{BK0_F7_TEST_BUS_SELECT, 0xC8},
	{BK0_F8_TEST_MODE, 0x00},

	{_END_OF_TBL_, 0x00}
};

RegUnitType code tInitializeADC[] =
{
	// Initialize ADC/DVI table
	{BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU},

	// ADC setting
	{BK1_0E_FCOEF, 0x09}, // PLL FCOEF: For AV
	{BK1_16_DITHCTRL, 0x70}, // DITHCTRL 20050518 Apple for MariaC

	{BK1_1F, 0x55}, // 20051004 Lizst: ADC current control
	{BK1_22_TESTD2, 0x40}, // 20051004 Lizst: ADC current control

	{BK1_23_FPLL_STATUS, 0x24}, // ???: For CVBS

	{BK1_33, 0x18}, // SOG filter bandwitdh: 4.0MHz
	{BK1_34, 0x10}, // 20051007
	{BK1_35, 0x08}, // SOG trigger level for SOG/SOY(YPBPR)

	{BK1_3D, 0x14}, // ???: For CVBS
	{BK1_3E, 0x82}, // ???: For CVBS
	{BK1_3F, 0xA4}, // TST_MISC[29:24]: For CVBS
	{BK1_41, 0x88}, // ???: For CVBS
	{BK1_42, 0x80}, // ???: For CVBS

	{BK1_90_SARADC_CTRL, 0x20}, // SARADC_CTRL
	
	// {BK1_91, 0x20}, // SARADC_SAMPRD
	
	{BK1_92_SARADC_AISEL, 0x00}, // init SAR port to GPIO

	{BK1_9C, 0x05}, // 20061027 tony

	#if (( SCALER_TYPE == MARIA9 ) && PANEL_LVDS )
	{BK1_A0_RG_DRV, 0x15}, // BK1_A0[7:6]= 00 ,GOUT4 ~ GOUT7 are GPIOs in LVDS mode
	#else
	{BK1_A0_RG_DRV, 0x55},
	#endif
	
	{BK1_A1_BS_DRV, 0x55},
	{BK1_A2_CTR_DRV, 0x55},

	{BK1_B6_LCK_THR_FPLL, 0x40},

	{BK1_BF_LPLL_STLMT_H, 0x01},
	{BK1_B9_COEF_FPLL, 0x7F}, // By RD:John COEFF_FPLL
	
	// {BK1_C2, 0x17=default}, // Limit adjust line/pixel number
	
	{BK1_C3_IVS_DIFF_THR, 0x1A}, // Iuput v sync different threshold
	{BK1_C4_IVS_STALBE_THR, 0x07}, // Input v sync stable threshold

	{BK1_C5_CH_CH_MODE, 0x03},

	//{BK1_F4_PWM1C, 0x00}, //0x80}, // PWM1 coarse adjustment
	//{BK1_F5_PWM2C, 0x80}, // PWM2 coarse adjustment

	//{BK1_F6_PWM1EPL, 0x00},
	//{BK1_F7_PWM1EPH, 0xFF},

	//{BK1_FC_PWM6L, 0x01}, // PWM6 freq for count input clock
	//{BK1_FD_PWM6H, 0x01}, // PWM6 freq for count input clock

	{BK0_00_REGBK, REG_BANK4_LVDS_CCFL},

	{BK4_22, 0x00},//0xFF},

	{BK0_00_REGBK, REG_BANK_SCALER},

	{_END_OF_TBL_, 0x00}
};

RegUnitType code tInitializeVFE[] =
{
	{BK0_00_REGBK, REG_BANK2_VD}, // select register bank VFE

	{BK2_15_FPGA_CTRL, 0x82}, // FPGA_CTRL
	
	#if ( SCALER_TYPE == MARIA9 )
	#if ENABLE_VD_32FSC
	{BK2_17_FSC_SEL, 0xF9}, // CLK_CTRL
	#else//For 8FSC(Following M2)
	{BK2_17_FSC_SEL, 0xB9}, // CLK_CTRL
	#endif
	#else
	{BK2_17_FSC_SEL, 0xF9},
	#endif

	{BK2_1E_REG_DSP_EN, 0x80}, // enable SW DSP

	{BK2_23_APLL_TRANGE, 0x80},
	{BK2_26_APL_K1_NORMAL, 0x20},
	{BK2_27_APL_K2_NORMAL, 0x08},

	// {BK2_28_APL_K1_VCR, 0x20},
	{BK2_3C_HV_CTRL1, 0x1A},
	{BK2_4A_AGC_LOWTH, 0xFF}, // AGC_LOWTH 20051117.MH.Liao for AGC
	{BK2_4E_BK_WINDOW1, 0x25}, // BK_WINDOW1
	
	{BK2_5A_BRST_UNKNOW_TH, 0x20}, // BRST_UNKNOWN_TH
	
	{BK2_62, 0x10}, // AP_SYNTH2REAGC 20051117.MH.Liao for AGC redo {BK2_2F_BLACK_SEL, 0x24},

	{BK2_67_WP_REDO, 0x07}, // 20051208 0x07}, // 20051004 David.Shen

	// {BK2_6A_VCR_DETECT1, 0x91},

	#if( SCALER_TYPE == MARIA9 )
	
	#if(PanelWidth<480)
	{BK2_6F, 0x83}, //fixed for picture cleaved to two pieces
	#else
	{BK2_6F, 0x81}, // 20051123.Eric.Lin: Using old SW reset, DE by pass
	#endif
	
	#else
	{BK2_6F, 0x81}, // 20051123.Eric.Lin: Using old SW reset, DE by pass
	#endif
	
	{BK2_72, 0x74}, // HV_SLC_CTRL
	// {BK2_73_INI_CTRL2,0xF0},
	
	{BK2_76_656_CTRL1, 0x00}, // For Mode1, enable 656 mode (20050722)
	{BK2_77, 0x00},


	// {BK2_7D_NOISE_MLINE, 0x01}, // NOISE_MLINE
	// {BK2_7E_656_CTRL2, 0x80}, // 20051128.Eric:656_CTRL2

	{BK2_8F_FSC_TABLE, 0x19},

	{BK2_94_SPL_SPD_CTRL1, 0x0C}, // 20051230.KC: Lock H sync speed when no signal

	{BK2_9D_DPL_NSPL_HIGH, _656_PLL_VALUE},
	{BK2_9E_DPL_NSPL_LOW, 0x20},

	{BK2_96_EDGES_NOISY_TH, 0x60}, // 20051202.Eric.Lin: For Noise Mag

	{BK2_A0_DPL_K1_FORCE, 0x1A}, // 20060424. Michael
	{BK2_A1_DPL_K2_FORCE, 0x35}, // 20060424. Michael

	{BK2_A2_DPL_K1_NOISY, 0x2B}, // 20060216: Daniel.Wu
	{BK2_A3_DPL_K2_NOISY, 0x40}, // 20060216: Daniel.Wu
	{BK2_AB, 0x02},

	{BK2_B2, 0x99}, // 20051207.KC: 0x19 -> 0x99 For line lock
	{BK2_B9, 0x3F}, // 20051202.Eric.Lin: For DSP_18
	{BK2_BA, 0x3F}, // 20051202.Eric.Lin: For DSP_18

	#if (!ENABLE_VD_DSP )
	
	#if( !ENABLE_SW_FIELD )
	{BK2_BB, 0x06}, // Using COMB' VSync,Filed
	#endif
	
	#endif

	{BK0_00_REGBK, REG_BANK_SCALER}, // select register bank scaler
	{_END_OF_TBL_, 0x00}
};

RegUnitType code tInitializeVCE[] =
{
	{BK0_00_REGBK, REG_BANK3_COMB}, // select register bank VCF
	
	// select demodulation mode 0 (11h[5] = 1b'0)

	{BK3_10_COMBCFGA, 0x02},
	{BK3_11_COMBCFGB, 0x20},
	
	{BK3_12, 0x00}, // Don't use comb snow
	
	// {BK3_13, INIT_MSVD_COMB_YGAIN},//0xA0}, // YGAIN
	// {BK3_14, INIT_MSVD_COMB_CbGAIN}, // CBGAIN
	// {BK3_15, INIT_MSVD_COMB_CrGAIN}, // CRGAIN

	{BK3_16, 0x66},
	{BK3_17, 0x66},

	{BK3_1C_CTRLSWCH, 0xB3},//0xF3},//0xB3}, 
	// bit7: H sync from AFEC
	// bit6: V sync from AFEC
	// bit5: Black level from AFEC
	// bit4: Demodulation degree from afec
	// bit[1:0] NTSC/PAL decision
	// 01: force NTSC
	// 10: force PAL
	// Other: auto detect

	{BK3_21_COMB2DCFGB, 0xEF}, //0xE7},
	{BK3_22_COMB2DCFGC, 0x83}, //0x8F},
	{BK3_23_COMB2DCFGD, 0x40}, //0x60},
	{BK3_24_TH2DHOR, 0x20}, //0x60},
	{BK3_25_TLRNLUMA, 0x18}, //0x30},
	{BK3_26_THCRMAERR, 0x10}, //0x30},
	{BK3_27_THHORCHKV, 0x00},//0x10}, // 20051115.Daniel.Shen
	{BK3_48_BSTLVL_TH, 0x00},

	{BK3_60_IMGCTRL, 0x55},

	{BK3_63_REG_CTST, INIT_MSVD_COMB_CONTRAST}, // VD Contrast
	{BK3_64_REG_BRHT, INIT_MSVD_COMB_BRIGHTNESS}, // VD Brightness
	{BK3_65_REG_SAT, INIT_MSVD_COMB_SATURATION}, // VD Saturation

	{BK3_66_SENSCTST, 0x80},

	{BK0_00_REGBK, REG_BANK_SCALER}, // select register bank scaler
	{_END_OF_TBL_, 0x00}
};

#if ( PANEL_DIGITAL_TCON || PANEL_ANALOG_TCON )	
RegUnitType code tInitializeTCON[] =
{
	{BK1_CD_GPO_OEV2_WIDTH, SET_OEV2_WIDTH},
	{BK1_CE_GPO_OEV3_WIDTH, SET_OEV3_WIDTH},
	{BK1_CF_GPO_OEV_DELTA, SET_OEV_DELTA},

	{BK1_D0_PTC_MODE1, ( SET_PTC_MODE1 & 0x7F ) },

	{BK1_D2_PTC_MODE3, SET_PTC_MODE3},

	{BK1_DC_GPO_FRP_TRAN, SET_FRP_TRAN},
	{BK1_DD_GPO_STH_STT, SET_STH_START},
	{BK1_DE_GPO_STH_WIDTH, SET_STH_WIDTH},
	{BK1_DF_GPO_OEH_STT, SET_OEH_START},
	{BK1_E0_GPO_OEH_WIDTH, SET_OEH_WIDTH},
	{BK1_E1_GPO_OEV_STT, SET_OEV_START},
	{BK1_E2_GPO_OEV_WIDTH, SET_OEV_WIDTH},
	{BK1_E3_GPO_CKV_STT, SET_CKV_START},
	{BK1_E4_GPO_CKV_STT2, SET_CKV_START2},
	{BK1_E5_GPO_CKV_WIDTH, SET_CKV_WIDTH},
	{BK1_E6_GPO_STV_LN_TH, SET_STV_LINE_TH},
	{BK1_E7_GPO_STV_STT, SET_STV_START},
	{BK1_E8_GPO_STV_WIDTH, SET_STV_WIDTH},
	{BK1_E9_GPO_OEV2_STT, SET_OEV2_START},
	{BK1_EA_GPO_OEV3_STT, SET_OEV3_START},
	{BK1_EB_HSTT_DLY_L, SET_H_ST_DLY_L},
	{BK1_EC_HSTT_DLY_H, SET_H_ST_DLY_H},
	{BK1_ED_CLK_DLY_SYNC_OUT, SET_CLK_DLY_SYNC_OUT},
	{BK1_EE_GPO_CKV_END2, SET_CKV_END2},
	{BK1_EF_Q1H_SETTING, SET_Q1H},

	#if (( PANEL_TYPE==PanelPVI10_AT) || ( PANEL_TYPE == PanelPVI08_AT )) // For PVI10" Panel
	
	{BK1_D3_LN_EXTR_CNT_LMT, 0x00},
	{BK1_D4_LN_EXTR_SET1_H, 0x00},
	{BK1_D5_LN_EXTR_SET1_L, 0x00},
	{BK1_D6_LN_EXTR_SET2_H, 0x00},
	{BK1_D7_LN_EXTR_SET2_L, 0x00},
	{BK1_D8_EXTR_STT_LN1, 0x00},
	{BK1_D9_EXTR_END_LN1, 0x00},
	{BK1_DA_EXTR_STT_LN2, 0x00},
	{BK1_DB_EXTR_END_LN2, 0x13},
	{BK1_CB_IPOL_SET1, 0x08},
	{BK1_EF_Q1H_SETTING, 0x00},
	
	#endif

	#if PANEL_ANALOG_TCON
	
	//VCOM SETTING
	#if (SCALER_TYPE == MARIA9) //Linix 20100929
	
	{BK0_00_REGBK, REG_BANK4_LVDS_CCFL},
	{BK4_27, 0x01}, //Power Down VCOM
	{BK4_28, SET_BVOM_OUT}, //Set VCOM value
	{BK0_00_REGBK, REG_BANK1_ADC_ACE_MCU},
	
	#else //End Linix 20100929
	// {BK1_43_BVOM_DC, SET_BVOM_DC},
	// {BK1_44_BVOM_OUT, SET_BVOM_OUT},
	#endif

	// Power setting
	{BK1_46, 0x00},
	{BK1_47, 0x00},
	{BK1_48, 0x00},
	{BK1_49, 0x0F},
	{BK1_4A, 0x00},
	{BK1_4B, 0x40},
	{BK1_4C, 0x30},
	{BK1_4D, 0x55},
	{BK1_4E, 0x58},
	{BK1_4F, 0x00},
	
	// DAC output setting
	{BK1_A9_PD_VDAC, 0x00},
	{BK1_AA_VDAC_ADJ1, SET_VDAC_ADJ1},
	{BK1_AB_VDAC_ADJ2, SET_VDAC_ADJ2},
	
	#else
	
	{BK1_45, 0x01},
	{BK1_4A, 0xF1},
	{BK1_4B, 0x5F},
	{BK1_4C, 0x51},
	
	#endif

	{_END_OF_TBL_, 0x00}
};
#endif

#if (PANEL_LVDS)
RegUnitType code tInitializeLVDS[] =
{
	{BK0_00_REGBK, REG_BANK4_LVDS_CCFL}, // select register bank VCF

	#if( PANEL_LVDS )
	{BK4_19, ( PANEL_LVDS_TI_MODE & _BIT0 ) | ( PANEL_SWAP_LVDS_POL & _BIT1 ) | ( PANEL_SWAP_LVDS_CH & _BIT2 ) },
	
	#if ( SCALER_TYPE == MARIA9 )
	{BK4_19, 0x02},
	{BK4_29, 0x01},
	{BK4_2A, 0x55},
	{BK4_2B, 0x55},
	{BK4_2C, 0x55},
	{BK4_2D, 0x02},
	{BK4_1E, 0x04},
	
	#else
	
	{BK4_1E, 0x02},
	#endif

	{BK4_20, 0x00}, //Revised for LVDS Panel Nicolee 20051027
	{BK4_21, 0x00},
	{BK4_22, 0x06},//0x00 2010/5/18 02:19pm,Hubert add for CPT 8.9"_LVDS_1024x600
	
	#else
	
	{BK4_22, 0xFF},
	
	#endif

	{BK0_00_REGBK, REG_BANK_SCALER}, // select register bank scaler
	{_END_OF_TBL_, 0x00}
};
#endif

#if (CCFL_FUNCTION)
RegUnitType code tInitializeCCFL[] =
{
	{BK0_00_REGBK, REG_BANK4_LVDS_CCFL}, // select register bank VCF

	{BK4_6B, 0xFF},
	{BK4_9A, 0xCF},

	#if CCFL_BURST_MODE
	{BK4_6E, 0x0D},
	#else
	{BK4_6E, 0x0C},
	#endif

	#if ( MST_CHIP == MST712CX ) //64pin must disable VIN monitor function
	{BK4_72, 0xFF},
	{BK4_72, 0xFF},
	{BK4_73, 0xFF},
	{BK4_74, 0x00},
	{BK4_75, 0x00},
	{BK0_00_REGBK, REG_BANK5_MGD}, //Change to Bank5 (Monica only)
	{BK5_65, 0xEA}, //Enable QOR register writing
	{BK5_66, 0x2E}, //Set DPWM output QOR and use Max driving, also disable strike1 divider low boundary.
	{BK0_00_REGBK, REG_BANK4_LVDS_CCFL},
	#else

	#if ( SCALER_TYPE == MARIA9 )
	{BK4_72, 0xFF},
	{BK4_73, 0xFF},
	{BK4_74, 0x00},
	{BK4_75, 0x00},
	#else
	{BK4_72, 0xF5},
	{BK4_73, 0xE9},
	{BK4_74, 0x32},
	{BK4_75, 0x22},
	#endif
	#endif

	{BK4_78, 0x12},
	{BK4_79, 0x00},
	{BK4_7A, 0xFF},

	#if ( SCALER_TYPE == MARIA9 )
	{BK4_7B, 0x00},
	#else
	{BK4_7B, 0x38},
	#endif

	{BK4_86, 0x03}, //0x01
	{BK4_85, 0xFF}, //0x3C

	#if ( MST_CHIP == MST712CX )
	{BK4_8A, 0x00},
	{BK4_89, 0x86},
	#else
	{BK4_8A, 0x01},
	{BK4_89, 0x16},
	#endif

	#if CCFL_BURST_MODE
	{BK4_8F, 0x00},
	{BK4_8E, 0xAE},
	#endif

	{BK4_91, 0x03},
	{BK4_90, 0xFF}, //0xAE},//

	#if PANEL_ANALOG_TCON
	{BK4_AB, 0x13},
	#else
	{BK4_AB, 0x93},
	#endif

	// {BK4_AC, 0x81},

	#if LED_BACKLIGHT //100K freq

	#if ( MST_CHIP == MST712CX )
	{BK4_86, 0x00},
	{BK4_85, 0x6C}, //500Khz Strike1 divider
	
	#elif ( SCALER_TYPE == MARIA9 )
	{BK4_83, 0x95},
	{BK4_86, 0x00},
	{BK4_85, 0x02}, //Strike frequency set to 300KHz
	{BK4_AF, 0x20},
	
	#else
	{BK4_86, 0x00},
	{BK4_85, 0xB4}, //100KHZ
	
	#endif

	#else

	{BK4_86, 0x01},
	{BK4_85, 0x9C},

	#endif

	{BK4_AB, 0x93},

	#if ENABLE_MCU_USE_INTERNAL_CLOCK

	#if ( MST_CHIP == MST712CX )
	{BK4_B0, 0x22}, //Limit max on duty in 70% for 500Khz
	{BK4_B1, 0x00},
	#else

	#if( SCALER_TYPE == MARIA9 )
	//DIGITAL PWM DUTY CYCLE / FOR LCD BRIGHTNESS
	//CSRF;
	{BK4_B0, 0xFF}, //for 27Mhz
	{BK4_B1, 0x00},
	
	#else
	{BK4_B0, 0x93}, //for 27Mhz
	{BK4_B1, 0x01},
	#endif

	#endif

	#else

	#if( SCALER_TYPE == MARIA9 )
	{BK4_B0, 0x1E}, //for 27Mhz
	{BK4_B1, 0x00},
	#else
	{BK4_B0, 0xB3},
	{BK4_B1, 0x00},
	#endif
	#endif

	{BK4_B2, 0x0A},
	{BK4_6B, 0x00},

	{BK0_00_REGBK, REG_BANK_SCALER}, // select register bank scaler
	{_END_OF_TBL_, 0x00}
};
#endif