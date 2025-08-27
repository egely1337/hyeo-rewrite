CC = gcc
AS = nasm
ASFLAGS = -f elf32
SRCDIR = src
OBJDIR = dump
INCLUDEDIR = include/
CFLAGS = -ffreestanding -D DEBUG -std=c99 -m32 -g -Ttext 0x8000 -c -I $(INCLUDEDIR)
SOURCES = $(shell find -w)
SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/*.asm) $(wildcard $(SRCDIR)/*.asm) 
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES)) $(patsubst $(SRCDIR)/%.asm,$(OBJDIR)/%.o,$(filter %.asm,$(SOURCES)))
EXECUTABLE = hyeo.iso 
LD=ld

all: $(EXECUTABLE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC	$@"

$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	@$(AS) $(ASFLAGS) $< -o $@
	@echo "AS 	$@"

$(EXECUTABLE): $(OBJECTS)
	@$(LD) -T linker.ld
	@echo "LD 	$@"
	@grub-mkrescue -o $@ ./iso_root/
	@echo "MKRESCUE 	$@"

.PHONY = clean
clean:
	rm -f $(OBJDIR)/*.o $(EXECUTABLE)