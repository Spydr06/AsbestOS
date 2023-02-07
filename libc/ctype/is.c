#include <ctype.h>

int isalnum(int ch)
{
    return isalpha(ch) || isdigit(ch);
}

int isalpha(int ch)
{
    return ((unsigned) ch | 32) - 'a' < 26; 
}

int islower(int ch)
{
    return (unsigned) ch - 'a' < 26;
}

int isupper(int ch)
{
    return (unsigned) ch - 'A' < 26;
}

int isdigit(int ch)
{
    return (unsigned) ch - '0' < 10;
}

int isxdigit(int ch)
{
    return isdigit(ch) || ((unsigned) ch | 32) - 'a' < 6;
}

int iscntrl(int ch)
{
    return (unsigned) ch < 0x20 || ch == 0x7f;
}

int isgraph(int ch)
{
    return (unsigned) ch - 0x21 < 0x5e;
}

int isspace(int ch)
{
    return ch == ' ' || (unsigned) ch - '\t' < 5;
}

int isblank(int ch)
{
    return ch == ' ' || ch == '\t';
}

int isprint(int ch)
{
    return (unsigned) ch - 0x20 < 0x5f;
}

int ispunct(int ch)
{
    return isgraph(ch) && !isalnum(ch);
}
