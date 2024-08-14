//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "time_out.h"

#include "serial_port.h"

#include "leds.h"
#include "test_states.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============


//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

bool timeOutActivated = true; //ver como  mejorar
int timeOut = 0; // ver como mejorar

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void checkTimeout(){
    static int timeOutActivated = true;
    if (timeOutActivated == true) {
        if (checkEndState()) {
            timeOutActivated = false;
            timeOut = 0;
        } else if (timeOut == TIME_OVER) {
            mensajeTimeOut();
            LedZonaInit();
            LedSistemInit();
            setEndState();
            timeOutActivated = false;
        } else {
            timeOut++;
        }
    } else {
        timeOut = 0;
    }
}

void timeOutReset(){
    timeOut = 0;
}

//=====[Implementations of private functions]==================================