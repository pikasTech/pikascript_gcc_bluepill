/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "PikaMain.h"
#include "PikaStdLib_SysObj.h"
#include "PikaStdLib.h"
#include "machine.h"
#include <stdio.h>
#include <stdlib.h>
#include "BaseObj.h"

PikaObj *New_PikaMain(Args *args){
    PikaObj *self = New_PikaStdLib_SysObj(args);
    obj_newObj(self, "PikaStdLib", "PikaStdLib", New_PikaStdLib);
    obj_newObj(self, "machine", "machine", New_machine);
    return self;
}

Arg *PikaMain(PikaObj *self){
    return obj_newObjInPackage(New_PikaMain);
}
