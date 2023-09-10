.section .text

// outb - send a byte to an IO port
// stack: [rsp + 16] the data byte
//        [rsp + 8] the IO port
//        [rsp]     return address
.global outb
outb:
    mov 16(%rsp), %al
    mov 8(%rsp), %dx
    out %al, %dx
    ret

// inb - read a byte from an IO port
// stack: [rsp + 8] the IO port
//        [rsp]     return address
.globl inb
inb:
    mov 8(%rsp), %dx
    in %dx, %al
    ret
