#ifndef KERNEL_IRQ_HANDLERS_H
#define KERNEL_IRQ_HANDLERS_H

#include "../../x86.h"

#define IRQ_PIT 0
#define IRQ_PS2 1

typedef void (*InterruptHandler_T)(IFrame_T*);

void irq_register_handler(int irq, InterruptHandler_T handler);
void irq_unregister_handler(int irq);
void handle_platform_irq(IFrame_T* frame);

void sys_tick_handler(IFrame_T *frame);
void sys_key_handler(IFrame_T *frame);

#endif /* KERNEL_IRQ_HANDLERS_H */
