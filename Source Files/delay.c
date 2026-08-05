#include "types.h"   
void delay_us(u32 tdly)
{
    tdly *= 12;       // Adjust loop count for approximately 1 µs delay
    while(tdly--);    // Busy-wait loop
}
void delay_ms(u32 tdly)
{
    tdly *= 12000;    // Adjust loop count for approximately 1 ms delay
    while(tdly--);    // Busy-wait loop
}

void delay_s(u32 tdly)
{
    tdly *= 12000000; // Adjust loop count for approximately 1 second delay
    while(tdly--);    // Busy-wait loop
}