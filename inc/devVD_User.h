
#if( PanelWidth == 1366 )
	#define MSVD_HTOTAL_NTSC ((DWORD)1366*858/720) // 1628
	#define MSVD_HTOTAL_PAL ((DWORD)1366*864/720) // 1639
	#define MSVD_HTOTAL_SECAM ((DWORD)1366*864/720)
	#define MSVD_HTOTAL_NTSC_443 ((DWORD)1366*864/720)
	#define MSVD_HTOTAL_PAL_M ((DWORD)1366*858/720)
	#define MSVD_HTOTAL_PAL_NC ((DWORD)1366*858/720)
	#define MSVD_HACTIVE_NTSC ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_SECAM ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_NTSC_443 ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL_M ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL_NC ((DWORD)PanelWidth)


	#elif( PanelWidth == 1280 )
	#define MSVD_HTOTAL_NTSC ((DWORD)1366*858/720) // 1525
	#define MSVD_HTOTAL_PAL ((DWORD)1280*864/720) // 1536
	#define MSVD_HTOTAL_SECAM ((DWORD)1280*864/720)
	#define MSVD_HTOTAL_NTSC_443 ((DWORD)1280*864/720)
	#define MSVD_HTOTAL_PAL_M ((DWORD)1280*858/720)
	#define MSVD_HTOTAL_PAL_NC ((DWORD)1280*858/720)
	#define MSVD_HACTIVE_NTSC ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_SECAM ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_NTSC_443 ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL_M ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL_NC ((DWORD)PanelWidth)


	#elif( PanelWidth == 1024 )
	#if (SCALER_TYPE==MARIA9&&ENABLE_VD_32FSC)
		#define MSVD_HTOTAL_NTSC 858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL 858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_SECAM 858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_NTSC_443 858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_60 858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_M 858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_NC 858//((DWORD)1024+(1024-720))
		#define MSVD_HACTIVE_NTSC ((DWORD)720*MSVD_HTOTAL_NTSC*2/858)//((DWORD)((1440*MSVD_HTOTAL_NTSC/858)))//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL ((DWORD)720*MSVD_HTOTAL_PAL*2/858)//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_SECAM ((DWORD)720*MSVD_HTOTAL_SECAM*2/858)//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_NTSC_443 ((DWORD)720*MSVD_HTOTAL_NTSC_443*2/858)//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL_60 ((DWORD)720*MSVD_HTOTAL_PAL_60*2/858)//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL_M ((DWORD)720*MSVD_HTOTAL_PAL_M*2/858)//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL_NC ((DWORD)720*MSVD_HTOTAL_PAL_NC*2/858)//((DWORD)(PANEL_WIDTH<<1))
	#else
		#define MSVD_HTOTAL_NTSC ((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL ((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_SECAM ((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_NTSC_443 ((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_60 ((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_M ((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_NC ((DWORD)1024+(1024-720))
		#define MSVD_HACTIVE_NTSC ((DWORD)PanelWidth)
		#define MSVD_HACTIVE_PAL ((DWORD)PanelWidth)
		#define MSVD_HACTIVE_SECAM ((DWORD)PanelWidth)
		#define MSVD_HACTIVE_NTSC_443 ((DWORD)PanelWidth)
		#define MSVD_HACTIVE_PAL_M ((DWORD)PanelWidth)
		#define MSVD_HACTIVE_PAL_NC ((DWORD)PanelWidth)
	#endif

#elif ( PanelWidth == 800 )
	#if(SCALER_TYPE == MARIA9 && ENABLE_VD_32FSC)
		#define MSVD_HTOTAL_NTSC 858//1135//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL 858//1135//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_SECAM 858//1135//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_NTSC_443 858//1135//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_60 858//1135//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_M 858//1135//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_NC 858//1135//((DWORD)1024+(1024-720))
		#define MSVD_HACTIVE_NTSC ((DWORD)720*MSVD_HTOTAL_NTSC*2/858)//((DWORD)((1440*MSVD_HTOTAL_NTSC/858)))//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL ((DWORD)720*MSVD_HTOTAL_PAL*2/858)//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_SECAM ((DWORD)720*MSVD_HTOTAL_SECAM*2/858)//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_NTSC_443 ((DWORD)720*MSVD_HTOTAL_NTSC_443*2/858)//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL_60 ((DWORD)720*MSVD_HTOTAL_PAL_60*2/858)//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL_M ((DWORD)720*MSVD_HTOTAL_PAL_M*2/858)//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL_NC ((DWORD)720*MSVD_HTOTAL_PAL_NC*2/858)//((DWORD)(PANEL_WIDTH<<1))
	#else
		#define MSVD_HTOTAL_NTSC ((DWORD)PanelWidth*128/100) // 1628
		#define MSVD_HTOTAL_PAL ((DWORD)PanelWidth*128/100) // 1639
		#define MSVD_HTOTAL_SECAM ((DWORD)PanelWidth*128/100)
		#define MSVD_HTOTAL_NTSC_443 ((DWORD)PanelWidth*128/100)
		#define MSVD_HTOTAL_PAL_60 ((DWORD)PanelWidth*128/100)
		#define MSVD_HTOTAL_PAL_M ((DWORD)PanelWidth*128/100)
		#define MSVD_HTOTAL_PAL_NC ((DWORD)PanelWidth*128/100)
		#define MSVD_HACTIVE_NTSC ((DWORD)PanelWidth) //*115/100)
		#define MSVD_HACTIVE_PAL ((DWORD)PanelWidth) //*115/100)
		#define MSVD_HACTIVE_SECAM ((DWORD)PanelWidth) //*115/100)
		#define MSVD_HACTIVE_NTSC_443 ((DWORD)PanelWidth) //*115/100)
		#define MSVD_HACTIVE_PAL_60 ((DWORD)PanelWidth) //*115/100)
		#define MSVD_HACTIVE_PAL_M ((DWORD)PanelWidth) //*115/100)
		#define MSVD_HACTIVE_PAL_NC ((DWORD)PanelWidth) //*115/100)
	#endif

	#elif( PanelWidth == 640 )
	#if (SCALER_TYPE==MARIA9&&ENABLE_VD_32FSC)
		#define MSVD_HTOTAL_NTSC 910//858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL 910//1135//858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_SECAM 1097//858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_NTSC_443 1127//858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_60 1127//858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_M 909//858//((DWORD)1024+(1024-720))
		#define MSVD_HTOTAL_PAL_NC 917//858//((DWORD)1024+(1024-720))
		#define MSVD_HACTIVE_NTSC ((DWORD)720*MSVD_HTOTAL_NTSC*2/858)//((DWORD)(720<<1))//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL ((DWORD)720*MSVD_HTOTAL_PAL*2/858)//((DWORD)(720<<1))//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_SECAM ((DWORD)720*MSVD_HTOTAL_SECAM*2/858)//((DWORD)(720<<1))//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_NTSC_443 ((DWORD)720*MSVD_HTOTAL_NTSC_443*2/858)//((DWORD)(720<<1))//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL_60 ((DWORD)720*MSVD_HTOTAL_PAL_60*2/858)//((DWORD)(720<<1))//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL_M ((DWORD)720*MSVD_HTOTAL_PAL_M*2/858)//((DWORD)(720<<1))//((DWORD)(PANEL_WIDTH<<1))
		#define MSVD_HACTIVE_PAL_NC ((DWORD)720*MSVD_HTOTAL_PAL_NC*2/858)//((DWORD)(720<<1))//((DWORD)(PANEL_WIDTH<<1))
	#else

		#define MSVD_HTOTAL_NTSC ((DWORD)840)//858-(720-640)/2)
		#define MSVD_HTOTAL_PAL ((DWORD)840)//864-(720-640)/2)
		#define MSVD_HTOTAL_SECAM ((DWORD)864-(720-640)/2)
		#define MSVD_HTOTAL_NTSC_443 ((DWORD)864-(720-640)/2)
		#define MSVD_HTOTAL_PAL_60 ((DWORD)864-(720-640)/2)
		#define MSVD_HTOTAL_PAL_M ((DWORD)858-(720-640)/2)
		#define MSVD_HTOTAL_PAL_NC ((DWORD)858-(720-640)/2)
		#define MSVD_HACTIVE_NTSC ((DWORD)PanelWidth)
		#define MSVD_HACTIVE_PAL ((DWORD)PanelWidth)
		#define MSVD_HACTIVE_SECAM ((DWORD)PanelWidth)
		#define MSVD_HACTIVE_NTSC_443 ((DWORD)PanelWidth)
		#define MSVD_HACTIVE_PAL_M ((DWORD)PanelWidth)
		#define MSVD_HACTIVE_PAL_NC ((DWORD)PanelWidth)
	#endif

	#elif( PanelWidth == 480)

	#define MSVD_HTOTAL_NTSC ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_PAL ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_SECAM ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_NTSC_443 ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_PAL_M ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_PAL_NC ((DWORD)858-(640-480)/2)
	#define MSVD_HACTIVE_NTSC ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_SECAM ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_NTSC_443 ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL_M ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL_NC ((DWORD)PanelWidth)

	#elif( PanelWidth == 400)
	#define MSVD_HTOTAL_NTSC ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_PAL ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_SECAM ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_NTSC_443 ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_PAL_M ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_PAL_NC ((DWORD)858-(640-480)/2)
	#define MSVD_HACTIVE_NTSC ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_SECAM ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_NTSC_443 ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL_M ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL_NC ((DWORD)PanelWidth)

	#elif( PanelWidth == 320)
	#define MSVD_HTOTAL_NTSC ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_PAL ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_SECAM ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_NTSC_443 ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_PAL_M ((DWORD)858-(640-480)/2)
	#define MSVD_HTOTAL_PAL_NC ((DWORD)858-(640-480)/2)
	#define MSVD_HACTIVE_NTSC ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_SECAM ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_NTSC_443 ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL_M ((DWORD)PanelWidth)
	#define MSVD_HACTIVE_PAL_NC ((DWORD)PanelWidth)
#endif

#ifndef MSVD_HTOTAL_PAL_60
	#define MSVD_HTOTAL_PAL_60 MSVD_HTOTAL_NTSC_443
#endif
#ifndef MSVD_HACTIVE_PAL_60
	#define MSVD_HACTIVE_PAL_60 MSVD_HACTIVE_NTSC_443
#endif
