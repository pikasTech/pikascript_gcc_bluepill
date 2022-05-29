/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "machine_PWM.h"
#include "STM32F1_PWM.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

PikaObj *New_machine_PWM(Args *args){
    PikaObj *self = New_STM32F1_PWM(args);
    return self;
}

Arg *machine_PWM(PikaObj *self){
    return obj_newObjInPackage(New_machine_PWM);
}
