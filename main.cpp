//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Defines]===============================================================

#define LED_1       	    PB_12
#define LED_2       	    PB_13
#define LED_3          	    PB_14

#define BOTON1      	    PA_8
#define BOTON2              PA_9
#define BOTON3              PA_10

#define VBAT        	    PA_7

#define BUZZER		    PB_5

#define TIME_INCREMENT_MS   10
#define DEBOUNCE_TIME_MS    150
#define BUZZER_TIME_ON      300
#define TIME_OVER           600 //1200

//=====[Declaration of public data types]======================================
typedef enum {
    PREVIOUS_TEST,
    TEC1_TEST,
    TEC2_TEST,
    TEC3_TEST,
    LED1_TEST,
    LED2_TEST,
    LED3_TEST,
    BUZZER_TEST,
    ADC_TEST,
    END_TEST,
    STATE_DEBOUNCE
} testState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn tecla_1(BOTON1);
DigitalIn tecla_2(BOTON2);
DigitalIn tecla_3(BOTON3);

DigitalOut ledArm(LED_1);
DigitalOut ledReady(LED_2);
DigitalOut ledSystem(LED_3);

DigitalOut outBuzzer(BUZZER);

AnalogIn batVol(VBAT);

static UnbufferedSerial serial_port(USBTX, USBRX, 9600);

//=====[Declaration and initialization of public global variables]=============

testState_t current_State = PREVIOUS_TEST;
testState_t nextState = PREVIOUS_TEST;

int accumulatedDebounceTime = 0;
bool timeOutActivated = true;
int timeOut = 0;

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();
void actualizarEstado();
void taskADC();
void secuenciaLed();
void blinking_all_leds();
void checkTimeout();

//=====[Main function, the program entry point after power on or reset]========

int main() {
    inputsInit();
    outputsInit();
    serial_port.write( "Presione Tecla1 + Tecla 2 para iniciar test\r\n", 45);

    while (true) {
        actualizarEstado();
        checkTimeout();
        delay(TIME_INCREMENT_MS);
    }
}

//=====[Implementations of public functions]===================================

void inputsInit() {
    tecla_1.mode(PullDown);
    tecla_2.mode(PullDown);
    tecla_3.mode(PullDown);
}

void outputsInit() {
    ledArm = OFF;
    ledReady = OFF;
    ledSystem = OFF;
    outBuzzer = OFF;
}

void actualizarEstado() {
    switch (current_State) {
        case PREVIOUS_TEST:
            secuenciaLed();
            if ((tecla_1.read() == 1) && (tecla_2.read() == 1)) {
		timeOut = 0;
		nextState = TEC1_TEST;
		current_State = STATE_DEBOUNCE;
		ledArm = OFF;
		ledReady = OFF;
		ledSystem = OFF;
		serial_port.write( "INICIO DEL TEST\r\n", 17);
		serial_port.write( "Presione Tecla 1 para continuar\r\n", 33);
            }
            break;
			
        case TEC1_TEST:
            if (tecla_1.read() == 1) {
                timeOut = 0;
                nextState = TEC2_TEST;
                current_State = STATE_DEBOUNCE;
                serial_port.write( "Presione Tecla 2 para continuar\r\n", 33);
            }
            break;

        case TEC2_TEST:
            if (tecla_2.read() == 1) {
                timeOut = 0;
                nextState = TEC3_TEST;
                current_State = STATE_DEBOUNCE;
                serial_port.write( "Presione Tecla 3 para continuar\r\n", 33);
            }
            break;

        case TEC3_TEST:
            if (tecla_3.read() == 1) {
                timeOut = 0;
                nextState = LED1_TEST;
                current_State = STATE_DEBOUNCE;
                serial_port.write( "Presione Tecla 1 para continuar\r\n", 33);
            }
            break;

        case LED1_TEST:
            if (tecla_1.read() == 1) {
                timeOut = 0;
                nextState = LED2_TEST;
                current_State = STATE_DEBOUNCE;
                ledArm = ON;
                ledReady = OFF;
                ledSystem = OFF;
                serial_port.write( "Presione Tecla 1 para continuar\r\n", 33);
            }
            break;

        case LED2_TEST:
            if (tecla_1.read() == 1) {
                timeOut = 0;
                nextState = LED3_TEST;
                current_State = STATE_DEBOUNCE;
                ledArm = OFF;
                ledReady = ON;
                ledSystem = OFF;           
                serial_port.write( "Presione Tecla 1 para continuar\r\n", 33);
            }
            break;
        
        case LED3_TEST:
            if (tecla_1.read() == 1) {
                timeOut = 0;
                nextState = BUZZER_TEST;
                current_State = STATE_DEBOUNCE;
                ledArm = OFF;
                ledReady = OFF;
                ledSystem = ON;
                serial_port.write( "Presione Tecla 1 para continuar\r\n", 33);
            }
            break;

        case BUZZER_TEST:
            static int timeOn = 0;
            static bool probarBuzzer = false;
            if(tecla_1.read() == 1){
                timeOut = 0;
                nextState = BUZZER_TEST;
                current_State = STATE_DEBOUNCE;
                ledArm = OFF;
                ledReady = OFF;
                ledSystem = OFF;
                probarBuzzer = true;
            } else if (probarBuzzer == true) {

                if (timeOn < BUZZER_TIME_ON) {
                    timeOut = 0;
                    outBuzzer = ON;
                    timeOn = timeOn + TIME_INCREMENT_MS;
                } else {
		    timeOut = 0;
		    outBuzzer = OFF;
		    current_State = ADC_TEST;
		    serial_port.write( "Presione Tecla 1 para continuar\r\n", 33);
		    probarBuzzer = false;
                }
            }
            break;

        case ADC_TEST:
            static bool leerADC = false;
            if (tecla_1.read() == 1) {
                nextState = ADC_TEST;
                current_State = STATE_DEBOUNCE;
                timeOut = 0;
                leerADC = true;
            } else if (leerADC == true) {
                taskADC();
                serial_port.write( "FINAL DEL TEST\r\n", 16);
                current_State = END_TEST;
            }
            break;

        case END_TEST:
            blinking_all_leds();
            break;

        case STATE_DEBOUNCE:
            static int accumulatedDebounceTime = 0;
            if (accumulatedDebounceTime >= DEBOUNCE_TIME_MS) {
                current_State = nextState;
                accumulatedDebounceTime = 0;
            } else {
                accumulatedDebounceTime =   accumulatedDebounceTime + TIME_INCREMENT_MS;
            }
            break;
    }
}

void taskADC() {
    char str[100];
    int stringLength;
    float vbatReading = 3.3 * batVol.read();
    sprintf(str, "Voltaje: %.2f V\r\n", vbatReading);
    stringLength = strlen(str);
    serial_port.write(str, stringLength);
}

void secuenciaLed() {
    static int accumulatedTime = 0;
    accumulatedTime = accumulatedTime + TIME_INCREMENT_MS;
    if(accumulatedTime == 750){
	accumulatedTime = 0;
	} else if (accumulatedTime < 250) {
	ledArm = ON;
        ledReady = OFF;
        ledSystem = OFF;
	} else if(accumulatedTime < 500){
        ledArm = OFF;
        ledReady = ON;
        ledSystem = OFF;
	} else{
	ledArm = OFF;
	ledReady = OFF;
	ledSystem = ON;
	}			
}

void blinking_all_leds(){
    static int accumulatedTime = 0;
    if (accumulatedTime > 250) {
        ledArm = !ledArm;
        ledReady = !ledReady;
        ledSystem = !ledSystem;
        accumulatedTime = 0;
    } else {
        accumulatedTime = accumulatedTime + TIME_INCREMENT_MS;
    } 
}

void checkTimeout(){
    if (timeOutActivated == true) {
        if (current_State == END_TEST) {
            timeOutActivated = false;
            timeOut = 0;
        } else if (timeOut == TIME_OVER){
            serial_port.write( "Fin de Test x Time out!!!\r\n", 27);
            ledArm = OFF;
            ledReady = OFF;
            ledSystem = OFF;
            current_State = END_TEST;
            timeOutActivated = false;
        } else {
            timeOut++;
        }
    } else {
        timeOut = 0;
    }
}
