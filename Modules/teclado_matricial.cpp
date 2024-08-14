//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "teclado_matricial.h"

#include "functional_test.h"

//=====[Declaration of private defines]========================================


//NUMERO DE FILAS Y COLUMNAS DEL TECLADO
#define TEC_MAT_NUM_FILAS 4
#define TEC_MAT_NUM_COLUMNAS 3
/*
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
*/
#define TIEMPO_ANTIREBOTE_MS 40

//TECLADO MATRICIAL entradas
#define C1      	PB_0
#define C2              PB_1
#define C3              PB_4

//TECLADO MATRICIAL salidas:
#define F1      	PA_8
#define F2              PA_9
#define F3              PA_10
#define F4              PA_15

//=====[Declaration of private data types]=====================================

//ESTADO PARA EL TECLADO MATRICIAL
typedef enum {
    ESCANEANDO_TEC_MAT,
    ANTIREBOTE_TEC_MAT,
    MANTIENE_PRESIONADO_TEC_MAT
} estado_teclado_matricial_t;

//=====[Declaration and initialization of public global objects]===============

DigitalOut tecladoMatricialFilasPins[TEC_MAT_NUM_FILAS] = {F1, F2, F3, F4};
DigitalIn tecladoMatricialColumnasPins[TEC_MAT_NUM_COLUMNAS] = {C1, C2, C3};

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============


//=====[Declaration and initialization of private global variables]============

static estado_teclado_matricial_t tecladoMatricialEstado;

static char indice2caracerMatricial[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}
};

//=====[Declarations (prototypes) of private functions]========================

static char escaneoTecladoMatricial();
static void tecladoMatricialReset();

//=====[Implementations of public functions]===================================

void tecladoMatricialInit(){
    tecladoMatricialEstado = ESCANEANDO_TEC_MAT;
    int pinIndex = 0;
    for ( pinIndex = 0; pinIndex < TEC_MAT_NUM_COLUMNAS; pinIndex++ ){
        (tecladoMatricialColumnasPins[pinIndex]).mode(PullUp);
    }
}

bool detectarInicioTest(){
    static bool primera_tecla = false;
    static bool segunda_tecla = false;
    char tecla = escaneoTecladoMatricial();
    if(tecla == '1'){
    	primera_tecla = true;
    } else if ( tecla == '#'){
    	segunda_tecla = true;
    }

    if (primera_tecla == true && segunda_tecla == true){
        primera_tecla = false;
        segunda_tecla = false;
	return true;
    } else {
	return false;
    }
}

char ActTecMat() {
    static int tiempoAcumuladoAntirebote_tecladoMatricial = 0;
    static char ultimaTeclaPresionada = '\0';

    char teclaDetectada = '\0';
    char teclaLiberada = '\0';
    switch(tecladoMatricialEstado){
        case ESCANEANDO_TEC_MAT:
            teclaDetectada = escaneoTecladoMatricial();
            if( teclaDetectada != '\0' ) {
                ultimaTeclaPresionada = teclaDetectada;
                tiempoAcumuladoAntirebote_tecladoMatricial = 0;
                tecladoMatricialEstado = ANTIREBOTE_TEC_MAT;
            }
            break;

        case  ANTIREBOTE_TEC_MAT:
            if( tiempoAcumuladoAntirebote_tecladoMatricial >= TIEMPO_ANTIREBOTE_MS){
                teclaDetectada = escaneoTecladoMatricial();
                if ( teclaDetectada == ultimaTeclaPresionada ) {
                    tecladoMatricialEstado = MANTIENE_PRESIONADO_TEC_MAT;
                } else {
                    tecladoMatricialEstado = ESCANEANDO_TEC_MAT;
                }
            }
            tiempoAcumuladoAntirebote_tecladoMatricial = tiempoAcumuladoAntirebote_tecladoMatricial + TIME_INCREMENT_MS;
            break;

        case MANTIENE_PRESIONADO_TEC_MAT:
            teclaDetectada = escaneoTecladoMatricial();
            if ( teclaDetectada != ultimaTeclaPresionada ) {
                if ( teclaDetectada == '\0' ) {
                    teclaLiberada = ultimaTeclaPresionada;
                }
                tecladoMatricialEstado = ESCANEANDO_TEC_MAT;
            }
            break;

        default:
            tecladoMatricialReset();
            break;
    }
    return teclaLiberada;
}

//=====[Implementations of private functions]==================================

static char escaneoTecladoMatricial(){
    int fila = 0;
    int columna = 0;
    int i = 0;
    
    for ( fila = 0; fila < TEC_MAT_NUM_FILAS; fila++ ) {

        for ( i = 0; i < TEC_MAT_NUM_FILAS; i++ ){
            tecladoMatricialFilasPins[i].write(ON);
        }
        tecladoMatricialFilasPins[fila].write(OFF);

        for ( columna = 0; columna < TEC_MAT_NUM_COLUMNAS; columna++ ){
            if (tecladoMatricialColumnasPins[columna] == OFF) {
	        return indice2caracerMatricial[fila][columna];
	    }
        }
    }
    return '\0';
}

static void tecladoMatricialReset(){
    tecladoMatricialEstado = ESCANEANDO_TEC_MAT;
}
