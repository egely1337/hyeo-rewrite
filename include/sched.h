#ifndef SCHED_H
#define SCHED_H

#include <typedefs.h>
#include <isr.h>


#define PROCESS_STATE_IDLE 0x0A
#define PROCESS_STATE_KILLED 0xB8
#define PROCESS_STATE_NULL 0x13
#define PROCESS_STATE_CREATED 0xB1
#define MAX_PROCESS 16

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
	uint32_t eip;
} context_t;

typedef struct {
	context_t regs;	
	char process_name[48];
	pid_t pid;
	uint32_t state;
	uint32_t time_slice;
} process_t;

void init_scheduling(void);
void schedule(void);
pid_t allocate_pid(void);
void create_process_from_address(uint32_t eip, char* proc_name, uint32_t stack_addr);
process_t* get_next_process(void);
HYEO_EXPORT void switch_context(context_t* old, context_t* new);

#endif