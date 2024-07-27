//trabajar con este codigo que se aprobo en el Tp1 para el Tp2
/*
TP2 AGREGAR:
- manejo de teclado matricial
- cohesion y eso
- (sd card)
- (pantalla LCD)

*/

//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Defines]===============================================================
//TECLADO MATRICIAL entradas
#define C1      	    PA_8
#define C2              PA_9
#define C3              PA_10
#define C4              PA_15
#define C5              PB_15

//TECLADO MATRICIAL salidas: 
#define F1      	    PB_0
#define F2              PB_1
#define F3              PB_4


//PINES DE SISTEMAS
#define LED_1       	PB_12
#define LED_2       	PB_13
#define LED_3          	PB_14

// PINES DE ZONAS
#define LED_Z1       	PB_6
#define LED_Z2       	PB_7
#define LED_Z3          PB_8
#define LED_Z4       	PB_9
#define LED_Z5       	PB_10
#define LED_Z6          PB_11

// PINES DE ADC
#define VZONA        	PA_0
#define VBAT        	PA_1

// PINES DE BUZZER
#define BUZZER		    PB_5

//TIEMPOS
#define TIME_INCREMENT_MS   10
#define DEBOUNCE_TIME_MS    150
#define BUZZER_TIME_ON      300
#define TIME_OVER           600 //1200  falta implementar

#define TEC_MAT_NUM_COLUMNAS 5
#define TEC_MAT_NUM_FILAS 3
#define TIEMPO_ANTIREBOTE_MS 40

//MAXIMOS
#define MAX_LED_SISTEMA 3
#define MAX_LED_ZONAS 6
#define MAX_ADC		2

//=====[Declaration of public data types]======================================

//estados para el testeo
typedef enum {
    PREVIOUS_TEST,
	TEC1_TEST,
    TEC2_TEST,
    TEC3_TEST,
    TEC4_TEST,
    TEC5_TEST,
    TEC6_TEST,
    TEC7_TEST,
    TEC8_TEST,
    TEC9_TEST,
    TEC0_TEST,
    TEC_AST_TEST,
    TEC_NUM_TEST,
    TEC_P_TEST,
    TEC_F_TEST,
    TEC_E_TEST,
    LED_SISTEMA_TEST,
    LED_ZONAS_TEST,
    BUZZER_TEST,
    ADC_TEST,
	END_TEST
} testState_t;

//estados para teclado matricial
typedef enum {
    ESCANEANDO_TEC_MAT,
    ANTIREBOTE_TEC_MAT,
    MANTINE_PRECIONADO_TEC_MAT
} estado_teclado_matricial_t;


//=====[Declaration and initialization of public global objects]===============

DigitalIn tecladoMatricialColumnasPins[TEC_MAT_NUM_COLUMNAS] = {C1, C2, C3, C4, C5};
DigitalOut tecladoMatricialFilasPins[TEC_MAT_NUM_FILAS] = {F1, F2, F3};

DigitalOut ledsSistema[MAX_LED_SISTEMA] = {LED_1, LED_2, LED_3};
DigitalOut ledsZonas[MAX_LED_ZONAS] = {LED_Z1, LED_Z2, LED_Z3, LED_Z4, LED_Z5, LED_Z6};

DigitalOut outBuzzer(BUZZER);

AnalogIn lecturasAdc[MAX_ADC] = {VBAT, VZONA};

static UnbufferedSerial serial_port(USBTX, USBRX, 9600);


//=====[Declaration and initialization of public global variables]=============

testState_t current_State = PREVIOUS_TEST;

int tiempoAcumuladoAntirebote_tecladoMatricial = 0;

char ultimaTeclaPresionada = '\0';

char indice2caracerMatricial[3][5] = {
    {'1', '2', '3', '*', 'P'},
    {'4', '5', '6', '0', 'F'},
    {'7', '8', '9', '#', 'E'}
};

estado_teclado_matricial_t tecladoMatricialEstado;

int accumulatedDebounceTime = 0;
bool timeOutActivated = true;
int timeOut = 0;


//=====[Declarations (prototypes) of public functions]=========================

//******************
void tecladoMatricialInit();
char escaneoTecladoMatricial();
char actualizarTecladoMatricial(); // debuelve el caracter que se pulsa
//******************

void actualizarEstado();
void secuenciaLed();
void blinking_all_leds();
void checkTimeout();

void taskADC(int );
bool detectarInicioTest();
void prenderLedZonaNumero(int numeroLed);
void prenderLedSistemaNumero(int numeroLed);
void secuenciaLed();
void blinking_all_leds();


//=====[Main function, the program entry point after power on or reset]========

int main(){

    outBuzzer = OFF;
    
    serial_port.write( "Presione '1' + '#' para iniciar test\r\n", 38);

    while (true) {
        actualizarEstado();
        checkTimeout();
        delay(TIME_INCREMENT_MS);
    }
}


//=====[Implementations of public functions]===================================

void actualizarEstado(){
    switch (current_State) {

        case PREVIOUS_TEST:
			if( detectarInicioTest() == true ){
				//nextState = TEC1_TEST;
                //current_State = STATE_DEBOUNCE; // probar si no es suficiente pasar a tec1_ test y sacar el estado debounce po que el anti rebote se incluye en actualizarTercladoMatricial()
				timeOut = 0;
                //apagarLeds()
				//ledArm = OFF;
				//ledReady = OFF;
				//ledSystem = OFF;
				serial_port.write( "INICIO DEL TEST\r\n", 17);
				serial_port.write( "Presione '1' para continuar\r\n", 29);
                current_State = TEC1_TEST;
				//actualizarTercladoMatricial();
			}
            break;
			
		case TEC1_TEST:
            if(actualizarTecladoMatricial() == '1'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC2_TEST;
                serial_port.write( "Presione Tecla 2 para continuar\r\n", 33);
            }
            break;

        case TEC2_TEST:
            if(actualizarTecladoMatricial() == '2'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC3_TEST;
                serial_port.write( "Presione Tecla 3 para continuar\r\n", 33);
            }
            break;
		
		case TEC3_TEST:
            if(actualizarTecladoMatricial() == '3'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC4_TEST;
                serial_port.write( "Presione Tecla 4 para continuar\r\n", 33);
            }
            break;

        case TEC4_TEST:
            if(actualizarTecladoMatricial() == '4'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC5_TEST;
                serial_port.write( "Presione Tecla 5 para continuar\r\n", 33);
            }
            break;

		case TEC5_TEST:
            if(actualizarTecladoMatricial() == '5'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC6_TEST;
                serial_port.write( "Presione Tecla 6 para continuar\r\n", 33);
            }
            break;

        case TEC6_TEST:
            if(actualizarTecladoMatricial() == '6'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC7_TEST;
                serial_port.write( "Presione Tecla 7 para continuar\r\n", 33);
            }
            break;
		
		case TEC7_TEST:
            if(actualizarTecladoMatricial() == '7'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC8_TEST;
                serial_port.write( "Presione Tecla 8 para continuar\r\n", 33);
            }
            break;

        case TEC8_TEST:
            if(actualizarTecladoMatricial() == '8'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC9_TEST;
                serial_port.write( "Presione Tecla 9 para continuar\r\n", 33);
            }
            break;

		case TEC9_TEST:
            if(actualizarTecladoMatricial() == '9'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC0_TEST;
                serial_port.write( "Presione Tecla 0 para continuar\r\n", 33);
            }
            break;

        case TEC_AST_TEST:
            if(actualizarTecladoMatricial() == '*'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC_NUM_TEST;
                serial_port.write( "Presione Tecla # para continuar\r\n", 33);
            }
            break;
			
		case TEC_NUM_TEST:
            if(actualizarTecladoMatricial() == '#'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC_P_TEST;
                serial_port.write( "Presione Tecla P para continuar\r\n", 33);
            }
            break;
		
		case TEC_P_TEST:
            if(actualizarTecladoMatricial() == 'P'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC_F_TEST;
                serial_port.write( "Presione Tecla F para continuar\r\n", 33);
            }
            break;

        case TEC_F_TEST:
            if(actualizarTecladoMatricial() == 'F'){ //incluye antirebote
                timeOut = 0;
                current_State = TEC_E_TEST;
                serial_port.write( "Presione Tecla E para continuar\r\n", 33);
            }
             break;

		case TEC_E_TEST:
            if(actualizarTecladoMatricial() == 'E'){ //incluye antirebote
                timeOut = 0;
                current_State = LED_SISTEMA_TEST;
                serial_port.write( "Presione Tecla # para continuar\r\n", 33);
            }
            break;
		
		case LED_SISTEMA_TEST:
			static int cont = 0;
			if(actualizarTecladoMatricial() == '#'){
				cont ++;
				prenderLedSistemaNumero(cont);
				serial_port.write( "Presione Tecla # para continuar\r\n", 33);
				if(cont == MAX_LED_SISTEMA){
					current_State = LED_ZONAS_TEST;
					serial_port.write( "Presione Tecla # para continuar\r\n", 33);
				}
			}
            break;
			
		case LED_ZONAS_TEST:
			static int cont_led = 0;
			if(actualizarTecladoMatricial() == '#'){
				cont_led ++;
				prenderLedZonaNumero(cont_led);
				serial_port.write( "Presione Tecla # para continuar\r\n", 33);
				if(cont_led == MAX_LED_ZONAS){
					current_State = BUZZER_TEST;
					serial_port.write( "Presione Tecla # para continuar\r\n", 33);
				}
			}

		case BUZZER_TEST:
			static bool onBuzzer = false;
			static int timeOnBuzzer = 0;
			if(actualizarTecladoMatricial() == '#'){
				onBuzzer = true;
			}
			if(onBuzzer == true){
				timeOnBuzzer = timeOnBuzzer + TIME_INCREMENT_MS;
				outBuzzer = ON;
				if(timeOnBuzzer >= BUZZER_TIME_ON){
					outBuzzer = OFF;
					current_State = ADC_TEST;
				}
			}
		break;
		
		case ADC_TEST:
			static int cont_adc = 0;
			if(actualizarTecladoMatricial() == '#'){
				cont_adc ++;
				if(cont_adc == 1){
					serial_port.write( "TENSION DE BATERIA\r\n", 20);
				} else if(cont_adc == 2){
					serial_port.write( "TENSION DE ZONA\r\n", 17);
				} else{
					current_State = END_TEST;
					serial_port.write( "Presione Tecla # para terminar\r\n", 32);
					break;
				}
				taskADC(cont_adc);
				serial_port.write( "Presione Tecla # para continuar\r\n", 33);
		    break;

		case END_TEST:
			static bool endTest = false;
            if(actualizarTecladoMatricial()){

            }
			//if((actualizarTecladoMatricial() == '#') && (endTest == false)){
            if(actualizarTecladoMatricial() == '#'){
				serial_port.write( "FINAL DEL TEST\r\n", 16);
				endTest = true;
			} else if(endTest == true){
				blinking_all_leds();
			}
		break;		
		default:
		break;
    }
}
}


void secuenciaLed(){		
}

void blinking_all_leds(){
}

void checkTimeout(){
    if(timeOutActivated == true){
        if(current_State == END_TEST){
            timeOutActivated = false;
            timeOut = 0;
        }else if(timeOut == TIME_OVER){
            serial_port.write( "Fin de Test x Time out!!!\r\n", 27);
            //apago los leds todos
            current_State = END_TEST;
            timeOutActivated = false;
        }else{
            timeOut++;
        }
    }else{
        timeOut = 0;
    }
}


char actualizarTercladoMatricial(){
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
                tecladoMatricialEstado = MANTINE_PRECIONADO_TEC_MAT;
            } else {
                tecladoMatricialEstado = ESCANEANDO_TEC_MAT;
            }
        }
        tiempoAcumuladoAntirebote_tecladoMatricial = tiempoAcumuladoAntirebote_tecladoMatricial + TIME_INCREMENT_MS;
        break;

        case MANTINE_PRECIONADO_TEC_MAT:
        teclaDetectada = escaneoTecladoMatricial();
        if ( teclaDetectada != ultimaTeclaPresionada ) {
            if ( teclaDetectada == '\0' ) {
                teclaLiberada = ultimaTeclaPresionada;
            }
            tecladoMatricialEstado = ESCANEANDO_TEC_MAT;
        }
        break;

        default:
        tecladoMatricialInit();
        break;
    }
    return teclaLiberada;
}

void tecladoMatricialInit(){
    tecladoMatricialEstado = ESCANEANDO_TEC_MAT;
    int pinIndex = 0;
    for ( pinIndex = 0; pinIndex < TEC_MAT_NUM_COLUMNAS; pinIndex++ ){
        tecladoMatricialColumnasPins[pinIndex].mode(PullUp);
    }
}

char escaneoTecladoMatricial(){
    int fila = 0;
    int columna = 0;
    int i = 0;
    for ( fila = 0; fila < TEC_MAT_NUM_FILAS; fila++ ) {//--------------------FILA----------

        for ( i = 0; fila < TEC_MAT_NUM_FILAS; i++ ){
            tecladoMatricialFilasPins[i] = ON;
        }
        tecladoMatricialFilasPins[fila] = OFF;

        for ( columna = 0; columna < TEC_MAT_NUM_COLUMNAS; columna++ ){//-----COLUMNA-------
            if (tecladoMatricialColumnasPins[columna] == OFF) {
				return indice2caracerMatricial[fila][columna];// si detecto busco el caracter y devuelvo
			}
        }
    }
	return '\0'; // si no detecto nada devuelvo caracer nulo
}
bool detectarInicioTest(){
	static bool primera_tecla = false;
	static bool segunda_tecla = false;
    int fila = 0;
    int columna = 0;
    int i = 0;
    for ( fila = 0; fila < TEC_MAT_NUM_FILAS; fila++ ) {//--------------------FILA----------

        for ( i = 0; fila < TEC_MAT_NUM_FILAS; i++ ){
            tecladoMatricialFilasPins[i] = ON;
        }
        tecladoMatricialFilasPins[fila] = OFF;

        for ( columna = 0; columna < TEC_MAT_NUM_COLUMNAS; columna++ ){//-----COLUMNA-------
            if (tecladoMatricialColumnasPins[columna] == OFF) {
				if(indice2caracerMatricial[fila][columna] == '1' && primera_tecla == false){
					primera_tecla = true;
				} else if(indice2caracerMatricial[fila][columna] == '#' && segunda_tecla == false){
					segunda_tecla = true;
				}
			}
        }
    }
	if (primera_tecla == true && segunda_tecla == true){
		return true;
	}else{
		return false;
	}
}

void taskADC(int adc_a_leer){
    char str[100];
    int stringLength;
    float voltageReading;
    voltageReading = 3.3 * lecturasAdc[adc_a_leer].read();
    stringLength = sprintf(str, "Voltaje: %.2f V\r\n", voltageReading);
	if (stringLength <= 0) {
		serial_port.write( "ERROR LECTURA ADC\r\n", 19);
	} else {
		serial_port.write(str, stringLength);
	}
}

void prenderLedSistemaNumero(int numeroLed){
    int i;
    for ( i = 0; i < MAX_LED_SISTEMA; i++ ){
        ledsSistema[i] = OFF;
    }
    ledsSistema[numeroLed] = ON;
}

void prenderLedZonaNumero(int numeroLed){
    int i;
    for ( i = 0; i < MAX_LED_ZONAS; i++ ){
        ledsZonas[i] = OFF;
    }
    ledsZonas[numeroLed] = ON;
}
