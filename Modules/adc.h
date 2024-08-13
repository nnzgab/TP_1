//=====[#include guards - begin]===============================================

#ifndef _ADC_H_
#define _ADC_H_

//=====[Declaration of public defines]=========================================

#define MAX_ADC         2
#define VZONA        	PA_0
#define VBAT        	PA_1
#define ADCZONA        	0
#define ADCBAT        	1

//=====[Declaration of public data types]======================================


//=====[Declarations (prototypes) of public functions]=========================
float lecturaAdc( int adc_a_leer);


//=====[#include guards - end]=================================================

#endif // _ADC_H_
