#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>

void tx_short() {
  _delay_us(1000);
  PORTB |= _BV(PB0);
  _delay_us(500);
  PORTB &= ~_BV(PB0);
}

void tx_long() {
  _delay_us(500);
  PORTB |= _BV(PB0);
  _delay_us(1000);
  PORTB &= ~_BV(PB0);
}

void tx_byte(char c) {
  int i;
  for(i = 0; i < 8; i++) {
    if((c >> i) & 0x01) {
      tx_long();
    } else {
      tx_short();
    }
  }
}

void main() {
  DDRB = _BV(PB0);
  PORTB &= ~_BV(PB0);

  char a = 0b01000110; // Socket Identifier Byte 1
  char b = 0b10110110; // Socket Identifier Byte 2

  int i;

  while(1) {

    for(i = 0; i < 50; i++) {
      tx_byte(a);
      tx_byte(b);
      tx_short(); // 25 bit seems to always be 0
      tx_short(); // 25 bit seems to always be 0
      tx_short(); // 25 bit seems to always be 0
      tx_short(); // 25 bit seems to always be 0
      tx_short(); // 25 bit seems to always be 0
      _delay_us(2900); // delay between packets
    }


    _delay_ms(5000);

  }
}
