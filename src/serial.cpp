#include <stdio.h>

#include "Serial.h"

int main() {
  Serial::init(38400);
  Serial::attach_stdio();

  char input;

  while(1) {
    puts("Hello world!");
    input = getchar();
    printf("You wrote %c\n", input);
  }

  return 0;
}
