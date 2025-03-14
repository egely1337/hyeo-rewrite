// !!! IMPORTANT !!!
// REWRITE THIS SHITCODE
// THAT IS COMPLETELY CLUSTERFUCK!
// !!! IMPORTANT !!!

/*
 *  file: terminal.c
 *  author: egely1337
 *  purpose: terminal driver 
 */

#include <terminal.h>

terminal_t terminal = {
    .pos = {
        .x = 0,
        .y = 0
    },
    .color = VGA_COLOR_BROWN,
};

void terminal_print_char(uint8_t ch) {
    switch (ch) {
        case '\n':
            terminal.pos.x = 0;
            terminal.pos.y = terminal.pos.y + 1;
            break;
        default:
            // If rows bigger than max rows, increase columns.
            if(terminal.pos.x + 1 > VGA_ROWS) {
                terminal.pos.x = 0;
                terminal.pos.y = terminal.pos.y + 1;
            }

            // Append char
            terminal.buffer[terminal.pos.y][terminal.pos.x].ch = ch;

            // Advance
            terminal.pos.x = terminal.pos.x + 1;

            break;
    }
}

void terminal_init(void) {
    // Enable cursor
    terminal_cursor_enable();

    // Initialize terminal
    for(int columns = 0; columns < VGA_COLUMNS; columns++) {
        for(int rows = 0; rows < VGA_ROWS; rows++) {
            terminal.buffer[columns][rows].color = terminal.color;
        }
    }
}

void terminal_print_string(const char* str1) {
    uint8_t* ptr = (uint8_t*)str1;

    while(*ptr != '\0') {
        terminal_print_char(*ptr);
        ptr++;
    }

    terminal_flush();
}

void terminal_flush(void) {
    memcpy(VGA_ADDR, terminal.buffer, sizeof(terminal.buffer));
    terminal_update_cursor();
}

void terminal_cursor_enable(void)
{
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
}

void terminal_update_cursor(void)
{
    uint16_t pos = ((terminal.pos.y * VGA_ROWS) + terminal.pos.x);
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}
