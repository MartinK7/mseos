
#include <stdint.h>

#include "stm32f429xx.h"

int main(int argc, char *argv[])
{
	for(uint32_t i = 0; i < 8; ++i)
	{
		GPIOG->BSRR = GPIO_BSRR_BS13 | GPIO_BRR_BR14;
		for(volatile uint32_t k=0;k<100000;++k);// Stupid delay
		GPIOG->BSRR = GPIO_BSRR_BR13 | GPIO_BSRR_BS14;
		for(volatile uint32_t k=0;k<100000;++k);// Stupid delay
	}
	return 0;
}

