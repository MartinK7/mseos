
#include <stdint.h>
#include "sys/syscall.h"

int main(int argc, char *argv[])
{
	if(argc == 0)
		return -1;
	for(uint32_t i = 0; i < 1024; ++i)
	{
		if(argv[0][0] == '0')
			syscall_open();
		else
			syscall_close();
		for(volatile uint32_t k=0;k<100000;++k);// Stupid delay
		if(argv[0][0] == '0')
			syscall_read();
		else
			syscall_write();
		for(volatile uint32_t k=0;k<100000;++k);// Stupid delay
	}
	return 55;
}

