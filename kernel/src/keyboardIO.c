#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "io.h"
#include "pic.h"
#include "terminal.h"

#define MAX_KEY_BUFFER_SIZE 255

void keyboard_processScancode(void);

key_event keyboardBuffer[MAX_KEY_BUFFER_SIZE];
uint8_t bufferPosition = 0;

void keyboard_IRQ_handler()
{
    uint8_t scancode = keyboard_read();

    keyboardBuffer[bufferPosition].code = scancode;
    bufferPosition = (bufferPosition + 1) % MAX_KEY_BUFFER_SIZE;

    keyboard_processScancode();

    PIC_sendEOI(1);
}

void keyboard_processScancode()
{
    terminal_writeString("IRQ Handler Called");
}
