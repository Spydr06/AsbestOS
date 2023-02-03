#include "io.h"
#include "serial.h"

#if !defined(__i386__)
    #error "Expected x86 architecture"
#endif

void load_gdt(struct gdt* gdt);

void kmain(void) {
    serial_configure_baud_rate(SERIAL_COM1, 1);
    serial_configure_line(SERIAL_COM1);
    serial_write(SERIAL_COM1, "Serial port COM1 initialized" SERIAL_NEWLINE, 30);

    fb_init();
    fb_puts("I.\tHello, World!\r\nII.\tSecond Line\r\n");
    while(1) {}
}
