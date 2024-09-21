#include <idt.h>

#define IDT_ENTRIES 256
idt_entry_t idt[IDT_ENTRIES];
idt_ptr idpt;

void set_idt_gate(
    int num,
    uint32_t handler
) {
    idt[num].base_lo = LOW(handler);
    idt[num].base_hi = HIGH(handler);
    idt[num].sel = 0x08;
    idt[num].always0 = 0;
    idt[num].flags = 0x8E;
}

void idt_install(void) {
    idpt.base = (int)&idt;
    idpt.limit = IDT_ENTRIES * sizeof(idt_entry_t) - 1;

    // load idt
    __asm__ __volatile__("lidt %0" : : "m" (idpt));
}