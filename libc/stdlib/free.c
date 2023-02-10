#include <stdlib.h>
#include <assert.h>

void free(void* ptr)
{
#ifdef __is_libk
    assert(0);
#else
    assert(0);
#endif
}
