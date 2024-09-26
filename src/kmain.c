/*
 *  file: kmain.c
 *  author: egely1337
 *  purpose: kernel entry 
 */

#include <hyeo.h> 

uint8_t terminal_buffer[TEXTMODE_HEIGHT*TEXTMODE_WIDTH*sizeof(textmode_char_t)*2] = {0};


HYEO_STATUS print_hello_world(void) {
    terminal_print_string("print_hello_world() is here!");
    KERNEL_IDLE();
}

// Okay, this is the entry routine of the kernel
// we do some things so our kernel work well
// like setting up descriptors, initializing scheduling, terminal or etc.
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

    // create example process (hardcoded esp 0xc00000)
    create_process_from_address((kernel_task_t)print_hello_world, "task", 0xC00000);

    // enable interrupts
    sti();

    // kernel idle process
    KERNEL_IDLE() {
        __asm__ __volatile__ ("hlt");
    };

    // kernel should reach here.
    return HYEO_OK;
}   