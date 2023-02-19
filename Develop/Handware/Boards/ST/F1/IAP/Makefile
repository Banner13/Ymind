# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2023 - 02 - 11  start
# ------------------------------------------------

######################################
# target
######################################
TARGET = bootload

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

#######################################
# MCU FLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m3

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# device
DEVICE = STM32F10X_LD
ST_LIB = USE_STDPERIPH_DRIVER

#######################################
# compile gcc flags
#######################################
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

C_DEFS += -D$(DEVICE) 
C_DEFS += -D$(ST_LIB) 
CFLAGS += $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

# debug build?
DEBUG = 1
# optimization
OPT = -Og

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

######################################
# source
######################################
# ASM sources
ASM_SOURCES =  bootload.s

# AS includes
AS_INCLUDES = 

# C sources
C_SOURCES =  \
main.c \
./ST/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c \
./ST/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c \
./ST/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c \
./ST/Libraries/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c \
./assist/retarget.c

# C includes
C_INCLUDES = \
-I./ST/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x \
-I./ST/Libraries/CMSIS/CM3/CoreSupport/ \
-I./ST/Libraries/STM32F10x_StdPeriph_Driver/inc \
-I./ST/ \
-I./assist/

# link script
LDSCRIPT = stm32f103.ld

#######################################
# LDFLAGS
#######################################
# libraries
LIBS =  -lc -lm -lnosys
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

######################################
# build
######################################
# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@	

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)