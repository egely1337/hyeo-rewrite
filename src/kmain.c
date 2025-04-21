/*
 *  file: kmain.c
 *  author: egely1337
 *  purpose: kernel entry 
 */

#include <hyeo.h> 


extern int KERNEL_END;

// Okay, this is the entry routine of the kernel
// we do some things so our kernel work well
// like setting up descriptors, initializing scheduling, terminal or etc.
HYEO_STATUS _kentry(
    multiboot* multiboot // Boot information header given by grub (ebx register)
) { 
    // Init terminal 
    terminal_init();

    // Init Gdt
    gdt_install();

    // Init Isr
    isr_install();

    // Initialize PMM (hardcoded to mmap_addr + 4KiB)
    initalize_pmm(KERNEL_END, (uint32_t)(multiboot->mem_lower | multiboot->mem_upper));

    // Init timer
    timer_init();

    // Init scheduling
    init_scheduling();

    // Enable interrupts
    sti();

    // Kernel idle process
    KERNEL_IDLE();

    // Kernel should NOT reach here.
    return HYEO_OK;
}
