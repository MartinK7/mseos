
# DEFAULT CONFIGURE
CROSS_COMPILE ?= arm-none-eabi-
TARGET_PLATOFRM ?= STM32F429_DISCOVERY

# PLATFORM
ifeq ($(TARGET_PLATOFRM),STM32F429_DISCOVERY)
LINKERSCRIPT := ./kernel/platform/stm32f429_discovery/linkerscript.ld
TARGET := stm32f429_discovery
SRC += ./kernel/platform/stm32f429_discovery/head.o
SRC += ./kernel/cpu/arm/boot.o
CCFLAGS += -mthumb -mcpu=cortex-m4
endif

# SOURCES
SRC += ./kernel/main.o

# INCLUDES
INC += -I kernel/include

# COMPILER EXECUTABLES

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

# COMPILER SETTINGS

CCFLAGS += -nostdlib -nostdinc

# MAKEFILE DEPENDENCIES


all: tools apps kernel
	echo "Done"

.PHONY: tools	
tools:
	make -C tools/bin2c
	
.PHONY: apps
apps:
	make -C apps/stm32blink

kernel: $(SRC)
	$(LD) $(SRC) -o $(TARGET).elf -T $(LINKERSCRIPT)
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
	xxd $(TARGET).bin
	$(OBJDUMP) $(TARGET).elf -d

%.o: %.c
	$(CC) $(INC) $(CCFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(INC) $(CCFLAGS) -c $< -o $@

clean:
	make -C tools/bin2c clean
	make -C apps/stm32blink clean
	$(RM) $(SRC) $(TARGET).elf $(TARGET).bin
	echo "Done"
	
