void UART_SendMenu(void);
void UART0_Init(void);
void UART0_TxChar(char ch);
void UART0_TxString(char *p);
char UART0_RxChar(void);
char *UART0_RxString(char *buf);
void UART0_Int(unsigned int);
void UART0_Float(float );
void UART0_ISR(void) __irq;
