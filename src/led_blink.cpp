#include <util/delay.h>

#include "Pin.h"

int main() {
  Pin::mode(13, OUTPUT);
  Pin::mode(2, INPUT_PULLUP);

  do {
    if (!Pin::read(2)) {
      Pin::write(13, true);
      _delay_ms(500);
      Pin::write(13, false);
      _delay_ms(500);
    } else {
      Pin::write(13, false);
    }
  } while (true);
}
