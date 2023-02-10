#ifndef KERNEL_PIT_H
#define KERNEL_PIT_H

#include <stdint.h>

/* PIT (i8253) registers */
#define I8253_CONTROL_REG 0x43
#define I8253_DATA_REG  0x40

#define SYSTEM_TICKS_PER_SEC 100
#define INTERNAL_FREQUENCY 1193182ULL
#define INTERNAL_FREQUENCY_3X 3579546ULL

void init_pit(uint32_t frequency);

#endif /* KERNEL_PIT_H */
