#ifndef SCHED_H
#define SCHED_H

#include <typedefs.h>
#include <isr.h>

#define MAX_PROCESS 16

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
} process_t;


void initialize_init(void);
void init_scheduling(void);
void schedule(void);
pid_t allocate_pid(void);
void create_process_from_address(uint32_t eip, char* proc_name, uint32_t stack_addr);
process_t* get_next_process(void);
HYEO_EXPORT void switch_context(process_t* old, process_t* new); 
void new_task_setup(void);
#endif