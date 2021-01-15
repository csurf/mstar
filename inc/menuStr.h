#ifndef _MENUSTR_C_
#define _MENUSTR_H_

#ifdef _MENUSTR_C_
	#define _MENUSTRDEC_
#else
	#define _MENUSTRDEC_ extern
#endif

_MENUSTRDEC_ BYTE* ContrastText ( void );
_MENUSTRDEC_ BYTE* BrightnessText ( void );
_MENUSTRDEC_ BYTE* SaturationText ( void );
_MENUSTRDEC_ BYTE* VideoHueText ( void );

_MENUSTRDEC_ BYTE* ResetText ( void );
_MENUSTRDEC_ BYTE* HandIcon ( void );

_MENUSTRDEC_ BYTE* BacklightText ( void );

_MENUSTRDEC_ BYTE* VideoStdText ( void );
_MENUSTRDEC_ BYTE* CurrentChromaModeText ( void );

_MENUSTRDEC_ BYTE* SourceText ( void );

_MENUSTRDEC_ BYTE* SelectOFFText ( void );
_MENUSTRDEC_ BYTE* SelectONText ( void );

_MENUSTRDEC_ BYTE* S_SYSText ( void );
_MENUSTRDEC_ BYTE* SWAPText ( void );
_MENUSTRDEC_ BYTE* COPYText ( void );

_MENUSTRDEC_ BYTE* Scaling_ModeText ( void );
_MENUSTRDEC_ BYTE* ScalingText ( void );

#endif
