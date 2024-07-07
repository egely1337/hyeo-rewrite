OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

ENTRY(_main)

INPUT(
	dump/kmain.o
	dump/terminal.o
	dump/string.o
	dump/io.o
	dump/gdt.o
	dump/gdt_asm.o
	dump/multiboot.o
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

