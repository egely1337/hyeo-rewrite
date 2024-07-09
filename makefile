CC = gcc
AS = nasm
ASFLAGS = -f elf32
CFLAGS = -ffreestanding -m32 -g -c -I ./src
SRCDIR = ./src
OBJDIR = ./dump
SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*.asm) $(wildcard $(SRCDIR)/*.asm) 
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES)) $(patsubst $(SRCDIR)/%.asm,$(OBJDIR)/%.o,$(filter %.asm,$(SOURCES)))
EXECUTABLE = myprogram 
LD=ld

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(LD) -T linker.ld
	grub-mkrescue -o hyeo.iso ./iso_root/

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE)
