#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void __gripe(char* expr, char* file, int line, const char* func)
{
    printf("Assertion failed: %s (%s: %s: %d)\n", expr, file, func, line);
    abort();
}
