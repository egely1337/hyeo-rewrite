// file: kmain.c
// author: egely1337
// hyeo entry strategy:
// --------------------------------
// 1. Disable interrupts
// 2. Initialize terminal
// 3. Initialize gdt
// 4. Initialize interrupts
// 5. Initialize irqs
// 6. Enable interrupts
// 7. TODO: Initialize PMM and VMM  
// 8. TODO: Initialize file system
// 9. TODO: Initialize scheduling        
// --------------------------------

#include <hyeo.h> 

uint8_t terminal_buffer[TEXTMODE_HEIGHT*TEXTMODE_WIDTH*sizeof(textmode_char_t)*2] = {0};

int _kentry() {
    cli();
    terminal_buffer_init(&terminal_buffer[0]);  
    gdt_install();
    isr_install();
    //TODO: init_timer();
    sti();
    hlt();
    return 0;
}