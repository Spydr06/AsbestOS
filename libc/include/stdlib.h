#ifndef _STDLIB_H
#define _STDLIB_H

#include <sys/cdefs.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__)) void abort(void);

int itoa(int value, char* sp, int radix);
int utoa(unsigned int value, char* sp, int radix);

void* malloc(size_t size);
void* calloc(size_t num, size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif /* _STDLIB_H */
