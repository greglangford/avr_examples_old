#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>

void tx_short() {
  PORTB |= _BV(PB0);
  _delay_us(375);
  PORTB &= ~_BV(PB0);
  _delay_us(790);
}

void tx_long() {
  PORTB |= _BV(PB0);
  _delay_us(958);
  PORTB &= ~_BV(PB0);
  _delay_us(208);
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

  char a = 0b01010110;
  char b = 0b00001011;
  char c = 0b11110011; // socket on
  char d = 0b01110011; // socket off

  int i;

  while(1) {

    for(i = 0; i < 6; i++) {
      tx_byte(a);
      tx_byte(b);
      tx_byte(c);
      tx_short();
      _delay_ms(8); // delay between packets
    }

    _delay_ms(5000);

    for(i = 0; i < 6; i++) {
      tx_byte(a);
      tx_byte(b);
      tx_byte(d);
      tx_short(); // transmit last 0 bit
      _delay_ms(8);
    }

    _delay_ms(5000);


  }
}
