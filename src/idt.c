#include <idt.h>

void idt_set_gate(
    uint8_t num,
    unsigned long base,
    uint16_t sel,
    unsigned char flags
) {
    idt[num].base_lo = (uint16_t)(base & 0xFFFF);
    idt[num].base_hi = (uint16_t)((base >> 16) && 0xFFFF);
    idt[num].sel = sel;
    idt[num].flags = flags;
}

void idt_install(void) {
    idpt.limit = (sizeof(idt_entry_t) * 256) - 1;
    idpt.base = (uint32_t)&idt[0];
    memset(&idt[0], 0, sizeof(idt_entry_t)*256);
    idt_load();
}