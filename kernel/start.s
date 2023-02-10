.set MAGIC_NUMBER, 0x1BADB002
.set FLAGS, 0x0
.set CHECKSUM, -MAGIC_NUMBER
.set KERNEL_STACK_SIZE, 16384

.text
.align 4
.long MAGIC_NUMBER
.long FLAGS
.long CHECKSUM

# kernel entry point
.extern kmain
.global _start
.type _start, @function
_start:
    cli
    mov $kernel_stack_top, %esp

    # call kernel main function
    call kmain

    cli
    hlt

.bss
.align 4
kernel_stack:
    .skip KERNEL_STACK_SIZE
kernel_stack_top:
