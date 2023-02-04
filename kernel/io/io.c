#include "io.h"
#include "serial/serial.h"
#include <string.h>
#include "log/log.h"

uint8_t* fb = (uint8_t*) 0x000B8000;
uint16_t cursor_pos = 0;
uint8_t fg_color = FB_LT_GREY;
uint8_t bg_color = FB_BLACK;

void fb_move_cursor(uint16_t pos)
{
    cursor_pos = pos;
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00ff));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00ff);
}

uint16_t fb_cursor_pos(void)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    uint16_t pos = inb(FB_DATA_PORT) << 8;
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    pos |= inb(FB_DATA_PORT);
    return pos;
}

void fb_write_cell(uint32_t i, char c, uint8_t bg, uint8_t fg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0f) << 4) | (bg & 0x0f);
}

void fb_scroll(void)
{
    for(int pos = 1; pos < FB_HEIGHT; pos++)
        for(int i = 0; i < FB_WIDTH * 2; i++)
            fb[(pos - 1) * FB_WIDTH * 2 + i] = fb[pos * FB_WIDTH * 2 + i];
}

void fb_color(uint8_t fg, uint8_t bg)
{
    fg_color = fg;
    bg_color = bg;
}

void fb_delete_last_line(void)
{
    for(int32_t x = 0; x < FB_WIDTH * 2; x++) {
		uint8_t* ptr = fb + (FB_WIDTH * 2) * (FB_HEIGHT - 1) + x;
		*ptr = 0;
	}
}

int fb_write(const char* buf, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++) {
        switch(buf[i]) {
        case '\n':
            cursor_pos += FB_WIDTH; // fallthrough
        case '\r':
            cursor_pos = cursor_pos / FB_WIDTH * FB_WIDTH;
            break;
        case '\t':
            cursor_pos = (cursor_pos + FB_TABSIZE) / FB_TABSIZE * FB_TABSIZE;
            break;
        default:
            fb_write_cell(cursor_pos++ * 2, buf[i], fg_color, bg_color);
        }

        if(cursor_pos / FB_WIDTH > FB_HEIGHT - 1) {
            fb_scroll();
            fb_delete_last_line();
            cursor_pos -= FB_WIDTH;
        }
    }
    fb_move_cursor(cursor_pos);
    return len;
}

void fb_init(void)
{
    cursor_pos = fb_cursor_pos();
    klog(KLOG_OK, "framebuffer initialized");
}

int fb_puts(const char* buf)
{
    return fb_write(buf, strlen(buf));
}
