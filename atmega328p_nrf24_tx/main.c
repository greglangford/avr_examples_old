#include "defines.h"
#include "main.h"
#include "hw_uart.h"
#include "nrf24l01.h"
#include "nrf24l01-mnemonics.h"
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

// stdout
FILE mystdout = FDEV_SETUP_STREAM(hw_uart_putchar, NULL, _FDEV_SETUP_WRITE);

// nrf24
nRF24L01 *rf;
char rxaddr[5] = { 0x12, 0x12, 0x12, 0x12, 0x12 };

void setup() {
  hw_uart_init();
  stdout = &mystdout;
  rf = setup_rf();
}

void main() {
  setup();
  printf("Application started\r\n");

  while(true) {
    nRF24L01Message msg;
    memcpy(msg.data, "ON", 3);
    msg.length = strlen((char *)msg.data) + 1;
    nRF24L01_transmit(rf, rxaddr, &msg);
    _delay_ms(1000);
  }
}

nRF24L01 *setup_rf(void) {
    nRF24L01 *rf = nRF24L01_init();
    rf->ss.port = &PORTB;
    rf->ss.pin = PB2;
    rf->ce.port = &PORTB;
    rf->ce.pin = PB0;
    rf->sck.port = &PORTB;
    rf->sck.pin = PB5;
    rf->mosi.port = &PORTB;
    rf->mosi.pin = PB3;
    rf->miso.port = &PORTB;
    rf->miso.pin = PB4;
    // interrupt on falling edge of INT0 (PD2)
    //EICRA |= _BV(ISC01);
    //EIMSK |= _BV(INT0);
    nRF24L01_begin(rf);
    return rf;
}
