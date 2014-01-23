#include <avr/interrupt.h>
#include <avr/sleep.h>

#include "SPI.h"

/*
 * SPI transmission with default speed is so quick, that putting the
 * microcontroller into sleep mode is useless.
 */
uint8_t SPI::transmit(uint8_t data) {
  SPDR = data;

  /* Wait for transmission completion */
	loop_until_bit_is_set(SPSR, SPIF);

  return SPDR;
}
