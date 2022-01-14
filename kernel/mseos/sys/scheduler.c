
#include "scheduler.h"
#include "configure.h"

static scheduler_task_t *tasks[CONFIG_SCHEDULER_TASKS_MAX_COUNT];

void scheduler_switch_task_irq_cb(void)
{
}

uint32_t scheduler_create_task(void (*function)(void *data), void *data, uint32_t stack_size_words)
{
	return 0;
}

error_t scheduler_kill_task(uint32_t pid)
{
	return ERROR_OUT_OF_MEMORY;
}
