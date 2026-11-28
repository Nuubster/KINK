#include "interrupt.h"
#include "terminal.h"
#include "io.h"
#include <stddef.h>

void interrupt_dispatch(struct interrupt_frame *frame)
{
    asm volatile("cli");

    if (frame->vector < 32) {
        terminal_writeString("EXCEPTION!!!!!");
        for(;;)
            {   asm volatile("hlt");  }
    }
    else if (frame->vector == 33) {
        terminal_writeString("Called");
        keyboard_IRQ_handler(); 
    }
    else {  terminal_writeString("Meow!");    }
}
