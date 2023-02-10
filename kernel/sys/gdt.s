.text

.extern gdt_p
.global gdt_flush
.type gdt_flush, @function
gdt_flush:
    lgdt gdt_p
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ljmp $0x08, $flush_cs

flush_cs: ret
