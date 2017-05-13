void nrf24_init();
void nrf24_write_reg(char reg, char val[], char size);


/* Port Configuration */
#define NRF24_DDR  DDRB
#define NRF24_PORT PORTB
#define NRF24_CE   PB0
#define NRF24_CSN  PB2
#define NRF24_MOSI PB3
#define NRF24_SCK  PB5

/* NRF24 Memory */
#define NRF24_R_REG 0x00
#define NRF24_W_REG 0x20

#define NRF24_CONFIG                0x00
#define NRF24_AUTO_ACK              0x01
#define NRF24_RX_ADDR               0x02
#define NRF24_RF_ADDR_WIDTH         0x03
#define NRF24_RF_CHANNEL            0x05
#define NRF24_RF_CONFIG             0x06
#define NRF24_RX_P0_PAYLOAD_WIDTH   0x11
#define NRF24_RX_ADDR_P0            0x0A  // Pipe 0
#define NRF24_RX_ADDR_P1            0x0B  // Pipe 1
#define NRF24_RX_ADDR_P2            0x0C  // Pipe 2
#define NRF24_RX_ADDR_P3            0x0D  // Pipe 3
#define NRF24_RX_ADDR_P4            0x0E  // Pipe 4
#define NRF24_RX_ADDR_P5            0x0F  // Pipe 5

#define NRF24_TX_ADDR       0x10

#define NRF24_READ   0x00
#define NRF24_STATUS 0x07
