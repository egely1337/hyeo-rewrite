/*
 *	file: kpanic.c
 *	author: egely1337
 *	purpose: kernel panic function 
 */

#include <hyeo.h>
void panic(const char* str1, ...) {
	hlt();
}