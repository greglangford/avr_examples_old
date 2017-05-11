#define UBBR  0x33      /* 9600 baud */

void hw_uart_init();

void hw_uart_putchar(char c);

void hw_uart_putstring(char *str);
