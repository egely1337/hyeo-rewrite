/*
 *	file: kpanic.c
 *	author: egely1337
 *	purpose: kernel panic function 
 */

#include <hyeo.h>

//TODO: Make a full functionality panic function.
void panic(const char* str1, ...) {
	// print panic code
	terminal_print_string(str1);
	
	// halt cpu
	KERNEL_IDLE() {
		__asm__ __volatile__("hlt");
	}
}