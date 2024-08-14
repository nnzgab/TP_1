#include "mbed.h"
#include "arm_book_lib.h"

#include "adc.h"

//#include "functional_test.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn lecturasAdc[MAX_ADC] = {VBAT, VZONA};

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

float lecturaAdc( int adc_a_leer){
    float voltajeLeido = 3.3 * lecturasAdc[adc_a_leer].read();
    return voltajeLeido;
}

//=====[Implementations of private functions]==================================






