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

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

void fb_write_cell(uint32_t i, char c, uint8_t fg, uint8_t bg);
void fb_move_cursor(uint16_t pos);
uint16_t fb_cursor_pos(void);

void fb_scroll(void);
void fb_color(uint8_t fg, uint8_t bg);

int fb_write(const char* buf, uint32_t len);
int fb_puts(const char* buf);
void fb_init(void);

void fb_keycode(uint8_t scan_code);

#endif /* KERNEL_IO_H */
