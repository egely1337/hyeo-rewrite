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
    /* TODO: Parse multiboot. */
    //...

    // Initialize kernel.
    gdt_install();
    isr_install(); 
    terminal_init();
    acpi_init();
    parse_mmap(multiboot);
    initalize_pmm(multiboot->mmap_addr + 0x1000, (uint32_t)(multiboot->mem_lower + multiboot->mem_upper));
    init_scheduling();
    timer_init();

    #ifdef DEBUG
    printf("Hello, World! %x  %x", 0x1337, 0x1337);
    #endif

    // Enable interrupts
    sti();

    // Kernel should NOT reach here.
    return HYEO_OK;
}
