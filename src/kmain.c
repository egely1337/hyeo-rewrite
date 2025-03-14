/*
 *  file: kmain.c
 *  author: egely1337
 *  purpose: kernel entry 
 */

#include <hyeo.h> 

// Okay, this is the entry routine of the kernel
// we do some things so our kernel work well
// like setting up descriptors, initializing scheduling, terminal or etc.
HYEO_STATUS _kentry(
    multiboot* multiboot // Boot information header given by grub (ebx register)
) { 
    // Init gdt
    gdt_install();

    // Init isr
    isr_install();

    // Init timer
    timer_init();

    // Init scheduling
    init_scheduling();

    // Enable interrupts
    sti();

    // Init terminal 
    terminal_init();

    // Kernel idle process
    KERNEL_IDLE();

    // Kernel should NOT reach here.
    return HYEO_OK;
}
