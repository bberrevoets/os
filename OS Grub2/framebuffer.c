/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framebuffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: B.N. Berrevoets <bert@berrevoets.net>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:33:32 by B.N. Berrev       #+#    #+#             */
/*   Updated: 2020/10/17 00:33:32 by B.N. Berrev      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "framebuffer.h"

// The VGA framebuffer starts at 0xB8000.
unsigned short *fb = (unsigned short *)0xB8000;

// Stores the current cursor position
unsigned char cursor_x = 0;
unsigned char cursor_y = 0;

/** fb_move_cursor:
 * Moves the cursor of the framebuffer to the given position
 * 
 * @param pos The new position of the cursor
 */
void fb_move_cursor()
{
    unsigned short pos = cursor_y * 80 + cursor_x;
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}

/** fb_init:
 * Initialization of the framebuffer to the default values
 */
void fb_init(void)
{
    fg = FB_LIGHT_GREY;
    bg = FB_BLACK;
    fb_clear();
}

/** fb_set_color:
 * Sets the current colors the framebuffer uses
 * 
 * @param foreground The forground color
 * @param background The backgroud color
 */
void fb_set_color(unsigned char foreground, unsigned char background)
{
    fg = foreground;
    bg = background;
}

/** fb_scroll:
 * Scrolls the text on the screen up by one line.
 */
void fb_scroll()
{
    // Get a space character with the default color attributes.
    unsigned char attributeByte = (bg << 4) | (fg & 0x0F);
    unsigned short blank = 0x20 | (attributeByte << 8);

    // Row 25 is the end, this means we need to scroll up
    if (cursor_y >= 25)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 0 * 80; i < 24 * 80; i++)
        {
            fb[i] = fb[i + 80];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 24 * 80; i < 25 * 80; i++)
        {
            fb[i] = blank;
        }
        // The cursor should now be on the last line.
        cursor_y = 24;
    }
}

/** fb_put:
 * Writes a character with the current foreground and background to position i
 * in the framebuffer.
 * 
 * @param c The character
 */
void fb_put(char c)
{
    // Get a space character with the default color attributes.
    unsigned char attributeByte = (bg << 4) | (fg & 0x0F);
    unsigned short attribute = attributeByte << 8;
    unsigned short *location;

    // Handle a backspace, by moving the cursor back one space
    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }

    // Handle a tab by increasing the cursor's X, but only to a point
    // where it is divisible by 8.
    else if (c == 0x09)
    {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    }

    // Handle carriage return
    else if (c == '\r')
    {
        cursor_x = 0;
    }

    // Handle newline by moving cursor back to left and increasing the row
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    // Handle any other printable character.
    else if (c >= ' ')
    {
        location = fb + (cursor_y * 80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    // Check if we need to insert a new line because we have reached the end
    // of the screen.
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }

    // Scroll the screen if needed.
    fb_scroll();
    // Move the hardware cursor.
    fb_move_cursor();
}

/** fb_clear:
 * Clears the screen
 */
void fb_clear()
{
    // Make an attribute byte for the default colours
    unsigned char attributeByte = (bg << 4) | (fg & 0x0F);
    unsigned short blank = 0x20 /* space */ | (attributeByte << 8);

    int i;
    for (i = 0; i < 80 * 25; i++)
    {
        fb[i] = blank;
    }

    // Move the hardware cursor back to the start.
    cursor_x = 0;
    cursor_y = 0;
    fb_move_cursor();
}

/** fb_write:
 * Outputs a null-terminated ASCII string to the framebuffer
 */
void fb_write(char *c)
{
    int i = 0;
    while (c[i])
    {
        fb_put(c[i++]);
    }
}

void fb_write_hex(unsigned int n)
{
    int tmp;

    fb_write("0x");

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
            fb_put(tmp - 0xA + 'a');
        }
        else
        {
            noZeroes = 0;
            fb_put(tmp + '0');
        }
    }

    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        fb_put(tmp - 0xA + 'a');
    }
    else
    {
        fb_put(tmp + '0');
    }
}

void fb_write_dec(unsigned int n)
{
    if (n == 0)
    {
        fb_put('0');
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
    fb_write(c2);
}
