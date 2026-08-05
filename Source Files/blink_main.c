#include <LPC21xx.H>             
#include "fixed_string.h"        
#include "sipo_74hc164.h"  

//#define DBUG                  

int main()
{
    Init_SIPO();

    // Initialize the dot matrix anode connections
    Init_dotmatrix_anodes();

    while(1)
    {
        // Display the string "ARIF" for 500 ms
        display_str("LUCK", 500);

        // Turn OFF all rows of the dot matrix display
        CLEARBYTE(IOCLR0, 0xFF);

        // Wait for 300 ms before displaying the next string
        delay_ms(300);

        // Display the string "MAHI" for 500 ms
        display_str("GOOD", 500);

        // Turn OFF all rows of the dot matrix display
        CLEARBYTE(IOCLR0, 0xFF);

        // Wait for 300 ms before repeating the sequence
        delay_ms(300);
    }
}