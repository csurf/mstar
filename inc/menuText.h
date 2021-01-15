#ifndef _MENUTEXT_H_
#define _MENUTEXT_H_

BYTE code strHandIcon[3] = { 0x7E, 0x7F, '\0' };

BYTE code strBrightness[11]    = {"BRIGHTNESS"};
BYTE code strSaturation[6]     = {"COLOR"};
BYTE code strContrast[9]       = {"CONTRAST"};
BYTE code strBacklight[10]     = {"BACKLIGHT"};
BYTE code strVideoHue[4]       = {"HUE"};

BYTE code strScalingText[5]    = {"ZOOM"};
BYTE code strSourceInput[6]    = {"INPUT"};
BYTE code strReset[6]          = {"RESET"};
BYTE code strVideoStandard[7]  = {"FORMAT"};

BYTE code strScaling_ModeText[Scaling_NUMS][5] =
{
	{"16:9"},
	{" 4:3"},
};

BYTE code strCurrentChromaMode[CHROMA_NUMS][6] =
{
	//123456789012345678901234567890
	{" NTSC"},
	{" PAL "},
};

BYTE code strSourceText_AV[2][4] =
{
	{"AV1"},
	{"AV2"},
};

#endif
