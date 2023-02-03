#include "interrupt.h"

void interrupt_handler(struct cpu_state cpu, struct stack_state stack, uint32_t interrupt)
{

}

void pic_acknowledge(uint32_t interrupt)
{
    if(interrupt < PIC1_START_INTERRUPT || interrupt > PIC2_END_INTERRUPT)
        return;

    if(interrupt < PIC2_START_INTERRUPT)
        outb(PIC1_PORT_A, PIC_ACK);
    else
        outb(PIC2_PORT_A, PIC_ACK);
}

uint8_t read_scan_code(void)
{
    return inb(KBD_DATA_PORT);
}
