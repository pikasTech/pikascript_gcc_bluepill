/* ******************************** */
/* Warning! Don't modify this file! */
/* ******************************** */
#include "PikaMain.h"
#include <stdio.h>
#include <stdlib.h>

PikaObj *__pikaMain;
PikaObj *pikaScriptInit(void){
    __platform_printf("======[pikascript packages installed]======\r\n");
    __platform_printf("PikaStdDevice==v1.8.0\r\n");
    __platform_printf("PikaStdLib==v1.8.3\r\n");
    __platform_printf("STM32F1==v1.1.0\r\n");
    __platform_printf("pikascript-core==v1.8.3\r\n");
    __platform_printf("===========================================\r\n");
    __pikaMain = newRootObj("pikaMain", New_PikaMain);
    extern unsigned char pikaModules_py_a[];
    obj_linkLibrary(__pikaMain, pikaModules_py_a);
#if PIKA_INIT_STRING_ENABLE
    obj_run(__pikaMain,
            "import PikaStdLib\n"
            "# import machine\n"
            "print('hello pikascript!')\n"
            "mem = PikaStdLib.MemChecker()\n"
            "print('mem used max:')\n"
            "mem.max()\n"
            "\n");
#else 
    obj_runModule(__pikaMain, "main");
#endif
    return __pikaMain;
}

