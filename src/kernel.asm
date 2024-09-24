
;; -- GDT START --
[extern gp]
[global gdt_flush]

[bits 32]
gdt_flush:
    lgdt [gp]        
    mov ax, 0x10    
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush
.flush:
    ret
;; -- GDT END --


;; -- INTERRUPTS START --
[extern isr_handler]
[extern irq_handler]

isr_common_stub:
    pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds               ; Lower 16-bits of eax = ds.
    push eax                 ; save the data segment descriptor

    mov ax, 0x10  ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop ebx        ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                     ; Pops edi,esi,ebp...
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    sti
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

irq_common_stub:
    pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds               ; Lower 16-bits of eax = ds.
    push eax                 ; save the data segment descriptor

    mov ax, 0x10  ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call irq_handler

    pop ebx        ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                     ; Pops edi,esi,ebp...
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    sti
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

%macro irq_handler 2
    global irq%1
    irq%1:
        cli
        push byte 0
        push byte %2
        jmp irq_common_stub
%endmacro

%macro isr_handler 1
    global isr%1
    isr%1:
        cli
        push byte 0
        push byte %1
        jmp isr_common_stub
%endmacro

;; -- ISR START --
isr_handler 0
isr_handler 1
isr_handler 2
isr_handler 3
isr_handler 4
isr_handler 5
isr_handler 6
isr_handler 7
isr_handler 8
isr_handler 9
isr_handler 10
isr_handler 11
isr_handler 12
isr_handler 13
isr_handler 14
isr_handler 15
isr_handler 16
isr_handler 17
isr_handler 18
isr_handler 19
isr_handler 20
isr_handler 21
isr_handler 22
isr_handler 23
isr_handler 24
isr_handler 25
isr_handler 26
isr_handler 27
isr_handler 28
isr_handler 29
isr_handler 30
;; -- ISR END --


global isr31
isr31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub

    ;; -- IRQ START --
    irq_handler 0, 32
    irq_handler 1, 33
    irq_handler 2, 34
    irq_handler 3, 35
    irq_handler 4, 36
    irq_handler 5, 37
    irq_handler 6, 38
    irq_handler 7, 39
    irq_handler 8, 40
    irq_handler 9, 41
    irq_handler 10, 42
    irq_handler 11, 43
    irq_handler 12, 44
    irq_handler 13, 45
    irq_handler 14, 46
    irq_handler 15, 47
    ;; - IRQ END --

;; -- INTERRUPTS END --

;; SWITCH-CONTEXT START
[global switch_context]
;; TODO: [extern current_task]


;; C declaration:
;;  void switch_context(void);
;; WARNING: Caller is expected to disable IRQs before calling, and enable IRQs again after function returns
;; TODO: switch_context
switch_context:
    ret


;; SWITCH-CONTEXT END