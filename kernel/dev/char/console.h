#ifndef KERNEL_IO_H
#define KERNEL_IO_H

#include <stdint.h>

// framebuffer colors
#define FB_BLACK        0
#define FB_BLUE         1
#define FB_GREEN        2
#define FB_CYAN         3
#define FB_RED          4
#define FB_MAGENTA      5
#define FB_BROWN        6
#define FB_LT_GREY      7
#define FB_DARK_GREY    8
#define FB_LT_BLUE      9
#define FB_LT_GREEN    10
#define FB_LT_CYAN     11
#define FB_LT_RED      12
#define FB_LT_MAGENTA  13
#define FB_LT_BROWN    14
#define FB_WHITE       15

#define FB_WIDTH 80
#define FB_HEIGHT 25

#define FB_TABSIZE 4

// The I/O ports
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

// The I/O port commands
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15



void console_write_cell(uint32_t i, char c, uint8_t fg, uint8_t bg);
void console_move_cursor(uint16_t pos);
uint16_t console_cursor_pos(void);

void console_scroll(void);
void console_color(uint8_t fg, uint8_t bg);

int console_write(const char* buf, uint32_t len);
int console_puts(const char* buf);
void console_init(void);

void console_keycode(uint8_t scan_code);

#endif /* KERNEL_IO_H */
