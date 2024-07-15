/* arranca secuencia de led uno tras otro si pulsa t1 y t2 
arranca el testel test probando las teclas los leds el buzzer
y el adc termina el test y apaga todo y pone fin al test*/

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
#define TIME_OVER           600 //1200

static UnbufferedSerial serial_port(USBTX, USBRX, 9600);

//=====[Declaration and initialization of public global objects]===============

DigitalIn tecla_1(BOTON1);
DigitalIn tecla_2(BOTON2);
DigitalIn tecla_3(BOTON3);

DigitalOut ledArm(LED_1);
DigitalOut ledReady(LED_2);
DigitalOut ledSystem(LED_3);

DigitalOut outBuzzer(BUZZER);

AnalogIn batVol(VBAT);

//=====[Declaration and initialization of public global variables]=============

bool timerOutActivated = true;
bool runTest = false;
bool endTest = false;

bool finishRecorrerTeclas = false;
bool finishRecorrerLeds = false;
bool finishBuzzer = false;
bool finishReadAdc = false;

int timeout = 0;
int accumulatedTime = 0;
int testNum = 0;

float vbatReading = 0.0;

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();
void previoTest();
void startTest();
void run_Test();
void end_Test();
void checkTimeout();
void secuenciaLed();
void apagarLeds();
void recorrer_teclas();
void controlarLed();
void prenderLedNumero(int );
void beepBeep();
void mostrarLecturaAdc();

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    inputsInit();
    outputsInit();
    serial_port.write( "Presione Tecla1 + Tecla 2 para iniciar test\r\n", 45);
    while (true) {
        previoTest();
        startTest();
        run_Test();
        end_Test();
        checkTimeout();
        delay(TIME_INCREMENT_MS);
    }
}

//=====[Implementations of public functions]===================================

void inputsInit()
{
    tecla_1.mode(PullDown);
    tecla_2.mode(PullDown);
    tecla_3.mode(PullDown);
}

void outputsInit()
{
    ledArm = OFF;
    ledReady = OFF;
    ledSystem = OFF;
    outBuzzer = OFF;
}

void secuenciaLed(){
    accumulatedTime = accumulatedTime + TIME_INCREMENT_MS;
    if(accumulatedTime < 250){
        ledArm = ON;
        ledReady = OFF;
        ledSystem = OFF;
    }
    if(accumulatedTime >= 250 && accumulatedTime < 500){
        ledArm = OFF;
        ledReady = ON;
        ledSystem = OFF;
    }
    if(accumulatedTime >= 500 && accumulatedTime < 750){
        ledArm = OFF;
        ledReady = OFF;
        ledSystem = ON;
    }
    if(accumulatedTime == 750){
        accumulatedTime = 0;
    }
}

void previoTest(){
    if (runTest == false && endTest == false){
        secuenciaLed();
    }
}

void startTest(){
    if(runTest == false && endTest == false){
        if(tecla_1 == 1 && tecla_2 == 1){
            runTest = true;
            ledArm = 0;
            ledReady = 0;
            ledSystem = 0;
            accumulatedTime = 0;
            timeout = 0;
			delay(250);
        }
    }
}

void run_Test(){
    if(runTest == true && timeout < TIME_OVER){
        if(finishRecorrerTeclas == false){
            recorrer_teclas();
        }
        if(finishRecorrerLeds == false && finishRecorrerTeclas == true){
            controlarLed();
        }
        if(finishBuzzer == false && finishRecorrerLeds == true){
            beepBeep();
        }
        if(finishReadAdc == false && finishBuzzer == true){
            mostrarLecturaAdc();
        }
    }
}

void apagarLeds(){
    ledArm = OFF;    
    ledReady = OFF;
    ledSystem = OFF;
}

void prenderLedNumero(int numeroLed){
    switch(numeroLed){
        case 1: 
        ledArm = 1;
        serial_port.write( "LedArm encendido\r\n", 18);
        serial_port.write( "Presione Boton 1 para continuar\r\n", 33);
        break;
        case 2: 
        ledReady = 1; 
        serial_port.write( "LedReady encendido\r\n", 20);
        serial_port.write( "Presione Boton 1 para continuar\r\n", 33);
        break;
        case 3: 
        ledSystem = 1; 
        serial_port.write( "LedSystem encendido\r\n", 21);
        serial_port.write( "Presione Boton 1 para continuar\r\n", 33);
        break;
        default: 
        break;
    }
}

void controlarLed(){
    static int currentLED = 0;
    if(currentLED == 0){
            serial_port.write( "Testear LEDS\r\n", 14);
            serial_port.write( "Presione Tecla 1 para continuar\r\n", 33);
            currentLED++;
        }
    if (tecla_1 == 1) {
        delay(250);
        timeout = 0;
        apagarLeds();
        prenderLedNumero(currentLED);
        currentLED++;
        if (currentLED > 4) {
            timeout = 0;
            apagarLeds();
            finishRecorrerLeds = true;
        }
    }   
}

void end_Test(){
    if(endTest == true){
		runTest = false;
        timerOutActivated = false;
        apagarLeds();
        accumulatedTime = accumulatedTime + TIME_INCREMENT_MS;
        if(accumulatedTime == 500){
            ledArm = !ledArm;
            ledReady = !ledReady;
            ledSystem = !ledSystem;
            accumulatedTime = 0;
        }
    }
}

void checkTimeout(){
    if(timerOutActivated == true){
        timeout = timeout+1;
        if(timeout == TIME_OVER){
        endTest = true;
        runTest = false;
        apagarLeds();
        serial_port.write( "Fin de Test x Time out!!!\r\n", 27);
        }
    }
}

float analogReadingVoltage(float voltajeVbat){
    voltajeVbat = 3.3 * vbatReading;
    return voltajeVbat;
}

void taskADC(){
    char str[100];
    int stringLength;
    vbatReading = batVol.read();
    vbatReading = analogReadingVoltage(vbatReading);
    sprintf(str, "Voltaje: %.2f\r\n", vbatReading);
    stringLength = strlen(str);
    serial_port.write(str, stringLength);
}

void recorrer_teclas(){
    static int buttonNumberTest = 0;
    switch(buttonNumberTest){
    	case 0:
    		serial_port.write( "Presione Tecla 1 para continuar\r\n", 33);
        	buttonNumberTest ++;
    		break;
    	case 1: //pruebo tecla 1
    		if(tecla_1 == 1){
    			serial_port.write( "Presione Tecla 2 para continuar\r\n", 33);
		        timeout = 0;
		        delay(250);
		        buttonNumberTest ++;
    		}
            break;
    	case 2: //pruebo tecla 2
    		if(tecla_2 == 1){
    			serial_port.write( "Presione Tecla 3 para continuar\r\n", 33);
		        timeout = 0;
		        delay(250);
		        buttonNumberTest ++;
    		}
            break;
    	default: //pruebo tecla 3
    		if(tecla_3 == 1){
    			serial_port.write( "Fin Test Teclas\r\n", 17);
		        timeout = 0;
		        delay(250);
		        buttonNumberTest = 4;
		        finishRecorrerTeclas = true;
    		}
            break;
    }
}

void beepBeep(){
    static int timeBuzzer = 15;
    static int acum = 0;
    static int cont = 0;
    acum = acum + 1;
    if(cont == 0){
        serial_port.write( "Beep del Buzzer\r\n", 17);
        serial_port.write( "Presione Boton 1 para continua*\r\n", 33);
        cont = cont + 1;
    }
    
    if(acum == timeBuzzer && cont < 5){
        outBuzzer = !outBuzzer;
        acum = 0;
        cont = cont + 1;
    }
    if(cont == 5 && tecla_1 == 1){
        timeout = 0;
        finishBuzzer = true;
        delay(250);
    }
}

void mostrarLecturaAdc(){
    static bool mensaje = false;

    if(finishReadAdc == false && mensaje == false){
        serial_port.write( "Lectura ADC\r\n", 21);
        taskADC(); 
        serial_port.write( "Presione Boton 1 para Finalizar\r\n", 33);
        mensaje = true;
    }
    if(finishReadAdc == false && tecla_1 == 1){
        timeout = 0;
        serial_port.write( "Fin del Testeo\r\n", 16);
        finishReadAdc = true;
        endTest = true;
        delay(250);
    }   
}
