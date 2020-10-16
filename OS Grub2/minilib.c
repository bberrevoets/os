/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: B.N. Berrevoets <bert@berrevoets.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:34:12 by B.N. Berrev       #+#    #+#             */
/*   Updated: 2020/10/17 00:34:12 by B.N. Berrev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilib.h"

void itoa(char *buf, int base, int d)
{
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    /* If %d is specified and D is minus, put `-' in the head.  */
    if (base == 'd' && d < 0)
    {
        *p++ = '-';
        buf++;
        ud = -d;
    }
    else if (base == 'x')
        divisor = 16;

    /* Divide UD by DIVISOR until UD == 0.  */
    do
    {
        int remainder = ud % divisor;

        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (ud /= divisor);

    /* Terminate BUF.  */
    *p = 0;

    /* Reverse BUF.  */
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

void *memset(void *dest, int ch, unsigned int size)
{
    char *cdest = (char *)dest;
    char cch = (char)ch;
    while (size--)
    {
        *cdest = cch;
        cdest++;
    }
    return dest;
}

void *memcpy(void *dest, void *src, unsigned int size)
{
    char *cdest = (char *)dest;
    char *csrc = (char *)src;
    if (csrc == cdest || !size)
        ;
    else
    {
        if (cdest > csrc && cdest < (csrc + size))
        { /* L to R */
            cdest += size - 1;
            csrc += size - 1;
            while (size--)
            {
                *cdest = *csrc;
                cdest--;
                csrc--;
            }
        }
        else
        { /* R to L */
            while (size--)
            {
                *cdest = *csrc;
                cdest++;
                csrc++;
            }
        }
    }
    return dest;
}

void printf(int stream, int label, const char *format, ...)
{
    unsigned char old_fg = fg;
    switch (label)
    {
    case DEBUG_PRINT:
        if (stream == SCREEN_STREAM)
        {
            fb_set_color(FB_LIGHT_BLUE, bg);
            fb_write("[DEBUG] ");
            fb_set_color(old_fg, bg);
        }
        else if (stream == SERIAL_STREAM)
        {
            sw_write("[DEBUG] ");
        }
        else if (stream == BOTH_STREAM)
        {
            fb_set_color(FB_LIGHT_BLUE, bg);
            fb_write("[DEBUG] ");
            fb_set_color(old_fg, bg);
            sw_write("[DEBUG] ");
        }

        break;
    case INFO_PRINT:
        if (stream == SCREEN_STREAM)
        {
            fb_set_color(FB_LIGHT_GREEN, bg);
            fb_write("[INFO] ");
            fb_set_color(old_fg, bg);
        }
        else if (stream == SERIAL_STREAM)
        {
            sw_write("[INFO] ");
        }
        else if (stream == BOTH_STREAM)
        {
            fb_set_color(FB_LIGHT_GREEN, bg);
            fb_write("[INFO] ");
            fb_set_color(old_fg, bg);
            sw_write("[INFO] ");
        }
        break;
    case ERROR_PRINT:
        if (stream == SCREEN_STREAM)
        {
            fb_set_color(FB_RED, bg);
            fb_write("[ERROR] ");
            fb_set_color(old_fg, bg);
        }
        else if (stream == SERIAL_STREAM)
        {
            sw_write("[ERROR] ");
        }
        else if (stream == BOTH_STREAM)
        {
            fb_set_color(FB_RED, bg);
            fb_write("[ERROR] ");
            fb_set_color(old_fg, bg);
            sw_write("[ERROR] ");
        }
        break;

    default:
        break;
    }

    char **arg = (char **)&format;
    int c;
    char buf[20];

    arg++;

    while ((c = *format++) != 0)
    {
        if (c != '%')
            if (stream == SERIAL_STREAM)
                sw_put(c);
            else if (stream == SCREEN_STREAM)
                fb_put(c);
            else
            {
                sw_put(c);
                fb_put(c);
            }

        else
        {
            char *p;

            c = *format++;
            switch (c)
            {
            case 'd':
            case 'u':
            case 'x':
                itoa(buf, c, *((int *)arg++));
                p = buf;
                goto string;
                break;

            case 's':
                p = *arg++;
                if (!p)
                    p = "(null)";

            string:
                while (*p)
                    if (stream == SERIAL_STREAM)
                        sw_put(*p++);
                    else if (stream == SCREEN_STREAM)
                        fb_put(*p++);
                    else
                    {
                        sw_put(*p);
                        fb_put(*p++);
                    }
                break;

            default:
                if (stream == SERIAL_STREAM)
                    sw_put(*((int *)arg++));
                else if (stream == SCREEN_STREAM)
                    fb_put(*((int *)arg++));
                else
                {
                    sw_put(*((int *)arg));
                    fb_put(*((int *)arg++));
                }
                break;
            }
        }
    }
}
