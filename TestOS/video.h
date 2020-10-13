#ifndef VIDEO_H
#define VIDEO_H

#include <common.h>

/* Some screen stuff. */
/* The number of columns. */
#define COLUMNS 80
/* The number of lines. */
#define LINES 24
/* The attribute of an character. */
#define ATTRIBUTE 7
/* The video memory address. */
#define VIDEO 0xB8000

/* Variables. */
/* Save the X position. */
int xpos;
/* Save the Y position. */
int ypos;
/* Point to the video memory. */
volatile unsigned char *video;

/* Forward declarations. */
void cls(void);
void itoa(char *buf, int base, int d);
void putchar(int c);
void printf(const char *format, ...);

#endif