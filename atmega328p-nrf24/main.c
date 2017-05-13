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

  nrf24_read_reg(NRF24_RX_P0_PAYLOAD_WIDTH, ptrval, 5);

  sprintf(debug, "[%02x] [%02x] [%02x] [%02x] [%02x]\r\n", val[0], val[1], val[2], val[3], val[4]);

  hw_uart_putstring(debug);

  while(1) {

  }

}
