#include "defines.h"
#include "hw_uart.h"
#include "nrf24.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void main() {
  char c;
  char str[50];

  hw_uart_init();
  nrf24_init();

  while(1) {

    c = nrf24_read(0x00 + 0x07);

    memset(str, 0, sizeof(str));
    sprintf(str, "Char: %02x\r\n", c);

    hw_uart_putstring(str);

    _delay_ms(5000);
  }

}
