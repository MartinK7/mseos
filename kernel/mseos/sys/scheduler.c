
#include "configure.h"
#include "sys/scheduler.h"
#include "sys/kheap.h"

typedef struct {
	uint32_t *sp;
	uint32_t pid;
} scheduler_task_t;

static scheduler_task_t *tasks[CONFIG_SCHEDULER_TASKS_MAX_COUNT] = {0};
static scheduler_task_t *task_running = NULL;
static uint32_t ready = 0, pid_counter = 256, task_running_index = 0;

static void switch_task(void)
{
	do {
		task_running_index++;
		if(task_running_index >= CONFIG_SCHEDULER_TASKS_MAX_COUNT)
			task_running_index = 0;
		if(tasks[task_running_index] != NULL) {
			task_running = tasks[task_running_index];
			task_running->sp[8] &= 0xFFFFFFFCUL;
			return;
		}
	} while(1);
}

__attribute__((naked)) void scheduler_switch_task_irq_cb(void)
{
	__asm (
		// [ASSEMBLY CODE]               [NOTE]              [C equivalent pseudo code]
		//
		"cpsid i                  \n" // Disable interrupt   backup_cpu_context();
		"push  {r4-r11}           \n" // Backup r4-r11       ..
		"ldr   r0, =task_running  \n" // r0 = &task_running  task_running->sp = $sp;
		"ldr   r1, [r0]           \n" // r1 = *r0            ..
		"str   sp, [r1]           \n" // sp = *r1            ..
		"push  {r0,lr}            \n" // Backup r0,lr        switch_task();
		"bl    switch_task        \n" // Call scheduler      ..
		"pop   {r0,lr}            \n" // Restore r0,lr       ..
		"ldr   r1, [r0]           \n" // r1 = *r0            $sp = task_running->sp;
		"ldr   sp, [r1]           \n" // sp = *r1            ..
		"pop   {r4-r11}           \n" // Restore r4-r11      restore_cpu_context();
		"cpsie i                  \n" // Enable interrupt    ..
		"bx    lr                 \n" // Exit                return;
	);
}

static void __attribute__((naked)) scheduler_start_asm(void)
{
	__asm (
		// [ASSEMBLY CODE]               [NOTE]              [C equivalent pseudo code]
		//
		"cpsid i                  \n" // Disable interrupt
		"ldr   r0, =ready         \n" //                      ready = 1;
		"mov   r1, #1             \n" //                      ..
		"str   r1, [r0]           \n" //                      ..
		"ldr   r0, =task_running  \n" //                      $sp = task_running->sp;
		"ldr   r1, [r0]           \n" //                      ..
		"ldr   sp, [r1]           \n" //                      ..
		"pop   {r4-r11}           \n" // Restore r4-11
		"pop   {r0-r3}            \n" // Restore r0-r3
		"pop   {r12}              \n" // Restore r12
		"add   sp, sp, #4         \n" // Discard lr
		"pop   {lr}               \n" // Restore ReturnAddress to lr
		"add   sp, sp, #4         \n" // Discard xPSR
		"cpsie i                  \n" // Enable interrupt
		"blx   lr                 \n" //                      $lr($r0); ~ function(data);
		"b     trap               \n" //                      goto trap;

		// Unused debug code
//		"ldr   r0, gpiog          \n" //                      GPIOG->BSRR = GPIO_BSRR_BS13;
//		"ldr   r1, gpiogset       \n" //                      ..
//		"str   r1, [r0]           \n" //                      ..
//		"gpiog:                   \n" //                      const uint32_t gpiog = 0x40021818UL;
//		".word 0x40021818UL       \n" //                      ..
//		"gpiogset:                \n" //                      const uint32_t gpiogset = 0x000002000UL;
//		".word 0x00002000UL       \n" //                      ..
	);
}

#if 0
SP_OFFSET 4byte align / 8byte align
0x24      orig_sp     / untouched
0x20      reserved    / orig_sp
0x1C      xPSR
0x18      RetAddr
0x14      lr
0x10      r12
0x0C      r3
0x08      r2
0x04      r1
0x00      r0  (new sp)
#endif

static void trap(void)
{
	for(;;);
}

void scheduler_start(void)
{
	// Find first thread and execute it!
	task_running = NULL;
	for(uint32_t i = 0;i < CONFIG_SCHEDULER_TASKS_MAX_COUNT; ++i) {
		if(tasks[i] != NULL) {
			task_running = tasks[i];
			task_running_index = i;
			break;
		}
	}
	// Start task
	if(task_running != NULL)
		scheduler_start_asm();
}

uint32_t scheduler_create_task(void (*function)(void *data), void *data, uint32_t stack_size_words)
{
	uint32_t *stack = kheap_alloc(stack_size_words * sizeof(uint32_t));
	if(stack == NULL) {
		return 0;
	}

	scheduler_task_t *t = kheap_alloc(sizeof(scheduler_task_t));
	if(t == NULL) {
		kheap_free(stack);
		return 0;
	}

	t->sp = &stack[stack_size_words - 1];
	t->pid = pid_counter++;

	// Setup initial stack
	// Reserved
	t->sp[  0] = t->pid;     // reserved here sp should ends after everything pop out
	// Saved in interrupt automatically (CPU context)
	t->sp[ -1] = 0x01000000; // xPSR
	t->sp[ -2] = (uint32_t)function; // ReturnAddress
	t->sp[ -3] = (uint32_t)trap; // $lr
	t->sp[ -4] = 0x55aa0012; // $r12
	t->sp[ -5] = 0x55aa0003; // $r3
	t->sp[ -6] = 0x55aa0002; // $r2
	t->sp[ -7] = 0x55aa0001; // $r1
	t->sp[ -8] = (uint32_t)data; // 0x55aa0000; // $r0
	// Saved in interrupt manually
	t->sp[ -9] = 0x55aa0011; // $r11
	t->sp[-10] = 0x55aa0010; // $r10
	t->sp[-11] = 0x55aa0009; // $r9
	t->sp[-12] = 0x55aa0008; // $r8
	t->sp[-13] = 0x55aa0007; // $r7
	t->sp[-14] = 0x55aa0006; // $r6
	t->sp[-15] = 0x55aa0005; // $r5
	t->sp[-16] = 0x55aa0004; // $r4

	t->sp = &t->sp[-16]; // move

	// Register task
	for(uint32_t i = 0; i < CONFIG_SCHEDULER_TASKS_MAX_COUNT; ++i) {
		if(tasks[i] == NULL) {
			tasks[i] = t;
			return pid_counter++;
		}
	}

	return 0;
}

error_t scheduler_kill_task(uint32_t pid)
{
	return ERROR_OUT_OF_MEMORY;
}
