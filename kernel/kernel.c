#include "io.h"
#include "serial.h"
#include <stdio.h>
#include "log.h"

#if !defined(__i386__)
    #error "Expected x86 architecture"
#endif

void load_gdt(struct gdt* gdt);

void kmain(void) {
    serial_configure_baud_rate(SERIAL_COM1, 1);
    serial_configure_line(SERIAL_COM1);
    serial_write(SERIAL_COM1, "Serial port COM1 initialized" SERIAL_NEWLINE, 30);

    fb_init();
    klog(KLOG_NONE, "kmain() at address: 0x%x", (unsigned int) kmain);

    printf("I.\t%s\nII.\t%s\n", "Hello, World!", "Second line...");
    while(1) {}
}
