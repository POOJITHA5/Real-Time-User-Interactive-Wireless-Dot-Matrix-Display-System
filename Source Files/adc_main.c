#include "types.h"          // Contains custom data types (u32, f32, etc.)
#include "adc.h"            // ADC function declarations
#include "adc_defines.h"    // ADC channel definitions and macros
#include "uart.h"           // UART communication functions
#include "delay.h"          // Delay function declarations
#include "dot_matrix.h"     // Dot matrix display functions

// Global variables
f32 eAR;                    // Stores the converted ADC voltage value
u32 adcDVal;                // Stores the raw ADC digital value

// Function prototype for Serial-In Parallel-Out (SIPO) initialization
void Init_SIPO(void);

int main(void)
{
    UART0_Init();           // Initialize UART0 for serial communication

    Init_ADC(CH1);          // Initialize ADC Channel 1

    Init_SIPO();            // Initialize SIPO shift register

    // Init_SPI0();         // SPI initialization (currently not used)

    Init_dotmatrix();       // Initialize the dot matrix display

    // Infinite loop
    while(1)
    {
        /*
        // Read ADC value (older method)
        aR0 = Read_ADC(CH1);

        // Display ADC value through UART
        UART0_TxString("Voltage: ");
        UART0_Int(aR0);
        UART0_TxString("\r\n");
        */

        // Read ADC Channel 1
        // eAR receives the converted analog voltage
        // adcDVal receives the raw ADC digital value
        Read_ADC(CH1, &eAR, &adcDVal);

        // Display temperature on the dot matrix
        // Voltage is multiplied by 100 to convert into temperature
        // Second parameter (500) specifies display delay/time
        Displaytemperature(eAR * 100, 500);

        // Send temperature value through UART
        UART0_TxString("Temp: ");
        UART0_Int(eAR * 100);
        UART0_TxString("\r\n");

        // Wait for 1 second before the next reading
        delay_ms(1000);
    }
}