#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>
#include "sw_uart_tx.h"

void MASTER_TX() {
  DDRB |= _BV(PB1);
}

void MASTER_RX() {
  DDRB &= ~_BV(PB1);
}

void BUS_HIGH() {
  PORTB |= _BV(PB1);
}

void BUS_LOW() {
  PORTB &= ~_BV(PB1);
}

void write_bit(uint8_t bit) {
  MASTER_TX();
  BUS_LOW();
  _delay_us(1);

  if(bit != 0) {
    BUS_HIGH();
  }

  _delay_us(59);
  MASTER_RX();
  _delay_us(1);
}

void read() {
  unsigned char c;
  int i;

  for(i = 0; i < 12; i++) {
    MASTER_TX();
    BUS_LOW();
    _delay_us(1);

    MASTER_RX();
    _delay_us(10);

    if(bit_is_set(PINB, PB1)) {
      c = '1';
    } else {
      c = '0';
    }

    _delay_us(50);

    sw_uart_tx_putchar(c);
  }

}

void write(unsigned char c) {
  int i;

  for(i = 0; i < 8; i++) {
    write_bit(c & (1<<i));
  }
}

void detect_presence() {
  MASTER_RX();
  BUS_HIGH();

  /* wait for low bus */
  loop_until_bit_is_clear(PINB, PB1);

  unsigned char *init_response = "DS18B20 init pulled line low\r\n";
  // sw_uart_tx_putstring(init_response);

  /* wait for high bus */
  loop_until_bit_is_set(PINB, PB1);

  unsigned char *init_complete = "DS18B20 init complete\r\n";
  // sw_uart_tx_putstring(init_complete);
}

void issue_reset() {
  DDRB |= _BV(PB1);     /* PB1 output */
  PORTB |= _BV(PB1);    /* PB1 high   */

  /* start init tx */
  PORTB &= ~_BV(PB1);   /* pull PB1 low */
  _delay_us(480);
  PORTB |= _BV(PB1);    /* pull PB1 high */
}

void main() {
  sw_uart_tx_init();

  while(1) {
    issue_reset();
    detect_presence();
    write(0xCC);
    write(0x44);
    issue_reset();
    detect_presence();
    write(0xCC);
    write(0xBE);
    read();

    unsigned char *c = "\r\n";

    sw_uart_tx_putstring(c);
    _delay_ms(5000);
  }
}
