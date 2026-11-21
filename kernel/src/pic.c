#include <stdint.h>
#include "io.h"

#define MasterPIC           0x20
#define SlavePIC            0xA0
#define MasterPIC_Command   MasterPIC
#define MasterPIC_Data      0x21
#define SlavePIC_Command    SlavePIC
#define SlavePIC_Data       0xA1
#define PIC_EOI             0x20

// ICW - Initialization Command Words
#define ICW1_ICW4       0x01    // Indicates that ICW4 will be present
#define ICW1_SINGLE     0x02    // Single mode
#define ICW1_INTERVAL4  0x04    // Call address interval 4
#define ICW1_LEVEL      0x08    // Level triggered mode
#define ICW1_INIT       0x10    // Initialization
                                
#define ICW4_8086       0x01    // 8086 mode
#define ICW4_AUTO       0x02    // Auto EOI
#define ICW4_BUF_SLAVE  0x08    // Buffered mode S
#define ICW4_BUF_MASTER 0x0C    // Buffered mode M
#define ICW4_SFNM       0x10    // Special fullynested (not) [?]

#define CASCADE_IRQ     2

void PIC_sendEOI(uint8_t irq)
{
    if (irq >= 8)
        outb(SlavePIC_Command, PIC_EOI);

    outb(MasterPIC_Command, PIC_EOI);
}

void PIC_remap(int offset1, int offset2)
{
    outb(MasterPIC_Command, ICW1_INIT | ICW1_ICW4);
    io_wait(); 
    outb(SlavePIC_Command, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(MasterPIC_Data, offset1);
    io_wait();
    outb(SlavePIC_Data, offset2);
    io_wait();
    outb(MasterPIC_Data, 1 << CASCADE_IRQ);
    io_wait();
    outb(SlavePIC_Data, CASCADE_IRQ);

    outb(MasterPIC_Data, ICW4_8086);
    outb(SlavePIC_Data, ICW4_8086);

    /* Unmask both PICs 
    outb(MasterPIC_Data, 0);
    outb(SlavePIC_Data, 0);
    */
}

void IRQ_setMask(uint8_t IRQLine)
{
    uint16_t port;
    uint8_t value;

    if (IRQLine < 8) { port = MasterPIC_Data; }
    else { port = SlavePIC_Data; IRQLine -= 8; }

    value = inb(port) | (1 << IRQLine);
    outb(port, value);
}

void IRQ_clearMask(uint8_t IRQLine)
{
    uint16_t port;
    uint8_t value;

    if (IRQLine < 8) { port = MasterPIC_Data; }
    else { port = SlavePIC_Data; IRQLine -= 8; }

    value = inb(port) & ~(1 << IRQLine);
    outb(port, value);
}
