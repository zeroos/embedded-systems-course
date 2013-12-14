#include <avr/interrupt.h>
#include <stdio.h>

#include "Analog.h"
#include "ProgMem.h"
#include "Serial.h"

/*
 * Uses builtin temperature sensor.
 *
 * Following values have to be calibrated accoring to methods described in
 * "AVR122: Calibration of the AVR's internal temperature reference"
 */
const float chipTempOffset = 336.59;
const float chipTempCoeff = 1.17;

int main() {
  Serial::init();
  Serial::attachStdIO();

  Analog::init();
  Analog::selectInput(Analog::TEMPERATURE);

  sei();

  do {
    int16_t value = Analog::read();
    int16_t temp = (int16_t)(((float)value - chipTempOffset) / chipTempCoeff);
    printf_P(PSTR("value = %d, temp = %d\n"), value, temp);
  } while (true);

  return 0;
}
