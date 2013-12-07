#include <stdio.h>

#include "Serial.h"

int main() {
  Serial::init(38400);
  Serial::attachStdIO();

  while(1) {
    puts_P(PSTR("Hello world!"));
    char input = getchar();
    printf_P(PSTR("You wrote %c\n"), input);
  }

  return 0;
}
