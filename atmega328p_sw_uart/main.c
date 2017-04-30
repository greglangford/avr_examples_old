#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>
#include "sw_uart_tx.h"
#include <stdio.h>
#include <string.h>

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

uint8_t read_bit() {
  int bit = 0;

  MASTER_TX();
  BUS_LOW();
  _delay_us(2);
  MASTER_RX();

  if(bit_is_set(PINB, PB1)) {
    bit = 1;
  }

  _delay_us(58);

  return bit;
}

uint8_t read_byte() {
  int i, byte;
  byte = 0;

  for(i = 0; i < 8; i++) {

    if(read_bit() == 1) {
      byte |= 0x01 << i;
    }
  }

  return byte;
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
  _delay_us(2);
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

float read_temp() {
  int temp = 0;
  char temp1 = 0, temp2 = 0;

  temp1 = read_byte();
  temp2 = read_byte();


  temp = ((signed int) temp2 << 8) + temp1;
  temp = temp / 16;

  issue_reset();

  return temp;
}

void main() {
  int temp;
  char buf[50];
  sw_uart_tx_init();

  sw_uart_tx_putstring("Starting up...\r\n");

  while(1) {

    /* DS18B20 start */
    issue_reset();
    detect_presence();
    write(0xCC);
    write(0x44);
    _delay_ms(750);
    issue_reset();
    detect_presence();
    write(0xCC);
    write(0xBE);

    temp = 0;
    temp = read_temp();

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "Temperature: %d\r\n", temp);

    sw_uart_tx_putstring(buf);

    _delay_ms(10000);
  }
}
