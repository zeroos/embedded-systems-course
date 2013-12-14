#include <stdio.h>

#include "ProgMem.h"
#include "Serial.h"

int main() {
  Serial::init();
  Serial::attachStdIO();

  while(1) {
    puts_P(PSTR("Hello world!"));
    char input = getchar();
    printf_P(PSTR("You wrote %c\n"), input);
  }

  return 0;
}
