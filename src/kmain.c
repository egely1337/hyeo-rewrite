/*
 *  file: kmain.c
 *  author: egely1337
 *  purpose: kernel entry 
 */

#include <hyeo.h> 

uint8_t terminal_buffer[TEXTMODE_HEIGHT*TEXTMODE_WIDTH*sizeof(textmode_char_t)*2] = {0};

// Literally this routine does nothing
// if this killed, then you must be panik!
static void kernel_idle() {
    while(1) {
        // do nothing
    }
}

// Okay, this is the entry routine of the kernel
// we do some things so our kernel work well
// like setting up descriptors, initialize scheduling, terminal or etc.
int _kentry(multiboot *ebx) {
    terminal_buffer_init(&terminal_buffer[0]);  
    terminal_init();
    gdt_install();
    isr_install();
    timer_init();
    init_scheduling();
    create_process_from_address((uint32_t) kernel_idle, "kidle",  0xC00000);
    sti();
    return 0;
}