#include <io.h>

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ ("inb %w1, %b0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void outb(uint16_t port, uint8_t val) {
        asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

