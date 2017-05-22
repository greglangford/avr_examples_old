#include "defines.h"
#include "hw_uart.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "nrf24l01.h"
#include "nrf24l01-mnemonics.h"
#include "main.h"

char val[5];
char debug[100];
char to_address[5] = { 0x12, 0x12, 0x12, 0x12, 0x12 };

void main() {
  hw_uart_init();
  nRF24L01 *rf = setup_rf();

  nRF24L01_read_register(rf, 0x07, val, 1);
  memset(debug, 0, sizeof(debug));
  sprintf(debug, "Startup Status: %02x %02x %02x %02x %02x\r\n", val[0], val[1], val[2], val[3], val[4]);
  hw_uart_putstring(debug);

  while(1) {

    nRF24L01Message msg;
    memcpy(msg.data, "ON", 3);
    msg.length = strlen((char *)msg.data) + 1;
    nRF24L01_transmit(rf, to_address, &msg);
    _delay_ms(500);


    val[0] = nRF24L01_transmit_success(rf);

    memset(debug, 0, sizeof(debug));
    sprintf(debug, "%d %02x %02x %02x %02x\r\n", val[0], val[1], val[2], val[3], val[4]);
    hw_uart_putstring(debug);

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
