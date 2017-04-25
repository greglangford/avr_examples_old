#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>
#include "sw_uart_tx.h"

volatile int i;

void sw_uart_tx_init() {
  DDRB |= _BV(PB0);     /* PB0 output */
  PORTB |= _BV(PB0);    /* PB0 high   */
}

void sw_uart_tx_putchar(unsigned char c) {
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

void sw_uart_tx_putstring(unsigned char *str) {
  while(*str) {
    sw_uart_tx_putchar(*str++);
  }
}
