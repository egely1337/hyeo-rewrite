/*
 *	file: kpanic.c
 *	author: egely1337
 *	purpose: kernel panic function 
 */

#include <hyeo.h>

//TODO: Make a full functionality panic function.
void panic(const char* str1, ...) {
	terminal_print_string(str1);
	hlt();
}