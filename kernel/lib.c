#include "lib.h"

uint32_t strlen(const char *str)
{
    for (uint32_t len = 0;;++len) if (str[len]==0) return len;
}