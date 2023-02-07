#ifndef _ASSERT_H
#define _ASSERT_H

#include <sys/cdefs.h>

#undef assert
#ifdef NDEBUG
#define assert(ignore) ((void) 0)
#else
extern void __gripe(char* expr, char* file, int line, const char* func);

#define assert(expr) \
    ((expr) ? (void) 0 : \
    __gripe(#expr, __FILE__, __LINE__, __func__))
#endif /* NDEBUG */

#endif /* _ASSERT_H */
