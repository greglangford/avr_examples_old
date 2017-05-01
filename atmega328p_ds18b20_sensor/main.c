#include "include/defines.h"
#include "include/uart.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>



void main() {
  char buf[50];
  uint8_t byte1, byte2;

  float temp1;

  int16_t temp;
  uart_init();


  while(1) {
  onewire_reset();

  onewire_write_byte(0xCC);
  onewire_write_byte(0x44);
  _delay_ms(1000);
  onewire_reset();
  onewire_write_byte(0xCC);
  onewire_write_byte(0xBE);
  byte1 = onewire_read_byte();
  byte2 = onewire_read_byte();

  //temp = (((int16_t) byte2) << 11) | (((int16_t) byte1) << 3);

  temp1 = ((byte2 << 8) | byte1);
  temp1 /= 16;

  sprintf(buf, "%2.2f\r\n", temp1);

  uart_putstring(buf);

  uart_putstring("\r\n");

  _delay_ms(2000);

}

}
