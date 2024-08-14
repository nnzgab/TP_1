//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "leds.h"

//#include "buzzer.h"

#include "functional_test.h"

//=====[Declaration of private defines]========================================

#define LED_1       	PB_12
#define LED_2       	PB_13
#define LED_3          	PB_14

#define LED_Z1       	PB_6
#define LED_Z2       	PB_7
#define LED_Z3          PB_8
#define LED_Z4       	PB_9
#define LED_Z5       	PB_10
#define LED_Z6          PB_11

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut ledsSistema[MAX_LED_SISTEMA] = {LED_1, LED_2, LED_3};
DigitalOut ledsZonas[MAX_LED_ZONAS] = {LED_Z1, LED_Z2, LED_Z3, LED_Z4, LED_Z5, LED_Z6};

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void LedSistemInit(){
    int i;
    for ( i = 0; i < MAX_LED_SISTEMA; i++ ){
        ledsSistema[i] = OFF;
    }
}

void LedZonaInit(){
    int i;
    for ( i = 0; i < MAX_LED_ZONAS; i++ ){
        ledsZonas[i] = OFF;
    }
}

void LedSistemOn(){
    int i;
    for ( i = 0; i < MAX_LED_SISTEMA; i++ ){
        ledsSistema[i] = ON;
    }
}

void LedZonaOn(){
    int i;
    for ( i = 0; i < MAX_LED_ZONAS; i++ ){
        ledsZonas[i] = ON;
    }
}

void prenderLedSistemaNumero(int numeroLed){
    int i;
    for ( i = 0; i < MAX_LED_SISTEMA; i++ ){
        ledsSistema[i].write(OFF);
    }
    ledsSistema[numeroLed].write(ON);
}

void prenderLedZonaNumero(int numeroLed){
    int i;
    for ( i = 0; i < MAX_LED_ZONAS; i++ ){
        ledsZonas[i].write(OFF);
    }
    ledsZonas[numeroLed].write(ON);
}

void secuenciaLed(){
    static int timeBlink = 0;
    timeBlink = timeBlink + TIME_INCREMENT_MS;
    if(timeBlink < 500){
        LedZonaOn();
        LedSistemInit();
    } else if (timeBlink < 1000){
        LedSistemOn();
        LedZonaInit();
    }else{
        timeBlink = 0;
    }
}	

void blinking_all_leds(){
    static int timeBlink = 0;
    timeBlink = timeBlink + TIME_INCREMENT_MS;
    if (timeBlink < 500) {
        LedZonaOn();
        LedSistemOn();
    } else if (timeBlink < 1000) {
        LedZonaInit();
        LedSistemInit();
    } else {
        timeBlink = 0;
    }
}

//=====[Implementations of private functions]==================================
