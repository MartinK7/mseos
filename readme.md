# MSEOS - Minimal and Simple Educative Operating System

It is an experimental operating system (mostly for ARM) at a *VERY* early stage of development.

What works now:
- Boot kernel on STM32F429 discovery kit
- Build blinking app, embed its MEXE data in raw format to kernel (flash)
- Copy MEXE app from flash to RAM and execute
- Simple heap (free not implemented, only alloc)
- Simple sytem call (temporary solution via syscall table in memory at fixed address (not portable))
- Task sheduler test, 2 MEXE application running simultaneously!! yey!

Todo:
- Temporary debug system calls: debwrite, debread
- Rootdir manager + RAMFS -> InitRAMFS (open,write,close,etc.)
- System call for executing MEXE files
- Simple shell-terminal program via. UART (creating files, read files, executing file)

In future todo:
- Device drivers
- Some simple libraries
- True systemcalls (rather then calling functions at fixed address)
