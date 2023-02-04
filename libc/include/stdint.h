#ifndef _STDINT_H
#define _STDINT_H

#include <sys/cdefs.h>
#include <limits.h>

typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef signed short int16_t;
typedef unsigned short uint16_t;

typedef signed int int32_t;
typedef unsigned int uint32_t;

typedef signed long long int64_t;
typedef unsigned long long uint64_t;

#define INT8_MAX SCHAR_MAX
#define INT8_MIN SCHAR_MIN
#define UINT8_MAX UCHAR_MAX

#define INT16_MAX SHRT_MAX
#define INT16_MIN SHRT_MIN
#define UINT16_MAX USHRT_MAX

#define INT32_MAX INT_MAX
#define INT32_MIN INT_MIN
#define UINT32_MAX UINT_MAX

#define INT64_MAX LLONG_MAX
#define INT64_MIN LLONG_MIN
#define UINT64_MAX ULLONG_MAX

#endif /* _STDINT_H */
