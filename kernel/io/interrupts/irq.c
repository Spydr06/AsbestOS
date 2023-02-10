#include "irq.h"
#include "../io.h"
#include "pic.h"
#include "../serial/serial.h"
#include "../io.h"

#include <stdio.h>
#include <stddef.h>

static InterruptHandler_T irq_routines[16] = {0};

void irq_register_handler(int irq, InterruptHandler_T handler)
{
    if(handler == NULL || irq < 0 || irq > 15)
        return;
    irq_routines[irq] = handler;
}

void irq_unregister_handler(int irq)
{
    if(irq < 0 || irq > 15)
        return;
    irq_routines[irq] = NULL;
}

void handle_platform_irq(IFrame_T *frame)
{
    uint32_t irq = frame->vector - 32;
    InterruptHandler_T handler = irq_routines[irq];
    if(handler)
        handler(frame);

    if(irq == IRQ_PIT)
        return;

    pic_send_EOI(irq);
}

void sys_tick_handler(IFrame_T* frame)
{
    pic_send_EOI(IRQ_PIT);
}

void sys_key_handler(IFrame_T* frame)
{
    uint8_t scan_code = inb(0x60);
    fb_keycode(scan_code);
}
