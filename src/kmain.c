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
    /* Disable Interrupts */
    cli();

    // Initialize kernel.
    gdt_install();
    isr_install(); 
    terminal_init();
    initalize_pmm(multiboot);
    acpi_init();
    timer_init();

    /* Enable interrupts */
    sti();

    // Kernel Idle task
    KERNEL_IDLE() {
        __asm__("hlt");
    }

    // Kernel should NOT reach here.
    return HYEO_OK;
}
