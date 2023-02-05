#ifndef KERNEL_EXCEPTION_H
#define KERNEL_EXCEPTION_H

#include "x86.h"

void exception_handler(struct iframe* iframe);

#endif
