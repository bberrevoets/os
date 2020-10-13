// keyboard.c -- Initialises the PIT, and handles keyboard interrupts.

#include "keyboard.h"
#include "isr.h"
#include "minilib.h"

static void keyboard_callback(registers_t regs)
{
    key = inb(0x60);
}

void init_keyboard()
{
    // Firstly, register our timer callback.
    register_interrupt_handler(IRQ1, &keyboard_callback);
}
