
#include "sys/types.h"

#include "configure.h"
#include "kernel.h"

extern void platform_init(void);
extern void platform_register(void);

extern uint32_t _rodata_end;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;

// Kernel space
__attribute__((section(".kstack")))
uint32_t _kstack[CONFIG_KSTACK_SIZE];

// Userspace
__attribute__((section(".uheap")))
uint32_t _uheap[CONFIG_UHEAP_SIZE];

_Noreturn
void _loop(void)
{
	for(;;);
}

_Noreturn
void _reset(void)
{
	// Fix Optimize: volatile -> Do not use memcpy!
	volatile uint32_t *src, *dst;

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

