#include <LPC21xx.H>          

#include "fixed_string.h"     
#include "sipo_74hc164.h"   

//#define DEBUG               

int main()
{
    // Initialize the 74HC164 SIPO shift registers
    Init_SIPO();

    // Initialize the dot matrix display
    Init_dotmatrix();

    // Infinite loop
    while(1)
    {
        // Display the string "ARIF" on the dot matrix
        display_str("LUCK", 500);

        // Display another string (currently disabled)
        //display_str("GOOD", 500);
    }
}