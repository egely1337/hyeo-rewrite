/*
 *  file: sched.c
 *  author: egely1337
 *  purpose: scheduling 
 */

#include <sched.h>
#include <string.h>
#include <kpanic.h>


// We use this for initializing init process.
const char *init_process_name = "init";


// I know this a easy way to do a scheduling,
// but i didn't even implemented a memory manager.
// so i have to use this easy and cheap method
process_t processes[MAX_PROCESS] = {0};

// Current process so our scheduler can know why we are scheduling process
process_t* current_proc = null;

// Total process number
pid_t process_num = 0;


/*
 *	author: egely1337
 *	purpose: this is the initialize function of scheduling
 *	params: no params
 */
void init_scheduling() {
	memset(&processes[0], 0, sizeof processes * MAX_PROCESS);
	initialize_init();
}


/*
 *	author: egely1337
 *	purpose: initializes kernel init process
 *	params: no params
 */
void initialize_init() {
	// allocate new process
	pid_t init_pid = allocate_pid();
	current_proc = &processes[init_pid];
	
	// set up
	current_proc->pid = init_pid;
	memcpy(current_proc->process_name, (void*)init_process_name, strlen(init_process_name));
	current_proc->process_name[strlen(init_process_name)] = '\0';
}

/*
 *	author: egely1337
 *	purpose: allocates a process id usually for a new process
 *	params: no params
 *  returns: pid_t
 */
pid_t allocate_pid() {
	process_num++;
	if(process_num > MAX_PROCESS) {
		panic("Too many processes created.\n");
	}
	return process_num;
}

/*
 *	author: egely1337
 *	purpose: returns next process to schedule
 *	param: @eip 
 */
void create_process_from_address(kernel_task_t eip, char* proc_name, uint32_t stack_addr) {
	// allocate process id for new process
	pid_t pid = allocate_pid();
	process_t* process = &processes[pid];

	// set up process name
	process->pid = pid;
	
	// set up kernel stack
	uint8_t* kernel_esp = (uint8_t*)stack_addr;
	kernel_esp -= sizeof(kernel_stack_t);
	kernel_stack_t* kernel_stack = (kernel_stack_t*)kernel_esp;

	// initialize kernel stack registers
	kernel_stack->ebp = kernel_stack->edi = kernel_stack->esi = kernel_stack->ebx = 0;
	kernel_stack->data_selector = 0x10;
	kernel_stack->switch_addr = (uint32_t)new_task_setup;
	kernel_stack->eip = (uint32_t)eip;
	kernel_stack->cs = 0x08;
	kernel_stack->eflags = 0x200; // enable interrupts

	// set process kernel stack
	process->kernel_esp = (uint32_t)kernel_esp;
}

/*
 *	author: egely1337
 *	purpose: this is the main schedule function called by timer handler every interrupt
 *	params: no params
 */
void schedule() {
	process_t* old = current_proc;
	process_t* next = get_next_process();
	current_proc = next; 
	switch_context(old, next);
}

/*
 *	author: egely1337
 *	purpose: returns next process to schedule
 *	params: no params
 */
process_t* get_next_process() {
	// Check current pid if pid + 1 greater than total process count
	// if yes, start the loop from first element
	if(current_proc->pid + 1 > process_num) {
		return &processes[1];
	}

	// Else, return next process to content switch
	// :-)
	return &processes[current_proc->pid+1];
}