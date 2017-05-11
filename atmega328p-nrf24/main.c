#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>

#define NRF24_CSN PB0
#define NRF24_CE  PB1

char nrf_write_byte(char c) {

}

void main() {

  DDRB |= _BV(NRF24_CSN) | _BV(NRF24_CE);
  SPCR |= _BV(SPE) | _BV(MSTR) | _BV(SPR0) | _BV(SPR1) | _BV(SPI2X);

  
  while(1) {

  }
}
