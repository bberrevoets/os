#ifndef INCLUDE_SERIALWRITER_H
#define INCLUDE_SERIALWRITER_H

#define PORT 0x3F8  // COM1

void sw_init(void);
void sw_put(char c);
void sw_write(char *c);
void sw_write_hex(unsigned int n);
void sw_write_dec(unsigned int n);

#endif
