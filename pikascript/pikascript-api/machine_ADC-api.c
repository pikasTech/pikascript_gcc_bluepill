/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "machine_ADC.h"
#include "STM32F1_ADC.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

PikaObj *New_machine_ADC(Args *args){
    PikaObj *self = New_STM32F1_ADC(args);
    return self;
}

Arg *machine_ADC(PikaObj *self){
    return obj_newObjInPackage(New_machine_ADC);
}
