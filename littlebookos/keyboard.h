// keyboard.h -- Defines the interface for all PIT-related functions.

#ifndef INCLUDE_KEYBOARD_H
#define INCLUDE_KEYBOARD_H

unsigned int key;

void init_keyboard(void);
unsigned char read_scan_code(void);

#endif
