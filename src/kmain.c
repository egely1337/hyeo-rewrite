#include <hyeo.h>

int _main() {
    gdt_install();
    terminal_init();
    terminal_print_string("Hello, World!\n");

    hlt();
    return 0;
}
