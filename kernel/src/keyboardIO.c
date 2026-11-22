#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "io.h"
#include "pic.h"

#define MAX_KEY_BUFFER_SIZE 255

key_event keyboardBuffer[MAX_KEY_BUFFER_SIZE];
uint8_t bufferPosition = 0;

void keyboard_IRQ_handler()
{
    uint8_t scancode = keyboard_read();

    keyboardBuffer[bufferPosition].code = scancode;
    bufferPosition = (bufferPosition + 1) % MAX_KEY_BUFFER_SIZE;

    PIC_sendEOI(1);
}
