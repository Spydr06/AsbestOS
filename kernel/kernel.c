#include "io/io.h"
#include "io/serial/serial.h"
#include "io/log/log.h"
#include "memory/gdt.h"

#include <stdio.h>
#include <stdlib.h>

#if !defined(__i386__)
    #error "Expected x86 architecture"
#endif

#define X86_OK 0

int x86_pc_init(void) {
    gdt_install_flat();
    klog(KLOG_OK, "GDT installed");

    return X86_OK;
}

void kmain(void) {
    fb_init();
    klog(KLOG_NONE, "kmain() at address: 0x%x", (unsigned int) kmain);

    serial_configure_baud_rate(SERIAL_COM1, 1);
    serial_configure_line(SERIAL_COM1);
    serial_write(SERIAL_COM1, "Serial port COM1 initialized" SERIAL_NEWLINE, 30);

    if(x86_pc_init() != X86_OK)
        goto failure;

    while(1) {}

failure:
    klog(KLOG_FAIL, "kmain@failure: label reached");
    abort();
}
