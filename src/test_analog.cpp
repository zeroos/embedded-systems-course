#include <stdio.h>

#include "Analog.h"
#include "Serial.h"

int main() {
  Serial::init(38400);
  Serial::attachStdIO();

  do {
    printf_P(PSTR("value = %d\n"), Analog::read(A5));
  } while (true);

  return 0;
}
