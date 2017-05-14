#include "defines.h"
#include "hw_uart.h"
#include "nrf24.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void main() {
  int i;
  char val[5];
  char *ptrval = val;

  char debug[100];

  hw_uart_init();     // Init hardware uart
  nrf24_init();       // Init nrf24

  val[0] = 0x01;
  val[1] = 0x02;
  val[2] = 0x03;
  val[3] = 0x04;
  val[4] = 0x05;

  nrf24_read_reg(0x07, ptrval, 1);
  memset(debug, 0, sizeof(debug));
  sprintf(debug, "Init Status: %02x\r\n", val[0]);
  hw_uart_putstring(debug);

  while(1) {
    nrf24_transmit_payload(val);

    nrf24_read_reg(0x07, ptrval, 1);

    sprintf(debug, "%02x\r\n", val[0]);

    hw_uart_putstring(debug);

    nrf24_reset_irq();

    _delay_ms(1000);
  }

}
