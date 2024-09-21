#ifndef ISR_H
#define ISR_H

#include <typedefs.h>


#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

// irqs end

typedef struct {
   uint32_t ds;
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
   uint32_t int_no, err_code;
   uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed)) registers_t;

typedef void (*IsrHandler)(registers_t);
extern void isr_handler(registers_t);
void isr_install();
void register_interrupt_handler(uint8_t, IsrHandler);
extern void isr_handler(registers_t regs);
extern void irq_handler(registers_t regs);
#endif 