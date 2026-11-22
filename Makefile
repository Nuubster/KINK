CC	= i686-elf-gcc
CFLAGS	= -std=gnu99 -ffreestanding -O2 -Wall -Wextra -Ikernel/include
OBJECTS = boot.o kernel.o keyboard.o keyboardIO.o cursor.o io.o terminal.o gdt.o gdt_flush.o interrupt.o idt.o idt_macro.o pic.o

build: KINK

boot.o: kernel/arch/i386/boot.s
	$(CC) -c kernel/arch/i386/boot.s -o boot.o

gdt_flush.o: kernel/arch/i386/gdt_flush.S
	$(CC) -c kernel/arch/i386/gdt_flush.S -o gdt_flush.o

idt_macro.o: kernel/arch/i386/idt_macro.S
	$(CC) -c kernel/arch/i386/idt_macro.S -o idt_macro.o

kernel.o: kernel/src/kernel.c
	$(CC) $(CFLAGS) -c kernel/src/kernel.c -o kernel.o 

terminal.o: kernel/src/terminal.c
	$(CC) $(CFLAGS) -c kernel/src/terminal.c -o terminal.o

cursor.o: kernel/src/cursor.c
	$(CC) $(CFLAGS) -c kernel/src/cursor.c -o cursor.o

gdt.o: kernel/src/gdt.c
	$(CC) $(CFLAGS) -c kernel/src/gdt.c -o gdt.o

keyboardIO.o: kernel/src/keyboardIO.c
	$(CC) $(CFLAGS) -c kernel/src/keyboardIO.c -o keyboardIO.o

interrupt.o: kernel/src/interrupt.c
	$(CC) $(CFLAGS) -c kernel/src/interrupt.c -o interrupt.o

idt.o: kernel/src/idt.c
	$(CC) $(CFLAGS) -c kernel/src/idt.c -o idt.o

pic.o: kernel/src/pic.c
	$(CC) $(CFLAGS) -c kernel/src/pic.c -o pic.o

keyboard.o: kernel/drivers/keyboard.S
	$(CC) -c kernel/drivers/keyboard.S -o keyboard.o

io.o: kernel/drivers/io.s
	$(CC) -c kernel/drivers/io.s -o io.o

KINK: $(OBJECTS)
	$(CC) -T kernel/arch/i386/linker.ld -o KINK -ffreestanding -O2 -nostdlib $(OBJECTS) -lgcc

run :
	qemu-system-i386 -kernel KINK

clean:
	rm -f *.o KINK

