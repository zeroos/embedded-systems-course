#include <util/delay.h>

#include "Pin.h"

static Pin::Pin<2> button;
static Pin::Pin<13> led;

int main() {
  led.mode(OUTPUT);
  button.mode(INPUT_PULLUP);

  do {
    if (!button.read()) {
      led.high();
      _delay_ms(500);
      led.low();
      _delay_ms(500);
    } else {
      led.low();
    }
  } while (true);
}
