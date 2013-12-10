#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/sleep.h>

#include "EEPROM.h"

/* EEPROM ready interrupt */
EMPTY_INTERRUPT(EE_READY_vect);

uint8_t EEPROM::read(uint16_t address) {
  while (!eeprom_is_ready())
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
  while (!eeprom_is_ready())
    sleep_mode();

  /* Set up Address and Data Registers */
  EEAR = address;
  EEDR = data;

  /* Enable EEPROM write for next 4 cycles */
  bset(EECR, EEMPE);
  /* Start EEPROM write */
  bset(EECR, EEPE);
}
