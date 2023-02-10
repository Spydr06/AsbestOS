#include "pit.h"
#include "dev.h"

static uint32_t timer_delta_time;
static uint32_t divisor;

void init_pit(uint32_t frequency)
{
    uint32_t count, remainder;

    if (frequency <= 18)
        count = 0xffff;
    else if(frequency >= INTERNAL_FREQUENCY)
        count = 1;
    else {
        count = INTERNAL_FREQUENCY_3X / frequency;
        remainder = INTERNAL_FREQUENCY_3X % frequency;

        if(remainder >= INTERNAL_FREQUENCY_3X / 2)
            count++;
        
        count /= 3;
        remainder = count % 3;

        if(remainder >= 1)
            count++;
    }

    divisor = count & 0xffff;
    timer_delta_time = (3685982306ULL * count) >> 10;

    outb(I8253_CONTROL_REG, 0x34);
    outb(I8253_DATA_REG, divisor & 0xff); // LSB
    outb(I8253_DATA_REG, divisor >> 8); // MSB
}
