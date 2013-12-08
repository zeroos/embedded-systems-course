#include <util/delay.h>

#include "Pin.h"

static Pin::Pin<2> button;
static Pin::Pin<13> led;

int main() {
  led.mode(OUTPUT);
  button.mode(INPUT_PULLUP);

  do {
    if (!button.read()) {
      led.write(true);
      _delay_ms(500);
      led.write(false);
      _delay_ms(500);
    } else {
      led.write(false);
    }
  } while (true);
}
