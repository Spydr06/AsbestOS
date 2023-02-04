section .text

global gdt_flush
gdt_flush:
    extern gdt_p
    lgdt [gdt_p]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush_cs

flush_cs: ret
