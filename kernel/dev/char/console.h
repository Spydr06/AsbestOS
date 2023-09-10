#ifndef _KERNEL_DEV_CHAR_CONSOLE_H
#define _KERNEL_DEV_CHAR_CONSOLE_H

#include <stdint.h>

#define CONSOLE_BLACK           0
#define CONSOLE_BLUE            1
#define CONSOLE_GREEN           2
#define CONSOLE_CYAN            3
#define CONSOLE_RED             4
#define CONSOLE_MAGENTA         5
#define CONSOLE_BROWN           6
#define CONSOLE_LIGHT_GREY      7
#define CONSOLE_DARK_GREY       8
#define CONSOLE_LIGHT_BLUE      9
#define CONSOLE_LIGHT_GREEN     10
#define CONSOLE_LIGHT_CYAN      11
#define CONSOLE_LIGHT_RED       12
#define CONSOLE_LIGHT_MAGENTA   13
#define CONSOLE_LIGHT_BROWN     14
#define CONSOLE_WHITE           15

#define CONSOLE_TABSIZE 4

#define CONSOLE_COMMAND_PORT 0x3d4
#define CONSOLE_DATA_PORT    0x3d5

#define CONSOLE_HIGH_BYTE_COMMAND 14
#define CONSOLE_LOW_BYTE_COMMAND  15

void console_putchar(char c);
void console_puts(const char* str);

void console_move_cursor(uint16_t pos);
uint16_t console_cursor_pos(void);

#endif /* _KERNEL_DEV_CHAR_CONSOLE_H */
