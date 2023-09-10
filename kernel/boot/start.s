.set STACK_LOCATION, 0x9d400

.set MB_MAGIC, 0x1badb002
.set MB_FLAGS, 0x3 // align + meminfo

.extern _MULTIBOOT_START_
.extern _LOAD_START_
.extern _LOAD_END_
.extern _end
.extern begin_enter_longmode
.extern kernel_main

.align 4
.section .multiboot
    .int MB_MAGIC
    .int MB_FLAGS
    .int -(MB_MAGIC + MB_FLAGS)
    .int _MULTIBOOT_START_
    .int _LOAD_START_
    .int _LOAD_END_
    .int _end
    .int _start

.section .data
.global multiboot_data_magic
multiboot_data_magic:
    .quad 0
.global multiboot_data_address
multiboot_data_address:
    .quad

.code32
.section .text
.global _start
_start:
    cli

continue:
    // 32-bit stack ptr
    mov $STACK_LOCATION, %esp
    mov %esp, %ebp

    movl %eax, multiboot_data_magic
    movl %ebx, multiboot_data_address

    call enable_cpu_feat

    .extern _BSS_START_
    .extern _BSS_END_
    mov _BSS_START_, %edi
    mov _BSS_END_, %ecx
    sub _BSS_START_, %ecx
    mov $0, %eax
    rep stosb

    // enable stack protector
    rdtsc
    movl (0x1014), %eax
    call begin_enter_longmode
    cli
    hlt

enable_cpu_feat:
    // enable SSE
    mov %cr0, %eax
    and $0xfffb, %ax // clear coprocessor emulation CR0.EM
    or $0x2, %ax     // set coprocessor monitoring CR0.MP
    mov %eax, %cr0
    mov %cr4, %eax
    or $(3 << 9), %ax // set CR4.OSFXSR and CR4.OSXMMEXCPT
    or $0x20, %ax     // enable native PFU exception handling
    mov %eax, %cr4
    
    // read out cpu features
    mov $1, %eax
    xor %ecx, %ecx
    cpuid
    mov %ecx, %edx
    // check for XSAVE support (bit 26)
    and $0x04000000, %ecx
    jz xsave_not_supported
    // enable XSAVE
    mov %cr4, %eax
    or $0x40000, %eax
    mov %eax, %cr4

xsave_not_supported:
    // check for AVX support (bit 26)
    and $0x10000000, %edx
    jz avx_not_supported
    // enable AVX
    xor %ecx, %ecx
    xgetbv
    or $0x7, %eax
    xsetbv

avx_not_supported:
    ret
