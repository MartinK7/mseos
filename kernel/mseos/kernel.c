
#include "sys/types.h"
#include "sys/scheduler.h"

void kernel_init(void)
{
}

void kernel_start(void)
{
	scheduler_start();
}
