#include "panic.h"

void panic(const char *str1, ...)
{
    terminal_print_string(str1);
    hlt();
}