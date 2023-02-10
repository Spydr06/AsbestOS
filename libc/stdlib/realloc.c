#include <stdlib.h>
#include <assert.h>

void* realloc(void* ptr, size_t new_size)
{
#ifdef __is_libk
    assert(0);
    return NULL;
#else
    assert(0);
    return NULL;
#endif
}
