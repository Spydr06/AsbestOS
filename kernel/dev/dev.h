#ifndef KERNEL_DEV_H
#define KERNEL_DEV_H

#include <stdint.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

#endif /* KERNEL_DEV_H */
