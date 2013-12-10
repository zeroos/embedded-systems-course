#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/atomic.h>

#include "Pin.h"
#include "SPI.h"

/* SPI serial transfer complete interrupt */
EMPTY_INTERRUPT(SPI_STC_vect);

uint8_t SPI::transmit(uint8_t data) {
  SPDR = data;

  /* Wait for transmission completion */
  while (bit_is_clear(SPSR, SPIF))
    sleep_mode();

  return SPDR;
}
