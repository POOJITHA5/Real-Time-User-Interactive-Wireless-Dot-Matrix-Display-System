#include <LPC21xx.H>              

#include "dotmatrix_driver.h"     
#include "sipo_74hc164.h"         

//#define DBUG                     

int main()
{
   
    u8 i, user_str[] = "   V25HE4 BATCH IS TOOO GOOD BATCH!   ";

   
    Init_SIPO();

       Init_dotmatrix_anodes();

    // Infinite loop to continuously scroll the message
    while(1)
    {
        // Move the display window through each character of the message
        // 38-3 is used to limit the scrolling length of the string
        for(i=0; i<38-3; i++)
        {
            // Display 4 characters at a time on dot matrix
            // The second parameter controls display refresh delay
            display_str(user_str+i, 10);
        }
    }
}