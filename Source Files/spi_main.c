#include <LPC21xx.h>
#include "types.h"
#include "delay.h"
#include "spi.h"
#include "spi_eeprom.h"
#include "spi_eeprom_defines.h"
#include "lcd.h"
#include "uart.h"

#define BLED 16
#define GLED 17

u8 t;
u8 fbuff[10];
u8 sbuff[50];

int main(void)
{
    IODIR1 |= ((1<<GLED)|(1<<BLED));
    IOCLR1 |= ((1<<GLED)|(1<<BLED));

    Init_SPI0();
    InitLCD();
	UART0_Init();

    ByteWrite_25LC512(0x0001,'1');
    delay_ms(10);

    t = ByteRead_25LC512(0x0001);
	UART0_TxChar(t);
    if(t=='1')
        IOSET1 = 1<<BLED;
    else
        IOSET1 = 1<<GLED;

				 CmdLCD(0x80);
				 UART0_TxChar('A');
				 CharLCD('A');
				 CmdLCD(0x81);
				 CharLCD(t);
				 UART0_TxChar(t);

    PageWrite_25LC512(0x0002,"ARIF");
    PageRead_25LC512(0x0002,fbuff,4);
    fbuff[4]='\0';

    CmdLCD(0xC0);
    StrLCD(fbuff);
	UART0_TxString(fbuff);

    PageWrite_25LC512(0x0008,"   V25HE4 BATCH IS BEST BATCH");
    PageRead_25LC512(0x0008,sbuff,29);
    sbuff[26]='\0';

    
		CmdLCD(0xC0);
    StrLCD(sbuff);

    while(1);
}
