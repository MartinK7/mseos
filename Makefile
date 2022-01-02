
# DEFAULT CONFIGURE
CROSS_COMPILE ?= arm-none-eabi-
TARGET_PLATOFRM ?= STM32F429_DISCOVERY

# SOURCES DEPENDENCY

ifeq ($(TARGET_PLATOFRM),STM32F429_DISCOVERY)
LINKERSCRIPT := ./kernel/platform/stm32f429_discovery/linkerscript.ld
TARGET := stm32f429_discovery
SRC += ./kernel/platform/stm32f429_discovery/head.o
SRC += ./kernel/platform/stm32f429_discovery/boot.o
CCFLAGS += -mthumb -mcpu=cortex-m4
endif

SRC += ./kernel/main.o

# COMPILER CODE

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

all: $(SRC)
	$(LD) $(SRC) -o $(TARGET).elf -T $(LINKERSCRIPT)
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
	xxd $(TARGET).bin
	$(OBJDUMP) $(TARGET).elf -d

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	$(RM) $(SRC) $(TARGET).elf $(TARGET).elf $(TARGET).bin
	
