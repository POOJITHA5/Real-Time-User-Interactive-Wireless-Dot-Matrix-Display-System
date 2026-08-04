#include <LPC21xx.h>        // LPC2129 microcontroller registers
#include "fixed_string.h"   // Dot matrix display functions
#include "uart.h"           // UART communication functions

// Function declarations (defined in other files)
void UART_SendMenu(void);
void fixed_string(void);
void blinking_string(void);
void scrolling_string(void);

// External variable (updated in UART ISR when data is received)
extern char rx_data;

int main()
{
    // Initialize hardware modules
    Init_SIPO();        // Initialize Shift Register (used for dot matrix control)
    Init_dotmatrix();   // Initialize dot matrix display
    UART0_Init();       // Initialize UART for Bluetooth communication

    // Infinite loop
    while(1)
    {
        // If user sends '!' → show menu
        if(rx_data == '!')
        {
            UART_SendMenu();   // Send menu over UART (Bluetooth)
            rx_data = 0;       // Clear received data
        }

        // Option 1 → Fixed string display
        if(rx_data == '1')
        {
            fixed_string();    // Display static text
            rx_data = 0;       // Clear input
        }

        // Option 2 → Blinking string
        if(rx_data == '2')
        {
            blinking_string(); // Display blinking text
            rx_data = 0;
        }

        // Option 3 → Scrolling string
        if(rx_data == '3')
        {
            scrolling_string(); // Display moving text
            rx_data = 0;
        }
    }
}
