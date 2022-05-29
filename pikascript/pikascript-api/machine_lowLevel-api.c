/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "machine_lowLevel.h"
#include "STM32F1_lowLevel.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

PikaObj *New_machine_lowLevel(Args *args){
    PikaObj *self = New_STM32F1_lowLevel(args);
    return self;
}

Arg *machine_lowLevel(PikaObj *self){
    return obj_newObjInPackage(New_machine_lowLevel);
}
