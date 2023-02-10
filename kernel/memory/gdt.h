#ifndef KERNEL_GDT_H
#define KERNEL_GDT_H

#include <stdint.h>

#define GDT_ENTRIES 3

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) GDTPointer_T;

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) GDTEntry_T;

void gdt_flush(void);
void init_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);
void gdt_install_flat(void);

#endif /* KERNEL_GDT_H */
