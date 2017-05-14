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
