#include "dev/char/console.h"
extern void _halt(void);

#include <stdint.h>

void kernel_main(uint32_t eax, uint32_t ebx) {
    console_move_cursor(4);
    uint16_t* vga_buffer = (uint16_t*) 0xb8000;
    vga_buffer[0] = 'A' | 15 << 8;


    while(1);
};
