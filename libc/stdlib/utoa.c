#include <stdlib.h>

int utoa(unsigned int value, char* sp, int radix)
{
    char tmp[16];// be careful with the length of the buffer
    char *tp = tmp;
    int i;

    while (value || tp == tmp)
    {
        i = value % radix;
        value /= radix;
        if (i < 10)
          *tp++ = i+'0';
        else
          *tp++ = i + 'a' - 10;
    }

    int len = tp - tmp;

    while (tp > tmp)
        *sp++ = *--tp;

    *sp = '\0';
    return len;
}
