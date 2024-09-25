/*
 *  file: sched.c
 *  author: egely1337
 *  purpose: scheduling 
 */

#include <sched.h>
#include <string.h>
#include <terminal.h>


// I know this a easy way to do a scheduling,
// but i didn't even implemented a memory manager.
// so i have to use this easy and cheap method
process_t processes[MAX_PROCESS] = {0};

// Current process so our scheduler can know why we are scheduling process
process_t* current_proc = null;

// Total process number
pid_t process_num = 0;

void init_scheduling() {
	memset(&processes[0], 0, sizeof processes);
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
		//TODO: give a panic if too many processes are created.
	}
	return process_num;
}

/*
 *	author: egely1337
 *	purpose: returns next process to schedule
 *	param: @eip 
 */
void create_process_from_address(uint32_t eip, char* proc_name, uint32_t stack_addr) {
	pid_t pid = allocate_pid();
	process_t* process = &processes[pid];

	// hardcoded stack addr u know =)
	process->pid = pid;

	// setup process name
	memcpy(process->process_name, proc_name, 48);
	process->process_name[47] = '\0';
	
	process->regs.eip = (uint32_t)eip;
	process->regs.esp = (uint32_t)stack_addr;
	process->regs.eax = process->regs.ebx = process->regs.edx = process->regs.ecx = process->regs.edi = process->regs.esi = 0;

	// make current process if there is non
	if(!current_proc) {
		current_proc = process;
	}
}

/*
 *	author: egely1337
 *	purpose: this is the main schedule function called by timer handler every interrupt
 *	params: no params
 */
void schedule() {
	process_t* next = get_next_process();
	process_t* old = current_proc;
	current_proc = next; 
	switch_context(&old->regs, &next->regs);
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