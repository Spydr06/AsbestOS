#ifndef _SETJMP_H
#define _SETJMP_H

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long __jmp_buf[6];

typedef struct {
    __jmp_buf __jb;
    unsigned long __fl;
    unsigned long __ss[128 / sizeof(long)];
} jmp_buf[1];

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 1)
#define __setjmp_attr __attribute__((__returns_twice__))
#endif

int setjmp(jmp_buf) __setjmp_attr;
void longjmp(jmp_buf, int);

#ifdef __cplusplus
}
#endif

#endif /* _SETJMP_H */
