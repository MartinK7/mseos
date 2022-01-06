
#include "configure.h"
#include "main.h"

extern void platform_init(void);
extern void platform_register(void);

extern unsigned int _rodata_end;
extern unsigned int _data_start;
extern unsigned int _data_end;
extern unsigned int _bss_start;
extern unsigned int _bss_end;

// Kernel space
unsigned int __attribute__((section(".kstack"))) _kstack[CONFIG_KSTACK_SIZE];
unsigned int __attribute__((section(".kheap"))) _kheap[CONFIG_KHEAP_SIZE];

// Userspace
unsigned int __attribute__((section(".uheap"))) _uheap[CONFIG_UHEAP_SIZE];

_Noreturn void _loop(void)
{
	for(;;);
}

_Noreturn void _reset(void)
{
	unsigned int *src, *dst;

	asm volatile ("cpsid i");

	src = &_rodata_end;
	dst = &_data_start;
	while (dst < &_data_end) {
		*dst++ = *src++;
	}

	dst = &_bss_start;
	while (dst < &_bss_end) {
		*dst++ = 0;
	}

	platform_init();
	kernel_init();
	platform_register();
	kernel_start();
	_loop();
}

