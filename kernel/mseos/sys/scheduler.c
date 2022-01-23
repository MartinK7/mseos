
#include "configure.h"
#include "sys/scheduler.h"
#include "sys/kheap.h"
#include "sys/memops.h"

typedef struct scheduler_task {
	uint32_t *sp;
	void *load_at;
	uint32_t pid;
	uint32_t index;
	uint32_t kill_me_flag;
//	void *alloc[CONFIG_SCHEDULER_MAX_ALLOCS];
	// Parent process
	struct scheduler_task *parent_task;
	// Child processes
	struct scheduler_task *child_tasks[CONFIG_SCHEDULER_CHILDTASKS_MAX_COUNT];
} scheduler_task_t;

static uint32_t running_task_index = 0;
struct scheduler_task *tasks[CONFIG_SCHEDULER_TASKS_MAX_COUNT] = {0};
static scheduler_task_t *task_running = NULL;
volatile static uint32_t suspend_cnt = 1;  // After init, scheduler is suspended
static uint32_t pid_counter = 1;

static void kill(scheduler_task_t *task)
{
	// Kill recursive
	for(uint32_t i = 0; i < CONFIG_SCHEDULER_CHILDTASKS_MAX_COUNT; ++i) {
		if(task->child_tasks[i] != NULL)
			kill(task->child_tasks[i]);
	}
	// Free memory
	uint32_t index = task->index;
	kheap_free(task->sp);
	kheap_free(task);
	// Unregister
	if(tasks[index] != task)
		__asm volatile ("b _loop"); // Kernel panic! Bad index!
	tasks[index] = NULL;
}

static int8_t check_kill(scheduler_task_t *task)
{
	if(task->parent_task != NULL)
		if(task->parent_task->kill_me_flag != 0)
			return 0; // Not killed
	if(task->kill_me_flag != 0) {
		kill(task);
		return 1; // Killed
	}
	return 0; // Not killed
}

__attribute__((used)) // Fix Optimize: This function is used in assembly, do not remove
static void switch_task(void)
{
	uint32_t last_task_index = running_task_index;
	running_task_index++;
	do {
		if(last_task_index == running_task_index)
			__asm volatile ("b _loop"); // Kernel panic! No process found!
		if(running_task_index >= CONFIG_SCHEDULER_TASKS_MAX_COUNT)
			running_task_index = 0;
		if(tasks[running_task_index] != NULL) {
			if(check_kill(tasks[running_task_index]) != 0)
				continue;
			task_running = tasks[running_task_index];
			return;
		}
		running_task_index++;
	} while(1);
}

__attribute__((naked))
void scheduler_switch_task_irq_cb(void)
{
	__asm volatile (
		// [ASSEMBLY CODE]               [NOTE]              [C equivalent pseudo code]
		//
		"cpsid i                  \n" // Disable interrupt   __irq_disable();
		"ldr   r0, =suspend_cnt   \n" //                     if(suspend_cnt == 0) return;
		"ldr   r1, [r0]           \n" //                     ..
		"cmp   r1, #0             \n" //                     ..
		"bne   switch_task_exit   \n" //                     ..
		"push  {r4-r11}           \n" // Backup r4-r11       backup_cpu_context();
		"ldr   r0, =task_running  \n" // r0 = &task_running  task_running->sp = $sp;
		"ldr   r1, [r0]           \n" // r1 = *r0            ..
		"str   sp, [r1]           \n" // sp = *r1            ..
		"push  {r0,lr}            \n" // Backup r0,lr        switch_task();
		"bl    switch_task        \n" // Call scheduler      ..
		"pop   {r0,lr}            \n" // Restore r0,lr       ..
		"ldr   r1, [r0]           \n" // r1 = *r0            $sp = task_running->sp;
		"ldr   sp, [r1]           \n" // sp = *r1            ..
		"pop   {r4-r11}           \n" // Restore r4-r11      restore_cpu_context();
		"switch_task_exit:        \n" // Just a label
		"cpsie i                  \n" // Enable interrupt    __irq_enable();
		"bx    lr                 \n" // Exit                return;
	);
}

__attribute__((naked))
static void scheduler_start_asm(void)
{
	__asm volatile (
		// [ASSEMBLY CODE]               [NOTE]              [C equivalent pseudo code]
		//
		"cpsid i                  \n" // Disable interrupt
		"ldr   r0, =suspend_cnt   \n" // $r0 = &suspend_cnt;  if(suspend_cnt != 1) goto _loop; // Kernel panic!
		"ldr   r1, [r0]           \n" // $r1 = *$r0           ..
		"cmp   r1, #1             \n" // cmp($r1,0)           ..
		"bne   _loop              \n" // goto ifne _loop      ..
		"sub   r1, #1             \n" //                      suspend_cnt -= 1;
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
	);
}

_Noreturn
static void trap(void)
{
	scheduler_suspend_all_tasks();
	task_running->kill_me_flag = 1;
	scheduler_resume_all_tasks();
	for(;;);
}

void scheduler_suspend_all_tasks(void)
{
	__asm volatile ("cpsid i"); // Disable interrupt
	if(suspend_cnt == -1)
		__asm volatile ("b _loop"); // Kernel panic!
	suspend_cnt += 1;
	__asm volatile ("cpsie i"); // Enable interrupt
}

void scheduler_resume_all_tasks(void)
{
	__asm volatile ("cpsid i"); // Disable interrupt
	if(suspend_cnt == 0)
		__asm volatile ("b _loop"); // Kernel panic!
	suspend_cnt -= 1;
	__asm volatile ("cpsie i"); // Enable interrupt
}

void scheduler_start(void)
{
	// Find first thread and execute it!
	task_running = NULL;
	for(uint32_t i = 0; i < CONFIG_SCHEDULER_CHILDTASKS_MAX_COUNT; ++i) {
		if(tasks[i] != NULL) {
			task_running = tasks[i];
			running_task_index = i;
			break;
		}
	}
	// Start task
	if(task_running != NULL)
		scheduler_start_asm();
	// Kernel panic, to process found!
	__asm volatile ("b _loop"); // Kernel panic!
}

// Create task under running task (child task)
uint32_t scheduler_create_task(void *load_at, void (*function)(void *data), void *data, uint32_t stack_size_words)
{
	scheduler_suspend_all_tasks();

	// Find empty task slot
	uint32_t register_index = -1, child_index = -1;
	for(uint32_t i = 0; i < CONFIG_SCHEDULER_TASKS_MAX_COUNT; ++i) {
		if(tasks[i] == NULL) {
			register_index = i;
			break;
		}
	}
	if(register_index == -1) {
		scheduler_resume_all_tasks();
		return 0;
	}

	// Find empty child slot in parent task
	if(task_running != NULL) {
		for(uint32_t i = 0; i < CONFIG_SCHEDULER_CHILDTASKS_MAX_COUNT; ++i) {
			if(tasks[i] == NULL) {
				child_index = i;
				break;
			}
		}
		if(child_index == -1) {
			scheduler_resume_all_tasks();
			return 0;
		}
	}

	uint32_t *stack = kheap_alloc(stack_size_words * sizeof(uint32_t));
	if(stack == NULL) {
		scheduler_resume_all_tasks();
		return 0;
	}

	scheduler_task_t *t = kheap_alloc(sizeof(scheduler_task_t));
	memset(t, 0, sizeof(scheduler_task_t));
	if(t == NULL) {
		kheap_free(stack);
		scheduler_resume_all_tasks();
		return 0;
	}

	uint32_t new_pid = pid_counter++;
	if(pid_counter == 0)
			__asm volatile ("b _loop"); // Kernel panic! Out of unique PIDs!

	t->load_at = load_at;
	t->parent_task = task_running;
	t->sp = &stack[stack_size_words - 1];
	t->pid = new_pid;
	t->index = register_index;

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

	// Register task - sub tasks
	if(t->parent_task != NULL) {
		t->parent_task->child_tasks[child_index] = t;
	}

	// Register task - main tasks
	tasks[register_index] = t;

	scheduler_resume_all_tasks();
	return new_pid;
}

error_t scheduler_kill_task(uint32_t pid)
{
	return ERROR_OUT_OF_MEMORY;
}

// Export System Calls:
uint32_t syscall_spawn(void (*function)(void *data), void *data, uint32_t stack_size_words)
{
	scheduler_suspend_all_tasks();
	uint32_t pid = scheduler_create_task(task_running->load_at, (uint32_t)function + task_running->load_at, data, stack_size_words);
	scheduler_resume_all_tasks();
	return pid;
}
