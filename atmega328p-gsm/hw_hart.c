#include "defines.h"
#include "include/hw_uart.h"
#include <avr/io.h>

void hw_uart_init() {
  UBRR0H = (UBBR>>8);
  UBRR0L = UBBR;
  UCSR0A = 0;                           /* disable doube data rate mode */
  UCSR0B |= _BV(TXEN0);                 /* enable transmitter */
  UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);  /* 8 data bits, 1 stop bit*/
}

void hw_uart_putchar(unsigned char c) {
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = c;
}

void hw_uart_putstring(char *str) {
  while(*str) {
    hw_uart_putchar(*str++);
  }
}
