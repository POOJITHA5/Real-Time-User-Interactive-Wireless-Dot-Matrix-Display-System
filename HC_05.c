#include <LPC21xx.h>        // LPC2129 microcontroller register definitions
#include "fixed_string.h"   // Functions for displaying strings
#include "defines.h"        // Macros like CLEARBYTE
#include "delay.h"          // Delay functions

char rx_data = 0;           // Variable to store received UART data
int tx_index = 0;           // Index to track menu transmission

// Menu displayed over UART (Bluetooth terminal)
char menu[] =
"\r\n------ DOT MATRIX MENU ------\r\n"
"1. FIXED STRING\r\n"
"2. FIXED STRING WITH BLINKING\r\n"
"3. STRING WITH SCROLLING\r\n"
"4. TIME DISPLAY\r\n"
"5. RTC DISPLAY WITH SCROLLING\r\n"
"6. TEMPERATURE DISPLAY\r\n"
"7. TEXT EDIT MODE\r\n"
"8. TIME EDIT MODE\r\n"
"9. EXIT\r\n"
"Enter Choice:\r\n";

// UART0 Interrupt Service Routine
void UART0_ISR(void) __irq
{
    unsigned int iir;

    iir = U0IIR;   // Read interrupt identification register

    // RX interrupt → data received
    if((iir & 0x04) == 0x04)
    {
        rx_data = U0RBR;   // Read received data from UART buffer
    }

    // TX interrupt → ready to send next character
    if((iir & 0x02) == 0x02)
    {
        if(menu[tx_index] != '\0')   // Check if string not finished
        {
            U0THR = menu[tx_index++];  // Send next character
        }
    }

    VICVectAddr = 0;   // Acknowledge interrupt
}

// Function to display fixed string
void fixed_string()
{
    display_str("ARIF",500);  
    // Display static text "ARIF" with delay
}

// Function to display blinking string
void blinking_string()
{    
    // Display string first
    display_str("ARIF",500);

    // Turn OFF display (clear all rows)
    CLEARBYTE(IOCLR0,0xFF);   

    delay_ms(300);   // Delay to create blinking effect
}

// Function for scrolling string display
void scrolling_string()
{
    u8 i;
    u8 user_str[] = "   V25HE4 BATCH IS TOOO GOOD BATCH!   ";

    // Scroll string character by character
    for(i = 0; i < 38-3; i++)
    {
        display_str(user_str + i,10);  
        // Shift pointer to create scrolling effect
    }		
}

// Function to send menu via UART
void UART_SendMenu()
{
    tx_index = 0;              // Reset index
    U0THR = menu[tx_index++];  // Start sending first character
}
