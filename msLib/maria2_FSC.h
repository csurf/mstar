#ifndef __MSVD_FSC_H
#define __MSVD_FSC_H

void msVD_FSC_Init ( void );
void msVD_FSC_Detect ( void );

// Get current color burst status
BYTE msVD_FSC_GetColorBurstStatus ( void );


// Default parameter:
// ucNoise1 = 12. When noise < ucNoise1, => non noise mode
// ucNoise2 = 13. When noise > ucNoise2, => moise mode
void msVD_FSC_SetNoiseModeLevel ( BYTE ucNoise1, BYTE ucNoise2 );

// If Noise > ucNoiseOff => Color kill
void msVD_FSC_SetColorKillNoise ( BYTE ucNoiseOn, BYTE ucNoiseOff );


// If Burst < ucBurstOff => Color kill
void msVD_FSC_SetColorKillBurst ( BYTE ucBurstOn, BYTE ucBurstOff );


// Default parameter:
// ucBurstOn = 35. In low noise, if(input burst > ucBurstOn) => Has color
// ucBurstOff = 19. In low noise, if(input burst < ucBurstOff) => No color
// ucPhaseErrOn = 68. In high noise, if(input phase error < ucPhaseErrOn) => Has color
// ucPhaseErrOff = 76. In high noise, if(input phase error > ucPhaseErrOff) => No color
void msVD_FSC_SetColorKillLevel ( BYTE ucBurstOn, BYTE ucBurstOff, BYTE ucPhaseErrOn, BYTE ucPhaseErrOff );


// For debug
BYTE* msVD_FSC_GetVersion ( void );

// Reset internal status
void msVD_FSC_ResetColorBurstStatus ( void );


#endif
