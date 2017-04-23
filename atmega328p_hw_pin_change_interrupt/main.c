#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// PCINT0 ISR
ISR(PCINT0_vect) {
  PCMSK0 &= _BV(PCINT0);    /* disable interrupt */

  // falling edge
  if(bit_is_clear(PINB, 0)) {
    _delay_ms(300);
    PORTB ^= _BV(PB5);
  }

  PCMSK0 |= _BV(PCINT0);    /* enable interrupt */
}

void pcint_init() {
  PCICR |= _BV(PCIE0);    // enable pin change interrupt 7:0
  PCMSK0 |= _BV(PCINT0);  // enable PCINT0
}

void main() {
  pcint_init();
  DDRB |= _BV(PB5);
  PORTB |= _BV(PB0);

  sei();

  for(;;);
}
