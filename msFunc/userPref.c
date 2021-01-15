#define _USERPREF_C_

#include <MATH.H>
#include "types.h"
#include "board.h"
#include "global.h"
#include "nvram.h"
#include "debug.h"
#include "menuDef.h"
#include "menuFunc.h"
#include "panel.h"
#include "mstar.h"
#include "msACE.h"
#include "adjust.h"
#include "userPref.h"
#include "ms_rwreg.h"

#define HFreq_Tol 16 // 1.6 KHz
#define VFreq_Tol 8 // 0.8 Hz

BYTE usrCalCheckSum ( BYTE* pBuf, BYTE ucBufLen )
{
	BYTE CheckSum;
	CheckSum = 0;

	do
	{
		CheckSum += pBuf[ucBufLen - 1];
		ucBufLen--;
	}
	while ( ucBufLen );

	return CheckSum;
}

void InitVideoSetting ( void )
{
	putstr ( "\r\nInit Video Setting!" );
	g_VideoSetting.ucVersion = VideoVersion;

	g_VideoSetting.OsdHStart = 50;
	g_VideoSetting.OsdVStart = 50;
	g_VideoSetting.InputType = Input_CVBS1;

	g_VideoSetting.MonitorFlag = bPowerOnBit;

	g_VideoSetting.VideoBrightness = DefVideoBrightness;
	g_VideoSetting.VideoContrast = DefVideoContrast;
	g_VideoSetting.VideoSaturation = DefVideoSaturation;
	g_VideoSetting.VideoHue = DefVideoHue;
	
	g_VideoSetting.Backlight = DefBacklight;

	g_VideoSetting.Scaling = Scaling_4_3;

	g_VideoSetting.OsdTime = 1;
	g_VideoSetting.VideoColorSys = CHROMA_NTSC;
	g_VideoSetting.videoAGC = 8;

	g_VideoSetting.VcomDC = SET_BVOM_DC;
}

void SaveVideoSetting ( void )
{
	//putstr("\r\nSave Video Setting!");
	g_VideoSetting.Checksum = usrCalCheckSum ( ( BYTE* ) & g_VideoSetting, ( VideoSettingSize - CheckSumSize ) );
	NVRam_WriteTbl ( VideoSettingAddr, ( BYTE* ) & g_VideoSetting, VideoSettingSize );
}

void msChipVersionRead ( void )
{
	BYTE ucBank;
	BYTE ucChip_D_Version = 0;
	ucBank = msReadByte ( BK0_00_REGBK );
	msWriteByte ( BK0_00_REGBK, REG_BANK_SCALER );
	ucChip_D_Version = msReadByte ( BK0_F1_CHIP_VERSION );

	switch ( ucChip_D_Version )
	{
	case 5:
		VD_Type = MARIA2_F;
		break;

	case 4:
		VD_Type = MARIA2_E;
		break;

	case 3:
		VD_Type = MARIA2_D;
		break;

	case 6:
		VD_Type = MARIA2_G;
		break;

	default:
		VD_Type = MARIA2_G;
		break;
	}

	msWriteByte ( BK0_00_REGBK, ucBank );
}

#if RM_EEPROM_TYPE < RM_TYPE_SST512

void LoadVideoSetting ( void )
{
	BYTE ucCheckSum;

	//putstr("\r\nLoad Video Setting!");
	NVRam_ReadTbl ( VideoSettingAddr, ( BYTE* ) &g_VideoSetting, VideoSettingSize );
	ucCheckSum = usrCalCheckSum ( ( BYTE* ) &g_VideoSetting, VideoSettingSize - CheckSumSize );

	if ( g_VideoSetting.Checksum != ucCheckSum )
	{
		InitVideoSetting();
		SaveVideoSetting();
	}
}

BOOL CheckBoard ( void )
{
	BYTE i = 5, j = 5, temp;
	BOOL VideoSumOk, BoardSumOK;

	while ( i-- )
	{
		NVRam_ReadByte ( nvrVideoAddr ( ucVersion ), & ( g_VideoSetting.ucVersion ) );

		if ( g_VideoSetting.ucVersion == VideoVersion )
		{
			VideoSumOk = TRUE;
			break;
		}

		else
		{
			VideoSumOk = FALSE;
		}
	}

	while ( j-- )
	{
		NVRam_ReadByte ( BoardChkSumAddr, &temp );

		if ( temp == BoardVersion )
		{
			BoardSumOK = TRUE;
			break;
		}

		else
		{
			BoardSumOK = FALSE;
		}
	}

	// printf ( "\r\nBoardVer<%x>", temp );

	if ( BoardSumOK && VideoSumOk )
	{
		return TRUE;
	}

	else
	{
		return FALSE;
	}
}


void ReadSetting ( void )
{
	BOOL tempValue;
	tempValue = CheckBoard();

	if ( tempValue )
	{
		putstr ( "\r\nLoad !" );

		LoadVideoSetting();
	}

	else
	{
		putstr ( "\r\nUpdate!" );
		InitVideoSetting();
		SaveVideoSetting();
		NVRam_WriteByte ( BoardChkSumAddr, BoardVersion );
	}

}

#else

#define CS_ERR _BIT0
#define VER_ERR _BIT1

BYTE CheckFlashDataBlockError ( BOOL Block )
{
	BYTE ErrorType;
	BYTE i;
	BYTE ucCheckSum;

	for ( i = 0; i < 5; i++ )
	{
		ErrorType = 0;

		if ( !Block )
		{
			mstLoadDisplayData ( SFD_ADDRESS );
		}

		else
		{
			mstLoadDisplayData ( SFD_ADDRESS + 0x1000 );
		}

		ucCheckSum = usrCalCheckSum ( ( BYTE* ) & g_VideoSetting, VideoSettingSize - CheckSumSize );

		if ( g_VideoSetting.Checksum != ucCheckSum )
		{
			ErrorType |= CS_ERR;
		}

		if ( g_VideoSetting.ucVersion != VideoVersion )
		{
			ErrorType |= VER_ERR;
		}

		if ( !ErrorType )
		{
			break;
		}
	}

	return ErrorType;
}


void ReadSetting ( void )
{
	BYTE Block0Err;
	BYTE Block1Err;

	if ( g_bFlashReadOK )
	{
		return;
	}

	Block0Err = CheckFlashDataBlockError ( 0 );
	Block1Err = CheckFlashDataBlockError ( 1 );

	if ( Block0Err && !Block1Err ) //Block0 error, Block1 OK, restore Block1 to Block0
	{
		putstr ( "Block0 Err!\r\n" );
		SaveVideoSetting();
	}

	else if ( !Block0Err && Block1Err )
	{
		putstr ( "Block1 Err!\r\n" );
		CheckFlashDataBlockError ( 0 );
		SaveVideoSetting();
	}

	else if ( Block0Err && Block1Err )
	{
		putstr ( "Update!\r\n" );
		InitVideoSetting();
		SaveVideoSetting();
	}

	else
	{
		putstr ( "Load OK!\r\n" );
	}

	g_bFlashReadOK = 1;
}

#endif

//*******************************************************************
// Function Name: msSetUserPref
//
// Decscription: Restore user setting from NVRAM
//
// callee: msWriteByte() in ms_rwreg.c
//
// caller: msSetupMode() in mStar.c
//*******************************************************************
void msSetUserPref ( void )
{
	BYTE tempSat, tempCon, tempBri;

	msAdjustVideoRGB ( RedGain, GreenGain, BlueGain );
	msAdjustVideoCbCr ( CbGain, CrGain );

	tempSat = usrNonLinearCalculate ( g_NLCSaturation, g_VideoSetting.VideoSaturation );
	tempCon = usrNonLinearCalculate ( g_NLCContrast, g_VideoSetting.VideoContrast );

	msAdjustHSC ( g_VideoSetting.VideoHue, tempSat, tempCon );

	msAdjustVideoHue ( g_VideoSetting.VideoHue );

	tempBri = usrNonLinearCalculate ( g_NLCBrightness, g_VideoSetting.VideoBrightness );
	msAdjustBrightness ( tempBri );
	
	#if LED_BACKLIGHT || BACKLIGHT_PWM
	msSetBacklight ( g_VideoSetting.Backlight );
	#endif
}
