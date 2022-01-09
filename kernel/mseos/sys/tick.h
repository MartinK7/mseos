
#ifndef MSEOS_TICK_H
#define MSEOS_TICK_H

#include "sys/types.h"

void tick_irq_callback_increment(uint32_t delta_ticks);
uint32_t tick_get(void);
int8_t tick_check_timeout(uint32_t start_tick, uint32_t timeout_ticks);
void tick_delay(uint32_t time_ticks);

#endif //MSEOS_TICK_H
