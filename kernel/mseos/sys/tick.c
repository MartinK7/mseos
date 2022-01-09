
#include "tick.h"

volatile static uint32_t system_tick;

void tick_irq_callback_increment(uint32_t delta_ticks)
{
	system_tick += delta_ticks;
}

uint32_t tick_get(void)
{
	return system_tick;
}

int8_t tick_check_timeout(uint32_t start_tick, uint32_t timeout_ticks)
{
	if((system_tick - start_tick) > timeout_ticks) {
		return -1;
	}
	return 0;
}

void tick_delay(uint32_t time_ticks)
{
	uint32_t start = tick_get();
	while(!tick_check_timeout(start, time_ticks));
}
