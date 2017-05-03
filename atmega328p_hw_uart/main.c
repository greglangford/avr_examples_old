#include <avr/io.h>

void uart_init() {
  UBRR0H = (UBBR>>8);
  UBRR0L = UBBR;
  UCSR0A = 0;                           /* disable doube data rate mode */
  UCSR0B |= _BV(TXEN0);                 /* enable transmitter */
  UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);  /* 8 data bits, 1 stop bit*/
}



void main() {
  uart_init();
  char *string = "This is the string to send\r\n";

  while(1) {
    uart_putstring(string);
  }
}
