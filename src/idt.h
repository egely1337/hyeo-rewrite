#ifndef IDT_H
#define IDT_H
#include <typedefs.h>
#include <string.h>

#define LOW(address) (uint16_t)((address) & 0xFFFF)
#define HIGH(address) (uint16_t)((address) >> 16)

typedef struct
{
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_ptr;

void set_idt_gate(int num, uint32_t handler);
void idt_install(void);
#endif