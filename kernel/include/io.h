#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#include <stdint.h>

void outb(unsigned short port, unsigned char data);
void io_wait(void);
unsigned char inb(unsigned short port);

#endif
