/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "machine_GPIO.h"
#include "STM32F1_GPIO.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

PikaObj *New_machine_GPIO(Args *args){
    PikaObj *self = New_STM32F1_GPIO(args);
    return self;
}

Arg *machine_GPIO(PikaObj *self){
    return obj_newObjInPackage(New_machine_GPIO);
}
