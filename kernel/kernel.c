#include "io.h"
#include "serial.h"

void kmain(void) {
    serial_configure_baud_rate(SERIAL_COM1, 1);
    serial_configure_line(SERIAL_COM1);
    serial_write(SERIAL_COM1, "Serial port COM1 initialized" SERIAL_NEWLINE, 30);

    fb_write("Hello, World! ", 14);
    while(1) {}
}
