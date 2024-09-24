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
    .buffer = (void*)0
};
const size_t TEXTMODE_BYTE_LENGHT = 2*TEXTMODE_WIDTH*TEXTMODE_HEIGHT;


void terminal_init(void) {
    if(terminal.buffer == (void*)0) hlt();

    memset(terminal.buffer, 0, TEXTMODE_BYTE_LENGHT);
    for(int i = 0; i < TEXTMODE_BYTE_LENGHT; i++) {
        textmode_char_t* ch = (textmode_char_t*)terminal.buffer + i;
        ch->ch = ' ';
        ch->color = COLOR_MAGENTA;
    }
}

void terminal_buffer_init(uint8_t *buffer)
{
    memset(buffer, 0, TEXTMODE_BYTE_LENGHT);
    terminal.buffer = buffer;
}

void terminal_print_char(uint8_t ch) {
    switch (ch)
    {
        case '\n':
            terminal.pos.x = 0;
            terminal.pos.y++;
            terminal_advance();
            break;
        default:;
            unsigned char* ptr = (unsigned char*)&terminal.buffer[0] + ((terminal.pos.y * TEXTMODE_WIDTH + terminal.pos.x) * 2);
            textmode_char_t *character = (textmode_char_t*)ptr;
            character->ch = ch;
            character->color = COLOR_MAGENTA;
            terminal_advance();
            break;
    }
}

void terminal_advance(void) {
    if(terminal.pos.x + 1 > TEXTMODE_WIDTH) {
        terminal.pos.x = 0;
        terminal.pos.y++;
    } else terminal.pos.x++;

    terminal_update_cursor();
}

void terminal_cursor_enable(void)
{
    outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
}

void terminal_update(void)
{
    uint8_t* ptr = VGA_ADDR;
    memset(VGA_ADDR, 0, TEXTMODE_BYTE_LENGHT);
    memcpy(VGA_ADDR, terminal.buffer, TEXTMODE_BYTE_LENGHT);
}

void terminal_print_string(const char *str1)
{
    uint8_t* ptr = (uint8_t*)str1;

    while(*ptr != '\0') {
        terminal_print_char(*ptr);
        ptr++;
    }

    terminal_update();
}

void terminal_update_cursor(void)
{
    uint16_t pos = ((terminal.pos.y * TEXTMODE_WIDTH) + terminal.pos.x);
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}
