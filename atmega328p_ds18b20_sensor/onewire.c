#include "include/defines.h"
#include "include/onewire.h"
#include "include/uart.h"
#include <avr/io.h>
#include <util/delay.h>

void MASTER_TX() {
  DATA_DIRECTION_REGISTER |= _BV(PORT_PIN);
}

void MASTER_RX() {
  DATA_DIRECTION_REGISTER &= ~_BV(PORT_PIN);
}

void BUS_HIGH() {
  PORT_REGISTER |= _BV(PORT_PIN);
}

void BUS_LOW() {
  PORT_REGISTER &= ~_BV(PORT_PIN);
}

void onewire_reset() {
  MASTER_TX();
  BUS_LOW();
  _delay_us(480);
  MASTER_RX();
  BUS_HIGH();
  _delay_us(10);
  while(bit_is_clear(PORT_REGISTER, PORT_PIN));
  _delay_us(420);
}

void onewire_write_bit(uint8_t bit) {
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

void onewire_write_byte(uint8_t byte) {
  uint8_t i;

  for(i = 0; i < 8; i++) {
    onewire_write_bit(byte & (1 << i));
  }
}

uint8_t onewire_read_bit() {
  uint8_t bit = 0;

  MASTER_TX();
  BUS_LOW();
  _delay_us(2);
  MASTER_RX();
  _delay_us(8);

  if(bit_is_set(PINB, PB1)) {
    bit = 1;
  }

  _delay_us(50);

  return bit;
}

uint8_t onewire_read_byte() {
  uint8_t byte = 0x00;
  uint8_t i;

  for(i = 0; i < 8; i++) {
    if(onewire_read_bit() == 1) {
      byte |= 0x01 << i;
    }
  }

  return byte;
}
