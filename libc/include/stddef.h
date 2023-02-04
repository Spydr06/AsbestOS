#ifndef _STDDEF_H
#define _STDDEF_H

#include <sys/cdefs.h>
#include <sys/types.h>

#define NULL ((void*) 0)

#define offsetof(TYPE, MEMBER) __builtin_offsetof(TYPE, MEMBER)

#ifdef __size_t_defined
typedef __size_t size_t;
#endif

#endif /* _STDDEF_H */
