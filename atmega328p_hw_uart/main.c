#define F_CPU 8000000UL /* 8Mhz */
#define UBBR  0x33      /* 9600 baud */

#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>

volatile int rxbuf_pos, rxbuf_ready;
unsigned char rxbuf[100];
unsigned char *ptrrxbuf = rxbuf;

void uart_init() {
  UBRR0H = (UBBR>>8);
  UBRR0L = UBBR;
  UCSR0A = 0;                                         /* disable doube data rate mode */
  UCSR0B |= _BV(TXEN0) | _BV(RXEN0) | _BV(RXCIE0);    /* enable transmitter */
  UCSR0C |= _BV(UCSZ00) | _BV(UCSZ01);                /* 8 data bits, 1 stop bit*/
}

void uart_putchar(char c) {
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = c;
}

void uart_putstring(unsigned char *str) {
  int i;

  for(i = 0; str[i] != '\0'; i++) {
    uart_putchar(str[i]);
  }
}

unsigned char uart_getchar() {
  while (!(UCSR0A & (1<<RXC0)));
  return UDR0;
}

void uart_getstring(unsigned char *str) {
  memset(rxbuf, 0, sizeof(rxbuf));  /* clear rxbuf */
  while(rxbuf_ready != 1);          /* wait until rxbuf_ready */
  strcpy(str, rxbuf);               /* copy rxbuf to pointer */
  rxbuf_ready = 0;                  /* reset ready */
}

ISR(USART_RX_vect) {
  unsigned char c;

  if((c = uart_getchar()) != '\r') {
    rxbuf[rxbuf_pos] = c;
    rxbuf_pos++;
  } else {
    rxbuf_pos = 0;
    rxbuf_ready = 1;
  }
}

void main() {
  rxbuf_pos = 0;
  rxbuf_ready = 0;

  uart_init();
  sei();

  unsigned char string[100];
  unsigned char *ptrstring = string;

  while(1) {
    uart_getstring(ptrstring);

    while(*ptrstring) {
      uart_putchar(*ptrstring);
      ++ptrstring;
    }
  }
}
