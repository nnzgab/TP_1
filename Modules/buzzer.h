//=====[#include guards - begin]===============================================

#ifndef _BUZZER_H_
#define _BUZZER_H_

//=====[Declaration of public defines]=========================================
#define BUZZER		        PB_5
#define BUZZER_TIME_ON      300
//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void buzzerInit();
bool buzzerUpdate();

//=====[#include guards - end]=================================================

#endif // _BUZZER_H_