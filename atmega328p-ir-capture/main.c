#include "include/defines.h"
#include "include/uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

char str[100];
volatile uint16_t Capt1, Capt2, Capt3;

uint16_t ov_counter;


ISR(TIMER1_OVF_vect){

  ov_counter++;

}

ISR(TIMER1_CAPT_vect) {
  Capt1 = ICR1;

  if(bit_is_set(PINB, PB0)) {
    TCCR1B &= ~_BV(ICES1);   // Switch to detect falling edge
    Capt1 = ICR1;
  } else {
    TCCR1B |= _BV(ICES1);   // Switch to detect rising edge
    Capt2 = ICR1;
  }

  sprintf(str, "%d", Capt1);
  uart_putstring(str);
}

void main() {
  uart_init();

  TCCR1A = 0x00;
  TCCR1B |= _BV(ICES1);   // Rising edge detect
  TCCR1C |= _BV(CS10);
  TIMSK1 |= _BV(ICIE1) | _BV(TOIE1);   // Enable interrupt
  sei();

  uart_putstring("Started up ...\r\n");

  for(;;);
}
