
#ifndef MSEOS_SCHEDULER_H
#define MSEOS_SCHEDULER_H

#include "sys/types.h"

typedef struct {

} scheduler_task_t;

void scheduler_switch_task_irq_cb(void);

// Returns PID
uint32_t scheduler_create_task(void (*function)(void *data), void *data, uint32_t stack_size_words);
error_t scheduler_kill_task(uint32_t pid);

#endif //MSEOS_SCHEDULER_H
