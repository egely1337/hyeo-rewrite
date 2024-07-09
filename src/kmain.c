#include <hyeo.h>

uint8_t terminal_buffer[TEXTMODE_HEIGHT*TEXTMODE_WIDTH*sizeof(textmode_char_t)*2] = {0};

int _kentry() {
    gdt_install();
    idt_install();

    terminal_buffer_init(&terminal_buffer[0]);
    terminal_init();
    terminal_print_string("boot up");

    hlt();
    return 0;
}
