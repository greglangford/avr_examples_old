#include <stdio.h>

// Functions
void hw_uart_init();
int hw_uart_putchar(char c, FILE *stream);

// Baud Rate
#define UBBR  0x33
