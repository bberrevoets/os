#include "serialwriter.h"
#include "io.h"
/*
Divisor Latch Byte Values(common baud rates)
    Baud Rate   | Divisor Latch High Byte   | Divisor Latch Low Byte
    50              $09                         $00
    110             $04                         $17
    220             $02                         $0C
    300             $01                         $80
    600             $00                         $C0
    1200            $00                         $60
    2400            $00                         $30
    4800            $00                         $18
    9600            $00                         $0C
    19200           $00                         $06
    38400           $00                         $03
    57600           $00                         $02
    115200          $00                         $01
*/

void sw_init(void)
{
    outb(PORT + 1, 0x00); // Disable all interrupts
    outb(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(PORT + 0, 0x01); // Set divisor to 1 (lo byte) 115200 baud
    outb(PORT + 1, 0x00); //                  (hi byte)
    outb(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

int is_transmit_empty()
{
    return inb(PORT + 5) & 0x20;
}

void sw_put(char c)
{
    while (is_transmit_empty() == 0)
        ;
    outb(PORT, c);
}

void sw_write(char *c)
{
    int i = 0;
    while (c[i])
    {
        sw_put(c[i++]);
    }
}

void sw_write_hex(unsigned int n)
{
    int tmp;

    sw_write("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }

        if (tmp >= 0xA)
        {
            noZeroes = 0;
            sw_put(tmp - 0xA + 'a');
        }
        else
        {
            noZeroes = 0;
            sw_put(tmp + '0');
        }
    }

    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        sw_put(tmp - 0xA + 'a');
    }
    else
    {
        sw_put(tmp + '0');
    }
}

void sw_write_dec(unsigned int n)
{
    if (n == 0)
    {
        sw_put('0');
        return;
    }

    int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc % 10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while (i >= 0)
    {
        c2[i--] = c[j++];
    }
    sw_write(c2);
}
