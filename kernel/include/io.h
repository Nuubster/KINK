#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#include <stdint.h>

void outb(unsigned short port, unsigned char data);
void io_wait(void);
unsigned char inb(unsigned short port);

typedef struct {
    uint8_t code;
} key_event;

extern key_event keyboardBuffer[];
extern uint8_t keyboard_read();
extern uint8_t keyboard_readStatus();

void keyboard_IRQ_handler(void);

#endif
