.set STACK_LOCATION, 0x9d000
.set P4_TAB,         0x1000 // one page
.set P3_TAB,         0x2000 // one page
.set P2_TAB,         0x3000 // many pages

.set NUM_P3_ENTRIES, 4
.set NUM_P2_ENTRIES, (NUM_P3_ENTRIES * 512)

.set IA32_EFER,             0xc0000080
.set IA32_STAR,             0xc0000081
.set IA32_LSTAR,            0xc0000082
.set IA32_FMASK,            0xc0000084
.set IA32_FS_BASE,          0xc0000100
.set IA32_GS_BASE,          0xc0000101
.set IA32_KERNEL_GS_BASE,   0xc0000102

// cr0 paging enable bit
.set PAGING_ENABLE, 0x80000000
// cr0 supervisor write-protect enable bit
.set SUPER_WP_ENABLE, 0x10000

// EFER longmode enable bit
.set LONGMODE_ENABLE, 0x100
// EFER execute disable bit
.set NX_ENABLE, 0x800
// EFER syscall enable bit
.set SYSCALL_ENABLE, 0x1

.code32
.section .text
.global begin_enter_longmode
begin_enter_longmode:

    // disable old paging
    mov %cr0, %eax
    mov $0x7fffffff, %eax
    mov %eax, %cr0

    // address  for page map level 4
    mov $P4_TAB, %edi
    mov %edi, %cr3
    // clear out P4 and P3
    mov $0x800 /* 0x2000 / 0x4 */, %ecx
    xor %eax, %eax
    rep stos %eax, %es:(%edi)

    // create page map entry
    mov $P4_TAB, %edi
    movl $(P3_TAB | 0x3), (%edi)

    // create 1GB mappings
    mov $NUM_P3_ENTRIES, %ecx
    mov $P3_TAB, %edi
    mov $(P2_TAB | 0x3), %eax
    mov $0x0, %ebx

.p3_loop:
    movl %eax, (%edi)
    movl %ebx, 4(%edi)
    add $(1 << 12), %eax
    adc $0, %ebx
    add $8, %edi
    loop .p3_loop

    // create 2Mb mappings
    mov $NUM_P2_ENTRIES, %ecx
    mov $P2_TAB, %edi
    mov $(0x0 | 0x3 | 1 << 7), %eax
    mov $0x0, %ebx

.p2_loop:
    movl %eax, (%edi)
    movl %ebx, 4(%edi)
    add $(1 << 12), %eax
    adc $0, %ebx
    add $8, %edi
    loop .p2_loop

    // enable PAE
    mov %cr4, %eax
    or $(1 << 5), %eax
    mov %eax, %cr4

    // enable long mode
    mov $IA32_EFER, %ecx
    rdmsr
    or $(LONGMODE_ENABLE | NX_ENABLE | SYSCALL_ENABLE), %eax
    wrmsr

    // enable paging
    mov %cr0, %eax
    or $(PAGING_ENABLE | SUPER_WP_ENABLE), %eax
    mov %eax, %cr0

    jmp long_mode
.code64

.extern kernel_main
.extern multiboot_data_magic
.extern multiboot_data_address

long_mode:
    cli

    push %rsp
    mov $STACK_LOCATION, %rsp
    push $0x0
    push $0x0
    mov %rsp, %rbp

    mov $IA32_STAR, %ecx
    mov $0x8, %edx
    mov $0x0, %eax
    wrmsr

    /*// enable stack protector
    .extern tls
    mov $IA32_FS_BASE, %ecx
    mov $0x0, %edx
    mov tls, %eax
    wrmsr

    .extern __SSP__
    rdtsc
    mov __SSP__, %rcx
    xor %rcx, %rax
    movq %rax, (tls + 0x28)*/

    movl multiboot_data_magic, %edi
    movl multiboot_data_address, %esi
    call kernel_main

    cli
    hlt
