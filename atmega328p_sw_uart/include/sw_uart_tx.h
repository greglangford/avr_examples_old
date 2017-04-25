#define BAUD      9600
#define BITDELAY  (1000000/BAUD)

void sw_uart_tx_init();
void sw_uart_tx_putchar(unsigned char c);
void sw_uart_tx_putstring(unsigned char *str);
