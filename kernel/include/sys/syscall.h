
#ifndef MSEOS_SYSCALL_H
#define MSEOS_SYSCALL_H

#define __TO_STRING0(x) #x
#define __TO_STRING(x) __TO_STRING0(x)

#define __SYSCALL __attribute__((naked,noinline)) static

#define __SWI(NUM)                                \
{                                                 \
	__asm volatile (                              \
		"mov   r7, #"__TO_STRING(NUM)"        \n" \
		"swi   0                              \n" \
		"bx    lr                             \n" \
	);                                            \
}

// Syscall table list
__SYSCALL uint32_t syscall_open(uint32_t a, uint32_t b, uint32_t c, uint32_t d) __SWI(0)
__SYSCALL uint32_t syscall_close(uint32_t a, uint32_t b, uint32_t c, uint32_t d) __SWI(1)
__SYSCALL uint32_t syscall_read(uint32_t a, uint32_t b, uint32_t c, uint32_t d) __SWI(2)
__SYSCALL uint32_t syscall_write(uint32_t a, uint32_t b, uint32_t c, uint32_t d) __SWI(3)
__SYSCALL uint32_t syscall_flush(uint32_t a, uint32_t b, uint32_t c, uint32_t d) __SWI(4)
__SYSCALL uint32_t syscall_ioctl(uint32_t a, uint32_t b, uint32_t c, uint32_t d) __SWI(5)

#undef __SYSCALL
#undef __SWI
#undef __SYSCALL_TO_STRING
#undef __SYSCALL_TO_STRING0

#endif //MSEOS_SYSCALL_H
