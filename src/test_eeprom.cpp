#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

#include "EEPROM.h"
#include "ProgMem.h"
#include "Serial.h"

static EEPROM::Byte counter;

int main() {
  Serial::init();
  Serial::attachStdIO();

  sei();

  while(1) {
    uint8_t n = counter.get();

    printf_P(
      PSTR("Press [i] to increment or [d] to decrement counter [%d]!\n"), n);

    int c = getchar();

    if (c == 'i')
      counter.put(++n);
    if (c == 'd')
      counter.put(--n);
  }

  return 0;
}
