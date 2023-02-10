#include "gdt.h"
#include <stdlib.h>

GDTEntry_T gdt[GDT_ENTRIES];
GDTPointer_T gdt_p;

void init_gdt_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    if(index >= GDT_ENTRIES)
        abort();

    gdt[index].base_low = base & 0xffff;
    gdt[index].base_middle = (base >> 16) & 0xff;
    gdt[index].base_high = (base >> 24) & 0xff;
    gdt[index].limit_low = limit & 0xffff;
    gdt[index].granularity = ((limit >> 16) & 0x0f) | (granularity & 0xf0);
    gdt[index].access = access;
}

void gdt_install_flat(void)
{
    gdt_p.limit = (sizeof(GDTEntry_T) * GDT_ENTRIES) - 1;
    gdt_p.base = (uint32_t) gdt;

    init_gdt_entry(0, 0, 0, 0, 0); // null
    init_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code 
    init_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data

    gdt_flush();
}
