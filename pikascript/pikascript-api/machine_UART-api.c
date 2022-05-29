/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "machine_UART.h"
#include "STM32F1_UART.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

PikaObj *New_machine_UART(Args *args){
    PikaObj *self = New_STM32F1_UART(args);
    return self;
}

Arg *machine_UART(PikaObj *self){
    return obj_newObjInPackage(New_machine_UART);
}
