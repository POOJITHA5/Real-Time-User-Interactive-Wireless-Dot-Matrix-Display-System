#include <LPC21xx.H>          

//#include "dotmatrix_driver.h" 

#include "sipo_74hc164.h"     
#include "types.h"            

// Function prototypes
void Init_SIPO(void);                    
void Init_dotmatrix_anodes(void);        
void display_char(u8 ch, u32 delay, u8); 
void display_str(u8 *str, u32 delay);     

//#define DEBUG   
int main()
{            
  u8 i;

    // Message to be scrolled across the four dot matrix displays
    u8 user_str[] = "   V25HE4 BATCH IS TOOO GOOD BATCH!   ";

    // Initialize the shift registers
    Init_SIPO();

    // Initialize dot matrix row (anode) pins
    Init_dotmatrix_anodes();

    // Infinite loop
    while(1)
    {
#ifdef DEBUG
        // Display individual characters on different dot matrix modules
        display_char('A', 500, DM1);
        display_char('V', 500, DM3);
        display_char('H', 500, DM2);
        display_char('Z', 500, DM4);

        // Display fixed 4-character words
        display_str("HELP", 500);
        display_str("LUCK", 500);
        display_str("LOCK", 500);
#endif

        // Scroll the message across the four dot matrix displays
        for(i = 0; i < 38 - 3; i++)
        {
            display_str(user_str + i, 10);   // Display four consecutive characters
        }
    }
}