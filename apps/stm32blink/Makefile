
CROSS_COMPILE ?= arm-none-eabi-
LINKERSCRIPT := linkerscript.ld

TARGET := stm32blink

# SOURCES
SRC += main.o
SRC += head.o

# INCLUDES
INC += -I ../../kernel/include

# COMPILER EXECUTABLES

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
BIN2C := ../../tools/bin2c/bin2c.elf

# COMPILER SETTINGS

CCFLAGS += -nostdlib -nostdinc -fPIC

# MAKEFILE DEPENDENCIES

all: clean $(SRC)
	$(LD) $(SRC) -o $(TARGET).elf -T $(LINKERSCRIPT)
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin
	xxd $(TARGET).bin
	$(OBJDUMP) $(TARGET).elf -d
	$(BIN2C) $(TARGET).bin > $(TARGET).bin.c

%.o: %.c
	$(CC) $(INC) $(CCFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(INC) $(CCFLAGS) -c $< -o $@

clean:
	$(RM) $(SRC) $(TARGET).elf $(TARGET).bin $(TARGET).bin.c
	
