//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "functional_test.h"
#include "teclado_matricial.h"
#include "leds.h"
#include "buzzer.h"
#include "serial_port.h"
#include "test_states.h"
#include "time_out.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void functionalTestInit(){
    tecladoMatricialInit();
    LedSistemInit();
    LedZonaInit();
    buzzerInit();
    mensajeInicial();
}

void functionalTestUpdate(){
    actualizarEstado();
    checkTimeout();
    delay(TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================

