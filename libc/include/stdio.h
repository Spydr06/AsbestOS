#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int vprintf(const char* __restrict, va_list);
int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

#ifdef __cplusplus
}
#endif

#endif /* _STDIO_H */
