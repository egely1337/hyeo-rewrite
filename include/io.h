#ifndef IO_H
#define IO_H
#include <typedefs.h>
uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
uint16_t inw(uint16_t port);
void outw(uint16_t port, uint16_t data);
__FORCEINLINE__ void io_wait(void) {
    outb(0x80, 0);
}
#endif