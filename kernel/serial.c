#include "serial.h"

void serial_configure_baud_rate(uint16_t com, uint16_t divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00ff);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00ff);
}

int serial_write(uint16_t com, const char* buf, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++) {
        while(!serial_is_transmit_fifo_empty(com));
        outb(com, buf[i]);
    }
    return len;
}

void serial_configure_line(uint16_t com);
int serial_is_transmit_fifo_empty(uint32_t com);
