
#ifndef MSEOS_SYSCALL_H
#define MSEOS_SYSCALL_H

// I hate temporary solution, but I'm not currently successful with software interrupt
// Now the system call vector table lays at fixed address point
#define SYSCALL_OFFSET 0x080001ACUL

#define _O(id) (*((uint32_t*)(SYSCALL_OFFSET + 0x00000004UL * id)))

#define syscall_open  ((void (*)(void))_O(0))
#define syscall_close ((void (*)(void))_O(1))
#define syscall_read  ((void (*)(void))_O(2))
#define syscall_write ((void (*)(void))_O(3))
#define syscall_flush ((void (*)(void))_O(4))
#define syscall_ioctl ((void (*)(void))_O(5))

#endif //MSEOS_SYSCALL_H
