#include <avr/interrupt.h>
#include <stdio.h>

#include "Analog.h"
#include "ProgMem.h"
#include "Serial.h"

/*
 * Uses 10k potentiometer connected to 5V, GND and pin A5.
 */

int main() {
  Serial::init(38400);
  Serial::attachStdIO();

  Analog::init();
  Analog::selectInput(Analog::ADC5);

  sei();

  do {
    int16_t value = Analog::read();
    printf_P(PSTR("value = %d\n"), value);
  } while (true);

  return 0;
}
