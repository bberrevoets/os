//
// isr.c -- High level interrupt service routines and interrupt request handlers.
//

#include "isr.h"
#include "minilib.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
    printf(SERIAL_STREAM, INFO_PRINT, "received interrupt %d\n", regs.int_no);
}
