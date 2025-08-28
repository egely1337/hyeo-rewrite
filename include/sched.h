#ifndef SCHED_H
#define SCHED_H

#include <typedefs.h>
#include <irq.h>

#define MAX_PROCESS 16

typedef void(*kernel_task_t)();

typedef enum {
	PROCESS_PRIORITY_HIGH, // 1ms
	PROCESS_PRIORITY_MEDIUM, // 2ms
	PROCESS_PRIORITY_LOW // 3ms
} process_priority_t;

typedef  uint32_t pid_t ;
typedef struct {
	// callee saved regs
	uint32_t ebp, edi, esi, ebx;

	// popped by ret in switch context
	uint32_t switch_addr;

	// popped by us in new kernel stack;
	uint32_t data_selector;

	// popped by iret
	uint32_t eip, cs, eflags, usermode_esp, usermode_ss;
} kernel_stack_t;

typedef struct {
	pid_t pid;
	uint32_t kernel_esp;
	char process_name[48];
	uint32_t state;
	uint32_t time_slice;
	process_priority_t priority;
} process_t;


void switch_to_next(void);
void initialize_init(void);
void init_scheduling(void);
void schedule(void);
pid_t allocate_pid(void);
void create_thread_address(kernel_task_t eip, char* proc_name, uint32_t stack_addr, process_priority_t priority);
process_t* get_next_process(void);
HYEO_EXPORT void switch_context(process_t* old, process_t* new);
void new_task_setup(void);
void sched_lock();
void sched_unlock();
#endif