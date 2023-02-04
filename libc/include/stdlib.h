#ifndef _STDLIB_H
#define _STDLIB_H

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__)) void abort(void);

int itoa(int value, char* sp, int radix);
int utoa(unsigned int value, char* sp, int radix);

#ifdef __cplusplus
}
#endif

#endif /* _STDLIB_H */
