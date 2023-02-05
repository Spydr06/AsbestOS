#ifndef KERNEL_PIC_H
#define KERNEL_PIC_H

#include <stdint.h>

#define PIC_MASTER_REG 0x20
#define PIC_MASTER_IMR 0x21
#define PIC_SLAVE_REG 0xA0
#define PIC_SLAVE_IMR 0xA1

#define PIC_ICW_1 0x11

void init_pic(void);
void pic_disable(void);
void pic_send_EOI(uint32_t irq);

#endif /* KERNEL_PIC_H */
