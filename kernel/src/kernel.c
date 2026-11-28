#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "io.h"
#include "terminal.h"
#include "conf.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "ps2.h"

// Scancode port: 0x60; Status port: 0x64
uint8_t keyboard_read(void);
uint8_t keyboard_readStatus(void);

char ScancodeToChar[256] = {'\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 'B', '0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 
    'o', 'p', '[', ']', '\n', 'c', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', '\0', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', 
    '/', '\0', '\0', ' ', '\0'};

void kernel_main(void)
{
    asm volatile ("cli"); //disable interrupts

    GDT_init();
    IDT_init();

    PIC_remap(0x20, 0x28);

    outb(0x21, 0xFF); // MasterPIC_Data
    outb(0xA1, 0xFF); // SlavePIC_Data
    
    PS2_init();

    IRQ_clearMask(1); // Unmasks the keyboard IRQ port

    terminal_initialize();

    asm volatile ("sti");

    bool ShiftPressed = false;
    bool ShiftReleased = true;

    terminal_writeString("HelloWorld(Console.WriteLine)\n");
    terminal_writeString("THIS IS NOT A KIRNIL\n");
    terminal_writeString("1234\n");

/* A divide-by-zero error call
    int a = 1;
    int b = 0;
    asm volatile (
            "divl %%ebx"
            :
            : "a"(a), "b"(b)
            : "edx"
            );
*/
}
