#include "defines.h"
#include "include/sw_uart.h"
#include <avr/io.h>
#include <util/delay.h>

void sw_uart_init() {
  SW_UART_DDR |= _BV(SW_UART_TX_PIN);
  SW_UART_PORT |= _BV(SW_UART_TX_PIN);    /* PB0 high   */
}

void sw_uart_putchar(unsigned char c) {
  int i;

  SW_UART_PORT &= ~_BV(SW_UART_TX_PIN);   /* set line low for start bit */
  _delay_us(BITDELAY);

  for(i = 0; i < 8; i++) {
    /* high bit */
    if( (c >> i) & 0x01 ) {
      SW_UART_PORT |= _BV(SW_UART_TX_PIN);  /* set high */
    } else {
      SW_UART_PORT &= ~_BV(SW_UART_TX_PIN); /* set low */
    }

    _delay_us(BITDELAY);
  }

  /* stop bit */
  SW_UART_PORT |= _BV(SW_UART_TX_PIN);
  _delay_us(BITDELAY);
}

void sw_uart_putstring(char *str) {
  while(*str != '\0') {
    sw_uart_putchar(*str++);
  }
}

unsigned char sw_uart_getchar() {
  int i;
  unsigned char c = 0x00;

  while(bit_is_set(PINB, PB1));
    _delay_us(BITDELAY);
    _delay_us(BITDELAY / 2);

    for(i = 0; i < 8; i++) {
      if(bit_is_set(PINB, PB1)) {
        c += (1 << i);
      }

      _delay_us(BITDELAY);
    }

    if(bit_is_set(PINB, PB1)) {
      _delay_us(BITDELAY / 2);
      return c;
    } else {
      _delay_us(BITDELAY / 2);
      return 0x00;
    }
}
