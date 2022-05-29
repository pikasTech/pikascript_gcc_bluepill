/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "machine_Time.h"
#include "STM32F1_Time.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

PikaObj *New_machine_Time(Args *args){
    PikaObj *self = New_STM32F1_Time(args);
    return self;
}

Arg *machine_Time(PikaObj *self){
    return obj_newObjInPackage(New_machine_Time);
}
