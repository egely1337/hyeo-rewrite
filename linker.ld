OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

ENTRY(_entry)

INPUT(
    dump/kmain.o
    dump/kernel.o
    dump/kpanic.o
	dump/terminal.o
	dump/string.o
	dump/io.o
	dump/gdt.o
	dump/multiboot.o
    dump/idt.o
    dump/irq.o
    dump/timer.o
    dump/sched.o
    dump/reboot.o
    dump/pmm.o
    dump/printf.o
    dump/kalloc.o
    dump/acpi.o
)

OUTPUT(
	iso_root/boot/kernel.elf
)

SECTIONS {
    . = 0x100000;
    KERNEL_START = .;
    .text : ALIGN(0x1000){
		*(.multiboot)
        *(.text)
    }
    .data : ALIGN(0x1000){
        *(.data)
    }
    .rodata : ALIGN(0x1000) {
        *(.rodata)
    }
    .bss : ALIGN(0x1000){
        *(COMMON)
        *(.bss)
    }
    KERNEL_END = .;
}

