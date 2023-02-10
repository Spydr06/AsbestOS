#ifndef _STDDEF_H
#define _STDDEF_H

#include <sys/cdefs.h>

#define NULL ((void*) 0)

#define offsetof(TYPE, MEMBER) __builtin_offsetof(TYPE, MEMBER)

typedef unsigned long size_t;
typedef signed long ptrdiff_t;

#endif /* _STDDEF_H */
