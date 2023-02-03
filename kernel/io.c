#include "io.h"

void fb_move_cursor(uint16_t pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00ff));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00ff);
}

uint8_t* fb = (uint8_t*) 0x000B8000;

void fb_write_cell(uint32_t i, char c, uint8_t bg, uint8_t fg)
{
    fb[i] = c;
    fb[i + 1] = ((fg & 0x0f) << 4) | (bg & 0x0f);
}

int fb_write(const char* buf, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
        fb_write_cell(i * 2, buf[i], FB_WHITE, FB_BLACK);
    return len;
}
