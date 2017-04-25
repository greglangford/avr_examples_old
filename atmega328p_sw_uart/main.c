#define F_CPU 8000000UL /* 8Mhz */

#include <avr/io.h>
#include <util/delay.h>

#define BAUD      9600
#define BITDELAY  (1000000/BAUD)

volatile int i;

char *sendstring = "this is a long string\r\n";

void uart_tx(unsigned char c) {
  PORTB &= ~_BV(PB0);   /* set line low for start bit */
  _delay_us(BITDELAY);


  for(i = 0; i < 8; i++) {
    /* high bit */
    if( (c >> i) & 0x01 ) {
      PORTB |= _BV(PB0);  /* set high */
    } else {
      PORTB &= ~_BV(PB0); /* set low */
    }

    _delay_us(BITDELAY);
  }

  /* stop bit */
  PORTB |= _BV(PB0);
  _delay_us(BITDELAY);
}

void uart_putstring(char *str) {
  while(*str) {
    uart_tx(*str++);
  }
}

void main() {
  DDRB = 0xFF;
  PORTB |= _BV(PB0);    /* set line high */

  unsigned char c = 'a';

  while(1) {
    uart_putstring(sendstring);
  }
}
