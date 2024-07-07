#ifndef PRINT_H
#define PRINT_H

#include <typedefs.h>
#include <io.h>
#include <string.h>

#define VGA_ADDR (void*) 0xB8000
#define TEXTMODE_WIDTH 80
#define TEXTMODE_HEIGHT 50

typedef enum {
    COLOR_GREEN = 0x2,
    COLOR_CYAN = 0x3,
    COLOR_RED = 0x4,
    COLOR_MAGENTA = 0x5,
    COLOR_BROWN = 0x6,
    COLOR_LIGHTGRAY = 0x7
} textmode_colors_e;

typedef struct {
    uint8_t ch;
    uint8_t color;
} __attribute__((packed)) textmode_char_t;

typedef struct 
{
    int x,y;
} __attribute__((packed)) terminal_vec2;

typedef struct {
    terminal_vec2 pos;

    // * I know this is a mess, but believe me i am really fucking lazy.
    char buffer[TEXTMODE_HEIGHT * TEXTMODE_WIDTH * sizeof(textmode_char_t)];
} __attribute__((packed)) terminal_t;

void terminal_init(void);
void terminal_update(void);
void terminal_print_char(uint8_t ch);
void terminal_print_string(const char* str1);
void terminal_advance(void);
void terminal_cursor_enable(void);
void terminal_cursor_disable(void);
void terminal_update_cursor(void);

#endif