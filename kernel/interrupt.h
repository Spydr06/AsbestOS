#ifndef KERNEL_INTERRUPT_H
#define KERNEL_INTERRUPT_H

#include "io.h"

struct cpu_state {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t esp;
} __attribute__((packed));

struct stack_state {
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute((packed));

void interrupt_handler(struct cpu_state cpu, struct stack_state stack, uint32_t interrupt);

#define PIC1_PORT_A 0x20
#define PIC2_PORT_A 0xA0

/* The PIC interrupts have been remapped */
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT   PIC2_START_INTERRUPT + 7
#define PIC_ACK     0x20

void pic_acknowledge(uint32_t interrupt);

#define KBD_DATA_PORT   0x60

uint8_t read_scan_code(void);

#endif /* KERNEL_INTERRUPT_H */