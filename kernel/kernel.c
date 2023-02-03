#include "io.h"

void kmain(void) {
    for(unsigned char i = 'A', j = 0; i <= 'Z'; i++, j += 2)
    {
        fb_write_cell(j, i, FB_BLACK, FB_GREEN);
    }

    while(1) {}
}
