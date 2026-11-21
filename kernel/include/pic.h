#ifndef PIC_H
#define PIC_H

void PIC_sendEOI(uint8_t irq);
void PIC_remap(int offset1, int offset2);

void IRQ_setMask(uint8_t IRQLine);
void IRQ_clearMask(uint8_t IRQLine);

#endif

