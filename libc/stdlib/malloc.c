#include <stdlib.h>
#include <assert.h>

void* malloc(size_t size)
{
#ifdef __is_libk
    assert(0);
    return NULL;
#else
    assert(0);
    return NULL;
#endif
}
