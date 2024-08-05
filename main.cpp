//=====[Libraries]=============================================================

#include "functional_test.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    functionalTestInit();
    while (true) {
        functionalTestUpdate();
    }
}
