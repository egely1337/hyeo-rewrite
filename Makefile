CC = gcc
AS = nasm
ASFLAGS = -f elf32
SRCDIR = src/
OBJDIR = dump/
INCLUDEDIR = include/
CFLAGS = -ffreestanding -m32 -g -Ttext 0x8000 -c -I $(INCLUDEDIR)
SOURCES = $(shell find -w)
SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*.asm) $(wildcard $(SRCDIR)/*.asm) 
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES)) $(patsubst $(SRCDIR)/%.asm,$(OBJDIR)/%.o,$(filter %.asm,$(SOURCES)))
EXECUTABLE = myprogram 
LD=ld

all: $(EXECUTABLE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(LD) -T linker.ld
	grub2-mkrescue -o hyeo.iso ./iso_root/

clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE)
