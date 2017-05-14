#include "defines.h"
#include "hw_uart.h"
#include "nrf24.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void main() {
  hw_uart_init();     // Init hardware uart
  nrf24_init();       // Init nrf24

  while(1) {

  }
}
