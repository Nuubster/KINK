#include <stdint.h>
#include "io.h"

void PS2_init()
{
    outb(0x64, 0x20);
    while (!(keyboard_readStatus() & 0x1));

    uint8_t commandByte = keyboard_read();

    commandByte |= 0x01;    // enable IRQ1
    commandByte &= ~0x10;    // enable first PS/2 port's clock
                            
    while (keyboard_readStatus() & 0x2);
    outb(0x64, 0x60);

    while (keyboard_readStatus() & 0x2);
    outb(0x60, commandByte);

    while (keyboard_readStatus() & 0x2);
    outb(0x64, 0xAE);
}
