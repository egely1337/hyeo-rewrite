#ifndef TERMINAL_H
#define TERMINAL_H

#include <typedefs.h>
#include <string.h>
#include <io.h>

#define VGA_ADDR (void*) 0xB8000
#define VGA_ROWS 80
#define VGA_COLUMNS 50
#define MAX_CHAR_ON_SCREEN 4000
#define VGA_BYTE_LENGHT 0x1f40
#define TERMINAL_CHECK_MAX(expected) (expected >= MAX_CHAR_ON_SCREEN) ? true : false

typedef enum {
    VGA_COLOR_GREEN = 0x2,
    VGA_COLOR_CYAN = 0x3,
    VGA_COLOR_RED = 0x4,
    VGA_COLOR_MAGENTA = 0x5,
    VGA_COLOR_BROWN = 0x6,
    VGA_COLOR_LIGHTGRAY = 0x7
} textmode_colors_e;

typedef struct {
    uint8_t ch;
    uint8_t color;
} __attribute__((packed)) vga_char_t;

typedef struct 
{
    int x,y;
} __attribute__((packed)) terminal_vec2;

typedef struct {
    // Terminal position
    terminal_vec2 pos;

    // Buffer
    vga_char_t buffer[VGA_COLUMNS][VGA_ROWS];

    // Text color
    textmode_colors_e color;
} __attribute__((packed)) terminal_t;

void terminal_print_string(const char* str);
void terminal_init(void);
void terminal_print_char(uint8_t ch);
void terminal_flush(void);
void terminal_advance(void);
void terminal_cursor_enable(void);
void terminal_cursor_disable(void);
void terminal_update_cursor(void);
void printf(const char* b1, ...);

#endif