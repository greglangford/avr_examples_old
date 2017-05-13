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

#define NRF24_READ   0x00
#define NRF24_STATUS 0x07
