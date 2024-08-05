//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "buzzer.h"

#include "functional_test.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut outBuzzer(BUZZER);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void buzzerInit(){
    outBuzzer = OFF;
}

bool buzzerUpdate(){
    static int timeOnBuzzer = 0;
    timeOnBuzzer = timeOnBuzzer + TIME_INCREMENT_MS;
    outBuzzer = ON;
    if (timeOnBuzzer > BUZZER_TIME_ON) {
        outBuzzer = OFF;
        //current_State = ADC_TEST;
        //timeOut = 0;
        //serial_port.write( "Presione Tecla # para continuar\r\n", 33);
        // si termino de sonar cambio de estado pongo time cero y mando mensaje pero desde quien llama
        return true;
    }
    return false;

}

//=====[Implementations of private functions]==================================