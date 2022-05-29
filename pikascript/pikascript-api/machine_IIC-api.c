/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "machine_IIC.h"
#include "STM32F1_IIC.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

PikaObj *New_machine_IIC(Args *args){
    PikaObj *self = New_STM32F1_IIC(args);
    return self;
}

Arg *machine_IIC(PikaObj *self){
    return obj_newObjInPackage(New_machine_IIC);
}
