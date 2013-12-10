#include <avr/interrupt.h>
#include <stdio.h>

#include "EEPROM.h"
#include "ProgMem.h"
#include "Serial.h"

static EEPROM::Byte counter;

int main() {
  Serial::init(38400);
  Serial::attachStdIO();

  sei();

  while(1) {
    uint8_t c = counter.get();

    printf_P(PSTR("Counter = %d\n"), c);
    puts_P(PSTR("Enter a key to increment!"));
    (void)getchar();

    c++;

    counter.put(c);
  }

  return 0;
}
