PREFIX 			= arm-none-eabi-
CC 				= $(PREFIX)gcc
OBJCOPY			= $(PREFIX)objcopy
DUMP			= $(PREFIX)objdump
SIZE			= $(PREFIX)size
BIN_DIR 		= bin
OBJ_DIR 		= obj
LINKERSCRIPT 	= STM32F103C8Tx_FLASH.ld

# cflags
CFLAGS  = -c
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb
CFLAGS += -Os

# includes
INC  = -IBooter
INC += -IDrivers/STM32F1xx_HAL_Driver/Inc
INC += -IDrivers/CMSIS/Device/ST/STM32F1xx/Include
INC += -IDrivers/CMSIS/Include
INC += -IDrivers/STM32F1xx_HAL_Driver/Inc/Legacy
INC += -Ipikascript/pikascript-api
INC += -Ipikascript/pikascript-core
INC += -Ipikascript/pikascript-lib/STM32F1

# defines
DEF  = -DSTM32F103xB
DEF += -DUSE_STDPERIPH_DRIVER

# Linker flags
LDFLAGS  = -T$(LINKERSCRIPT)
LDFLAGS	+= -mthumb 
LDFLAGS	+= -mcpu=cortex-m0
LDFLAGS += --specs=nosys.specs
LDFLAGS += --specs=nano.specs

# objects
SRCS_PIKA_LIB1	 = $(wildcard pikascript/pikascript-lib/PikaStdDevice/*.c)
SRCS_PIKA_LIB2 	 = $(wildcard pikascript/pikascript-lib/PikaStdLib/*.c)
SRCS_PIKA_LIB3 	 = $(wildcard pikascript/pikascript-lib/STM32F1/*.c)
OBJS_PIKA_LIB1 	 = $(patsubst pikascript/pikascript-lib/PikaStdDevice/%.c, $(OBJ_DIR)/%.o, $(SRCS_PIKA_LIB1))
OBJS_PIKA_LIB2 	 = $(patsubst pikascript/pikascript-lib/PikaStdLib/%.c, $(OBJ_DIR)/%.o, $(SRCS_PIKA_LIB2))
OBJS_PIKA_LIB3 	 = $(patsubst pikascript/pikascript-lib/STM32F1/%.c, $(OBJ_DIR)/%.o, $(SRCS_PIKA_LIB3))
SRCS_PIKA_CORE 	 = $(wildcard pikascript/pikascript-core/*.c)
OBJS_PIKA_CORE	 = $(patsubst pikascript/pikascript-core/%.c, $(OBJ_DIR)/%.o, $(SRCS_PIKA_CORE))
SRCS_PIKA_API 	 = $(wildcard pikascript/pikascript-api/*.c)
OBJS_PIKA_API	 = $(patsubst pikascript/pikascript-api/%.c, $(OBJ_DIR)/%.o, $(SRCS_PIKA_API))
SRCS_HAL 		 = $(wildcard Drivers/STM32F1xx_HAL_Driver/Src/*.c)
OBJS_HAL 		 = $(patsubst Drivers/STM32F1xx_HAL_Driver/Src/%.c, $(OBJ_DIR)/%.o, $(SRCS_HAL))
SRCS_BOOTER		 = $(wildcard Booter/*.c)
OBJS_BOOTER		 = $(patsubst Booter/%.c, $(OBJ_DIR)/%.o, $(SRCS_BOOTER))
OBJ_STARTUP		 = $(OBJ_DIR)/startup_stm32f103xb_gcc.o
OBJS 			 = $(OBJS_PIKA_LIB1)
OBJS 			+= $(OBJS_PIKA_LIB2)
OBJS 			+= $(OBJS_PIKA_LIB3)
OBJS 			+= $(OBJS_PIKA_CORE)
OBJS 			+= $(OBJS_PIKA_API)
OBJS 			+= $(OBJS_HAL)
OBJS 			+= $(OBJS_BOOTER)
OBJS 			+= $(OBJ_STARTUP)

# link from objects, dump and make binaries
.PHONY: all
all: $(BIN_DIR)/firmware.elf $(BIN_DIR)/firmware.hex $(BIN_DIR)/firmware.bin $(BIN_DIR)/firmware_dump.lst
$(BIN_DIR)/firmware.elf $(BIN_DIR)/firmware.hex $(BIN_DIR)/firmware.bin $(BIN_DIR)/firmware_dump.lst: $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(OBJDUMP) -D $(BIN_DIR)/firmware.elf > $(BIN_DIR)/firmware_dump.lst
	$(OBJCOPY) -R .stack -O binary $(BIN_DIR)/firmware.elf $(BIN_DIR)/firmware.bin
	$(OBJCOPY) -R .stack -O ihex $(BIN_DIR)/firmware.elf $(BIN_DIR)/firmware.hex
	$(SIZE) $(BIN_DIR)/firmware.elf

# compile and assemble, but not link
.PHONY: objs
objs: $(OBJS)

.PHONY: pika_lib
pika_lib: $(OBJS_PIKA_LIB1) $(OBJS_PIKA_LIB2) $(OBJS_PIKA_LIB3) | $(OBJ_DIR)
$(OBJ_DIR)/%.o: pikascript/pikascript-lib/PikaStdDevice/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEF) $(INC) $< -o $@
$(OBJ_DIR)/%.o: pikascript/pikascript-lib/PikaStdLib/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEF) $(INC) $< -o $@
$(OBJ_DIR)/%.o: pikascript/pikascript-lib/STM32F1/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEF) $(INC) $< -o $@

.PHONY: startup
startup: $(OBJ_STARTUP) | $(OBJ_DIR)
$(OBJ_STARTUP): startup_stm32f103xb_gcc.s 
	$(CC) -x assembler-with-cpp $(CFLAGS) $(DEF) $(INC) $< -o $@

.PHONY: pika_api
# ERASE PIKA_BYTECODE_ALIGN BEFORE COMPILING
pika_api: $(OBJS_PIKA_API) | $(OBJ_DIR)
$(OBJ_DIR)/%.o: pikascript/pikascript-api/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEF) $(INC) $< -o $@

.PHONY: pika_core
pika_core: $(OBJS_PIKA_CORE) | $(OBJ_DIR)
$(OBJ_DIR)/%.o: pikascript/pikascript-core/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEF) $(INC) $< -o $@

.PHONY: hal
hal: $(OBJS_HAL) | $(OBJ_DIR)
$(OBJ_DIR)/%.o: Drivers/STM32F1xx_HAL_Driver/Src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEF) $(INC) $< -o $@

.PHONY: booter
booter: $(OBJS_BOOTER) | $(OBJ_DIR)
$(OBJ_DIR)/%.o: Booter/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEF) $(INC) $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir $@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
