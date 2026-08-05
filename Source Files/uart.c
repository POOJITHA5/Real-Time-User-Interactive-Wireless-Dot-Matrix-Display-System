#include <LPC21xx.H>
#include "uart.h"
#include "types.h"
#define MAX 128

u8 rx_buf[MAX];
u8 rx_index = 0;
u8 rx_done = 0;
u8 rx_data=0;
u8 tx_index=0;
u32 flag=0;
extern u32 size;
// u8 rx_data;

//char menu[] =
//"\r\n------ DOT MATRIX MENU ------\r\n"
//"1. FIXED STRING\r\n"
//"2. FIXED STRING WITH BLINKING\r\n"
//"3. STRING WITH SCROLLING\r\n"
//"4. TIME DISPLAY\r\n"
//"5. RTC DISPLAY WITH SCROLLING\r\n"
//"6. TEMPERATURE DISPLAY\r\n"
//"7. TEXT EDIT MODE\r\n"
//"8. TIME EDIT MODE\r\n"
//"9. EXIT\r\n"
//"Enter Choice:\r\n";


void UART0_Init(void)
{
    PINSEL0 |= 0x00000005;   // P0.0 TXD0, P0.1 RXD0

    U0LCR = 0x83;            // 8-bit, 1 stop bit, enable divisor
    U0DLL = 97;              // 9600 baud (PCLK = 15MHz)
    U0DLM = 0;
    U0LCR = 0x03;

    U0IER = 0x03;            // Enable RX and TX interrupts

    VICVectAddr0 = (unsigned)UART0_ISR;
    VICVectCntl0 = 0x20 | 6;
    VICIntEnable = 1 << 6;
}

//void UART_SendMenu()
//{
//   // tx_index = 0;
//   // U0THR = menu[tx_index++];
//   UART0_Str(menu);
//}
void UART0_ISR(void) __irq
{

     u32 status = U0IIR;
	
    // RX interrupt
		if((status & 0x06) == 0x04)
    {
        char ch = U0RBR;
//        rx_data = ch;
//			  flag=1;
//
//        if(ch == '\r')   // ENTER pressed
//        {
//            rx_buf[rx_index] = '\0';
//            rx_index = 0;
//            rx_done = 1;
//        }
//        else
//        {
//            rx_buf[rx_index++] = ch;
//        }
	}
		
    // TX interrupt (THRE empty)
    if((status & 0x02) == 0x02)
    {
//        if(menu[tx_index] != '\0')
//        {
//            U0THR = menu[tx_index++];
//        }
//        else
//        {
//            tx_index = 0;
//            U0IER &= ~(1 << 1);   // Disable TX interrupt
//        }
    }
    VICVectAddr = 0;
}
void UART0_TxChar(char ch)
{
    U0THR = ch;
    while(!(U0LSR & (1<<5)));   // wait until transmission complete
}

void UART0_TxString(char *p)
{
    while(*p)
    {
        UART0_TxChar(*p++);
    }
}

char UART0_RxChar()
{
    while(!(U0LSR & 0x01));   // wait until data received
    return U0RBR;
}

char *UART0_RxString(char *buf)
{
    int i = 0;
    char ch;

    while(1)
    {
        ch = UART0_RxChar();

        if(ch == '\r')     // ENTER pressed
            break;

        buf[i++] = ch;
    }

    buf[i] = '\0';   // string termination

    return buf;
}

void UART0_Int(unsigned int n)
{
  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0};
  int i=0;
  if(n==0)
  {
    UART0_TxChar('0');
	return;
  }
  else
  {
     while(n>0)
	 {
	   a[i++]=(n%10)+48;
	   n=n/10;
	 }
	 --i;
	 for(;i>=0;i--)
	 {
	   UART0_TxChar(a[i]);
	 }
   }
}

void UART0_Float(float f)
{
  int x;
  float temp;
  x=f;
  UART0_Int(x);
  UART0_TxChar('.');
  temp=(f-x)*100;
  x=temp;
  UART0_Int(x);
}

/*void Text_edit()
{
	
	 UART0_TxString("1.FIXED STRING\r\n");
	 UART0_TxString("2.STRING WITH SCROLLING\r\n");
	 while(flag!=1);
	 		flag=0;
			tx_index=0;			
	 		if(rx_data==1)
			{
					while(rx_done!=1)
					rx_done=0;
	*/

