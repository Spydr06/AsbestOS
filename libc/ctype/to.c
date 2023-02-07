#include <ctype.h>

int tolower(int ch)
{
    if(isupper(ch))
        return ch | 32;
    return ch;
}

int topupper(int ch)
{
    if(islower(ch))
        return ch & 0x5f;
    return ch;
}
