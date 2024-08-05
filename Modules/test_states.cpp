//=====[Libraries]=============================================================

#include "buzzer.h"
#include "mbed.h"
#include "arm_book_lib.h"

#include "test_states.h"
#include "leds.h"
#include "time_out.h"
#include "teclado_matricial.h"
#include "serial_port.h"
#include "adc.h"

//=====[Declaration of private defines]========================================


//=====[Declaration of private data types]=====================================

//ESTADOS PARA EL TESTEO
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
    LED_SISTEMA_TEST,
    LED_ZONAS_TEST,
    BUZZER_TEST,
    ADC_TEST,
	END_TEST
} testState_t;

//=====[Declaration and initialization of public global objects]===============


//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

testState_t current_State = PREVIOUS_TEST;

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================



//=====[Implementations of public functions]===================================

void actualizarEstado(){
    switch (current_State) {
        case PREVIOUS_TEST:
            secuenciaLed();
			if( detectarInicioTest() == true ){
				timeOutReset();
                LedSistemInit();
                LedZonaInit();
                mensajeInciaTest();
                current_State = TEC1_TEST;
			}
            break;
			
		case TEC1_TEST:
            if(ActTecMat() == '1'){
                timeOutReset();
                current_State = TEC2_TEST;
                mensajeContinuarTecla('2');
            }
            break;

        case TEC2_TEST:
            if(ActTecMat() == '2'){
                timeOutReset();
                current_State = TEC3_TEST;
                mensajeContinuarTecla('3');
            }
            break;
		
		case TEC3_TEST:
            if(ActTecMat() == '3'){
                timeOutReset();
                current_State = TEC4_TEST;
                mensajeContinuarTecla('4');
            }
            break;

        case TEC4_TEST:
            if(ActTecMat() == '4'){
                timeOutReset();
                current_State = TEC5_TEST;
                mensajeContinuarTecla('5');
            }
            break;

		case TEC5_TEST:
            if(ActTecMat() == '5'){
                timeOutReset();
                current_State = TEC6_TEST;
                mensajeContinuarTecla('6');
            }
            break;

        case TEC6_TEST:
            if(ActTecMat() == '6'){
                timeOutReset();
                current_State = TEC7_TEST;
                mensajeContinuarTecla('7');
            }
            break;
		
		case TEC7_TEST:
            if(ActTecMat() == '7'){
                timeOutReset();
                current_State = TEC8_TEST;
                mensajeContinuarTecla('8');
            }
            break;

        case TEC8_TEST:
            if(ActTecMat() == '8'){
                timeOutReset();
                current_State = TEC9_TEST;
                mensajeContinuarTecla('9');
            }
            break;

		case TEC9_TEST:
            if(ActTecMat() == '9'){
                timeOutReset();
                current_State = TEC0_TEST;
                mensajeContinuarTecla('0');
            }
            break;

        case TEC0_TEST:
            if(ActTecMat() == '0'){
                timeOutReset();
                current_State = TEC_AST_TEST;
                mensajeContinuarTecla('*');
            }
            break;

        case TEC_AST_TEST:
            if(ActTecMat() == '*'){
                timeOutReset();
                current_State = TEC_NUM_TEST;
                mensajeContinuarTecla('#');
            }
            break;
			
		case TEC_NUM_TEST:
            if(ActTecMat() == '#'){
                timeOutReset();
                current_State = LED_SISTEMA_TEST;//TEC_P_TEST;
                mensajeContinuarSecuencia();
            }
            break;

		case LED_SISTEMA_TEST:
			static int cont = 0;
			if(ActTecMat() == '#'){
                timeOutReset();
                if(cont<MAX_LED_SISTEMA){
                    prenderLedSistemaNumero(cont);
                    cont ++;
                    mensajeContinuarSecuencia();
                } else {
                    current_State = LED_ZONAS_TEST;
                    LedSistemInit();
                }
			}
            break;
			
		case LED_ZONAS_TEST:
			static int cont_led = 0;
			if(ActTecMat() == '#'){
                timeOutReset();
                if(cont_led<MAX_LED_ZONAS){
                    prenderLedZonaNumero(cont_led);
                    cont_led ++;
                    mensajeContinuarSecuencia();
                } else {
                    current_State = BUZZER_TEST;
                    LedZonaInit();
                }
			}
            break;

		case BUZZER_TEST://OJO CUANDO DA TRUE VER BUZZER.CPP
            if(buzzerUpdate()){
                current_State = ADC_TEST;
                mensajeContinuarSecuencia();
            } else {
                current_State = BUZZER_TEST;
            }
            break;
		
		case ADC_TEST:
			static int cont_adc = 0;
            static float lectura = 0.0;
			if(ActTecMat() == '#'){
				timeOutReset();
                switch (cont_adc) {
                case 0:
                    lectura = lecturaAdc(cont_adc);
                    serial_portStringLecturaAdc(lectura, cont_adc);                    
                    break;
                case 1:
                    lectura = lecturaAdc(cont_adc);
                    serial_portStringLecturaAdc(lectura, cont_adc);
                    break;
                default:
                    current_State = END_TEST;
                    mensajeContinuarSecuencia();
                break;
                }
                cont_adc ++;
            }
            break;

        case END_TEST:
            static bool firstTime = true;
            if (firstTime) {
                mensajeFinalizaTest();
                firstTime = false;
            }
            blinking_all_leds();
        break;

        default:
            current_State = PREVIOUS_TEST;
        break;
    }
}
bool checkEndState(){
    if( current_State == END_TEST){
        return true;
    } else {
        return false;
    }
}

void setEndState(){
    current_State = END_TEST;
}
//=====[Implementations of private functions]==================================

