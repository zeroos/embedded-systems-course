#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/atomic.h>

#include "EEPROM.h"

/*
 * The interrupt generates a constant interrupt when EEPE is cleared.
 */
ISR(EE_READY_vect, ISR_NAKED) {
  bclr(EECR, EERIE);
  reti();
}

uint8_t EEPROM::read(uint16_t address) {
  bset(EECR, EERIE);

  while (bget(EECR, EEPE))
    sleep_mode();

  /* Set up Address Register */
  EEAR = address;
  /* Start EEPROM read */
  bset(EECR, EERE);

  /* Return data from Data Register */
  return EEDR;
}

/* Note that erase & write cycle takes 3.4 ms */
void EEPROM::write(uint16_t address, uint8_t data) {
  bset(EECR, EERIE);

  while (bget(EECR, EEPE))
    sleep_mode();

  /* Set up Address and Data Registers */
  EEAR = address;
  EEDR = data;

  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    /* Enable EEPROM write for next 4 cycles.
     * Next instruction must be executed without a delay.. */
    bset(EECR, EEMPE);
    /* Start EEPROM write. */
    bset(EECR, EEPE);
  }
}
