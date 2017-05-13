#include "defines.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "hw_uart.h"
#include <stdio.h>


volatile int reading;


int analogRead() {
  ADCSRA |= _BV(ADSC);
  while ( (ADCSRA & _BV(ADSC)) );

  return ADC;
}

void main() {
  hw_uart_init();

  DDRC = 0xFF;

  ADMUX |= _BV(REFS0);

  ADCSRA |= _BV(ADPS1) | _BV(ADPS2) | _BV(ADPS0) | _BV(ADEN) | _BV(ADIE);

  hw_uart_putstring("Started ...\r\n");

  char buf[50];

  int read;


  while(1) {

    read = analogRead();

    memset(buf, 0, sizeof(buf));
    sprintf(buf, "Complete: %d\r\n", read);

    hw_uart_putstring(buf);
  }
}
