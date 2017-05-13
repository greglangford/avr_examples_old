#include "defines.h"
#include "nrf24.h"
#include "spi.h"
#include <avr/io.h>
#include <util/delay.h>

void nrf24_init() {
  NRF24_DDR |= _BV(NRF24_CSN) | _BV(NRF24_CE);
  NRF24_PORT |= _BV(NRF24_CSN);
  NRF24_PORT &= ~_BV(NRF24_CE);

  spi_init();
}

void nrf24_write(uint8_t reg, uint8_t data) {
  _delay_us(10);
  NRF24_PORT &= ~_BV(NRF24_CSN);
  _delay_us(10);
  spi_write_byte(NRF24_W_REG + reg);
  _delay_us(10);
  spi_write_byte(data);
  _delay_us(10);
  NRF24_PORT |= _BV(NRF24_CSN);
}

uint8_t nrf24_read(uint8_t reg) {
  _delay_us(10);
  NRF24_PORT &= ~_BV(NRF24_CSN);
  _delay_us(10);
  spi_write_byte(reg);
  _delay_us(10);
  reg = spi_write_byte(0xFF);
  _delay_us(10);
  NRF24_PORT |= _BV(10);

  return reg;
}
