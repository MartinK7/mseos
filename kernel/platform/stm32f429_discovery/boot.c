
extern void main(void);

extern unsigned int _rodata_end;
extern unsigned int _start_data;
extern unsigned int _end_data;
extern unsigned int _start_bss;
extern unsigned int _end_bss;

_Noreturn void _loop(void)
{
	for(;;);
}

_Noreturn void _reset(void)
{
	unsigned int *src, *dst;

	asm volatile ("cpsid i");

	src = &_rodata_end;
	dst = &_start_data;
	while (dst < &_end_data) {
		*dst++ = *src++;
	}

	dst = &_start_bss;
	while (dst < &_end_bss) {
		*dst++ = 0;
	}

	main();
	_loop();
}

