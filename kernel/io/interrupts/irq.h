#ifndef KERNEL_IRQ_HANDLERS_H
#define KERNEL_IRQ_HANDLERS_H

#include "../../x86.h"

#define IRQ_PIT 0
#define IRQ_PS2 1

void irq_register_handler(int irq, void (*handler)(struct iframe*));
void irq_unregister_handler(int irq);
void handle_platform_irq(struct iframe* frame);

void sys_tick_handler(struct iframe *frame);
void sys_key_handler(struct iframe *frame);

#endif /* KERNEL_IRQ_HANDLERS_H */
