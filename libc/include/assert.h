#ifndef _ASSERT_H
#define _ASSERT_H

#include <sys/cdefs.h>

#undef assert
#ifdef NDEBUG
#define assert(ignore) ((void) 0)
#else
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
void __gripe(char* expr, char* file, int line, const char* func);

#define assert(expr) ((void)((expr) || (__gripe(#expr, __FILE__, __LINE__, __func__), 1)))
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* NDEBUG */

#endif /* _ASSERT_H */
