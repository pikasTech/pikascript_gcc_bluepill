# PikaScript Bluepill GCC Build

Build PikaScript for STM32f103c8t6 with arm-gcc. Makefile does:

1. Build all `.c` files on folders:

- `Booter/`
- `Drivers/STM32F1xx_HAL_Driver/Src/`
- `startup_stm32f103xb_gcc.s` (startup file)
- `pikascript/pikascript-lib/PikaStdDevice/`
- `pikascript/pikascript-lib/PikaStdLib/`
- `pikascript/pikascript-lib/STM32F1/`
- `pikascript/pikascript-core/`
- `pikascript/pikascript-api/`

and save all objects in `obj` directory

2. Links all objects in `obj` directory to produce `bin/firmware.elf` file

3. Dumps and make `.hex` and `.bin` binaries in `bin` folder

4. Display the size of the binary in terminal window

## Issues

Image size too big (a lot!) to fit 128K Flash

## Observation

Packages needed:

- arm-none-eabi-gcc
- make
- VS Code (optional)