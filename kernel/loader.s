global loader

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER
KERNEL_STACK_SIZE equ 4096

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

; kernel entry point
loader:
    mov eax, 0xCAFEBABE
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    extern kmain
    call kmain ; call kernel main function

global load_gdt
load_gdt:
    mov eax, [esp + 4]
    lgdt [eax]
    ret

global load_idt
load_idt:
    mov eax, [esp + 4]
    lidt [eax]
    ret

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE
