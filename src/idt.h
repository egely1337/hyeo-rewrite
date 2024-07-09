#ifndef IDT_H
#define IDT_H
#include <typedefs.h>
#include <string.h>
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

idt_entry_t idt[256];
idt_ptr idpt;


void idt_set_gate( uint8_t num, unsigned long base, uint16_t sel, unsigned char flags);
void idt_install(void);
extern void idt_load(void);
#endif