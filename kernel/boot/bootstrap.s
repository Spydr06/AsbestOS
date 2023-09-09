.section .text
.extern kmain

.global _start
.type _start, @function
_start:
    call kmain
    cli
.global _halt
.type _halt, @function
_halt:
    hlt
    jmp _halt

.size _start, . - _start
