#ifndef KERNEL_CPU_H
#define KERNEL_CPU_H

#include <stdint.h>

typedef struct {
    uint32_t di, si, bp, sp, bx, dx, cx, ax;
    uint32_t ds, es, fs, gs;
    uint32_t vector;
    uint32_t err_code;
    uint32_t ip, cs, flags;
    uint32_t user_sp, user_ss;
} __attribute__((packed)) IFrame_T;

#define kpanic() __kpanic(__FILE__, __func__, __LINE__)

void __kpanic(const char* file, const char* function, int line);

#define x86_enable_int() asm volatile("sti")
#define x86_disable_int() asm volatile("cli")
#define x86_halt() asm volatile("cli; hlt");

#endif /* KERNEL_CPU_H */
