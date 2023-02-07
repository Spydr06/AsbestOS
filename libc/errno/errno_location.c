#include <errno.h>

// TODO: fix this to support multi-threading eventually
static int __errno;

int* __errno_location(void)
{
    return &__errno;
}
