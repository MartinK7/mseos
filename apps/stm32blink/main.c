
#include "sys/types.h"
#include "sys/syscall.h"

void _start(void *data)
{
	uint32_t data_u32 = (uint32_t)data;

	for(uint32_t i = 0; i < 32 + 32 * data_u32; ++i)
	{
		if(data_u32 == 0) {
			volatile uint32_t test = syscall_open(0x11, 0x12, 0x13, 0x14);
			(void)test;
		}
		else
			syscall_close(0x21, 0x22, 0x23, 0x24);
		for(volatile uint32_t k=0;k<100000+100000*data_u32;++k);// Stupid delay
		if(data_u32 == 0)
			syscall_read(0x31, 0x32, 0x33, 0x34);
		else
			syscall_write(0x11, 0x12, 0x13, 0x44);
		for(volatile uint32_t k=0;k<100000+100000*data_u32;++k);// Stupid delay
	}
}
