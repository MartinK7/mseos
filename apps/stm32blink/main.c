
#include "sys/types.h"
#include "sys/syscall.h"

void _start(void *data)
{
	uint32_t data_u32 = (uint32_t)data;
	for(uint32_t i = 0; i < 32 + 32 * data_u32; ++i)
	{
		if(data_u32 == 0)
			syscall_open();
		else
			syscall_close();
		for(volatile uint32_t k=0;k<100000;++k);// Stupid delay
		if(data_u32 == 0)
			syscall_read();
		else
			syscall_write();
		for(volatile uint32_t k=0;k<100000;++k);// Stupid delay
	}
}
