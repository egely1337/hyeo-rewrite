global idt_load
extern idpt

idt_load:
    lidt [idpt]
    ret