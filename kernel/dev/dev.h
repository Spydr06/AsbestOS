#ifndef _KERNEL_DEV_H
#define _KERNEL_DEV_H

#include <stdint.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

#endif /* _KERNEL_DEV_H */