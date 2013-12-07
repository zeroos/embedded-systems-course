#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "Pin.h"
#include "SPI.h"

/* SPI serial transfer complete interrupt */
EMPTY_INTERRUPT(SPI_STC_vect);

void SPI::masterInit() {
  Pin::mode(MISO, INPUT);
  Pin::mode(MOSI, OUTPUT);
  Pin::mode(SCK, OUTPUT);
  Pin::mode(SS, OUTPUT);

  Pin::write(SS, true);

  /* Enable SPI, SPI_STC interrupt, master mode */
  SPCR = _BV(SPE) | _BV(SPIE) | _BV(MSTR);
  /* set clock rate F_CPU/2 */
  SPSR = _BV(SPI2X);
}

void SPI::slaveInit() {
  Pin::mode(MISO, OUTPUT);
  Pin::mode(MOSI, INPUT);
  Pin::mode(SCK, INPUT);
  Pin::mode(SS, INPUT);

  /* Enable SPI, SPI_STC interrupt, slave mode */
  SPCR = _BV(SPE) | _BV(SPIE);
}

uint8_t SPI::transmit(uint8_t data) {
  SPDR = data;

  /* Wait for transmission completion */
  while (bit_is_clear(SPSR, SPIF))
    sleep_mode();

  return SPDR;
}
