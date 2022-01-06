
################################################################################
##                                 TARGET                                     ##
################################################################################

# DEFAULT CONFIGURE
CROSS_COMPILE ?= arm-none-eabi-
TARGET_PLATOFRM ?= STM32F429_DISCOVERY
TARGET_ARCH ?= ARM

################################################################################
##                            PLATFORM SOURCES                                ##
################################################################################

# PLATFORM
ifeq ($(TARGET_PLATOFRM),STM32F429_DISCOVERY)
LINKERSCRIPT := kernel/platform/stm32f429_discovery/linkerscript.ld
TARGET := stm32f429_discovery
CFLAGS += -mthumb -mcpu=cortex-m4 -D STM32F429xx
# Sources
SRC += kernel/platform/stm32f429_discovery/head.s
SRC += kernel/platform/stm32f429_discovery/platform.c
SRC += kernel/cpu/arm/boot.c
# Includes
INC += -I kernel/platform/stm32f429_discovery
INC += -I kernel/cpu/arm/device/st/stm32f4xx
endif

################################################################################
##                              ARCH SOURCES                                  ##
################################################################################

# PLATFORM
ifeq ($(TARGET_ARCH),ARM)
INC += -I kernel/cpu/arm/cmsis
endif

################################################################################
##                   KERNEL COMMON SOURCES AND INCLUDES                       ##
################################################################################

# SOURCES
SRC += kernel/source/main.c

# INCLUDES
INC += -I kernel/include

################################################################################
##                              COMPILER                                      ##
################################################################################

# COMPILER EXECUTABLES

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

# COMPILER SETTINGS

CFLAGS += -nostdlib -nostdinc

# MAKEFILE DEPENDENCIES

OBJ := $(SRC:.c=.o)
OBJ := $(OBJ:.s=.o)

.PHONY: all
all: clean
	make tools
	make apps
	make kernel
	@echo "ALL - DONE"

.PHONY: tools
tools:
	make -C tools/bin2c
	@echo "TOOLS - DONE"
	
.PHONY: apps
apps:
	make -C apps/stm32blink
	@echo "APPS - DONE"

.PHONY: kernel
kernel: $(OBJ)
	$(LD) $(OBJ) -o $(TARGET).elf -T $(LINKERSCRIPT)
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
	xxd $(TARGET).bin
	$(OBJDUMP) $(TARGET).elf -d
	@echo "KERNEL - DONE"

%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(INC) $(CFLAGS) -c $< -o $@
	
################################################################################
##                              OTHER                                         ##
################################################################################

.PHONY: clean
clean:
	make -C tools/bin2c clean
	make -C apps/stm32blink clean
	$(RM) $(OBJ) $(TARGET).elf $(TARGET).bin
	@echo "CLEAN - DONE"
	
################################################################################
##                     Auto-Dependency Generation                             ##
################################################################################

# TODO :D I'm still not successful to do it properly
