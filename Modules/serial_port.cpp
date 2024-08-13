//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "serial_port.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================



//=====[Declaration and initialization of public global objects]===============

static UnbufferedSerial serial_port(USBTX, USBRX, 9600);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================
void mensajeInicial(){
    serial_port.write( "Presione '1' + '#' para iniciar test\r\n", 38);
}

void mensajeContinuarTecla( char teclaSiguiente){ // agregar que reciba el valor de x
    char mensaje_str[100];
    int mensaje_stringLength;
    mensaje_stringLength = sprintf(mensaje_str, "Presione Tecla %c para continuar\r\n", teclaSiguiente);
    serial_port.write(mensaje_str, mensaje_stringLength);
}

void mensajeContinuarSecuencia(){
    serial_port.write( "Presione Tecla # para continuar\r\n", 33);
}

void mensajeInciaTest(){
    serial_port.write( "INICIO DEL TEST\r\n", 17);
	serial_port.write( "Presione Tecla 1 para continuar\r\n", 33);
}
void mensajeFinalizaTest(){
    serial_port.write( "FINAL DEL TEST\r\n", 16);
}

void serial_portStringLecturaAdc( float lecturaAdc, int adcLeido){
    char str[100];
    int stringLength;
    switch(adcLeido){
        case 0:
        serial_port.write( "TENSION DE BATERIA\r\n", 20);
        break;
        case 1:
        serial_port.write( "TENSION DE ZONA\r\n", 17);
        break;
        default:
        serial_port.write( "ERROR\r\n", 7);
        break;        
    }
    stringLength = sprintf(str, "Voltaje: %.2f V\r\n", lecturaAdc);
	if (stringLength <= 0) {
		serial_port.write( "ERROR LECTURA ADC\r\n", 19);
	} else {
		serial_port.write(str, stringLength);
	}
}

void mensajeTimeOut(){
    serial_port.write( "Fin de Test x Time out!!!\r\n", 27);
}
            
//=====[Implementations of private functions]==================================

