#!/bin/bash
openocd \
-c "tcl_port disabled" \
-c "gdb_port 3333" \
-c "telnet_port 4444" \
-s /usr/share/openocd/scripts \
-f board/stm32f429discovery.cfg \
-c "init;reset init;" \
-c "echo (((READY)))" \
-c "flash write_image erase $(find . -type f -name "kernel.elf.bin" -print -quit) 0x08000000 bin" \
-c "halt"
