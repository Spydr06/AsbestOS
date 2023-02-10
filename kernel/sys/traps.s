.set NUM_INT, 0x31
.set NUM_EXC, 0x14

.set CODE_SELECTOR, 0x08
.set DATA_SELECTOR, 0x10

.text

// interrupt service routine stubs
_isr:

.set i, 0
.rept NUM_INT

.set isr_stub_start, .

.if i == 8 || (i >= 10 && i <= 14) || i == 17
    nop
    nop
    pushl $i
    jmp interrupt_common
.else
    pushl $0
    pushl $i
    jmp interrupt_common
.endif

.set isr_stub_len, . - isr_stub_start

.set i, i + 1
.endr

.fill 256

interrupt_common:
    pushl %gs               /* save segment registers */
    pushl %fs
    pushl %es
    pushl %ds
    pusha                   /* save general purpose registers */
    movl $DATA_SELECTOR, %eax /* put known good value in segment registers */
    movl %eax, %gs
    movl %eax, %fs
    movl %eax, %es
    movl %eax, %ds

    movl %esp, %eax         /* store pointer to iframe */
    pushl %eax

    call exception_handler

    popl %eax               /* drop pointer to iframe */

    popa                    /* restore general purpose registers */
    popl %ds                /* restore segment registers */
    popl %es
    popl %fs
    popl %gs
    addl $8, %esp           /* drop exception number and error code */
    iret

.global init_idt
.type init_idt, @function
init_idt:
    movl $_isr, %esi
    movl $_idt, %edi
    movl $NUM_INT, %ecx

.Lloop:
    movl %esi, %ebx
    movw %bx, (%edi)        /* low word in IDT(n).low */
    shrl $16, %ebx
    movw %bx, 6(%edi)       /* high word in IDT(n).high */

    addl $isr_stub_len, %esi/* index the next ISR stub */
    addl $8, %edi           /* index the next IDT entry */

    loop .Lloop

    lidt _idtr

    ret

.data

.align 8
.global _idtr
_idtr:
    .short _idt_end - _idt - 1
    .int _idt

// interrupt descriptor table
.global _idt
_idt:

.set i, 0
.rept NUM_INT - 1
    .short 0
    .short CODE_SELECTOR
    .byte 0
    .byte 0x8e
    .short 0

.set i, i + 1
.endr

.global _idt_end
_idt_end:
