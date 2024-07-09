OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

ENTRY(_kentry)

INPUT(
	dump/kmain.o
	dump/terminal.o
	dump/string.o
	dump/io.o
	dump/gdt.o
	dump/gdt_load.o
	dump/multiboot.o
    dump/idt_load.o
    dump/idt.o
    dump/panic.o
)

OUTPUT(
	iso_root/boot/kernel.elf
)

SECTIONS {
    . = 0x8000;

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
}

