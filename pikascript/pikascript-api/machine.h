/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#ifndef __machine__H
#define __machine__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New_machine(Args *args);

Arg* machine_ADC(PikaObj *self);
Arg* machine_GPIO(PikaObj *self);
Arg* machine_IIC(PikaObj *self);
Arg* machine_PWM(PikaObj *self);
Arg* machine_Time(PikaObj *self);
Arg* machine_UART(PikaObj *self);
Arg* machine_lowLevel(PikaObj *self);

#endif
