#include <LPC21xx.h>
#include <string.h>
#include "fixed_string.h"
#include "uart_interrupt.h"
#include "spi.h"
#include "defines.h"
#include "types.h"
#include "adc.h"
#include "dot_matrix.h"
#include "adc_defines.h"
#include "spi.h"																	 
#include "spi_eeprom.h"
#include "rtc.h"
u8 t;
extern u8 f;
extern u8 tx_index;
extern u8 rx_buf[128];
u8 msg_flag=0;
u8 cnt=0;
extern u8 index_val,new_var,ch,t_flag,r_flag,rec_buff[100],updated_str[100];
int main()
{
        Init_SIPO();
       	Init_SPI0();
       	Init_dotmatrix();
	    UART0_init() ;
        RTC_Init();
        Init_ADC(CH1);
		IODIR0&=~(1<<10);
		IOCLR0=1<<10;
        while(1)
        {
			
			if(f==1)
			{
				f=0;
				if(rec_buff[0]!='!')
				{
					UART0_Str("\r\nInvalid Character\r\n");
					UART0_Str("\r\nEnter ! to Display menu and to change the mode\r\n");	
				}
			}
// Check if switch/button connected to P0.10 is pressed and counter is zero
if((IOPIN0 & (1<<10)) && cnt==0)
{
    // Display message asking user to enter '!' to open menu and change mode
    UART0_Str("\r\nEnter ! to Display menu and to change the mode\r\n");

    // Set counter to 1 to avoid repeated message display
    cnt=1;
}

// Read the stored mode value from external EEPROM (25LC512) address 0x0001
t = ByteRead_25LC512(0x0001);

// Reset buffer index value
index_val=0;

// Check if received UART data is '!' to display menu
if(rec_buff[0]=='!')
{
    // Clear receive flag after detecting menu command
    r_flag=0;

    // Reset flag variable
    f=0;

    // Clear receive buffer
    memset(rec_buff,'\0',100);

    // Send available mode selection menu through UART
    UART_SendMenu();

    // Clear lower 8 bits of IO port output
    CLEARBYTE(IOCLR0,0xFF);

    // Reset receive buffer index
    index_val=0;

    // Wait until user sends a response from UART
    while(r_flag!=1);

    // Clear receive flag after receiving response
    r_flag=0;

    // Reset flag variable
    f=0;

    // Check whether received character is between '1' and '6'
    if(rec_buff[0] >= '1' && rec_buff[0]<= '6')
    {
        // Store selected mode value into external EEPROM
        ByteWrite_25LC512(0x0001,rec_buff[0]);

        // Display message again for changing mode
        UART0_Str("\r\nEnter ! to Display menu and to change the mode\r\n");
    }

    // Store selected mode value into variable t
    t=rec_buff[0];

    // Clear message display flag
    msg_flag=0;

    // Reset receive buffer index
    index_val=0;
}
 switch(t)
                {
                        case '1':fixed_string();
                                break;

                        case '2':blinking_string();
                              	break;

                        case '3':scrolling_string();
                                break;

                        case '4':display_m_s();
                                break;
 
                        case '5':display_rtc();
                                break;
 
                        case '6': lm35();
								break;

						case '7':text_edit_mode();
								UART0_Str("Text Edited successful\r\n");
								UART0_Str("\r\nEnter ! to Display menu and to change the mode\r\n");
								break;

						case '8':time_edit_mode();
							//	UART0_Str("Time edit successful\r\n");
								UART0_Str("\r\nEnter ! to Display menu and to change the mode\r\n");
								index_val=0;
								break;

						case '9':
								break;
                }
        }
}

