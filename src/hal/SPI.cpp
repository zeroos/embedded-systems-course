#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "GenIOReg.h"
#include "SPI.h"

/*
 * SPI serial transfer complete interrupt.
 *
 * We cannot rely on SPIF flag in SPI::transmit waiting loop as it's cleared
 * automatically when CPU enters interrupt handler.
 */
ISR (SPI_STC_vect, ISR_NAKED) {
  bset(GIO0, SPI_IRQ);
  reti();
}

uint8_t SPI::transmit(uint8_t data) {
  SPDR = data;

  /* Wait for transmission completion */
  while (!bget(GIO0, SPI_IRQ))
    sleep_mode();

  bclr(GIO0, SPI_IRQ);

  return SPDR;
}
