/*
 *  file: io.c
 *  author: egely1337
 *  purpose: in/out inline assembly functions 
 */

#include <io.h>

void outb(uint16_t port, uint8_t data){
    asm volatile("outb %0, %1" : : "a"(data), "Nd"(port));
    return;
}

uint8_t inb(uint16_t port){
    uint8_t res;
    asm volatile("inb %1, %0" : "=a"(res) : "Nd"(port));
    return res;
}