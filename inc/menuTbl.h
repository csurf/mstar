#include "menuTblDef.h"

#ifndef _MENUTBL_H_
#define _MENUTBL_H_

/*************************************************************************************************************************/

RadioTextType code ShowSourceText[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, XPos, YPos, DisplayText
	{dwiEnd, CP_GrayColor, CP_GrayColor, CP_GreenColor, CP_GrayColor, 0, 0, SourceText},
};

DrawRadioGroupType code DrawDisplayShowSourceRatioGroup[] =
{
	//Flags,GetValue RadioText DrawTVVideoSoundMode,
	{0, NULL, ShowSourceText},
};

DrawValueType code DisplayShowSource[] =
{
	{
		dwiEnd,
		NULL, // DrawNumberType
		NULL, // DrawGaugeType
		DrawDisplayShowSourceRatioGroup // DrawRadioGroupType
	}
};

MenuItemType code ShowSourceMenuItems[] =
{
	{
		0, 0, // XPos, YPos;
		CP_GreenColor1, CP_WhiteColor, // ForeColor, BackColor;
		CP_GreenColor1, CP_WhiteColor, // SelForeColor, SelBackColor;
		PictureMenu, //NextMenuPage;
		DWI_CenterText,// DrawMenuItemType;
		NULL, // DisplayText;
		RootKeyEvent, //KeyEvent
		{
			NULL, // AdjustFunction
			NULL // ExecFunction
		},// DisplayValue;
		DisplayShowSource,
		mibSelectable // Flags
	}
};

//==============================================================================

RadioTextType code DisplayBacklightIconRadioText[] =
{
	{
		dwiEnd, //Flags
		CP_WhiteColor, //ForeColor
		CP_GrayColor, //BackColor
		CP_GreenColor1, //SelForeColor
		CP_GrayColor, //SelBackColor
		2, 1, //XPos, YPos
		BacklightText //DisplayText
	},
};

DrawRadioGroupType code DisplayBacklightIconRadioGroup[] =
{
	{
		0, //Flags
		NULL, //GetValue
		DisplayBacklightIconRadioText //RadioText
	}
};

DrawNumberType code DrawBacklightIconNumber[] =
{
	{
		dwiEnd, //Flags
		CP_WhiteColor, //ForeColor
		CP_GrayColor, //BackColor
		CP_GreenColor1, //SelForeColor
		CP_GrayColor, //SelBackColor
		13, 1, //XPos,YPos
		#if LED_BACKLIGHT || BACKLIGHT_PWM
		GetBacklightValue //GetValue
		#else
		GetVideoVCOMDCValue
		#endif
	}
};

DrawGaugeType code DrawBacklightIconGauge[] =
{
	{
		dwiEnd, // Flags,
		CP_GrayColor, //ForeColor
		CP_GrayColor, //BackColor
		CP_SeaBlueColor, //SelBackColor
		CP_GrayColor, //SelBackColor
		15, 0, 11, //Length, XPos, YPos,
		
		#if LED_BACKLIGHT || BACKLIGHT_PWM
		GetBacklightValue //GetValue
		#else
		GetVideoVCOMDCValue
		#endif
	}
};

DrawValueType code DisplayBacklightIconGroup[] =
{
	{
		dwiEnd, //Flags
		DrawBacklightIconNumber,// DrawNumberType
		DrawBacklightIconGauge,// DrawGaugeType
		DisplayBacklightIconRadioGroup// DrawRadioGroupType
	}
};


RadioTextType code DisplayBrightnessIconRadioText[] =
{
	{
		dwiEnd, //Flags
		CP_WhiteColor, //ForeColor
		CP_GrayColor, //BackColor
		CP_GreenColor1, //SelForeColor
		CP_GrayColor, //SelBackColor
		2, 2, //XPos, YPos
		BrightnessText //DisplayText
	},
};

DrawRadioGroupType code DisplayBrightnessIconRadioGroup[] =
{
	{
		0, //Flags
		NULL, //GetValue
		DisplayBrightnessIconRadioText //RadioText
	}
};

DrawNumberType code DrawBrightnessIconNumber[] =
{
	{
		dwiEnd, //Flags
		CP_WhiteColor, //ForeColor
		CP_GrayColor, //BackColor
		CP_GreenColor1, //SelForeColor
		CP_GrayColor, //SelBackColor
		13, 2, //XPos,YPos
		GetBrightnessValue //GetValue
	}
};

DrawGaugeType code DrawBrightnessIconGauge[] =
{
	{
		dwiEnd, // Flags,
		CP_GrayColor, //ForeColor
		CP_GrayColor, //BackColor
		CP_SeaBlueColor, //SelBackColor
		CP_GrayColor, //SelBackColor
		15, 0, 11, //Length, XPos, YPos,
		GetBrightnessValue //GetValue
	}
};

DrawValueType code DisplayBrightnessIconGroup[] =
{
	{
		dwiEnd, //Flags
		DrawBrightnessIconNumber,// DrawNumberType
		DrawBrightnessIconGauge,// DrawGaugeType
		DisplayBrightnessIconRadioGroup// DrawRadioGroupType
	}
};


/*************************************************************************************************************************/

RadioTextType code DisplayContrastIconRadioText[] =
{
	{
		dwiEnd, //Flags
		CP_WhiteColor, //ForeColor
		CP_GrayColor, //BackColor
		CP_GreenColor1, //SelForeColor
		CP_GrayColor, //SelBackColor
		2, 3, //XPos, YPos,
		ContrastText //DisplayText
	},
};

DrawRadioGroupType code DisplayContrastIconRadioGroup[] =
{
	// Flags, GetValue RadioText
	{ 0, NULL, DisplayContrastIconRadioText}
};

DrawNumberType code DrawContrastIconNumber[] =
{
	// Flags, ForeColor, BackColor, XPos, YPos, GetValue
	{dwiEnd, CP_WhiteColor, CP_GrayColor, CP_GreenColor1, CP_GrayColor, 13, 3, GetContrastValue}
};

DrawGaugeType code DrawContrastIconGauge[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, Length, XPos, YPos, GetValue
	{dwiEnd, CP_GrayColor, CP_GrayColor, CP_SeaBlueColor, CP_GrayColor, 15, 0, 11, GetContrastValue}
};

DrawValueType code DisplayContrastIconGroup[] =
{
	{
		dwiEnd,
		DrawContrastIconNumber,// DrawNumberType
		DrawContrastIconGauge,// DrawGaugeType
		DisplayContrastIconRadioGroup// DrawRadioGroupType
	}
};

/*************************************************************************************************************************/
/*
RadioTextType code DisplaySharpnessIconRadioText[] =
{
 {
 dwiEnd, //Flags
 CP_WhiteColor, //ForeColor
 CP_GrayColor, //BackColor
 CP_GreenColor1, //SelForeColor
 CP_GrayColor, //SelBackColor
 2, 3, //XPos, YPos
 SharpnessText //DisplayText
 },
};

DrawRadioGroupType code DisplaySharpnessIconRadioGroup[] =
{
 {
 0, //Flags
 NULL, //GetValue
 DisplaySharpnessIconRadioText //RadioText
 }
};

DrawNumberType code DrawSharpnessIconNumber[] =
{
 {
 dwiEnd, //Flags
 CP_WhiteColor, //ForeColor
 CP_GrayColor, //BackColor
 CP_GreenColor1, //SelForeColor
 CP_GrayColor, //SelBackColor
 13, 3, //XPos,YPos
 GetSharpnessValue //GetValue
 }
};

DrawGaugeType code DrawSharpnessIconGauge[] =
{
 {
 dwiEnd, // Flags,
 CP_GrayColor, //ForeColor
 CP_GrayColor, //BackColor
 CP_SeaBlueColor, //SelBackColor
 CP_GrayColor, //SelBackColor
 15, 0, 11, //Length, XPos, YPos,
 GetSharpnessValue //GetValue
 }
};

DrawValueType code DisplaySharpnessIconGroup[] =
{
 {
 dwiEnd, //Flags
 DrawSharpnessIconNumber,// DrawNumberType
 DrawSharpnessIconGauge,// DrawGaugeType
 DisplaySharpnessIconRadioGroup// DrawRadioGroupType
 }
};
*/

RadioTextType code DisplaySaturationIconRadioText[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, XPos, YPos, DisplayText
	{dwiEnd, CP_WhiteColor, CP_GrayColor, CP_GreenColor1, CP_GrayColor, 2, 4, SaturationText},
};

DrawRadioGroupType code DisplaySaturationIconRadioGroup[] =
{
	// Flags, GetValue RadioText
	{ 0, NULL, DisplaySaturationIconRadioText}
};

DrawNumberType code DrawSaturationIconNumber[] =
{
	// Flags, ForeColor, BackColor, XPos, YPos, GetValue
	{dwiEnd, CP_WhiteColor, CP_GrayColor, CP_GreenColor1, CP_GrayColor, 13, 4, GetSaturationValue}
};

DrawGaugeType code DrawSaturationIconGauge[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, Length, XPos, YPos, GetValue
	{dwiEnd, CP_GrayColor, CP_GrayColor, CP_SeaBlueColor, CP_GrayColor, 15, 0, 11, GetSaturationValue}
};

DrawValueType code DisplaySaturationIconGroup[] =
{
	{
		dwiEnd,
		DrawSaturationIconNumber,// DrawNumberType
		DrawSaturationIconGauge,// DrawGaugeType
		DisplaySaturationIconRadioGroup// DrawRadioGroupType
	}
};

/*************************************************************************************************************************/

RadioTextType code DisplayVideoHueIconRadioText[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, XPos, YPos, DisplayText
	{dwiEnd, CP_WhiteColor, CP_GrayColor, CP_GreenColor1, CP_GrayColor, 2, 5, VideoHueText},
};

DrawRadioGroupType code DisplayVideoHueIconRadioGroup[] =
{
	// Flags, GetValue RadioText
	{ 0, NULL, DisplayVideoHueIconRadioText}
};

DrawNumberType code DrawVideoHueIconNumber[] =
{
	// Flags, ForeColor, BackColor, XPos, YPos, GetValue
	{dwiEnd, CP_WhiteColor, CP_GrayColor, CP_GreenColor1, CP_GrayColor, 13, 5, GetVideoHueValue}
};

DrawGaugeType code DrawVideoHueIconGauge[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, Length, XPos, YPos, GetValue
	{dwiEnd, CP_GrayColor, CP_GrayColor, CP_SeaBlueColor, CP_GrayColor, 15, 0, 11, GetVideoHueValue}
};

DrawValueType code DisplayVideoHueIconGroup[] =
{
	{
		dwiEnd,
		DrawVideoHueIconNumber,// DrawNumberType
		DrawVideoHueIconGauge,// DrawGaugeType
		DisplayVideoHueIconRadioGroup// DrawRadioGroupType
	}
};

/*************************************************************************************************************************/

RadioTextType code DisplayScalingModeIconRadioText[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, XPos, YPos, DisplayText
	{dwiEnd, CP_WhiteColor, CP_GrayColor, CP_GreenColor1, CP_GrayColor, 13, 6, Scaling_ModeText},
};

DrawRadioGroupType code DisplayScalingIconRadioGroup[] =
{
	// Flags, GetValue RadioText
	{0, NULL, DisplayScalingModeIconRadioText}
};

RadioTextType code DisplayScalingFontIconRadioText[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, XPos, YPos, DisplayText
	{dwiEnd, CP_WhiteColor, CP_GrayColor, CP_GreenColor1, CP_GrayColor, 2, 6, ScalingText},
};

DrawRadioGroupType code DisplayScalingFontIconRadioGroup[] =
{
	// Flags, GetValue RadioText
	{ 0, NULL, DisplayScalingFontIconRadioText}
};

DrawValueType code DisplayScalingIconGroup[] =
{
	{
		0,
		NULL,// DrawNumberType
		NULL,// DrawGaugeType
		DisplayScalingIconRadioGroup// DrawRadioGroupType
	},
	{
		dwiEnd,
		NULL,// DrawNumberType
		NULL,// DrawGaugeType
		DisplayScalingFontIconRadioGroup// DrawRadioGroupType
	}
};


//==============================================================================================

//==============================================================================================


RadioTextType code DisplayC_SYSIconRadioText[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, XPos, YPos, DisplayText
	{dwiEnd, CP_WhiteColor, CP_GrayColor, CP_GreenColor1, CP_GrayColor, 2, 7, VideoStdText},
};

DrawRadioGroupType code DisplayC_SYSIconRadioGroup[] =
{
	// Flags, GetValue RadioText
	{0, NULL, DisplayC_SYSIconRadioText}
};

RadioTextType code DisplayChromaModeIconRadioText[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, XPos, YPos, DisplayText
	{
		dwiEnd,
		CP_WhiteColor,
		CP_GrayColor,
		CP_GreenColor1,
		CP_GrayColor,
		12, 7,
		CurrentChromaModeText
	},
};

DrawRadioGroupType code DisplayChromaModeIconRadioGroup[] =
{
	// Flags, GetValue RadioText
	{
		0,
		NULL,
		DisplayChromaModeIconRadioText
	}
};

DrawValueType code DisplayC_SYSIconGroup[] =
{
	{
		0,
		NULL,// DrawNumberType
		NULL,// DrawGaugeType
		DisplayC_SYSIconRadioGroup// DrawRadioGroupType
	},
	{
		dwiEnd,
		NULL,// DrawNumberType
		NULL,// DrawGaugeType
		DisplayChromaModeIconRadioGroup// DrawRadioGroupType
	}
};


//==============================================================================================

RadioTextType code DisplayResetIconRadioText[] =
{
	// Flags, ForeColor, BackColor,SelForeColor, SelBackColor, XPos, YPos, DisplayText
	{dwiEnd, CP_WhiteColor, CP_GrayColor, CP_GreenColor1, CP_GrayColor, 5, 9, ResetText},
};

DrawRadioGroupType code DisplayResetIconRadioGroup[] =
{
	// Flags, GetValue RadioText
	{
		0,
		NULL,
		DisplayResetIconRadioText
	}
};

DrawValueType code DisplayResetIconGroup[] =
{
	{
		dwiEnd,
		NULL,// DrawNumberType
		NULL,// DrawGaugeType
		DisplayResetIconRadioGroup// DrawRadioGroupType
	}
};

//==============================================================================================

MenuItemType code PictureMenuItems[] =
{
	// BACKLIGHT
	{
		0, 1, // XPos, YPos;
		CP_GrayColor, CP_GrayColor, // ForeColor, BackColor;
		CP_GreenColor1, CP_GrayColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		HandIcon, // DisplayText;
		NaviKeyEvent, //KeyEvent;
		{
#if LED_BACKLIGHT || BACKLIGHT_PWM
			AdjustBacklight,// AdjustFunction
#else
			AdjustVideoVCOMDC,
#endif			
			NULL // ExecFunction
		},// *DisplayValue;
		DisplayBacklightIconGroup,
		mibSelectable | mibDrawValue // Flags
	},

	//BRIGHTNESS
	{
		0, 2, // XPos, YPos;
		CP_GrayColor, CP_GrayColor, // ForeColor, BackColor;
		CP_GreenColor1, CP_GrayColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		HandIcon, // DisplayText;
		NaviKeyEvent, //KeyEvent;
		{
			AdjustBrightness,// AdjustFunction
			NULL // ExecFunction
		},// *DisplayValue;
		DisplayBrightnessIconGroup,
		mibSelectable | mibDrawValue // Flags
	},

	//CONTRAST
	{
		0, 3, // XPos, YPos;
		CP_GrayColor, CP_GrayColor, // ForeColor, BackColor;
		CP_GreenColor1, CP_GrayColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		HandIcon, // DisplayText;
		NaviKeyEvent, //KeyEvent;
		{
			AdjustContrast, // AdjustFunction
			NULL // ExecFunction
		},// *DisplayValue;
		DisplayContrastIconGroup,
		mibSelectable | mibDrawValue // Flags
	},

	/*
	//SHARPNESS
	{
	0, 3, // XPos, YPos;
	CP_GrayColor, CP_GrayColor, // ForeColor, BackColor;
	CP_GreenColor1, CP_GrayColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_Icon,// DrawMenuItemType;
	HandIcon, // DisplayText;
	NaviKeyEvent, //KeyEvent;
	{
	AdjustSharpness, // AdjustFunction
	NULL // ExecFunction
	},// *DisplayValue;
	DisplaySharpnessIconGroup,
	mibSelectable | mibDrawValue // Flags
	},
	*/

	// Saturation
	{
		0, 4, // XPos, YPos;
		CP_GrayColor, CP_GrayColor, // ForeColor, BackColor;
		CP_GreenColor1, CP_GrayColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		HandIcon, // DisplayText;
		NaviKeyEvent, //KeyEvent;
		{
			AdjustSaturation, // AdjustFunction
			NULL // ExecFunction
		},// *DisplayValue;
		DisplaySaturationIconGroup,
		mibSelectable | mibDrawValue // Flags
	},

	// Video Hue
	{
		0, 5, // XPos, YPos;
		CP_GrayColor, CP_GrayColor, // ForeColor, BackColor;
		CP_GreenColor1, CP_GrayColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		HandIcon, // DisplayText;
		NaviKeyEvent, //KeyEvent;
		{
			AdjustVideoHue, // AdjustFunction
			NULL // ExecFunction
		},// *DisplayValue;
		DisplayVideoHueIconGroup,
		mibSelectable | mibDrawValue // Flags
	},

	// ASPECT RATIO
	{
		0, 6, // XPos, YPos;
		CP_GrayColor, CP_GrayColor, // ForeColor, BackColor;
		CP_GreenColor1, CP_GrayColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		HandIcon, // DisplayText;
		NaviKeyEvent, //KeyEvent;
		{
			AdjustScaling, // AdjustFunction
			NULL // ExecFunction
		},// *DisplayValue;
		DisplayScalingIconGroup,
		mibSelectable | mibDrawValue// Flags
	},


	// VIDEO STANDARD
	{
		0, 7, // XPos, YPos;
		CP_GrayColor, CP_GrayColor, // ForeColor, BackColor;
		CP_GreenColor1, CP_GrayColor, // SelForeColor, SelBackColor;
		RootMenu, //NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		HandIcon, // DisplayText;
		NaviKeyEvent, //KeyEvent;
		{
			AdjustChromaMode,// AdjustFunction
			NULL // ExecFunction
		},// *DisplayValue;
		DisplayC_SYSIconGroup,
		mibSelectable | mibDrawValue// Flags
	},

	// CHANGE SOURCE INPUT
	/*
	{
	0, 5, // XPos, YPos;
	CP_GreenColor1, CP_WhiteColor, // ForeColor, BackColor;
	CP_GreenColor1, CP_WhiteColor, // SelForeColor, SelBackColor;
	RootMenu, //NextMenuPage;
	DWI_CenterText,// DrawMenuItemType;
	HandIcon, // DisplayText;
	NaviKeyEvent, //KeyEvent
	{
	AdjustSource, // AdjustFunction
	NULL // ExecFunction
	},// DisplayValue;
	SelectSourceIconGroup,
	mibSelectable // Flags
	},
	*/

	// RESET SETTINGS
	{
		0, 9, // XPos, YPos;
		CP_GrayColor, CP_GrayColor, // ForeColor, BackColor;
		CP_GreenColor1, CP_GrayColor, // SelForeColor, SelBackColor;
		NULL, //NextMenuPage;
		DWI_Icon,// DrawMenuItemType;
		NULL, // DisplayText;
		ExecKeyEvent, //KeyEvent;
		{
			NULL,// AdjustFunction
			ResetAllSettings // ExecFunction
		},// *DisplayValue;
		DisplayResetIconGroup,
		mibSelectable | mibDrawValue// Flags
	}
};

//==============================================================================================
MenuPageType code tblMenus[] =
{
	// 6 RootMenu
	{
		16, 3, // XSize, YSize;
		RootMenu,// PrevMenuPage;
		RootMenuItems, // MenuItems;
		sizeof ( RootMenuItems ) / sizeof ( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		mtbIndividualTimeOut | 0,//TimeOut//0 means disable time out
		mpbInvisible | mpbStay // Flags;
	},
	// 10 ShowSourceMenu
	{
		5, 1, // XSize, YSize;
		RootMenu,// PrevMenuPage;
		ShowSourceMenuItems, // MenuItems;
		sizeof ( ShowSourceMenuItems ) / sizeof ( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL,//TimeOut//NUll means using osd time out
		mpbStay | mpbSetItemTop // Flags;
	},
	//13 PictureMenu
	{
		18, 13, // XSize, YSize;
		RootMenu,// PrevMenuPage;
		PictureMenuItems, // MenuItems;
		sizeof ( PictureMenuItems ) / sizeof ( MenuItemType ), // MenuItemCount;
		NULL, // ExecFunction;
		NULL, //TimeOut, NULL means using osd time out
		mpbStay | mpbSizeofItem // Flags;
	},
};
#endif
