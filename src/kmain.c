/*
 *  file: kmain.c
 *  author: egely1337
 *  purpose: kernel entry 
 */

#include <hyeo.h> 

uint8_t terminal_buffer[TEXTMODE_HEIGHT*TEXTMODE_WIDTH*sizeof(textmode_char_t)*2] = {0};

// Okay, this is the entry routine of the kernel
// we do some things so our kernel work well
// like setting up descriptors, initialize scheduling, terminal or etc.
HYEO_STATUS _kentry(
    multiboot* multiboot // boot information header given by grub (ebx register)
) {
    // init terminal
    terminal_buffer_init(&terminal_buffer[0]);  
    terminal_init();

    // init gdt
    gdt_install();

    // init isr
    isr_install();

    // init timer
    timer_init();

    // init scheduling
    init_scheduling();

    // enable interrupts
    sti();

    // kernel idle process
    KERNEL_IDLE() {
        __asm__ __volatile__ ("hlt");
    };
}   