#include "exception.h"
#include "io/log/log.h"
#include "io/interrupts/irq.h"
#include "x86.h"

#include <stdlib.h>
#include <stdio.h>

static char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

static void __attribute__((noreturn)) handle_exception(IFrame_T* iframe)
{
    klog(KLOG_FAIL, "Exception raised: %s", exception_messages[iframe->vector]);
    printf("di: %x,\tsi: %x,\tbp: %x,\tsp: %x\n"
        "bx: %x,\tdx: %x,\tcx: %x,\tax: %x\n"
        "dx: %x,\tex: %x\tfs: %x,\tgs: %x\n"
        "vector: %x,\terr_code: %x\n"
        "ip: %x,\tcs: %x,\tflags: %x\n"
        "user_sp: %x,\tuser_ss: %x\n",
        iframe->di, iframe->si, iframe->bp, iframe->sp, 
        iframe->bx, iframe->dx, iframe->cx, iframe->ax, 
        iframe->ds, iframe->es, iframe->fs, iframe->gs, 
        iframe->vector, iframe->err_code, iframe->ip, 
        iframe->cs, iframe->flags, iframe->user_sp, 
        iframe->user_ss
    );
    kpanic();
}

static inline void __attribute__((noreturn)) handle_unknown(IFrame_T* iframe)
{
    iframe->vector = 16;
    handle_exception(iframe);
}

void exception_handler(IFrame_T* iframe)
{
    uint32_t vector = iframe->vector;
    if(31 >= vector)
        handle_exception(iframe);
    else if(47 >= vector)
        handle_platform_irq(iframe);
    else
        handle_unknown(iframe);
}
