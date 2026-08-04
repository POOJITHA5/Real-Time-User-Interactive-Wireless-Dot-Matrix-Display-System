#define FOSC 12000000
#define CCLK1 (5*FOSC)
#define PCLK1 (CCLK1/4)
#define BAUD 9600
#define DIVISOR (PCLK1/(16*BAUD))

#define UART0_CHNO 6


#define TXD0_EN (1<<0)
#define RXD0_EN (1<<2)

#define _8BIT 3
#define WORD_LEN_SEL _8BIT
#define DLAB_BIT 7
#define DR_BIT 0
#define THRE_BIT 5
#define TEMT_BIT 6
#define RBR_INTERRUPT_EN (1<<0)
#define THRE_INTERRUPT_EN (1<<1)

void UART0_init(void);
void UART0_Tx(unsigned char);
void UART0_Str(unsigned char *);
void UART_SendMenu(void);
