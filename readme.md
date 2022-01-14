# MSEOS - Minimal and Simple Educative Operating System

It is an experimental operating system (mostly for ARM) at a *VERY* early stage of development.

What works now:
- Boot kernel on STM32F429 discovery kit
- Build blinking app, embed its MEXE data in raw format to kernel (flash)
- Copy MEXE app from flash to RAM and execute
- Simple heap (free not implemented, only alloc)
- Simple sytem call (temporary solution via syscall table in memory at fixed address (not portable))

Todo:
- Task sheduler (2 MEXE application should run simultaneously)

In future todo:
- Process system (tasks switching etc.)
- Rootdir manager
- Device driver
- FS driver
- Some simple libraries
