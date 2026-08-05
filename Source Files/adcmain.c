#include "types.h"          
#include "adc.h"            
#include "adc_defines.h"    
#include "uart0.h"          
#include "delay.h"          


f32 aR0, aR1;

int main(void)
{
    // Initialize UART0 for serial communication
    Init_UART0();

    // Initialize the ADC peripheral
    Init_ADC();

    // Infinite loop
    while(1)
    {
        // Read analog voltage from ADC Channel 1
        aR0 = Read_ADC(CH1);

        // Send voltage value to the serial terminal
        UART0_Tx_str("Voltage: ");
        UART0_Tx_float(aR0, 3);      // Display voltage with 3 decimal places
        UART0_Tx_str("\r\n");

        /*
        // Read ADC value again for temperature measurement
        aR1 = Read_ADC(CH1);

        // Convert voltage to temperature (LM35: 10mV/°C)
        // Temperature = Voltage × 100
        UART0_Tx_str("Temp: ");
        UART0_Tx_int(aR1 * 100);
        UART0_Tx_str("\r\n");
        */

        // Wait for 1 second before taking the next reading
        delay_ms(1000);
    }
}