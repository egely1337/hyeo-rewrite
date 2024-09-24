/*
 *  file: kmain.c
 *  author: egely1337
 *  purpose: kernel entry 
 */

#include <hyeo.h> 

uint8_t terminal_buffer[TEXTMODE_HEIGHT*TEXTMODE_WIDTH*sizeof(textmode_char_t)*2] = {0};

int _kentry(multiboot *ebx) {
    cli();
    terminal_buffer_init(&terminal_buffer[0]);  
    gdt_install();
    isr_install();
    timer_init();
    sti();
    hlt();
    return 0;
}