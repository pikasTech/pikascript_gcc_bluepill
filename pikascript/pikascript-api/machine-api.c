/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "machine.h"
#include "TinyObj.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

void machine_ADCMethod(PikaObj *self, Args *args){
    Arg* res = machine_ADC(self);
    method_returnArg(args, res);
}

void machine_GPIOMethod(PikaObj *self, Args *args){
    Arg* res = machine_GPIO(self);
    method_returnArg(args, res);
}

void machine_IICMethod(PikaObj *self, Args *args){
    Arg* res = machine_IIC(self);
    method_returnArg(args, res);
}

void machine_PWMMethod(PikaObj *self, Args *args){
    Arg* res = machine_PWM(self);
    method_returnArg(args, res);
}

void machine_TimeMethod(PikaObj *self, Args *args){
    Arg* res = machine_Time(self);
    method_returnArg(args, res);
}

void machine_UARTMethod(PikaObj *self, Args *args){
    Arg* res = machine_UART(self);
    method_returnArg(args, res);
}

void machine_lowLevelMethod(PikaObj *self, Args *args){
    Arg* res = machine_lowLevel(self);
    method_returnArg(args, res);
}

PikaObj *New_machine(Args *args){
    PikaObj *self = New_TinyObj(args);
    class_defineConstructor(self, "ADC()->any", machine_ADCMethod);
    class_defineConstructor(self, "GPIO()->any", machine_GPIOMethod);
    class_defineConstructor(self, "IIC()->any", machine_IICMethod);
    class_defineConstructor(self, "PWM()->any", machine_PWMMethod);
    class_defineConstructor(self, "Time()->any", machine_TimeMethod);
    class_defineConstructor(self, "UART()->any", machine_UARTMethod);
    class_defineConstructor(self, "lowLevel()->any", machine_lowLevelMethod);
    return self;
}

