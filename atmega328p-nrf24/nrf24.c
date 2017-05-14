#include "defines.h"
#include "nrf24.h"
#include "spi.h"
#include <avr/io.h>
#include <util/delay.h>

void nrf24_init() {
  NRF24_DDR |= _BV(NRF24_CSN) | _BV(NRF24_CE);
  NRF24_PORT |= _BV(NRF24_CSN);
  NRF24_PORT &= ~_BV(NRF24_CE);

  spi_init();

  char val[5];

  // Receive address
  char rx_addr[5];
  rx_addr[0] = 0x12;
  rx_addr[1] = 0x12;
  rx_addr[2] = 0x12;
  rx_addr[3] = 0x12;
  rx_addr[4] = 0x12;

  val[0] = 0x00;
  nrf24_write_reg(NRF24_AUTO_ACK, val, 1);            // Auto Acknowledge

  val[0] = 0x01;
  nrf24_write_reg(NRF24_RX_ADDR, val, 1);             // Pipe 0

  val[0] = 0x03;
  nrf24_write_reg(NRF24_RF_ADDR_WIDTH, val, 1);       // RF Address Width 5 bytes

  val[0] = 0x01;
  nrf24_write_reg(NRF24_RF_CHANNEL, val, 1);          // RF channel

  val[0] = 0x07;
  nrf24_write_reg(NRF24_RF_CONFIG, val, 1);           // RF Configuration

  nrf24_write_reg(NRF24_RX_ADDR_P0, rx_addr, 5);       // RX Address Pipe 0
  nrf24_write_reg(NRF24_TX_ADDR, rx_addr, 5);          // TX Address

  val[0] = 0x5;
  nrf24_write_reg(NRF24_RX_P0_PAYLOAD_WIDTH, val, 1); // Payload Size 32 Bytes

  val[0] = 0x1E;
  nrf24_write_reg(NRF24_CONFIG, val, 1);              // Enable Transmitter

  _delay_ms(100);
}

void nrf24_write_reg(char reg, char *val, char size) {
  int i;

  _delay_us(10);
  NRF24_PORT &= ~_BV(NRF24_CSN);
  _delay_us(10);
  spi_write_byte(NRF24_W_REG + reg);
  _delay_us(10);

  for(i = 0; i < size; i++) {
    spi_write_byte(val[i]);
    _delay_us(10);
  }

  NRF24_PORT |= _BV(NRF24_CSN);
}

void nrf24_read_reg(char reg, char *val, char size) {
  int i;

  _delay_us(10);
  NRF24_PORT &= ~_BV(NRF24_CSN);
  _delay_us(10);
  spi_write_byte(NRF24_R_REG + reg);
  _delay_us(10);
  spi_write_byte(0xFF);   // Discard first byte (STATUS always returned first byte after command)
  _delay_us(10);

  for(i = 0; i < size; i++) {
    val[i] = spi_write_byte(0xFF);
    _delay_us(10);
  }

  NRF24_PORT |= _BV(NRF24_CSN);
}

void nrf24_transmit_payload(char *payload) {
  nrf24_write_reg(0xE1, payload, 0);    // clear tx buffer
  nrf24_write_reg(0xA0, payload, 5);    // load tx bugger

  _delay_ms(10);
  PORTB |= _BV(NRF24_CE);
  _delay_us(20);
  PORTB &= ~_BV(NRF24_CE);
  _delay_ms(10);
}

void nrf24_reset_irq() {
  _delay_us(10);
  NRF24_PORT &= ~_BV(NRF24_CSN);
  _delay_us(10);
  spi_write_byte(NRF24_W_REG + NRF24_STATUS);
  _delay_us(10);
  NRF24_PORT |= _BV(NRF24_CSN);
}
