#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>

void main() {

  int brightness, count;

  DDRB |= _BV(PB1) | _BV(PB0) | _BV(PB2) | _BV(PB3);

  PORTB |= _BV(PB0) | _BV(PB1) | _BV(PB2) | _BV(PB3); // all high

  OCR1A = 128;

  TCCR1A |= _BV(COM1A1);

  TCCR1A |= _BV(WGM12) | _BV(WGM11);

  TCCR1B |= _BV(CS11);

  OCR1A = 0;

  count = 1;

  while(1) {

    switch(count) {
      case 1:
        PORTB |= _BV(PB2) | _BV(PB3);
        PORTB &= ~_BV(PB0);
        break;
      case 2:
        PORTB |= _BV(PB0) | _BV(PB3);
        PORTB &= ~_BV(PB2);
        break;
      case 3:
        PORTB |= _BV(PB0) | _BV(PB2);
        PORTB &= ~_BV(PB3);
        break;
    }

    for(brightness = 10; brightness < 255; brightness++) {
      OCR1A = brightness;
      _delay_ms(5);
    }

    for(brightness = 255; brightness > 10; brightness--) {
      OCR1A = brightness;
      _delay_ms(3);
    }

    if(count == 3) {
      count = 1;
    } else {
      count++;
    }
  }
}
