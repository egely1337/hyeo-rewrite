/*
 *  file: io.c
 *  author: egely1337
 *  purpose: in/out inline assembly functions 
 */

#include <io.h>

void outb(uint16_t port, uint8_t data){
    __asm__ volatile("outb %0, %1" : : "a"(data), "Nd"(port));
}

void outw(uint16_t port, uint16_t data){
    __asm__ volatile("outw %0, %1" : : "a"(data), "Nd"(port));
}

uint16_t inw(uint16_t port){
    uint16_t res;
    __asm__ volatile("inw %1, %0" : "=a"(res) : "Nd"(port));
    return res;
}

uint8_t inb(uint16_t port){
    uint8_t res;
    __asm__ volatile("inb %1, %0" : "=a"(res) : "Nd"(port));
    return res;
}