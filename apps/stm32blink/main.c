
#include <stdint.h>

static int k;
static int p = 5;
static const int x = 7;
static int qwe[4] = {0};

int32_t main(int32_t argc, char *argv[])
{
	// Here place GPIO INIT
	// ...
	
	for(uint32_t i = 0; i < 64; ++i)
	{
		// SET GPIO
		for(volatile uint32_t k=0;k<10000000;++k);// Stupid delay
		// RESET GPIO
		for(volatile uint32_t k=0;k<10000000;++k);// Stupid delay
	}
	return 0;
}

