#include "defines.h"
#include <avr/io.h>
#include <util/delay.h>
#include "sw_uart_tx.h"

char *sendstring = "this is a long string\r\n";

void main() {
  sw_uart_tx_init();

  while(1) {
    sw_uart_tx_putstring(sendstring);
  }
}
