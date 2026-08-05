#include <LPC21xx.H>

#include <string.h>
#include "types.h"
#include "uart_interrupt.h"
u8 index_val,new_var,ch,t_flag,r_flag,rec_buff[100],updated_str[100]="GOOD BYE 2025";
extern u32 cnt;
u8 f=0;

#include "delay.h"
void UART_SendMenu(void);

u8 menu[] =
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
void UART_SendMenu()
{
   UART0_Str(menu);
}
void UART0_interrupt(void) __irq

{

	new_var = U0IIR;

	if(new_var & 0x04)	//RBR interrupt

	{

		ch = U0RBR;

		if(ch != 0x0d)

			rec_buff[index_val++] = ch;

		else

		{

			rec_buff[index_val] = '\0';

			r_flag = 1;
			f=1;

		}

		

	}

	else if(new_var & 0x02)	//THRE interrupt

	{

		t_flag = 1;

	}	

	

	VICVectAddr = 0;

}

void UART0_init()

{

	PINSEL0 |= (TXD0_EN | RXD0_EN);

	

	U0LCR = (WORD_LEN_SEL | (1<<DLAB_BIT));

	U0DLL = DIVISOR;

	U0DLM = DIVISOR>>8;

	U0LCR &= ~(1<<DLAB_BIT);

	

	VICVectAddr0 = (unsigned)UART0_interrupt;

	VICVectCntl0 = 0x20 | UART0_CHNO;

	VICIntEnable = 1<<UART0_CHNO;

	

	U0IER = RBR_INTERRUPT_EN|THRE_INTERRUPT_EN;

}

void UART0_Tx(unsigned char ch)

{

	t_flag = 0;

	U0THR = ch;

	while(t_flag == 0);	

}


void UART0_Str(unsigned char *str)

{

	while(*str)

		UART0_Tx(*str++);	

}
/*void display_mode(u8 ch)
{
	switch(ch)
	{
		case '1':
				UART0_Str("\r\nFixed String Mode Enabled\n\r");
				break;
		case '2':
				UART0_Str("\r\nBlinking String Mode Enabled\n\r");
				break;
		case '3':
				UART0_Str("\r\nScrolling String Mode Enabled\n\r");
				break;
		case '4':
				UART0_Str("\r\nScrolling String Mode Enabled\n\r");
				break;
		case '5':
				UART0_Str("\r\nScrolling String Mode Enabled\n\r");
				break;
		case '6':
				UART0_Str("\r\nScrolling String Mode Enabled\n\r");
				break;
	}
}						   */
