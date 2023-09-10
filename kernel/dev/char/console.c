#include "console.h"
#include "dev/dev.h"

#define VGA_BUFFER ((uint16_t*) 0xb8000)

void console_move_cursor(uint16_t pos)
{
    outb(CONSOLE_COMMAND_PORT, CONSOLE_HIGH_BYTE_COMMAND);
    outb(CONSOLE_DATA_PORT,    (pos >> 8) & 0x00ff);
    outb(CONSOLE_COMMAND_PORT, CONSOLE_LOW_BYTE_COMMAND);
    outb(CONSOLE_DATA_PORT,    pos & 0x00ff);
}
