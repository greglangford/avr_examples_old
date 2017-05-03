#include "defines.h"
#include "include/hw_uart.h"
#include "include/sw_uart.h"
#include <util/delay.h>

#include <stdio.h>
#include <string.h>


void main() {
  hw_uart_init();
  sw_uart_init();

  hw_uart_putstring("Init complete ...\r\n");

  unsigned char c;
  unsigned char buf[100];
  int i;

  i = 0;

  sw_uart_putstring("AT\r\n");

  while(1) {
    c = sw_uart_getchar();
    if(c == '\0') {
      break;
    }
    buf[i] = c;
    i++;
  }

  hw_uart_putstring(buf);


}
