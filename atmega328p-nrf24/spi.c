#include "defines.h"
#include <avr/io.h>

void spi_init() {
  // SCK, MOSI
  DDRB |= _BV(PB5) | _BV(PB3);

  // SPI Enable, SPI Master
  SPCR |= _BV(SPE) | _BV(MSTR);
}

char spi_write_byte(unsigned char c) {
  SPDR = c;
  while(!(SPSR) & (_BV(SPIF)));
  return SPDR;
}
