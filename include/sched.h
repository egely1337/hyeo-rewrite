#ifndef SCHED_H
#define SCHED_H

#include <typedefs.h>
#include <isr.h>

typedef  uint32_t pid_t ;
typedef struct {
	uint32_t eax;
	uint32_t ecx;
	uint32_t edx;
	uint32_t ebx;
	uint32_t esp;
	uint32_t ebp;
	uint32_t esi;
	uint32_t edi;
	uint32_t eflags;
	uint32_t cr3;
	uint32_t eip;
} context_t;

typedef struct {
	char process_name[512];
	context_t regs;
	pid_t pid;
	void* stack;
	uint32_t state;
	uint32_t time_slice;
} process_t;

HYEO_EXPORT process_t* current_proc;
HYEO_EXPORT registers_t saved_context;

void schedule(void);
pid_t allocate_pid(void);
void create_process_routine(void* routine, char* name);
void kernel_regs_switch(void);

#endif