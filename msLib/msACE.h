#ifndef _MSACE_H_
#define _MSACE_H_

#ifdef _MSACE_C_
	#define _MSACEDEC_
#else
	#define _MSACEDEC_ extern
#endif

// sRGB matrix for PC
// this variable must pointer to a array[3][3]
_MSACEDEC_ short xdata* tSrgbMatrix;

// Color correction matrix for Video
// this variable must pointer to a array[3][3]

//_MSACEDEC_ short code tVideoColorCorrectionMatrix[3][3];
_MSACEDEC_ short xdata tColorCorrectionMatrix[3][3];

// Basic color control function(Library)

// Initialize ACE varible
// Must call this function before call other ace function
_MSACEDEC_ void InitACEVar();

//------------------------------------------------------------------------
// Only for Video input, not support PC input
// Input:
// ucContrast: 0~FFh, (gain range x0 ~ x4, 80h is x1)
// Mstar use: 50h~A0h
//------------------------------------------------------------------------
_MSACEDEC_ void msAdjustVideoContrast ( BYTE ucContrast );
//------------------------------------------------------------------------
// Only for Video input, not support PC input
// Input:
// ucSaturation: 0~FFh, (gain range x0 ~ x4, 80h is x1)
// Mstar use: 50h~A0h
//------------------------------------------------------------------------
_MSACEDEC_ void msAdjustVideoSaturation ( BYTE ucSaturation );
//------------------------------------------------------------------------
// Only for Video input, not support PC input
// Input:
// ucHue: 0~100, (angel -50 degree ~ angel 50 degree, 50 is 0 degree)
// Mstar use: 0~100
//------------------------------------------------------------------------
_MSACEDEC_ void msAdjustVideoHue ( BYTE ucHue );
//------------------------------------------------------------------------
// Only for Video input, not support PC input
// Adjust video R,G,B gain
// Input:
// ucContrast: 0~FFh, (gain range x0 ~ x4, 80h is x1)
// Mstar use: 80h
//------------------------------------------------------------------------
_MSACEDEC_ void msAdjustVideoRGB ( BYTE ucRCon, BYTE ucGCon, BYTE ucBCon );

//------------------------------------------------------------------------
// Only for PC input, not support Video input
// Input:
// ucContrast: 0~FFh, (gain range x0 ~ x4, 80h is x1)
// Mstar use: 50h~A0h
//------------------------------------------------------------------------
_MSACEDEC_ void msAdjustPCContrast ( BYTE ucContrast );
//------------------------------------------------------------------------
// Only for PC input, not support Video input
// Adjust vide R,G,B gain
// Input:
// ucContrast: 0~FFh, (gain range x0 ~ x4, 80h is x1)
// Mstar use: 80h
//------------------------------------------------------------------------
_MSACEDEC_ void msAdjustPCRGB ( BYTE ucRed, BYTE ucGreen, BYTE ucBlue );

// Special color control function
//------------------------------------------------------------------------
// Only for Video input, not support PC input
// Adjust vide contrast, hue, saturation together
// Input:
// ucContrast: 0~FFh, (gain range x0 ~ x4, 80h is x1)
// ucHue: 0~100, (angel -50 degree ~ angel 50 degree, 50 is 0 degree)
// ucSaturation: 0~FFh, (gain range x0 ~ x4, 80h is x1)
//------------------------------------------------------------------------
_MSACEDEC_ void msAdjustHSC ( BYTE ucHue, BYTE ucSaturation, BYTE ucContrast );

_MSACEDEC_ void msAdjustPCContrastRGB ( BYTE ucContrast, BYTE ucRed, BYTE ucGreen, BYTE ucBlue );

_MSACEDEC_ void msAdjustVideoCbCr ( BYTE ucCb, BYTE ucCr );

_MSACEDEC_ void msAdjustBrightness ( BYTE brightness );

// Turn On/Off sRGB, PC use only
//void msACEPCsRGBCtl( BOOL bEnable );

//------------------------------------------------------------------------
void msACEPCYUV2RGBCtl ( BOOL bEnable );


//------------------------------------------------------------------------
// Input:
// bCtrl:
// 0 Enable for RGB
// 1 Disable for YUV
//------------------------------------------------------------------------
//void msACEColorCtrl( BOOL bCtrl );
#endif
