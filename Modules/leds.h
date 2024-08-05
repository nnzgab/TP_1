//=====[#include guards - begin]===============================================

#ifndef _LEDS_H_
#define _LEDS_H_

//=====[Declaration of public defines]=========================================

#define MAX_LED_SISTEMA 3
#define MAX_LED_ZONAS   6

//=====[Declaration of public data types]======================================


//=====[Declarations (prototypes) of public functions]=========================


void LedSistemInit();
void LedZonaInit();

void secuenciaLed();
void blinking_all_leds();


void prenderLedSistemaNumero(int numeroLed);
void prenderLedZonaNumero(int numeroLed);

//=====[#include guards - end]=================================================

#endif // _LEDS_H_