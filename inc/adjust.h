#ifndef _ADJUST_H_
#define _ADJUST_H_

#ifdef _ADJUST_C_
	#define _ADJUSTDEC_
#else
	#define _ADJUSTDEC_ extern
#endif

#if(VGA_ENABLE||YPBPR_ENABLE)
	_ADJUSTDEC_ void msAdjustHPosition ( WORD position );
	_ADJUSTDEC_ void msAdjustVPosition ( WORD position );
	_ADJUSTDEC_ void msAdjustPhase ( BYTE phase );
	_ADJUSTDEC_ void msSetAdcOffset ( BYTE ucColor, BYTE ucValue );
	#if (SCALER_TYPE==MARIA9)
		_ADJUSTDEC_ void msAdjustAdcGain ( WORD ucRedValue, WORD ucGreenValue, WORD ucBlueValue );
	#else
		_ADJUSTDEC_ void msAdjustAdcGain ( BYTE ucRedValue, BYTE ucGreenValue, BYTE ucBlueValue );
		_ADJUSTDEC_ void msAdjustAdcOffset ( BYTE ucRedValue, BYTE ucGreenValue, BYTE ucBlueValue );
	#endif
	_ADJUSTDEC_ void msAdjustAdcClock ( WORD wValue );
	#if (SCALER_TYPE==MARIA9)
		_ADJUSTDEC_ void msAdjustAdcPhase ( WORD wValue );
		_ADJUSTDEC_ void msADC_SOG_FilterBW ( BYTE ucPixClk );
		_ADJUSTDEC_ void msADC_PLL ( BYTE ucPixClk );
		_ADJUSTDEC_ void msADC_inputLPF ( BYTE ucPixClk );
		_ADJUSTDEC_ void msADC_iclamp_clpdur ( BYTE ucPixClk );
		_ADJUSTDEC_ void msADC_iclamp_clpdly ( BYTE ucPixClk );
		_ADJUSTDEC_ void msADC_iclamp_clk_rate ( BYTE ucPixClk );
		_ADJUSTDEC_ void msADC_HSYNC_Polarity ( BIT bPolarity );
		_ADJUSTDEC_ void msADCSelfMismatchCal_RGB_YCbCr ( void );
		_ADJUSTDEC_ void msADCGainOffsetMismatchCal_RGB_YCbCr ( void );
	#else
		_ADJUSTDEC_ void msAdjustAdcPhase ( BYTE ucValue );
	#endif
#endif
//_ADJUSTDEC_ void msAdjustBackgroundColor(BYTE pattern);
#if (SCALER_TYPE==MARIA9)
	_ADJUSTDEC_ void msADCWaitStatusReady ( BYTE ucRegIndex, BYTE ucRegMask );
	_ADJUSTDEC_ void msADCSelfMismatchCal_CVBS_SVIDEO_Y ( void );
	_ADJUSTDEC_ void msADCSelfMismatchCal_SVIDEO_C ( void );
#endif
#endif
