#include <LPC21xx.H>

#include "defines.h"
#include "types.h"
#include "delay.h"


//shift registers signals
#define SIN_1 16	  //data
#define CP_1  17	  //clock
#define SIN_2 18	//data
#define CP_2  19	//clock
#define SIN_3 20	//data
#define CP_3  21	//clock
#define SIN_4 22	//data
#define CP_4  23	//clock
// Function to initialize GPIO pins used for 74HC164 shift registers
void Init_SIPO()
{
    // Configure Serial Input pin and Clock pin of SIPO-1 as output
    SETBIT(IODIR1,SIN_1);
    SETBIT(IODIR1,CP_1);

    // Configure Serial Input pin and Clock pin of SIPO-2 as output
    SETBIT(IODIR1,SIN_2);
    SETBIT(IODIR1,CP_2);

    // Configure Serial Input pin and Clock pin of SIPO-3 as output
    SETBIT(IODIR1,SIN_3);
    SETBIT(IODIR1,CP_3);

    // Configure Serial Input pin and Clock pin of SIPO-4 as output
    SETBIT(IODIR1,SIN_4);
    SETBIT(IODIR1,CP_4);
}


void SIPO_74HC164_1(u8 ch)
{
    u8 i;

    // Send each bit of data serially (MSB first)
    for(i=0;i<8;i++)
    {
        // Send current bit value to serial input pin
        // Extract bit from MSB to LSB
        WRITEBIT(IOPIN1,SIN_1,((ch>>(7-i))&1));

        // Generate clock pulse for shifting data into register
        IOCLR1 = 1<<CP_1;      // Make clock pin LOW
        delay_us(1);           // Small delay for clock timing
        IOSET1 = 1<<CP_1;      // Make clock pin HIGH
        delay_us(1);           // Small delay for clock timing
    }
}



void SIPO_74HC164_2(u8 ch)
{
    u8 i;

    // Send data bits serially from MSB to LSB
    for(i=0;i<8;i++)
    {
        // Write current bit to SIPO-2 serial input pin
        WRITEBIT(IOPIN1,SIN_2,((ch>>(7-i))&1));

        // Generate clock pulse to shift the bit
        IOCLR1 = 1<<CP_2;      // Clock LOW
        delay_us(1);           // Clock delay
        IOSET1 = 1<<CP_2;      // Clock HIGH
        delay_us(1);           // Clock delay
    }
}


void SIPO_74HC164_3(u8 ch)
{
    u8 i;

    // Transfer data bits one by one to SIPO-3
    for(i=0;i<8;i++)
    {
        // Send individual bit through serial input pin
        WRITEBIT(IOPIN1,SIN_3,((ch>>(7-i))&1));

        // Generate clock pulse for data shifting
        IOCLR1 = 1<<CP_3;      // Clock LOW
        delay_us(1);           // Delay
        IOSET1 = 1<<CP_3;      // Clock HIGH
        delay_us(1);           // Delay
    }
}


void SIPO_74HC164_4(u8 ch)
{
    u8 i;

    // Send data serially to SIPO-4 shift register
    for(i=0;i<8;i++)
    {
        // Write each bit from MSB to LSB
        WRITEBIT(IOPIN1,SIN_4,((ch>>(7-i))&1));

        // Generate clock pulse to latch the bit into register
        IOCLR1 = 1<<CP_4;      // Clock LOW
        delay_us(1);           // Delay
        IOSET1 = 1<<CP_4;      // Clock HIGH
        delay_us(1);           // Delay
    }
}
