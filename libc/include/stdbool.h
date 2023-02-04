#ifndef _STDBOOL_H
#define _STDBOOL_H

#include <sys/cdefs.h>

#define _Bool signed char
#define bool _Bool

#ifdef __cplusplus
    #define true true
    #define false false
#else
    #define true 1
    #define false 0
#endif

#endif /* _STDBOOL_H */
