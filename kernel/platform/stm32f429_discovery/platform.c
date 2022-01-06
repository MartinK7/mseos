
#include "stm32f4xx.h"

void platform_init(void)
{
	// Enable FPU (set CP10 and CP11 Full Access)
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
}

void platform_register(void)
{
}

