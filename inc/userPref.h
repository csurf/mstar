#ifndef _USERPREF_H_
#define _USERPREF_H_

#ifdef _USERPREF_C_
	#define _USERPREFDEC_
#else
	#define _USERPREFDEC_ extern
#endif

_USERPREFDEC_ void InitPCSetting ( void );
_USERPREFDEC_ void InitVideoSetting ( void );
//_USERPREFDEC_ void CheckMonitorSettingRange(void);
_USERPREFDEC_ void SaveVideoSetting ( void );
_USERPREFDEC_ void ReadSetting ( void );
_USERPREFDEC_ void SaveChannelNumberSetting ( void );
_USERPREFDEC_ void ReadChannelNumberSetting ( void );
_USERPREFDEC_ void msSetUserPref ( void );
_USERPREFDEC_ void msChipVersionRead ( void );
_USERPREFDEC_ BYTE usrCalCheckSum ( BYTE* pBuf, BYTE ucBufLen );

#endif
